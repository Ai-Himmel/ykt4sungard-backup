/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.portal.servlet.PortletServlet;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.EntityResolver;
import com.liferay.util.FileUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.xml.XMLFormatter;
import com.liferay.util.xml.XMLMerger;
import com.liferay.util.xml.descriptor.FacesXMLDescriptor;

import java.io.File;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="PortletDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.40 $
 *
 */
public class PortletDeployer extends BaseDeployer {

	public static void main(String[] args) {
		if (args.length >= 2) {
			List jars = new ArrayList();

			for (int i = 0; i < args.length; i++) {
				jars.add(args[i]);
			}

			new PortletDeployer(jars);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	protected PortletDeployer(List jars) {
		super(jars);
	}

	protected void checkArguments() {
		super.checkArguments();

		if (Validator.isNull(portletTaglibDTD)) {
			throw new IllegalArgumentException(
				"The system property deployer.portlet.taglib.dtd is not set");
		}
	}

	protected String getExtraContent(File srcFile, String displayName)
		throws Exception {

		String extraContent = super.getExtraContent(srcFile, displayName);

		extraContent +=
			"<listener>" +
			"<listener-class>" +
			"com.liferay.portal.servlet.PortletContextListener" +
			"</listener-class>" +
			"</listener>";

		File facesXML = new File(srcFile + "/WEB-INF/faces-config.xml");
		File portletXML = new File(srcFile + "/WEB-INF/portlet.xml");
		File webXML = new File(srcFile + "/WEB-INF/web.xml");

		extraContent += _getServletContent(portletXML, webXML);

		_setupJSF(facesXML, portletXML);

		if (_sunFacesPortlet) {
			extraContent +=
				"<listener>" +
				"<listener-class>" +
				"com.sun.faces.config.LiferayConfigureListener" +
				"</listener-class>" +
				"</listener>";
		}

		return extraContent;
	}

	private String _getServletContent(File portletXML, File webXML)
		throws Exception {

		FastStringBuffer sb = new FastStringBuffer();

		SAXReader reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		// Add wrappers for portlets

		Document doc = reader.read(portletXML);

		Element root = doc.getRootElement();

		Iterator itr1 = root.elements("portlet").iterator();

		while (itr1.hasNext()) {
			Element portlet = (Element)itr1.next();

			String portletName = portlet.elementText("portlet-name");
			String portletClass = portlet.elementText("portlet-class");

			sb.append("<servlet>");
			sb.append("<servlet-name>");
			sb.append(portletName);
			sb.append("</servlet-name>");
			sb.append("<servlet-class>");
			sb.append(PortletServlet.class.getName());
			sb.append("</servlet-class>");
			sb.append("<init-param>");
			sb.append("<param-name>portlet-class</param-name>");
			sb.append("<param-value>");
			sb.append(portletClass);
			sb.append("</param-value>");
			sb.append("</init-param>");
			sb.append("<load-on-startup>0</load-on-startup>");
			sb.append("</servlet>");

			sb.append("<servlet-mapping>");
			sb.append("<servlet-name>");
			sb.append(portletName);
			sb.append("</servlet-name>");
			sb.append("<url-pattern>/");
			sb.append(portletName);
			sb.append("/*</url-pattern>");
			sb.append("</servlet-mapping>");
		}

		// Make sure there is a company id specified

		doc = reader.read(webXML);

		root = doc.getRootElement();

		boolean hasCompanyId = false;

		itr1 = root.elements("context-param").iterator();

		while (itr1.hasNext()) {
			Element contextParam = (Element)itr1.next();

			String paramName = contextParam.elementText("param-name");

			if ((paramName != null) && (paramName.equals("company_id"))) {
				hasCompanyId = true;

				break;
			}
		}

		if (!hasCompanyId) {
			sb.append("<context-param>");
			sb.append("<param-name>company_id</param-name>");
			sb.append("<param-value>liferay.com</param-value>");
			sb.append("</context-param>");
		}

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

				sb.append("<servlet>");

				if (icon != null) {
					sb.append("<icon>");
					sb.append(icon);
					sb.append("</icon>");
				}

				if (servletName != null) {
					sb.append("<servlet-name>");
					sb.append(servletName);
					sb.append("</servlet-name>");
				}

				if (displayName != null) {
					sb.append("<display-name>");
					sb.append(displayName);
					sb.append("</display-name>");
				}

				if (description != null) {
					sb.append("<description>");
					sb.append(description);
					sb.append("</description>");
				}

				Iterator itr2 = initParams.iterator();

				while (itr2.hasNext()) {
					Element initParam = (Element)itr2.next();

					String paramName = initParam.elementText("param-name");
					String paramValue = initParam.elementText("param-value");
					String paramDesc = initParam.elementText("description");

					if ((paramName != null) &&
						(paramName.equals("servlet-class"))) {

						sb.append("<servlet-class>");
						sb.append(paramValue);
						sb.append("</servlet-class>");
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

						sb.append("<init-param>");
						sb.append("<param-name>");
						sb.append(paramName);
						sb.append("</param-name>");

						if (paramValue != null) {
							sb.append("<param-value>");
							sb.append(paramValue);
							sb.append("</param-value>");
						}

						if (paramDesc != null) {
							sb.append("<description>");
							sb.append(paramDesc);
							sb.append("</description>");
						}

						sb.append("</init-param>");
					}
				}

				if (loadOnStartup != null) {
					sb.append("<load-on-startup>");
					sb.append(loadOnStartup);
					sb.append("</load-on-startup>");
				}

				if (runAs != null) {
					sb.append("<run-as>");
					sb.append(runAs);
					sb.append("</run-as>");
				}

				itr2 = securityRoleRefs.iterator();

				while (itr2.hasNext()) {
					Element roleRef = (Element)itr2.next();

					String roleDesc = roleRef.elementText("description");
					String roleName = roleRef.elementText("role-name");
					String roleLink = roleRef.elementText("role-link");

					sb.append("<security-role-ref>");

					if (roleDesc != null) {
						sb.append("<description>");
						sb.append(roleDesc);
						sb.append("</description>");
					}

					if (roleName != null) {
						sb.append("<role-name>");
						sb.append(roleName);
						sb.append("</role-name>");
					}

					if (roleLink != null) {
						sb.append("<role-link>");
						sb.append(roleLink);
						sb.append("</role-link>");
					}

					sb.append("</security-role-ref>");
				}

				sb.append("</servlet>");
			}
		}

		return sb.toString();
	}

