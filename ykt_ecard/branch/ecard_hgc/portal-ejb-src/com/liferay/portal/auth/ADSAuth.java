/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.auth;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;

import java.util.Date;
import java.util.Hashtable;
import java.util.Locale;

import javax.naming.Binding;
import javax.naming.Context;
import javax.naming.NamingEnumeration;
import javax.naming.directory.Attributes;
import javax.naming.directory.SearchControls;
import javax.naming.ldap.InitialLdapContext;
import javax.naming.ldap.LdapContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ADSAuth.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Paul Hussein
 * @author  Steve Goldsmith
 * @version $Revision: 1.4 $
 *
 */
public class ADSAuth implements Authenticator {

	public static String INITIAL_CONTEXT_FACTORY =
		PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_INITIAL_CONTEXT_FACTORY);

	public static String SECURITY_AUTHENTICATION =
		PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_SECURITY_AUTHENTICATION);

	public static String HOST = PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_HOST);

	public static String PORT = PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_PORT);

	public static String USERID = PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_USERID);

	public static String PASSWORD =
		PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_PASSWORD);

	public static String DOMAINLOOKUP =
		PropsUtil.get(PropsUtil.AUTH_IMPL_ADS_DOMAINLOOKUP);

	public static String URL =
		"ldap://" + HOST + ":" + PORT + "/" + DOMAINLOOKUP;

	public int authenticateByEmailAddress(
			String companyId,  String emailAddress, String password)
		throws AuthException {

		// Pass the used id part of the email address

		return authenticate(companyId, emailAddress.split("@")[0], password);
	}

	public int authenticateByUserId(
			String companyId, String userId, String password)
		throws AuthException {

		return authenticate(companyId, userId, password);
	}

	public int authenticate(String companyId, String userId, String password)
		throws AuthException {

		LdapContext ctx = null;

		try {

			// Check the LDAP server to ensure the company id, email address,
			// and password is valid

			Hashtable env = new Hashtable();

			env.put(Context.INITIAL_CONTEXT_FACTORY, INITIAL_CONTEXT_FACTORY);
			env.put(Context.SECURITY_PRINCIPAL, USERID);
			env.put(Context.SECURITY_CREDENTIALS, PASSWORD);
			env.put(Context.PROVIDER_URL, URL);

			try {
				ctx = new InitialLdapContext(env, null);
			}
			catch (Exception e) {
				return FAILURE;
			}

			String authId = null;
			String emailAddress = null;
			String firstName = null;
			String middleName = null;
			String lastName = null;

			String ldapFilterString =
				"(&(objectCategory=person)(sAMAccountName=" + userId + "))";
			SearchControls sch = new SearchControls(
				SearchControls.SUBTREE_SCOPE, 1, 0, null, false, false);

			NamingEnumeration ctxSearch = ctx.search("", ldapFilterString, sch);

			if (ctxSearch.hasMore()) {
				Binding bd = (Binding)ctxSearch.next();

				Attributes attrs = ctx.getAttributes(bd.getName());

				authId = attrs.get("cn").get().toString();
				emailAddress = attrs.get("mail").get().toString();
				firstName = attrs.get("givenName").get().toString();

				if (attrs.get("initials") != null) {
					middleName = attrs.get("initials").get().toString();
				}

				lastName = attrs.get("sn").get().toString();
			}

			ctx.close();

			if ((emailAddress == null) || (emailAddress.length() < 3)) {
				return FAILURE;
			}

			// Make sure the fetched user id and password combination can bind
			// against the LDAP server

			env.put(Context.SECURITY_PRINCIPAL, emailAddress);
			env.put(Context.SECURITY_CREDENTIALS, password);

			try {
				ctx = new InitialLdapContext(env, null);
			}
			catch (Exception e) {
				return FAILURE;
			}

			// Make sure the user has a portal account

			User user = null;

			try {
				user = UserLocalServiceUtil.getUserById(companyId, userId);
			}
			catch (NoSuchUserException nsue) {
				boolean autoUserId = false;
				boolean autoPassword = false;
				String password1 = password;
				String password2 = password;
				boolean passwordReset = false;
				String nickName = "";
				boolean male = true;
				Date birthday = new Date();
				Locale locale = Locale.US;

				user = UserLocalServiceUtil.addUser(
					companyId, autoUserId, userId, autoPassword, password1,
					password2, passwordReset, firstName, middleName, lastName,
					nickName, male, birthday, emailAddress, locale);
			}

			return SUCCESS;
		}
		catch (Exception e) {
			e.printStackTrace();

			throw new AuthException(e);
		}
		finally {
			try {
				ctx.close();
			}
			catch (Exception e) {
			}
		}
	}

	private static final Log _log = LogFactory.getLog(ADSAuth.class);

}