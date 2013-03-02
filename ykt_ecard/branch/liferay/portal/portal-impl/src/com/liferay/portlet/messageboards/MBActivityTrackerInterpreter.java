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

package com.liferay.portlet.messageboards;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.ActivityFeedEntry;
import com.liferay.portal.model.ActivityTracker;
import com.liferay.portal.model.ActivityTrackerInterpreter;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBActivityTrackerInterpreter.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBActivityTrackerInterpreter
	implements ActivityTrackerInterpreter {

	public String[] getClassNames() {
		return _CLASS_NAMES;
	}

	public ActivityFeedEntry interpret(
		ActivityTracker activityTracker, ThemeDisplay themeDisplay) {

		try {
			return doInterpret(activityTracker, themeDisplay);
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return null;
	}

	protected ActivityFeedEntry doInterpret(
			ActivityTracker activityTracker, ThemeDisplay themeDisplay)
		throws Exception {

		User creatorUser = UserLocalServiceUtil.getUserById(
			activityTracker.getUserId());

		String creatorUserName = creatorUser.getFullName();
		String creatorUserDisplayURL = creatorUser.getDisplayURL(
			themeDisplay.getURLPortal());

		creatorUserName = "<a href=\"" + creatorUserDisplayURL + "\">" + creatorUserName + "</a>";

		String activity = activityTracker.getActivity();

		String receiverUserName = activityTracker.getReceiverUserName();

		if (activityTracker.getReceiverUserId() > 0) {
			User receiverUser = UserLocalServiceUtil.getUserById(
				activityTracker.getReceiverUserId());

			receiverUserName = receiverUser.getFullName();
		}

		// Title

		String title = StringPool.BLANK;

		if (activity.equals(MBActivityKeys.ADD)) {
			title = LanguageUtil.format(
				themeDisplay.getCompanyId(), themeDisplay.getLocale(),
				"activity-message-boards-add",
				new Object[] {creatorUserName});
		}
		else if (activity.equals(MBActivityKeys.REPLY)) {
			title = LanguageUtil.format(
				themeDisplay.getCompanyId(), themeDisplay.getLocale(),
				"activity-message-boards-reply",
				new Object[] {creatorUserName, receiverUserName});
		}

		// Body

		MBMessage message = MBMessageLocalServiceUtil.getMessage(
			activityTracker.getClassPK());

		StringMaker sm = new StringMaker();

		sm.append("<b>");
		sm.append(message.getSubject());
		sm.append("</b><br />");
		sm.append(StringUtil.shorten(message.getBody(), 200));

		String body = sm.toString();

		return new ActivityFeedEntry(title, body);
	}

	private static final String[] _CLASS_NAMES = new String[] {
		MBMessage.class.getName()
	};

	private static Log _log =
		LogFactory.getLog(MBActivityTrackerInterpreter.class);

}