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
 * <a href="ShoppingCategoryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCategoryUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.shopping.model.ShoppingCategory"),
			"com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingCategory"));

	public static com.liferay.portlet.shopping.model.ShoppingCategory create(
		java.lang.String categoryId) {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(categoryId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory remove(
		java.lang.String categoryId)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(categoryId));
		}

		com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory = persistence.remove(categoryId);

		if (listener != null) {
			listener.onAfterRemove(shoppingCategory);
		}

		return shoppingCategory;
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory update(
		com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = shoppingCategory.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingCategory);
			}
			else {
				listener.onBeforeUpdate(shoppingCategory);
			}
		}

		shoppingCategory = persistence.update(shoppingCategory);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingCategory);
			}
			else {
				listener.onAfterUpdate(shoppingCategory);
			}
		}

		return shoppingCategory;
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory findByPrimaryKey(
		java.lang.String categoryId)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(categoryId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory[] findByCompanyId_PrevAndNext(
		java.lang.String categoryId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(categoryId, companyId,
			obc);
	}

	public static java.util.List findByC_P(java.lang.String companyId,
		java.lang.String parentCategoryId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P(companyId, parentCategoryId);
	}

	public static java.util.List findByC_P(java.lang.String companyId,
		java.lang.String parentCategoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P(companyId, parentCategoryId, begin, end);
	}

	public static java.util.List findByC_P(java.lang.String companyId,
		java.lang.String parentCategoryId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P(companyId, parentCategoryId, begin, end,
			obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory findByC_P_First(
		java.lang.String companyId, java.lang.String parentCategoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P_First(companyId, parentCategoryId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory findByC_P_Last(
		java.lang.String companyId, java.lang.String parentCategoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P_Last(companyId, parentCategoryId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory[] findByC_P_PrevAndNext(
		java.lang.String categoryId, java.lang.String companyId,
		java.lang.String parentCategoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchCategoryException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P_PrevAndNext(categoryId, companyId,
			parentCategoryId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByC_P(java.lang.String companyId,
		java.lang.String parentCategoryId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_P(companyId, parentCategoryId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByC_P(java.lang.String companyId,
		java.lang.String parentCategoryId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryPersistence persistence = (ShoppingCategoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_P(companyId, parentCategoryId);
	}

	private static final Log _log = LogFactory.getLog(ShoppingCategoryUtil.class);
}