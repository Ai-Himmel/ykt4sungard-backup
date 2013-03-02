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

package com.liferay.portlet.messageboards.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.messageboards.NoSuchTopicException;
import com.liferay.portlet.messageboards.TopicNameException;
import com.liferay.portlet.messageboards.TopicReadRolesException;
import com.liferay.portlet.messageboards.TopicWriteRolesException;
import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;
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
 * <a href="EditTopicAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class EditTopicAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			ActionUtil.getTopic(req);
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof NoSuchTopicException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.message_boards.error");
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
				_updateTopic(config, req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.message_boards.error");
				}
				else if (e != null &&
						 e instanceof TopicNameException ||
						 e instanceof TopicReadRolesException ||
						 e instanceof TopicWriteRolesException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.message_boards.edit_topic");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteTopic(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTopicException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.message_boards.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.message_boards.edit_topic");
		}
	}

	private void _deleteTopic(ActionRequest req, ActionResponse res)
		throws Exception {

		String topicId = ParamUtil.getString(req, "topic_id");

		MBTopicServiceUtil.deleteTopic(topicId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateTopic(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String topicId = ParamUtil.getString(req, "topic_id");

		String readRoles = ParamUtil.getString(req, "topic_rr");
		String writeRoles = ParamUtil.getString(req, "topic_wr");

		String name = ParamUtil.getString(req, "topic_name");
		String description = ParamUtil.getString(req, "topic_desc");

		if (Validator.isNull(topicId)) {

			// Add topic

			MBTopicServiceUtil.addTopic(
				config.getPortletName(), PortalUtil.getPortletGroupId(req),
				readRoles, writeRoles, name, description);
		}
		else {

			// Update topic

			MBTopicServiceUtil.updateTopic(
				topicId, readRoles, writeRoles, name, description);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}