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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.PrincipalThreadLocal;
import com.liferay.portal.security.permission.PermissionCheckerFactory;
import com.liferay.portal.security.permission.PermissionCheckerImpl;
import com.liferay.portal.security.permission.PermissionThreadLocal;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.webdav.methods.Method;
import com.liferay.portal.webdav.methods.MethodFactory;

import java.io.IOException;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="WebDAVServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class WebDAVServlet extends HttpServlet {

	public void init(ServletConfig config) throws ServletException {
		super.init(config);

		String storageClass = config.getInitParameter("storage-class");

		_storage = (WebDAVStorage)InstancePool.get(storageClass);
	}

 	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		PermissionCheckerImpl permissionChecker = null;

		int status = HttpServletResponse.SC_NOT_IMPLEMENTED;

		try {

			// Set the path only if it hasn't already been set. This works if
			// and only if the servlet is not mapped to more than one URL.

			if (_storage.getRootPath() == null) {
				_storage.setRootPath(getRootPath(req));
			}

			// Permission checker

			String remoteUser = req.getRemoteUser();

			if (remoteUser != null) {
				PrincipalThreadLocal.setName(remoteUser);

				long userId = GetterUtil.getLong(remoteUser);

				User user = UserLocalServiceUtil.getUserById(userId);

				permissionChecker = PermissionCheckerFactory.create(user, true);

				PermissionThreadLocal.setPermissionChecker(permissionChecker);
			}

			// Get the method instance

			Method method = MethodFactory.create(req);

			// Process the method

			WebDAVRequest webDavReq = new WebDAVRequest(
				_storage, req, res, permissionChecker);

			if (_log.isInfoEnabled()) {
				_log.info(
					"Remote user " + remoteUser + " " + req.getMethod() + " " +
						req.getRequestURI());
			}

			status = method.process(webDavReq);
		}
		catch (Exception e) {
			_log.error(e, e);
		}
		finally {
			if (status > 0) {
				res.setStatus(status);

				if (_log.isInfoEnabled()) {
					_log.info("Returning status code " + status);
				}
			}

			try {
				PermissionCheckerFactory.recycle(permissionChecker);
			}
			catch (Exception e) {
			}
		}
	}

	protected String getRootPath(HttpServletRequest req) {
		StringMaker sm = new StringMaker();

		sm.append(WebDAVUtil.fixPath(req.getContextPath()));
		sm.append(WebDAVUtil.fixPath(req.getServletPath()));

		String rootPath = sm.toString();

		if (_log.isDebugEnabled()) {
			_log.debug("Root path " + rootPath);
		}

		return rootPath;
	}

	private static Log _log = LogFactory.getLog(WebDAVServlet.class);

	private WebDAVStorage _storage;

}