	private void _setupJSF(File facesXML, File portletXML) throws Exception {
		_myFacesPortlet = false;
		_sunFacesPortlet = false;

		if (!facesXML.exists()) {
			return;
		}

		// portlet.xml

		SAXReader reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(portletXML);

		Element root = doc.getRootElement();

		List elements = root.elements("portlet");

		Iterator itr = elements.iterator();

		while (itr.hasNext()) {
			Element portlet = (Element)itr.next();

			String portletClass = portlet.elementText("portlet-class");

			if (portletClass.equals(Constants.JSF_MYFACES)) {
				_myFacesPortlet = true;

				break;
			}
			else if (portletClass.equals(Constants.JSF_SUN)) {
				_sunFacesPortlet = true;

				break;
			}
		}

		// faces-config.xml

		reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		doc = reader.read(facesXML);

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

			renderKitFactoryEl.addText(Constants.LIFERAY_RENDER_KIT_FACTORY);
		}
		else if (_myFacesPortlet && (facesContextFactoryEl == null)) {
			facesContextFactoryEl =
				factoryEl.addElement("faces-context-factory");

			facesContextFactoryEl.addText(Constants.MYFACES_CONTEXT_FACTORY);
		}

		if (!appServerType.equals("orion") && (_sunFacesPortlet)) {
			factoryEl.detach();
		}

		XMLMerger merger = new XMLMerger(new FacesXMLDescriptor());

		merger.organizeXML(doc);

		FileUtil.write(facesXML, XMLFormatter.toString(doc), true);
	}

	private boolean _myFacesPortlet;
	private boolean _sunFacesPortlet;

}