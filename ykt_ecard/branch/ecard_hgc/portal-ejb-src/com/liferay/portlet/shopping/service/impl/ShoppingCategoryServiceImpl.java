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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.shopping.CategoryNameException;
import com.liferay.portlet.shopping.NoSuchCategoryException;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCategoryService;
import com.liferay.portlet.shopping.service.spring.ShoppingItemServiceUtil;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingCategoryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class ShoppingCategoryServiceImpl
	extends PrincipalBean implements ShoppingCategoryService {

	// Business methods

	public ShoppingCategory addCategory(String parentCategoryId, String name)
		throws PortalException, SystemException {

		parentCategoryId = _getParentCategoryId(parentCategoryId);

		_validate(name);

		if (!hasAdmin()) {
			throw new PrincipalException();
		}

		User user = getUser();

		String categoryId = Long.toString(CounterServiceUtil.increment(
			ShoppingCategory.class.getName()));

		ShoppingCategory category = ShoppingCategoryUtil.create(categoryId);

		Date now = new Date();

		category.setCompanyId(user.getCompanyId());
		category.setCreateDate(now);
		category.setModifiedDate(now);
		category.setParentCategoryId(parentCategoryId);
		category.setName(name);

		ShoppingCategoryUtil.update(category);

		return category;
	}

	public void deleteCategory(String categoryId)
		throws PortalException, SystemException {

		ShoppingCategory category =
			ShoppingCategoryUtil.findByPrimaryKey(categoryId);

		deleteCategory(category);
	}

	public void deleteCategory(ShoppingCategory category)
		throws PortalException, SystemException {

		if (!hasAdmin(category.getCategoryId())) {
			throw new PrincipalException();
		}

		Iterator itr = ShoppingCategoryUtil.findByC_P(
			category.getCompanyId(), category.getCategoryId()).iterator();

		while (itr.hasNext()) {
			deleteCategory((ShoppingCategory)itr.next());
		}

		itr = ShoppingItemUtil.findByC_C(
			category.getCompanyId(), category.getCategoryId()).iterator();

		while (itr.hasNext()) {
			ShoppingItemServiceUtil.deleteItem((ShoppingItem)itr.next());
		}

		ShoppingCategoryUtil.remove(category.getCategoryId());
	}

	public ShoppingCategory getCategory(String categoryId)
		throws PortalException, SystemException {

		return ShoppingCategoryUtil.findByPrimaryKey(categoryId);
	}

	public List getCategories(String companyId) throws SystemException {
		return ShoppingCategoryUtil.findByCompanyId(companyId);
	}

	public List getCategories(String companyId, String parentCategoryId)
		throws SystemException {

		return ShoppingCategoryUtil.findByC_P(companyId, parentCategoryId);
	}

	public List getCategories(ShoppingCategory category)
		throws SystemException {

		return ShoppingCategoryUtil.findByC_P(
			category.getCompanyId(), category.getCategoryId());
	}

	public int getCategoriesSize(String companyId) throws SystemException {
		return ShoppingCategoryUtil.countByCompanyId(companyId);
	}

	public int getCategoriesSize(String companyId, String parentCategoryId)
		throws SystemException {

		return ShoppingCategoryUtil.countByC_P(
			companyId, parentCategoryId);
	}

	public int getCategoriesSize(ShoppingCategory category)
		throws SystemException {

		return ShoppingCategoryUtil.countByC_P(
			category.getCompanyId(), category.getCategoryId());
	}

	public ShoppingCategory getParentCategory(ShoppingCategory category)
		throws PortalException, SystemException {

		ShoppingCategory parentCategory = ShoppingCategoryUtil.findByPrimaryKey(
			category.getParentCategoryId());

		return parentCategory;
	}

	public List getParentCategories(String categoryId)
		throws PortalException, SystemException {

		return getParentCategories(
			ShoppingCategoryUtil.findByPrimaryKey(categoryId));
	}

	public List getParentCategories(ShoppingCategory category)
		throws PortalException, SystemException {

		List parentCategories = new ArrayList();

		ShoppingCategory tempCategory = category;

		for (;;) {
			parentCategories.add(tempCategory);

			if (tempCategory.getParentCategoryId().equals(
					ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID)) {

				break;
			}

			tempCategory = ShoppingCategoryUtil.findByPrimaryKey(
				tempCategory.getParentCategoryId());
		}

		Collections.reverse(parentCategories);

		return parentCategories;
	}

	public ShoppingCategory updateCategory(
			String categoryId, String parentCategoryId, String name)
		throws PortalException, SystemException {

		parentCategoryId = _getParentCategoryId(parentCategoryId);

		_validate(name);

		if (!hasAdmin(categoryId)) {
			throw new PrincipalException();
		}

		ShoppingCategory category =
			ShoppingCategoryUtil.findByPrimaryKey(categoryId);

		category.setModifiedDate(new Date());
		category.setParentCategoryId(parentCategoryId);
		category.setName(name);

		ShoppingCategoryUtil.update(category);

		return category;
	}

	// Permission methods

	public boolean hasAdmin() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.SHOPPING_ADMIN)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasAdmin(String categoryId)
		throws PortalException, SystemException {

		ShoppingCategory category =
			ShoppingCategoryUtil.findByPrimaryKey(categoryId);

		if (getUser().getCompanyId().equals(category.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.SHOPPING_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private String _getParentCategoryId(String parentCategoryId)
		throws PortalException, SystemException {

		if (!parentCategoryId.equals(
				ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID)) {

			// Ensure parent category exists and belongs to the proper company

			try {
				ShoppingCategory parentCategory =
					ShoppingCategoryUtil.findByPrimaryKey(parentCategoryId);

				if (!parentCategory.getCompanyId().equals(
						getUser().getCompanyId())) {

					parentCategoryId =
						ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID;
				}
			}
			catch (NoSuchCategoryException nsce) {
				parentCategoryId = ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID;
			}
		}

		return parentCategoryId;
	}

	private void _validate(String name) throws PortalException {
		if ((Validator.isNull(name)) || (name.indexOf("\\\\") != -1) ||
			(name.indexOf("//") != -1)) {

			throw new CategoryNameException();
		}
	}

}