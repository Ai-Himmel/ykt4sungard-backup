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

package com.liferay.portlet.biblejournal.service.spring;

/**
 * <a href="BJTopicServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJTopicServiceUtil {
	public static com.liferay.portlet.biblejournal.model.BJTopic addTopic(
		java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();

			return bjTopicService.addTopic(name, description);
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
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();
			bjTopicService.deleteTopic(topicId);
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

	public static void deleteTopic(
		com.liferay.portlet.biblejournal.model.BJTopic topic)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();
			bjTopicService.deleteTopic(topic);
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

	public static java.util.List getEntries(java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();

			return bjTopicService.getEntries(topicId);
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

	public static com.liferay.portlet.biblejournal.model.BJTopic getTopic(
		java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();

			return bjTopicService.getTopic(topicId);
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

	public static java.util.List getTopicsByCompany(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();

			return bjTopicService.getTopicsByCompany(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getTopicsByUser(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();

			return bjTopicService.getTopicsByUser(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic updateTopic(
		java.lang.String topicId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJTopicService bjTopicService = BJTopicServiceFactory.getService();

			return bjTopicService.updateTopic(topicId, name, description);
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