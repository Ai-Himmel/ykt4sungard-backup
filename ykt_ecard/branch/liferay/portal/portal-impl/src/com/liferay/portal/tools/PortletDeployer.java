/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.tools;

import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.FileUtil;
import com.liferay.util.TextFormatter;
import com.liferay.util.xml.XMLFormatter;
import com.liferay.util.xml.XMLMerger;
import com.liferay.util.xml.descriptor.FacesXMLDescriptor;

import java.io.File;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Properties;

import org.dom4j.Document;
import org.dom4j.Element;

/**
 * <a href="PortletDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 *
 */
public class PortletDeployer extends BaseDeployer {

	public static final String JSF_MYFACES =
		"org.apache.myfaces.portlet.MyFacesGenericPortlet";

	public static final String JSF_SUN =
		"com.sun.faces.portlet.FacesPortlet";

	public static final String LIFERAY_RENDER_KIT_FACTORY =
		"com.liferay.util.jsf.sun.faces.renderkit.LiferayRenderKitFactoryImpl";

	public static final String MYFACES_CONTEXT_FACTORY =
		"com.liferay.util.bridges.jsf.myfaces.MyFacesContextFactoryImpl";

	public static void main(String[] args) {
		List wars = new ArrayList();
		List jars = new ArrayList();

		for (int i = 0; i < args.length; i++) {
			if (args[i].endsWith(".war")) {
				wars.add(args[i]);
			}
			else if (args[i].endsWith(".jar")) {
				jars.add(args[i]);
			}
		}

		new PortletDeployer(wars, jars);
	}

	protected PortletDeployer() {
	}

	protected PortletDeployer(List wars, List jars) {
		super(wars, jars);
	}

	protected void checkArguments() {
		super.checkArguments();

		if (Validator.isNull(portletTaglibDTD)) {
			throw new IllegalArgumentException(
				"The system property deployer.portlet.taglib.dtd is not set");
		}
	}

	protected String getExtraContent(
			double webXmlVersion, File srcFile, String displayName)
		throws Exception {

		String extraContent = super.getExtraContent(
			webXmlVersion, srcFile, displayName);

		extraContent +=
			"<listener>" +
			"<listener-class>" +
			"com.liferay.portal.kernel.servlet.PortletContextListener" +
			"</listener-class>" +
			"</listener>";

		File facesXML = new File(srcFile + "/WEB-INF/faces-config.xml");
		File portletXML = new File(
			srcFile + "/WEB-INF/" + PortalUtil.PORTLET_XML_FILE_NAME_STANDARD);
		File webXML = new File(srcFile + "/WEB-INF/web.xml");

		extraContent += getServletContent(portletXML, webXML);

		setupJSF(facesXML, portletXML);

		if (_sunFacesPortlet) {
			extraContent +=
				"<listener>" +
				"<listener-class>" +
				"com.liferay.util.bridges.jsf.sun.LiferayConfigureListener" +
				"</listener-class>" +
				"</listener>";
		}

		return extraContent;
	}

