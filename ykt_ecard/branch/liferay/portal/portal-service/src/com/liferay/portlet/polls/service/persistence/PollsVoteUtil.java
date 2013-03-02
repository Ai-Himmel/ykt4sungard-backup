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

package com.liferay.portlet.polls.service.persistence;

/**
 * <a href="PollsVoteUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsVoteUtil {
	public static com.liferay.portlet.polls.model.PollsVote create(long voteId) {
		return getPersistence().create(voteId);
	}

	public static com.liferay.portlet.polls.model.PollsVote remove(long voteId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().remove(voteId);
	}

	public static com.liferay.portlet.polls.model.PollsVote remove(
		com.liferay.portlet.polls.model.PollsVote pollsVote)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(pollsVote);
	}

	public static com.liferay.portlet.polls.model.PollsVote update(
		com.liferay.portlet.polls.model.PollsVote pollsVote)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pollsVote);
	}

	public static com.liferay.portlet.polls.model.PollsVote update(
		com.liferay.portlet.polls.model.PollsVote pollsVote, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pollsVote, merge);
	}

	public static com.liferay.portlet.polls.model.PollsVote updateImpl(
		com.liferay.portlet.polls.model.PollsVote pollsVote, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(pollsVote, merge);
	}

	public static com.liferay.portlet.polls.model.PollsVote findByPrimaryKey(
		long voteId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByPrimaryKey(voteId);
	}

	public static com.liferay.portlet.polls.model.PollsVote fetchByPrimaryKey(
		long voteId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(voteId);
	}

	public static java.util.List findByQuestionId(long questionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId(questionId);
	}

	public static java.util.List findByQuestionId(long questionId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId(questionId, begin, end);
	}

	public static java.util.List findByQuestionId(long questionId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId(questionId, begin, end, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote findByQuestionId_First(
		long questionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByQuestionId_First(questionId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote findByQuestionId_Last(
		long questionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByQuestionId_Last(questionId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote[] findByQuestionId_PrevAndNext(
		long voteId, long questionId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByQuestionId_PrevAndNext(voteId,
			questionId, obc);
	}

	public static java.util.List findByChoiceId(long choiceId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByChoiceId(choiceId);
	}

	public static java.util.List findByChoiceId(long choiceId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByChoiceId(choiceId, begin, end);
	}

	public static java.util.List findByChoiceId(long choiceId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByChoiceId(choiceId, begin, end, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote findByChoiceId_First(
		long choiceId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByChoiceId_First(choiceId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote findByChoiceId_Last(
		long choiceId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByChoiceId_Last(choiceId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote[] findByChoiceId_PrevAndNext(
		long voteId, long choiceId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByChoiceId_PrevAndNext(voteId, choiceId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsVote findByQ_U(
		long questionId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		return getPersistence().findByQ_U(questionId, userId);
	}

	public static com.liferay.portlet.polls.model.PollsVote fetchByQ_U(
		long questionId, long userId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByQ_U(questionId, userId);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByQuestionId(long questionId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByQuestionId(questionId);
	}

	public static void removeByChoiceId(long choiceId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByChoiceId(choiceId);
	}

	public static void removeByQ_U(long questionId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException {
		getPersistence().removeByQ_U(questionId, userId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByQuestionId(long questionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByQuestionId(questionId);
	}

	public static int countByChoiceId(long choiceId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByChoiceId(choiceId);
	}

	public static int countByQ_U(long questionId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByQ_U(questionId, userId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PollsVotePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PollsVotePersistence persistence) {
		_persistence = persistence;
	}

	private static PollsVoteUtil _getUtil() {
		if (_util == null) {
			_util = (PollsVoteUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PollsVoteUtil.class.getName();
	private static PollsVoteUtil _util;
	private PollsVotePersistence _persistence;
}