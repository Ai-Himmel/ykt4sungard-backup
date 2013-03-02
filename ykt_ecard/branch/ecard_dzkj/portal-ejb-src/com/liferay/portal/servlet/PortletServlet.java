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

package com.liferay.portal.servlet;

import com.liferay.portal.util.WebKeys;

import java.io.IOException;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.Portlet;
import javax.portlet.PortletException;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class PortletServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		PortletRequest portletReq =
			(PortletRequest)req.getAttribute(WebKeys.JAVAX_PORTLET_REQUEST);

		PortletResponse portletRes =
			(PortletResponse)req.getAttribute(WebKeys.JAVAX_PORTLET_RESPONSE);

		Portlet portlet =
			(Portlet)req.getAttribute(WebKeys.JAVAX_PORTLET_PORTLET);

		try {
			if (portletReq instanceof ActionRequest) {
				ActionRequest actionReq = (ActionRequest)portletReq;
				ActionResponse actionRes = (ActionResponse)portletRes;

				portlet.processAction(actionReq, actionRes);
			}
			else {
				RenderRequest renderReq = (RenderRequest)portletReq;
				RenderResponse renderRes = (RenderResponse)portletRes;

				portlet.render(renderReq, renderRes);
			}
		}
		catch (PortletException pe) {
			pe.printStackTrace();

			throw new ServletException(pe);
		}
	}

	private static final Log _log = LogFactory.getLog(PortletServlet.class);

}