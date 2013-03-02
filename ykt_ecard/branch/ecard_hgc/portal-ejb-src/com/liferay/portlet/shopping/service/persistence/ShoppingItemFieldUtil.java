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

package com.liferay.portlet.shopping.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ShoppingItemFieldUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemFieldUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.shopping.model.ShoppingItemField"),
			"com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingItemField"));

	public static com.liferay.portlet.shopping.model.ShoppingItemField create(
		java.lang.String itemFieldId) {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(itemFieldId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField remove(
		java.lang.String itemFieldId)
		throws com.liferay.portlet.shopping.NoSuchItemFieldException, 
			com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(itemFieldId));
		}

		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField = persistence.remove(itemFieldId);

		if (listener != null) {
			listener.onAfterRemove(shoppingItemField);
		}

		return shoppingItemField;
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField update(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = shoppingItemField.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingItemField);
			}
			else {
				listener.onBeforeUpdate(shoppingItemField);
			}
		}

		shoppingItemField = persistence.update(shoppingItemField);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingItemField);
			}
			else {
				listener.onAfterUpdate(shoppingItemField);
			}
		}

		return shoppingItemField;
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField findByPrimaryKey(
		java.lang.String itemFieldId)
		throws com.liferay.portlet.shopping.NoSuchItemFieldException, 
			com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(itemFieldId);
	}

	public static java.util.List findByItemId(java.lang.String itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId(itemId);
	}

	public static java.util.List findByItemId(java.lang.String itemId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId(itemId, begin, end);
	}

	public static java.util.List findByItemId(java.lang.String itemId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId(itemId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField findByItemId_First(
		java.lang.String itemId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemFieldException, 
			com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId_First(itemId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField findByItemId_Last(
		java.lang.String itemId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemFieldException, 
			com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId_Last(itemId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField[] findByItemId_PrevAndNext(
		java.lang.String itemFieldId, java.lang.String itemId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemFieldException, 
			com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId_PrevAndNext(itemFieldId, itemId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByItemId(java.lang.String itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByItemId(itemId);
	}

	public static int countByItemId(java.lang.String itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldPersistence persistence = (ShoppingItemFieldPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByItemId(itemId);
	}

	private static final Log _log = LogFactory.getLog(ShoppingItemFieldUtil.class);
}