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

import com.liferay.portal.kernel.util.ClassUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.ListUtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;

import org.apache.tools.ant.DirectoryScanner;

/**
 * <a href="SourceFormatter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SourceFormatter {

	public static void main(String[] args) {
		try {
			_formatJava();
			_formatJSP();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static String stripImports(
			String content, String packageDir, String className)
		throws IOException {

		int x = content.indexOf("import ");

		if (x == -1) {
			return content;
		}

		int y = content.indexOf("{", x);

		y = content.substring(0, y).lastIndexOf(";") + 1;

		String imports = _formatImports(content.substring(x, y));

		content =
			content.substring(0, x) + imports +
				content.substring(y + 1, content.length());

		Set classes = ClassUtil.getClasses(
			new StringReader(content), className);

		classes.add("_getMarkup");
		classes.add("_performBlockingInteraction");

		x = content.indexOf("import ");

		y = content.indexOf("{", x);

		y = content.substring(0, y).lastIndexOf(";") + 1;

		imports = content.substring(x, y);

		StringMaker sm = new StringMaker();

		BufferedReader br = new BufferedReader(new StringReader(imports));

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.indexOf("import ") != -1) {
				int importX = line.indexOf(" ");
				int importY = line.lastIndexOf(".");

				String importPackage = line.substring(importX + 1, importY);
				String importClass = line.substring(
					importY + 1, line.length() - 1);

				if (!packageDir.equals(importPackage)) {
					if (!importClass.equals("*")) {
						if (classes.contains(importClass)) {
							sm.append(line);
							sm.append("\n");
						}
					}
					else {
						sm.append(line);
						sm.append("\n");
					}
				}
			}
		}

		imports = _formatImports(sm.toString());

		content =
			content.substring(0, x) + imports +
				content.substring(y + 1, content.length());

		return content;
	}

	public static String _formatImports(String imports) throws IOException {
		if ((imports.indexOf("/*") != -1) ||
			(imports.indexOf("*/") != -1) ||
			(imports.indexOf("//") != -1)) {

			return imports + "\n";
		}

		List importsList = new ArrayList();

		BufferedReader br = new BufferedReader(new StringReader(imports));

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.indexOf("import ") != -1) {
				if (!importsList.contains(line)) {
					importsList.add(line);
				}
			}
		}

		Collections.sort(importsList);

		StringMaker sm = new StringMaker();

		String temp = null;

		for (int i = 0; i < importsList.size(); i++) {
			String s = (String)importsList.get(i);

			int pos = s.indexOf(".");

			pos = s.indexOf(".", pos + 1);

			if (pos == -1) {
				pos = s.indexOf(".");
			}

			String packageLevel = s.substring(7, pos);

			if ((i != 0) && (!packageLevel.equals(temp))) {
				sm.append("\n");
			}

			temp = packageLevel;

			sm.append(s);
			sm.append("\n");
		}

		return sm.toString();
	}

	private static void _formatJava() throws IOException {
		String basedir = "../";

		List list = new ArrayList();

		DirectoryScanner ds = new DirectoryScanner();

		ds.setBasedir(basedir);
		ds.setExcludes(
			new String[] {
				"**\\classes\\*", "**\\jsp\\*", "**\\tmp\\**",
				"**\\EARXMLBuilder.java", "**\\EJBXMLBuilder.java",
				"**\\JSMin.java", "**\\PropsUtil.java",
				"**\\InstanceWrapperBuilder.java",
				"**\\ServiceBuilder.java", "**\\SourceFormatter.java",
				"**\\UserAttributes.java", "**\\WebKeys.java",
				"**\\*_IW.java", "**\\XHTMLComplianceFormatter.java",
				"**\\portal-service\\**\\model\\*Model.java",
				"**\\portal-service\\**\\model\\*Soap.java",
				"**\\model\\impl\\*ModelImpl.java",
				"**\\portal\\service\\**", "**\\portal-client\\**",
				"**\\portal-web\\test\\**\\*Test.java",
				"**\\portlet\\**\\service\\**", "**\\tools\\ext_tmpl\\**",
				"**\\util-wsrp\\**"
			});
		ds.setIncludes(new String[] {"**\\*.java"});

		ds.scan();

		list.addAll(ListUtil.fromArray(ds.getIncludedFiles()));

		ds = new DirectoryScanner();

		ds.setBasedir(basedir);
		ds.setExcludes(
			new String[] {
				"**\\tools\\ext_tmpl\\**", "**\\*_IW.java",
				"**\\test\\**\\*PersistenceTest.java"
			});
		ds.setIncludes(
			new String[] {
				"**\\service\\http\\*HttpTest.java",
				"**\\service\\http\\*SoapTest.java",
				"**\\service\\impl\\*.java", "**\\service\\jms\\*.java",
				"**\\service\\permission\\*.java",
				"**\\service\\persistence\\BasePersistence.java",
				"**\\service\\persistence\\*FinderImpl.java",
				"**\\portal-impl\\test\\**\\*.java",
				"**\\portal-service\\**\\liferay\\counter\\**.java",
				"**\\portal-service\\**\\liferay\\documentlibrary\\**.java",
				"**\\portal-service\\**\\liferay\\lock\\**.java",
				"**\\portal-service\\**\\liferay\\mail\\**.java",
				"**\\util-bridges\\**\\*.java"
			});

		ds.scan();

		list.addAll(ListUtil.fromArray(ds.getIncludedFiles()));

		String copyright = FileUtil.read("../copyright.txt");

		String[] files = (String[])list.toArray(new String[list.size()]);

		for (int i = 0; i < files.length; i++) {
			File file = new File(basedir + files[i]);

			String content = FileUtil.read(file);

			String className = file.getName();

			className = className.substring(0, className.length() - 5);

			String packagePath = files[i];

			int packagePathX = packagePath.indexOf(
				File.separator + "src" + File.separator);
			int packagePathY = packagePath.lastIndexOf(File.separator);

			packagePath = packagePath.substring(packagePathX + 5, packagePathY);
			packagePath = StringUtil.replace(
				packagePath, File.separator, StringPool.PERIOD);

			if (packagePath.endsWith(".model")) {
				if (content.indexOf(
						"extends " + className + "Model {") != -1) {

					continue;
				}
			}

			String newContent = _formatJavaContent(files[i], content);

			if (newContent.indexOf("$\n */") != -1) {
				System.out.println("*: " + files[i]);

				newContent = StringUtil.replace(
					newContent, "$\n */", "$\n *\n */");
			}

			if (newContent.indexOf(copyright) == -1) {
				System.out.println("(c): " + files[i]);
			}

			if (newContent.indexOf(className + ".java.html") == -1) {
				System.out.println("Java2HTML: " + files[i]);
			}

			newContent = stripImports(newContent, packagePath, className);

			if (newContent.indexOf(";\n/**") != -1) {
				newContent = StringUtil.replace(
					newContent,
					";\n/**",
					";\n\n/**");
			}

			if (newContent.indexOf("\t/*\n\t *") != -1) {
				newContent = StringUtil.replace(
					newContent,
					"\t/*\n\t *",
					"\t/**\n\t *");
			}

			if (newContent.indexOf("if(") != -1) {
				newContent = StringUtil.replace(
					newContent,
					"if(",
					"if (");
			}

			if (newContent.indexOf("while(") != -1) {
				newContent = StringUtil.replace(
					newContent,
					"while(",
					"while (");
			}

			if (newContent.indexOf("\n\n\n") != -1) {
				newContent = StringUtil.replace(
					newContent,
					"\n\n\n",
					"\n\n");
			}

			if  (newContent.indexOf("*/\npackage ") != -1) {
				System.out.println("package: " + files[i]);
			}

			if (!newContent.endsWith("\n\n}") &&
				!newContent.endsWith("{\n}")) {

				System.out.println("}: " + files[i]);
			}

			if ((newContent != null) && !content.equals(newContent)) {
				FileUtil.write(file, newContent);

				System.out.println(file.toString());
			}
		}
	}

	private static String _formatJavaContent(String fileName, String content)
		throws IOException {

		StringMaker sm = new StringMaker();

		BufferedReader br = new BufferedReader(new StringReader(content));

		int lineCount = 0;

		String line = null;

		while ((line = br.readLine()) != null) {
			lineCount++;

			if (line.trim().length() == 0) {
				line = StringPool.BLANK;
			}

			line = StringUtil.trimTrailing(line);

			sm.append(line);
			sm.append("\n");

			line = StringUtil.replace(line, "\t", "    ");

			if (((line.length() - 1) > 79) && !line.startsWith("import ")) {
				System.out.println("> 80: " + fileName + " " + lineCount);
			}
		}

		br.close();

		String newContent = sm.toString();

		if (newContent.endsWith("\n")) {
			newContent = newContent.substring(0, newContent.length() -1);
		}

		return newContent;
	}

	private static void _formatJSP() throws IOException {
		String basedir = "../";

		List list = new ArrayList();

		DirectoryScanner ds = new DirectoryScanner();

		ds.setBasedir(basedir);
		ds.setExcludes(new String[] {"**\\null.jsp", "**\\tmp\\**"});
		ds.setIncludes(new String[] {"**\\*.jsp", "**\\*.jspf", "**\\*.vm"});

		ds.scan();

		list.addAll(ListUtil.fromArray(ds.getIncludedFiles()));

		String copyright = FileUtil.read("../copyright.txt");

		String[] files = (String[])list.toArray(new String[list.size()]);

		for (int i = 0; i < files.length; i++) {
			File file = new File(basedir + files[i]);

			String content = FileUtil.read(file, true);
			String newContent = _formatJSPContent(files[i], content);

			if (files[i].endsWith(".jsp")) {
				if (newContent.indexOf(copyright) == -1) {
					System.out.println("(c): " + files[i]);
				}
			}

			if (newContent.indexOf("alert('<%= LanguageUtil.") != -1) {
				newContent = StringUtil.replace(newContent,
					"alert('<%= LanguageUtil.",
					"alert('<%= UnicodeLanguageUtil.");
			}

			if (newContent.indexOf("alert(\"<%= LanguageUtil.") != -1) {
				newContent = StringUtil.replace(newContent,
					"alert(\"<%= LanguageUtil.",
					"alert(\"<%= UnicodeLanguageUtil.");
			}

			if (newContent.indexOf("confirm('<%= LanguageUtil.") != -1) {
				newContent = StringUtil.replace(newContent,
					"confirm('<%= LanguageUtil.",
					"confirm('<%= UnicodeLanguageUtil.");
			}

			if (newContent.indexOf("confirm(\"<%= LanguageUtil.") != -1) {
				newContent = StringUtil.replace(newContent,
					"confirm(\"<%= LanguageUtil.",
					"confirm(\"<%= UnicodeLanguageUtil.");
			}

			if ((newContent != null) && !content.equals(newContent)) {
				FileUtil.write(file, newContent);

				System.out.println(file.toString());
			}
		}
	}

	private static String _formatJSPContent(String fileName, String content)
		throws IOException {

		StringMaker sm = new StringMaker();

		BufferedReader br =
			new BufferedReader(new StringReader(content));

		int lineCount = 0;

		String line = null;

		while ((line = br.readLine()) != null) {
			lineCount++;

			int x = line.indexOf("\"<%=");
			int y = line.indexOf("%>\"", x);

			boolean hasTagLibrary = false;

			for (int i = 0; i < _TAG_LIBRARIES.length; i++) {
				if (line.indexOf("<" + _TAG_LIBRARIES[i] + ":") != -1) {
					hasTagLibrary = true;

					break;
				}
			}

			if ((x != -1) && (y != -1) && hasTagLibrary) {
				String regexp = line.substring(x, y + 3);

				if (regexp.indexOf("\\\"") == -1) {
					regexp = regexp.substring(1, regexp.length() - 1);

					if (regexp.indexOf("\"") != -1) {
						line =
							line.substring(0, x) + "'" + regexp + "'" +
								line.substring(y + 3, line.length());
					}
				}
			}

			if (line.trim().length() == 0) {
				line = StringPool.BLANK;
			}

			line = StringUtil.trimTrailing(line);

			sm.append(line);
			sm.append("\n");
		}

		br.close();

		String newContent = sm.toString();

		if (newContent.endsWith("\n")) {
			newContent = newContent.substring(0, newContent.length() -1);
		}

		return newContent;
	}

	private static final String[] _TAG_LIBRARIES = new String[] {
		"c", "html", "jsp", "liferay-portlet", "liferay-security",
		"liferay-theme", "liferay-ui", "liferay-util", "portlet", "struts",
		"tiles"
	};

}