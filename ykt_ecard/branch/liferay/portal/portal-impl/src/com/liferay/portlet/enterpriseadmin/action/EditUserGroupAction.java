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

package com.liferay.portlet.enterpriseadmin.action;

import com.liferay.portal.DuplicateUserGroupException;
import com.liferay.portal.NoSuchUserGroupException;
import com.liferay.portal.RequiredUserGroupException;
import com.liferay.portal.UserGroupNameException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.UserGroupServiceUtil;
import com.liferay.portal.struts.PortletAction;
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
 * <a href="EditUserGroupAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class EditUserGroupAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateUserGroup(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteUserGroups(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof PrincipalException) {
				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof DuplicateUserGroupException ||
					 e instanceof NoSuchUserGroupException ||
					 e instanceof RequiredUserGroupException ||
					 e instanceof UserGroupNameException) {

				SessionErrors.add(req, e.getClass().getName());

				if (cmd.equals(Constants.DELETE)) {
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
			ActionUtil.getUserGroup(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchUserGroupException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_user_group"));
	}

	protected void deleteUserGroups(ActionRequest req) throws Exception {
		long[] deleteUserGroupIds = StringUtil.split(
			ParamUtil.getString(req, "deleteUserGroupIds"), 0L);

		for (int i = 0; i < deleteUserGroupIds.length; i++) {
			UserGroupServiceUtil.deleteUserGroup(deleteUserGroupIds[i]);
		}
	}

	protected void updateUserGroup(ActionRequest req) throws Exception {
		long userGroupId = ParamUtil.getLong(req, "userGroupId");

		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");

		if (userGroupId <= 0) {

			// Add user group

			UserGroupServiceUtil.addUserGroup(name, description);
		}
		else {

			// Update user group

			UserGroupServiceUtil.updateUserGroup(
				userGroupId, name, description);
		}
	}

}