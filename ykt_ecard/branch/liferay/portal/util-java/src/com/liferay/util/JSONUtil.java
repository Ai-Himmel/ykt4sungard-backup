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

import com.liferay.portal.kernel.util.StringPool;

import java.util.Date;

import org.json.JSONObject;

/**
 * <a href="JSONUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JSONUtil {

	public static void put(JSONObject jsonObj, String key, boolean value) {
		jsonObj.put(key, value);
	}

	public static void put(JSONObject jsonObj, String key, double value) {
		jsonObj.put(key, value);
	}

	public static void put(JSONObject jsonObj, String key, int value) {
		jsonObj.put(key, value);
	}

	public static void put(JSONObject jsonObj, String key, long value) {
		jsonObj.put(key, value);
	}

	public static void put(JSONObject jsonObj, String key, short value) {
		jsonObj.put(key, value);
	}

	public static void put(JSONObject jsonObj, String key, Date value) {
		if (value == null) {
			jsonObj.put(key, StringPool.BLANK);
		}
		else {

			// Unix timestamp

			long time = value.getTime() / Time.SECOND;

			put(jsonObj, key, String.valueOf(time));
		}
	}

	public static void put(JSONObject jsonObj, String key, Object value) {
		if (value == null) {
			jsonObj.put(key, StringPool.BLANK);
		}
		else {
			jsonObj.put(key, value.toString());
		}
	}

}