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

import com.liferay.portal.kernel.util.CharPool;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.UnicodeFormatter;
import com.liferay.portal.tools.servicebuilder.ServiceBuilder;
import com.liferay.portal.util.InitUtil;
import com.liferay.util.FileUtil;

import java.io.File;

import org.apache.tools.ant.DirectoryScanner;

/**
 * <a href="SeleneseToJavaBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SeleneseToJavaBuilder {

	static {
		InitUtil.init();
	}

	public static void main(String[] args) throws Exception {
		if (args.length == 1) {
			new SeleneseToJavaBuilder(args[0]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public SeleneseToJavaBuilder(String basedir) throws Exception {
		DirectoryScanner ds = new DirectoryScanner();

		ds.setBasedir(basedir);
		ds.setIncludes(new String[] {"**\\*.html"});

		ds.scan();

		String[] files = ds.getIncludedFiles();

		for (int i = 0; i < files.length; i++) {

			// I would have preferred to use XlateHtmlSeleneseToJava, but it
			// is horribly out of sync with Selenium IDE and generates incorrect
			// code.

			/*File file = new File(basedir + "/" + files[i]);

			String input = StringUtil.replace(file.toString(), "\\", "/");

			XlateHtmlSeleneseToJava.main(
				new String[] {
					"test", "-silent", input
				}
			);*/

			translate(basedir, files[i]);
		}
	}

	protected String fixParam(String param) {
		StringMaker sm = new StringMaker();

		char[] array = param.toCharArray();

		for (int i = 0; i < array.length; ++i) {
			char c = array[i];

			if (c == CharPool.BACK_SLASH) {
				sm.append("\\\\");
			}
			else if (c == CharPool.QUOTE) {
				sm.append("\\\"");
			}
			else if (Character.isWhitespace(c)) {
				sm.append(c);
			}
			else if ((c < 0x0020) || (c > 0x007e)) {
				sm.append("\\u");
				sm.append(UnicodeFormatter.charToHex(c));
			}
			else {
				sm.append(c);
			}
		}

		return StringUtil.replace(
			sm.toString(), _FIX_PARAM_OLDSUB, _FIX_PARAM_NEWSUB);
	}

	protected String[] getParams(String step) throws Exception {
		String[] params = new String[3];

		int x = 0;
		int y = 0;

		for (int i = 0; i < 3; i++) {
			x = step.indexOf("<td>", x) + 4;
			y = step.indexOf("\n", x);
			y = step.lastIndexOf("</td>", y);

			params[i] =	step.substring(x, y);
		}

		return params;
	}

	protected void translate(String basedir, String file) throws Exception {
		file = StringUtil.replace(
			file, StringPool.BACK_SLASH, StringPool.SLASH);

		int x = file.lastIndexOf(StringPool.SLASH);
		int y = file.indexOf(StringPool.PERIOD);

		String testPackagePath = StringUtil.replace(
			file.substring(0, x), StringPool.SLASH, StringPool.PERIOD);
		String testName = file.substring(x + 1, y);
		String testMethodName =
			"test" + testName.substring(0, testName.length() - 4);
		String testFileName = basedir + "/" + file.substring(0, y) + ".java";

		StringMaker sm = new StringMaker();

		sm.append("package " + testPackagePath + ";\n\n");

		sm.append("import com.liferay.portal.kernel.util.StringPool;\n");
		sm.append("import com.liferay.portalweb.portal.BaseTestCase;\n\n");

		sm.append("public class " + testName + " extends BaseTestCase {");

		sm.append("public void " + testMethodName + "() throws Exception {");

		String xml = FileUtil.read(
			new File(basedir + "/" + file), StringPool.UTF8, false);

		if ((xml.indexOf("<title>" + testName + "</title>") == -1) ||
			(xml.indexOf("colspan=\"3\">" + testName + "</td>") == -1)) {

			System.out.println(testName + " has an invalid test name");
		}

		x = xml.indexOf("<tbody>");
		y = xml.indexOf("</tbody>");

		xml = xml.substring(x, y + 8);

		x = 0;
		y = 0;

		while (true) {
			x = xml.indexOf("<tr>", x);
			y = xml.indexOf("\n</tr>", x);

			if ((x == -1) || (y == -1)) {
				break;
			}

			x += 6;
			y++;

			String step = xml.substring(x, y);

			String[] params = getParams(step);

			String param1 = params[0];
			String param2 = fixParam(params[1]);
			String param3 = fixParam(params[2]);

			if (param1.equals("assertConfirmation")) {
				param2 = StringUtil.replace(param2, "?", "[\\\\s\\\\S]");

				sm.append("assertTrue(selenium.getConfirmation().matches(\"^");
				sm.append(param2);
				sm.append("$\"));");
			}
			else if (param1.equals("click") || param1.equals("mouseDown") ||
					 param1.equals("mouseUp") || param1.equals("open") ||
					 param1.equals("selectFrame") ||
					 param1.equals("selectWindow")) {

				sm.append("selenium.");
				sm.append(param1);
				sm.append("(\"");
				sm.append(param2);
				sm.append("\");");
			}
			else if (param1.equals("clickAndWait")) {
				sm.append("selenium.click(\"");
				sm.append(param2);
				sm.append("\");");
				sm.append("selenium.waitForPageToLoad(\"30000\");");
			}
			else if (param1.equals("close")) {
				sm.append("selenium.");
				sm.append(param1);
				sm.append("();");
			}
			else if (param1.equals("pause")) {
				sm.append("Thread.sleep(");
				sm.append(param2);
				sm.append(");");
			}
			else if (param1.equals("select") || param1.equals("type") ||
					 param1.equals("typeKeys") ||
					 param1.equals("waitForPopUp")) {

				sm.append("selenium.");
				sm.append(param1);
				sm.append("(\"");
				sm.append(param2);
				sm.append("\", \"");
				sm.append(param3);
				sm.append("\");");
			}
			else if (param1.equals("selectAndWait")) {
				sm.append("selenium.select(\"");
				sm.append(param1);
				sm.append("\", \"");
				sm.append(param2);
				sm.append("\");");
				sm.append("selenium.waitForPageToLoad(\"30000\");");
			}
			else if (param1.equals("verifyTextPresent") ||
					 param1.equals("verifyTextNotPresent")) {

				if (param1.equals("verifyTextPresent")) {
					sm.append("verifyTrue");
				}
				else if (param1.equals("verifyTextNotPresent")) {
					sm.append("verifyFalse");
				}

				sm.append("(selenium.isTextPresent(\"");
				sm.append(param2);
				sm.append("\"));");
			}
			else if (param1.equals("verifyTitle")) {
				sm.append("verifyEquals(\"");
				sm.append(param2);
				sm.append("\", selenium.getTitle());");
			}
			else if (param1.equals("waitForElementPresent") ||
					 param1.equals("waitForTextPresent")) {

				sm.append("for (int second = 0;; second++) {");
				sm.append("if (second >= 60) {");
				sm.append("fail(\"timeout\");");
				sm.append("}");

				sm.append("try {");
				sm.append("if (selenium.");

				if (param1.equals("waitForElementPresent")) {
					sm.append("isElementPresent");
				}
				else if (param1.equals("waitForTextPresent")) {
					sm.append("isTextPresent");
				}

				sm.append("(\"");
				sm.append(param2);
				sm.append("\")) {");
				sm.append("break;");
				sm.append("}");
				sm.append("}");
				sm.append("catch (Exception e) {");
				sm.append("}");

				sm.append("Thread.sleep(1000);");
				sm.append("}");
			}
			else if (param1.equals("waitForTable")) {
				sm.append("for (int second = 0;; second++) {");
				sm.append("if (second >= 60) {");
				sm.append("fail(\"timeout\");");
				sm.append("}");

				sm.append("try {");
				sm.append("if (StringPool.BLANK.equals(selenium.getTable(\"");
				sm.append(param2);
				sm.append("\"))) {");
				sm.append("break;");
				sm.append("}");
				sm.append("}");
				sm.append("catch (Exception e) {");
				sm.append("}");

				sm.append("Thread.sleep(1000);");
				sm.append("}");
			}
			else {
				System.out.println(param1 + " was not translated");
			}
		}

		sm.append("}");
		sm.append("}");

		String content = sm.toString();

		ServiceBuilder.writeFile(new File(testFileName), content);
	}

	private static final String [] _FIX_PARAM_OLDSUB = new String[] {"\\\\n", "<br />"};
	private static final String [] _FIX_PARAM_NEWSUB = new String[] {"\\n", "\\n"};

}