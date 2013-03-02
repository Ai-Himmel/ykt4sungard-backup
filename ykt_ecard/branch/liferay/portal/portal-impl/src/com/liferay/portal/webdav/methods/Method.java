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

package com.liferay.portal.webdav.methods;

import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.webdav.WebDAVException;
import com.liferay.portal.webdav.WebDAVRequest;

/**
 * <a href="Method.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface Method {

	public static final String COPY = "COPY";

	public static final String DELETE = "DELETE";

	public static final String GET = "GET";

	public static final String HEAD = "HEAD";

	public static final String LOCK = "LOCK";

	public static final String MKCOL = "MKCOL";

	public static final String MOVE = "MOVE";

	public static final String OPTIONS = "OPTIONS";

	public static final String PROPFIND = "PROPFIND";

	public static final String PROPPATCH = "PROPPATCH";

	public static final String PUT = "PUT";

	public static final String UNLOCK = "UNLOCK";

	public static final String[] SUPPORTED_METHODS_ARRAY = {
		COPY, DELETE, GET, HEAD, LOCK, MKCOL, MOVE, OPTIONS, PROPFIND,
		PROPPATCH, PUT, UNLOCK
	};

	public static final String SUPPORTED_METHODS =
		StringUtil.merge(SUPPORTED_METHODS_ARRAY);

	public int process(WebDAVRequest webDavReq) throws WebDAVException;

}