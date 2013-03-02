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

import com.liferay.portal.model.Layout;
import com.liferay.portal.model.User;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseImpl;

import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;
import javax.portlet.WindowStateException;

import javax.servlet.http.HttpServletResponse;

import oasis.names.tc.wsrp.v1.types.PerformBlockingInteraction;

import org.apache.wsrp4j.producer.provider.Provider;

/**
 * <a href="WSRPActionResponseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class WSRPActionResponseImpl extends ActionResponseImpl {

	public WSRPActionResponseImpl() {
		super();
	}

	public WSRPActionResponseImpl(PerformBlockingInteraction pbo, Provider wsrpProvider,
			ActionRequestImpl req, HttpServletResponse res, String portletName,
			User user, Layout layout, WindowState windowState,
			PortletMode portletMode) throws PortletModeException,
			WindowStateException {
		init(req, res, portletName, user, layout, windowState, portletMode);
		_init(pbo, wsrpProvider);
	}

	protected PortletURL createPortletURL(String portletName, boolean action) {
		return new WSRPPortletURLImpl(_pbo, _wsrpProvider, getReq(),
				portletName, getLayout().getLayoutId(), action);
	}

	private void _init(PerformBlockingInteraction pbo, Provider wsrpProvider) {
		_pbo = pbo;
		_wsrpProvider = wsrpProvider;
	}

	private PerformBlockingInteraction _pbo;

	private Provider _wsrpProvider;

}