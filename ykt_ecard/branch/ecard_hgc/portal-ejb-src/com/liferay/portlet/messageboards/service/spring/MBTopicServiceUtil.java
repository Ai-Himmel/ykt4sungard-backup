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

package com.liferay.portlet.messageboards.service.spring;

/**
 * <a href="MBTopicServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBTopicServiceUtil {
	public static final String PORTLET_ID = "19";

	public static com.liferay.portlet.messageboards.model.MBTopic addTopic(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String readRoles, java.lang.String writeRoles,
		java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.addTopic(portletId, groupId, readRoles,
				writeRoles, name, description);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteTopic(java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();
			mbTopicService.deleteTopic(topicId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.messageboards.model.MBTopic getTopic(
		java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.getTopic(topicId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getTopics(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.getTopics(portletId, groupId, companyId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getTopics(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.getTopics(portletId, groupId, companyId,
				begin, end);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getTopicsSize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.getTopicsSize(portletId, groupId, companyId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessage postNewThread(
		java.lang.String topicId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.postNewThread(topicId, subject, body, files,
				anonymous);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessage postReply(
		java.lang.String topicId, java.lang.String threadId,
		java.lang.String parentMessageId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.postReply(topicId, threadId, parentMessageId,
				subject, body, files, anonymous);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();
			mbTopicService.reIndex(ids);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String[] topicIds,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.search(companyId, portletId, groupId,
				topicIds, keywords);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.messageboards.model.MBTopic updateTopic(
		java.lang.String topicId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.updateTopic(topicId, readRoles, writeRoles,
				name, description);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin(java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.hasAdmin(topicId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasRead(java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.hasRead(topicId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasWrite(java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBTopicService mbTopicService = MBTopicServiceFactory.getService();

			return mbTopicService.hasWrite(topicId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}