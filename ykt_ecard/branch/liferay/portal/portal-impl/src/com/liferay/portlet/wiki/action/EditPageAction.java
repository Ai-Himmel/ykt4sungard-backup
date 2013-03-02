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

package com.liferay.portlet.wiki.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portlet.tags.TagsEntryException;
import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.NoSuchPageException;
import com.liferay.portlet.wiki.PageContentException;
import com.liferay.portlet.wiki.PageTitleException;
import com.liferay.portlet.wiki.service.WikiPageServiceUtil;
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
 * <a href="EditPageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditPageAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updatePage(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deletePage(req);
			}
			else if (cmd.equals(Constants.REVERT)) {
				revertPage(req);
			}

			if (Validator.isNotNull(cmd)) {
				sendRedirect(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchNodeException ||
				e instanceof NoSuchPageException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.wiki.error");
			}
			else if (e instanceof PageContentException ||
					 e instanceof PageTitleException) {

				SessionErrors.add(req, e.getClass().getName());
			}
			else if (e instanceof TagsEntryException) {
				SessionErrors.add(req, e.getClass().getName(), e);
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
			ActionUtil.getNode(req);
			ActionUtil.getPage(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchNodeException ||
				e instanceof NoSuchPageException ||
				e instanceof PageTitleException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.wiki.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(getForward(req, "portlet.wiki.edit_page"));
	}

	protected void deletePage(ActionRequest req) throws Exception {
		long nodeId = ParamUtil.getLong(req, "nodeId");
		String title = ParamUtil.getString(req, "title");

		WikiPageServiceUtil.deletePage(nodeId, title);
	}

	protected void revertPage(ActionRequest req) throws Exception {
		long nodeId = ParamUtil.getLong(req, "nodeId");
		String title = ParamUtil.getString(req, "title");
		double version = ParamUtil.getDouble(req, "version");

		WikiPageServiceUtil.revertPage(nodeId, title, version);
	}

	protected void updatePage(ActionRequest req) throws Exception {
		long nodeId = ParamUtil.getLong(req, "nodeId");
		String title = ParamUtil.getString(req, "title");

		String content = ParamUtil.getString(req, "content");
		String format = ParamUtil.getString(req, "format");

		String[] tagsEntries = StringUtil.split(
			ParamUtil.getString(req, "tagsEntries"));

		WikiPageServiceUtil.updatePage(
			nodeId, title, content, format, tagsEntries);
	}

}