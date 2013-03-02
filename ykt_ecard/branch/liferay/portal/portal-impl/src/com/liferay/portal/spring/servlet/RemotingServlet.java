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

package com.liferay.portal.spring.servlet;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.security.auth.PrincipalThreadLocal;
import com.liferay.portal.security.permission.PermissionCheckerFactory;
import com.liferay.portal.security.permission.PermissionCheckerImpl;
import com.liferay.portal.security.permission.PermissionThreadLocal;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.util.spring.context.LazyWebApplicationContext;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.springframework.web.servlet.DispatcherServlet;

/**
 * <a href="RemotingServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RemotingServlet extends DispatcherServlet {

	public static final String CONTEXT_CLASS =
		LazyWebApplicationContext.class.getName();

	public static final String CONTEXT_CONFIG_LOCATION =
		"/WEB-INF/remoting-servlet.xml,/WEB-INF/remoting-servlet-ext.xml";

	public Class getContextClass() {
		try {
			return Class.forName(CONTEXT_CLASS);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return null;
	}

	public String getContextConfigLocation() {
		return CONTEXT_CONFIG_LOCATION;
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		PermissionCheckerImpl permissionChecker = null;

		try {
			String remoteUser = req.getRemoteUser();

			if (_log.isDebugEnabled()) {
				_log.debug("Remote user " + remoteUser);
			}

			long companyId = PortalInstances.getCompanyId(req);

			CompanyThreadLocal.setCompanyId(companyId);

			if (remoteUser != null) {
				PrincipalThreadLocal.setName(remoteUser);

				long userId = GetterUtil.getLong(remoteUser);

				User user = UserLocalServiceUtil.getUserById(userId);

				permissionChecker = PermissionCheckerFactory.create(user, true);

				PermissionThreadLocal.setPermissionChecker(permissionChecker);
			}
			else {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"User id is not provided. An exception will be " +
							"thrown  if a protected method is accessed.");
				}
			}

			super.service(req, res);
		}
		catch (Exception e) {
			throw new ServletException(e);
		}
		finally {
			try {
				PermissionCheckerFactory.recycle(permissionChecker);
			}
			catch (Exception e) {
			}
		}
	}

	private static Log _log = LogFactory.getLog(RemotingServlet.class);

}