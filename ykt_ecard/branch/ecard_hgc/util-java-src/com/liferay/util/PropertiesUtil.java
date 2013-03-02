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

package com.liferay.util;

import com.liferay.util.lang.FastStringBuffer;

import java.io.ByteArrayInputStream;
import java.io.IOException;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.Map;
import java.util.Properties;

/**
 * <a href="PropertiesUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class PropertiesUtil {

	public static void copyProperties(Properties from, Properties to) {
		Iterator itr = from.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			to.setProperty((String)entry.getKey(), (String)entry.getValue());
		}
	}

	public static Properties fromMap(Map map) {
		Properties p = new Properties();

		Iterator itr = map.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			p.setProperty((String)entry.getKey(), (String)entry.getValue());
		}

		return p;
	}

	public static void fromProperties(Properties p, Map map) {
		map.clear();

		Iterator itr = p.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			map.put(entry.getKey(), entry.getValue());
		}
	}

	public static Properties load(String s) throws IOException {
		Properties p = new Properties();

		load(p, s);

		return p;
	}

	public static void load(Properties p, String s) throws IOException {
		if (Validator.isNotNull(s)) {
			/*
			s = UnicodeFormatter.toString(s);
			s = StringUtil.replace(s, "\\u003d", "=");
			s = StringUtil.replace(s, "\\u000a", "\n");
			*/			
			p.load(new ByteArrayInputStream(s.getBytes()));
		}
	}

	public static void merge(Properties p1, Properties p2) {
		Enumeration enu = p2.propertyNames();

		while (enu.hasMoreElements()) {
			String key = (String)enu.nextElement();
			String value = p1.getProperty(key);

			p1.setProperty(key, value);
		}
	}

	public static String toString(Properties p) {
		FastStringBuffer sb = new FastStringBuffer();

		Enumeration enu = p.propertyNames();

		while (enu.hasMoreElements()) {
			String key = (String)enu.nextElement();

			sb.append(key);
			sb.append(StringPool.EQUAL);
			sb.append(p.getProperty(key));
			sb.append("\n");
		}

		return sb.toString();
	}

	public static void trimKeys(Properties p) {
		Enumeration enu = p.propertyNames();

		while (enu.hasMoreElements()) {
			String key = (String)enu.nextElement();
			String value = p.getProperty(key);

			String trimmedKey = key.trim();

			if (!key.equals(trimmedKey)) {
				p.remove(key);
				p.setProperty(trimmedKey, value);
			}
		}
	}

}