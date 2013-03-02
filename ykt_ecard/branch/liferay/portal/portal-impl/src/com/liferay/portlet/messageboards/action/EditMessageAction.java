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
import com.liferay.portal.captcha.CaptchaTextException;
import com.liferay.portal.captcha.CaptchaUtil;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ObjectValuePair;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
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
import com.liferay.portlet.tags.TagsEntryException;
import com.liferay.util.FileUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.util.ArrayList;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditMessageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditMessageAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateMessage(req, res);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteMessage(req);
			}
			else if (cmd.equals(Constants.SUBSCRIBE)) {
				subscribeMessage(req);
			}
			else if (cmd.equals(Constants.UNSUBSCRIBE)) {
				unsubscribeMessage(req);
			}

			if (cmd.equals(Constants.DELETE) ||
				cmd.equals(Constants.SUBSCRIBE) ||
				cmd.equals(Constants.UNSUBSCRIBE)) {

				sendRedirect(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchMessageException ||
				e instanceof PrincipalException ||
				e instanceof RequiredMessageException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.message_boards.error");
			}
			else if (e instanceof CaptchaTextException ||
					 e instanceof FileNameException ||
					 e instanceof FileSizeException ||
					 e instanceof MessageBodyException ||
					 e instanceof MessageSubjectException) {

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
			ActionUtil.getMessage(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchMessageException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.message_boards.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.message_boards.edit_message"));
	}

	protected void deleteMessage(ActionRequest req) throws Exception {
		long messageId = ParamUtil.getLong(req, "messageId");

		MBMessageServiceUtil.deleteMessage(messageId);
	}

	protected void subscribeMessage(ActionRequest req) throws Exception {
		long messageId = ParamUtil.getLong(req, "messageId");

		MBMessageServiceUtil.subscribeMessage(messageId);
	}

	protected void unsubscribeMessage(ActionRequest req) throws Exception {
		long messageId = ParamUtil.getLong(req, "messageId");

		MBMessageServiceUtil.unsubscribeMessage(messageId);
	}

	protected void updateMessage(ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		PortletPreferences prefs = req.getPreferences();

		long messageId = ParamUtil.getLong(req, "messageId");

		long categoryId = ParamUtil.getLong(req, "categoryId");
		long threadId = ParamUtil.getLong(req, "threadId");
		long parentMessageId = ParamUtil.getLong(req, "parentMessageId");
		String subject = ParamUtil.getString(req, "subject");
		String body = ParamUtil.getString(req, "body");
		boolean attachments = ParamUtil.getBoolean(req, "attachments");

		List files = new ArrayList();

		if (attachments) {
			UploadPortletRequest uploadReq =
				PortalUtil.getUploadPortletRequest(req);

			for (int i = 1; i <= 5; i++) {
				File file = uploadReq.getFile("msgFile" + i);
				String fileName = uploadReq.getFileName("msgFile" + i);
				byte[] bytes = FileUtil.getBytes(file);

				if ((bytes != null) && (bytes.length > 0)) {
					ObjectValuePair ovp = new ObjectValuePair(fileName, bytes);

					files.add(ovp);
				}
			}
		}

		boolean anonymous = ParamUtil.getBoolean(req, "anonymous");
		double priority = ParamUtil.getDouble(req, "priority");

		String[] tagsEntries = StringUtil.split(
			ParamUtil.getString(req, "tagsEntries"));

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		MBMessage message = null;

		if (messageId <= 0) {
			CaptchaUtil.check(req);

			if (threadId <= 0) {

				// Post new thread

				message = MBMessageServiceUtil.addMessage(
					categoryId, subject, body, files, anonymous, priority,
					tagsEntries, prefs, communityPermissions, guestPermissions,
				    themeDisplay);
			}
			else {

				// Post reply

				message = MBMessageServiceUtil.addMessage(
					categoryId, threadId, parentMessageId, subject, body, files,
					anonymous, priority, tagsEntries, prefs,
					communityPermissions, guestPermissions, themeDisplay);
			}
		}
		else {

			// Update message

			message = MBMessageServiceUtil.updateMessage(
				messageId, subject, body, files, priority, tagsEntries, prefs,
				themeDisplay);
		}

		PortletURL portletURL = ((ActionResponseImpl)res).createRenderURL();

		portletURL.setParameter(
			"struts_action", "/message_boards/view_message");
		portletURL.setParameter(
			"messageId", String.valueOf(message.getMessageId()));

		res.sendRedirect(portletURL.toString());
	}

}