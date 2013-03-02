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

import com.liferay.util.Validator;

import java.io.File;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="ThemeDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.38 $
 *
 */
public class ThemeDeployer extends BaseDeployer {

	public static void main(String[] args) {
		if (args.length >= 2) {
			List jars = new ArrayList();

			for (int i = 0; i < args.length; i++) {
				jars.add(args[i]);
			}

			new ThemeDeployer(jars);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	protected ThemeDeployer(List jars) {
		super(jars);
	}

	protected void checkArguments() {
		super.checkArguments();

		if (Validator.isNull(themeTaglibDTD)) {
			throw new IllegalArgumentException(
				"The system property deployer.theme.taglib.dtd is not set");
		}

		if (Validator.isNull(utilTaglibDTD)) {
			throw new IllegalArgumentException(
				"The system property deployer.util.taglib.dtd is not set");
		}
	}

	protected String getExtraContent(File srcFile, String displayName)
		throws Exception {

		String extraContent = super.getExtraContent(srcFile, displayName);

		extraContent +=
			"<listener>" +
			"<listener-class>" +
			"com.liferay.portal.servlet.ThemeContextListener" +
			"</listener-class>" +
			"</listener>";

		return extraContent;
	}

}