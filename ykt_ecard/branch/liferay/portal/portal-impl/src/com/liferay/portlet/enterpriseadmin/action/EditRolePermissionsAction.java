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

import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.security.permission.ResourceActionsUtil;
import com.liferay.portal.security.permission.comparator.ActionComparator;
import com.liferay.portal.service.PermissionServiceUtil;
import com.liferay.portal.service.RoleServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditRolePermissionsAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class EditRolePermissionsAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals("actions")) {
				updateActions(req, res);
			}
			else if (cmd.equals("delete_permission")) {
				deletePermission(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchRoleException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
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
			ActionUtil.getRole(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchRoleException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_role_permissions"));
	}

	protected void deletePermission(ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long roleId = ParamUtil.getLong(req, "roleId");
		long permissionId = ParamUtil.getLong(req, "permissionId");

		PermissionServiceUtil.unsetRolePermission(
			roleId, themeDisplay.getPortletGroupId(), permissionId);

		// Send redirect

		SessionMessages.add(req, "permissionDeleted");

		String redirect = ParamUtil.getString(req, "redirect");

		res.sendRedirect(redirect);
	}

	protected void updateActions(ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long roleId = ParamUtil.getLong(req, "roleId");

		String portletResource = ParamUtil.getString(req, "portletResource");
		String[] modelResources = StringUtil.split(
			ParamUtil.getString(req, "modelResources"));

		Map resourceActionsMap = new HashMap();

		if (Validator.isNotNull(portletResource)) {
			resourceActionsMap.put(
				portletResource,
				ResourceActionsUtil.getResourceActions(
					themeDisplay.getCompanyId(), portletResource, null));
		}

		for (int i = 0; i < modelResources.length; i++) {
			resourceActionsMap.put(
				modelResources[i],
				ResourceActionsUtil.getResourceActions(
					themeDisplay.getCompanyId(), null, modelResources[i]));
		}

		Iterator itr = resourceActionsMap.keySet().iterator();

		while (itr.hasNext()) {
			String selResource = (String)itr.next();

			List actions = (List)resourceActionsMap.get(selResource);

			Collections.sort(
				actions,
				new ActionComparator(
					themeDisplay.getCompanyId(), themeDisplay.getLocale()));

			Role role = RoleServiceUtil.getRole(roleId);

			for (int i = 0; i < actions.size(); i++) {
				String actionId = (String)actions.get(i);

				int scope = ParamUtil.getInteger(
					req, "scope" + selResource + actionId);

				if (scope == ResourceImpl.SCOPE_COMPANY) {
					PermissionServiceUtil.setRolePermission(
						roleId, themeDisplay.getPortletGroupId(), selResource,
						scope, String.valueOf(themeDisplay.getCompanyId()),
						actionId);
				}
				else if (scope == ResourceImpl.SCOPE_GROUP) {
					if ((role.getType() == RoleImpl.TYPE_COMMUNITY) ||
						(role.getType() == RoleImpl.TYPE_ORGANIZATION)) {

						PermissionServiceUtil.setRolePermission(
							roleId, themeDisplay.getPortletGroupId(),
							selResource, ResourceImpl.SCOPE_GROUP_TEMPLATE,
							String.valueOf(GroupImpl.DEFAULT_PARENT_GROUP_ID),
							actionId);
					}
					else {
						String[] groupIds = StringUtil.split(
							ParamUtil.getString(
								req, "groupIds" + selResource + actionId));

						if (groupIds.length == 0) {
							SessionErrors.add(req, "missingGroupIdsForAction");
							return;
						}

						groupIds = ArrayUtil.distinct(groupIds);

						PermissionServiceUtil.unsetRolePermissions(
							roleId, themeDisplay.getPortletGroupId(),
							selResource, ResourceImpl.SCOPE_GROUP, actionId);

						for (int j = 0; j < groupIds.length; j++) {
							PermissionServiceUtil.setRolePermission(
								roleId, themeDisplay.getPortletGroupId(),
								selResource, ResourceImpl.SCOPE_GROUP,
								groupIds[j], actionId);
						}
					}
				}
				else {

					// Remove company, group template, and group permissions

					PermissionServiceUtil.unsetRolePermissions(
						roleId, themeDisplay.getPortletGroupId(), selResource,
						ResourceImpl.SCOPE_COMPANY, actionId);

					PermissionServiceUtil.unsetRolePermissions(
						roleId, themeDisplay.getPortletGroupId(), selResource,
						ResourceImpl.SCOPE_GROUP_TEMPLATE, actionId);

					PermissionServiceUtil.unsetRolePermissions(
						roleId, themeDisplay.getPortletGroupId(), selResource,
						ResourceImpl.SCOPE_GROUP, actionId);
				}
			}
		}

		// Send redirect

		SessionMessages.add(req, "permissionsUpdated");

		String redirect =
			ParamUtil.getString(req, "redirect") + "&" + Constants.CMD + "=" +
				Constants.VIEW;

		res.sendRedirect(redirect);
	}

}