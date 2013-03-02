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

package com.liferay.portlet;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.portlet.LiferayPortletURL;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.Encryptor;
import com.liferay.util.EncryptorException;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;

import java.io.Serializable;

import java.security.Key;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.PortletRequest;
import javax.portlet.PortletSecurityException;
import javax.portlet.WindowState;
import javax.portlet.WindowStateException;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletURLImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class PortletURLImpl implements LiferayPortletURL, Serializable {

	public static final boolean APPEND_PARAMETERS = GetterUtil.getBoolean(
		PropsUtil.get(PropsUtil.PORTLET_URL_APPEND_PARAMETERS));

	public PortletURLImpl(
		ActionRequestImpl req, String portletId, long plid, boolean action) {

		this(req.getHttpServletRequest(), portletId, plid, action);

		_portletReq = req;
	}

	public PortletURLImpl(
		RenderRequestImpl req, String portletId, long plid, boolean action) {

		this(req.getHttpServletRequest(), portletId, plid, action);

		_portletReq = req;
	}

	public PortletURLImpl(
		HttpServletRequest req, String portletId, long plid, boolean action) {

		_req = req;
		_portletId = portletId;
		_plid = plid;
		_secure = req.isSecure();
		_action = action;
		_params = new LinkedHashMap();
		_parametersIncludedInPath = new LinkedHashSet();
	}

	public HttpServletRequest getReq() {
		return _req;
	}

	public PortletRequest getPortletReq() {
		return _portletReq;
	}

	public String getPortletId() {
		return _portletId;
	}

	public void setPortletId(String portletId) {
		_portletId = portletId;

		// Clear cache

		_toString = null;
	}

	/**
	 * @deprecated Use <code>getPortletId</code>.
	 */
	public String getPortletName() {
		return getPortletId();
	}

	/**
	 * @deprecated Use <code>setPortletId</code>.
	 */
	public void setPortletName(String portletName) {
		setPortletId(portletName);
	}

	public Portlet getPortlet() {
		if (_portlet == null) {
			try {
				_portlet = PortletLocalServiceUtil.getPortletById(
					PortalUtil.getCompanyId(_req), _portletId);
			}
			catch (SystemException se) {
				_log.error(se.getMessage());
			}
		}

		return _portlet;
	}

	public String getPortletFriendlyURLPath() {
		String portletFriendlyURLPath = null;

		Portlet portlet = getPortlet();

		if (portlet != null) {
			FriendlyURLMapper mapper = portlet.getFriendlyURLMapperInstance();

			if (mapper != null) {
				portletFriendlyURLPath = mapper.buildPath(this);

				if (_log.isDebugEnabled()) {
					_log.debug(
						"Portlet friendly URL path " + portletFriendlyURLPath);
				}
			}
		}

		return portletFriendlyURLPath;
	}

	public String getNamespace() {
		if (_namespace == null) {
			_namespace = PortalUtil.getPortletNamespace(_portletId);
		}

		return _namespace;
	}

	public long getPlid() {
		return _plid;
	}

	public Layout getLayout() {
		if (_layout == null) {
			try {
				if (_plid > 0) {
					_layout = LayoutLocalServiceUtil.getLayout(_plid);
				}
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn("Layout cannot be found for " + _plid);
				}
			}
		}

		return _layout;
	}

	public String getLayoutFriendlyURL() {
		return _layoutFriendlyURL;
	}

	public boolean isAction() {
		return _action;
	}

	public void setAction(boolean action) {
		_action = action;

		// Clear cache

		_toString = null;
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

		if (LiferayWindowState.isWindowStatePreserved(
				getWindowState(), windowState)) {

			_windowState = windowState;
		}

		// Clear cache

		_toString = null;
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

		// Clear cache

		_toString = null;
	}

	public void setPortletMode(String portletMode)
		throws PortletModeException {

		setPortletMode(new PortletMode(portletMode));
	}

	public String getParameter(String name) {
		String[] values = (String[])_params.get(name);

		if ((values != null) && (values.length > 0)) {
			return values[0];
		}
		else {
			return null;
		}
	}

	public void setParameter(String name, String value) {
		setParameter(name, value, APPEND_PARAMETERS);
	}

	public void setParameter(String name, String value, boolean append) {
		if ((name == null) || (value == null)) {
			throw new IllegalArgumentException();
		}

		setParameter(name, new String[] {value}, append);
	}

	public void setParameter(String name, String[] values) {
		setParameter(name, values, APPEND_PARAMETERS);
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

			String[] newValues = ArrayUtil.append(oldValues, values);

			_params.put(name, newValues);
		}
		else {
			_params.put(name, values);
		}

		// Clear cache

		_toString = null;
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

		// Clear cache

		_toString = null;
	}

	public Map getParameterMap() {
		return _params;
	}

	public Set getParametersIncludedInPath() {
		return _parametersIncludedInPath;
	}

	public void addParameterIncludedInPath(String name) {
		_parametersIncludedInPath.add(name);
	}

	public boolean isParameterIncludedInPath(String name) {
		if (_parametersIncludedInPath.contains(name)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isSecure() {
		return _secure;
	}

	public void setSecure(boolean secure) throws PortletSecurityException {
		_secure = secure;

		// Clear cache

		_toString = null;
	}

	public boolean isAnchor() {
		return _anchor;
	}

	public void setAnchor(boolean anchor) {
		_anchor = anchor;

		// Clear cache

		_toString = null;
	}

	public boolean isEncrypt() {
		return _encrypt;
	}

	public void setEncrypt(boolean encrypt) {
		_encrypt = encrypt;

		// Clear cache

		_toString = null;
	}

	public void setDoAsUserId(long doAsUserId) {
		_doAsUserId = doAsUserId;

		// Clear cache

		_toString = null;
	}

	public String toString() {
		if (_toString != null) {
			return _toString;
		}

		_toString = generateToString();

		return _toString;
	}

	protected String generateToString() {
		StringMaker sm = new StringMaker();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)_req.getAttribute(WebKeys.THEME_DISPLAY);

		PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

		String portalURL = PortalUtil.getPortalURL(_req, _secure);

		try {
			if (_layoutFriendlyURL == null) {
				Layout layout = getLayout();

				if (layout != null) {
					_layoutFriendlyURL = GetterUtil.getString(
						PortalUtil.getLayoutFriendlyURL(layout, themeDisplay));
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		Key key = null;

		try {
			if (_encrypt) {
				Company company = PortalUtil.getCompany(_req);

				key = company.getKeyObj();
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		if (Validator.isNull(_layoutFriendlyURL)) {
			sm.append(portalURL);
			sm.append(themeDisplay.getPathMain());
			sm.append("/portal/layout?");

			sm.append("p_l_id");
			sm.append(StringPool.EQUAL);
			sm.append(processValue(key, _plid));
			sm.append(StringPool.AMPERSAND);
		}
		else {

			// A virtual host URL will contain the complete path. Do not append
			// the portal URL if the virtual host URL starts with "http://" or
			// "https://".

			if (!_layoutFriendlyURL.startsWith(Http.HTTP_WITH_SLASH) &&
				!_layoutFriendlyURL.startsWith(Http.HTTPS_WITH_SLASH)) {

				sm.append(portalURL);
			}

			sm.append(_layoutFriendlyURL);

			String friendlyURLPath = getPortletFriendlyURLPath();

			if (Validator.isNotNull(friendlyURLPath)) {
				sm.append(friendlyURLPath);

				if (!isAction()) {
					addParameterIncludedInPath("p_p_action");
				}

				//if ((_windowState != null) &&
				//	_windowState.equals(WindowState.MAXIMIZED)) {

					addParameterIncludedInPath("p_p_state");
				//}

				//if ((_portletMode != null) &&
				//	_portletMode.equals(PortletMode.VIEW)) {

					addParameterIncludedInPath("p_p_mode");
				//}

				addParameterIncludedInPath("p_p_col_id");
				addParameterIncludedInPath("p_p_col_pos");
				addParameterIncludedInPath("p_p_col_count");
			}

			sm.append(StringPool.QUESTION);
		}

		if (!isParameterIncludedInPath("p_p_id")) {
			sm.append("p_p_id");
			sm.append(StringPool.EQUAL);
			sm.append(processValue(key, _portletId));
			sm.append(StringPool.AMPERSAND);
		}

		if (!isParameterIncludedInPath("p_p_action")) {
			sm.append("p_p_action");
			sm.append(StringPool.EQUAL);

			if (_action) {
				sm.append(processValue(key, "1"));
			}
			else {
				sm.append(processValue(key, "0"));
			}

			sm.append(StringPool.AMPERSAND);
		}

		if (!isParameterIncludedInPath("p_p_state")) {
			if (_windowState != null) {
				sm.append("p_p_state");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, _windowState.toString()));
				sm.append(StringPool.AMPERSAND);
			}
		}

		if (!isParameterIncludedInPath("p_p_mode")) {
			if (_portletMode != null) {
				sm.append("p_p_mode");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, _portletMode.toString()));
				sm.append(StringPool.AMPERSAND);
			}
		}

		if (!isParameterIncludedInPath("p_p_col_id")) {
			if (Validator.isNotNull(portletDisplay.getColumnId())) {
				sm.append("p_p_col_id");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, portletDisplay.getColumnId()));
				sm.append(StringPool.AMPERSAND);
			}
		}

		if (!isParameterIncludedInPath("p_p_col_pos")) {
			if (portletDisplay.getColumnPos() > 0) {
				sm.append("p_p_col_pos");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, portletDisplay.getColumnPos()));
				sm.append(StringPool.AMPERSAND);
			}
		}

		if (!isParameterIncludedInPath("p_p_col_count")) {
			if (portletDisplay.getColumnCount() > 0) {
				sm.append("p_p_col_count");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, portletDisplay.getColumnCount()));
				sm.append(StringPool.AMPERSAND);
			}
		}

		if (_doAsUserId > 0) {
			try {
				Company company = PortalUtil.getCompany(_req);

				sm.append("doAsUserId");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(company.getKeyObj(), _doAsUserId));
				sm.append(StringPool.AMPERSAND);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
		else {
			String doAsUserId = themeDisplay.getDoAsUserId();

			if (Validator.isNotNull(doAsUserId)) {
				sm.append("doAsUserId");
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, doAsUserId));
				sm.append(StringPool.AMPERSAND);
			}
		}

		Iterator itr = _params.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name = (String)entry.getKey();
			String[] values = (String[])entry.getValue();

			for (int i = 0; i < values.length; i++) {
				if (isParameterIncludedInPath(name)) {
					continue;
				}

				if (!PortalUtil.isReservedParameter(name)) {
					sm.append(getNamespace());
				}

				sm.append(name);
				sm.append(StringPool.EQUAL);
				sm.append(processValue(key, values[i]));

				if ((i + 1 < values.length) || itr.hasNext()) {
					sm.append(StringPool.AMPERSAND);
				}
			}
		}

		if (_encrypt) {
			sm.append(StringPool.AMPERSAND + WebKeys.ENCRYPT + "=1");
		}

		if (PropsValues.PORTLET_URL_ANCHOR_ENABLE) {
			if (_anchor && (_windowState != null) &&
				(!_windowState.equals(WindowState.MAXIMIZED)) &&
				(!_windowState.equals(LiferayWindowState.EXCLUSIVE)) &&
				(!_windowState.equals(LiferayWindowState.POP_UP))) {

				if (sm.lastIndexOf(StringPool.AMPERSAND) != (sm.length() - 1)) {
					sm.append(StringPool.AMPERSAND);
				}

				sm.append("#p_").append(_portletId);
			}
		}

		String result = sm.toString();

		if (result.endsWith(StringPool.QUESTION)) {
			result = result.substring(0, result.length() - 1);
		}

		if (!PropsValues.SESSION_ENABLE_PERSISTENT_COOKIES) {
			result = PortalUtil.getURLWithSessionId(
				result, _req.getSession().getId());
		}

		return result;
	}

	protected String processValue(Key key, int value) {
		return processValue(key, String.valueOf(value));
	}

	protected String processValue(Key key, long value) {
		return processValue(key, String.valueOf(value));
	}

	protected String processValue(Key key, String value) {
		if (key == null) {
			return HttpUtil.encodeURL(value);
		}
		else {
			try {
				return HttpUtil.encodeURL(Encryptor.encrypt(key, value));
			}
			catch (EncryptorException ee) {
				return value;
			}
		}
	}

	private static Log _log = LogFactory.getLog(PortletURLImpl.class);

	private HttpServletRequest _req;
	private PortletRequest _portletReq;
	private String _portletId;
	private Portlet _portlet;
	private String _namespace;
	private long _plid;
	private Layout _layout;
	private String _layoutFriendlyURL;
	private boolean _action;
	private WindowState _windowState;
	private PortletMode _portletMode;
	private Map _params;
	private Set _parametersIncludedInPath;
	private boolean _secure;
	private boolean _anchor = true;
	private boolean _encrypt = false;
	private long _doAsUserId;
	private String _toString;

}