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

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.blogs.EntryContentException;
import com.liferay.portlet.blogs.EntryDisplayDateException;
import com.liferay.portlet.blogs.EntryTitleException;
import com.liferay.portlet.blogs.NoSuchEntryException;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.BlogsEntryLocalServiceUtil;
import com.liferay.portlet.blogs.service.BlogsEntryServiceUtil;
import com.liferay.portlet.taggedcontent.util.AssetPublisherUtil;
import com.liferay.portlet.tags.TagsEntryException;
import com.liferay.util.servlet.SessionErrors;

import java.util.Calendar;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Wilson S. Man
 *
 */
public class EditEntryAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			BlogsEntry entry = null;
			String oldUrlTitle = StringPool.BLANK;

			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				Object[] returnValue = updateEntry(req);

				entry = (BlogsEntry)returnValue[0];
				oldUrlTitle = ((String)returnValue[1]);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteEntry(req);
			}

			String redirect = ParamUtil.getString(req, "redirect");

			if ((entry != null) && (Validator.isNotNull(oldUrlTitle)) &&
				(redirect.endsWith("/blogs/" + oldUrlTitle) ||
				 redirect.indexOf("/blogs/" + oldUrlTitle + "?") != -1)) {

				int pos = redirect.indexOf("?");

				if (pos == -1) {
					pos = redirect.length();
				}

				String newRedirect = redirect.substring(
					0, pos - oldUrlTitle.length());

				newRedirect += entry.getUrlTitle();

				if (pos < redirect.length()) {
					newRedirect +=
						"?" + redirect.substring(pos + 1, redirect.length());
				}

				redirect = newRedirect;
			}

			ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
				WebKeys.THEME_DISPLAY);

			LayoutTypePortlet layoutTypePortlet =
				themeDisplay.getLayoutTypePortlet();

			if (layoutTypePortlet.hasPortletId(config.getPortletName())) {
				sendRedirect(req, res, redirect);
			}
			else {
				res.sendRedirect(redirect);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchEntryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.blogs.error");
			}
			else if (e instanceof EntryContentException ||
					 e instanceof EntryDisplayDateException ||
					 e instanceof EntryTitleException) {

				SessionErrors.add(req, e.getClass().getName());
			}
			else if (e instanceof TagsEntryException) {
				SessionErrors.add(req, e.getClass().getName(), e);
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			ActionUtil.getEntry(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchEntryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.blogs.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(getForward(req, "portlet.blogs.edit_entry"));
	}

	protected void deleteEntry(ActionRequest req) throws Exception {
		long entryId = ParamUtil.getLong(req, "entryId");

		BlogsEntryServiceUtil.deleteEntry(entryId);
	}

	protected Object[] updateEntry(ActionRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		Layout layout = themeDisplay.getLayout();

		long entryId = ParamUtil.getLong(req, "entryId");

		String title = ParamUtil.getString(req, "title");
		String content = ParamUtil.getString(req, "content");

		int displayDateMonth = ParamUtil.getInteger(req, "displayDateMonth");
		int displayDateDay = ParamUtil.getInteger(req, "displayDateDay");
		int displayDateYear = ParamUtil.getInteger(req, "displayDateYear");
		int displayDateHour = ParamUtil.getInteger(req, "displayDateHour");
		int displayDateMinute = ParamUtil.getInteger(req, "displayDateMinute");
		int displayDateAmPm = ParamUtil.getInteger(req, "displayDateAmPm");

		if (displayDateAmPm == Calendar.PM) {
			displayDateHour += 12;
		}

		String[] tagsEntries = StringUtil.split(
			ParamUtil.getString(req, "tagsEntries"));

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		BlogsEntry entry = null;
		String oldUrlTitle = StringPool.BLANK;

		if (entryId <= 0) {

			// Add entry

			entry = BlogsEntryServiceUtil.addEntry(
				layout.getPlid(), title, content, displayDateMonth,
				displayDateDay, displayDateYear, displayDateHour,
				displayDateMinute, tagsEntries, communityPermissions,
				guestPermissions, themeDisplay);

			AssetPublisherUtil.addAndStoreSelection(
				req, BlogsEntry.class.getName(), entry.getEntryId(), -1);
		}
		else {

			// Update entry

			entry = BlogsEntryLocalServiceUtil.getEntry(entryId);

			String tempOldUrlTitle = entry.getUrlTitle();

			entry = BlogsEntryServiceUtil.updateEntry(
				entryId, title, content, displayDateMonth, displayDateDay,
				displayDateYear, displayDateHour, displayDateMinute,
				tagsEntries, themeDisplay);

			if (!tempOldUrlTitle.equals(entry.getUrlTitle())) {
				oldUrlTitle = tempOldUrlTitle;
			}
		}

		return new Object[] {entry, oldUrlTitle};
	}

}