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
import com.liferay.portlet.polls.DuplicateVoteException;
import com.liferay.portlet.polls.NoSuchQuestionException;
import com.liferay.portlet.polls.QuestionExpiredException;
import com.liferay.portlet.polls.model.PollsChoice;
import com.liferay.portlet.polls.model.PollsQuestion;
import com.liferay.portlet.polls.model.PollsVote;
import com.liferay.portlet.polls.service.base.PollsVoteLocalServiceBaseImpl;

import java.util.Date;
import java.util.List;

/**
 * <a href="PollsVoteLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsVoteLocalServiceImpl extends PollsVoteLocalServiceBaseImpl {

	public PollsVote addVote(long userId, long questionId, long choiceId)
		throws PortalException, SystemException {

		// Choice

		Date now = new Date();

		PollsChoice choice = pollsChoicePersistence.findByPrimaryKey(choiceId);

		if (choice.getQuestionId() != questionId) {
			throw new NoSuchQuestionException();
		}

		// Question

		PollsQuestion question = pollsQuestionPersistence.findByPrimaryKey(
			questionId);

		if (question.isExpired()) {
			throw new QuestionExpiredException();
		}

		question.setLastVoteDate(now);

		pollsQuestionPersistence.update(question);

		// Vote

		PollsVote vote = pollsVotePersistence.fetchByQ_U(questionId, userId);

		if (vote != null) {
			throw new DuplicateVoteException();
		}
		else {
			long voteId = counterLocalService.increment();

			vote = pollsVotePersistence.create(voteId);

			vote.setUserId(userId);
			vote.setQuestionId(questionId);
			vote.setChoiceId(choiceId);
			vote.setVoteDate(now);

			pollsVotePersistence.update(vote);
		}

		return vote;
	}

	public List getChoiceVotes(long choiceId, int begin, int end)
		throws SystemException {

		return pollsVotePersistence.findByChoiceId(choiceId,  begin, end);
	}

	public int getChoiceVotesCount(long choiceId) throws SystemException {
		return pollsVotePersistence.countByChoiceId(choiceId);
	}

	public PollsVote getVote(long questionId, long userId)
		throws PortalException, SystemException {

		return pollsVotePersistence.findByQ_U(questionId, userId);
	}

	public List getQuestionVotes(long questionId, int begin, int end)
		throws SystemException {

		return pollsVotePersistence.findByQuestionId(questionId, begin, end);
	}

	public int getQuestionVotesCount(long questionId) throws SystemException {
		return pollsVotePersistence.countByQuestionId(questionId);
	}

}