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

package com.liferay.portlet.messageboards.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBMessageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessageUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.messageboards.model.MBMessage"),
			"com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.messageboards.model.MBMessage"));

	public static com.liferay.portlet.messageboards.model.MBMessage create(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK) {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(mbMessagePK);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage remove(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(mbMessagePK));
		}

		com.liferay.portlet.messageboards.model.MBMessage mbMessage = persistence.remove(mbMessagePK);

		if (listener != null) {
			listener.onAfterRemove(mbMessage);
		}

		return mbMessage;
	}

	public static com.liferay.portlet.messageboards.model.MBMessage update(
		com.liferay.portlet.messageboards.model.MBMessage mbMessage)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = mbMessage.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mbMessage);
			}
			else {
				listener.onBeforeUpdate(mbMessage);
			}
		}

		mbMessage = persistence.update(mbMessage);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mbMessage);
			}
			else {
				listener.onAfterUpdate(mbMessage);
			}
		}

		return mbMessage;
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByPrimaryKey(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(mbMessagePK);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByCompanyId_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(mbMessagePK, companyId,
			obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByUserId_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(mbMessagePK, userId, obc);
	}

	public static java.util.List findByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId);
	}

	public static java.util.List findByTopicId(java.lang.String topicId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId, begin, end);
	}

	public static java.util.List findByTopicId(java.lang.String topicId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByTopicId_First(
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_First(topicId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByTopicId_Last(
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_Last(topicId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByTopicId_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK,
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_PrevAndNext(mbMessagePK, topicId, obc);
	}

	public static java.util.List findByThreadId(java.lang.String threadId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByThreadId(threadId);
	}

	public static java.util.List findByThreadId(java.lang.String threadId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByThreadId(threadId, begin, end);
	}

	public static java.util.List findByThreadId(java.lang.String threadId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByThreadId(threadId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByThreadId_First(
		java.lang.String threadId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByThreadId_First(threadId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByThreadId_Last(
		java.lang.String threadId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByThreadId_Last(threadId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByThreadId_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK,
		java.lang.String threadId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByThreadId_PrevAndNext(mbMessagePK, threadId, obc);
	}

	public static java.util.List findByT_P(java.lang.String threadId,
		java.lang.String parentMessageId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_P(threadId, parentMessageId);
	}

	public static java.util.List findByT_P(java.lang.String threadId,
		java.lang.String parentMessageId, int begin, int end)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_P(threadId, parentMessageId, begin, end);
	}

	public static java.util.List findByT_P(java.lang.String threadId,
		java.lang.String parentMessageId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_P(threadId, parentMessageId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByT_P_First(
		java.lang.String threadId, java.lang.String parentMessageId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_P_First(threadId, parentMessageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByT_P_Last(
		java.lang.String threadId, java.lang.String parentMessageId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_P_Last(threadId, parentMessageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByT_P_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK mbMessagePK,
		java.lang.String threadId, java.lang.String parentMessageId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageException, 
			com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_P_PrevAndNext(mbMessagePK, threadId,
			parentMessageId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByTopicId(topicId);
	}

	public static void removeByThreadId(java.lang.String threadId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByThreadId(threadId);
	}

	public static void removeByT_P(java.lang.String threadId,
		java.lang.String parentMessageId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByT_P(threadId, parentMessageId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByTopicId(topicId);
	}

	public static int countByThreadId(java.lang.String threadId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByThreadId(threadId);
	}

	public static int countByT_P(java.lang.String threadId,
		java.lang.String parentMessageId)
		throws com.liferay.portal.SystemException {
		MBMessagePersistence persistence = (MBMessagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByT_P(threadId, parentMessageId);
	}

	private static final Log _log = LogFactory.getLog(MBMessageUtil.class);
}