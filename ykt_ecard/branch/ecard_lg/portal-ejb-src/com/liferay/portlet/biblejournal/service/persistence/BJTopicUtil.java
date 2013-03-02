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

package com.liferay.portlet.biblejournal.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BJTopicUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJTopicUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.biblejournal.model.BJTopic"),
			"com.liferay.portlet.biblejournal.service.persistence.BJTopicPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.biblejournal.model.BJTopic"));

	public static com.liferay.portlet.biblejournal.model.BJTopic create(
		java.lang.String topicId) {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(topicId);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic remove(
		java.lang.String topicId)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
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

		com.liferay.portlet.biblejournal.model.BJTopic bjTopic = persistence.remove(topicId);

		if (listener != null) {
			listener.onAfterRemove(bjTopic);
		}

		return bjTopic;
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic update(
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = bjTopic.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(bjTopic);
			}
			else {
				listener.onBeforeUpdate(bjTopic);
			}
		}

		bjTopic = persistence.update(bjTopic);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(bjTopic);
			}
			else {
				listener.onAfterUpdate(bjTopic);
			}
		}

		return bjTopic;
	}

	public static java.util.List getBJEntries(java.lang.String pk)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJEntries(pk);
	}

	public static java.util.List getBJEntries(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJEntries(pk, begin, end);
	}

	public static java.util.List getBJEntries(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJEntries(pk, begin, end, obc);
	}

	public static int getBJEntriesSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJEntriesSize(pk);
	}

	public static void setBJEntries(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.setBJEntries(pk, pks);
	}

	public static void setBJEntries(java.lang.String pk, java.util.List entries)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.setBJEntries(pk, entries);
	}

	public static boolean addBJEntry(java.lang.String pk,
		java.lang.String bjEntryPK)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJEntry(pk, bjEntryPK);
	}

	public static boolean addBJEntry(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJEntry(pk, bjEntry);
	}

	public static boolean addBJEntries(java.lang.String pk,
		java.lang.String[] bjEntryPKs)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJEntries(pk, bjEntryPKs);
	}

	public static boolean addBJEntries(java.lang.String pk,
		java.util.List bjEntries)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJEntries(pk, bjEntries);
	}

	public static void clearBJEntries(java.lang.String pk)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearBJEntries(pk);
	}

	public static boolean containsBJEntry(java.lang.String pk,
		java.lang.String bjEntryPK)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsBJEntry(pk, bjEntryPK);
	}

	public static boolean containsBJEntry(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsBJEntry(pk, bjEntry);
	}

	public static boolean removeBJEntry(java.lang.String pk,
		java.lang.String bjEntryPK)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJEntry(pk, bjEntryPK);
	}

	public static boolean removeBJEntry(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJEntry(pk, bjEntry);
	}

	public static boolean removeBJEntries(java.lang.String pk,
		java.lang.String[] bjEntryPKs)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJEntries(pk, bjEntryPKs);
	}

	public static boolean removeBJEntries(java.lang.String pk,
		java.util.List bjEntries)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJEntries(pk, bjEntries);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic findByPrimaryKey(
		java.lang.String topicId)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(topicId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic[] findByCompanyId_PrevAndNext(
		java.lang.String topicId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(topicId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJTopic[] findByUserId_PrevAndNext(
		java.lang.String topicId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(topicId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BJTopicPersistence persistence = (BJTopicPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(BJTopicUtil.class);
}