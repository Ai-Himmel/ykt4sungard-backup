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

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.tools.servicebuilder.ServiceBuilder;
import com.liferay.portal.util.InitUtil;

import com.thoughtworks.qdox.JavaDocBuilder;
import com.thoughtworks.qdox.model.JavaClass;
import com.thoughtworks.qdox.model.JavaMethod;
import com.thoughtworks.qdox.model.JavaParameter;
import com.thoughtworks.qdox.model.Type;

import java.io.File;
import java.io.IOException;

import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Set;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="InstanceWrapperBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InstanceWrapperBuilder {

	static {
		InitUtil.init();
	}

	public static void main(String[] args) {
		if (args.length == 1) {
			new InstanceWrapperBuilder(args[0]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public InstanceWrapperBuilder(String xml) {
		try {
			File file = new File(xml);

			SAXReader reader = new SAXReader();

			Document doc = null;

			try {
				doc = reader.read(file);
			}
			catch (DocumentException de) {
				de.printStackTrace();
			}

			Element root = doc.getRootElement();

			Iterator itr = root.elements("instance-wrapper").iterator();

			while (itr.hasNext()) {
				Element instanceWrapper = (Element)itr.next();

				String parentDir = instanceWrapper.attributeValue("parent-dir");
				String srcFile = instanceWrapper.attributeValue("src-file");

				_createIW(parentDir, srcFile);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void _createIW(String parentDir, String srcFile)
		throws IOException {

		JavaClass javaClass = _getJavaClass(parentDir, srcFile);

		JavaMethod[] methods = javaClass.getMethods();

		StringMaker sm = new StringMaker();

		// Package

		sm.append("package " + javaClass.getPackage() + ";");

		// Class declaration

		sm.append("public class " + javaClass.getName() + "_IW {");

		// Methods

		sm.append("public static " + javaClass.getName() + "_IW getInstance() {");
		sm.append("return _instance;");
		sm.append("}");

		for (int i = 0; i < methods.length; i++) {
			JavaMethod javaMethod = methods[i];

			String methodName = javaMethod.getName();

			if (javaMethod.isPublic() && javaMethod.isStatic()) {
				if (methodName.equals("getInstance")) {
					methodName = "getWrappedInstance";
				}

				sm.append("public " + javaMethod.getReturns().getValue() + _getDimensions(javaMethod.getReturns()) + " " + methodName + "(");

				JavaParameter[] parameters = javaMethod.getParameters();

				for (int j = 0; j < parameters.length; j++) {
					JavaParameter javaParameter = parameters[j];

					sm.append(javaParameter.getType().getValue() + _getDimensions(javaParameter.getType()) + " " + javaParameter.getName());

					if ((j + 1) != parameters.length) {
						sm.append(", ");
					}
				}

				sm.append(")");

				Type[] thrownExceptions = javaMethod.getExceptions();

				Set newExceptions = new LinkedHashSet();

				for (int j = 0; j < thrownExceptions.length; j++) {
					Type thrownException = thrownExceptions[j];

					newExceptions.add(thrownException.getValue());
				}

				if (newExceptions.size() > 0) {
					sm.append(" throws ");

					Iterator itr = newExceptions.iterator();

					while (itr.hasNext()) {
						sm.append(itr.next());

						if (itr.hasNext()) {
							sm.append(", ");
						}
					}
				}

				sm.append("{");

				if (!javaMethod.getReturns().getValue().equals("void")) {
					sm.append("return ");
				}

				sm.append(javaClass.getName() + "." + javaMethod.getName() + "(");

				for (int j = 0; j < parameters.length; j++) {
					JavaParameter javaParameter = parameters[j];

					sm.append(javaParameter.getName());

					if ((j + 1) != parameters.length) {
						sm.append(", ");
					}
				}

				sm.append(");");
				sm.append("}");
			}
		}

		// Private constructor

		sm.append("private " + javaClass.getName() + "_IW() {");
		sm.append("}");

		// Fields

		sm.append("private static " + javaClass.getName() + "_IW _instance = new " + javaClass.getName() + "_IW();");

		// Class close brace

		sm.append("}");

		// Write file

		File file = new File(parentDir + "/" + StringUtil.replace(javaClass.getPackage(), ".", "/") + "/" + javaClass.getName() + "_IW.java");

		ServiceBuilder.writeFile(file, sm.toString());
	}

	private String _getDimensions(Type type) {
		String dimensions = "";

		for (int i = 0; i < type.getDimensions(); i++) {
			dimensions += "[]";
		}

		return dimensions;
	}

	private JavaClass _getJavaClass(String parentDir, String srcFile)
		throws IOException {

		String className = StringUtil.replace(
			srcFile.substring(0, srcFile.length() - 5), "/", ".");

		JavaDocBuilder builder = new JavaDocBuilder();

		builder.addSource(new File(parentDir + "/" + srcFile));

		return builder.getClassByName(className);
	}

}