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

package com.liferay.portal.security.jaas.ext;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.security.jaas.PortalPrincipal;
import com.liferay.portal.service.UserLocalServiceUtil;

import java.io.IOException;

import java.security.Principal;

import java.util.Map;

import javax.security.auth.Subject;
import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.NameCallback;
import javax.security.auth.callback.PasswordCallback;
import javax.security.auth.callback.UnsupportedCallbackException;
import javax.security.auth.login.LoginException;
import javax.security.auth.spi.LoginModule;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BasicLoginModule.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BasicLoginModule implements LoginModule {

	public boolean abort() {
		return true;
	}

	public boolean commit() {
		if (getPrincipal() != null) {
			getSubject().getPrincipals().add(getPrincipal());

			return true;
		}
		else {
			return false;
		}
	}

	public void initialize(
		Subject subject, CallbackHandler callbackHandler, Map sharedState,
		Map options) {

		_subject = subject;
		_callbackHandler = callbackHandler;
	}

	public boolean login() throws LoginException {
		String[] credentials = null;

		try {
			credentials = authenticate();
		}
		catch (Exception e) {
			_log.error(e.getMessage());

			throw new LoginException();
		}

		if ((credentials != null) && (credentials.length == 2)) {
			setPrincipal(getPortalPrincipal(credentials[0]));
			setPassword(credentials[1]);

			return true;
		}
		else {
			throw new LoginException();
		}
	}

	public boolean logout() {
		getSubject().getPrincipals().clear();

		return true;
	}

	protected Subject getSubject() {
		return _subject;
	}

	protected Principal getPrincipal() {
		return _principal;
	}

	protected void setPrincipal(Principal principal) {
		_principal = principal;
	}

	protected Principal getPortalPrincipal(String name) {
		return new PortalPrincipal(name);
	}

	protected String getPassword() {
		return _password;
	}

	protected void setPassword(String password) {
		_password = password;
	}

	protected String[] authenticate()
		throws IOException, UnsupportedCallbackException {

		NameCallback nameCallback = new NameCallback("name: ");
		PasswordCallback passwordCallback =
			new PasswordCallback("password: ", false);

		_callbackHandler.handle(
			new Callback[] {
				nameCallback, passwordCallback
			});

		String name = nameCallback.getName();

		String password = null;
		char[] passwordChar = passwordCallback.getPassword();

		if (passwordChar != null) {
			password = new String(passwordChar);
		}

		if (name == null) {
			return new String[] {StringPool.BLANK, StringPool.BLANK};
		}

		try {
			long userId = GetterUtil.getLong(name);

			if (UserLocalServiceUtil.authenticateForJAAS(userId, password)) {
				return new String[] {name, password};
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		return null;
	}

	private static Log _log = LogFactory.getLog(BasicLoginModule.class);

	private Subject _subject;
	private CallbackHandler _callbackHandler;
	private Principal _principal;
	private String _password;

}