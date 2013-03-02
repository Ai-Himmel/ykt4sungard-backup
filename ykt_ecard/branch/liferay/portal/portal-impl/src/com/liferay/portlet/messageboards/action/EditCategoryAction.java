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

package com.liferay.portlet.messageboards.action;

import com.liferay.portal.captcha.CaptchaTextException;
import com.liferay.portal.captcha.CaptchaUtil;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.messageboards.CategoryNameException;
import com.liferay.portlet.messageboards.NoSuchCategoryException;
import com.liferay.portlet.messageboards.service.MBCategoryServiceUtil;
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
 * <a href="EditCategoryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditCategoryAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateCategory(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteCategory(req);
			}
			else if (cmd.equals(Constants.SUBSCRIBE)) {
				subscribeCategory(req);
			}
			else if (cmd.equals(Constants.UNSUBSCRIBE)) {
				unsubscribeCategory(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchCategoryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.message_boards.error");
			}
			else if (e instanceof CaptchaTextException ||
					 e instanceof CategoryNameException) {

				SessionErrors.add(req, e.getClass().getName());
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
			ActionUtil.getCategory(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchCategoryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.message_boards.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.message_boards.edit_category"));
	}

	protected void deleteCategory(ActionRequest req) throws Exception {
		long categoryId = ParamUtil.getLong(req, "categoryId");

		MBCategoryServiceUtil.deleteCategory(categoryId);
	}

	protected void subscribeCategory(ActionRequest req) throws Exception {
		long categoryId = ParamUtil.getLong(req, "categoryId");

		MBCategoryServiceUtil.subscribeCategory(categoryId);
	}

	protected void unsubscribeCategory(ActionRequest req) throws Exception {
		long categoryId = ParamUtil.getLong(req, "categoryId");

		MBCategoryServiceUtil.unsubscribeCategory(categoryId);
	}

	protected void updateCategory(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long categoryId = ParamUtil.getLong(req, "categoryId");

		long parentCategoryId = ParamUtil.getLong(req, "parentCategoryId");
		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");

		boolean mergeWithParentCategory = ParamUtil.getBoolean(
			req, "mergeWithParentCategory");

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (categoryId <= 0) {
			CaptchaUtil.check(req);

			// Add category

			MBCategoryServiceUtil.addCategory(
				layout.getPlid(), parentCategoryId, name, description,
				communityPermissions, guestPermissions);
		}
		else {

			// Update category

			MBCategoryServiceUtil.updateCategory(
				categoryId, parentCategoryId, name, description,
				mergeWithParentCategory);
		}
	}

}