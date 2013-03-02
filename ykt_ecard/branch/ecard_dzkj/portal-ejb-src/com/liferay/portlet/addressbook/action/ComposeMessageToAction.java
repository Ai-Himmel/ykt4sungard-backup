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

package com.liferay.portlet.addressbook.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.Recipient;
import com.liferay.portal.util.RecipientComparator;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.portlet.addressbook.service.spring.ABContactServiceUtil;
import com.liferay.portlet.addressbook.service.spring.ABListServiceUtil;
import com.liferay.portlet.mail.model.Message;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.JS;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.WindowState;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ComposeMessageToAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class ComposeMessageToAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			PortletSession ses = req.getPortletSession();

			List recipients = new ArrayList();

			String[] ids = req.getParameterValues("contact_ids");

			for (int i = 0; ids != null && i < ids.length; i++) {
				recipients.add(ABContactServiceUtil.getContact(ids[i]));
			}

			ids = req.getParameterValues("list_ids");

			for (int i = 0; ids != null && i < ids.length; i++) {
				recipients.add(ABListServiceUtil.getList(ids[i]));
			}

			Collections.sort(recipients, new RecipientComparator());

			PortletPreferences prefs = MailUtil.getPreferences(req);

			Message msg = new Message(req, prefs);

			if (recipients.size() > 0) {
				FastStringBuffer sb = new FastStringBuffer();

				for (int i = 0; i < recipients.size(); i++) {
					Recipient recipient = (Recipient)recipients.get(i);
					sb.append(recipient.getRecipientInternetAddress());

					if ((i + 1) != recipients.size()) {
						sb.append(", ");
					}
				}

				msg.setTo(sb.toString());
			}

			FastStringBuffer msgBody = new FastStringBuffer();

			String signature = prefs.getValue("signature", StringPool.BLANK);

			if (Validator.isNotNull(signature)) {
				signature = JS.decodeURIComponent(signature);

				if (msg.isHTMLFormat()) {
					msgBody.append("<br><br>");
					msgBody.append(StringUtil.replace(signature, "\n", "<br>"));
				}
				else {
					msgBody.append("\n\n\n");
					msgBody.append(signature);
				}
			}

			msg.setBody(msgBody.toString());

			ses.setAttribute(
				WebKeys.MAIL_MESSAGE_MODEL, msg,
				PortletSession.APPLICATION_SCOPE);

			// Send redirect

			List layouts = (List)req.getAttribute(WebKeys.LAYOUTS);

			String layoutId = PortalUtil.getLayoutIdWithPortletId(
				layouts, PortletKeys.MAIL);

			PortletURLImpl portletURLImpl = new PortletURLImpl(
				(ActionRequestImpl)req, PortletKeys.MAIL, layoutId, true);

			portletURLImpl.setWindowState(WindowState.MAXIMIZED);
			portletURLImpl.setPortletMode(PortletMode.VIEW);

			portletURLImpl.setParameter(
				"struts_action", "/mail/compose_message");

			res.sendRedirect(portletURLImpl.toString());
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			setForward(req, Constants.COMMON_ERROR);
		}
	}

}