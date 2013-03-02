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

package com.liferay.portlet.polls.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.polls.model.PollsQuestion;
import com.liferay.portlet.polls.service.base.PollsQuestionServiceBaseImpl;
import com.liferay.portlet.polls.service.permission.PollsQuestionPermission;

import java.util.List;

/**
 * <a href="PollsQuestionServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsQuestionServiceImpl extends PollsQuestionServiceBaseImpl {

	public PollsQuestion addQuestion(
			long plid, String title, String description,
			int expirationDateMonth, int expirationDateDay,
			int expirationDateYear, int expirationDateHour,
			int expirationDateMinute, boolean neverExpire, List choices,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.POLLS,
			ActionKeys.ADD_QUESTION);

		return pollsQuestionLocalService.addQuestion(
			getUserId(), plid, title, description, expirationDateMonth,
			expirationDateDay, expirationDateYear, expirationDateHour,
			expirationDateMinute, neverExpire, choices,
			addCommunityPermissions, addGuestPermissions);
	}

	public PollsQuestion addQuestion(
			long plid, String title, String description,
			int expirationDateMonth, int expirationDateDay,
			int expirationDateYear, int expirationDateHour,
			int expirationDateMinute, boolean neverExpire, List choices,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.POLLS,
			ActionKeys.ADD_QUESTION);

		return pollsQuestionLocalService.addQuestion(
			getUserId(), plid, title, description, expirationDateMonth,
			expirationDateDay, expirationDateYear, expirationDateHour,
			expirationDateMinute, neverExpire, choices, communityPermissions,
			guestPermissions);
	}

	public void deleteQuestion(long questionId)
		throws PortalException, SystemException {

		PollsQuestionPermission.check(
			getPermissionChecker(), questionId, ActionKeys.DELETE);

		pollsQuestionLocalService.deleteQuestion(questionId);
	}

	public PollsQuestion getQuestion(long questionId)
		throws PortalException, SystemException {

		PollsQuestionPermission.check(
			getPermissionChecker(), questionId, ActionKeys.VIEW);

		return pollsQuestionLocalService.getQuestion(questionId);
	}

	public PollsQuestion updateQuestion(
			long questionId, String title, String description,
			int expirationDateMonth, int expirationDateDay,
			int expirationDateYear, int expirationDateHour,
			int expirationDateMinute, boolean neverExpire, List choices)
		throws PortalException, SystemException {

		PollsQuestionPermission.check(
			getPermissionChecker(), questionId, ActionKeys.UPDATE);

		return pollsQuestionLocalService.updateQuestion(
			getUserId(), questionId, title, description, expirationDateMonth,
			expirationDateDay, expirationDateYear, expirationDateHour,
			expirationDateMinute, neverExpire, choices);
	}

}