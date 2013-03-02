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

package com.liferay.portal.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ContactUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ContactUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.Contact"),
			"com.liferay.portal.service.persistence.ContactPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Contact"));

	public static com.liferay.portal.model.Contact create(
		java.lang.String contactId) {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(contactId);
	}

	public static com.liferay.portal.model.Contact remove(
		java.lang.String contactId)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);
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

		com.liferay.portal.model.Contact contact = persistence.remove(contactId);

		if (listener != null) {
			listener.onAfterRemove(contact);
		}

		return contact;
	}

	public static com.liferay.portal.model.Contact update(
		com.liferay.portal.model.Contact contact)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = contact.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(contact);
			}
			else {
				listener.onBeforeUpdate(contact);
			}
		}

		contact = persistence.update(contact);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(contact);
			}
			else {
				listener.onAfterUpdate(contact);
			}
		}

		return contact;
	}

	public static com.liferay.portal.model.Contact findByPrimaryKey(
		java.lang.String contactId)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(contactId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Contact findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Contact findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Contact[] findByCompanyId_PrevAndNext(
		java.lang.String contactId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(contactId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portal.model.Contact findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.Contact findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.Contact[] findByUserId_PrevAndNext(
		java.lang.String contactId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchContactException, 
			com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(contactId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ContactPersistence persistence = (ContactPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(ContactUtil.class);
}