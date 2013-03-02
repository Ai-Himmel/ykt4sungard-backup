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

package com.liferay.portlet.polls.service;


/**
 * <a href="PollsVoteLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.polls.service.PollsVoteLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.polls.service.PollsVoteLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.polls.service.PollsVoteLocalService
 * @see com.liferay.portlet.polls.service.PollsVoteLocalServiceFactory
 *
 */
public class PollsVoteLocalServiceUtil {
	public static com.liferay.portlet.polls.model.PollsVote addPollsVote(
		com.liferay.portlet.polls.model.PollsVote model)
		throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.addPollsVote(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.polls.model.PollsVote updatePollsVote(
		com.liferay.portlet.polls.model.PollsVote model)
		throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.updatePollsVote(model);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsChoicePersistence getPollsChoicePersistence() {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getPollsChoicePersistence();
	}

	public static void setPollsChoicePersistence(
		com.liferay.portlet.polls.service.persistence.PollsChoicePersistence pollsChoicePersistence) {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		pollsVoteLocalService.setPollsChoicePersistence(pollsChoicePersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsChoiceFinder getPollsChoiceFinder() {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getPollsChoiceFinder();
	}

	public static void setPollsChoiceFinder(
		com.liferay.portlet.polls.service.persistence.PollsChoiceFinder pollsChoiceFinder) {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		pollsVoteLocalService.setPollsChoiceFinder(pollsChoiceFinder);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence getPollsQuestionPersistence() {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getPollsQuestionPersistence();
	}

	public static void setPollsQuestionPersistence(
		com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence pollsQuestionPersistence) {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		pollsVoteLocalService.setPollsQuestionPersistence(pollsQuestionPersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsVotePersistence getPollsVotePersistence() {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getPollsVotePersistence();
	}

	public static void setPollsVotePersistence(
		com.liferay.portlet.polls.service.persistence.PollsVotePersistence pollsVotePersistence) {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		pollsVoteLocalService.setPollsVotePersistence(pollsVotePersistence);
	}

	public static void afterPropertiesSet() {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		pollsVoteLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.polls.model.PollsVote addVote(
		long userId, long questionId, long choiceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.addVote(userId, questionId, choiceId);
	}

	public static java.util.List getChoiceVotes(long choiceId, int begin,
		int end) throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getChoiceVotes(choiceId, begin, end);
	}

	public static int getChoiceVotesCount(long choiceId)
		throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getChoiceVotesCount(choiceId);
	}

	public static com.liferay.portlet.polls.model.PollsVote getVote(
		long questionId, long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getVote(questionId, userId);
	}

	public static java.util.List getQuestionVotes(long questionId, int begin,
		int end) throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getQuestionVotes(questionId, begin, end);
	}

	public static int getQuestionVotesCount(long questionId)
		throws com.liferay.portal.SystemException {
		PollsVoteLocalService pollsVoteLocalService = PollsVoteLocalServiceFactory.getService();

		return pollsVoteLocalService.getQuestionVotesCount(questionId);
	}
}