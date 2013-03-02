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
import com.liferay.portlet.blogs.LinkNameException;
import com.liferay.portlet.blogs.LinkURLException;
import com.liferay.portlet.blogs.NoSuchLinkException;
import com.liferay.portlet.blogs.model.BlogsLink;
import com.liferay.portlet.blogs.service.spring.BlogsLinkServiceUtil;
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
 * <a href="EditLinkAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class EditLinkAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editLink(req);

				_updateLink(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof LinkNameException ||
					e instanceof LinkURLException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.blogs.edit_link");
				}
				else if (e != null &&
						 e instanceof NoSuchLinkException ||
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
				_deleteLink(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchLinkException ||
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
				_editLink(req);

				setForward(req, "portlet.blogs.edit_link");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchLinkException ||
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
			setForward(req, "portlet.blogs.edit_link");
		}
	}

	private void _deleteLink(ActionRequest req, ActionResponse res)
		throws Exception {

		String linkId = ParamUtil.getString(req, "link_id");

		BlogsLinkServiceUtil.deleteLink(linkId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editLink(ActionRequest req) throws Exception {
		String linkId = ParamUtil.getString(req, "link_id");

		BlogsLink link = null;

		try {
			link = BlogsLinkServiceUtil.getLink(linkId);
		}
		catch (NoSuchLinkException nsce) {
		}

		req.setAttribute(WebKeys.BLOGS_LINK, link);
	}

	private void _updateLink(ActionRequest req, ActionResponse res)
		throws Exception {

		String linkId = ParamUtil.getString(req, "link_id");

		String name = ParamUtil.getString(req, "link_name");
		String url = ParamUtil.getString(req, "link_url");

		if (Validator.isNull(linkId)) {

			// Add link

			BlogsLinkServiceUtil.addLink(name, url);
		}
		else {

			// Update link

			BlogsLinkServiceUtil.updateLink(linkId, name, url);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}