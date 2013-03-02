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

package com.liferay.portal.servlet;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.util.Base64;
import com.liferay.util.ObjectValuePair;
import com.liferay.util.lang.MethodWrapper;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import java.net.HttpURLConnection;
import java.net.URL;

/**
 * <a href="TunnelUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class TunnelUtil {

	public static Object invoke(
			HttpPrincipal httpPrincipal, MethodWrapper methodWrapper)
		throws Exception {

		HttpURLConnection urlc = _getConnection(httpPrincipal);

		ObjectOutputStream oos = new ObjectOutputStream(urlc.getOutputStream());

		oos.writeObject(new ObjectValuePair(httpPrincipal, methodWrapper));

		oos.flush();
		oos.close();

		Object returnObj = null;

		try {
			ObjectInputStream ois =
				new ObjectInputStream(urlc.getInputStream());

			returnObj = ois.readObject();

			ois.close();
		}
		catch (EOFException eofe) {
		}
		catch (IOException ioe) {
			String ioeMessage = ioe.getMessage();

			if ((ioeMessage != null) &&
					(ioeMessage.indexOf("HTTP response code: 401") != -1)) {
				throw new PrincipalException(ioeMessage);
			}
			else {
				throw ioe;
			}
		}

		if ((returnObj != null) && returnObj instanceof Exception) {
			throw (Exception)returnObj;
		}

		return returnObj;
	}

	private static HttpURLConnection _getConnection(HttpPrincipal httpPrincipal)
		throws IOException {

		if (httpPrincipal == null || httpPrincipal.getUrl() == null) {
			return null;
		}

		URL url = null;
		if (httpPrincipal.getUserId() == null ||
			httpPrincipal.getPassword() == null) {

			url = new URL(
				httpPrincipal.getUrl() + "/tunnel/servlet/TunnelServlet");
		}
		else {
			url = new URL(
				httpPrincipal.getUrl() + "/tunnel/servlet/AuthTunnelServlet");
		}

		HttpURLConnection urlc = (HttpURLConnection)url.openConnection();

		urlc.setDoInput(true);
		urlc.setDoOutput(true);
		urlc.setUseCaches(false);

		urlc.setRequestMethod("POST");

		if (httpPrincipal.getUserId() != null &&
			httpPrincipal.getPassword() != null) {

			String userNameAndPassword =
				httpPrincipal.getUserId() + ":" + httpPrincipal.getPassword();

			urlc.setRequestProperty(
				"Authorization",
				"Basic " + Base64.encode(userNameAndPassword.getBytes()));
		}

		return urlc;
	}

}