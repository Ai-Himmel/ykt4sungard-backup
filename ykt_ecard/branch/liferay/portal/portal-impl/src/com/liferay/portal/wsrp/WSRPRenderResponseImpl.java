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

import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.RenderResponseImpl;

import javax.portlet.PortletURL;

import javax.servlet.http.HttpServletResponse;

import oasis.names.tc.wsrp.v1.types.GetMarkup;

import org.apache.wsrp4j.producer.provider.Provider;

/**
 * <a href="WSRPRenderResponseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class WSRPRenderResponseImpl extends RenderResponseImpl {

	public WSRPRenderResponseImpl() {
		super();
	}

	public WSRPRenderResponseImpl(GetMarkup getMarkup, Provider wsrpProvider,
			RenderRequestImpl req, HttpServletResponse res, String portletName,
			long companyId, long plid) {
		init(req, res, portletName, companyId, plid);
		_init(getMarkup, wsrpProvider);
	}

	public PortletURL createPortletURL(String portletName, boolean action) {
		return new WSRPPortletURLImpl(
				_getMarkup, _wsrpProvider, getReq(), portletName, getPlid(),
			action);
	}

	private void _init(GetMarkup getMarkup, Provider wsrpProvider) {
		_getMarkup = getMarkup;
		_wsrpProvider = wsrpProvider;
	}

	private GetMarkup _getMarkup;
	private Provider _wsrpProvider;

}