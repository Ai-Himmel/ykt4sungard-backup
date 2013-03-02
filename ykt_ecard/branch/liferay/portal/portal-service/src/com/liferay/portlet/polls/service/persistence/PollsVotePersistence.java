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
 * <a href="PollsVotePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface PollsVotePersistence {
	public com.liferay.portlet.polls.model.PollsVote create(long voteId);

	public com.liferay.portlet.polls.model.PollsVote remove(long voteId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote remove(
		com.liferay.portlet.polls.model.PollsVote pollsVote)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsVote update(
		com.liferay.portlet.polls.model.PollsVote pollsVote)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsVote update(
		com.liferay.portlet.polls.model.PollsVote pollsVote, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsVote updateImpl(
		com.liferay.portlet.polls.model.PollsVote pollsVote, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsVote findByPrimaryKey(
		long voteId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote fetchByPrimaryKey(
		long voteId) throws com.liferay.portal.SystemException;

	public java.util.List findByQuestionId(long questionId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByQuestionId(long questionId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByQuestionId(long questionId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsVote findByQuestionId_First(
		long questionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote findByQuestionId_Last(
		long questionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote[] findByQuestionId_PrevAndNext(
		long voteId, long questionId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public java.util.List findByChoiceId(long choiceId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByChoiceId(long choiceId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByChoiceId(long choiceId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsVote findByChoiceId_First(
		long choiceId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote findByChoiceId_Last(
		long choiceId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote[] findByChoiceId_PrevAndNext(
		long voteId, long choiceId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote findByQ_U(
		long questionId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public com.liferay.portlet.polls.model.PollsVote fetchByQ_U(
		long questionId, long userId) throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByQuestionId(long questionId)
		throws com.liferay.portal.SystemException;

	public void removeByChoiceId(long choiceId)
		throws com.liferay.portal.SystemException;

	public void removeByQ_U(long questionId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchVoteException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByQuestionId(long questionId)
		throws com.liferay.portal.SystemException;

	public int countByChoiceId(long choiceId)
		throws com.liferay.portal.SystemException;

	public int countByQ_U(long questionId, long userId)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}