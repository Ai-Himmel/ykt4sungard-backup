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
 * <a href="PollsQuestionLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.polls.service.PollsQuestionLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.polls.service.PollsQuestionLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.polls.service.PollsQuestionLocalService
 * @see com.liferay.portlet.polls.service.PollsQuestionLocalServiceFactory
 *
 */
public class PollsQuestionLocalServiceUtil {
	public static com.liferay.portlet.polls.model.PollsQuestion addPollsQuestion(
		com.liferay.portlet.polls.model.PollsQuestion model)
		throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.addPollsQuestion(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion updatePollsQuestion(
		com.liferay.portlet.polls.model.PollsQuestion model)
		throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.updatePollsQuestion(model);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsChoicePersistence getPollsChoicePersistence() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getPollsChoicePersistence();
	}

	public static void setPollsChoicePersistence(
		com.liferay.portlet.polls.service.persistence.PollsChoicePersistence pollsChoicePersistence) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setPollsChoicePersistence(pollsChoicePersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsChoiceFinder getPollsChoiceFinder() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getPollsChoiceFinder();
	}

	public static void setPollsChoiceFinder(
		com.liferay.portlet.polls.service.persistence.PollsChoiceFinder pollsChoiceFinder) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setPollsChoiceFinder(pollsChoiceFinder);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence getPollsQuestionPersistence() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getPollsQuestionPersistence();
	}

	public static void setPollsQuestionPersistence(
		com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence pollsQuestionPersistence) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setPollsQuestionPersistence(pollsQuestionPersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsVotePersistence getPollsVotePersistence() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getPollsVotePersistence();
	}

	public static void setPollsVotePersistence(
		com.liferay.portlet.polls.service.persistence.PollsVotePersistence pollsVotePersistence) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setPollsVotePersistence(pollsVotePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.polls.model.PollsQuestion addQuestion(
		long userId, long plid, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.addQuestion(userId, plid, title,
			description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion addQuestion(
		java.lang.String uuid, long userId, long plid, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.addQuestion(uuid, userId, plid, title,
			description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion addQuestion(
		long userId, long plid, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire, java.util.List choices,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.addQuestion(userId, plid, title,
			description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire, choices, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion addQuestion(
		long userId, long plid, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire, java.util.List choices,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.addQuestion(userId, plid, title,
			description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire, choices, communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion addQuestion(
		java.lang.String uuid, long userId, long plid, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire, java.util.List choices,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.addQuestion(uuid, userId, plid, title,
			description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire, choices, addCommunityPermissions, addGuestPermissions,
			communityPermissions, guestPermissions);
	}

	public static void addQuestionResources(long questionId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.addQuestionResources(questionId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addQuestionResources(
		com.liferay.portlet.polls.model.PollsQuestion question,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.addQuestionResources(question,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addQuestionResources(long questionId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.addQuestionResources(questionId,
			communityPermissions, guestPermissions);
	}

	public static void addQuestionResources(
		com.liferay.portlet.polls.model.PollsQuestion question,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.addQuestionResources(question,
			communityPermissions, guestPermissions);
	}

	public static void deleteQuestion(long questionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.deleteQuestion(questionId);
	}

	public static void deleteQuestion(
		com.liferay.portlet.polls.model.PollsQuestion question)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.deleteQuestion(question);
	}

	public static void deleteQuestions(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		pollsQuestionLocalService.deleteQuestions(groupId);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion getQuestion(
		long questionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getQuestion(questionId);
	}

	public static java.util.List getQuestions(long groupId)
		throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getQuestions(groupId);
	}

	public static java.util.List getQuestions(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getQuestions(groupId, begin, end);
	}

	public static int getQuestionsCount(long groupId)
		throws com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.getQuestionsCount(groupId);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion updateQuestion(
		long userId, long questionId, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.updateQuestion(userId, questionId,
			title, description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion updateQuestion(
		long userId, long questionId, java.lang.String title,
		java.lang.String description, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire, java.util.List choices)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PollsQuestionLocalService pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getService();

		return pollsQuestionLocalService.updateQuestion(userId, questionId,
			title, description, expirationDateMonth, expirationDateDay,
			expirationDateYear, expirationDateHour, expirationDateMinute,
			neverExpire, choices);
	}
}