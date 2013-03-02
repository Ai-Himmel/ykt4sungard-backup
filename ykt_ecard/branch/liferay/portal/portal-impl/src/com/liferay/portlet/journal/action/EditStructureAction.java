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

package com.liferay.portlet.journal.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.DuplicateStructureIdException;
import com.liferay.portlet.journal.NoSuchStructureException;
import com.liferay.portlet.journal.RequiredStructureException;
import com.liferay.portlet.journal.StructureDescriptionException;
import com.liferay.portlet.journal.StructureIdException;
import com.liferay.portlet.journal.StructureNameException;
import com.liferay.portlet.journal.StructureXsdException;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.service.JournalStructureServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditStructureAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditStructureAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateStructure(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteStructures(req);
			}

			if (Validator.isNotNull(cmd)) {
				sendRedirect(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchStructureException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.journal.error");
			}
			else if (e instanceof DuplicateStructureIdException ||
					 e instanceof RequiredStructureException ||
					 e instanceof StructureDescriptionException ||
					 e instanceof StructureIdException ||
					 e instanceof StructureNameException ||
					 e instanceof StructureXsdException) {

				SessionErrors.add(req, e.getClass().getName());

				if (e instanceof RequiredStructureException) {
					res.sendRedirect(ParamUtil.getString(req, "redirect"));
				}
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
			String cmd = ParamUtil.getString(req, Constants.CMD);

			if (!cmd.equals(Constants.ADD)) {
				ActionUtil.getStructure(req);
			}
		}
		catch (NoSuchStructureException nsse) {

			// Let this slide because the user can manually input a structure id
			// for a new structure that does not yet exist.

		}
		catch (Exception e) {
			if (//e instanceof NoSuchStructureException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.journal.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.journal.edit_structure"));
	}

	protected void deleteStructures(ActionRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");

		String[] deleteStructureIds = StringUtil.split(
			ParamUtil.getString(req, "deleteStructureIds"));

		for (int i = 0; i < deleteStructureIds.length; i++) {
			JournalStructureServiceUtil.deleteStructure(
				groupId, deleteStructureIds[i]);

			JournalUtil.removeRecentStructure(req, deleteStructureIds[i]);
		}
	}

	protected void updateStructure(ActionRequest req) throws Exception {
		String cmd = ParamUtil.getString(req, Constants.CMD);

		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long groupId = ParamUtil.getLong(req, "groupId");

		String structureId = ParamUtil.getString(req, "structureId");
		boolean autoStructureId = ParamUtil.getBoolean(req, "autoStructureId");

		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");
		String xsd = ParamUtil.getString(req, "xsd");

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		JournalStructure structure = null;

		if (cmd.equals(Constants.ADD)) {

			// Add structure

			structure = JournalStructureServiceUtil.addStructure(
				structureId, autoStructureId, layout.getPlid(), name,
				description, xsd, communityPermissions, guestPermissions);
		}
		else {

			// Update structure

			structure = JournalStructureServiceUtil.updateStructure(
				groupId, structureId, name, description, xsd);
		}

		// Recent structures

		JournalUtil.addRecentStructure(req, structure);
	}

}