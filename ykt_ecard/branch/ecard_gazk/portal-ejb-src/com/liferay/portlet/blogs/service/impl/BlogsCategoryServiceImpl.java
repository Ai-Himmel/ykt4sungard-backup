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

package com.liferay.portlet.blogs.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.blogs.CategoryNameException;
import com.liferay.portlet.blogs.model.BlogsCategory;
import com.liferay.portlet.blogs.service.persistence.BlogsCategoryUtil;
import com.liferay.portlet.blogs.service.spring.BlogsCategoryLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsCategoryService;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;

/**
 * <a href="BlogsCategoryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsCategoryServiceImpl
	extends PrincipalBean implements BlogsCategoryService {

	// Business methods

	public BlogsCategory addCategory(String name)
		throws PortalException, SystemException {

		_validate(name);

		User user = getUser();

		String categoryId = Long.toString(CounterServiceUtil.increment(
			BlogsCategory.class.getName()));

		BlogsCategory category = BlogsCategoryUtil.create(categoryId);

		Date now = new Date();

		category.setCompanyId(user.getCompanyId());
		category.setUserId(user.getUserId());
		category.setCreateDate(now);
		category.setModifiedDate(now);
		category.setName(name);

		BlogsCategoryUtil.update(category);

		return category;
	}

	public void deleteCategory(String categoryId)
		throws PortalException, SystemException {

		BlogsCategory category = BlogsCategoryUtil.findByPrimaryKey(categoryId);

		deleteCategory(category);
	}

	public void deleteCategory(BlogsCategory category)
		throws PortalException, SystemException {

		if (!category.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		BlogsCategoryLocalServiceUtil.deleteCategory(category.getCategoryId());
	}

	public BlogsCategory getCategory(String categoryId)
		throws PortalException, SystemException {

		return BlogsCategoryUtil.findByPrimaryKey(categoryId);
	}

	public List getCategories() throws PortalException, SystemException {
		User user = getUser();

		if (hasAdministrator(user.getCompanyId())) {
			throw new PrincipalException();
		}

		return BlogsCategoryUtil.findByCompanyId(user.getCompanyId());
	}

	public List getCategories(String userId) throws SystemException {
		return BlogsCategoryUtil.findByUserId(userId);
	}

	public int getCategoriesSize(String userId) throws SystemException {
		return BlogsCategoryUtil.countByUserId(userId);
	}

	public BlogsCategory updateCategory(String categoryId, String name)
		throws PortalException, SystemException {

		_validate(name);

		BlogsCategory category = BlogsCategoryUtil.findByPrimaryKey(categoryId);

		if (!category.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		category.setModifiedDate(new Date());
		category.setName(name);

		BlogsCategoryUtil.update(category);

		return category;
	}

	// Private methods

	private void _validate(String name) throws PortalException {
		if (Validator.isNull(name)) {
			throw new CategoryNameException();
		}
	}

}