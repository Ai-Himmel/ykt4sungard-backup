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

package com.liferay.portlet.wsrp;

import com.liferay.util.GetterUtil;
import com.liferay.util.axis.SimpleHTTPSender;
import com.liferay.util.lang.FastStringBuffer;

import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletMode;
import javax.portlet.PortletURL;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import org.apache.wsrp4j.consumer.URLGenerator;
import org.apache.wsrp4j.producer.util.Base64;
import org.apache.wsrp4j.producer.util.ObjectSerializer;
import org.apache.wsrp4j.util.Constants;
import org.apache.wsrp4j.util.Modes;
import org.apache.wsrp4j.util.WindowStates;

/**
 * <a href="URLGeneratorImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.12 $
 *
 */
public class URLGeneratorImpl implements URLGenerator {

	public static String getResourceProxyURL(Map params) {
		FastStringBuffer url = new FastStringBuffer();

		url.append("/wsrp/resource_proxy/get");

		if (params != null) {

			String paramValue = GetterUtil.getString((String) params
					.get(Constants.URL));

			url.append(Constants.PARAMS_START);
			url.append("url");
			url.append(Constants.EQUALS);
			try {
				paramValue = Base64.encode(ObjectSerializer.serialize(paramValue));
				url.append(paramValue);
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}

		String cookie = SimpleHTTPSender.getCurrentCookie();
		try {
			cookie = Base64.encode(ObjectSerializer.serialize(cookie));
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		url.append(Constants.NEXT_PARAM);
		url.append("cookie");
		url.append(Constants.EQUALS);
		url.append(cookie);

		return url.toString();

	}

	public static URLGenerator getInstance(RenderResponse response,
			PortletConfig config) {
		if (response == null) {
			throw new IllegalArgumentException("response must not be null");
		}
		if (config == null) {
			throw new IllegalArgumentException("config must not be null");
		}

		if (_instance == null) {

			_instance = new URLGeneratorImpl(response);

		}
		else {
			_instance.setRenderResponse(response);
		}

		return _instance;
	}

	private URLGeneratorImpl(RenderResponse response) {
		this._renderResponse = response;
	}

	public void setRenderResponse(RenderResponse response) {
		if (response != null) {
			this._renderResponse = response;
		}
	}

	public void setConsumerParameters(Map consumerParameters) {
		if (consumerParameters != null) {
			this._consumerParameters = consumerParameters;
		}
	}

	public String getBlockingActionURL(Map params) {
		PortletURL url = _renderResponse.createActionURL();

		if (params != null) {

			Iterator iter = params.keySet().iterator();

			String paramName = "";
			String paramValue = "";

			while (iter.hasNext()) {
				paramName = (String) iter.next();

				if (paramName.equalsIgnoreCase(Constants.WINDOW_STATE)) {
					if ((paramValue = (String) params.get(paramName)) != null) {

						setWindowState(url, paramValue);

					}
				}
				else if (paramName.equalsIgnoreCase(Constants.PORTLET_MODE)) {
					if ((paramValue = (String) params.get(paramName)) != null) {

						setPortletMode(url, paramValue);

					}
				}
				else {
					if ((paramValue = (String) params.get(paramName)) != null) {

						url.setParameter(paramName, paramValue);

					}
				}
			}
		}

		if (_consumerParameters != null) {

			Iterator iter2 = _consumerParameters.keySet().iterator();
			String name = null;
			String value = null;

			while (iter2.hasNext()) {

				if ((value = (String) _consumerParameters.get(name)) != null) {
					url.setParameter(name, value);
				}
			}
		}

		url.setParameter(WSRPProxyPortlet.REMOTE_INVOCATION, "true");

		return url.toString();

	}

	public String getRenderURL(Map params) {

		PortletURL url = _renderResponse.createRenderURL();

		if (params != null) {

			Iterator iter = params.keySet().iterator();

			String paramName = "";
			String paramValue = "";

			while (iter.hasNext()) {
				paramName = (String) iter.next();

				if (paramName.equalsIgnoreCase(Constants.WINDOW_STATE)) {
					if ((paramValue = (String) params.get(paramName)) != null) {

						setWindowState(url, paramValue);

					}
				}
				else if (paramName.equalsIgnoreCase(Constants.PORTLET_MODE)) {
					if ((paramValue = (String) params.get(paramName)) != null) {

						setPortletMode(url, paramValue);

					}
				}
				else {
					if (!paramName.equalsIgnoreCase(Constants.URL_TYPE)
							&& (paramValue = (String) params.get(paramName)) != null) {

						url.setParameter(paramName, paramValue);

					}
				}
			}
		}

		if (_consumerParameters != null) {

			Iterator iter2 = _consumerParameters.keySet().iterator();
			String name = null;
			String value = null;

			while (iter2.hasNext()) {

				if ((value = (String) _consumerParameters.get(name)) != null) {
					url.setParameter(name, value);
				}
			}
		}

		url.setParameter(WSRPProxyPortlet.REMOTE_INVOCATION, "true");

		return url.toString();

	}

	public String getResourceURL(Map params) {
		return getResourceProxyURL(params);
	}

	public String getNamespacedToken(String token) {
		return _renderResponse.getNamespace();
	}

	/**
	 * Maps wsrp-windowStates to pluto-windowStates.
	 */
	private void setWindowState(PortletURL url, String windowState) {

		try {
			if (windowState.equalsIgnoreCase(WindowStates._maximized)) {

				url.setWindowState(WindowState.MAXIMIZED);

			}
			else if (windowState.equalsIgnoreCase(WindowStates._minimized)) {

				url.setWindowState(WindowState.MINIMIZED);

			}
			else if (windowState.equalsIgnoreCase(WindowStates._normal)) {

				url.setWindowState(WindowState.NORMAL);

			}
			else if (windowState.equalsIgnoreCase(WindowStates._solo)) {

				url.setWindowState(WindowState.MAXIMIZED);

			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

	}

	/**
	 * Maps wsrp-portletModes to pluto-portletModes.
	 */
	private void setPortletMode(PortletURL url, String mode) {

		try {
			if (mode.equalsIgnoreCase(Modes._edit)) {

				url.setPortletMode(PortletMode.EDIT);

			}
			else if (mode.equalsIgnoreCase(Modes._view)) {

				url.setPortletMode(PortletMode.VIEW);

			}
			else if (mode.equalsIgnoreCase(Modes._help)) {

				url.setPortletMode(PortletMode.HELP);

			}
			else if (mode.equalsIgnoreCase(Modes._preview)) {

				url.setPortletMode(PortletMode.VIEW);

			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

	}

	private static URLGeneratorImpl _instance = null;

	private RenderResponse _renderResponse = null;

	private Map _consumerParameters = null;

}