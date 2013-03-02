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
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.mail.model.Message;
import com.liferay.util.JS;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.PortletURL;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ComposeMessageToAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class ComposeMessageToAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			PortletSession ses = req.getPortletSession();

			String address = req.getParameter("recipient_address");
			String name = req.getParameter("recipient_name");

			PortletPreferences prefs = req.getPreferences();

			Message msg = new Message(req, prefs);

			if ((name != null) && (address != null)) {
				msg.setTo(name + " &#60;" + address + "&#62;");
			}
			else if (address != null) {
				msg.setTo(address);
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

			PortletURL portletURL = ((ActionResponseImpl)res).createRenderURL();

			portletURL.setParameter("struts_action", "/mail/compose_message");

			res.sendRedirect(portletURL.toString());
		}
		catch (Exception e) {
			e.printStackTrace();

			// Send redirect

			res.sendRedirect(ParamUtil.getString(req, "redirect"));
		}
	}

}