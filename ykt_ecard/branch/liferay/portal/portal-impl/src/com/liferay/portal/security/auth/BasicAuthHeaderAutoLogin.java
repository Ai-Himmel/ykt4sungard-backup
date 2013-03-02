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
import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.service.UserLocalServiceUtil;

import java.util.StringTokenizer;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BasicAuthHeaderAutoLogin.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * 1. Install Firefox. These instructions assume you have Firefox 2.0.0.1.
 * Previous version of Firefox have been tested and are known to work.
 * </p>
 *
 * <p>
 * 2. Install the Modify Headers 0.5.4 Add-on. Tools > Add Ons. Click the get
 * extensions link at the bottom of the window. Type in "Modify Headers" in the
 * Search box. Find Modify Headers in the results page and click on it. Then
 * click the install now link.
 * </p>
 *
 * <p>
 * 3. Configure Modify Headers to add a basic authentication header. Tools >
 * Modify Headers. In the Modify Headers window select the Add drop down. Type
 * in "Authorization" in the next box. Type in "Basic bGlmZXJheS5jb20uMTp0ZXN0"
 * in the next box. Click the Add button.
 * </p>
 *
 * <p>
 * 4. Make sure your header modification is enabled and point your browser to
 * the Liferay portal.
 * </p>
 *
 * <p>
 * 5. You should now be authenticated as Joe Bloggs.
 * </p>
 *
 * @author Britt Courtney
 * @author Brian Wing Shun Chan
 *
 */
public class BasicAuthHeaderAutoLogin implements AutoLogin {

	public String[] login(HttpServletRequest req, HttpServletResponse res)
		throws AutoLoginException {

		try {
			String[] credentials = null;

			// Get the Authorization header, if one was supplied

			String authHeader = req.getHeader("Authorization");

			if (authHeader == null) {
				return credentials;
			}

			StringTokenizer st = new StringTokenizer(authHeader);

			if (!st.hasMoreTokens()) {
				return credentials;
			}

			String basic = st.nextToken();

			// We only handle HTTP Basic authentication

			if (basic.equalsIgnoreCase("Basic")) {
				String encodedCredentials = st.nextToken();

				if (_log.isDebugEnabled()) {
					_log.debug("Encoded credentials are " + encodedCredentials);
				}

				String decodedCredentials = new String(
					Base64.decode(encodedCredentials));

				if (_log.isDebugEnabled()) {
					_log.debug("Decoded credentials are " + decodedCredentials);
				}

				int p = decodedCredentials.indexOf(StringPool.COLON);

				if (p == -1) {
					return credentials;
				}

				long userId = GetterUtil.getLong(
					decodedCredentials.substring(0, p));
				String password = decodedCredentials.substring(p + 1);

				try {
					UserLocalServiceUtil.getUserById(userId);

					credentials = new String[3];

					credentials[0] = String.valueOf(userId);
					credentials[1] = password;
					credentials[2] = Boolean.TRUE.toString();
				}
				catch (NoSuchUserException nsue) {
					if (_log.isWarnEnabled()) {
						_log.warn(userId + " is not a valid user id");
					}
				}
			}

			return credentials;
		}
		catch (Exception e) {
			throw new AutoLoginException(e);
		}
	}

	private static Log _log = LogFactory.getLog(BasicAuthHeaderAutoLogin.class);

}