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

import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.mail.MailMessageException;
import com.liferay.portlet.mail.model.MailReceipt;
import com.liferay.portlet.mail.service.spring.MailReceiptServiceUtil;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.portlet.mail.util.multiaccount.MailAccount;
import com.liferay.portlet.mail.util.multiaccount.MailAccounts;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.mail.BodyPart;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.Multipart;
import javax.mail.SendFailedException;
import javax.mail.Transport;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMultipart;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.PortletURL;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="SendMessageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class SendMessageAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			ActionUtil.getMessageModel(req);

			_sendMessage(req, res);
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof AddressException ||
				e instanceof MailMessageException ||
				e instanceof SendFailedException) {

				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, "portlet.mail.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
	}

	private String _getUpdateReceiptURL(
			Company company, String mainPath, MailReceipt receipt)
		throws Exception {

		FastStringBuffer sb = new FastStringBuffer();
		sb.append("\n\n");
		sb.append("<img height='0' hspace='0' src='");
		sb.append("http://");
		sb.append(company.getPortalURL());
		sb.append(mainPath);
		sb.append("/mail/update_receipt?receipt_id=");
		sb.append(receipt.getReceiptId());
		sb.append("' vspace='0' width='0'>");

		return sb.toString();
	}

	private void _sendMessage(ActionRequest req, ActionResponse res)
		throws Exception {

		PortletSession ses = req.getPortletSession();

		PortletPreferences prefs = req.getPreferences();

		String to = req.getParameter("msg_to");
		String subject = req.getParameter("msg_sub");
		String cc = req.getParameter("msg_cc");
		String bcc = req.getParameter("msg_bcc");
		String body = req.getParameter("msg_body");

		boolean returnReceipt = false;
		String returnReceiptParam = req.getParameter("msg_return_receipt_1");
		if ((Validator.isNotNull(returnReceiptParam)) &&
			(returnReceiptParam.equals("on"))) {

			returnReceipt = true;
		}

		boolean htmlFormat = false;
		String htmlFormatParam = req.getParameter("html_cb_1");
		if ((Validator.isNotNull(htmlFormatParam)) &&
			(htmlFormatParam.equals("on"))) {

			htmlFormat = true;
		}

		Message msg = (Message)ses.getAttribute(
			WebKeys.MAIL_MESSAGE, PortletSession.APPLICATION_SCOPE);

		if (msg == null) {
			throw new MailMessageException();
		}

		User user = PortalUtil.getUser(req);

		MailAccount account = MailAccounts.getCurrentAccount(req);

		msg.setFrom(new InternetAddress(
			account.getEmailAddress(), user.getFullName()));

		String replyToAddress =
			prefs.getValue("reply-to-address", StringPool.BLANK);

		if (Validator.isNotNull(replyToAddress)) {
			if (!account.getEmailAddress().equals(replyToAddress)) {
				InternetAddress[] replyTo = new InternetAddress[1];
				replyTo[0] = new InternetAddress(
					replyToAddress, user.getFullName());
				msg.setReplyTo(replyTo);
			}
		}

		msg.setRecipients(
			Message.RecipientType.TO, MailUtil.parseAddresses(req, to));

		msg.setSubject(subject);

		if (cc != null) {
			msg.setRecipients(
				Message.RecipientType.CC, MailUtil.parseAddresses(req, cc));
		}

		InternetAddress[] auditTrail = InternetAddress.parse(
			PropsUtil.get(PropsUtil.MAIL_AUDIT_TRAIL));

		if (bcc != null) {
			InternetAddress[] bccAddresses =
				MailUtil.parseAddresses(req, bcc);

			InternetAddress[] allBccAddresses = new InternetAddress[
				bccAddresses.length + auditTrail.length];

			System.arraycopy(
				bccAddresses, 0, allBccAddresses, 0, bccAddresses.length);

			System.arraycopy(
				auditTrail, 0, allBccAddresses, bccAddresses.length,
				auditTrail.length);

			msg.setRecipients(
				Message.RecipientType.BCC, allBccAddresses);
		}
		else if (auditTrail.length > 0) {
			msg.setRecipients(
				Message.RecipientType.BCC, auditTrail);
		}

		msg.setSentDate(new Date());

		BodyPart bodyPart = new MimeBodyPart();

		if (htmlFormat) {
			bodyPart.setContent(body, Constants.TEXT_HTML);
		}
		else {
			bodyPart.setText(body);
		}

		Multipart multipart = (Multipart)msg.getContent();
		multipart.removeBodyPart(0);
		multipart.addBodyPart(bodyPart, 0);

		// Send message

		if (returnReceipt && htmlFormat) {
			try {
				Company company = PortalUtil.getCompany(req);

				PortletContext portletCtx =
					req.getPortletSession().getPortletContext();

				String mainPath =
					(String)portletCtx.getAttribute(WebKeys.MAIN_PATH);

				_sendReceiptMessage(company, mainPath, msg, body, htmlFormat);
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
		else {
			Transport.send(msg);
		}

		// Copy to sent mail folder

		Message[] messages = {msg};

		Folder sentMailFolder = MailUtil.getFolder(
			req, MailUtil.MAIL_BOX_STYLE + "sent-mail");
		sentMailFolder.appendMessages(messages);

		com.liferay.portlet.mail.model.Message msgModel =
			(com.liferay.portlet.mail.model.Message)
				ses.getAttribute(
					WebKeys.MAIL_MESSAGE_MODEL,
					PortletSession.APPLICATION_SCOPE);

		if (msgModel.isDraft()) {
			Message oldMsg = msgModel.getMessage();
			Message[] oldMessages = {oldMsg};

			Folder draftFolder = MailUtil.getFolder(
				req, MailUtil.MAIL_BOX_STYLE + "drafts");
			draftFolder.setFlags(
				oldMessages, new Flags(Flags.Flag.DELETED), true);
			draftFolder.expunge();
		}
		else if (Validator.isNumber(msgModel.getParentNumber())) {
			Folder folder =
				MailUtil.getFolder(req, msgModel.getParentFolder());

			Message parentMessage = null;

			try {
				parentMessage = folder.getMessage(
					Integer.parseInt(msgModel.getParentNumber()));
			}
			catch (IndexOutOfBoundsException ioobe) {
			}

			if (parentMessage != null) {
				parentMessage.setFlag(Flags.Flag.ANSWERED, true);
			}
		}

		ses.removeAttribute(
			WebKeys.MAIL_MESSAGE, PortletSession.APPLICATION_SCOPE);
		ses.removeAttribute(
			WebKeys.MAIL_MESSAGE_MODEL, PortletSession.APPLICATION_SCOPE);

		// Send redirect

		PortletURL portletURL = ((ActionResponseImpl)res).createRenderURL();

		portletURL.setParameter("struts_action", "/mail/view_folder");

		String msgType = msgModel.getMessageType();

		if ((msgType != null) &&
			((msgType.equals("forward"))||
			 (msgType.equals("reply")) ||
			 (msgType.equals("reply_all")))) {

			if ((Validator.isNotNull(msgModel.getParentFolder())) &&
				(Validator.isNotNull(msgModel.getParentFolder()))) {

				portletURL.setParameter(
					"folder_name", msgModel.getParentFolder());
				portletURL.setParameter(
					"msg_num", msgModel.getParentNumber());
			}
		}

		res.sendRedirect(portletURL.toString());
	}

	private void _sendReceiptMessage(
			Company company, String mainPath, Message msg, String body,
			boolean htmlFormat)
		throws Exception {

		InternetAddress[] toAddresses =
			(InternetAddress[])msg.getRecipients(Message.RecipientType.TO);

		InternetAddress[] ccAddresses =
			(InternetAddress[])msg.getRecipients(Message.RecipientType.CC);

		InternetAddress[] bccAddresses =
			(InternetAddress[])msg.getRecipients(Message.RecipientType.BCC);

		List addresses = new ArrayList();

		if (toAddresses != null) {
			for (int i = 0; i < toAddresses.length; i++) {
				addresses.add(toAddresses[i]);
			}
		}

		if (ccAddresses != null) {
			for (int i = 0; i < ccAddresses.length; i++) {
				addresses.add(ccAddresses[i]);
			}
		}

		if (bccAddresses != null) {
			for (int i = 0; i < bccAddresses.length; i++) {
				addresses.add(bccAddresses[i]);
			}
		}

		for (int i = 0; i < addresses.size(); i++) {
			InternetAddress toAddress = (InternetAddress)addresses.get(i);

			Message newMsg = MailUtil.getNewMessage();

			newMsg.setFrom(msg.getFrom()[0]);
			newMsg.setRecipient(Message.RecipientType.TO, toAddress);
			newMsg.setSubject(msg.getSubject());
			newMsg.setSentDate(msg.getSentDate());

			MailReceipt receipt = MailReceiptServiceUtil.addReceipt(
				toAddress.getPersonal(), toAddress.getAddress(),
				msg.getSubject(), msg.getSentDate());

			String newBody =
				body + _getUpdateReceiptURL(company, mainPath, receipt);

			BodyPart newBodyPart = new MimeBodyPart();

			if (htmlFormat) {
				newBodyPart.setContent(newBody, Constants.TEXT_HTML);
			}
			else {
				newBodyPart.setText(newBody);
			}

			Multipart newMultipart = new MimeMultipart();

			Multipart multipart = (Multipart)msg.getContent();

			for (int j = 0; j < multipart.getCount(); j++) {
				newMultipart.addBodyPart(multipart.getBodyPart(j));
			}

			newMultipart.removeBodyPart(0);
			newMultipart.addBodyPart(newBodyPart, 0);

			newMsg.setContent(newMultipart);

			Transport.send(newMsg);
		}
	}

}