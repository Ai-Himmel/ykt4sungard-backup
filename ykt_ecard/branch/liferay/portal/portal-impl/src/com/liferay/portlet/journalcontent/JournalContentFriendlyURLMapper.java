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

package com.liferay.portlet.journalcontent;

import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.portlet.LiferayPortletURL;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortletKeys;

import java.util.Map;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

/**
 * <a href="JournalContentFriendlyURLMapper.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Raymond Augé
 *
 */
public class JournalContentFriendlyURLMapper implements FriendlyURLMapper {

	public String getMapping() {
		return _MAPPING;
	}

	public String buildPath(LiferayPortletURL portletURL) {
		String friendlyURLPath = null;

		String strutsAction = GetterUtil.getString(
			portletURL.getParameter("struts_action"));

		if (strutsAction.equals("/journal_content/view")) {
			String portletId = portletURL.getPortletId();
			String groupId = portletURL.getParameter("groupId");
			String articleId = portletURL.getParameter("articleId");
			String templateId = portletURL.getParameter("templateId");

			if (Validator.isNotNull(portletId) &&
				Validator.isNotNull(groupId) &&
				Validator.isNotNull(articleId)) {

				if (portletId.equals(_PORTLET_DEFAULT_INSTANCE)) {
					portletId = _PORTLET_ID;
				}

				friendlyURLPath =
					"/journal_content/" + portletId + "/" + groupId + "/" +
						articleId;

				portletURL.addParameterIncludedInPath("groupId");
				portletURL.addParameterIncludedInPath("articleId");

				if (Validator.isNotNull(templateId)) {
					friendlyURLPath += "/" + templateId;

					portletURL.addParameterIncludedInPath("templateId");
				}
			}
		}

		if (Validator.isNotNull(friendlyURLPath)) {
			portletURL.addParameterIncludedInPath("p_p_id");
			portletURL.addParameterIncludedInPath("struts_action");
		}

		return friendlyURLPath;
	}

	public void populateParams(String friendlyURLPath, Map params) {
		int w = friendlyURLPath.indexOf("/", 1);
		int x = friendlyURLPath.indexOf("/", w + 1);
		int y = friendlyURLPath.indexOf("/", x + 1);
		int z = friendlyURLPath.indexOf("/", y + 1);

		if (x == -1) {
			return;
		}

		String portletId = friendlyURLPath.substring(w + 1, x);

		String namespace =
			StringPool.UNDERLINE + portletId + StringPool.UNDERLINE;

		if (Validator.equals(portletId, _PORTLET_ID)) {
			portletId = _PORTLET_DEFAULT_INSTANCE;

			namespace = StringPool.UNDERLINE + portletId + StringPool.UNDERLINE;

			params.put("p_p_id", portletId);
			params.put("p_p_state", WindowState.MAXIMIZED.toString());
		}
		else {
			params.put("p_p_id", portletId);
			params.put("p_p_state", WindowState.NORMAL.toString());
		}

		params.put("p_p_action", "0");
		params.put("p_p_mode", PortletMode.VIEW.toString());

		String groupId = friendlyURLPath.substring(x + 1, y);

		params.put(namespace + "groupId", groupId);

		String articleId = null;

		if (z == -1) {
			articleId =
				friendlyURLPath.substring(y + 1, friendlyURLPath.length());

			params.put(namespace + "articleId", articleId);
		}
		else {
			articleId = friendlyURLPath.substring(y + 1, z);

			params.put(namespace + "articleId", articleId);

			String templateId =
				friendlyURLPath.substring(z + 1, friendlyURLPath.length());

			params.put(namespace + "templateId", templateId);
		}

		params.put(namespace + "struts_action", "/journal_content/view");
	}

	private static final String _MAPPING = "journal_content";

	private static final String _PORTLET_DEFAULT_INSTANCE =
		PortletKeys.JOURNAL_CONTENT + "_INSTANCE_0000";

	private static final String _PORTLET_ID = PortletKeys.JOURNAL_CONTENT;

}