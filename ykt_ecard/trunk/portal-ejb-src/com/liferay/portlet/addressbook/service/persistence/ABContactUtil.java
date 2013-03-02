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

package com.liferay.portlet.addressbook.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ABContactUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ABContactUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.addressbook.model.ABContact"),
			"com.liferay.portlet.addressbook.service.persistence.ABContactPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.addressbook.model.ABContact"));

	public static com.liferay.portlet.addressbook.model.ABContact create(
		java.lang.String contactId) {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(contactId);
	}

	public static com.liferay.portlet.addressbook.model.ABContact remove(
		java.lang.String contactId)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(contactId));
		}

		com.liferay.portlet.addressbook.model.ABContact abContact = persistence.remove(contactId);

		if (listener != null) {
			listener.onAfterRemove(abContact);
		}

		return abContact;
	}

	public static com.liferay.portlet.addressbook.model.ABContact update(
		com.liferay.portlet.addressbook.model.ABContact abContact)
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = abContact.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(abContact);
			}
			else {
				listener.onBeforeUpdate(abContact);
			}
		}

		abContact = persistence.update(abContact);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(abContact);
			}
			else {
				listener.onAfterUpdate(abContact);
			}
		}

		return abContact;
	}

	public static java.util.List getABLists(java.lang.String pk)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABLists(pk);
	}

	public static java.util.List getABLists(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABLists(pk, begin, end);
	}

	public static java.util.List getABLists(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABLists(pk, begin, end, obc);
	}

	public static int getABListsSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABListsSize(pk);
	}

	public static void setABLists(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);
		persistence.setABLists(pk, pks);
	}

	public static void setABLists(java.lang.String pk, java.util.List lists)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);
		persistence.setABLists(pk, lists);
	}

	public static boolean addABList(java.lang.String pk,
		java.lang.String abListPK)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABList(pk, abListPK);
	}

	public static boolean addABList(java.lang.String pk,
		com.liferay.portlet.addressbook.model.ABList abList)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABList(pk, abList);
	}

	public static boolean addABLists(java.lang.String pk,
		java.lang.String[] abListPKs)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABLists(pk, abListPKs);
	}

	public static boolean addABLists(java.lang.String pk, java.util.List abLists)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABLists(pk, abLists);
	}

	public static void clearABLists(java.lang.String pk)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearABLists(pk);
	}

	public static boolean containsABList(java.lang.String pk,
		java.lang.String abListPK)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsABList(pk, abListPK);
	}

	public static boolean containsABList(java.lang.String pk,
		com.liferay.portlet.addressbook.model.ABList abList)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsABList(pk, abList);
	}

	public static boolean removeABList(java.lang.String pk,
		java.lang.String abListPK)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABList(pk, abListPK);
	}

	public static boolean removeABList(java.lang.String pk,
		com.liferay.portlet.addressbook.model.ABList abList)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABList(pk, abList);
	}

	public static boolean removeABLists(java.lang.String pk,
		java.lang.String[] abListPKs)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABLists(pk, abListPKs);
	}

	public static boolean removeABLists(java.lang.String pk,
		java.util.List abLists)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABLists(pk, abLists);
	}

	public static com.liferay.portlet.addressbook.model.ABContact findByPrimaryKey(
		java.lang.String contactId)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(contactId);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.addressbook.model.ABContact findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.addressbook.model.ABContact findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.addressbook.model.ABContact[] findByUserId_PrevAndNext(
		java.lang.String contactId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(contactId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ABContactPersistence persistence = (ABContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(ABContactUtil.class);
}