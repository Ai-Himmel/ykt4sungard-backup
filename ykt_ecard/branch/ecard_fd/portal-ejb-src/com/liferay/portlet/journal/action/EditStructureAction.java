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

package com.liferay.portlet.journal.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.DuplicateStructureIdException;
import com.liferay.portlet.journal.NoSuchStructureException;
import com.liferay.portlet.journal.RequiredStructureException;
import com.liferay.portlet.journal.StructureDescriptionException;
import com.liferay.portlet.journal.StructureIdException;
import com.liferay.portlet.journal.StructureNameException;
import com.liferay.portlet.journal.StructureXsdException;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.service.spring.JournalStructureServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditStructureAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class EditStructureAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			_editStructure(req);
		}
		catch (Exception e) {
			if (e != null &&
				//e instanceof NoSuchStructureException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.journal.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			if (cmd.equals(Constants.ADD)) {
				req.removeAttribute(WebKeys.JOURNAL_STRUCTURE);
			}

			try {
				_updateStructure(config, req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchStructureException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else if (e != null &&
						 e instanceof DuplicateStructureIdException ||
						 e instanceof StructureDescriptionException ||
						 e instanceof StructureIdException ||
						 e instanceof StructureNameException ||
						 e instanceof StructureXsdException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.edit_structure");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteStructure(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchStructureException ||
					e instanceof PrincipalException ||
					e instanceof RequiredStructureException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.journal.edit_structure");
		}
	}

	private void _deleteStructure(ActionRequest req, ActionResponse res)
		throws Exception {

		String structureId = ParamUtil.getString(req, "structure_id");

		JournalStructureServiceUtil.deleteStructure(structureId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editStructure(ActionRequest req) throws Exception {
		String structureId = ParamUtil.getString(req, "structure_id");

		// Find structure

		JournalStructure structure = null;

		if (Validator.isNotNull(structureId)) {
			structure = JournalStructureServiceUtil.getStructure(structureId);
		}

		req.setAttribute(WebKeys.JOURNAL_STRUCTURE, structure);

		JournalUtil.addRecentStructure(req, structure);
	}

	private void _updateStructure(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		String structureId = ParamUtil.getString(req, "structure_id");
		boolean autoStructureId = ParamUtil.get(
			req, "auto_structure_id", false);

		String name = ParamUtil.getString(req, "structure_name");
		String description = ParamUtil.getString(req, "structure_desc");
		String xsd = ParamUtil.getString(req, "structure_xsd");

		JournalStructure structure = null;

		if (cmd.equals(Constants.ADD)) {

			// Add structure

			structure = JournalStructureServiceUtil.addStructure(
				structureId, autoStructureId, config.getPortletName(),
				PortalUtil.getPortletGroupId(req), name, description, xsd);
		}
		else {

			// Update structure

			structure = JournalStructureServiceUtil.updateStructure(
				structureId, name, description, xsd);
		}

		// Session messages

		SessionMessages.add(req, "structure_saved");

		// Recent structures

		JournalUtil.addRecentStructure(req, structure);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}