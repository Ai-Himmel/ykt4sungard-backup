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

package com.liferay.portlet.biblejournal.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.biblejournal.TopicDescriptionException;
import com.liferay.portlet.biblejournal.TopicNameException;
import com.liferay.portlet.biblejournal.model.BJTopic;
import com.liferay.portlet.biblejournal.service.persistence.BJTopicUtil;
import com.liferay.portlet.biblejournal.service.spring.BJTopicService;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;

/**
 * <a href="BJTopicServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BJTopicServiceImpl
	extends PrincipalBean implements BJTopicService {

	// Business methods

	public BJTopic addTopic(String name, String description)
		throws PortalException, SystemException {

		_validate(name, description);

		User user = getUser();

		String topicId = Long.toString(CounterServiceUtil.increment(
			BJTopic.class.getName()));

		BJTopic topic = BJTopicUtil.create(topicId);

		Date now = new Date();

		topic.setCompanyId(user.getCompanyId());
		topic.setUserId(user.getUserId());
		topic.setCreateDate(now);
		topic.setModifiedDate(now);
		topic.setName(name);
		topic.setDescription(description);

		BJTopicUtil.update(topic);

		return topic;
	}

	public void deleteTopic(String topicId)
		throws PortalException, SystemException {

		BJTopic topic = BJTopicUtil.findByPrimaryKey(topicId);

		deleteTopic(topic);
	}

	public void deleteTopic(BJTopic topic)
		throws PortalException, SystemException {

		if (!topic.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		BJTopicUtil.remove(topic.getTopicId());
	}

	public List getEntries(String topicId)
		throws PortalException, SystemException {

		return BJTopicUtil.getBJEntries(topicId);
	}

	public BJTopic getTopic(String topicId)
		throws PortalException, SystemException {

		return BJTopicUtil.findByPrimaryKey(topicId);
	}

	public List getTopicsByCompany(String companyId) throws SystemException {
		return BJTopicUtil.findByCompanyId(companyId);
	}

	public List getTopicsByUser(String userId) throws SystemException {
		return BJTopicUtil.findByUserId(userId);
	}

	public BJTopic updateTopic(String topicId, String name, String description)
		throws PortalException, SystemException {

		_validate(name, description);

		BJTopic topic = BJTopicUtil.findByPrimaryKey(topicId);

		if (!topic.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		topic.setModifiedDate(new Date());
		topic.setName(name);
		topic.setDescription(description);

		BJTopicUtil.update(topic);

		return topic;
	}

	// Private methods

	private void _validate(String name, String description)
		throws PortalException {

		if (Validator.isNull(name)) {
			throw new TopicNameException();
		}
		else if (Validator.isNull(description)) {
			throw new TopicDescriptionException();
		}
	}

}