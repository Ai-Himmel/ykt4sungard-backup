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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.blogs.model.BlogsCategory;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.persistence.BlogsCategoryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.spring.BlogsCategoryLocalService;

import java.util.Iterator;

/**
 * <a href="BlogsCategoryLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsCategoryLocalServiceImpl
	implements BlogsCategoryLocalService {

	// Business methods

	public void deleteAll(String userId)
		throws PortalException, SystemException {

		Iterator itr = BlogsCategoryUtil.findByUserId(userId).iterator();

		while (itr.hasNext()) {
			BlogsCategory category = (BlogsCategory)itr.next();

			deleteCategory(category.getCategoryId());
		}
	}

	public void deleteCategory(String categoryId)
		throws PortalException, SystemException {

		Iterator itr = BlogsEntryUtil.findByCategoryId(categoryId).iterator();

		while (itr.hasNext()) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			entry.setCategoryId(BlogsCategory.DEFAULT_PARENT_CATEGORY_ID);

			BlogsEntryUtil.update(entry);
		}

		BlogsCategoryUtil.remove(categoryId);
	}

}