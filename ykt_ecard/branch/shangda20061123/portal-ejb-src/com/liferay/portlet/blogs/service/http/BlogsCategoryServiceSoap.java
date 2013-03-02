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

package com.liferay.portlet.blogs.service.http;

import com.liferay.portlet.blogs.service.spring.BlogsCategoryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BlogsCategoryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsCategoryServiceSoap {
	public static com.liferay.portlet.blogs.model.BlogsCategoryModel addCategory(
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsCategory returnValue = BlogsCategoryServiceUtil.addCategory(name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteCategory(java.lang.String categoryId)
		throws RemoteException {
		try {
			BlogsCategoryServiceUtil.deleteCategory(categoryId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteCategory(
		com.liferay.portlet.blogs.model.BlogsCategory category)
		throws RemoteException {
		try {
			BlogsCategoryServiceUtil.deleteCategory(category);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsCategoryModel getCategory(
		java.lang.String categoryId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsCategory returnValue = BlogsCategoryServiceUtil.getCategory(categoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsCategoryModel[] getCategories()
		throws RemoteException {
		try {
			java.util.List returnValue = BlogsCategoryServiceUtil.getCategories();

			return (com.liferay.portlet.blogs.model.BlogsCategory[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsCategoryModel[] getCategories(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = BlogsCategoryServiceUtil.getCategories(userId);

			return (com.liferay.portlet.blogs.model.BlogsCategory[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCategoriesSize(java.lang.String userId)
		throws RemoteException {
		try {
			int returnValue = BlogsCategoryServiceUtil.getCategoriesSize(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsCategoryModel updateCategory(
		java.lang.String categoryId, java.lang.String name)
		throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsCategory returnValue = BlogsCategoryServiceUtil.updateCategory(categoryId,
					name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}