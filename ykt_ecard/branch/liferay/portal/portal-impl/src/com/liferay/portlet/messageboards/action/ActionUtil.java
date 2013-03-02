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

package com.liferay.portlet.messageboards.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.portlet.messageboards.model.impl.MBCategoryImpl;
import com.liferay.portlet.messageboards.service.MBBanLocalServiceUtil;
import com.liferay.portlet.messageboards.service.MBCategoryServiceUtil;
import com.liferay.portlet.messageboards.service.MBMessageServiceUtil;
import com.liferay.portlet.messageboards.service.MBThreadLocalServiceUtil;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionUtil {

	public static void getCategory(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getCategory(httpReq);
	}

	public static void getCategory(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getCategory(httpReq);
	}

	public static void getCategory(HttpServletRequest req) throws Exception {

		// Add redundant check here because the JSP does not check permissions
		// on the initial search container

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		MBBanLocalServiceUtil.checkBan(
			themeDisplay.getPortletGroupId(), themeDisplay.getUserId());

		long categoryId = ParamUtil.getLong(req, "categoryId");

		MBCategory category = null;

		if ((categoryId > 0) &&
			(categoryId != MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID)) {

			category = MBCategoryServiceUtil.getCategory(categoryId);
		}

		req.setAttribute(WebKeys.MESSAGE_BOARDS_CATEGORY, category);
	}

	public static void getMessage(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getMessage(httpReq);
	}

	public static void getMessage(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getMessage(httpReq);
	}

	public static void getMessage(HttpServletRequest req) throws Exception {
		long messageId = ParamUtil.getLong(req, "messageId");

		MBMessage message = null;

		if (messageId > 0) {
			message = MBMessageServiceUtil.getMessage(messageId);
		}

		req.setAttribute(WebKeys.MESSAGE_BOARDS_MESSAGE, message);
	}

	public static void getThreadMessage(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getThreadMessage(httpReq);
	}

	public static void getThreadMessage(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getThreadMessage(httpReq);
	}

	public static void getThreadMessage(HttpServletRequest req)
		throws Exception {

		long threadId = ParamUtil.getLong(req, "threadId");

		MBMessage message = null;

		if (threadId > 0) {
			MBThread thread = MBThreadLocalServiceUtil.getThread(threadId);

			message = MBMessageServiceUtil.getMessage(
				thread.getRootMessageId());
		}

		req.setAttribute(WebKeys.MESSAGE_BOARDS_MESSAGE, message);
	}

}