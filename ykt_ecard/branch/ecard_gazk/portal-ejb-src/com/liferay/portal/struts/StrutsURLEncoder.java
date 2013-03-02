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

package com.liferay.portal.struts;

import com.liferay.portlet.PortletURLImpl;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.URLEncoder;

import java.util.HashMap;

import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.WindowState;
import javax.portlet.WindowStateException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="StrutsURLEncoder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class StrutsURLEncoder implements URLEncoder {

	public static void setParameters(
		PortletURLImpl portletURL, String queryString) {

		String[] params = StringUtil.split(queryString, "&");

		for (int i = 0; i < params.length; i++) {
			int pos = params[i].indexOf("=");

			if (pos != -1) {
				String param = params[i].substring(0, pos);
				String value = params[i].substring(pos + 1, params[i].length());

				if (param.equals("windowState")) {
					try {
						portletURL.setWindowState(new WindowState(value));
					}
					catch (WindowStateException wse) {
						wse.printStackTrace();
					}
				}
				else if (param.equals("portletMode")) {
					try {
						portletURL.setPortletMode(new PortletMode(value));
					}
					catch (PortletModeException pme) {
						pme.printStackTrace();
					}
				}
				else if (param.equals("actionURL")) {
					portletURL.setAction(GetterUtil.getBoolean(value));
				}
				else {
					portletURL.setParameter(param, Http.decodeURL(value));
				}
			}
		}
	}

	public StrutsURLEncoder(String mainPath, String servletMapping,
							PortletURLImpl portletURL) {

		_mainPath = mainPath;
		_setServletMapping(servletMapping);
		_portletURL = portletURL;
		_windowState = portletURL.getWindowState();
		_portletMode = portletURL.getPortletMode();
	}

	public String encodeURL(String path) {
		_log.debug("Encode " + path);

		// Struts uses &amp; instead of & to delimit parameter key value pairs
		// when you set the "name" attribute for html:link.

		path = StringUtil.replace(path, "&amp;", "&");

		// Reset portlet URL settings so it can be reused

		try {
			_portletURL.setWindowState(_windowState);
		}
		catch (WindowStateException wse) {
		}

		try {
			_portletURL.setPortletMode(_portletMode);
		}
		catch (PortletModeException pme) {
		}

		_portletURL.setParameters(new HashMap());
		_portletURL.setAction(false);

		// Separate the Struts action from the query string

		String strutsAction = path;
		String queryString = StringPool.BLANK;

		int pos = strutsAction.indexOf("?");
		if (pos != -1) {
			strutsAction = path.substring(0, pos);
			queryString = path.substring(pos + 1, path.length());
		}

		// Set the Struts action

		if (Validator.isNotNull(_mainPath)) {
			strutsAction = strutsAction.substring(
				_mainPath.length(), strutsAction.length());
		}

		// Workaround for bug in Struts where it adds the servlet mapping
		// path to the action path

		if ((_servletMapping != null) && (_servletMapping.length() > 0) &&
			(strutsAction.startsWith(_servletMapping))) {

			strutsAction = strutsAction.substring(
				_servletMapping.length() - 1, strutsAction.length());
		}

		_portletURL.setParameter("struts_action", strutsAction);

		// Set the query string

		setParameters(_portletURL, queryString);

		// Return the portlet URL

		String portletURLToString = _portletURL.toString();

		_log.debug("Encoded portlet URL " + portletURLToString);

		return portletURLToString;
	}

	private void _setServletMapping(String servletMapping) {
		if (servletMapping != null) {

			// See org.apache.struts.util.RequestUtils.getActionMappingURL

			if (servletMapping.endsWith("/*")) {
				_servletMapping = servletMapping.substring(
					0, servletMapping.length() - 1);
			}
		}
	}

	private static final Log _log = LogFactory.getLog(StrutsURLEncoder.class);

	private String _mainPath;
	private String _servletMapping;
	private PortletURLImpl _portletURL;
	private WindowState _windowState;
	private PortletMode _portletMode;

}