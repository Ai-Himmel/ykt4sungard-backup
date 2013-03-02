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

package com.liferay.portlet.sms;

import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.JSPPortlet;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.mail.MailMessage;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.io.IOException;

import javax.mail.internet.InternetAddress;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletException;

/**
 * <a href="SMSPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class SMSPortlet extends JSPPortlet {

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {

		try {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			if (cmd.equals(Constants.SEND)) {
				String selectTo = req.getParameter("select_to");
				String to = req.getParameter("to");
				String subject = ParamUtil.getString(req, "subject");
				String message = ParamUtil.getString(req, "message");

				if (!Validator.isEmailAddress(selectTo) &&
					!Validator.isEmailAddress(to)) {

					SessionErrors.add(req, "to_invalid");
				}
				else if (!Validator.isEmailAddress(to)) {
					to = selectTo;
				}

				if (SessionErrors.isEmpty(req)) {
					User user = PortalUtil.getUser(req);

					MailServiceUtil.sendEmail(new MailMessage(
						new InternetAddress(
							user.getEmailAddress(), user.getFullName()),
						new InternetAddress(to), subject, message));

					res.setRenderParameter("select_to", StringPool.BLANK);
					res.setRenderParameter("to", StringPool.BLANK);
					res.setRenderParameter("subject", StringPool.BLANK);
					res.setRenderParameter("message", StringPool.BLANK);

					SessionMessages.add(
						req, getPortletConfig().getPortletName() + ".send", to);
				}
				else {
					res.setRenderParameter("select_to", selectTo);
					res.setRenderParameter("to", to);
					res.setRenderParameter("subject", subject);
					res.setRenderParameter("message", message);
				}
			}
		}
		catch (Exception e) {
			throw new PortletException(e);
		}
	}

}