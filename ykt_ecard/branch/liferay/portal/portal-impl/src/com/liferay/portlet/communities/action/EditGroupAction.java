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

package com.liferay.portlet.communities.action;

import com.liferay.portal.DuplicateGroupException;
import com.liferay.portal.GroupFriendlyURLException;
import com.liferay.portal.GroupNameException;
import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.RequiredGroupException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.GroupServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.LiveUsers;
import com.liferay.portal.util.PortalUtil;
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
 * <a href="EditGroupAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditGroupAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateGroup(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteGroup(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchGroupException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.communities.error");
			}
			else if (e instanceof DuplicateGroupException ||
					 e instanceof GroupFriendlyURLException ||
					 e instanceof GroupNameException ||
					 e instanceof RequiredGroupException) {

				SessionErrors.add(req, e.getClass().getName(), e);

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
			ActionUtil.getGroup(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchGroupException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.communities.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.communities.edit_community"));
	}

	protected void deleteGroup(ActionRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");

		GroupServiceUtil.deleteGroup(groupId);

		LiveUsers.deleteGroup(groupId);
	}

	protected void updateGroup(ActionRequest req) throws Exception {
		long userId = PortalUtil.getUserId(req);

		long groupId = ParamUtil.getLong(req, "groupId");

		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");
		int type = ParamUtil.getInteger(req, "type");
		String friendlyURL = ParamUtil.getString(req, "friendlyURL");
		boolean active = ParamUtil.getBoolean(req, "active");

		if (groupId <= 0) {

			// Add group

			Group group = GroupServiceUtil.addGroup(
				name, description, type, friendlyURL, active);

			LiveUsers.joinGroup(userId, group.getGroupId());
		}
		else {

			// Update group

			GroupServiceUtil.updateGroup(
				groupId, name, description, type, friendlyURL, active);
		}
	}

}