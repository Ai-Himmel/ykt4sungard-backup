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
 * <a href="MBMessageFlagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessageFlagUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.messageboards.model.MBMessageFlag"),
			"com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.messageboards.model.MBMessageFlag"));

	public static com.liferay.portlet.messageboards.model.MBMessageFlag create(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK) {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(mbMessageFlagPK);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag remove(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(mbMessageFlagPK));
		}

		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag = persistence.remove(mbMessageFlagPK);

		if (listener != null) {
			listener.onAfterRemove(mbMessageFlag);
		}

		return mbMessageFlag;
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag update(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = mbMessageFlag.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mbMessageFlag);
			}
			else {
				listener.onBeforeUpdate(mbMessageFlag);
			}
		}

		mbMessageFlag = persistence.update(mbMessageFlag);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mbMessageFlag);
			}
			else {
				listener.onAfterUpdate(mbMessageFlag);
			}
		}

		return mbMessageFlag;
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByPrimaryKey(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(mbMessageFlagPK);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag[] findByUserId_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(mbMessageFlagPK, userId, obc);
	}

	public static java.util.List findByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId);
	}

	public static java.util.List findByTopicId(java.lang.String topicId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId, begin, end);
	}

	public static java.util.List findByTopicId(java.lang.String topicId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByTopicId_First(
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_First(topicId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByTopicId_Last(
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_Last(topicId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag[] findByTopicId_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK,
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_PrevAndNext(mbMessageFlagPK, topicId,
			obc);
	}

	public static java.util.List findByT_M(java.lang.String topicId,
		java.lang.String messageId) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_M(topicId, messageId);
	}

	public static java.util.List findByT_M(java.lang.String topicId,
		java.lang.String messageId, int begin, int end)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_M(topicId, messageId, begin, end);
	}

	public static java.util.List findByT_M(java.lang.String topicId,
		java.lang.String messageId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_M(topicId, messageId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByT_M_First(
		java.lang.String topicId, java.lang.String messageId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_M_First(topicId, messageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByT_M_Last(
		java.lang.String topicId, java.lang.String messageId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_M_Last(topicId, messageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag[] findByT_M_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK,
		java.lang.String topicId, java.lang.String messageId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_M_PrevAndNext(mbMessageFlagPK, topicId,
			messageId, obc);
	}

	public static java.util.List findByT_U(java.lang.String topicId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_U(topicId, userId);
	}

	public static java.util.List findByT_U(java.lang.String topicId,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_U(topicId, userId, begin, end);
	}

	public static java.util.List findByT_U(java.lang.String topicId,
		java.lang.String userId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_U(topicId, userId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByT_U_First(
		java.lang.String topicId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_U_First(topicId, userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByT_U_Last(
		java.lang.String topicId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_U_Last(topicId, userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag[] findByT_U_PrevAndNext(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK mbMessageFlagPK,
		java.lang.String topicId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchMessageFlagException, 
			com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByT_U_PrevAndNext(mbMessageFlagPK, topicId,
			userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByTopicId(topicId);
	}

	public static void removeByT_M(java.lang.String topicId,
		java.lang.String messageId) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByT_M(topicId, messageId);
	}

	public static void removeByT_U(java.lang.String topicId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByT_U(topicId, userId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByTopicId(topicId);
	}

	public static int countByT_M(java.lang.String topicId,
		java.lang.String messageId) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByT_M(topicId, messageId);
	}

	public static int countByT_U(java.lang.String topicId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		MBMessageFlagPersistence persistence = (MBMessageFlagPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByT_U(topicId, userId);
	}

	private static final Log _log = LogFactory.getLog(MBMessageFlagUtil.class);
}