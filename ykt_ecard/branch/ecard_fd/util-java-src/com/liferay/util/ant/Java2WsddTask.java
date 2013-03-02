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

package com.liferay.util.ant;

import com.liferay.util.FileUtil;
import com.liferay.util.Html;
import com.liferay.util.StringUtil;
import com.liferay.util.xml.XMLFormatter;

import java.io.File;
import java.io.IOException;

import java.text.SimpleDateFormat;

import java.util.Date;

import org.apache.axis.tools.ant.wsdl.Java2WsdlAntTask;
import org.apache.axis.tools.ant.wsdl.NamespaceMapping;
import org.apache.axis.tools.ant.wsdl.Wsdl2javaAntTask;
import org.apache.tools.ant.Project;

import org.dom4j.DocumentException;

/**
 * <a href="Java2WsddTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Unknown
 * @version $Rev: $
 *
 */
public class Java2WsddTask {

	public static String[] generateWsdd(String className, String serviceName)
		throws IOException {

		// Create temp directory

		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddkkmmssSSS");

		File tempDir = new File(sdf.format(new Date()));

		tempDir.mkdir();

		// axis-java2wsdl

		String wsdlFileName = tempDir + "/service.wsdl";

		int pos = className.lastIndexOf(".");

		String packagePath = className.substring(0, pos);

		String[] packagePaths = StringUtil.split(packagePath, ".");

		String namespace = "urn:";

		for (int i = packagePaths.length - 1; i >= 0; i--) {
			namespace += packagePaths[i];

			if (i > 0) {
				namespace += ".";
			}
		}

		String location = "http://localhost/services/" + serviceName;

		String mappingPackage = packagePath.substring(
			0, packagePath.lastIndexOf(".")) + ".ws";

		Project project = AntUtil.getProject();

		Java2WsdlAntTask java2Wsdl = new Java2WsdlAntTask();

		NamespaceMapping mapping = new NamespaceMapping();
		mapping.setNamespace(namespace);
		mapping.setPackage(mappingPackage);

		java2Wsdl.setProject(project);
		java2Wsdl.setClassName(className);
		java2Wsdl.setOutput(new File(wsdlFileName));
		java2Wsdl.setLocation(location);
		java2Wsdl.setNamespace(namespace);
		java2Wsdl.addMapping(mapping);

		java2Wsdl.execute();

		// axis-wsdl2java

		Wsdl2javaAntTask wsdl2Java = new Wsdl2javaAntTask();

		wsdl2Java.setProject(project);
		wsdl2Java.setURL(wsdlFileName);
		wsdl2Java.setOutput(tempDir);
		wsdl2Java.setServerSide(true);
		wsdl2Java.setTestCase(false);
		wsdl2Java.setVerbose(false);

		wsdl2Java.execute();

		// Get content

		String deployContent = FileUtil.read(
			tempDir + "/" + StringUtil.replace(packagePath, ".", "/") +
				"/deploy.wsdd");

		deployContent = StringUtil.replace(
			deployContent, packagePath + "." + serviceName + "SoapBindingImpl",
			className);

		deployContent = _format(deployContent);

		String undeployContent = FileUtil.read(
			tempDir + "/" + StringUtil.replace(packagePath, ".", "/") +
				"/undeploy.wsdd");

		undeployContent = _format(undeployContent);

		// Delete temp directory

		DeleteTask.deleteDirectory(tempDir);

		return new String[] {deployContent, undeployContent};
	}

	private static String _format(String content) throws IOException {
		content = Html.stripComments(content);

		try {
			content = XMLFormatter.toString(content);
		}
		catch (DocumentException de) {
			de.printStackTrace();
		}

		return content;
	}

}