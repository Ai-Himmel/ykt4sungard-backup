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

package com.liferay.portal.spring.remoting;

import com.liferay.portal.PwdEncryptorException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.security.pwd.PwdEncryptor;

import java.io.IOException;

import java.net.HttpURLConnection;

import org.apache.commons.codec.binary.Base64;

import org.springframework.remoting.httpinvoker.SimpleHttpInvokerRequestExecutor;

/**
 * <a href="AuthenticatingHttpInvokerRequestExecutor.java.html"><b><i>
 * View Source</i></b></a>
 *
 * <p>
 * An HttpInvoker request executor for Spring Remoting that provides HTTP BASIC
 * authentication information for service invocations.
 * </p>
 *
 * @author Joel Kozikowski
 *
 */
public class AuthenticatingHttpInvokerRequestExecutor
	extends SimpleHttpInvokerRequestExecutor {

	public AuthenticatingHttpInvokerRequestExecutor() {
		super();
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public String getPassword() {
		return _password;
	}

	public void setPassword(String password) throws PwdEncryptorException {
		_password = PwdEncryptor.encrypt(password);
	}

	/**
	 * Called every time a HTTP invocation is made. This implementation allows
	 * the parent to setup the connection, and then adds an
	 * <code>Authorization</code> HTTP header property for BASIC authentication.
	 */
	protected void prepareConnection(HttpURLConnection con, int contentLength)
		throws IOException {

		prepareConnection(con, contentLength);

		if (getUserId() > 0) {
			String password = GetterUtil.getString(getPassword());

			String base64 = getUserId() + StringPool.COLON + password;

			con.setRequestProperty(
				"Authorization",
				"Basic " + new String(Base64.encodeBase64(base64.getBytes())));
		}
	}

	private long _userId;
	private String _password;

}