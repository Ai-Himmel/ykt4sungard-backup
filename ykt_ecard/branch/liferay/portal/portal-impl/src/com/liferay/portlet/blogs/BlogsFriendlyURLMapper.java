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

package com.liferay.portlet.blogs;

import com.liferay.portal.kernel.portlet.BaseFriendlyURLMapper;
import com.liferay.portal.kernel.portlet.LiferayPortletURL;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortletKeys;

import java.util.Map;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

/**
 * <a href="BlogsFriendlyURLMapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsFriendlyURLMapper extends BaseFriendlyURLMapper {

	public String getMapping() {
		return _MAPPING;
	}

	public String getPortletId() {
		return _PORTLET_ID;
	}

	public String buildPath(LiferayPortletURL portletURL) {
		String friendlyURLPath = null;

		String strutsAction = GetterUtil.getString(
			portletURL.getParameter("struts_action"));

		if (strutsAction.equals("/blogs/rss")) {
			friendlyURLPath = "/blogs/rss";
		}
		else if (strutsAction.equals("/blogs/view_entry")) {
			String entryId = portletURL.getParameter("entryId");

			String urlTitle = portletURL.getParameter("urlTitle");

			if (Validator.isNotNull(entryId)) {
				friendlyURLPath = "/blogs/" + entryId;

				portletURL.addParameterIncludedInPath("entryId");
			}
			else if (Validator.isNotNull(urlTitle)) {
				friendlyURLPath = "/blogs/" + urlTitle;

				portletURL.addParameterIncludedInPath("urlTitle");
			}
		}

		if (Validator.isNotNull(friendlyURLPath)) {
			portletURL.addParameterIncludedInPath("p_p_id");
			portletURL.addParameterIncludedInPath("struts_action");
		}

		return friendlyURLPath;
	}

	public void populateParams(String friendlyURLPath, Map params) {
		params.put("p_p_id", _PORTLET_ID);
		params.put("p_p_action", "0");
		params.put("p_p_state", WindowState.NORMAL.toString());
		params.put("p_p_mode", PortletMode.VIEW.toString());

		int x = friendlyURLPath.indexOf("/", 1);
		int y = friendlyURLPath.length();

		if ((x + 1) == y) {
			addParam(params, "struts_action", "/blogs/view");

			return;
		}

		String type = friendlyURLPath.substring(x + 1, y);

		if (type.equals("rss")) {
			params.put("p_p_action", "1");
			params.put("p_p_state", LiferayWindowState.EXCLUSIVE.toString());

			addParam(params, "struts_action", "/blogs/rss");
		}
		else {
			addParam(params, "struts_action", "/blogs/view_entry");

			if (Validator.isNumber(type)) {
				String entryId = type;

				addParam(params, "entryId", entryId);
			}
			else {
				String urlTitle = type;

				addParam(params, "urlTitle", urlTitle);
			}
		}
	}

	private static final String _MAPPING = "blogs";

	private static final String _PORTLET_ID = PortletKeys.BLOGS;

}