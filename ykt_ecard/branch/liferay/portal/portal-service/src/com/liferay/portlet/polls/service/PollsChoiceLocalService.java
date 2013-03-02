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
 * <a href="PollsChoiceLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.polls.service.impl.PollsChoiceLocalServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.polls.service.PollsChoiceLocalServiceFactory
 * @see com.liferay.portlet.polls.service.PollsChoiceLocalServiceUtil
 *
 */
public interface PollsChoiceLocalService {
	public com.liferay.portlet.polls.model.PollsChoice addPollsChoice(
		com.liferay.portlet.polls.model.PollsChoice model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsChoice updatePollsChoice(
		com.liferay.portlet.polls.model.PollsChoice model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.service.persistence.PollsChoicePersistence getPollsChoicePersistence();

	public void setPollsChoicePersistence(
		com.liferay.portlet.polls.service.persistence.PollsChoicePersistence pollsChoicePersistence);

	public com.liferay.portlet.polls.service.persistence.PollsChoiceFinder getPollsChoiceFinder();

	public void setPollsChoiceFinder(
		com.liferay.portlet.polls.service.persistence.PollsChoiceFinder pollsChoiceFinder);

	public com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence getPollsQuestionPersistence();

	public void setPollsQuestionPersistence(
		com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence pollsQuestionPersistence);

	public com.liferay.portlet.polls.service.persistence.PollsVotePersistence getPollsVotePersistence();

	public void setPollsVotePersistence(
		com.liferay.portlet.polls.service.persistence.PollsVotePersistence pollsVotePersistence);

	public void afterPropertiesSet();

	public com.liferay.portlet.polls.model.PollsChoice addChoice(
		long questionId, java.lang.String name, java.lang.String description)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.polls.model.PollsChoice addChoice(
		java.lang.String uuid, long questionId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.polls.model.PollsChoice getChoice(long choiceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getChoices(long questionId)
		throws com.liferay.portal.SystemException;

	public int getChoicesCount(long questionId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.polls.model.PollsChoice updateChoice(
		long choiceId, long questionId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}