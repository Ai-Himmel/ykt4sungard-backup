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
 * <a href="MBMessageServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessageServiceUtil {
	public static final String PORTLET_ID = "19";

	public static void deleteMessage(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();
			mbMessageService.deleteMessage(pk);
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

	public static com.liferay.portlet.messageboards.model.MBMessage getMessage(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getMessage(pk);
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

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getMessageDisplay(pk);
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

	public static java.util.List getMessagesByThread(java.lang.String threadId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getMessagesByThread(threadId);
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

	public static java.util.List getMessagesByTopic(java.lang.String topicId,
		int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getMessagesByTopic(topicId, begin, end);
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

	public static int getMessagesSizeByThread(java.lang.String threadId)
		throws com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getMessagesSizeByThread(threadId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getMessagesSizeByTopic(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getMessagesSizeByTopic(topicId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getReadMessagesSize(java.lang.String topicId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		try {
			MBMessageService mbMessageService = MBMessageServiceFactory.getService();

			return mbMessageService.getReadMessagesSize(topicId, userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}