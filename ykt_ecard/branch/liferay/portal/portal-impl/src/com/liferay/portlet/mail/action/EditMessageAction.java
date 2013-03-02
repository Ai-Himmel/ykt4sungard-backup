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

package com.liferay.portlet.mail.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.ContentTypeUtil;
import com.liferay.portal.util.DateFormats;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.RecipientException;
import com.liferay.portlet.mail.model.MailAttachment;
import com.liferay.portlet.mail.model.MailMessage;
import com.liferay.portlet.mail.model.RemoteMailAttachment;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.portlet.mail.util.multiaccount.MailAccount;
import com.liferay.portlet.mail.util.multiaccount.MailAccounts;
import com.liferay.util.FileUtil;
import com.liferay.util.Html;
import com.liferay.util.mail.InternetAddressUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.text.DateFormat;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.mail.internet.InternetAddress;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletRequest;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditMessageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ming-Gih Lam
 * @author 	Alexander Chow
 *
 */
public class EditMessageAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			completeMessage(req);

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof RecipientException) {
				SessionErrors.add(req, e.getClass().getName());
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

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		String cmd = ParamUtil.getString(req, Constants.CMD);

		PortletPreferences prefs = req.getPreferences();

		String folderId = ParamUtil.getString(req, "folderId");
		long messageId = ParamUtil.getLong(req, "messageId");

		String signature = prefs.getValue("signature", StringPool.BLANK);

		if (Validator.isNotNull(signature)) {
			signature = "<br />--<br />" + signature;
		}

		if (cmd.equals("forward") || cmd.startsWith("reply")) {
			MailUtil.setFolder(httpReq, folderId);

			MailMessage mailMessage = MailUtil.getMessage(httpReq, messageId);

			if (cmd.equals("forward")) {
				req.setAttribute(
					WebKeys.MAIL_MESSAGE_SUBJECT,
					"Fw: " + getSubject(mailMessage.getSubject(), "fw"));
				req.setAttribute(
					WebKeys.MAIL_MESSAGE_ATTACHMENTS,
					mailMessage.getRemoteAttachments());
			}
			else {
				String to = StringPool.BLANK;
				String cc = StringPool.BLANK;

				if (cmd.equals("replyAll")) {
					User user = PortalUtil.getUser(req);

					String emailAddress = user.getEmailAddress();

					to = InternetAddressUtil.toString(
						InternetAddressUtil.removeEntry(
							mailMessage.getTo(), emailAddress));

					cc = InternetAddressUtil.toString(
						InternetAddressUtil.removeEntry(
							mailMessage.getCc(), emailAddress));

					String replyTo = InternetAddressUtil.toString(
						mailMessage.getReplyTo());

					if (Validator.isNull(replyTo)) {
						InternetAddress from =
							(InternetAddress)mailMessage.getFrom();

						replyTo = from.toUnicodeString();
					}

					to = replyTo + StringPool.COMMA + StringPool.SPACE + to;
				}
				else {
					to = InternetAddressUtil.toString(
						mailMessage.getReplyTo());

					if (Validator.isNull(to)) {
						InternetAddress from =
							(InternetAddress)mailMessage.getFrom();

						to = from.toUnicodeString();
					}
				}

				String[] recipients = new String[] {
					Html.escape(to), Html.escape(cc), StringPool.BLANK
				};

				req.setAttribute(WebKeys.MAIL_MESSAGE_ORIGINAL_ID,
					String.valueOf(mailMessage.getMessageId()));
				req.setAttribute(WebKeys.MAIL_MESSAGE_RECIPIENTS, recipients);
				req.setAttribute(
					WebKeys.MAIL_MESSAGE_IN_REPLY_TO,
					String.valueOf(mailMessage.getInReplyTo()));
				req.setAttribute(
					WebKeys.MAIL_MESSAGE_REFERENCES,
					String.valueOf(mailMessage.getReferences()));
				req.setAttribute(
					WebKeys.MAIL_MESSAGE_SUBJECT,
					"Re: " + getSubject(mailMessage.getSubject(), "re"));
			}

			req.setAttribute(
				WebKeys.MAIL_MESSAGE_BODY,
				signature + getBody(req, mailMessage));
		}
		else if (cmd.equals(Constants.EDIT)) {
			MailUtil.setFolder(httpReq, folderId);

			MailMessage mailMessage = MailUtil.getMessage(httpReq, messageId);

			String to = Html.escape(
				InternetAddressUtil.toString(mailMessage.getTo()));
			String cc = Html.escape(
				InternetAddressUtil.toString(mailMessage.getCc()));
			String bcc = Html.escape(
				InternetAddressUtil.toString(mailMessage.getBcc()));

			String[] recipients = new String[] {to, cc, bcc};

			req.setAttribute(
				WebKeys.MAIL_MESSAGE_ORIGINAL_ID,
				new String(_DRAFT_ID_PREFIX + messageId));
			req.setAttribute(WebKeys.MAIL_MESSAGE_RECIPIENTS, recipients);
			req.setAttribute(
				WebKeys.MAIL_MESSAGE_SUBJECT, mailMessage.getSubject());
			req.setAttribute(
				WebKeys.MAIL_MESSAGE_BODY, mailMessage.getBody());
			req.setAttribute(
				WebKeys.MAIL_MESSAGE_ATTACHMENTS,
				mailMessage.getRemoteAttachments());
		}
		else if (cmd.equals(Constants.SEND)) {
			String originalId = ParamUtil.getString(req, "originalId");

			String to = ParamUtil.getString(req, "to");
			String cc = ParamUtil.getString(req, "cc");
			String bcc = ParamUtil.getString(req, "bcc");

			String[] recipients = new String[] {to, cc, bcc};

			String subject = ParamUtil.getString(req, "subject");
			String body = ParamUtil.getString(req, "body");

			req.setAttribute(WebKeys.MAIL_MESSAGE_ORIGINAL_ID, originalId);
			req.setAttribute(WebKeys.MAIL_MESSAGE_RECIPIENTS, recipients);
			req.setAttribute(WebKeys.MAIL_MESSAGE_SUBJECT, subject);
			req.setAttribute(WebKeys.MAIL_MESSAGE_BODY, body);
			req.setAttribute(
				WebKeys.MAIL_MESSAGE_ATTACHMENTS, getRemoteAttachments(req));
		}
		else {
			String to = ParamUtil.getString(req, "to");

			String[] recipients =
				new String[] {to, StringPool.BLANK, StringPool.BLANK};

			req.setAttribute(WebKeys.MAIL_MESSAGE_RECIPIENTS, recipients);
			req.setAttribute(WebKeys.MAIL_MESSAGE_BODY, signature);
		}

		return mapping.findForward("portlet.mail.edit_message");
	}

	protected void completeMessage(ActionRequest req)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		User user = PortalUtil.getUser(req);

		String originalId = ParamUtil.getString(req, "originalId");

		boolean wasDraft = false;

		if (originalId.startsWith(_DRAFT_ID_PREFIX)) {
			wasDraft = true;

			originalId = originalId.substring(_DRAFT_ID_PREFIX.length());
		}

		String to = ParamUtil.getString(req, "to");
		String cc = ParamUtil.getString(req, "cc");
		String bcc = ParamUtil.getString(req, "bcc");
		String inReplyTo = ParamUtil.getString(req, "inReplyTo");
		String references = ParamUtil.getString(req, "references");
		String subject = ParamUtil.getString(req, "subject");
		String body = ParamUtil.getString(req, "body");

		MailMessage mailMessage = new MailMessage();

		try {
			MailAccount account = MailAccounts.getCurrentAccount(req);

			mailMessage.setFrom(new InternetAddress(
				account.getEmailAddress(), user.getFullName()));
			mailMessage.setTo(to);
			mailMessage.setCc(cc);
			mailMessage.setBcc(bcc);
			mailMessage.setInReplyTo(inReplyTo);
			mailMessage.setReferences(references);
		}
		catch (Exception ex) {
			throw new RecipientException(ex);
		}

		mailMessage.setSubject(subject);
		mailMessage.setBody(body);

		Iterator itr = getAttachments(req).entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String fileName = (String)entry.getKey();
			byte[] attachment = (byte[])entry.getValue();

			MailAttachment mailAttachment = new MailAttachment();

			mailAttachment.setFilename(fileName);
			mailAttachment.setContent(attachment);
			mailAttachment.setContentType(
				ContentTypeUtil.getContentType(fileName));

			mailMessage.appendAttachment(mailAttachment);
		}

		mailMessage.setRemoteAttachments(getRemoteAttachments(req));

		boolean send = cmd.equals(Constants.SEND);

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		MailUtil.completeMessage(
			httpReq, mailMessage, send, originalId, wasDraft);
	}

	protected Map getAttachments(ActionRequest req) throws Exception {
		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		Map attachments = new HashMap();

		Enumeration enu = uploadReq.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith("attachment")) {
				File file = uploadReq.getFile(name);
				String fileName = uploadReq.getFileName(name);
				byte[] bytes = FileUtil.getBytes(file);

				if ((bytes != null) && (bytes.length > 0)) {
					attachments.put(fileName, bytes);
				}
			}
		}

		return attachments;
	}

	protected String getBody(RenderRequest req, MailMessage mailMessage)
		throws Exception {

		StringMaker sm = new StringMaker();

		InternetAddress from = (InternetAddress)mailMessage.getFrom();

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		DateFormat dateFormatDateTime = DateFormats.getDateTime(
			themeDisplay.getLocale(), themeDisplay.getTimeZone());

		sm.append("<br /><br />");
		sm.append("On " + dateFormatDateTime.format(mailMessage.getSentDate()));
		sm.append(StringPool.COMMA + StringPool.NBSP + from.getPersonal());
		sm.append(" &lt;<a href=\"mailto: " + from.getAddress() + "\">");
		sm.append(from.getAddress() + "</a>&gt; wrote:<br />");
		sm.append("<div style=\"");
		sm.append("border-left: 1px solid rgb(204, 204, 204); ");
		sm.append("margin: 0pt 0pt 0pt 1ex; ");
		sm.append("padding-left: 1ex; \">");
		sm.append(mailMessage.getBody());
		sm.append("</div>");

		return sm.toString();
	}

	protected List getRemoteAttachments(PortletRequest req)
		throws Exception {

		List list = new ArrayList();

		String prefix = "remoteAttachment";

		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith(prefix)) {
				String fileName = name.substring(prefix.length());
				String contentPath = ParamUtil.getString(req, name);

				RemoteMailAttachment remoteMailAttachment =
					new RemoteMailAttachment();

				remoteMailAttachment.setFilename(fileName);
				remoteMailAttachment.setContentPath(contentPath);

				list.add(remoteMailAttachment);
			}
		}

		return list;
	}

	protected String getSubject(String subject, String prefix)
		throws Exception {

		if (Validator.isNotNull(subject)) {
			while (StringUtil.startsWith(subject, prefix + ":") ||
				   StringUtil.startsWith(subject, prefix + ">")) {

				subject = subject.substring(3).trim();
			}
		}

		return subject;
	}

	private String _DRAFT_ID_PREFIX = "draft.";

}