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
 * <a href="MBTopicUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBTopicUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.messageboards.model.MBTopic"),
			"com.liferay.portlet.messageboards.service.persistence.MBTopicPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.messageboards.model.MBTopic"));

	public static com.liferay.portlet.messageboards.model.MBTopic create(
		java.lang.String topicId) {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(topicId);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic remove(
		java.lang.String topicId)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(topicId));
		}

		com.liferay.portlet.messageboards.model.MBTopic mbTopic = persistence.remove(topicId);

		if (listener != null) {
			listener.onAfterRemove(mbTopic);
		}

		return mbTopic;
	}

	public static com.liferay.portlet.messageboards.model.MBTopic update(
		com.liferay.portlet.messageboards.model.MBTopic mbTopic)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = mbTopic.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mbTopic);
			}
			else {
				listener.onBeforeUpdate(mbTopic);
			}
		}

		mbTopic = persistence.update(mbTopic);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mbTopic);
			}
			else {
				listener.onAfterUpdate(mbTopic);
			}
		}

		return mbTopic;
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByPrimaryKey(
		java.lang.String topicId)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(topicId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic[] findByGroupId_PrevAndNext(
		java.lang.String topicId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(topicId, groupId, obc);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic[] findByCompanyId_PrevAndNext(
		java.lang.String topicId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(topicId, companyId, obc);
	}

	public static java.util.List findByP_G_C_R(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String[] readRolesArray)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_R(portletId, groupId, companyId,
			readRolesArray);
	}

	public static java.util.List findByP_G_C_R(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String[] readRolesArray, int begin, int end)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_R(portletId, groupId, companyId,
			readRolesArray, begin, end);
	}

	public static java.util.List findByP_G_C_R(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String[] readRolesArray, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_R(portletId, groupId, companyId,
			readRolesArray, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByP_G_C_R_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String[] readRolesArray,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_R_First(portletId, groupId, companyId,
			readRolesArray, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic findByP_G_C_R_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String[] readRolesArray,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_R_Last(portletId, groupId, companyId,
			readRolesArray, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBTopic[] findByP_G_C_R_PrevAndNext(
		java.lang.String topicId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String[] readRolesArray,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_R_PrevAndNext(topicId, portletId,
			groupId, companyId, readRolesArray, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByP_G_C_R(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String[] readRolesArray)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C_R(portletId, groupId, companyId,
			readRolesArray);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByP_G_C_R(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String[] readRolesArray)
		throws com.liferay.portal.SystemException {
		MBTopicPersistence persistence = (MBTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C_R(portletId, groupId, companyId,
			readRolesArray);
	}

	private static final Log _log = LogFactory.getLog(MBTopicUtil.class);
}