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

import com.liferay.util.ant.Wsdl2JavaTask;

import java.io.File;

import java.util.Iterator;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="PortalClientBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalClientBuilder {

	public static void main(String[] args) {
		if (args.length == 4) {
			new PortalClientBuilder(args[0], args[1], args[2], args[3]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public PortalClientBuilder(
		String fileName, String outputDir, String mappingFile, String url) {

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new File(fileName));

			Element root = doc.getRootElement();

			Iterator itr = root.elements("service").iterator();

			while (itr.hasNext()) {
				Element service = (Element)itr.next();

				String name = service.attributeValue("name");

				if (name.startsWith("Portal_") || name.startsWith("Portlet_")) {
					Wsdl2JavaTask.generateJava(
						url + "/" +  name + "?wsdl", outputDir, mappingFile);
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		File testNamespace = new File(outputDir + "/com/liferay/portal");

		if (testNamespace.exists()) {
			throw new RuntimeException(
				"Please update " + mappingFile + " to namespace " +
					"com.liferay.portal to com.liferay.client.portal");
		}
	}

}