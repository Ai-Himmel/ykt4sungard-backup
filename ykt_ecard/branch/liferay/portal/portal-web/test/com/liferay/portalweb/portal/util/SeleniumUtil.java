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

package com.liferay.portalweb.portal.util;

import com.liferay.portalweb.portal.util.TestPropsValues;

import com.thoughtworks.selenium.DefaultSelenium;
import com.thoughtworks.selenium.Selenium;

/**
 * <a href="SeleniumUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SeleniumUtil {

	public static Selenium getSelenium() {
		return _instance._getSelenium();
	}

	public static void startSelenium() {
		_instance._startSelenium();
	}

	public static void stopSelenium() {
		_instance._stopSelenium();
	}

	private SeleniumUtil() {
	}

	public Selenium _getSelenium() {
		if (_selenium == null) {
			_startSelenium();
		}

		return _selenium;
	}

	public void _startSelenium() {
		String seleniumHost = TestPropsValues.SELENIUM_HOST;
		int seleniumPort = TestPropsValues.SELENIUM_PORT;
		String browserType = TestPropsValues.BROWSER_TYPE;
		String portalURL = TestPropsValues.PORTAL_URL;

		_selenium = new DefaultSelenium(
			seleniumHost, seleniumPort, browserType, portalURL);

		_selenium.start();

		_selenium.setContext(this.getClass().getName());
	}

	private void _stopSelenium() {
		if (_selenium != null) {
			_selenium.stop();
		}

		_selenium = null;
	}

	private static SeleniumUtil _instance = new SeleniumUtil();

	private Selenium _selenium;

}