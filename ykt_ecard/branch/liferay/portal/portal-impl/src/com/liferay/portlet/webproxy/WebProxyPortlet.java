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

package com.liferay.portlet.webproxy;

import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.struts.StrutsUtil;
import com.liferay.portlet.RenderResponseImpl;

import java.io.IOException;

import javax.portlet.PortletException;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletRequestDispatcher;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.portletbridge.portlet.PortletBridgePortlet;

/**
 * <a href="WebProxyPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WebProxyPortlet extends PortletBridgePortlet {

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		PortletPreferences prefs = req.getPreferences();

		String initUrl = prefs.getValue("initUrl", StringPool.BLANK);

		if (Validator.isNull(initUrl)) {
			PortletRequestDispatcher prd =
				getPortletContext().getRequestDispatcher(
					StrutsUtil.TEXT_HTML_DIR + "/portal/portlet_not_setup.jsp");

			prd.include(req, res);
		}
		else {
			super.doView(req, res);

			RenderResponseImpl resImpl = (RenderResponseImpl)res;

			StringServletResponse stringServletRes =
				(StringServletResponse)resImpl.getHttpServletResponse();

			String output = stringServletRes.getString();

			output = StringUtil.replace(output, "//pbhs/", "/pbhs/");

			stringServletRes.setString(output);
		}
	}

}