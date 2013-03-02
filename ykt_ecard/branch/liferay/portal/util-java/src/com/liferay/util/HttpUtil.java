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

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;

import java.io.UnsupportedEncodingException;

import java.net.URLDecoder;
import java.net.URLEncoder;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="HttpUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class HttpUtil {

	public static final String ENCODING = "UTF-8";

	public static String decodeURL(String url) {
		if (url == null) {
			return null;
		}

		try {
			return URLDecoder.decode(url, ENCODING);
		}
		catch (UnsupportedEncodingException uee) {
			_log.error(uee, uee);

			return StringPool.BLANK;
		}
	}

	public static String encodeURL(String url) {
		if (url == null) {
			return null;
		}

		try {
			return URLEncoder.encode(url, ENCODING);
		}
		catch (UnsupportedEncodingException uee) {
			_log.error(uee, uee);

			return StringPool.BLANK;
		}
	}

	public static String getQueryString(String url) {
		if (Validator.isNull(url)) {
			return url;
		}

		int pos = url.indexOf(StringPool.QUESTION);

		if (pos == -1) {
			return StringPool.BLANK;
		}
		else {
			return url.substring(pos + 1, url.length());
		}
	}

	public static Map parameterMapFromString(String queryString) {
		Map parameterMap = new LinkedHashMap();

		if (Validator.isNull(queryString)) {
			return parameterMap;
		}

		StringTokenizer st = new StringTokenizer(
			queryString, StringPool.AMPERSAND);

		while (st.hasMoreTokens()) {
			String token = st.nextToken();

			if (Validator.isNotNull(token)) {
				String[] kvp = StringUtil.split(token, StringPool.EQUAL);

				String key = kvp[0];

				String value = StringPool.BLANK;

				if (kvp.length > 1) {
					value = kvp[1];
				}

				List values = (List)parameterMap.get(key);

				if (values == null) {
					values = new ArrayList();

					parameterMap.put(key, values);
				}

				values.add(value);
			}
		}

		Iterator itr = parameterMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			List values = (List)entry.getValue();

			parameterMap.put(key, (String[])values.toArray(new String[0]));
		}

		return parameterMap;
	}

	public static String parameterMapToString(Map parameterMap) {
		return parameterMapToString(parameterMap, true);
	}

	public static String parameterMapToString(
		Map parameterMap, boolean addQuestion) {

		StringMaker sm = new StringMaker();

		if (parameterMap.size() > 0) {
			if (addQuestion) {
				sm.append(StringPool.QUESTION);
			}

			Iterator itr = parameterMap.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				String name = (String)entry.getKey();
				Object value = entry.getValue();

				String[] values = null;

				if (value instanceof String[]) {
					values = (String[])entry.getValue();
				}
				else if (value instanceof String) {
				    values = new String[] {(String)value};
				}
				else {
					throw new IllegalArgumentException(
						"Values of type " + value.getClass() + " are not " +
							"supported");
				}

				for (int i = 0; i < values.length; i++) {
					sm.append(name);
					sm.append(StringPool.EQUAL);
					sm.append(encodeURL(values[i]));
					sm.append(StringPool.AMPERSAND);
				}
			}

			sm.deleteCharAt(sm.length() - 1);
		}

		return sm.toString();
	}

	private static Log _log = LogFactory.getLog(HttpUtil.class);

}