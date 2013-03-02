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

import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.portlet.mail.util.multiaccount.MailAccount;
import com.liferay.portlet.mail.util.multiaccount.MailAccounts;
import com.liferay.util.ParamUtil;
import com.liferay.util.PwdGenerator;

import java.util.Date;

import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.Multipart;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletSession;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="SaveDraftAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class SaveDraftAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			PortletSession ses = req.getPortletSession();

			String to = req.getParameter("msg_to");
			String subject = req.getParameter("msg_sub");
			String cc = req.getParameter("msg_cc");
			String bcc = req.getParameter("msg_bcc");
			String body = req.getParameter("msg_body");

			Message msg = (Message)ses.getAttribute(
				WebKeys.MAIL_MESSAGE, PortletSession.APPLICATION_SCOPE);

			User user = PortalUtil.getUser(req);

			MailAccount account = MailAccounts.getCurrentAccount(req);

			msg.setFrom(new InternetAddress(
				account.getEmailAddress(),
				user.getFirstName() + " " + user.getLastName()));

			msg.setRecipients(
				Message.RecipientType.TO, MailUtil.parseAddresses(req, to));

			msg.setSubject(subject);

			if (cc != null) {
				msg.setRecipients(
					Message.RecipientType.CC, MailUtil.parseAddresses(req, cc));
			}

			if (bcc != null) {
				msg.setRecipients(
					Message.RecipientType.BCC,
					MailUtil.parseAddresses(req, bcc));
			}

			msg.setSentDate(new Date());

			MimeBodyPart bodyPart = new MimeBodyPart();
			bodyPart.setText(body);

			Multipart multipart = (Multipart)msg.getContent();
			multipart.removeBodyPart(0);
			multipart.addBodyPart(bodyPart, 0);

			Folder folder = MailUtil.getFolder(
				req, MailUtil.MAIL_BOX_STYLE + "drafts");

			String[] liferayDraftIdArray = msg.getHeader("liferay-draft-id");

			String liferayDraftId = null;

			if ((liferayDraftIdArray != null) &&
				(liferayDraftIdArray.length > 0)) {

				liferayDraftId = liferayDraftIdArray[0];

				Message oldDraftMsg = null;

				Message[] messages = folder.getMessages();

				for (int i = 0; i < messages.length; i++) {
					String[] curLiferayDraftIdArray =
						messages[i].getHeader("liferay-draft-id");

					if ((curLiferayDraftIdArray != null) &&
						(curLiferayDraftIdArray.length > 0)) {

						String curLiferayDraftId = curLiferayDraftIdArray[0];

						if (liferayDraftId.equals(curLiferayDraftId)) {
							oldDraftMsg = messages[i];

							break;
						}
					}
				}

				if (oldDraftMsg != null) {
					folder.setFlags(
						new Message[] {oldDraftMsg},
						new Flags(Flags.Flag.DELETED), true);

					folder.expunge();
				}
			}

			if (liferayDraftId == null) {
				liferayDraftId = PwdGenerator.getPassword(
					PwdGenerator.KEY1 + PwdGenerator.KEY2, 6);

				msg.addHeader("liferay-draft-id", liferayDraftId);
			}

			folder.appendMessages(new Message[] {msg});

			ses.removeAttribute(
				WebKeys.MAIL_MESSAGE, PortletSession.APPLICATION_SCOPE);
			ses.removeAttribute(
				WebKeys.MAIL_MESSAGE_MODEL, PortletSession.APPLICATION_SCOPE);

			// Send redirect

			res.sendRedirect(ParamUtil.getString(req, "redirect"));
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			setForward(req, Constants.COMMON_ERROR);
		}
	}

}