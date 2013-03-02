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

package com.liferay.portlet.blogs.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.blogs.EntryContentException;
import com.liferay.portlet.blogs.EntryDisplayDateException;
import com.liferay.portlet.blogs.EntryTitleException;
import com.liferay.portlet.blogs.NoSuchCategoryException;
import com.liferay.portlet.blogs.NoSuchEntryException;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import java.util.Calendar;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletURL;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class EditEntryAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editEntry(req);

				_updateEntry(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof EntryContentException ||
					e instanceof EntryDisplayDateException ||
					e instanceof EntryTitleException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.edit_entry");
				}
				else if (e != null &&
						 e instanceof NoSuchCategoryException ||
						 e instanceof NoSuchEntryException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteEntry(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchEntryException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				_editEntry(req);

				setForward(req, "portlet.blogs.edit_entry");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchEntryException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals("update_sharing")) {
			try {
				_updateSharing(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchEntryException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.blogs.edit_entry");
		}
	}

	private void _deleteEntry(ActionRequest req, ActionResponse res)
		throws Exception {

		String entryId = ParamUtil.getString(req, "entry_id");

		BlogsEntryServiceUtil.deleteEntry(entryId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editEntry(ActionRequest req) throws Exception {
		String entryId = req.getParameter("entry_id");

		BlogsEntry entry = null;

		if (Validator.isNotNull(entryId)) {
			try {
				entry = BlogsEntryServiceUtil.getEntry(entryId);
			}
			catch (NoSuchEntryException nsee) {
			}
		}

		req.setAttribute(WebKeys.BLOGS_ENTRY, entry);
	}

	private void _updateEntry(ActionRequest req, ActionResponse res)
		throws Exception {

		String entryId = ParamUtil.getString(req, "entry_id");

		String categoryId = ParamUtil.getString(req, "category_id");
		String title = ParamUtil.getString(req, "entry_title");
		String content = ParamUtil.getString(req, "entry_content");

		int displayMonth = ParamUtil.getInteger(req, "entry_display_month");
		int displayDay = ParamUtil.getInteger(req, "entry_display_day");
		int displayYear = ParamUtil.getInteger(req, "entry_display_year");
		int displayHour = ParamUtil.get(req, "entry_display_hour", 0);
		int displayMinute = ParamUtil.get(req, "entry_display_minute", 0);
		int displayAMPM = ParamUtil.get(
			req, "entry_display_am_pm", Calendar.AM);

		if (displayAMPM == Calendar.PM) {
			displayHour += 12;
		}

		boolean sharing = ParamUtil.get(req, "entry_sharing", false);
		boolean commentable = ParamUtil.get(req, "entry_commentable", false);

		BlogsEntry entry = null;

		if (Validator.isNull(entryId)) {

			// Add entry

			entry = BlogsEntryServiceUtil.addEntry(
				categoryId, title, content, displayMonth, displayDay,
				displayYear, displayHour, displayMinute, sharing, commentable);
		}
		else {

			// Update entry

			entry = BlogsEntryServiceUtil.updateEntry(
				entryId, categoryId, title, content, displayMonth, displayDay,
				displayYear, displayHour, displayMinute, sharing, commentable);
		}

		// Send redirect

		String redirect = ParamUtil.getString(req, "redirect");

		if (Validator.isNull(redirect)) {
			ActionResponseImpl actionResponse = (ActionResponseImpl)res;

			PortletURL portletURL = actionResponse.createRenderURL();

			portletURL.setParameter("struts_action", "/blogs/view_entries");
			portletURL.setParameter("blogs_user_id", req.getRemoteUser());
			portletURL.setParameter("month", Integer.toString(displayMonth));
			portletURL.setParameter("day", Integer.toString(displayDay));
			portletURL.setParameter("year", Integer.toString(displayYear));
			portletURL.setParameter("category_id", categoryId);

			redirect =
				portletURL.toString() + "&#" + actionResponse.getNamespace() +
					"entry_id_" + entry.getEntryId();
		}

		res.sendRedirect(redirect);
	}

	private void _updateSharing(ActionRequest req, ActionResponse res)
		throws Exception {

		String entryId = ParamUtil.getString(req, "entry_id");

		BlogsEntryServiceUtil.updateSharing(entryId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}