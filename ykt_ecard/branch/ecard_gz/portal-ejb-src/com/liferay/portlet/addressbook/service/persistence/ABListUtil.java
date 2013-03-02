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
 * <a href="ABListUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ABListUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.addressbook.model.ABList"),
			"com.liferay.portlet.addressbook.service.persistence.ABListPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.addressbook.model.ABList"));

	public static com.liferay.portlet.addressbook.model.ABList create(
		java.lang.String listId) {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(listId);
	}

	public static com.liferay.portlet.addressbook.model.ABList remove(
		java.lang.String listId)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(listId));
		}

		com.liferay.portlet.addressbook.model.ABList abList = persistence.remove(listId);

		if (listener != null) {
			listener.onAfterRemove(abList);
		}

		return abList;
	}

	public static com.liferay.portlet.addressbook.model.ABList update(
		com.liferay.portlet.addressbook.model.ABList abList)
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = abList.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(abList);
			}
			else {
				listener.onBeforeUpdate(abList);
			}
		}

		abList = persistence.update(abList);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(abList);
			}
			else {
				listener.onAfterUpdate(abList);
			}
		}

		return abList;
	}

	public static java.util.List getABContacts(java.lang.String pk)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABContacts(pk);
	}

	public static java.util.List getABContacts(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABContacts(pk, begin, end);
	}

	public static java.util.List getABContacts(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABContacts(pk, begin, end, obc);
	}

	public static int getABContactsSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getABContactsSize(pk);
	}

	public static void setABContacts(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);
		persistence.setABContacts(pk, pks);
	}

	public static void setABContacts(java.lang.String pk,
		java.util.List contacts)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);
		persistence.setABContacts(pk, contacts);
	}

	public static boolean addABContact(java.lang.String pk,
		java.lang.String abContactPK)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABContact(pk, abContactPK);
	}

	public static boolean addABContact(java.lang.String pk,
		com.liferay.portlet.addressbook.model.ABContact abContact)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABContact(pk, abContact);
	}

	public static boolean addABContacts(java.lang.String pk,
		java.lang.String[] abContactPKs)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABContacts(pk, abContactPKs);
	}

	public static boolean addABContacts(java.lang.String pk,
		java.util.List abContacts)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addABContacts(pk, abContacts);
	}

	public static void clearABContacts(java.lang.String pk)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearABContacts(pk);
	}

	public static boolean containsABContact(java.lang.String pk,
		java.lang.String abContactPK)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsABContact(pk, abContactPK);
	}

	public static boolean containsABContact(java.lang.String pk,
		com.liferay.portlet.addressbook.model.ABContact abContact)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsABContact(pk, abContact);
	}

	public static boolean removeABContact(java.lang.String pk,
		java.lang.String abContactPK)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABContact(pk, abContactPK);
	}

	public static boolean removeABContact(java.lang.String pk,
		com.liferay.portlet.addressbook.model.ABContact abContact)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABContact(pk, abContact);
	}

	public static boolean removeABContacts(java.lang.String pk,
		java.lang.String[] abContactPKs)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABContacts(pk, abContactPKs);
	}

	public static boolean removeABContacts(java.lang.String pk,
		java.util.List abContacts)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portlet.addressbook.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeABContacts(pk, abContacts);
	}

	public static com.liferay.portlet.addressbook.model.ABList findByPrimaryKey(
		java.lang.String listId)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(listId);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.addressbook.model.ABList findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.addressbook.model.ABList findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.addressbook.model.ABList[] findByUserId_PrevAndNext(
		java.lang.String listId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.addressbook.NoSuchListException, 
			com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(listId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ABListPersistence persistence = (ABListPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(ABListUtil.class);
}