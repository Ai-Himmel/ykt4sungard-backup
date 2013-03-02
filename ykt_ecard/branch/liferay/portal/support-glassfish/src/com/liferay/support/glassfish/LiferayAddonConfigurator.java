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

package com.liferay.support.glassfish;

import com.sun.appserv.addons.AddonException;
import com.sun.appserv.addons.AddonVersion;
import com.sun.appserv.addons.ConfigurationContext.ConfigurationType;
import com.sun.appserv.addons.ConfigurationContext;
import com.sun.appserv.addons.Configurator;
import com.sun.appserv.addons.InstallationContext;
import com.sun.jbi.management.internal.support.JarFactory;
import com.sun.org.apache.xpath.internal.XPathAPI;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

import java.util.Properties;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Node;

/**
 * <a href="LiferayAddonConfigurator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raju Uppalapati
 * @author Brian Wing Shun Chan
 *
 */
public class LiferayAddonConfigurator implements Configurator {

	public void configure(ConfigurationContext cc) throws AddonException {
		try {
			doConfigure(cc);
		}
		catch (Exception e) {
			e.printStackTrace();

			throw new AddonException(e);
		}
	}

	public void disable(ConfigurationContext cc) throws AddonException {
	}

	public void enable(ConfigurationContext cc) throws AddonException {
	}

	public void unconfigure(ConfigurationContext cc) throws AddonException {
		try {
			doUnconfigure(cc);
		}
		catch (Exception e) {
			e.printStackTrace();

			throw new AddonException(e);
		}
	}

	public void upgrade(ConfigurationContext cc, AddonVersion av)
		throws AddonException {
	}

	protected void doConfigure(ConfigurationContext cc) throws Exception {
		InstallationContext ic = cc.getInstallationContext();

		String rootDir = ic.getInstallationDirectory().getAbsolutePath();
		String domainDir = cc.getDomainDirectory().getAbsolutePath();

		File tmpDir = LiferayAddonUtil.getTmpDir();

		JarFactory jarFactory = new JarFactory(tmpDir.getAbsolutePath());

		File liferayConfiguratorJar = new File(
			rootDir + "/lib/addons/liferay_configurator.jar");

		jarFactory.unJar(liferayConfiguratorJar);

		LiferayAddonUtil.copyFile(
			tmpDir + "/lportal.properties",
			domainDir + "/config/lportal.properties");

		LiferayAddonUtil.copyFile(
			tmpDir + "/lportal.script",
			domainDir + "/config/lportal.script");

		StringBuffer jarFiles = new StringBuffer();
		StringBuffer warFiles = new StringBuffer();

		File[] files = tmpDir.listFiles();

		for (int i = 0; i < files.length; i++) {
			File file = (File)files[i];

			String name = file.getName().toLowerCase();

			if (name.endsWith(".jar")) {
				LiferayAddonUtil.copyFile(
					file, new File(domainDir + "/lib/" + file.getName()));

				jarFiles.append(file.getName());
				jarFiles.append(":");
			}
			else if (name.endsWith(".war")) {
				LiferayAddonUtil.copyFile(
					file,
					new File(domainDir + "/autodeploy/" + file.getName()));

				warFiles.append(file.getName());
				warFiles.append(":");
			}
		}

		Properties props = new Properties();

		props.setProperty("jar.files", jarFiles.toString());
		props.setProperty("war.files", warFiles.toString());

		File propsFile = new File(domainDir + "/lib/liferay_addon.properties");

		FileOutputStream fos = new FileOutputStream(propsFile);

		props.store(fos, "");

		fos.close();

		ConfigurationType configurationType = cc.getConfigurationType();

		if (configurationType == ConfigurationType.DAS) {
			configureDomainXml(
				rootDir + "/lib/dtds",
				new File(domainDir + "/config/domain.xml"),
				new File(tmpDir + "/update-domain.xml"));
		}
	}

	protected void doUnconfigure(ConfigurationContext cc) throws Exception {
		String domainDir = cc.getDomainDirectory().getAbsolutePath();

		Properties props = new Properties();

		File propsFile = new File(domainDir + "/lib/liferay_addon.properties");

		FileInputStream fis = new FileInputStream(propsFile);

		props.load(fis);

		fis.close();

		String[] jarFiles = props.getProperty("jar.files", "").split(":");

		for (int i = 0; i < jarFiles.length; i++) {
			File file = new File(domainDir + "/lib/" + jarFiles[i]);

			if (file.exists() && file.isFile()) {
				file.delete();
			}
		}

		String[] warFiles = props.getProperty("war.files", "").split(":");

		for (int i = 0; i < warFiles.length; i++) {
			File file = new File(domainDir + "/autodeploy/" + warFiles[i]);

			if (file.exists() && file.isFile()) {
				file.delete();
			}
		}

		propsFile.delete();

		ConfigurationType ct = cc.getConfigurationType();

		if (ct == ConfigurationType.DAS) {
		}
	}

