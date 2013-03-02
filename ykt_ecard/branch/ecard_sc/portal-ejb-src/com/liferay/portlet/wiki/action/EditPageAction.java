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

package com.liferay.portlet.wiki.action;

import com.liferay.lock.DuplicateLockException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.NoSuchPageException;
import com.liferay.portlet.wiki.PageContentException;
import com.liferay.portlet.wiki.PageTitleException;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.spring.WikiPageServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class EditPageAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editPage(req);

				_updatePage(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof DuplicateLockException) {

					DuplicateLockException dle = (DuplicateLockException)e;

					SessionErrors.add(
						req, dle.getClass().getName(), dle.getLock());

					setForward(req, "portlet.wiki.error");
				}
				else if (e != null &&
						 e instanceof NoSuchNodeException ||
						 e instanceof PageContentException ||
						 e instanceof PageTitleException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.wiki.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.CANCEL)) {
			try {
				_cancelPage(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.wiki.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deletePage(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof DuplicateLockException) {

					DuplicateLockException dle = (DuplicateLockException)e;

					SessionErrors.add(
						req, dle.getClass().getName(), dle.getLock());

					setForward(req, "portlet.wiki.error");
				}
				else if (e != null &&
						 e instanceof NoSuchPageException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.wiki.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			try {
				ActionUtil.getNode(req);

				_editPage(req);

				setForward(req, "portlet.wiki.edit_page");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof DuplicateLockException) {

					DuplicateLockException dle = (DuplicateLockException)e;

					SessionErrors.add(
						req, dle.getClass().getName(), dle.getLock());

					setForward(req, "portlet.wiki.error");
				}
				else if (e != null &&
						 e instanceof NoSuchNodeException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.wiki.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
	}

	private void _cancelPage(ActionRequest req, ActionResponse res)
		throws Exception {

		String nodeId = ParamUtil.getString(req, "node_id");
		String title = ParamUtil.getString(req, "page_title");

		WikiPageServiceUtil.unlockPage(nodeId, title);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deletePage(ActionRequest req, ActionResponse res)
		throws Exception {

		String nodeId = ParamUtil.getString(req, "node_id");
		String title = ParamUtil.getString(req, "page_title");

		WikiPageServiceUtil.deletePage(nodeId, title);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editPage(ActionRequest req) throws Exception {
		String nodeId = ParamUtil.getString(req, "node_id");
		String title = ParamUtil.getString(req, "page_title");
		double version = ParamUtil.get(req, "page_version", 0.0);

		WikiPage page = WikiPageServiceUtil.lockPage(nodeId, title, version);

		req.setAttribute(WebKeys.WIKI_PAGE, page);
	}

	private void _updatePage(ActionRequest req, ActionResponse res)
		throws Exception {

		String nodeId = ParamUtil.getString(req, "node_id");
		String title = ParamUtil.getString(req, "page_title");

		String content = ParamUtil.getString(req, "page_content");
		String format = ParamUtil.get(
			req, "page_format", WikiPage.DEFAULT_FORMAT);

		// Update page

		WikiPageServiceUtil.updatePage(nodeId, title, content, format);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}