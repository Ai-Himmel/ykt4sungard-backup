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

package com.liferay.portal.servlet.filters.servletauthorizing;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.security.auth.PrincipalThreadLocal;
import com.liferay.portal.security.permission.PermissionCheckerFactory;
import com.liferay.portal.security.permission.PermissionCheckerImpl;
import com.liferay.portal.security.permission.PermissionThreadLocal;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.ProtectedServletRequest;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;

/**
 * <a href="ServletAuthorizingFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class ServletAuthorizingFilter extends BaseFilter {

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		HttpServletRequest httpReq = (HttpServletRequest)req;

		HttpSession ses = httpReq.getSession();

		// Company id

		long companyId = PortalInstances.getCompanyId(httpReq);

		// We need to set the COMPANY_ID request attribute explicitly because
		// the above does not.

		httpReq.setAttribute(WebKeys.COMPANY_ID, new Long(companyId));

		// Authorize

		long userId = PortalUtil.getUserId(httpReq);
		String remoteUser = httpReq.getRemoteUser();

		if (!PropsValues.PORTAL_JAAS_ENABLE) {
			String jRemoteUser = (String)ses.getAttribute("j_remoteuser");

			if (jRemoteUser != null) {
				remoteUser = jRemoteUser;

				ses.removeAttribute("j_remoteuser");
			}
		}

		if ((userId > 0) && (remoteUser == null)) {
			remoteUser = String.valueOf(userId);
		}

		// WebSphere will not return the remote user unless you are
		// authenticated AND accessing a protected path. Other servers will
		// return the remote user for all threads associated with an
		// authenticated user. We use ProtectedServletRequest to ensure we get
		// similar behavior across all servers.

		req = new ProtectedServletRequest(httpReq, remoteUser);

		PermissionCheckerImpl permissionChecker = null;

		if ((userId > 0) || (remoteUser != null)) {

			// Set the principal associated with this thread

			String name = String.valueOf(userId);

			if (remoteUser != null) {
				name = remoteUser;
			}

			PrincipalThreadLocal.setName(name);

			// User id

			userId = GetterUtil.getLong(name);

			try {

				// User

				User user = UserLocalServiceUtil.getUserById(userId);

				// Permission checker

				permissionChecker = PermissionCheckerFactory.create(user, true);

				PermissionThreadLocal.setPermissionChecker(permissionChecker);

				// User id

				ses.setAttribute(WebKeys.USER_ID, new Long(userId));

				// User locale

				ses.setAttribute(Globals.LOCALE_KEY, user.getLocale());
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}

		try {
			doFilter(ServletAuthorizingFilter.class, req, res, chain);
		}
		finally {
			try {

				// Clean up the permission checker

				PermissionCheckerFactory.recycle(permissionChecker);
			}
			catch (Exception e) {
				_log.error(e, e);
			}

			// Clear the company id associated with this thread

			CompanyThreadLocal.setCompanyId(0);

			// Clear the principal associated with this thread

			PrincipalThreadLocal.setName(null);
		}
	}

	private static final Log _log =
		LogFactoryUtil.getLog(ServletAuthorizingFilter.class);

}