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
 * <a href="MBThreadUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBThreadUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.messageboards.model.MBThread"),
			"com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.messageboards.model.MBThread"));

	public static com.liferay.portlet.messageboards.model.MBThread create(
		java.lang.String threadId) {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(threadId);
	}

	public static com.liferay.portlet.messageboards.model.MBThread remove(
		java.lang.String threadId)
		throws com.liferay.portlet.messageboards.NoSuchThreadException, 
			com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(threadId));
		}

		com.liferay.portlet.messageboards.model.MBThread mbThread = persistence.remove(threadId);

		if (listener != null) {
			listener.onAfterRemove(mbThread);
		}

		return mbThread;
	}

	public static com.liferay.portlet.messageboards.model.MBThread update(
		com.liferay.portlet.messageboards.model.MBThread mbThread)
		throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = mbThread.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mbThread);
			}
			else {
				listener.onBeforeUpdate(mbThread);
			}
		}

		mbThread = persistence.update(mbThread);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mbThread);
			}
			else {
				listener.onAfterUpdate(mbThread);
			}
		}

		return mbThread;
	}

	public static com.liferay.portlet.messageboards.model.MBThread findByPrimaryKey(
		java.lang.String threadId)
		throws com.liferay.portlet.messageboards.NoSuchThreadException, 
			com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(threadId);
	}

	public static java.util.List findByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId);
	}

	public static java.util.List findByTopicId(java.lang.String topicId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId, begin, end);
	}

	public static java.util.List findByTopicId(java.lang.String topicId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId(topicId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBThread findByTopicId_First(
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchThreadException, 
			com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_First(topicId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBThread findByTopicId_Last(
		java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchThreadException, 
			com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_Last(topicId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBThread[] findByTopicId_PrevAndNext(
		java.lang.String threadId, java.lang.String topicId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.messageboards.NoSuchThreadException, 
			com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTopicId_PrevAndNext(threadId, topicId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByTopicId(topicId);
	}

	public static int countByTopicId(java.lang.String topicId)
		throws com.liferay.portal.SystemException {
		MBThreadPersistence persistence = (MBThreadPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByTopicId(topicId);
	}

	private static final Log _log = LogFactory.getLog(MBThreadUtil.class);
}