	protected String getServletContent(File portletXML, File webXML)
		throws Exception {

		StringMaker sm = new StringMaker();

		// Add wrappers for portlets

		Document doc = PortalUtil.readDocumentFromFile(portletXML);

		Element root = doc.getRootElement();

		Iterator itr1 = root.elements("portlet").iterator();

		while (itr1.hasNext()) {
			Element portlet = (Element)itr1.next();

			String portletName = PortalUtil.getJsSafePortletId(
				portlet.elementText("portlet-name"));
			String portletClass = portlet.elementText("portlet-class");

			sm.append("<servlet>");
			sm.append("<servlet-name>");
			sm.append(portletName);
			sm.append("</servlet-name>");
			sm.append("<servlet-class>");
			sm.append("com.liferay.portal.kernel.servlet.PortletServlet");
			sm.append("</servlet-class>");
			sm.append("<init-param>");
			sm.append("<param-name>portlet-class</param-name>");
			sm.append("<param-value>");
			sm.append(portletClass);
			sm.append("</param-value>");
			sm.append("</init-param>");
			sm.append("<load-on-startup>0</load-on-startup>");
			sm.append("</servlet>");

			sm.append("<servlet-mapping>");
			sm.append("<servlet-name>");
			sm.append(portletName);
			sm.append("</servlet-name>");
			sm.append("<url-pattern>/");
			sm.append(portletName);
			sm.append("/*</url-pattern>");
			sm.append("</servlet-mapping>");
		}

		// Make sure there is a company id specified

		doc = PortalUtil.readDocumentFromFile(webXML);

		root = doc.getRootElement();

		// Remove deprecated references to SharedServletWrapper

		itr1 = root.elements("servlet").iterator();

		while (itr1.hasNext()) {
			Element servlet = (Element)itr1.next();

			String icon = servlet.elementText("icon");
			String servletName = servlet.elementText("servlet-name");
			String displayName = servlet.elementText("display-name");
			String description = servlet.elementText("description");
			String servletClass = servlet.elementText("servlet-class");
			List initParams = servlet.elements("init-param");
			String loadOnStartup = servlet.elementText("load-on-startup");
			String runAs = servlet.elementText("run-as");
			List securityRoleRefs = servlet.elements("security-role-ref");

			if ((servletClass != null) &&
				(servletClass.equals(
					"com.liferay.portal.servlet.SharedServletWrapper"))) {

				sm.append("<servlet>");

				if (icon != null) {
					sm.append("<icon>");
					sm.append(icon);
					sm.append("</icon>");
				}

				if (servletName != null) {
					sm.append("<servlet-name>");
					sm.append(servletName);
					sm.append("</servlet-name>");
				}

				if (displayName != null) {
					sm.append("<display-name>");
					sm.append(displayName);
					sm.append("</display-name>");
				}

				if (description != null) {
					sm.append("<description>");
					sm.append(description);
					sm.append("</description>");
				}

				Iterator itr2 = initParams.iterator();

				while (itr2.hasNext()) {
					Element initParam = (Element)itr2.next();

					String paramName = initParam.elementText("param-name");
					String paramValue = initParam.elementText("param-value");

					if ((paramName != null) &&
						(paramName.equals("servlet-class"))) {

						sm.append("<servlet-class>");
						sm.append(paramValue);
						sm.append("</servlet-class>");
					}
				}

				itr2 = initParams.iterator();

				while (itr2.hasNext()) {
					Element initParam = (Element)itr2.next();

					String paramName = initParam.elementText("param-name");
					String paramValue = initParam.elementText("param-value");
					String paramDesc = initParam.elementText("description");

					if ((paramName != null) &&
						(!paramName.equals("servlet-class"))) {

						sm.append("<init-param>");
						sm.append("<param-name>");
						sm.append(paramName);
						sm.append("</param-name>");

						if (paramValue != null) {
							sm.append("<param-value>");
							sm.append(paramValue);
							sm.append("</param-value>");
						}

						if (paramDesc != null) {
							sm.append("<description>");
							sm.append(paramDesc);
							sm.append("</description>");
						}

						sm.append("</init-param>");
					}
				}

				if (loadOnStartup != null) {
					sm.append("<load-on-startup>");
					sm.append(loadOnStartup);
					sm.append("</load-on-startup>");
				}

				if (runAs != null) {
					sm.append("<run-as>");
					sm.append(runAs);
					sm.append("</run-as>");
				}

				itr2 = securityRoleRefs.iterator();

				while (itr2.hasNext()) {
					Element roleRef = (Element)itr2.next();

					String roleDesc = roleRef.elementText("description");
					String roleName = roleRef.elementText("role-name");
					String roleLink = roleRef.elementText("role-link");

					sm.append("<security-role-ref>");

					if (roleDesc != null) {
						sm.append("<description>");
						sm.append(roleDesc);
						sm.append("</description>");
					}

					if (roleName != null) {
						sm.append("<role-name>");
						sm.append(roleName);
						sm.append("</role-name>");
					}

					if (roleLink != null) {
						sm.append("<role-link>");
						sm.append(roleLink);
						sm.append("</role-link>");
					}

					sm.append("</security-role-ref>");
				}

				sm.append("</servlet>");
			}
		}

		return sm.toString();
	}

