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

package com.liferay.portlet.polls.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.polls.model.PollsQuestion;
import com.liferay.portlet.polls.model.impl.PollsQuestionImpl;
import com.liferay.portlet.polls.service.PollsChoiceLocalService;
import com.liferay.portlet.polls.service.PollsChoiceLocalServiceFactory;
import com.liferay.portlet.polls.service.PollsQuestionLocalService;
import com.liferay.portlet.polls.service.PollsVoteLocalService;
import com.liferay.portlet.polls.service.PollsVoteLocalServiceFactory;
import com.liferay.portlet.polls.service.PollsVoteService;
import com.liferay.portlet.polls.service.PollsVoteServiceFactory;
import com.liferay.portlet.polls.service.persistence.PollsChoiceFinder;
import com.liferay.portlet.polls.service.persistence.PollsChoiceFinderUtil;
import com.liferay.portlet.polls.service.persistence.PollsChoicePersistence;
import com.liferay.portlet.polls.service.persistence.PollsChoiceUtil;
import com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence;
import com.liferay.portlet.polls.service.persistence.PollsQuestionUtil;
import com.liferay.portlet.polls.service.persistence.PollsVotePersistence;
import com.liferay.portlet.polls.service.persistence.PollsVoteUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="PollsQuestionLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class PollsQuestionLocalServiceBaseImpl
	implements PollsQuestionLocalService, InitializingBean {
	public PollsQuestion addPollsQuestion(PollsQuestion model)
		throws SystemException {
		PollsQuestion pollsQuestion = new PollsQuestionImpl();

		pollsQuestion.setNew(true);

		pollsQuestion.setUuid(model.getUuid());
		pollsQuestion.setQuestionId(model.getQuestionId());
		pollsQuestion.setGroupId(model.getGroupId());
		pollsQuestion.setCompanyId(model.getCompanyId());
		pollsQuestion.setUserId(model.getUserId());
		pollsQuestion.setUserName(model.getUserName());
		pollsQuestion.setCreateDate(model.getCreateDate());
		pollsQuestion.setModifiedDate(model.getModifiedDate());
		pollsQuestion.setTitle(model.getTitle());
		pollsQuestion.setDescription(model.getDescription());
		pollsQuestion.setExpirationDate(model.getExpirationDate());
		pollsQuestion.setLastVoteDate(model.getLastVoteDate());

		return pollsQuestionPersistence.update(pollsQuestion);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return pollsQuestionPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return pollsQuestionPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public PollsQuestion updatePollsQuestion(PollsQuestion model)
		throws SystemException {
		PollsQuestion pollsQuestion = new PollsQuestionImpl();

		pollsQuestion.setNew(false);

		pollsQuestion.setUuid(model.getUuid());
		pollsQuestion.setQuestionId(model.getQuestionId());
		pollsQuestion.setGroupId(model.getGroupId());
		pollsQuestion.setCompanyId(model.getCompanyId());
		pollsQuestion.setUserId(model.getUserId());
		pollsQuestion.setUserName(model.getUserName());
		pollsQuestion.setCreateDate(model.getCreateDate());
		pollsQuestion.setModifiedDate(model.getModifiedDate());
		pollsQuestion.setTitle(model.getTitle());
		pollsQuestion.setDescription(model.getDescription());
		pollsQuestion.setExpirationDate(model.getExpirationDate());
		pollsQuestion.setLastVoteDate(model.getLastVoteDate());

		return pollsQuestionPersistence.update(pollsQuestion);
	}

	public PollsChoiceLocalService getPollsChoiceLocalService() {
		return pollsChoiceLocalService;
	}

	public void setPollsChoiceLocalService(
		PollsChoiceLocalService pollsChoiceLocalService) {
		this.pollsChoiceLocalService = pollsChoiceLocalService;
	}

	public PollsChoicePersistence getPollsChoicePersistence() {
		return pollsChoicePersistence;
	}

	public void setPollsChoicePersistence(
		PollsChoicePersistence pollsChoicePersistence) {
		this.pollsChoicePersistence = pollsChoicePersistence;
	}

	public PollsChoiceFinder getPollsChoiceFinder() {
		return pollsChoiceFinder;
	}

	public void setPollsChoiceFinder(PollsChoiceFinder pollsChoiceFinder) {
		this.pollsChoiceFinder = pollsChoiceFinder;
	}

	public PollsQuestionPersistence getPollsQuestionPersistence() {
		return pollsQuestionPersistence;
	}

	public void setPollsQuestionPersistence(
		PollsQuestionPersistence pollsQuestionPersistence) {
		this.pollsQuestionPersistence = pollsQuestionPersistence;
	}

	public PollsVoteLocalService getPollsVoteLocalService() {
		return pollsVoteLocalService;
	}

	public void setPollsVoteLocalService(
		PollsVoteLocalService pollsVoteLocalService) {
		this.pollsVoteLocalService = pollsVoteLocalService;
	}

	public PollsVoteService getPollsVoteService() {
		return pollsVoteService;
	}

	public void setPollsVoteService(PollsVoteService pollsVoteService) {
		this.pollsVoteService = pollsVoteService;
	}

	public PollsVotePersistence getPollsVotePersistence() {
		return pollsVotePersistence;
	}

	public void setPollsVotePersistence(
		PollsVotePersistence pollsVotePersistence) {
		this.pollsVotePersistence = pollsVotePersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public ResourceLocalService getResourceLocalService() {
		return resourceLocalService;
	}

	public void setResourceLocalService(
		ResourceLocalService resourceLocalService) {
		this.resourceLocalService = resourceLocalService;
	}

	public ResourceService getResourceService() {
		return resourceService;
	}

	public void setResourceService(ResourceService resourceService) {
		this.resourceService = resourceService;
	}

	public ResourcePersistence getResourcePersistence() {
		return resourcePersistence;
	}

	public void setResourcePersistence(ResourcePersistence resourcePersistence) {
		this.resourcePersistence = resourcePersistence;
	}

	public ResourceFinder getResourceFinder() {
		return resourceFinder;
	}

	public void setResourceFinder(ResourceFinder resourceFinder) {
		this.resourceFinder = resourceFinder;
	}

	public UserLocalService getUserLocalService() {
		return userLocalService;
	}

	public void setUserLocalService(UserLocalService userLocalService) {
		this.userLocalService = userLocalService;
	}

	public UserService getUserService() {
		return userService;
	}

	public void setUserService(UserService userService) {
		this.userService = userService;
	}

	public UserPersistence getUserPersistence() {
		return userPersistence;
	}

	public void setUserPersistence(UserPersistence userPersistence) {
		this.userPersistence = userPersistence;
	}

	public UserFinder getUserFinder() {
		return userFinder;
	}

	public void setUserFinder(UserFinder userFinder) {
		this.userFinder = userFinder;
	}

	public void afterPropertiesSet() {
		if (pollsChoiceLocalService == null) {
			pollsChoiceLocalService = PollsChoiceLocalServiceFactory.getImpl();
		}

		if (pollsChoicePersistence == null) {
			pollsChoicePersistence = PollsChoiceUtil.getPersistence();
		}

		if (pollsChoiceFinder == null) {
			pollsChoiceFinder = PollsChoiceFinderUtil.getFinder();
		}

		if (pollsQuestionPersistence == null) {
			pollsQuestionPersistence = PollsQuestionUtil.getPersistence();
		}

		if (pollsVoteLocalService == null) {
			pollsVoteLocalService = PollsVoteLocalServiceFactory.getImpl();
		}

		if (pollsVoteService == null) {
			pollsVoteService = PollsVoteServiceFactory.getImpl();
		}

		if (pollsVotePersistence == null) {
			pollsVotePersistence = PollsVoteUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (resourceLocalService == null) {
			resourceLocalService = ResourceLocalServiceFactory.getImpl();
		}

		if (resourceService == null) {
			resourceService = ResourceServiceFactory.getImpl();
		}

		if (resourcePersistence == null) {
			resourcePersistence = ResourceUtil.getPersistence();
		}

		if (resourceFinder == null) {
			resourceFinder = ResourceFinderUtil.getFinder();
		}

		if (userLocalService == null) {
			userLocalService = UserLocalServiceFactory.getImpl();
		}

		if (userService == null) {
			userService = UserServiceFactory.getImpl();
		}

		if (userPersistence == null) {
			userPersistence = UserUtil.getPersistence();
		}

		if (userFinder == null) {
			userFinder = UserFinderUtil.getFinder();
		}
	}

	protected PollsChoiceLocalService pollsChoiceLocalService;
	protected PollsChoicePersistence pollsChoicePersistence;
	protected PollsChoiceFinder pollsChoiceFinder;
	protected PollsQuestionPersistence pollsQuestionPersistence;
	protected PollsVoteLocalService pollsVoteLocalService;
	protected PollsVoteService pollsVoteService;
	protected PollsVotePersistence pollsVotePersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
}