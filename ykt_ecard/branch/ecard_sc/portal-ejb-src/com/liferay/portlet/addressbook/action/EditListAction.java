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

package com.liferay.portlet.addressbook.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.addressbook.ListNameException;
import com.liferay.portlet.addressbook.model.ABList;
import com.liferay.portlet.addressbook.service.spring.ABContactServiceUtil;
import com.liferay.portlet.addressbook.service.spring.ABListServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import java.util.ArrayList;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditListAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class EditListAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_updateList(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof ListNameException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.address_book.edit_list");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals(Constants.DELETE))) {
			try {
				_deleteList(req, res);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else {
			setForward(req, "portlet.address_book.edit_list");
		}
	}

	private void _deleteList(ActionRequest req, ActionResponse res)
		throws Exception {

		String listId = req.getParameter("list_id");

		ABListServiceUtil.deleteList(listId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateList(ActionRequest req, ActionResponse res)
		throws Exception {

		String listId = req.getParameter("list_id");

		String name = ParamUtil.getString(req, "list_name");
		String[] contactIds = StringUtil.split(
			ParamUtil.getString(req, "contact_ids"));

		List contacts = new ArrayList();

		for (int i = 0; i < contactIds.length; i++) {
			contacts.add(ABContactServiceUtil.getContact(contactIds[i]));
		}

		if (Validator.isNull(listId)) {

			// Add list

			ABList list = ABListServiceUtil.addList(name);
			ABListServiceUtil.setContacts(list.getListId(), contacts);
		}
		else {

			// Update list

			ABListServiceUtil.updateList(listId, name);
			ABListServiceUtil.setContacts(listId, contacts);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}