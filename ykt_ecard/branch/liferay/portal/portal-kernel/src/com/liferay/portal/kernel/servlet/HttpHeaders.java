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

package com.liferay.portal.kernel.servlet;

/**
 * <a href="HttpHeaders.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface HttpHeaders {

	public static final String ACCEPT = "ACCEPT";

	public static final String ACCEPT_ENCODING = "Accept-Encoding";

	public static final String CACHE_CONTROL = "Cache-Control";

	public static final String CONNECTION = "Connection";

	public static final String CONTENT_DISPOSITION = "Content-Disposition";

	public static final String CONTENT_ID = "Content-ID";

	public static final String CONTENT_TYPE = "Content-Type";

	public static final String IF_MODIFIED_SINCE = "If-Modified-Since";

	public static final String KEEP_ALIVE = "Keep-Alive";

	public static final String LAST_MODIFIED = "Last-Modified";

	public static final String LOCATION = "Location";

	public static final String PRAGMA = "Pragma";

	public static final String PUBLIC = "public";

	public static final String USER_AGENT = "User-Agent";

}