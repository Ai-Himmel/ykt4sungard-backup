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

package com.liferay.portlet;

import com.liferay.portal.SystemException;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.BrowserSniffer;
import com.liferay.util.Encryptor;
import com.liferay.util.EncryptorException;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import java.security.Key;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.portlet.PortletContext;
import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.PortletRequest;
import javax.portlet.PortletSecurityException;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;
import javax.portlet.WindowStateException;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletURLImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.53 $
 *
 */
public class PortletURLImpl implements PortletURL {

	public PortletURLImpl(ActionRequestImpl req, String portletName,
						  String layoutId, boolean action) {

		this(req.getHttpServletRequest(), portletName, layoutId, action);

		_portletReq = req;
	}

	public PortletURLImpl(RenderRequestImpl req, String portletName,
						  String layoutId, boolean action) {

		this(req.getHttpServletRequest(), portletName, layoutId, action);

		_portletReq = req;
	}

	public PortletURLImpl(HttpServletRequest req, String portletName,
						  String layoutId, boolean action) {

		_req = req;
		_portletName = portletName;
		_layoutId = layoutId;
		_secure = req.isSecure();
		_action = action;
		_params = new LinkedHashMap();
	}

	public WindowState getWindowState() {
		return _windowState;
	}

	public void setWindowState(WindowState windowState)
		throws WindowStateException {

		if (_portletReq != null) {
			if (!_portletReq.isWindowStateAllowed(windowState)) {
				throw new WindowStateException(
					windowState.toString(), windowState);
			}
		}

		_windowState = windowState;
	}

	public void setWindowState(String windowState)
		throws WindowStateException {

		setWindowState(new WindowState(windowState));
	}

	public PortletMode getPortletMode() {
		return _portletMode;
	}

	public void setPortletMode(PortletMode portletMode)
		throws PortletModeException {

		if (_portletReq != null) {
			if (!getPortlet().hasPortletMode(
					_portletReq.getResponseContentType(), portletMode)) {

				throw new PortletModeException(
					portletMode.toString(), portletMode);
			}
		}

		_portletMode = portletMode;
	}

	public void setPortletMode(String portletMode)
		throws PortletModeException {

		setPortletMode(new PortletMode(portletMode));
	}

	public void setParameter(String name, String value) {
		setParameter(name, value, true);
	}

	public void setParameter(String name, String value, boolean append) {
		if ((name == null) || (value == null)) {
			throw new IllegalArgumentException();
		}

		setParameter(name, new String[] {value}, append);
	}

	public void setParameter(String name, String[] values) {
		setParameter(name, values, true);
	}

	public void setParameter(String name, String[] values, boolean append) {
		if ((name == null) || (values == null)) {
			throw new IllegalArgumentException();
		}

		for (int i = 0; i < values.length; i++) {
			if (values[i] == null) {
				throw new IllegalArgumentException();
			}
		}

		if (append && _params.containsKey(name)) {
			String[] oldValues = (String[])_params.get(name);
			String[] newValues = new String[oldValues.length + values.length];

			System.arraycopy(oldValues, 0, newValues, 0, oldValues.length);

			System.arraycopy(
				values, 0, newValues, oldValues.length, values.length);

			_params.put(name, newValues);
		}
		else {
			_params.put(name, values);
		}
	}

