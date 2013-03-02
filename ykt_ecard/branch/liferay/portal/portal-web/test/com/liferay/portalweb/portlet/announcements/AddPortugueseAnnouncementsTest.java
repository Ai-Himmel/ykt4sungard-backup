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
 * <a href="AddPortugueseAnnouncementsTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AddPortugueseAnnouncementsTest extends BaseTestCase {
	public void testAddPortugueseAnnouncements() throws Exception {
		selenium.click("//img[@title='\u69cb\u6210']");
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
		selenium.select("_86_languageId", "label=portugu\u00eas (Brasil)");
		selenium.type("_86_content",
			"This is a test announcement in Portugu\u011bse!");

		for (int second = 0;; second++) {
			if (second >= 60) {
				fail("timeout");
			}

			try {
				if (selenium.isElementPresent(
							"//input[@value='\u3092\u9664\u3051\u3070']")) {
					break;
				}
			}
			catch (Exception e) {
			}

			Thread.sleep(1000);
		}

		Thread.sleep(3000);
		selenium.click("//input[@value='\u3092\u9664\u3051\u3070']");
		selenium.waitForPageToLoad("30000");
		selenium.click("link=\u79c1\u306e\u8a18\u8ff0");
		selenium.waitForPageToLoad("30000");
		Thread.sleep(3000);
		selenium.select("_2_languageId", "label=portugu\u00eas (Brasil)");

		for (int second = 0;; second++) {
			if (second >= 60) {
				fail("timeout");
			}

			try {
				if (selenium.isElementPresent(
							"//input[@value='\u3092\u9664\u3051\u3070']")) {
					break;
				}
			}
			catch (Exception e) {
			}

			Thread.sleep(1000);
		}

		selenium.click("//input[@value='\u3092\u9664\u3051\u3070']");
		selenium.waitForPageToLoad("30000");
		selenium.click("link=Announcements Test Page");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(""));
		selenium.click("link=Meu Cliente");
		selenium.waitForPageToLoad("30000");
		Thread.sleep(3000);
		selenium.select("_2_languageId", "label=English (United States)");
		selenium.click("//input[@value='Excepto']");
		selenium.waitForPageToLoad("30000");
		selenium.click("link=Announcements Test Page");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(""));
	}
}