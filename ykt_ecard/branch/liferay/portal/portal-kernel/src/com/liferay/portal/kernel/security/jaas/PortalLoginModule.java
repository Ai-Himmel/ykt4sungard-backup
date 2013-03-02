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

package com.liferay.portal.kernel.security.jaas;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.PortalClassLoaderUtil;

import java.util.Map;

import javax.security.auth.Subject;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.login.LoginException;
import javax.security.auth.spi.LoginModule;

/**
 * <a href="PortalLoginModule.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalLoginModule implements LoginModule {

	public PortalLoginModule() {
		try {
			Class classObj = Class.forName(
				_CLASS_NAME, true, PortalClassLoaderUtil.getClassLoader());

			_loginModule = (LoginModule)classObj.newInstance();
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	public boolean abort() throws LoginException {
		return _loginModule.abort();
	}

	public boolean commit() throws LoginException {
		return _loginModule.commit();
	}

	public void initialize(
		Subject subject, CallbackHandler callbackHandler, Map sharedState,
		Map options) {

		_loginModule.initialize(subject, callbackHandler, sharedState, options);
	}

	public boolean login() throws LoginException {
		return _loginModule.login();
	}

	public boolean logout() throws LoginException {
		return _loginModule.logout();
	}

	private static final String _CLASS_NAME =
		"com.liferay.portal.security.jaas.PortalLoginModule";

 	private static Log _log = LogFactoryUtil.getLog(PortalLoginModule.class);

	private LoginModule _loginModule;

}