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

package com.liferay.portlet.mail.action;

import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.mail.model.Attachment;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.List;

import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.Part;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class ActionUtil {

	public static void getAttachments(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getAttachments(httpReq);
	}

	public static void getAttachments(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getAttachments(httpReq);
	}

	public static void getAttachments(HttpServletRequest req) throws Exception {
		try {
			HttpSession ses = req.getSession();

			Message msg = (Message)req.getAttribute(WebKeys.MAIL_MESSAGE);

			if (msg == null) {
				msg = (Message)ses.getAttribute(WebKeys.MAIL_MESSAGE);
			}

			if (msg == null) {
				msg = MailUtil.getNewMessage();
				ses.setAttribute(WebKeys.MAIL_MESSAGE, msg);
			}

			Object content = msg.getContent();

			if (content instanceof Multipart) {
				Multipart multipart = (Multipart)content;

				List attachments = new ArrayList();

				double totalSize = 0.0;
				boolean overLimit = false;

				for (int i = 1; i < multipart.getCount(); i++) {
					Part part = multipart.getBodyPart(i);

					String fileName = part.getFileName();

					boolean defaultFileName = true;

					if (fileName == null) {
						defaultFileName = false;
						fileName = "message" + i + ".txt";
					}

					double size = 0.0;
					int availableSize = part.getInputStream().available();

					if (availableSize == 0) {
						size = (double)part.getSize();
					}
					else {
						size = (double)availableSize;
					}

					size = size * MailUtil.SIZE_DIFFERENTIAL;

					totalSize = totalSize + size;

					if (totalSize >= MailUtil.ATTACHMENTS_MAX_SIZE) {
						multipart.removeBodyPart(i);
						totalSize = totalSize - size;
						overLimit = true;
					}

					// Do not show attachments unless it has a default file name

					//if (defaultFileName) {
						attachments.add(
							new Attachment(i, fileName, size, defaultFileName));
					//}
				}

				req.setAttribute(WebKeys.MAIL_ATTACHMENTS, attachments);

				req.setAttribute(
					WebKeys.MAIL_ATTACHMENT_TOTAL_SIZE, new Double(totalSize));

				Boolean sesOverLimit = (Boolean)ses.getAttribute(
					WebKeys.MAIL_ATTACHMENT_OVER_LIMIT);

				if (sesOverLimit == null) {
					ses.setAttribute(
						WebKeys.MAIL_ATTACHMENT_OVER_LIMIT,
						new Boolean(overLimit));
				}
			}
		}
		catch (MessagingException me) {
			_log.error(me);
		}
	}

	public static void getMessage(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getMessage(httpReq);
	}

	public static void getMessage(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getMessage(httpReq);
	}

	public static void getMessage(HttpServletRequest req) throws Exception {
		String folderName = req.getParameter("folder_name");
		int msgNum = Integer.parseInt(req.getParameter("msg_num"));

		Folder folder = MailUtil.getFolder(req, folderName);

		PortletPreferences prefs = PortalUtil.getPreferences(req);

		Message[] messages = folder.getMessages();
		MailUtil.sort(folder.getName(), messages, prefs);

		int msgIndex = 0;

		try {
			msgIndex = Integer.parseInt(req.getParameter("msg_i"));
		}
		catch (NumberFormatException nfe) {

			// Cannot use binary search because message number ordering is
			// random

			for (int i = 0; i < messages.length; i++) {
				if (messages[i].getMessageNumber() == msgNum) {
					msgIndex = i;
					break;
				}
			}
		}

		int messageCount = folder.getMessageCount();

		if (messageCount <= 1) {
			req.setAttribute("next_msg_num_after_delete", "-1");
		}
		else if (msgIndex == 0) {
			req.setAttribute(
				"msg_next",
				Integer.toString(messages[1].getMessageNumber()));

			int msgNextNum = messages[1].getMessageNumber() - 1;

			if (messages[0].getMessageNumber() >
				messages[1].getMessageNumber()) {

				msgNextNum++;
			}

			req.setAttribute(
				"next_msg_num_after_delete", Integer.toString(msgNextNum));
		}
		else if (msgIndex == (messageCount - 1)) {
			req.setAttribute(
				"msg_previous",
				Integer.toString(messages[msgIndex - 1].getMessageNumber()));

			int msgNextNum = messages[msgIndex - 1].getMessageNumber() - 1;

			if (messages[msgIndex].getMessageNumber() >
				messages[msgIndex - 1].getMessageNumber()) {

				msgNextNum++;
			}

			req.setAttribute(
				"next_msg_num_after_delete", Integer.toString(msgNextNum));
		}
		else {
			req.setAttribute(
				"msg_previous",
				Integer.toString(messages[msgIndex - 1].getMessageNumber()));

			req.setAttribute(
				"msg_next",
				Integer.toString(messages[msgIndex + 1].getMessageNumber()));

			int msgNextNum = messages[msgIndex + 1].getMessageNumber() - 1;

			if (messages[msgIndex].getMessageNumber() >
				messages[msgIndex + 1].getMessageNumber()) {

				msgNextNum++;
			}

			req.setAttribute(
				"next_msg_num_after_delete", Integer.toString(msgNextNum));
		}

		req.setAttribute(WebKeys.MAIL_MESSAGE, folder.getMessage(msgNum));

		// Get message division id

		int messagesPerPage = GetterUtil.getInteger(prefs.getValue(
			"messages-per-page", StringPool.BLANK));

		int msgDiv = (int)Math.ceil(msgIndex / messagesPerPage);
		msgDiv++;

		req.setAttribute(WebKeys.MAIL_MESSAGE_DIV, Integer.toString(msgDiv));
	}

	public static void getMessageModel(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getMessageModel(httpReq);
	}

	public static void getMessageModel(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getMessageModel(httpReq);
	}

	public static void getMessageModel(HttpServletRequest req)
		throws Exception {

		HttpSession ses = req.getSession();

		String to = req.getParameter("msg_to");
		String cc = req.getParameter("msg_cc");
		String bcc = req.getParameter("msg_bcc");
		String subject = req.getParameter("msg_sub");
		String body = req.getParameter("msg_body");
		String returnReceipt = req.getParameter("msg_return_receipt_1");
		String htmlFormat = req.getParameter("html_cb_1");

		com.liferay.portlet.mail.model.Message msg =
			(com.liferay.portlet.mail.model.Message)
				ses.getAttribute(WebKeys.MAIL_MESSAGE_MODEL);

		if ((to != null) && (!to.equals("null"))) {
			msg.setTo(to);
		}

		if ((cc != null) && (!cc.equals("null"))) {
			msg.setCc(cc);
		}

		if ((bcc != null) && (!bcc.equals("null"))) {
			msg.setBcc(bcc);
		}

		if ((subject != null) && (!subject.equals("null"))) {
			msg.setSubject(subject);
		}

		if ((body != null) && (!body.equals("null"))) {
			msg.setBody(body);
		}

		if ((Validator.isNotNull(returnReceipt)) &&
			(returnReceipt.equals("on"))) {

			msg.setReturnReceipt(true);
		}
		else {
			msg.setReturnReceipt(false);
		}

		if ((Validator.isNotNull(htmlFormat)) && (htmlFormat.equals("on"))) {
			msg.setHTMLFormat(true);
		}
		else {
			msg.setReturnReceipt(false);
			msg.setHTMLFormat(false);
		}
	}

	private static final Log _log = LogFactory.getLog(ActionUtil.class);

}