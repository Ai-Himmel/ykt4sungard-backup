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

package com.liferay.util.ant;

import java.io.File;
import java.io.IOException;

import org.apache.axis.tools.ant.wsdl.NamespaceMapping;
import org.apache.axis.tools.ant.wsdl.Wsdl2javaAntTask;

/**
 * <a href="Wsdl2JavaTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Wsdl2JavaTask {

	public static void generateJava(String url, String output)
		throws IOException {

		generateJava(url, output, null);
	}

	public static void generateJava(String url, String output, String mapping)
		throws IOException {

		Wsdl2javaAntTask wsdl2Java = new Wsdl2javaAntTask();

		wsdl2Java.setProject(AntUtil.getProject());
		wsdl2Java.setURL(url);
		wsdl2Java.setOutput(new File(output));
		wsdl2Java.setServerSide(true);
		wsdl2Java.setTestCase(false);
		wsdl2Java.setVerbose(false);

		if (mapping != null) {
			NamespaceMapping namespaceMapping = new NamespaceMapping();

			namespaceMapping.setFile(new File(mapping));

			wsdl2Java.addMapping(namespaceMapping);
		}

		wsdl2Java.execute();
	}

}