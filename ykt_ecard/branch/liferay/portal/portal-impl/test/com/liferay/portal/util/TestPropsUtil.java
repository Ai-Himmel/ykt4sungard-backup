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

package com.liferay.portal.util;

import java.io.InputStream;

import java.util.Collections;
import java.util.List;
import java.util.Properties;

/**
 * <a href="TestPropsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TestPropsUtil {

	public static String get(String key) {
		return _instance._get(key);
	}

	public static Properties getProperties() {
		return _instance._props;
	}

	private TestPropsUtil() {
		try {
			ClassLoader classLoader = ClassLoader.getSystemClassLoader();

			InputStream is = classLoader.getResourceAsStream(
				"test-portal-impl.properties");

			_props.load(is);

			is = classLoader.getResourceAsStream(
				"test-portal-impl-ext.properties");

			if (is != null) {
				_props.load(is);
			}

			List keys = Collections.list(_props.propertyNames());

			Collections.sort(keys);

			System.out.println("-- listing properties --");

			for (int i = 0; i < keys.size(); i++) {
				String key = (String)keys.get(i);

				System.out.println(key + "=" + _props.getProperty(key));
			}

			System.out.println("");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private String _get(String key) {
		return _props.getProperty(key);
	}

	private static TestPropsUtil _instance = new TestPropsUtil();

	private Properties _props = new Properties();

}