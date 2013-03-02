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
 * <a href="PollsChoiceLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.polls.service.PollsChoiceLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.polls.service.PollsChoiceLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.polls.service.PollsChoiceLocalService
 * @see com.liferay.portlet.polls.service.PollsChoiceLocalServiceFactory
 *
 */
public class PollsChoiceLocalServiceUtil {
	public static com.liferay.portlet.polls.model.PollsChoice addPollsChoice(
		com.liferay.portlet.polls.model.PollsChoice model)
		throws com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.addPollsChoice(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.polls.model.PollsChoice updatePollsChoice(
		com.liferay.portlet.polls.model.PollsChoice model)
		throws com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.updatePollsChoice(model);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsChoicePersistence getPollsChoicePersistence() {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getPollsChoicePersistence();
	}

	public static void setPollsChoicePersistence(
		com.liferay.portlet.polls.service.persistence.PollsChoicePersistence pollsChoicePersistence) {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		pollsChoiceLocalService.setPollsChoicePersistence(pollsChoicePersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsChoiceFinder getPollsChoiceFinder() {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getPollsChoiceFinder();
	}

	public static void setPollsChoiceFinder(
		com.liferay.portlet.polls.service.persistence.PollsChoiceFinder pollsChoiceFinder) {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		pollsChoiceLocalService.setPollsChoiceFinder(pollsChoiceFinder);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence getPollsQuestionPersistence() {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getPollsQuestionPersistence();
	}

	public static void setPollsQuestionPersistence(
		com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence pollsQuestionPersistence) {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		pollsChoiceLocalService.setPollsQuestionPersistence(pollsQuestionPersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsVotePersistence getPollsVotePersistence() {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getPollsVotePersistence();
	}

	public static void setPollsVotePersistence(
		com.liferay.portlet.polls.service.persistence.PollsVotePersistence pollsVotePersistence) {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		pollsChoiceLocalService.setPollsVotePersistence(pollsVotePersistence);
	}

	public static void afterPropertiesSet() {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		pollsChoiceLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.polls.model.PollsChoice addChoice(
		long questionId, java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.addChoice(questionId, name, description);
	}

	public static com.liferay.portlet.polls.model.PollsChoice addChoice(
		java.lang.String uuid, long questionId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.addChoice(uuid, questionId, name,
			description);
	}

	public static com.liferay.portlet.polls.model.PollsChoice getChoice(
		long choiceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getChoice(choiceId);
	}

	public static java.util.List getChoices(long questionId)
		throws com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getChoices(questionId);
	}

	public static int getChoicesCount(long questionId)
		throws com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.getChoicesCount(questionId);
	}

	public static com.liferay.portlet.polls.model.PollsChoice updateChoice(
		long choiceId, long questionId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsChoiceLocalService pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getService();

		return pollsChoiceLocalService.updateChoice(choiceId, questionId, name,
			description);
	}
}