	public void setParameters(Map params) {
		if (params == null) {
			throw new IllegalArgumentException();
		}
		else {
			Map newParams = new LinkedHashMap();

			Iterator itr = params.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				Object key = entry.getKey();
				Object value = entry.getValue();

				if (key == null) {
					throw new IllegalArgumentException();
				}
				else if (value == null) {
					throw new IllegalArgumentException();
				}

				if (value instanceof String[]) {
					newParams.put(key, value);
				}
				else {
					throw new IllegalArgumentException();
				}
			}

			_params = newParams;
		}
	}

	public void setSecure(boolean secure) throws PortletSecurityException {
		_secure = secure;
	}

	public void setAction(boolean action) {
		_action = action;
	}

	public void setAnchor(boolean anchor) {
		_anchor = anchor;
	}

	public void setEncrypt(boolean encrypt) {
		_encrypt = encrypt;
	}

	public String toString() {
		FastStringBuffer sb = new FastStringBuffer();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)_req.getAttribute(WebKeys.THEME_DISPLAY);

		PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

		sb.append(PortalUtil.getPortalURL(_req, _secure));

		String layoutFriendlyURL = null;

		try {
			Layout layout = getLayout();

			if (layout != null) {
				layoutFriendlyURL = PortalUtil.getLayoutFriendlyURL(
					layout, themeDisplay);
			}
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}

		Key key = null;
		try {
			if (_encrypt) {
				key = PortalUtil.getCompany(_req).getKeyObj();
			}
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}

		if (Validator.isNull(layoutFriendlyURL)) {
			String mainPath = null;
			if (_portletReq != null) {
				PortletContext portletCtx =
					_portletReq.getPortletSession().getPortletContext();

				mainPath = (String)portletCtx.getAttribute(WebKeys.MAIN_PATH);
			}
			else {
				mainPath = (String)_req.getAttribute(WebKeys.MAIN_PATH);
			}

			sb.append(mainPath);
			sb.append("/portal/layout?");

			sb.append("p_l_id");
			sb.append(StringPool.EQUAL);
			sb.append(_processValue(key, _layoutId));
			sb.append(StringPool.AMPERSAND);
		}
		else {
			sb.append(layoutFriendlyURL);
			sb.append(StringPool.QUESTION);
		}

		sb.append("p_p_id");
		sb.append(StringPool.EQUAL);
		sb.append(_processValue(key, _portletName));
		sb.append(StringPool.AMPERSAND);

		sb.append("p_p_action");
		sb.append(StringPool.EQUAL);
		sb.append(_action ? _processValue(key, "1") : _processValue(key, "0"));
		sb.append(StringPool.AMPERSAND);

		if (_windowState != null) {
			sb.append("p_p_state");
			sb.append(StringPool.EQUAL);
			sb.append(_processValue(key, _windowState.toString()));
			sb.append(StringPool.AMPERSAND);
		}

		if (_portletMode != null) {
			sb.append("p_p_mode");
			sb.append(StringPool.EQUAL);
			sb.append(_processValue(key, _portletMode.toString()));
			sb.append(StringPool.AMPERSAND);
		}

		sb.append("p_p_width");
		sb.append(StringPool.EQUAL);
		sb.append(_processValue(key, portletDisplay.getWidth()));
		sb.append(StringPool.AMPERSAND);

		sb.append("p_p_col_order");
		sb.append(StringPool.EQUAL);
		sb.append(_processValue(key, portletDisplay.getCurColumnOrder()));
		sb.append(StringPool.AMPERSAND);

		sb.append("p_p_col_pos");
		sb.append(StringPool.EQUAL);
		sb.append(_processValue(key, portletDisplay.getCurColumnPos()));
		sb.append(StringPool.AMPERSAND);

		sb.append("p_p_col_count");
		sb.append(StringPool.EQUAL);
		sb.append(_processValue(key, portletDisplay.getCurColumnCount()));
		sb.append(StringPool.AMPERSAND);

		Iterator itr = _params.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name =
				PortalUtil.getPortletNamespace(_portletName) +
				(String)entry.getKey();
			String[] values = (String[])entry.getValue();

			for (int i = 0; i < values.length; i++) {
				sb.append(name);
				sb.append(StringPool.EQUAL);
				sb.append(_processValue(key, values[i]));

				if ((i + 1 < values.length) || itr.hasNext()) {
					sb.append(StringPool.AMPERSAND);
				}
			}
		}

		if (_encrypt) {
			sb.append(StringPool.AMPERSAND + WebKeys.ENCRYPT + "=1");
		}

		if (!BrowserSniffer.is_ns_4(_req)) {
			if (_anchor && (_windowState != null) &&
				(!_windowState.equals(WindowState.MAXIMIZED))) {

				if (sb.lastIndexOf(StringPool.AMPERSAND) != (sb.length() - 1)) {
					sb.append(StringPool.AMPERSAND);
				}

				sb.append("#p_").append(_portletName);
			}
		}

		return sb.toString();
	}

	protected String getLayoutId() {
		return _layoutId;
	}

	protected Layout getLayout() {
		if (_layout == null) {
			try {
				LayoutPK pk = null;

				if (Layout.isGroup(_layoutId)) {
					String groupId = Layout.getGroupId(_layoutId);

					pk = new LayoutPK(_layoutId, Layout.GROUP + groupId);
				}
				else {
					pk = new LayoutPK(_layoutId, _req.getRemoteUser());
				}

				_layout = LayoutLocalServiceUtil.getLayout(pk);
			}
			catch (Exception e) {
				_log.warn("Layout cannot be found for " + _layoutId);
			}
		}

		return _layout;
	}

	protected Map getParams() {
		return _params;
	}

	protected String getPortletName() {
		return _portletName;
	}

	protected Portlet getPortlet() {
		if (_portlet == null) {
			try {
				_portlet = PortletServiceUtil.getPortletById(
					PortalUtil.getCompanyId(_req), _portletName);
			}
			catch (SystemException se) {
				_log.error(se.getMessage());
			}
		}

		return _portlet;
	}

	protected PortletRequest getPortletReq() {
		return _portletReq;
	}

	protected HttpServletRequest getReq() {
		return _req;
	}

	protected boolean isAction() {
		return _action;
	}

	protected boolean isAnchor() {
		return _anchor;
	}

	protected boolean isEncrypt() {
		return _encrypt;
	}

	protected boolean isSecure() {
		return _secure;
	}

	private String _processValue(Key key, int value) {
		return _processValue(key, Integer.toString(value));
	}

	private String _processValue(Key key, String value) {
		if (key == null) {
			return Http.encodeURL(value);
		}
		else {
			try {
				return Http.encodeURL(Encryptor.encrypt(key, value));
			}
			catch (EncryptorException ee) {
				return value;
			}
		}
	}

	private static final Log _log = LogFactory.getLog(PortletURLImpl.class);

	private HttpServletRequest _req;
	private PortletRequest _portletReq;
	private String _portletName;
	private Portlet _portlet;
	private String _layoutId;
	private Layout _layout;
	private boolean _action;
	private WindowState _windowState;
	private PortletMode _portletMode;
	private Map _params;
	private boolean _secure;
	private boolean _anchor = true;
	private boolean _encrypt = false;

}