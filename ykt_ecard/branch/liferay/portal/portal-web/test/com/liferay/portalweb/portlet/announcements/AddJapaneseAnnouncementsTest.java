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

package com.liferay.portalweb.portlet.announcements;

import com.liferay.portalweb.portal.BaseTestCase;

/**
 * <a href="AddJapaneseAnnouncementsTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AddJapaneseAnnouncementsTest extends BaseTestCase {
	public void testAddJapaneseAnnouncements() throws Exception {
		selenium.click("//img[@title='Configuraci\u00f3n']");
		selenium.waitForPageToLoad("30000");

		for (int second = 0;; second++) {
			if (second >= 60) {
				fail("timeout");
			}

			try {
				if (selenium.isElementPresent("_86_languageId")) {
					break;
				}
			}
			catch (Exception e) {
			}

			Thread.sleep(1000);
		}

		Thread.sleep(3000);
		selenium.select("_86_languageId", "label=\u4e2d\u6587 (\u53f0\u7063)");
		selenium.type("_86_content",
			"This is a test announcement in \u65e5\u672c\u8a9e !");

		for (int second = 0;; second++) {
			if (second >= 60) {
				fail("timeout");
			}

			try {
				if (selenium.isElementPresent("//input[@value='Guardar']")) {
					break;
				}
			}
			catch (Exception e) {
			}

			Thread.sleep(1000);
		}

		Thread.sleep(3000);
		selenium.click("//input[@value='Guardar']");
		selenium.waitForPageToLoad("30000");
		selenium.click("link=Mi cuenta");
		selenium.waitForPageToLoad("30000");
		selenium.select("_2_languageId", "label=\u4e2d\u6587 (\u53f0\u7063)");

		for (int second = 0;; second++) {
			if (second >= 60) {
				fail("timeout");
			}

			try {
				if (selenium.isElementPresent("//input[@value='Guardar']")) {
					break;
				}
			}
			catch (Exception e) {
			}

			Thread.sleep(1000);
		}

		Thread.sleep(3000);
		selenium.click("//input[@value='Guardar']");
		selenium.waitForPageToLoad("30000");
		selenium.click("link=Announcements Test Page");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(""));
	}
}