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

package com.liferay.portal.wsrp;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.wsrp.util.WSRPUtil;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.portlet.RenderRequestImpl;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

import oasis.names.tc.wsrp.v1.types.GetMarkup;
import oasis.names.tc.wsrp.v1.types.PerformBlockingInteraction;
import oasis.names.tc.wsrp.v1.types.PortletContext;
import oasis.names.tc.wsrp.v1.types.RuntimeContext;
import oasis.names.tc.wsrp.v1.types.UserContext;

import org.apache.wsrp4j.producer.provider.Provider;
import org.apache.wsrp4j.producer.provider.URLComposer;
import org.apache.wsrp4j.producer.util.Base64;
import org.apache.wsrp4j.producer.util.ObjectSerializer;

/**
 * <a href="WSRPPortletURLImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class WSRPPortletURLImpl extends PortletURLImpl {

	public WSRPPortletURLImpl(PerformBlockingInteraction pbo, Provider wsrpProvider,
							  ActionRequestImpl req, String portletName,
							  long plid, boolean action) {

		super(req, portletName, plid, action);

		_init(pbo, wsrpProvider);
	}

	public WSRPPortletURLImpl(GetMarkup getMarkup, Provider wsrpProvider,
							  RenderRequestImpl req, String portletName,
							  long plid, boolean action) {

		super(req, portletName, plid, action);

		_init(getMarkup, wsrpProvider);
	}

	public String toString() {
		PortletMode portletMode = getPortletMode();
		WindowState windowState = getWindowState();
		boolean action = isAction();
		boolean secure = isSecure();

		if (portletMode == null) {
			portletMode = PortletMode.VIEW;
		}

		if (windowState == null) {
			windowState = WindowState.NORMAL;
		}

		URLComposer urlComposer = _wsrpProvider.getURLComposer();
		String encodedParams = _getEncodedParameters();
		String url = StringPool.BLANK;

		if (action) {
			url = urlComposer.createBlockingActionURL(WSRPUtil
					.toWsrpMode(portletMode.toString()), null, encodedParams,
					WSRPUtil.toWsrpWindowState(windowState.toString()), secure,
					_runtimeContext, _portletContext, _userContext);
		}
		else {
			url = urlComposer.createRenderURL(WSRPUtil.toWsrpMode(portletMode
					.toString()), encodedParams, WSRPUtil
					.toWsrpWindowState(windowState.toString()), secure,
					_runtimeContext, _portletContext, _userContext);
		}
		return url;
	}

	private void _init(GetMarkup getMarkup, Provider wsrpProvider) {
		_runtimeContext = getMarkup.getRuntimeContext();
		_portletContext = getMarkup.getPortletContext();
		_userContext = getMarkup.getUserContext();
		_wsrpProvider = wsrpProvider;
	}

	private void _init(PerformBlockingInteraction pbo, Provider wsrpProvider) {
		_runtimeContext = pbo.getRuntimeContext();
		_portletContext = pbo.getPortletContext();
		_userContext = pbo.getUserContext();
		_wsrpProvider = wsrpProvider;
	}

	private String _getEncodedParameters() {
		Map renderParams = getParameterMap();
		Map params = new HashMap();

		String[] plid = {String.valueOf(getPlid())};
		params.put("p_l_id", plid);

		String[] portletId = {getPortletId()};
		params.put("p_p_id", portletId);

		String[] action = {isAction() ? "1" : "0"};
		params.put("p_p_action", action);

		WindowState windowState = getWindowState();
		if (getWindowState() != null) {
			String[] stateStr = {windowState.toString()};
			params.put("p_p_state", stateStr);
		}

		PortletMode portletMode = getPortletMode();
		if (getPortletMode() != null) {
			String[] modeStr = {portletMode.toString()};
			params.put("p_p_mode", modeStr);
		}

		Iterator itr = renderParams.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name =
				PortalUtil.getPortletNamespace(portletId[0]) +
				(String)entry.getKey();
			String[] values = (String[])entry.getValue();

			for (int i = 0; i < values.length; i++) {
				params.put(name, values);
			}
		}

		String encodedParams = null;

		try {
			encodedParams = Base64.encode(ObjectSerializer
					.serialize(params));
		}
		catch (Exception e) {
		}

		return encodedParams;
	}

	private RuntimeContext _runtimeContext;
	private PortletContext _portletContext;
	private UserContext _userContext;
	private Provider _wsrpProvider;

}