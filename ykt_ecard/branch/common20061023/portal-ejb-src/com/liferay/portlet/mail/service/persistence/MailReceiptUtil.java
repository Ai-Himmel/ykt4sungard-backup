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

package com.liferay.portlet.mail.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailReceiptUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MailReceiptUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.mail.model.MailReceipt"),
			"com.liferay.portlet.mail.service.persistence.MailReceiptPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.mail.model.MailReceipt"));

	public static com.liferay.portlet.mail.model.MailReceipt create(
		java.lang.String receiptId) {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(receiptId);
	}

	public static com.liferay.portlet.mail.model.MailReceipt remove(
		java.lang.String receiptId)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(receiptId));
		}

		com.liferay.portlet.mail.model.MailReceipt mailReceipt = persistence.remove(receiptId);

		if (listener != null) {
			listener.onAfterRemove(mailReceipt);
		}

		return mailReceipt;
	}

	public static com.liferay.portlet.mail.model.MailReceipt update(
		com.liferay.portlet.mail.model.MailReceipt mailReceipt)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = mailReceipt.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mailReceipt);
			}
			else {
				listener.onBeforeUpdate(mailReceipt);
			}
		}

		mailReceipt = persistence.update(mailReceipt);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mailReceipt);
			}
			else {
				listener.onAfterUpdate(mailReceipt);
			}
		}

		return mailReceipt;
	}

	public static com.liferay.portlet.mail.model.MailReceipt findByPrimaryKey(
		java.lang.String receiptId)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(receiptId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.mail.model.MailReceipt findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.mail.model.MailReceipt findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.mail.model.MailReceipt[] findByCompanyId_PrevAndNext(
		java.lang.String receiptId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(receiptId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.mail.model.MailReceipt findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.mail.model.MailReceipt findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.mail.model.MailReceipt[] findByUserId_PrevAndNext(
		java.lang.String receiptId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.mail.NoSuchReceiptException, 
			com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(receiptId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		MailReceiptPersistence persistence = (MailReceiptPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(MailReceiptUtil.class);
}