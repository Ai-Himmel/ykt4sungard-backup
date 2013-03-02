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

package com.liferay.util.portlet;

import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.xml.DocUtil;
import com.liferay.util.xml.XMLFormatter;

import java.io.IOException;

import java.util.Collection;
import java.util.Enumeration;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.PortletSession;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowStateException;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="PortletRequestUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class PortletRequestUtil {

	public static String toXML(PortletRequest req, PortletResponse res) {
		String xml = null;

		Document doc = DocumentHelper.createDocument();

		Element reqEl = doc.addElement("request");

		DocUtil.add(reqEl, "container-type", "portlet");
		DocUtil.add(reqEl, "container-namespace", req.getContextPath());
		DocUtil.add(reqEl, "content-type", req.getResponseContentType());
		DocUtil.add(reqEl, "server-name", req.getServerName());
		DocUtil.add(reqEl, "server-port", req.getServerPort());
		DocUtil.add(reqEl, "secure", req.isSecure());
		DocUtil.add(reqEl, "auth-type", req.getAuthType());
		DocUtil.add(reqEl, "remote-user", req.getRemoteUser());
		DocUtil.add(reqEl, "context-path", req.getContextPath());
		DocUtil.add(reqEl, "locale", req.getLocale());
		DocUtil.add(reqEl, "portlet-mode", req.getPortletMode());
		DocUtil.add(reqEl, "portlet-session-id", req.getRequestedSessionId());
		DocUtil.add(reqEl, "scheme", req.getScheme());
		DocUtil.add(reqEl, "window-state", req.getWindowState());

		if (req instanceof RenderRequest) {
			DocUtil.add(reqEl, "action", Boolean.FALSE);
		}
		else if (req instanceof ActionRequest) {
			DocUtil.add(reqEl, "action", Boolean.TRUE);
		}

		if (res instanceof RenderResponse) {
			_renderResponseToXML((RenderResponse)res, reqEl);
		}

		Element parametersEl = reqEl.addElement("parameters");

		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			Element parameterEl = parametersEl.addElement("parameter");

			DocUtil.add(parameterEl, "name", name);

			String[] values = req.getParameterValues(name);

			for (int i = 0; i < values.length; i++) {
				DocUtil.add(parameterEl, "value", values[i]);
			}
		}

		Element attributesEl = reqEl.addElement("attributes");

		enu = req.getAttributeNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (!_isValidAttributeName(name)) {
				continue;
			}

			Object value = req.getAttribute(name);

			if (!_isValidAttributeValue(value)) {
				continue;
			}

			Element attributeEl = attributesEl.addElement("attribute");

			DocUtil.add(attributeEl, "name", name);
			DocUtil.add(attributeEl, "value", String.valueOf(value));
		}

		Element portletSessionEl = reqEl.addElement("portlet-session");

		attributesEl = portletSessionEl.addElement("portlet-attributes");

		PortletSession ses = req.getPortletSession();

		enu = ses.getAttributeNames(PortletSession.PORTLET_SCOPE);

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (!_isValidAttributeName(name)) {
				continue;
			}

			Object value = ses.getAttribute(name, PortletSession.PORTLET_SCOPE);

			if (!_isValidAttributeValue(value)) {
				continue;
			}

			Element attributeEl = attributesEl.addElement("attribute");

			DocUtil.add(attributeEl, "name", name);
			DocUtil.add(attributeEl, "value", String.valueOf(value));
		}

		attributesEl = portletSessionEl.addElement("application-attributes");

		enu = ses.getAttributeNames(PortletSession.APPLICATION_SCOPE);

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (!_isValidAttributeName(name)) {
				continue;
			}

			Object value = ses.getAttribute(
				name, PortletSession.APPLICATION_SCOPE);

			if (!_isValidAttributeValue(value)) {
				continue;
			}

			Element attributeEl = attributesEl.addElement("attribute");

			DocUtil.add(attributeEl, "name", name);
			DocUtil.add(attributeEl, "value", String.valueOf(value));
		}

		try {
			xml = XMLFormatter.toString(doc);
		}
		catch (IOException ioe) {
		}

		return xml;
	}

	private static void _renderResponseToXML(
		RenderResponse res, Element reqEl) {

		DocUtil.add(reqEl, "portlet-namespace", res.getNamespace());

		PortletURL url = res.createRenderURL();

		DocUtil.add(reqEl, "render-url", url);

		try {
			url.setWindowState(LiferayWindowState.EXCLUSIVE);

			DocUtil.add(reqEl, "render-url-exclusive", url);
		}
		catch (WindowStateException wse) {
		}

		try {
			url.setWindowState(LiferayWindowState.MAXIMIZED);

			DocUtil.add(reqEl, "render-url-maximized", url);
		}
		catch (WindowStateException wse) {
		}

		try {
			url.setWindowState(LiferayWindowState.MINIMIZED);

			DocUtil.add(reqEl, "render-url-minimized", url);
		}
		catch (WindowStateException wse) {
		}

		try {
			url.setWindowState(LiferayWindowState.NORMAL);

			DocUtil.add(reqEl, "render-url-normal", url);
		}
		catch (WindowStateException wse) {
		}

		try {
			url.setWindowState(LiferayWindowState.POP_UP);

			DocUtil.add(reqEl, "render-url-pop-up", url);
		}
		catch (WindowStateException wse) {
		}
	}

	private static boolean _isValidAttributeName(String name) {
		if (name.equalsIgnoreCase("j_password") ||
			name.equalsIgnoreCase("LAYOUT_CONTENT") ||
			name.equalsIgnoreCase("LAYOUTS") ||
			name.equalsIgnoreCase("PORTLET_RENDER_PARAMETERS") ||
			name.equalsIgnoreCase("USER_PASSWORD") ||
			name.startsWith("javax.") ||
			name.startsWith("liferay-ui:")) {

			return false;
		}
		else {
			return true;
		}
	}

	private static boolean _isValidAttributeValue(Object obj) {
		if (obj == null) {
			return false;
		}
		else if (obj instanceof Collection) {
			Collection col = (Collection)obj;

			if (col.size() == 0) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (obj instanceof Map) {
			Map map = (Map)obj;

			if (map.size() == 0) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			String objString = String.valueOf(obj);

			if (Validator.isNull(objString)) {
				return false;
			}

			String hashCode =
				StringPool.AT + Integer.toHexString(obj.hashCode());

			if (objString.endsWith(hashCode)) {
				return false;
			}

			return true;
		}
	}

}