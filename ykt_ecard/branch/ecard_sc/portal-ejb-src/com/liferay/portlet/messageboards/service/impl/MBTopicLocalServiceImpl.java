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

package com.liferay.portlet.messageboards.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.documentlibrary.NoSuchDirectoryException;
import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Company;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBTopic;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.messageboards.service.persistence.MBThreadUtil;
import com.liferay.portlet.messageboards.service.persistence.MBTopicUtil;
import com.liferay.portlet.messageboards.service.spring.MBTopicLocalService;

import java.util.Iterator;

/**
 * <a href="MBTopicLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MBTopicLocalServiceImpl implements MBTopicLocalService {

	// Business methods

	public void deleteAll(String groupId)
		throws PortalException, SystemException {

		Iterator itr = MBTopicUtil.findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			MBTopic topic = (MBTopic)itr.next();

			deleteTopic(topic.getTopicId());
		}
	}

	public void deleteTopic(String topicId)
		throws PortalException, SystemException {

		// Find topic

		MBTopic topic = MBTopicUtil.findByPrimaryKey(topicId);

		// Delete topic

		MBTopicUtil.remove(topicId);

		// Delete all message flags associated with this topic

		MBMessageFlagUtil.removeByTopicId(topicId);

		// Delete all messages associated with this topic

		MBMessageUtil.removeByTopicId(topicId);

		// Delete all threads associated with this topic

		MBThreadUtil.removeByTopicId(topicId);

		// Reset counter associated with this topic

		CounterServiceUtil.reset(
			MBMessage.class.getName() + "." + topicId);

		// File attachments

		String companyId = topic.getCompanyId();
		String portletId = Company.SYSTEM;
		String repositoryId = Company.SYSTEM;
		String dirName = topic.getAttachmentsDir();

		try {
			DLServiceUtil.deleteDirectory(
				companyId, portletId, repositoryId, dirName);
		}
		catch (NoSuchDirectoryException nsde) {
		}
	}

}