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

package com.liferay.portal.security.auth;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;

import edu.yale.its.tp.cas.client.filter.CASFilter;

import javax.naming.Binding;
import javax.naming.NamingEnumeration;
import javax.naming.directory.Attributes;
import javax.naming.directory.SearchControls;
import javax.naming.ldap.LdapContext;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CASAutoLogin.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class CASAutoLogin implements AutoLogin {

	public String[] login(HttpServletRequest req, HttpServletResponse res)
		throws AutoLoginException {

		try {
			String[] credentials = null;

			long companyId = PortalUtil.getCompanyId(req);

			if (!PrefsPropsUtil.getBoolean(
					companyId, PropsUtil.CAS_AUTH_ENABLED,
					PropsValues.CAS_AUTH_ENABLED)) {

				return credentials;
			}

			HttpSession ses = req.getSession();

			String screenName =
				(String)ses.getAttribute(CASFilter.CAS_FILTER_USER);

			if (screenName != null) {
				User user = null;

				try {
					user = UserLocalServiceUtil.getUserByScreenName(
						companyId, screenName);
				}
				catch (NoSuchUserException nsue) {
					if (PrefsPropsUtil.getBoolean(
							companyId, PropsUtil.CAS_IMPORT_FROM_LDAP)) {

						user = addUser(companyId, screenName);
					}
					else {
						throw nsue;
					}
				}

				credentials = new String[3];

				credentials[0] = String.valueOf(user.getUserId());
				credentials[1] = user.getPassword();
				credentials[2] = Boolean.TRUE.toString();
			}

			return credentials;
		}
		catch (Exception e) {
			throw new AutoLoginException(e);
		}
	}

	protected User addUser(long companyId, String screenName)
		throws PortalException, SystemException {

		try {
			String baseDN = PrefsPropsUtil.getString(
				companyId, PropsUtil.LDAP_BASE_DN);

			LdapContext ctx = PortalLDAPUtil.getContext(companyId);

			if (ctx == null) {
				throw new SystemException("Failed to bind to the LDAP server");
			}

			String filter = PrefsPropsUtil.getString(
				companyId, PropsUtil.LDAP_AUTH_SEARCH_FILTER);

			if (_log.isDebugEnabled()) {
				_log.debug("Search filter before transformation " + filter);
			}

			filter = StringUtil.replace(
				filter,
				new String[] {
					"@company_id@", "@email_address@", "@screen_name@"
				},
				new String[] {
					String.valueOf(companyId), StringPool.BLANK, screenName
				});

			if (_log.isDebugEnabled()) {
				_log.debug("Search filter after transformation " + filter);
			}

			SearchControls cons = new SearchControls(
				SearchControls.SUBTREE_SCOPE, 1, 0, null, false, false);

			NamingEnumeration enu = ctx.search(baseDN, filter, cons);

			if (enu.hasMore()) {
				if (_log.isDebugEnabled()) {
					_log.debug("Search filter returned at least one result");
				}

				Binding binding = (Binding)enu.next();

				Attributes attrs = ctx.getAttributes(binding.getName());

				return PortalLDAPUtil.importLDAPUser(
					companyId, ctx, attrs, StringPool.BLANK, true);
			}
			else {
				throw new NoSuchUserException(
					"User " + screenName + " was not found in the LDAP server");
			}
		}
		catch (Exception e) {
			_log.error("Problem accessing LDAP server ", e);

			throw new SystemException(
				"Problem accessign LDAP server " + e.getMessage());
		}
	}

	private static Log _log = LogFactory.getLog(CASAutoLogin.class);

}