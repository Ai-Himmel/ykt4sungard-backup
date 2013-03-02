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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * <a href="MapUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class MapUtil {

	public static void copy(Map master, Map copy) {
		copy.clear();

		merge(master, copy);
	}

	public static boolean getBoolean(Map map, String key) {
		return getBoolean(map, key, GetterUtil.DEFAULT_BOOLEAN);
	}

	public static boolean getBoolean(
		Map map, String key, boolean defaultValue) {

		return GetterUtil.getBoolean(
			getString(map, key, String.valueOf(defaultValue)), defaultValue);
	}

	public static long getLong(Map map, long key) {
		return getLong(map, key, GetterUtil.DEFAULT_LONG);
	}

	public static long getLong(Map map, long key, long defaultValue) {
		Long keyObj = new Long(key);

		if (map.containsKey(keyObj)) {
			Object value = map.get(keyObj);

			if (value instanceof Long) {
				return ((Long)value).longValue();
			}
		}

		return defaultValue;
	}

	public static String getString(Map map, String key) {
		return getString(map, key, GetterUtil.DEFAULT_STRING);
	}

	public static String getString(Map map, String key, String defaultValue) {
		if (map.containsKey(key)) {
			Object value = map.get(key);

			if (value instanceof String[]) {
				String[] array = (String[])value;

				if (array.length > 0) {
					return GetterUtil.getString(array[0], defaultValue);
				}
			}
			else if (value instanceof String) {
				return GetterUtil.getString((String)value, defaultValue);
			}
			else {
				return defaultValue;
			}
		}

		return defaultValue;
	}

	public static void merge(Map master, Map copy) {
		Iterator itr = master.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			Object key = entry.getKey();
			Object value = entry.getValue();

			copy.put(key, value);
		}
	}

	public static LinkedHashMap toLinkedHashMap(String[] params) {
		LinkedHashMap map = new LinkedHashMap();

		for (int i = 0; i < params.length; i++) {
			String[] kvp = StringUtil.split(params[i], StringPool.COLON);

			map.put(kvp[0], kvp[1]);
		}

		return map;
	}

}