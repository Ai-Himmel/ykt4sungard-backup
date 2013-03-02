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
 * <a href="BJEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJEntryUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.biblejournal.model.BJEntry"),
			"com.liferay.portlet.biblejournal.service.persistence.BJEntryPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.biblejournal.model.BJEntry"));

	public static com.liferay.portlet.biblejournal.model.BJEntry create(
		java.lang.String entryId) {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(entryId);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry remove(
		java.lang.String entryId)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(entryId));
		}

		com.liferay.portlet.biblejournal.model.BJEntry bjEntry = persistence.remove(entryId);

		if (listener != null) {
			listener.onAfterRemove(bjEntry);
		}

		return bjEntry;
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry update(
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = bjEntry.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(bjEntry);
			}
			else {
				listener.onBeforeUpdate(bjEntry);
			}
		}

		bjEntry = persistence.update(bjEntry);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(bjEntry);
			}
			else {
				listener.onAfterUpdate(bjEntry);
			}
		}

		return bjEntry;
	}

	public static java.util.List getBJVerses(java.lang.String pk)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJVerses(pk);
	}

	public static java.util.List getBJVerses(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJVerses(pk, begin, end);
	}

	public static java.util.List getBJVerses(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJVerses(pk, begin, end, obc);
	}

	public static int getBJVersesSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJVersesSize(pk);
	}

	public static void setBJVerses(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.setBJVerses(pk, pks);
	}

	public static void setBJVerses(java.lang.String pk, java.util.List verses)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.setBJVerses(pk, verses);
	}

	public static boolean addBJVerse(java.lang.String pk,
		java.lang.String bjVersePK)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJVerse(pk, bjVersePK);
	}

	public static boolean addBJVerse(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJVerse(pk, bjVerse);
	}

	public static boolean addBJVerses(java.lang.String pk,
		java.lang.String[] bjVersePKs)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJVerses(pk, bjVersePKs);
	}

	public static boolean addBJVerses(java.lang.String pk,
		java.util.List bjVerses)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJVerses(pk, bjVerses);
	}

	public static void clearBJVerses(java.lang.String pk)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearBJVerses(pk);
	}

	public static boolean containsBJVerse(java.lang.String pk,
		java.lang.String bjVersePK)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsBJVerse(pk, bjVersePK);
	}

	public static boolean containsBJVerse(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsBJVerse(pk, bjVerse);
	}

	public static boolean removeBJVerse(java.lang.String pk,
		java.lang.String bjVersePK)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJVerse(pk, bjVersePK);
	}

	public static boolean removeBJVerse(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJVerse(pk, bjVerse);
	}

	public static boolean removeBJVerses(java.lang.String pk,
		java.lang.String[] bjVersePKs)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJVerses(pk, bjVersePKs);
	}

	public static boolean removeBJVerses(java.lang.String pk,
		java.util.List bjVerses)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJVerses(pk, bjVerses);
	}

	public static java.util.List getBJTopics(java.lang.String pk)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJTopics(pk);
	}

	public static java.util.List getBJTopics(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJTopics(pk, begin, end);
	}

	public static java.util.List getBJTopics(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJTopics(pk, begin, end, obc);
	}

	public static int getBJTopicsSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getBJTopicsSize(pk);
	}

	public static void setBJTopics(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.setBJTopics(pk, pks);
	}

	public static void setBJTopics(java.lang.String pk, java.util.List topics)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.setBJTopics(pk, topics);
	}

	public static boolean addBJTopic(java.lang.String pk,
		java.lang.String bjTopicPK)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJTopic(pk, bjTopicPK);
	}

	public static boolean addBJTopic(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJTopic(pk, bjTopic);
	}

	public static boolean addBJTopics(java.lang.String pk,
		java.lang.String[] bjTopicPKs)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJTopics(pk, bjTopicPKs);
	}

	public static boolean addBJTopics(java.lang.String pk,
		java.util.List bjTopics)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addBJTopics(pk, bjTopics);
	}

	public static void clearBJTopics(java.lang.String pk)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearBJTopics(pk);
	}

	public static boolean containsBJTopic(java.lang.String pk,
		java.lang.String bjTopicPK)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsBJTopic(pk, bjTopicPK);
	}

	public static boolean containsBJTopic(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsBJTopic(pk, bjTopic);
	}

	public static boolean removeBJTopic(java.lang.String pk,
		java.lang.String bjTopicPK)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJTopic(pk, bjTopicPK);
	}

	public static boolean removeBJTopic(java.lang.String pk,
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJTopic(pk, bjTopic);
	}

	public static boolean removeBJTopics(java.lang.String pk,
		java.lang.String[] bjTopicPKs)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJTopics(pk, bjTopicPKs);
	}

	public static boolean removeBJTopics(java.lang.String pk,
		java.util.List bjTopics)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeBJTopics(pk, bjTopics);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry findByPrimaryKey(
		java.lang.String entryId)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(entryId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry[] findByCompanyId_PrevAndNext(
		java.lang.String entryId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(entryId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry[] findByUserId_PrevAndNext(
		java.lang.String entryId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.biblejournal.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(entryId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BJEntryPersistence persistence = (BJEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(BJEntryUtil.class);
}