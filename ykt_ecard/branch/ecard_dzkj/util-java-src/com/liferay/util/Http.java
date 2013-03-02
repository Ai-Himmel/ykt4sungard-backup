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

package com.liferay.util;

import com.liferay.util.lang.FastStringBuffer;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;

import java.net.URL;
import java.net.URLConnection;
import java.net.URLDecoder;
import java.net.URLEncoder;

import java.util.Iterator;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.httpclient.Cookie;
import org.apache.commons.httpclient.Header;
import org.apache.commons.httpclient.HostConfiguration;
import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpMethod;
import org.apache.commons.httpclient.HttpState;
import org.apache.commons.httpclient.SimpleHttpConnectionManager;
import org.apache.commons.httpclient.URI;
import org.apache.commons.httpclient.cookie.CookiePolicy;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.commons.httpclient.methods.PostMethod;

/**
 * <a href="Http.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.37 $
 *
 */
public class Http {

	public static final String FILE_ENCODING = "file.encoding";

	public static final String HTTP = "http";

	public static final String HTTPS = "https";

	public static final String HTTP_WITH_SLASH = "http://";

	public static final String HTTPS_WITH_SLASH = "https://";

	public static final int HTTP_PORT = 80;

	public static final int HTTPS_PORT = 443;

	public static final String PROXY_HOST = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.host"));

	public static final int PROXY_PORT = GetterUtil.getInteger(
		SystemProperties.get(Http.class.getName() + ".proxy.port"));

	public static final int TIMEOUT = GetterUtil.getInteger(
		SystemProperties.get(Http.class.getName() + ".timeout"), 5000);

	public static String decodeURL(String url) {
		if (url == null) {
			return null;
		}

		try {
			return URLDecoder.decode(url, SystemProperties.get(FILE_ENCODING));
		}
		catch (UnsupportedEncodingException uee) {
			uee.printStackTrace();

			return StringPool.BLANK;
		}
	}

	public static String encodeURL(String url) {
		if (url == null) {
			return null;
		}

		try {
			return URLEncoder.encode(url, SystemProperties.get(FILE_ENCODING));
		}
		catch (UnsupportedEncodingException uee) {
			uee.printStackTrace();

			return StringPool.BLANK;
		}
	}

	public static String getCompleteURL(HttpServletRequest req) {
		StringBuffer completeURL = req.getRequestURL();

		if (completeURL == null) {
			completeURL = new StringBuffer();
		}

		if (req.getQueryString() != null) {
			completeURL.append(StringPool.QUESTION);
			completeURL.append(req.getQueryString());
		}

		return completeURL.toString();
	}

	public static String getProtocol(boolean secure) {
		if (!secure) {
			return HTTP;
		}
		else {
			return HTTPS;
		}
	}

	public static String getProtocol(HttpServletRequest req) {
		return getProtocol(req.isSecure());
	}

	public static String getProtocol(ActionRequest req) {
		return getProtocol(req.isSecure());
	}

	public static String getProtocol(RenderRequest req) {
		return getProtocol(req.isSecure());
	}

	public static String getRequestURL(HttpServletRequest req) {
		return req.getRequestURL().toString();
	}

	public static String parameterMapToString(Map parameterMap) {
		return parameterMapToString(parameterMap, true);
	}

	public static String parameterMapToString(
		Map parameterMap, boolean addQuestion) {

		FastStringBuffer sb = new FastStringBuffer();

		if (parameterMap.size() > 0) {
			if (addQuestion) {
				sb.append(StringPool.QUESTION);
			}

			Iterator itr = parameterMap.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				String name = (String)entry.getKey();
				String[] values = (String[])entry.getValue();

				for (int i = 0; i < values.length; i++) {
					sb.append(name);
					sb.append(StringPool.EQUAL);
					sb.append(Http.encodeURL(values[i]));
					sb.append(StringPool.AMPERSAND);
				}
			}

			sb.deleteCharAt(sb.length() - 1);
		}

