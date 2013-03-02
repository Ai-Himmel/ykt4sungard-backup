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

/**
 * <a href="HttpUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class HttpUtil_IW {
	public static HttpUtil_IW getInstance() {
		return _instance;
	}

	public java.lang.String decodeURL(java.lang.String url) {
		return HttpUtil.decodeURL(url);
	}

	public java.lang.String encodeURL(java.lang.String url) {
		return HttpUtil.encodeURL(url);
	}

	public java.lang.String getQueryString(java.lang.String url) {
		return HttpUtil.getQueryString(url);
	}

	public java.util.Map parameterMapFromString(java.lang.String queryString) {
		return HttpUtil.parameterMapFromString(queryString);
	}

	public java.lang.String parameterMapToString(java.util.Map parameterMap) {
		return HttpUtil.parameterMapToString(parameterMap);
	}

	public java.lang.String parameterMapToString(java.util.Map parameterMap,
		boolean addQuestion) {
		return HttpUtil.parameterMapToString(parameterMap, addQuestion);
	}

	private HttpUtil_IW() {
	}

	private static HttpUtil_IW _instance = new HttpUtil_IW();
}