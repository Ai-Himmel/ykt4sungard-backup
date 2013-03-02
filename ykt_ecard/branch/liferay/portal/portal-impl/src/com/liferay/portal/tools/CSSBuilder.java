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
import com.liferay.util.FileUtil;

import java.io.File;

/**
 * <a href="CSSBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CSSBuilder {

	public static void main(String[] args) {
		if (args.length == 2) {
			new CSSBuilder(args[0], args[1]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public CSSBuilder(String cssDir, String mergedFile) {
		try {
			File mainCssFile = new File(cssDir + "/main.css");

			if (!mainCssFile.exists()) {
				System.out.println(
					"Do not pack " + cssDir +
						"/main.css because it does not exist.");

				return;
			}

			String content = FileUtil.read(mainCssFile);

			content = replaceImports(cssDir, content);

			FileUtil.write(mergedFile, content);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public String replaceImports(String cssDir, String s) throws Exception {
		StringMaker sm = new StringMaker(s.length());

		int pos = 0;

		while (true) {
			int x = s.indexOf(_BEGIN, pos);
			int y = s.indexOf(_END, x + _BEGIN.length());

			if ((x == -1) || (y == -1)) {
				sm.append(s.substring(pos, s.length()));

				break;
			}
			else {
				sm.append(s.substring(pos, x));

				String importFile = s.substring(x + _BEGIN.length(), y);

				String importContent = FileUtil.read(cssDir + "/" + importFile);

				importContent = replaceImports(cssDir, importContent);

				sm.append(importContent);

				pos = y + _END.length();
			}
		}

		return sm.toString();
	}

	private static final String _BEGIN = "@import url(";

	private static final String _END = ");";

}