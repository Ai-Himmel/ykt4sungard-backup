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

package com.liferay.portal.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.RequestWait;
import com.liferay.portal.model.ReverseAjax;
import com.liferay.portal.struts.JSONAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.messaging.util.MessagingUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.json.JSONObject;

/**
 * <a href="ReverseAjaxAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ming-Gih Lam
 *
 */
public class ReverseAjaxAction extends JSONAction {

	public String getJSON(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		HttpSession ses = req.getSession();

		ReverseAjax reverseAjax =
			(ReverseAjax)ses.getAttribute(WebKeys.REVERSE_AJAX);

		JSONObject jo = new JSONObject();

		boolean release = ParamUtil.getBoolean(req, "release");

		if (release) {
			release(reverseAjax);
		}
		else {
			try {
				RequestWait reqWait = reverseAjax.getRequestWait();
				boolean missedEvents = true;

				if (reqWait != null) {
					reverseAjax.setRequestWait(null);
					reqWait.expire();
				}

				if (!reverseAjax.pendingEvents()) {
					missedEvents = false;
					reqWait = new RequestWait();
					reqWait.setSessionId(ses.getId());

					reverseAjax.setRequestWait(reqWait);

					reqWait.waitForRequest();
				}

				if (missedEvents || (reverseAjax.pendingEvents() &&
					!reqWait.isExpired())) {

					if (reverseAjax.isPendingChatMessage()) {
						jo.put("chatMessages",
							MessagingUtil.getChatMessages(req.getSession()));

						reverseAjax.setPendingChatMessage(false);
					}
					if (reverseAjax.isPendingChatRoster()) {
						jo.put("chatRoster",
							MessagingUtil.getRosterEntries(req.getSession()));

						reverseAjax.setPendingChatRoster(false);
					}

					jo.put("status", "success");
				}
				else if (reqWait.isTimedOut()) {
					jo.put("status", "timedOut");
				}
				else {
					jo.put("status", "failure");
				}
			}
			catch (Exception e) {
				jo.put("status", "failure");
			}
			finally {
				reverseAjax.setRequestWait(null);
			}
		}

		return jo.toString();
	}

	protected void release(ReverseAjax reverseAjax) {
		RequestWait reqWait = reverseAjax.getRequestWait();

		if (reqWait != null) {
			reverseAjax.setRequestWait(null);

			reqWait.expire();
		}
	}

}