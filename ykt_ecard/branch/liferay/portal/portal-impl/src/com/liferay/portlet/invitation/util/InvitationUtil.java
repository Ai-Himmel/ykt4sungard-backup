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

package com.liferay.portlet.invitation.util;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PropsUtil;

import java.io.IOException;

import javax.portlet.PortletPreferences;

/**
 * <a href="InvitationUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InvitationUtil {

	public static int getEmailMessageMaxRecipients() {
		return GetterUtil.getInteger(PropsUtil.get(
			PropsUtil.INVITATION_EMAIL_MAX_RECIPIENTS));
	}

	public static String getEmailMessageBody(PortletPreferences prefs)
		throws IOException {

		String emailMessageBody = prefs.getValue(
			"email-message-body", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageBody)) {
			return emailMessageBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.INVITATION_EMAIL_MESSAGE_BODY));
		}
	}

	public static String getEmailMessageSubject(PortletPreferences prefs)
		throws IOException {

		String emailMessageSubject = prefs.getValue(
			"email-message-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageSubject)) {
			return emailMessageSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.INVITATION_EMAIL_MESSAGE_SUBJECT));
		}
	}

}