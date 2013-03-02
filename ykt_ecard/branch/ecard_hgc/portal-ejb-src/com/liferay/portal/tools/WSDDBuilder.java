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

import com.liferay.portal.util.EntityResolver;
import com.liferay.util.FileUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.TextFormatter;
import com.liferay.util.ant.Java2WsddTask;
import com.liferay.util.xml.XMLFormatter;

import java.io.File;
import java.io.IOException;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="WSDDBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class WSDDBuilder {

	public static void main(String[] args) {
		if (args.length == 2) {
			new WSDDBuilder(args[0], args[1]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public WSDDBuilder(String fileName, String serverConfigFileName) {
		try {
			_serverConfigFileName = serverConfigFileName;

			SAXReader reader = new SAXReader(true);
			reader.setEntityResolver(new EntityResolver());

			Document doc = reader.read(new File(fileName));

			Element root = doc.getRootElement();

			String packageDir = root.attributeValue("package-dir");

			_portletName = root.element("portlet").attributeValue("name");

			_portletPackageName =
				TextFormatter.format(_portletName, TextFormatter.B);

			_outputPath =
				"src/" + StringUtil.replace(packageDir, ".", "/") + "/" +
					_portletPackageName + "/service/http";

			_packagePath = packageDir + "." + _portletPackageName;

			List entities = root.elements("entity");

			Iterator itr = entities.iterator();

			while (itr.hasNext()) {
				Element entity = (Element)itr.next();

				String entityName = entity.attributeValue("name");

				_createServiceWSDD(entityName);
				_createServerConfig(entityName);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void _createServiceWSDD(String entityName) throws IOException {
		String className =
			_packagePath + ".service.http." + entityName + "ServiceSoap";

		String serviceName = StringUtil.replace(_portletName, " ", "_");

		if (!_portletName.equals("Portal")) {
			serviceName = "Portlet_" + serviceName;
		}

		serviceName += ("_" + entityName + "Service");

		String[] wsdds = Java2WsddTask.generateWsdd(className, serviceName);

		_writeFile(
			new File(_outputPath + "/" + entityName + "Service_deploy.wsdd"),
			wsdds[0]);

		_writeFile(
			new File(_outputPath + "/" + entityName + "Service_undeploy.wsdd"),
			wsdds[1]);
	}

	private void _createServerConfig(String entityName)
		throws DocumentException, IOException {

		// WSDD

		File wsddFile = new File(
			_outputPath + "/" + entityName + "Service_deploy.wsdd");

		SAXReader reader = new SAXReader();

		Document doc = reader.read(wsddFile);

		Element root = doc.getRootElement();

		Element selService = root.element("service");

		if (selService == null) {
			return;
		}

		selService.detach();

		// Server Config

		File serverConfigFile = new File(_serverConfigFileName);

		reader = new SAXReader();

		doc = reader.read(serverConfigFile);

		root = doc.getRootElement();

		Map servicesMap = new TreeMap();

		Iterator itr = root.elements("service").iterator();

		while (itr.hasNext()) {
			Element service = (Element)itr.next();

			String name = service.attributeValue("name");

			servicesMap.put(name, service);

			service.detach();
		}

		servicesMap.put(selService.attributeValue("name"), selService);

		itr = servicesMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name = (String)entry.getKey();
			Element service = (Element)entry.getValue();

			root.add(service);
		}

		_writeFile(serverConfigFile, XMLFormatter.toString(doc));
	}

	public void _writeFile(File file, String newContent) throws IOException {
		String oldContent = null;
		if (file.exists()) {
			oldContent = FileUtil.read(file);
		}

		if ((oldContent == null) || (!oldContent.equals(newContent))) {
			FileUtil.write(file, newContent);
		}
	}

	private String _serverConfigFileName;
	private String _portletName;
	private String _portletShortName;
	private String _portletPackageName;
	private String _outputPath;
	private String _packagePath;

}