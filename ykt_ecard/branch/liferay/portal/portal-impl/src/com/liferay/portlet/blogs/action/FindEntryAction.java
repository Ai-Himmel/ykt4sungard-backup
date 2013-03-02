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

package com.liferay.portlet.blogs.action;

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.BlogsEntryLocalServiceUtil;

import java.util.List;

import javax.portlet.PortletMode;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="FindEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class FindEntryAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			long plid = ParamUtil.getLong(req, "p_l_id");
			String redirect = ParamUtil.getString(req, "redirect");
			long entryId = ParamUtil.getLong(req, "entryId");
			boolean showAllEntries = ParamUtil.getBoolean(
				req, "showAllEntries");

			plid = getPlid(plid, entryId);

			String urlTitle = getUrlTitle(entryId);

			PortletURL portletURL = new PortletURLImpl(
				req, PortletKeys.BLOGS, plid, false);

			portletURL.setWindowState(WindowState.NORMAL);
			portletURL.setPortletMode(PortletMode.VIEW);

			if (Validator.isNotNull(redirect)) {
				portletURL.setParameter("redirect", redirect);
			}

			if (showAllEntries) {
				portletURL.setParameter("struts_action", "/blogs/view");
			}
			else {
				portletURL.setParameter("struts_action", "/blogs/view_entry");

				if (Validator.isNotNull(urlTitle)) {
					portletURL.setParameter("urlTitle", urlTitle);
				}
				else {
					portletURL.setParameter("entryId", String.valueOf(entryId));
				}
			}

			res.sendRedirect(portletURL.toString());

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

	protected long getPlid(long plid, long entryId) throws Exception {
		if (plid != 0) {
			try {
				Layout layout = LayoutLocalServiceUtil.getLayout(plid);

				LayoutTypePortlet layoutTypePortlet =
					(LayoutTypePortlet)layout.getLayoutType();

				if (layoutTypePortlet.hasPortletId(PortletKeys.BLOGS)) {
					return plid;
				}
			}
			catch (NoSuchLayoutException nsle) {
			}
		}

		BlogsEntry entry = BlogsEntryLocalServiceUtil.getEntry(entryId);

		long groupId = entry.getGroupId();
		boolean privateLayout = false;

		List layouts = LayoutLocalServiceUtil.getLayouts(
			groupId, privateLayout);

		for (int i = 0; i < layouts.size(); i++) {
			Layout layout = (Layout)layouts.get(i);

			if (!layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
				continue;
			}

			LayoutTypePortlet layoutTypePortlet =
				(LayoutTypePortlet)layout.getLayoutType();

			if (layoutTypePortlet.hasPortletId(PortletKeys.BLOGS)) {
				return layout.getPlid();
			}
		}

		throw new NoSuchLayoutException(
			"No public page was found with the Blogs portlet.");
	}

	protected String getUrlTitle(long entryId) {
		String urlTitle = StringPool.BLANK;

		try {
			BlogsEntry entry = BlogsEntryLocalServiceUtil.getEntry(entryId);

			urlTitle = entry.getUrlTitle();
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return urlTitle;
	}

	private static Log _log = LogFactory.getLog(FindEntryAction.class);

}