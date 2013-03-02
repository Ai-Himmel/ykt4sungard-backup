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

package com.liferay.portlet.shopping.service.http;

import com.liferay.portlet.shopping.service.spring.ShoppingCategoryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingCategoryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCategoryServiceSoap {
	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel addCategory(
		java.lang.String parentCategoryId, java.lang.String name)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCategory returnValue = ShoppingCategoryServiceUtil.addCategory(parentCategoryId,
					name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteCategory(java.lang.String categoryId)
		throws RemoteException {
		try {
			ShoppingCategoryServiceUtil.deleteCategory(categoryId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws RemoteException {
		try {
			ShoppingCategoryServiceUtil.deleteCategory(category);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel getCategory(
		java.lang.String categoryId) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCategory returnValue = ShoppingCategoryServiceUtil.getCategory(categoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel[] getCategories(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCategoryServiceUtil.getCategories(companyId);

			return (com.liferay.portlet.shopping.model.ShoppingCategory[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel[] getCategories(
		java.lang.String companyId, java.lang.String parentCategoryId)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCategoryServiceUtil.getCategories(companyId,
					parentCategoryId);

			return (com.liferay.portlet.shopping.model.ShoppingCategory[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel[] getCategories(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCategoryServiceUtil.getCategories(category);

			return (com.liferay.portlet.shopping.model.ShoppingCategory[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCategoriesSize(java.lang.String companyId)
		throws RemoteException {
		try {
			int returnValue = ShoppingCategoryServiceUtil.getCategoriesSize(companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCategoriesSize(java.lang.String companyId,
		java.lang.String parentCategoryId) throws RemoteException {
		try {
			int returnValue = ShoppingCategoryServiceUtil.getCategoriesSize(companyId,
					parentCategoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCategoriesSize(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws RemoteException {
		try {
			int returnValue = ShoppingCategoryServiceUtil.getCategoriesSize(category);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel getParentCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCategory returnValue = ShoppingCategoryServiceUtil.getParentCategory(category);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel[] getParentCategories(
		java.lang.String categoryId) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCategoryServiceUtil.getParentCategories(categoryId);

			return (com.liferay.portlet.shopping.model.ShoppingCategory[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel[] getParentCategories(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCategoryServiceUtil.getParentCategories(category);

			return (com.liferay.portlet.shopping.model.ShoppingCategory[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCategory[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategoryModel updateCategory(
		java.lang.String categoryId, java.lang.String parentCategoryId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCategory returnValue = ShoppingCategoryServiceUtil.updateCategory(categoryId,
					parentCategoryId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin() throws RemoteException {
		try {
			boolean returnValue = ShoppingCategoryServiceUtil.hasAdmin();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String categoryId)
		throws RemoteException {
		try {
			boolean returnValue = ShoppingCategoryServiceUtil.hasAdmin(categoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}