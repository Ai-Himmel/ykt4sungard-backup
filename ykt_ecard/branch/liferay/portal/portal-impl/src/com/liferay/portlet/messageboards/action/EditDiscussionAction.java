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

import com.liferay.documentlibrary.FileNameException;
import com.liferay.documentlibrary.FileSizeException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.messageboards.MessageBodyException;
import com.liferay.portlet.messageboards.MessageSubjectException;
import com.liferay.portlet.messageboards.NoSuchMessageException;
import com.liferay.portlet.messageboards.RequiredMessageException;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.service.MBMessageServiceUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditDiscussionAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditDiscussionAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		ActionResponseImpl resImpl = (ActionResponseImpl)res;

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			String redirect = ParamUtil.getString(req, "redirect");

			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				MBMessage message = updateMessage(req);

				redirect +=
					"#" + resImpl.getNamespace() + "messageScroll" +
						message.getMessageId();
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteMessage(req);
			}

			sendRedirect(req, res, redirect);
		}
		catch (Exception e) {
			if (e instanceof NoSuchMessageException ||
				e instanceof PrincipalException ||
				e instanceof RequiredMessageException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.message_boards.error");
			}
			else if (e instanceof FileNameException ||
					 e instanceof FileSizeException ||
					 e instanceof MessageBodyException ||
					 e instanceof MessageSubjectException) {

				SessionErrors.add(req, e.getClass().getName());

				sendRedirect(req, res);
			}
			else {
				throw e;
			}
		}
	}

	protected void deleteMessage(ActionRequest req) throws Exception {
		long groupId = PortalUtil.getPortletGroupId(req);
		String className = ParamUtil.getString(req, "className");
		long classPK = ParamUtil.getLong(req, "classPK");

		long messageId = ParamUtil.getLong(req, "messageId");

		MBMessageServiceUtil.deleteDiscussionMessage(
			groupId, className, classPK, messageId);
	}

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	protected MBMessage updateMessage(ActionRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long groupId = PortalUtil.getPortletGroupId(req);
		String className = ParamUtil.getString(req, "className");
		long classPK = ParamUtil.getLong(req, "classPK");

		long messageId = ParamUtil.getLong(req, "messageId");

		long threadId = ParamUtil.getLong(req, "threadId");
		long parentMessageId = ParamUtil.getLong(req, "parentMessageId");
		String subject = ParamUtil.getString(req, "subject");
		String body = ParamUtil.getString(req, "body");

		MBMessage message = null;

		if (messageId <= 0) {

			// Add message

			message = MBMessageServiceUtil.addDiscussionMessage(
				groupId, className, classPK, threadId, parentMessageId, subject,
				body, themeDisplay);
		}
		else {

			// Update message

			message = MBMessageServiceUtil.updateDiscussionMessage(
				groupId, className, classPK, messageId, subject, body);
		}

		return message;
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;

}