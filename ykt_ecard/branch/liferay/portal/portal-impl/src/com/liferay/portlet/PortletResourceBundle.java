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

package com.liferay.portlet;

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.model.PortletInfo;

import java.util.Enumeration;
import java.util.Locale;
import java.util.MissingResourceException;
import java.util.ResourceBundle;

/**
 * <a href="PortletResourceBundle.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletResourceBundle extends ResourceBundle {

	public PortletResourceBundle(ResourceBundle parentBundle,
								 PortletInfo portletInfo) {

		_parentBundle = parentBundle;
		_portletInfo = portletInfo;
	}

	public Enumeration getKeys() {
		return _parentBundle.getKeys();
	}

	public Locale getLocale() {
		return _parentBundle.getLocale();
	}

	protected Object handleGetObject(String key) {
		try {
			if (_parentBundle == null) {
				return _getJavaxPortletString(key);
			}
			else {
				return _parentBundle.getObject(key);
			}
		}
		catch (MissingResourceException mre) {
			String value = _getJavaxPortletString(key);

			if (value != null) {
				return value;
			}
			else {
				throw mre;
			}
		}
	}

	private String _getJavaxPortletString(String key) {
		if (key == null) {
			return null;
		}
		else if (key.equals(JavaConstants.JAVAX_PORTLET_TITLE)) {
			return _portletInfo.getTitle();
		}
		else if (key.equals(JavaConstants.JAVAX_PORTLET_SHORT_TITLE)) {
			return _portletInfo.getShortTitle();
		}
		else if (key.equals(JavaConstants.JAVAX_PORTLET_KEYWORDS)) {
			return _portletInfo.getKeywords();
		}

		return null;
	}

	private ResourceBundle _parentBundle;
	private PortletInfo _portletInfo;

}