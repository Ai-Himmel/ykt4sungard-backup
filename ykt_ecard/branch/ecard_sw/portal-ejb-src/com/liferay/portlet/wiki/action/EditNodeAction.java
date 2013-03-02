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

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.NodeNameException;
import com.liferay.portlet.wiki.NodeReadRolesException;
import com.liferay.portlet.wiki.NodeWriteRolesException;
import com.liferay.portlet.wiki.service.spring.WikiNodeServiceUtil;
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
 * <a href="EditNodeAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class EditNodeAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			ActionUtil.getNode(req);
		}
		catch (Exception e) {
			if (e != null &&
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

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_updateNode(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchNodeException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.wiki.error");
				}
				else if (e != null &&
						 e instanceof NodeNameException ||
						 e instanceof NodeReadRolesException ||
						 e instanceof NodeWriteRolesException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.wiki.edit_node");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteNode(req, res);
			}
			catch (Exception e) {
				if (e != null &&
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
		else {
			setForward(req, "portlet.wiki.edit_node");
		}
	}

	private void _deleteNode(ActionRequest req, ActionResponse res)
		throws Exception {

		String nodeId = ParamUtil.getString(req, "node_id");

		WikiNodeServiceUtil.deleteNode(nodeId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateNode(ActionRequest req, ActionResponse res)
		throws Exception {

		String nodeId = ParamUtil.getString(req, "node_id");

		String readRoles = ParamUtil.getString(req, "node_rr");
		String writeRoles = ParamUtil.getString(req, "node_wr");

		String name = ParamUtil.getString(req, "node_name");
		String description = ParamUtil.getString(req, "node_desc");
		boolean sharing = ParamUtil.get(req, "node_sharing", true);

		if (Validator.isNull(nodeId)) {

			// Add node

			WikiNodeServiceUtil.addNode(
				readRoles, writeRoles, name, description, sharing);
		}
		else {

			// Update node

			WikiNodeServiceUtil.updateNode(
				nodeId, readRoles, writeRoles, name, description, sharing);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}