	protected void processPluginPackageProperties(
			File srcFile, String displayName, PluginPackage pluginPackage)
		throws Exception {

		if (pluginPackage == null) {
			return;
		}

		Properties props = getPluginPackageProperties(srcFile);

		if ((props == null) || (props.size() == 0)) {
			return;
		}

		String moduleGroupId = pluginPackage.getGroupId();
		String moduleArtifactId = pluginPackage.getArtifactId();
		String moduleVersion = pluginPackage.getVersion();

		String pluginName = pluginPackage.getName();
		String pluginType = (String)pluginPackage.getTypes().get(0);
		String pluginTypeName = TextFormatter.format(
			pluginType, TextFormatter.J);

		if (!pluginType.equals("portlet")) {
			return;
		}

		String tags = getPluginPackageTagsXml(pluginPackage.getTags());
		String shortDescription = pluginPackage.getShortDescription();
		String longDescription = pluginPackage.getLongDescription();
		String changeLog = pluginPackage.getChangeLog();
		String pageURL = pluginPackage.getPageURL();
		String author = pluginPackage.getAuthor();
		String licenses = getPluginPackageLicensesXml(
			pluginPackage.getLicenses());
		String liferayVersions = getPluginPackageLiferayVersionsXml(
			pluginPackage.getLiferayVersions());

		Map filterMap = new HashMap();

		filterMap.put("module_group_id", moduleGroupId);
		filterMap.put("module_artifact_id", moduleArtifactId);
		filterMap.put("module_version", moduleVersion);

		filterMap.put("plugin_name", pluginName);
		filterMap.put("plugin_type", pluginType);
		filterMap.put("plugin_type_name", pluginTypeName);

		filterMap.put("tags", tags);
		filterMap.put("short_description", shortDescription);
		filterMap.put("long_description", longDescription);
		filterMap.put("change_log", changeLog);
		filterMap.put("page_url", pageURL);
		filterMap.put("author", author);
		filterMap.put("licenses", licenses);
		filterMap.put("liferay_versions", liferayVersions);

		copyDependencyXml(
			"liferay-plugin-package.xml", srcFile + "/WEB-INF", filterMap,
			true);
	}

	protected void setupJSF(File facesXML, File portletXML) throws Exception {
		_myFacesPortlet = false;
		_sunFacesPortlet = false;

		if (!facesXML.exists()) {
			return;
		}

		// portlet.xml

		Document doc = PortalUtil.readDocumentFromFile(portletXML, true);

		Element root = doc.getRootElement();

		List elements = root.elements("portlet");

		Iterator itr = elements.iterator();

		while (itr.hasNext()) {
			Element portlet = (Element)itr.next();

			String portletClass = portlet.elementText("portlet-class");

			if (portletClass.equals(JSF_MYFACES)) {
				_myFacesPortlet = true;

				break;
			}
			else if (portletClass.equals(JSF_SUN)) {
				_sunFacesPortlet = true;

				break;
			}
		}

		// faces-config.xml

		doc = PortalUtil.readDocumentFromFile(facesXML, true);

		root = doc.getRootElement();

		Element factoryEl = root.element("factory");

		Element renderKitFactoryEl = null;
		Element facesContextFactoryEl = null;

		if (factoryEl == null) {
			factoryEl = root.addElement("factory");
		}

		renderKitFactoryEl = factoryEl.element("render-kit-factory");
		facesContextFactoryEl = factoryEl.element("faces-context-factory");

		if ((appServerType.equals("orion") && (_sunFacesPortlet) &&
			(renderKitFactoryEl == null))) {

			renderKitFactoryEl = factoryEl.addElement("render-kit-factory");

			renderKitFactoryEl.addText(LIFERAY_RENDER_KIT_FACTORY);
		}
		else if (_myFacesPortlet && (facesContextFactoryEl == null)) {
			facesContextFactoryEl =
				factoryEl.addElement("faces-context-factory");

			facesContextFactoryEl.addText(MYFACES_CONTEXT_FACTORY);
		}

		if (!appServerType.equals("orion") && (_sunFacesPortlet)) {
			factoryEl.detach();
		}

		XMLMerger merger = new XMLMerger(new FacesXMLDescriptor());

		merger.organizeXML(doc);

		FileUtil.write(facesXML, XMLFormatter.toString(doc), true);
	}

	protected void updateDeployDirectory(File srcFile) throws Exception {
		try {
			if (!PrefsPropsUtil.getBoolean(
					PropsUtil.AUTO_DEPLOY_CUSTOM_PORTLET_XML,
					PropsValues.AUTO_DEPLOY_CUSTOM_PORTLET_XML)) {

				return;
			}
		}
		catch (Exception e) {

			// This will only happen when running the deploy tool in Ant in the
			// classical way where the WAR file is actually massaged and
			// packaged.

			if (!PropsValues.AUTO_DEPLOY_CUSTOM_PORTLET_XML) {
				return;
			}
		}

		File portletXML = new File(
			srcFile + "/WEB-INF/" + PortalUtil.PORTLET_XML_FILE_NAME_STANDARD);

		if (portletXML.exists()) {
			File portletCustomXML = new File(
				srcFile + "/WEB-INF/" +
					PortalUtil.PORTLET_XML_FILE_NAME_CUSTOM);

			if (portletCustomXML.exists()) {
				portletCustomXML.delete();
			}

			portletXML.renameTo(portletCustomXML);
		}
	}

	private boolean _myFacesPortlet;
	private boolean _sunFacesPortlet;

}