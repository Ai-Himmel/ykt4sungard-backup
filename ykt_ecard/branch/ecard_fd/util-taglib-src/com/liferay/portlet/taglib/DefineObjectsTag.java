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

package com.liferay.portlet.taglib;

import com.liferay.portal.servlet.PortletSessionPool;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.portlet.PortletSessionImpl;
import com.liferay.util.ServerDetector;

import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="DefineObjectsTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class DefineObjectsTag extends TagSupport {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		PortletConfigImpl portletConfig =
			(PortletConfigImpl)req.getAttribute(WebKeys.JAVAX_PORTLET_CONFIG);

		if (portletConfig != null) {
			pageContext.setAttribute("portletConfig", portletConfig);
		}

		RenderRequest renderRequest =
			(RenderRequest)req.getAttribute(WebKeys.JAVAX_PORTLET_REQUEST);

		if (renderRequest != null) {
			pageContext.setAttribute("renderRequest", renderRequest);
		}

		RenderResponse renderResponse =
			(RenderResponse)req.getAttribute(WebKeys.JAVAX_PORTLET_RESPONSE);

		if (renderResponse != null) {
			pageContext.setAttribute("renderResponse", renderResponse);
		}

		if (portletConfig.isWARFile() && ServerDetector.isWebLogic()) {
			PortletSessionImpl portletSession =
				(PortletSessionImpl)renderRequest.getPortletSession();

			PortletSessionPool.put(
				portletSession.getPortalSessionId(), pageContext.getSession());
		}

		return SKIP_BODY;
	}

	public int doEndTag() {
		return EVAL_PAGE;
	}

}