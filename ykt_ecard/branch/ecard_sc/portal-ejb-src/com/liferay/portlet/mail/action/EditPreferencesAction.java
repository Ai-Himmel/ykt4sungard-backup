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

import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.SystemException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.mail.util.multiaccount.MailAccount;
import com.liferay.portlet.mail.util.multiaccount.MailAccounts;
import com.liferay.util.JS;
import com.liferay.util.ListUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionMessages;

import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletException;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPreferencesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class EditPreferencesAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		PortletPreferences prefs = req.getPreferences();

		String page = ParamUtil.getString(req, "page");

		if (page.equals("filter")) {
			List blocked = new ArrayList();

			StringTokenizer st = new StringTokenizer(
				req.getParameter("blocked_list"), StringPool.COMMA);

			while (st.hasMoreTokens()) {
				String emailAddress = st.nextToken();

				if (Validator.isEmailAddress(emailAddress)) {
					blocked.add(emailAddress);
				}
			}

			ListUtil.distinct(blocked);

			prefs.setValues(
				"blocked", (String[])blocked.toArray(new String[0]));

			try {
				MailServiceUtil.updateBlocked(req.getRemoteUser(), blocked);
			}
			catch (SystemException se) {
				throw new PortletException(se);
			}
		}
		else if (page.equals("forward_address")) {
			String[] forwardAddressArray = StringUtil.split(
				ParamUtil.getString(req, "forward_address"), "\n");

			List forwardAddressList = new ArrayList();

			for (int i = 0; i < forwardAddressArray.length; i++) {
				if (Validator.isEmailAddress(forwardAddressArray[i])) {
					forwardAddressList.add(forwardAddressArray[i]);
				}
			}

			if (forwardAddressList.size() > 0) {
				prefs.setValue(
					"forward-address",
					StringUtil.merge(forwardAddressArray, StringPool.SPACE));
			}
			else {
				prefs.setValue("forward-address", StringPool.BLANK);
			}

			try {
				MailServiceUtil.addForward(
					req.getRemoteUser(), forwardAddressList);
			}
			catch (SystemException se) {
				throw new PortletException(se);
			}
		}
		else if (page.equals("mail_display")) {
			String messagesPerPortlet = req.getParameter("msg_p_i_p");
			if (Validator.isNotNull(messagesPerPortlet)) {
				try {
					int x = Integer.parseInt(messagesPerPortlet);

					if ((x >= 1) && (x <= 10)) {
						prefs.setValue(
							"messages-per-portlet", Integer.toString(x));
					}
				}
				catch (NumberFormatException nfe) {
				}
			}

			String messagesPerPage = req.getParameter("msg_p_p");
			if (Validator.isNotNull(messagesPerPage)) {
				try {
					int x = Integer.parseInt(messagesPerPage);

					if ((x >= 1) && (x <= 100)) {
						prefs.setValue(
							"messages-per-page", Integer.toString(x));
					}
				}
				catch (NumberFormatException nfe) {
				}
			}

			String messageHeaders = req.getParameter("msg_h");
			if (Validator.isNotNull(messageHeaders)) {
				try {
					int x = Integer.parseInt(messageHeaders);

					if ((x >= 0) && (x <= 3)) {
						prefs.setValue("message-headers", Integer.toString(x));
					}
				}
				catch (NumberFormatException nfe) {
				}
			}

			String messageRecipientsLimit = req.getParameter("msg_r_l");
			if (Validator.isNotNull(messageRecipientsLimit)) {
				try {
					int x = Integer.parseInt(messageRecipientsLimit);

					if ((x >= 1) && (x <= 100)) {
						prefs.setValue(
							"message-recipients-limit", Integer.toString(x));
					}
				}
				catch (NumberFormatException nfe) {
				}
			}
		}
		else if (page.equals("reply_related")) {
			String includeOriginal = req.getParameter("i_o_t");
			if (Validator.isNotNull(includeOriginal)) {
				try {
					int x = Integer.parseInt(includeOriginal);

					if (x == 0) {
						prefs.setValue("include-original", "false");
					}
					else if (x == 1) {
						prefs.setValue("include-original", "true");
					}
				}
				catch (NumberFormatException nfe) {
				}
			}

			String originalTextIndicator = req.getParameter("o_t_i");
			if (Validator.isNotNull(originalTextIndicator)) {
				try {
					int x = Integer.parseInt(originalTextIndicator);

					if ((x >= 0) && (x <= 2)) {
						prefs.setValue(
							"original-text-indicator", Integer.toString(x));
					}
				}
				catch (NumberFormatException nfe) {
				}
			}

			String replyToAddress = req.getParameter("r_t_a");
			if (Validator.isEmailAddress(replyToAddress)) {
				prefs.setValue("reply-to-address", replyToAddress);
			}
		}
		else if (page.equals("signature")) {
			String signature = ParamUtil.getString(req, "signature");

			// Escape the signature to allow users to set HTML formatted
			// signatures

			prefs.setValue("signature", JS.encodeURIComponent(signature));
		}
		else if (page.equals("sound")) {
			String newMailNotification = req.getParameter("n_m_n");
			if (Validator.isNotNull(newMailNotification)) {
				try {
					int x = Integer.parseInt(newMailNotification);

					if ((x >= 0) && (x <= 7)) {
						prefs.setValue(
							"new-mail-notification", Integer.toString(x));
					}
				}
				catch (NumberFormatException nfe) {
				}
			}
		}
		else if (page.equals("vacation_message")) {
			String vacationMessage = ParamUtil.getString(
				req, "vacation_message");

			// Escape the vacation message to allow users to set HTML formatted
			// vacation messages

			prefs.setValue(
				"vacation-message", JS.encodeURIComponent(vacationMessage));

			MailAccount account = MailAccounts.getCurrentAccount(req);

			try {
				MailServiceUtil.addVacationMessage(
					req.getRemoteUser(), account.getEmailAddress(),
					vacationMessage);
			}
			catch (SystemException se) {
				throw new PortletException(se);
			}
		}

		if (Validator.isNotNull(page)) {
			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doEdit");

			setForward(req, "portlet.mail.edit");
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		String page = ParamUtil.getString(req, "page");

		String forward =
			"portlet.mail.edit" +
			(Validator.isNotNull(page) ?
				StringPool.UNDERLINE + page : StringPool.BLANK);

		return mapping.findForward(getForward(req, forward));
	}

}