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

package com.liferay.portlet.polls.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.polls.NoSuchVoteException;
import com.liferay.portlet.polls.model.PollsQuestion;
import com.liferay.portlet.polls.model.PollsVote;
import com.liferay.portlet.polls.service.persistence.PollsQuestionUtil;
import com.liferay.portlet.polls.service.persistence.PollsVotePK;
import com.liferay.portlet.polls.service.persistence.PollsVoteUtil;
import com.liferay.portlet.polls.service.spring.PollsQuestionLocalServiceUtil;
import com.liferay.portlet.polls.service.spring.PollsQuestionService;

import java.util.Date;
import java.util.List;

/**
 * <a href="PollsQuestionServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class PollsQuestionServiceImpl
	extends PrincipalBean implements PollsQuestionService {

	// Business methods

	public PollsQuestion addQuestion(
			String portletId, String groupId, String title, String description,
			int expMonth, int expDay, int expYear, boolean neverExpires,
			List choices)
		throws PortalException, SystemException {

		return PollsQuestionLocalServiceUtil.addQuestion(
			getUserId(), portletId, groupId, title, description, expMonth,
			expDay, expYear, neverExpires, choices);
	}

	public void checkQuestions() throws PortalException, SystemException {
		List questions = PollsQuestionUtil.findAll();

		Date now = new Date();

		for (int i = 0; i < questions.size(); i++) {
			PollsQuestion question = (PollsQuestion)questions.get(i);

			if (question.getExpirationDate() != null &&
				question.getExpirationDate().before(now)) {

				PollsQuestionUtil.remove(question.getQuestionId());
			}
		}
	}

	public void deleteQuestion(String questionId)
		throws PortalException, SystemException {

		if (!hasAdmin(questionId)) {
			throw new PrincipalException();
		}

		PollsQuestionLocalServiceUtil.deleteQuestion(questionId);
	}

	public PollsQuestion getQuestion(String questionId)
		throws PortalException, SystemException {

		return PollsQuestionUtil.findByPrimaryKey(questionId);
	}

	public List getQuestions(String portletId, String groupId, String companyId)
		throws SystemException {

		return PollsQuestionUtil.findByP_G_C(portletId, groupId, companyId);
	}

	public List getQuestions(
			String portletId, String groupId, String companyId, int begin,
			int end)
		throws SystemException {

		return PollsQuestionUtil.findByP_G_C(
			portletId, groupId, companyId, begin, end);
	}

	public int getQuestionsSize(
			String portletId, String groupId, String companyId)
		throws SystemException {

		return PollsQuestionUtil.countByP_G_C(portletId, groupId, companyId);
	}

	public boolean hasVoted(String questionId)
		throws PortalException, SystemException {

		try {
			PollsVote vote = PollsVoteUtil.findByPrimaryKey(
				new PollsVotePK(questionId, getUserId()));
		}
		catch (NoSuchVoteException nsve) {
			return false;
		}

		return true;
	}

	public PollsQuestion updateQuestion(
			String questionId, String title, String description, int expMonth,
			int expDay, int expYear, boolean neverExpires, List choices)
		throws PortalException, SystemException {

		if (!hasAdmin(questionId)) {
			throw new PrincipalException();
		}

		return PollsQuestionLocalServiceUtil.updateQuestion(
			getUserId(), questionId, title, description, expMonth, expDay,
			expYear, neverExpires, choices);
	}

	public void vote(String questionId, String choiceId)
		throws PortalException, SystemException {

		User user = getUser();

		PollsQuestion question = getQuestion(questionId);

		if (!question.getCompanyId().equals(user.getCompanyId())) {
			throw new PrincipalException();
		}

		PollsQuestionLocalServiceUtil.vote(
			user.getUserId(), questionId, choiceId);
	}

	// Permission methods

	// Permission methods

	public boolean hasAdmin() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.POLLS_ADMIN)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasAdmin(String questionId)
		throws PortalException, SystemException {

		PollsQuestion question = PollsQuestionUtil.findByPrimaryKey(questionId);

		if ((question.getUserId().equals(getUserId())) ||
			(getUser().getCompanyId().equals(question.getCompanyId()) &&
			 RoleServiceUtil.hasRole(getUserId(), Role.POLLS_ADMIN))) {

			return true;
		}
		else {
			return false;
		}
	}

}