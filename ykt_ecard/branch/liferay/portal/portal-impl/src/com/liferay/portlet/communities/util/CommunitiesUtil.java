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

package com.liferay.portlet.communities.util;

import com.germinus.easyconf.Filter;

import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.LayoutServiceUtil;
import com.liferay.portal.service.permission.LayoutPermissionUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.RenderResponseImpl;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="CommunitiesUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class CommunitiesUtil {

	public static void deleteLayout(ActionRequest req, ActionResponse res)
		throws Exception {

		HttpServletRequest httpReq = (HttpServletRequest)
			((ActionRequestImpl)req).getHttpServletRequest();
		HttpServletResponse httpRes = (HttpServletResponse)
			((ActionResponseImpl)res).getHttpServletResponse();

		deleteLayout(httpReq, httpRes);
	}

	public static void deleteLayout(RenderRequest req, RenderResponse res)
		throws Exception {

		HttpServletRequest httpReq = (HttpServletRequest)
			((RenderRequestImpl)req).getHttpServletRequest();
		HttpServletResponse httpRes = (HttpServletResponse)
			((RenderResponseImpl)res).getHttpServletResponse();

		deleteLayout(httpReq, httpRes);
	}

	public static void deleteLayout(
			HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		PermissionChecker permissionChecker =
			themeDisplay.getPermissionChecker();

		long plid = ParamUtil.getLong(req, "plid");

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
		long layoutId = ParamUtil.getLong(req, "layoutId");

		Layout layout = null;

		if (plid <= 0) {
			layout = LayoutLocalServiceUtil.getLayout(
				groupId, privateLayout, layoutId);
		}
		else {
			layout = LayoutLocalServiceUtil.getLayout(plid);

			groupId = layout.getGroupId();
			privateLayout = layout.isPrivateLayout();
			layoutId = layout.getLayoutId();
		}

		if (LayoutPermissionUtil.contains(
				permissionChecker, groupId, privateLayout, layoutId,
				ActionKeys.DELETE)) {

			String[] eventClasses = StringUtil.split(
				PropsUtil.getComponentProperties().getString(
					PropsUtil.LAYOUT_CONFIGURATION_ACTION_DELETE,
					Filter.by(layout.getType())));

			EventsProcessor.process(eventClasses, req, res);
		}

		LayoutServiceUtil.deleteLayout(groupId, privateLayout, layoutId);
	}

}