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

package com.liferay.portal.webdav;

import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="WebDAVRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WebDAVRequest {

	public WebDAVRequest(WebDAVStorage storage, HttpServletRequest req,
						 HttpServletResponse res,
						 PermissionChecker permissionChecker) {

		_storage = storage;
		_req = req;
		_res = res;
		_path = WebDAVUtil.fixPath(_req.getPathInfo());
		_groupPath = WebDAVUtil.isGroupPath(_path);
		_companyId = WebDAVUtil.getCompanyId(_path);
		_groupId = WebDAVUtil.getGroupId(_path);
		_userId = GetterUtil.getLong(_req.getRemoteUser());
		_permissionChecker = permissionChecker;
	}

	public WebDAVStorage getWebDAVStorage() {
		return _storage;
	}

	public HttpServletRequest getHttpServletRequest() {
		return _req;
	}

	public HttpServletResponse getHttpServletResponse() {
		return _res;
	}

	public String getRootPath() {
		return _storage.getRootPath();
	}

	public String getPath() {
		return _path;
	}

	public String[] getPathArray() {
		return WebDAVUtil.getPathArray(_path);
	}

	public boolean isGroupPath() {
		return _groupPath;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public long getGroupId() {
		return _groupId;
	}

	public long getUserId() {
		return _userId;
	}

	public PermissionChecker getPermissionChecker() {
		return _permissionChecker;
	}

	private WebDAVStorage _storage;
	private HttpServletRequest _req;
	private HttpServletResponse _res;
	private String _path = StringPool.BLANK;
	private boolean _groupPath;
	private long _companyId;
	private long _groupId;
	private long _userId;
	private PermissionChecker _permissionChecker;

}