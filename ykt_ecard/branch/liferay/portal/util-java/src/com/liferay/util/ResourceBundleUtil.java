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

package com.liferay.util;

import java.text.MessageFormat;

import java.util.Locale;
import java.util.ResourceBundle;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ResourceBundleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class provides a convenience routine named getString() that
 * gets the value of a ResourceBundle key, but also provides the ability
 * to perform search & replace on tokens within the value of the key.
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class ResourceBundleUtil {

	public static String getString(
		ResourceBundle bundle, Locale locale, String key, Object[] args) {

		String value = null;

		if (bundle == null) {
			if (_log.isErrorEnabled()) {
				_log.error("Resource bundle is null");
			}
		}
		else {

			// Get the value associated with the specified key, and substitute
			// any arguuments like {0}, {1}, {2}, etc. with the specified
			// argument values.

			value = bundle.getString(key);

			if (value == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No value found for key " + key);
				}
			}
			else {
				if ((args != null) && (args.length > 0)) {
					MessageFormat format = new MessageFormat(value, locale);

					value = format.format(args);
				}
			}
		}

		if (value == null) {
			value = key;
		}

		return value;
	}

	private static Log _log = LogFactory.getLog(ResourceBundleUtil.class);

}