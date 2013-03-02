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

package com.liferay.util;

import com.liferay.portal.kernel.util.ByteArrayMaker;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;

import java.io.IOException;
import java.io.InputStream;

import java.net.URL;
import java.net.URLConnection;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.httpclient.Cookie;
import org.apache.commons.httpclient.Credentials;
import org.apache.commons.httpclient.Header;
import org.apache.commons.httpclient.HostConfiguration;
import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpMethod;
import org.apache.commons.httpclient.HttpState;
import org.apache.commons.httpclient.MultiThreadedHttpConnectionManager;
import org.apache.commons.httpclient.NTCredentials;
import org.apache.commons.httpclient.NameValuePair;
import org.apache.commons.httpclient.URI;
import org.apache.commons.httpclient.UsernamePasswordCredentials;
import org.apache.commons.httpclient.auth.AuthPolicy;
import org.apache.commons.httpclient.auth.AuthScope;
import org.apache.commons.httpclient.cookie.CookiePolicy;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.commons.httpclient.methods.PostMethod;
import org.apache.commons.httpclient.params.HttpConnectionParams;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="Http.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Http {

	public static final String HTTP = "http";

	public static final String HTTPS = "https";

	public static final String HTTP_WITH_SLASH = "http://";

	public static final String HTTPS_WITH_SLASH = "https://";

	public static final int HTTP_PORT = 80;

	public static final int HTTPS_PORT = 443;

	public static final String LIFERAY_PROXY_HOST = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.host"));

	public static final int LIFERAY_PROXY_PORT = GetterUtil.getInteger(
		SystemProperties.get(Http.class.getName() + ".proxy.port"));

	private static final int MAX_CONNECTIONS_PER_HOST = GetterUtil.getInteger(
		SystemProperties.get(
			Http.class.getName() + ".max.connections.per.host"),
		2);

	private static final int MAX_TOTAL_CONNECTIONS = GetterUtil.getInteger(
		SystemProperties.get(Http.class.getName() + ".max.total.connections"),
		20);

	public static final String PROXY_HOST = GetterUtil.getString(
		SystemProperties.get("http.proxyHost"), LIFERAY_PROXY_HOST);

	public static final int PROXY_PORT = GetterUtil.getInteger(
		SystemProperties.get("http.proxyPort"), LIFERAY_PROXY_PORT);

	public static final String NON_PROXY_HOSTS =
		SystemProperties.get("http.nonProxyHosts");

	public static final String PROXY_AUTH_TYPE = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.auth.type"));

	public static final String PROXY_USERNAME = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.username"));

	public static final String PROXY_PASSWORD = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.password"));

	public static final String PROXY_NTLM_DOMAIN = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.ntlm.domain"));

	public static final String PROXY_NTLM_HOST = GetterUtil.getString(
		SystemProperties.get(Http.class.getName() + ".proxy.ntlm.host"));

	public static final int TIMEOUT = GetterUtil.getInteger(
		SystemProperties.get(Http.class.getName() + ".timeout"), 5000);

	public static String addParameter(String url, String name, boolean value) {
		return addParameter(url, name, String.valueOf(value));
	}

	public static String addParameter(String url, String name, double value) {
		return addParameter(url, name, String.valueOf(value));
	}

	public static String addParameter(String url, String name, int value) {
		return addParameter(url, name, String.valueOf(value));
	}

	public static String addParameter(String url, String name, long value) {
		return addParameter(url, name, String.valueOf(value));
	}

	public static String addParameter(String url, String name, short value) {
		return addParameter(url, name, String.valueOf(value));
	}

	public static String addParameter(String url, String name, String value) {
		if (url == null) {
			return null;
		}

		if (url.indexOf(StringPool.QUESTION) == -1) {
			url += StringPool.QUESTION;
		}

		if (!url.endsWith(StringPool.QUESTION) &&
			!url.endsWith(StringPool.AMPERSAND)) {

			url += StringPool.AMPERSAND;
		}

		return url + name + StringPool.EQUAL + HttpUtil.encodeURL(value);
	}

	/**
	 * @deprecated This method has been moved to
	 * <code>com.liferay.util.HttpUtil</code>.
	 */
	public static String decodeURL(String url) {
		return HttpUtil.decodeURL(url);
	}

	/**
	 * @deprecated This method has been moved to
	 * <code>com.liferay.util.HttpUtil</code>.
	 */
	public static String encodeURL(String url) {
		return HttpUtil.encodeURL(url);
	}

	public static HttpClient getClient(HostConfiguration hostConfig)
		throws IOException {

		return _instance._getClient(hostConfig);
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

	public static HostConfiguration getHostConfig(String location)
		throws IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Location is " + location);
		}

		HostConfiguration hostConfig = new HostConfiguration();

		hostConfig.setHost(new URI(location, false));

		if (isProxyHost(hostConfig.getHost())) {
			hostConfig.setProxy(PROXY_HOST, PROXY_PORT);
		}

		return hostConfig;
	}

	public static String getParameter(String url, String name) {
		return getParameter(url, name, true);
	}

	public static String getParameter(
		String url, String name, boolean escaped) {

		if (Validator.isNull(url) || Validator.isNull(name)) {
			return StringPool.BLANK;
		}

		String[] parts = StringUtil.split(url, StringPool.QUESTION);

		if (parts.length == 2) {
			String[] params = null;

			if (escaped) {
				params = StringUtil.split(parts[1], "&amp;");
			}
			else {
				params = StringUtil.split(parts[1], StringPool.AMPERSAND);
			}

			for (int i = 0; i < params.length; i++) {
				String[] kvp = StringUtil.split(params[i], StringPool.EQUAL);

				if ((kvp.length == 2) && kvp[0].equals(name)) {
					return kvp[1];
				}
			}
		}

		return StringPool.BLANK;
	}

	/**
	 * @deprecated This method has been moved to
	 * <code>com.liferay.util.HttpUtil</code>.
	 */
	public static Map getParameterMap(String queryString) {
		return HttpUtil.parameterMapFromString(queryString);
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

	/**
	 * @deprecated This method has been moved to
	 * <code>com.liferay.util.HttpUtil</code>.
	 */
	public static String getQueryString(String url) {
		return HttpUtil.getQueryString(url);
	}

	public static String getRequestURL(HttpServletRequest req) {
		return req.getRequestURL().toString();
	}

	public static boolean hasProxyConfig() {
		if (Validator.isNotNull(PROXY_HOST) && (PROXY_PORT > 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isNonProxyHost(String host) {
		return _instance._isNonProxyHost(host);
	}

	public static boolean isProxyHost(String host) {
		if (hasProxyConfig() && !isNonProxyHost(host)) {
			return true;
		}
		else {
			return false;
		}
	}

	/**
	 * @deprecated This method has been moved to
	 * <code>com.liferay.util.HttpUtil</code>.
	 */
	public static String parameterMapToString(Map parameterMap) {
		return HttpUtil.parameterMapToString(parameterMap);
	}

	/**
	 * @deprecated This method has been moved to
	 * <code>com.liferay.util.HttpUtil</code>.
	 */
	public static String parameterMapToString(
		Map parameterMap, boolean addQuestion) {

		return HttpUtil.parameterMapToString(parameterMap, addQuestion);
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

	public static void proxifyState(
		HttpState state, HostConfiguration hostConfig) {

		Credentials proxyCredentials = _instance._proxyCredentials;

		String host = hostConfig.getHost();

		if (isProxyHost(host) && (proxyCredentials != null)) {
			AuthScope scope = new AuthScope(PROXY_HOST, PROXY_PORT, null);

			state.setProxyCredentials(scope, proxyCredentials);
		}
	}

	public static String removeParameter(String url, String name) {
		int pos = url.indexOf(StringPool.QUESTION);

		if (pos == -1) {
			return url;
		}

		StringMaker sm = new StringMaker();

		sm.append(url.substring(0, pos + 1));

		StringTokenizer st = new StringTokenizer(
			url.substring(pos + 1, url.length()), StringPool.AMPERSAND);

		while (st.hasMoreTokens()) {
			String token = st.nextToken();

			if (Validator.isNotNull(token)) {
				String[] kvp = StringUtil.split(token, StringPool.EQUAL);

				String key = kvp[0];

				String value = StringPool.BLANK;

				if (kvp.length > 1) {
					value = kvp[1];
				}

				if (!key.equals(name)) {
					sm.append(key);
					sm.append(StringPool.EQUAL);
					sm.append(value);
					sm.append(StringPool.AMPERSAND);
				}
			}
		}

		url = StringUtil.replace(
			sm.toString(), StringPool.AMPERSAND + StringPool.AMPERSAND,
			StringPool.AMPERSAND);

		return url;
	}

	public static String removeProtocol(String url) {
		if (url.startsWith(HTTP_WITH_SLASH)) {
			return url.substring(HTTP_WITH_SLASH.length() , url.length());
		}
		else if (url.startsWith(HTTPS_WITH_SLASH)) {
			return url.substring(HTTPS_WITH_SLASH.length() , url.length());
		}
		else {
			return url;
		}
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

	public static void submit(
			String location, Cookie[] cookies, Map parts, boolean post)
		throws IOException {

		URLtoByteArray(location, cookies, parts, post);
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

		return URLtoByteArray(location, cookies, null, post);
	}

	public static byte[] URLtoByteArray(
			String location, Cookie[] cookies, Map parts, boolean post)
		throws IOException {

		byte[] byteArray = null;

		HttpMethod method = null;

		try {
			if (location == null) {
				return byteArray;
			}
			else if (!location.startsWith(HTTP_WITH_SLASH) &&
					 !location.startsWith(HTTPS_WITH_SLASH)) {

				location = HTTP_WITH_SLASH + location;
			}

			HostConfiguration hostConfig = getHostConfig(location);

			HttpClient client = getClient(hostConfig);

			if (post) {
				method = new PostMethod(location);

				if ((parts != null) && (parts.size() > 0)) {
					List nvpList = new ArrayList();

					Iterator itr = parts.entrySet().iterator();

					while (itr.hasNext()) {
						Map.Entry entry = (Map.Entry)itr.next();

						String key = (String)entry.getKey();
						String value = (String)entry.getValue();

						if (value != null) {
							nvpList.add(new NameValuePair(key, value));
						}
					}

					NameValuePair[] nvpArray = (NameValuePair[])nvpList.toArray(
						new NameValuePair[nvpList.size()]);

					PostMethod postMethod = (PostMethod)method;

					postMethod.setRequestBody(nvpArray);
				}
			}
			else {
				method = new GetMethod(location);
			}

			method.addRequestHeader(
				"Content-Type", "application/x-www-form-urlencoded");

			method.addRequestHeader(
				"User-agent",
				"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)");

			//method.setFollowRedirects(true);

			HttpState state = new HttpState();

			if ((cookies != null) && (cookies.length > 0)) {
				state.addCookies(cookies);

				method.getParams().setCookiePolicy(
					CookiePolicy.BROWSER_COMPATIBILITY);
			}

			proxifyState(state, hostConfig);

			client.executeMethod(hostConfig, method, state);

			Header locationHeader = method.getResponseHeader("location");

			if (locationHeader != null) {
				return URLtoByteArray(locationHeader.getValue(), cookies, post);
			}

			InputStream is = method.getResponseBodyAsStream();

			if (is != null) {
				ByteArrayMaker bam = new ByteArrayMaker();
				byte[] bytes = new byte[512];

				for (int i = is.read(bytes, 0, 512); i != -1;
						i = is.read(bytes, 0, 512)) {

					bam.write(bytes, 0, i);
				}

				byteArray = bam.toByteArray();

				is.close();
				bam.close();
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
				_log.error(e, e);
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

	public static String URLtoString(
			String location, Cookie[] cookies, boolean post)
		throws IOException {

		return new String(URLtoByteArray(location, cookies, post));
	}

	public static String URLtoString(
			String location, Cookie[] cookies, Map parts, boolean post)
		throws IOException {

		return new String(URLtoByteArray(location, cookies, parts, post));
	}

	/**
	 * This method only uses the default Commons HttpClient implementation when
	 * the URL object represents a HTTP resource. The URL object could also
	 * represent a file or some JNDI resource. In that case, the default Java
	 * implementation is used.
	 *
	 * @param		url URL object
	 * @return		A string representation of the resource referenced by the
	 *				URL object
	 * @throws		IOException
	 */
	public static String URLtoString(URL url) throws IOException {
		String xml = null;

		if (url != null) {
			String protocol = url.getProtocol().toLowerCase();

			if (protocol.startsWith(HTTP) || protocol.startsWith(HTTPS)) {
				return URLtoString(url.toString());
			}

			URLConnection con = url.openConnection();

			InputStream is = con.getInputStream();

			ByteArrayMaker bam = new ByteArrayMaker();
			byte[] bytes = new byte[512];

			for (int i = is.read(bytes, 0, 512); i != -1;
					i = is.read(bytes, 0, 512)) {

				bam.write(bytes, 0, i);
			}

			xml = new String(bam.toByteArray());

			is.close();
			bam.close();
		}

		return xml;
	}

	private Http() {

		// Mimic behavior found in
		// http://java.sun.com/j2se/1.5.0/docs/guide/net/properties.html

		if (Validator.isNotNull(NON_PROXY_HOSTS)) {
			String nonProxyHostsRegEx = NON_PROXY_HOSTS;

			nonProxyHostsRegEx = nonProxyHostsRegEx.replaceAll(
				"\\.", "\\\\.");
			nonProxyHostsRegEx = nonProxyHostsRegEx.replaceAll(
				"\\*", ".*?");
			nonProxyHostsRegEx = nonProxyHostsRegEx.replaceAll(
				"\\|", ")|(");

			nonProxyHostsRegEx = "(" + nonProxyHostsRegEx + ")";

			_nonProxyHostsPattern = Pattern.compile(nonProxyHostsRegEx);
		}

		MultiThreadedHttpConnectionManager connectionManager =
			new MultiThreadedHttpConnectionManager();

		HttpConnectionParams params = connectionManager.getParams();

		params.setParameter(
			"maxConnectionsPerHost", new Integer(MAX_CONNECTIONS_PER_HOST));
		params.setParameter(
			"maxTotalConnections", new Integer(MAX_TOTAL_CONNECTIONS));
		params.setConnectionTimeout(TIMEOUT);
		params.setSoTimeout(TIMEOUT);

		_client.setHttpConnectionManager(connectionManager);
		_proxyClient.setHttpConnectionManager(connectionManager);

		if (hasProxyConfig() && Validator.isNotNull(PROXY_USERNAME)) {
			if (PROXY_AUTH_TYPE.equals("username-password")) {
				_proxyCredentials = new UsernamePasswordCredentials(
					PROXY_USERNAME, PROXY_PASSWORD);
			}
			else if (PROXY_AUTH_TYPE.equals("ntlm")) {
				_proxyCredentials = new NTCredentials(
					PROXY_USERNAME, PROXY_PASSWORD, PROXY_NTLM_HOST,
					PROXY_NTLM_DOMAIN);

				List authPrefs = new ArrayList();

				authPrefs.add(AuthPolicy.NTLM);
				authPrefs.add(AuthPolicy.BASIC);
				authPrefs.add(AuthPolicy.DIGEST);

				_proxyClient.getParams().setParameter(
					AuthPolicy.AUTH_SCHEME_PRIORITY, authPrefs);
			}
		}
	}

	private HttpClient _getClient(HostConfiguration hostConfig)
		throws IOException {

		if (isProxyHost(hostConfig.getHost())) {
			return _proxyClient;
		}
		else {
			return _client;
		}
	}

	private boolean _isNonProxyHost(String host) {
		if (_nonProxyHostsPattern == null ||
			_nonProxyHostsPattern.matcher(host).matches()) {

			return true;
		}
		else {
			return false;
		}
	}

	private static Log _log = LogFactory.getLog(Http.class);

	private static Http _instance = new Http();

	private HttpClient _client = new HttpClient();
	private HttpClient _proxyClient = new HttpClient();
	private Credentials _proxyCredentials;
	private Pattern _nonProxyHostsPattern;

}