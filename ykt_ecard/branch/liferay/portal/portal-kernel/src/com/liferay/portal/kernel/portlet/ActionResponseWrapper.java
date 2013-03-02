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

package com.liferay.portal.kernel.portlet;

import java.io.IOException;

import java.util.Map;

import javax.portlet.ActionResponse;
import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.WindowState;
import javax.portlet.WindowStateException;

/**
 * <a href="ActionResponseWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionResponseWrapper
	extends PortletResponseWrapper implements ActionResponse {

	public ActionResponseWrapper(ActionResponse res) {
		super(res);

		_res = res;
	}

	public void setWindowState(WindowState windowState)
		throws WindowStateException {

		_res.setWindowState(windowState);
	}

	public void setPortletMode(PortletMode portletMode)
		throws PortletModeException {

		_res.setPortletMode(portletMode);
	}

	public void sendRedirect(String location) throws IOException {
		_res.sendRedirect(location);
	}

	public void setRenderParameters(Map parameters) {
		_res.setRenderParameters(parameters);
	}

	public void setRenderParameter(String key, String value) {
		_res.setRenderParameter(key, value);
	}

	public void setRenderParameter(String key, String[] values) {
		_res.setRenderParameter(key, values);
	}

	private ActionResponse _res;

}