	protected void configureDomainXml(
			String dtdDir, File curDomainXmlFile, File newDomainXmlFile)
		throws Exception {

		DocumentBuilderFactory documentBuilderFactory =
			DocumentBuilderFactory.newInstance();

		documentBuilderFactory.setValidating(false);

		DocumentBuilder documentBuilder =
			documentBuilderFactory.newDocumentBuilder();

		DTDResolver dtdResolver = new DTDResolver(dtdDir);

		documentBuilder.setEntityResolver(dtdResolver);
		documentBuilder.setErrorHandler(dtdResolver);

		Document curDomainXmlDoc = documentBuilder.parse(curDomainXmlFile);

		Node curResourcesNode = XPathAPI.selectSingleNode(
			curDomainXmlDoc, "/domain/resources");

		Node curJdbcResourceNode = XPathAPI.selectSingleNode(
			curDomainXmlDoc, "/domain/resources/jdbc-resource");

		Node curJdbcConnectionPoolNode = XPathAPI.selectSingleNode(
			curDomainXmlDoc, "/domain/resources/jdbc-connection-pool");

		Node curServerNode = XPathAPI.selectSingleNode(
			curDomainXmlDoc, "/domain/servers/server[@name='server']");

		Node curResourceRefNode = XPathAPI.selectSingleNode(
			curDomainXmlDoc, "/domain/servers/*/resource-ref[last()]");

		Document newDomainXmlDoc = documentBuilder.parse(newDomainXmlFile);

		Node newJdbcResourceNode = XPathAPI.selectSingleNode(
			newDomainXmlDoc, "/domain/resources/jdbc-resource");

		Node newMailResourceNode = XPathAPI.selectSingleNode(
			newDomainXmlDoc, "/domain/resources/mail-resource");

		Node newJdbcConnectionPoolNode = XPathAPI.selectSingleNode(
			newDomainXmlDoc, "/domain/resources/jdbc-connection-pool");

		Node newLiferayPoolResourceRefNode = XPathAPI.selectSingleNode(
			newDomainXmlDoc,
			"/domain/servers/*/resource-ref[@ref='jdbc/LiferayPool']");

		Node newMailSessionResourceRefNode = XPathAPI.selectSingleNode(
			newDomainXmlDoc,
			"/domain/servers/*/resource-ref[@ref='mail/MailSession']");

		curResourcesNode.insertBefore(
			curDomainXmlDoc.importNode(newJdbcResourceNode, true),
			curJdbcResourceNode);

		curResourcesNode.insertBefore(
			curDomainXmlDoc.importNode(newMailResourceNode, true),
			curJdbcConnectionPoolNode);

		curResourcesNode.insertBefore(
			curDomainXmlDoc.importNode(newJdbcConnectionPoolNode, true),
			curJdbcConnectionPoolNode);

		curServerNode.insertBefore(
			curDomainXmlDoc.importNode(newLiferayPoolResourceRefNode, true),
			curResourceRefNode);

		curServerNode.insertBefore(
			curDomainXmlDoc.importNode(newMailSessionResourceRefNode, true),
			curResourceRefNode);

		LiferayAddonUtil.copyFile(
			curDomainXmlFile,
			new File(
				curDomainXmlFile + ".bak." + LiferayAddonUtil.getTimestamp()));

		Document curDoc = curResourcesNode.getOwnerDocument();

		Source input = new DOMSource(curDoc);

		Result output = new StreamResult(
			new FileOutputStream(curDomainXmlFile));

		TransformerFactory transformerFactory =
			TransformerFactory.newInstance();

		Transformer transformer = transformerFactory.newTransformer();

		transformer.setOutputProperty(
			OutputKeys.DOCTYPE_PUBLIC, curDoc.getDoctype().getPublicId());
		transformer.setOutputProperty(
			OutputKeys.DOCTYPE_SYSTEM, curDoc.getDoctype().getSystemId());
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		transformer.setOutputProperty(OutputKeys.METHOD, "xml");
		transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");

		transformer.transform(input, output);
	}

}