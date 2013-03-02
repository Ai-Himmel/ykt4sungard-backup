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

import java.io.File;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="LayoutTemplateDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutTemplateDeployer extends BaseDeployer {

	public static void main(String[] args) {
		List wars = new ArrayList();
		List jars = new ArrayList();

		for (int i = 0; i < args.length; i++) {
			if (args[i].endsWith(".war")) {
				wars.add(args[i]);
			}
			else if (args[i].endsWith(".jar")) {
				jars.add(args[i]);
			}
		}

		new LayoutTemplateDeployer(wars, jars);
	}

	protected LayoutTemplateDeployer() {
	}

	protected LayoutTemplateDeployer(List wars, List jars) {
		super(wars, jars);
	}

	protected String getExtraContent(
			double webXmlVersion, File srcFile, String displayName)
		throws Exception {

		StringMaker sm = new StringMaker();

		String extraContent = super.getExtraContent(
			webXmlVersion, srcFile, displayName);

		sm.append(extraContent);

		sm.append("<listener>");
		sm.append("<listener-class>");
		sm.append("com.liferay.portal.kernel.servlet.");
		sm.append("LayoutTemplateContextListener");
		sm.append("</listener-class>");
		sm.append("</listener>");

		return sm.toString();
	}

}