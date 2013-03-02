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
import com.liferay.portlet.blogs.CategoryNameException;
import com.liferay.portlet.blogs.NoSuchCategoryException;
import com.liferay.portlet.blogs.model.BlogsCategory;
import com.liferay.portlet.blogs.service.spring.BlogsCategoryServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditCategoryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class EditCategoryAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editCategory(req);

				_updateCategory(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof CategoryNameException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.edit_category");
				}
				else if (e != null &&
						 e instanceof NoSuchCategoryException ||
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
				_deleteCategory(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchCategoryException ||
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
				_editCategory(req);

				setForward(req, "portlet.blogs.edit_category");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchCategoryException ||
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
			setForward(req, "portlet.blogs.edit_category");
		}
	}

	private void _deleteCategory(ActionRequest req, ActionResponse res)
		throws Exception {

		String categoryId = ParamUtil.getString(req, "category_id");

		BlogsCategoryServiceUtil.deleteCategory(categoryId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editCategory(ActionRequest req) throws Exception {
		String categoryId = ParamUtil.getString(req, "category_id");

		BlogsCategory category = null;

		try {
			category = BlogsCategoryServiceUtil.getCategory(categoryId);
		}
		catch (NoSuchCategoryException nsce) {
		}

		req.setAttribute(WebKeys.BLOGS_CATEGORY, category);
	}

	private void _updateCategory(ActionRequest req, ActionResponse res)
		throws Exception {

		String categoryId = ParamUtil.getString(req, "category_id");

		String name = ParamUtil.getString(req, "category_name");

		if (Validator.isNull(categoryId)) {

			// Add category

			BlogsCategoryServiceUtil.addCategory(name);
		}
		else {

			// Update category

			BlogsCategoryServiceUtil.updateCategory(categoryId, name);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}