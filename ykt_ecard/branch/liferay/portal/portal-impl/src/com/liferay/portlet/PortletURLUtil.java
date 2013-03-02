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

import com.liferay.portal.kernel.portlet.LiferayPortletURL;

import java.util.Enumeration;

import javax.portlet.PortletException;
import javax.portlet.PortletMode;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

/**
 * <a href="PortletURLUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletURLUtil {

	public static PortletURL getCurrent(RenderRequest req, RenderResponse res) {
		PortletURL portletURL = res.createRenderURL();

		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String param = (String)enu.nextElement();
			String[] values = req.getParameterValues(param);

			boolean addParam = true;

			// Don't set paramter values that are over 32 kb. See LEP-1755.

			for (int i = 0; i < values.length; i++) {
				if (values[i].length() > _CURRENT_URL_PARAMETER_THRESHOLD) {
					addParam = false;

					break;
				}
			}

			if (addParam) {
				portletURL.setParameter(param, values);
			}
		}

		return portletURL;
	}

	public static PortletURL clone(PortletURL portletURL, RenderResponse res)
		throws PortletException {

		LiferayPortletURL liferayPortletURL = (LiferayPortletURL)portletURL;

		return clone(liferayPortletURL, liferayPortletURL.isAction(), res);
	}

	public static PortletURL clone(
			PortletURL portletURL, boolean action, RenderResponse res)
		throws PortletException {

		LiferayPortletURL liferayPortletURL = (LiferayPortletURL)portletURL;

		return clone(liferayPortletURL, action, res);
	}

	public static PortletURL clone(
			LiferayPortletURL liferayPortletURL, boolean action,
			RenderResponse res)
		throws PortletException {

		LiferayPortletURL newURLImpl = null;

		if (action) {
			newURLImpl = (LiferayPortletURL)res.createActionURL();
		}
		else {
			newURLImpl = (LiferayPortletURL)res.createRenderURL();
		}

		newURLImpl.setPortletId(liferayPortletURL.getPortletId());

		WindowState windowState = liferayPortletURL.getWindowState();

		if (windowState != null) {
			newURLImpl.setWindowState(windowState);
		}

		PortletMode portletMode = liferayPortletURL.getPortletMode();

		if (portletMode != null) {
			newURLImpl.setPortletMode(portletMode);
		}

		newURLImpl.setParameters(liferayPortletURL.getParameterMap());

		return newURLImpl;
	}

	private static final int _CURRENT_URL_PARAMETER_THRESHOLD = 32768;

}