		return sb.toString();
	}

	public static String protocolize(String url, boolean secure) {
		if (secure) {
			if (url.startsWith(HTTP_WITH_SLASH)) {
				return StringUtil.replace(
					url, HTTP_WITH_SLASH, HTTPS_WITH_SLASH);
			}
		}
		else {
			if (url.startsWith(HTTPS_WITH_SLASH)) {
				return StringUtil.replace(
					url, HTTPS_WITH_SLASH, HTTP_WITH_SLASH);
			}
		}

		return url;
	}

	public static String protocolize(String url, HttpServletRequest req) {
		return protocolize(url, req.isSecure());
	}

	public static String protocolize(String url, ActionRequest req) {
		return protocolize(url, req.isSecure());
	}

	public static String protocolize(String url, RenderRequest req) {
		return protocolize(url, req.isSecure());
	}

	public static void submit(String location) throws IOException {
		submit(location, null);
	}

	public static void submit(String location, Cookie[] cookies)
		throws IOException {

		submit(location, cookies, false);
	}

	public static void submit(String location, boolean post)
		throws IOException {

		submit(location, null, post);
	}

	public static void submit(
			String location, Cookie[] cookies, boolean post)
		throws IOException {

		URLtoByteArray(location, cookies, post);
	}

	public static byte[] URLtoByteArray(String location)
		throws IOException {

		return URLtoByteArray(location, null);
	}

	public static byte[] URLtoByteArray(String location, Cookie[] cookies)
		throws IOException {

		return URLtoByteArray(location, cookies, false);
	}

	public static byte[] URLtoByteArray(String location, boolean post)
		throws IOException {

		return URLtoByteArray(location, null, post);
	}

	public static byte[] URLtoByteArray(
			String location, Cookie[] cookies, boolean post)
		throws IOException {

		byte[] byteArray = null;

		HttpMethod method = null;

		try {
			HttpClient client =
				new HttpClient(new SimpleHttpConnectionManager());

			if (location == null) {
				return byteArray;
			}
			else if (!location.startsWith(HTTP_WITH_SLASH) &&
					 !location.startsWith(HTTPS_WITH_SLASH)) {

				location = HTTP_WITH_SLASH + location;
			}

			HostConfiguration hostConfig = new HostConfiguration();

			hostConfig.setHost(new URI(location));

			if (Validator.isNotNull(PROXY_HOST) && PROXY_PORT > 0) {
				hostConfig.setProxy(PROXY_HOST, PROXY_PORT);
			}

			client.setHostConfiguration(hostConfig);
			client.setConnectionTimeout(TIMEOUT);
			client.setTimeout(TIMEOUT);

			if (cookies != null && cookies.length > 0) {
				HttpState state = new HttpState();

				state.addCookies(cookies);
				state.setCookiePolicy(CookiePolicy.COMPATIBILITY);

				client.setState(state);
			}

			if (post) {
				method = new PostMethod(location);
			}
			else {
				method = new GetMethod(location);
			}

			method.setFollowRedirects(true);

			client.executeMethod(method);

			Header locationHeader = method.getResponseHeader("location");
			if (locationHeader != null) {
				return URLtoByteArray(locationHeader.getValue(), cookies, post);
			}

			InputStream is = method.getResponseBodyAsStream();

			if (is != null) {
				ByteArrayOutputStream buffer = new ByteArrayOutputStream();
				byte[] bytes = new byte[512];

				for (int i = is.read(bytes, 0, 512); i != -1;
						i = is.read(bytes, 0, 512)) {

					buffer.write(bytes, 0, i);
				}

				byteArray = buffer.toByteArray();

				is.close();
				buffer.close();
			}

			return byteArray;
		}
		finally {
			try {
				if (method != null) {
					method.releaseConnection();
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	public static String URLtoString(String location)
		throws IOException {

		return URLtoString(location, null);
	}

	public static String URLtoString(String location, Cookie[] cookies)
		throws IOException {

		return URLtoString(location, cookies, false);
	}

	public static String URLtoString(String location, boolean post)
		throws IOException {

		return URLtoString(location, null, post);
	}

	public static String URLtoString(String location, Cookie[] cookies,
									 boolean post)
		throws IOException {

		return new String(URLtoByteArray(location, cookies, post));
	}

	public static String URLtoString(URL url) throws IOException {
		String xml = null;

		if (url != null) {
			URLConnection con = url.openConnection();

			con.setRequestProperty(
				"Content-Type", "application/x-www-form-urlencoded");

			con.setRequestProperty(
				"User-agent",
				"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)");

			InputStream is = con.getInputStream();

			ByteArrayOutputStream buffer = new ByteArrayOutputStream();
			byte[] bytes = new byte[512];

			for (int i = is.read(bytes, 0, 512); i != -1;
					i = is.read(bytes, 0, 512)) {

				buffer.write(bytes, 0, i);
			}

			xml = new String(buffer.toByteArray());

			is.close();
			buffer.close();
		}

		return xml;
	}

}