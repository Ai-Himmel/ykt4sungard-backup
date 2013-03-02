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

package com.liferay.portlet;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.ProtectedPrincipal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.UnsupportedEncodingException;

import java.security.Principal;

import java.util.Enumeration;
import java.util.Locale;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletServletRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 *
 */
public class PortletServletRequest extends HttpServletRequestWrapper {

	public PortletServletRequest(
		HttpServletRequest req, RenderRequestImpl renderReq, String pathInfo,
		String queryString, String requestURI, String servletPath) {

		super(req);

		_req = req;
		_renderReq = renderReq;
		_pathInfo = GetterUtil.getString(pathInfo);
		_queryString = GetterUtil.getString(queryString);
		_requestURI = GetterUtil.getString(requestURI);
		_servletPath = GetterUtil.getString(servletPath);

		long userId = PortalUtil.getUserId(req);
		String remoteUser = req.getRemoteUser();

		Portlet portlet = renderReq.getPortlet();

		String userPrincipalStrategy = portlet.getUserPrincipalStrategy();

		if (userPrincipalStrategy.equals(
				PortletImpl.USER_PRINCIPAL_STRATEGY_SCREEN_NAME)) {

			try {
				User user = PortalUtil.getUser(req);

				_remoteUser = user.getScreenName();
				_remoteUserId = user.getUserId();
				_userPrincipal = new ProtectedPrincipal(_remoteUser);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
		else {
			if ((userId > 0) && (remoteUser == null)) {
				_remoteUser = String.valueOf(userId);
				_remoteUserId = userId;
				_userPrincipal = new ProtectedPrincipal(_remoteUser);
			}
			else {
				_remoteUser = remoteUser;
				_remoteUserId = GetterUtil.getLong(remoteUser);
				_userPrincipal = req.getUserPrincipal();
			}
		}
	}

	public Object getAttribute(String name) {
		Object retVal = super.getAttribute(name);

		if (name == null) {
			return retVal;
		}

		if (ServerDetector.isWebSphere()) {
			if (_renderReq.getPortlet().isWARFile()) {
				if (name.equals(
						JavaConstants.JAVAX_SERVLET_INCLUDE_CONTEXT_PATH)) {

					retVal = _renderReq.getContextPath();
				}
				else if (name.equals(
							JavaConstants.JAVAX_SERVLET_INCLUDE_PATH_INFO)) {

					retVal = _pathInfo;
				}
				else if (name.equals(
							JavaConstants.JAVAX_SERVLET_INCLUDE_QUERY_STRING)) {

					retVal = _queryString;
				}
				else if (name.equals(
							JavaConstants.JAVAX_SERVLET_INCLUDE_REQUEST_URI)) {

					retVal = _requestURI;
				}
				else if (name.equals(
							JavaConstants.JAVAX_SERVLET_INCLUDE_SERVLET_PATH)) {

					retVal = _servletPath;
				}
			}

			if ((name.startsWith(JavaConstants.JAVAX_SERVLET_INCLUDE)) &&
				(retVal == null)) {

				retVal = StringPool.BLANK;
			}
		}

		return retVal;
	}

	public String getCharacterEncoding() {
		if (_isUploadRequest()) {
			return super.getCharacterEncoding();
		}
		else {
			return null;
		}
	}

	public void setCharacterEncoding(String encoding)
		throws UnsupportedEncodingException {
	}

	public int getContentLength() {
		if (_isUploadRequest()) {
			return super.getContentLength();
		}
		else {
			return 0;
		}
	}

	public String getContentType() {
		if (_isUploadRequest()) {
			return super.getContentType();
		}
		else {
			return null;
		}
	}

	public String getContextPath() {
		return _renderReq.getContextPath();
	}

	public ServletInputStream getInputStream() throws IOException {
		if (_isUploadRequest()) {
			return super.getInputStream();
		}
		else {
			return null;
		}
	}

	public Locale getLocale() {
		return _renderReq.getLocale();
	}

	public Enumeration getLocales() {
		return _renderReq.getLocales();
	}

	public String getPathInfo() {
		return _pathInfo;
	}

	public String getProtocol() {
		return null;
	}

	public String getQueryString() {
		return _queryString;
	}

	public BufferedReader getReader() throws IOException {
		if (_isUploadRequest()) {
			return super.getReader();
		}
		else {
			return null;
		}
	}

	public String getRealPath(String path) {
		return null;
	}

	public String getRemoteAddr() {
		return null;
	}

	public String getRemoteHost() {
		return null;
	}

	public String getRequestURI() {
		return _requestURI;
	}

	public StringBuffer getRequestURL() {
		return null;
	}

	public String getServletPath() {
		return _servletPath;
	}

	public String getRemoteUser() {
		return _remoteUser;
	}

	public Principal getUserPrincipal() {
		return _userPrincipal;
	}

	public boolean isUserInRole(String role) {
		if (_remoteUserId <= 0) {
			return false;
		}
		else {
			try {
				long companyId = PortalUtil.getCompanyId(_req);

				return RoleLocalServiceUtil.hasUserRole(
					_remoteUserId, companyId, role, true);
			}
			catch (Exception e) {
				_log.error(e);
			}

			return super.isUserInRole(role);
		}
	}

	private boolean _isUploadRequest() {
		if (!_uploadRequestInvoked) {
			_uploadRequestInvoked = true;

			if (PortalUtil.getUploadServletRequest(this) != null) {
				_uploadRequest = true;
			}
		}

		return _uploadRequest;
	}

	private static Log _log = LogFactory.getLog(PortletServletRequest.class);

	private HttpServletRequest _req;
	private RenderRequestImpl _renderReq;
	private String _pathInfo;
	private String _queryString;
	private String _requestURI;
	private String _servletPath;
	private String _remoteUser;
	private long _remoteUserId;
	private Principal _userPrincipal;
	private boolean _uploadRequest;
	private boolean _uploadRequestInvoked;

}