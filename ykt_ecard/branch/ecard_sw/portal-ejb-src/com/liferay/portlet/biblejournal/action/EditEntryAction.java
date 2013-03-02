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

package com.liferay.portlet.biblejournal.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.biblejournal.EntryContentException;
import com.liferay.portlet.biblejournal.EntryNameException;
import com.liferay.portlet.biblejournal.NoSuchEntryException;
import com.liferay.portlet.biblejournal.model.BJEntry;
import com.liferay.portlet.biblejournal.service.spring.BJEntryServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.crosswire.bible.passage.NoSuchVerseException;

/**
 * <a href="EditEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
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
					e instanceof EntryNameException ||
					e instanceof NoSuchVerseException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.bible_journal.edit_entry");
				}
				else if (e != null &&
						 e instanceof NoSuchEntryException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.bible_journal.error");
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

					setForward(req, "portlet.bible_journal.error");
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

				setForward(req, "portlet.bible_journal.edit_entry");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchEntryException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.bible_journal.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.bible_journal.edit_entry");
		}
	}

	private void _deleteEntry(ActionRequest req, ActionResponse res)
		throws Exception {

		String entryId = ParamUtil.getString(req, "entry_id");

		BJEntryServiceUtil.deleteEntry(entryId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editEntry(ActionRequest req) throws Exception {
		String entryId = ParamUtil.getString(req, "entry_id");

		BJEntry entry = null;

		if (Validator.isNotNull(entryId)) {
			entry = BJEntryServiceUtil.getEntry(entryId);
		}

		req.setAttribute(WebKeys.BIBLE_JOURNAL_ENTRY, entry);
	}

	private void _updateEntry(ActionRequest req, ActionResponse res)
		throws Exception {

		String entryId = ParamUtil.getString(req, "entry_id");

		String verses = ParamUtil.getString(req, "entry_verses");
		String[] topicIds = StringUtil.split(
			ParamUtil.getString(req, "entry_topics"));

		String name = ParamUtil.getString(req, "entry_name");
		String content = ParamUtil.getString(req, "entry_content");

		if (Validator.isNull(entryId)) {

			// Add entry

			BJEntryServiceUtil.addEntry(name, content, verses, topicIds);
		}
		else {

			// Update entry

			BJEntryServiceUtil.updateEntry(
				entryId, name, content, verses, topicIds);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}