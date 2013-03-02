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

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.model.Content;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.JS;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.mail.JavaMailUtil;

import java.util.Enumeration;

import javax.mail.BodyPart;
import javax.mail.Header;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMultipart;

import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ComposeMessageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class ComposeMessageAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if (cmd == null) {
			try {
				ActionUtil.getAttachments(req);

				return mapping.findForward("portlet.mail.compose_message");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else {
			try {
				ActionUtil.getMessage(req);

				_updateMessage(req);

				ActionUtil.getAttachments(req);

				return mapping.findForward("portlet.mail.compose_message");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
	}

	private void _updateMessage(RenderRequest req) throws Exception {
		PortletSession ses = req.getPortletSession();

		PortletPreferences prefs = req.getPreferences();

		// Message model

		com.liferay.portlet.mail.model.Message msgModel =
			new com.liferay.portlet.mail.model.Message(req, prefs);

		// Do not use Rich Text Format during reply

		//msgModel.setHTMLFormat(false);

		// Message

		Message msg = (Message)req.getAttribute(WebKeys.MAIL_MESSAGE);

		// Clone message

		Message newMsg = MailUtil.getNewMessage();

		Enumeration enu = msg.getAllHeaders();

		while (enu.hasMoreElements()) {
			Header header = (Header)enu.nextElement();

			newMsg.addHeader(header.getName(), header.getValue());
		}

		newMsg.setFrom((msg.getFrom())[0]);

		String subject = msg.getSubject();
		if (Validator.isNull(subject)) {
			subject = "";
		}

		String cmd = req.getParameter(Constants.CMD);

		if (cmd.equals("forward")) {
			newMsg.setSubject("FWD: " + subject);
		}
		else if ((cmd.equals("reply")) || (cmd.equals("reply_all"))) {
			newMsg.setSubject("RE: " + subject);
		}
		else if (cmd.equals("drafts")) {
			newMsg.setSubject(subject);
		}

		FastStringBuffer msgBody = new FastStringBuffer();

		String signature = prefs.getValue("signature", StringPool.BLANK);

		if ((Validator.isNotNull(signature)) &&
			(!cmd.equals("drafts"))) {

			signature = JS.decodeURIComponent(signature);

			if (msgModel.isHTMLFormat()) {
				msgBody.append("<br><br>");
				msgBody.append(StringUtil.replace(signature, "\n", "<br>"));
				msgBody.append("<br><br><br>");
			}
			else {
				msgBody.append("\n\n\n");
				msgBody.append(signature);
				msgBody.append("\n\n\n\n");
			}
		}

		boolean includeOriginal = GetterUtil.getBoolean(
			prefs.getValue("include-original", StringPool.BLANK));

		int originalTextIndicator = GetterUtil.getInteger(
			prefs.getValue("original-text-indicator", StringPool.BLANK));

		if (includeOriginal && (!cmd.equals("drafts"))) {
			if ((originalTextIndicator == 1) ||
				(originalTextIndicator == 2)) {

				msgBody.append("-----Original Message-----");

				if (msgModel.isHTMLFormat()) {
					msgBody.append("<br>");
				}
				else {
					msgBody.append("\n");
				}
			}

			// Must make text locale sensitive

			if (msg.getFrom() != null) {
				msgBody.append("From: ");
				msgBody.append(JavaMailUtil.toUnicodeString(msg.getFrom()));

				if (msgModel.isHTMLFormat()) {
					msgBody.append("<br>");
				}
				else {
					msgBody.append("\n");
				}
			}

			if (msg.getRecipients(Message.RecipientType.TO) != null) {
				msgBody.append("To: ");
				msgBody.append(InternetAddress.toString(
					msg.getRecipients(Message.RecipientType.TO)));

				if (msgModel.isHTMLFormat()) {
					msgBody.append("<br>");
				}
				else {
					msgBody.append("\n");
				}
			}

			if (msg.getRecipients(Message.RecipientType.CC) != null) {
				msgBody.append("CC: ");
				msgBody.append(InternetAddress.toString(
					msg.getRecipients(Message.RecipientType.CC)));

				if (msgModel.isHTMLFormat()) {
					msgBody.append("<br>");
				}
				else {
					msgBody.append("\n");
				}
			}

			//if (msg.getSubject() != null) {
				msgBody.append("Subject: ");
				msgBody.append(subject);

				if (msgModel.isHTMLFormat()) {
					msgBody.append("<br>");
				}
				else {
					msgBody.append("\n");
				}
			//}

			if (msg.getSentDate() != null) {
				msgBody.append("Date: ");
				msgBody.append(msg.getSentDate());

				if (msgModel.isHTMLFormat()) {
					msgBody.append("<br><br>");
				}
				else {
					msgBody.append("\n\n");
				}
			}
		}

		if (includeOriginal || cmd.equals("forward") ||
			cmd.equals("drafts")) {

			Content c = MailUtil.getContent(msg);

			String bodyText = null;
			String quotedBodyText = null;

			if (c != null) {
				bodyText = c.getText();
			}

			if (msgModel.isHTMLFormat()) {
				bodyText = StringUtil.replace(bodyText, "\n", "<br>");
			}

			quotedBodyText =
				MailUtil.addQuote(bodyText, msgModel.isHTMLFormat());

			try {
				Object content = msg.getContent();

				if (content instanceof Multipart) {
					MimeBodyPart defaultBodyPart = new MimeBodyPart();
					defaultBodyPart.setText("");

					Multipart newMultipart = new MimeMultipart();
					newMultipart.addBodyPart(defaultBodyPart);

					// Do not set attachments in reply

					if (!cmd.startsWith("reply")) {
						Multipart multipart = (Multipart)content;

						for (int i = 0; i < multipart.getCount(); i++) {
							BodyPart part = multipart.getBodyPart(i);

							String fileName = part.getFileName();

							// FIX

							if (fileName != null) {
								newMultipart.addBodyPart(part);
							}
						}
					}

					newMsg.setContent(newMultipart);

					if (c.getType().equals(Constants.TEXT_PLAIN)) {
						if ((originalTextIndicator == 2) &&
							(!cmd.equals("drafts"))) {

							msgBody.append(quotedBodyText);
						}
						else {
							msgBody.append(bodyText);
						}
					}
					else {
						msgBody.append(bodyText);
					}
				}
				else {
					Multipart multipart = new MimeMultipart();

					if (c.getType().equals(Constants.TEXT_PLAIN)) {
						if ((originalTextIndicator == 2) &&
							(!cmd.equals("drafts"))) {

							msgBody.append(quotedBodyText);
						}
						else {
							msgBody.append(bodyText);
						}
					}
					else {
						msgBody.append(c.getText());
					}

					BodyPart bodyPart = new MimeBodyPart();
					bodyPart.setText(msgBody.toString());
					multipart.addBodyPart(bodyPart);

					newMsg.setContent(multipart);
				}
			}
			catch (MessagingException me) {
				_log.error(me);
			}
		}
		else {

			// Workaround for a bug with JavaMail that occurs when users reply
			// to an email but have preferences set to not include the original
			// email

			Multipart multipart = new MimeMultipart();

			BodyPart bodyPart = new MimeBodyPart();
			bodyPart.setText(msgBody.toString());
			multipart.addBodyPart(bodyPart);

			newMsg.setContent(multipart);
		}

		// Update message model

		msgModel.setMessageType(cmd);
		msgModel.setParentFolder(req.getParameter("folder_name"));
		msgModel.setParentNumber(req.getParameter("msg_num"));

		if (cmd.equals("reply")) {
			InternetAddress from = ((InternetAddress[])newMsg.getFrom())[0];
			msgModel.setTo(from.toUnicodeString());
		}
		else if (cmd.equals("reply_all")) {
			InternetAddress from = ((InternetAddress[])newMsg.getFrom())[0];

			String to = InternetAddress.toString(
				msg.getRecipients(Message.RecipientType.TO));

			if (Validator.isNotNull(to)) {
				msgModel.setTo(from.toUnicodeString() + ", " + to);
			}
			else {
				msgModel.setTo(from.toUnicodeString());
			}

			String cc = InternetAddress.toString(
				msg.getRecipients(Message.RecipientType.CC));

			if (Validator.isNotNull(cc)) {
				msgModel.setCc(cc);
			}
		}
		else if (cmd.equals("drafts")) {
			if (msg.getRecipients(Message.RecipientType.TO) != null) {
				msgModel.setTo(InternetAddress.toString(
					msg.getRecipients(Message.RecipientType.TO)));
			}

			if (msg.getRecipients(Message.RecipientType.CC) != null) {
				msgModel.setCc(InternetAddress.toString(
					msg.getRecipients(Message.RecipientType.CC)));
			}

			if (msg.getRecipients(Message.RecipientType.BCC) != null) {
				msgModel.setBcc(InternetAddress.toString(
					msg.getRecipients(Message.RecipientType.BCC)));
			}

			msgModel.setDraft(true);
			msgModel.setMessage(msg);
		}

		if (newMsg.getSubject() != null) {
			msgModel.setSubject(newMsg.getSubject());
		}

		msgModel.setBody(msgBody.toString());

		ses.setAttribute(
			WebKeys.MAIL_MESSAGE, newMsg, PortletSession.APPLICATION_SCOPE);
		ses.setAttribute(
			WebKeys.MAIL_MESSAGE_MODEL, msgModel,
			PortletSession.APPLICATION_SCOPE);

		req.setAttribute(WebKeys.MAIL_MESSAGE, null);
	}

	private static final Log _log =
		LogFactory.getLog(ComposeMessageAction.class);

}