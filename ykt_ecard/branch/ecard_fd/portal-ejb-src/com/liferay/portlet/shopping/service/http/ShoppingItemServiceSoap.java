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

import com.liferay.portlet.shopping.service.spring.ShoppingItemServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingItemServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemServiceSoap {
	public static void addBookItems(java.lang.String categoryId,
		java.lang.String[] isbnArray) throws RemoteException {
		try {
			ShoppingItemServiceUtil.addBookItems(categoryId, isbnArray);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteItem(java.lang.String itemId)
		throws RemoteException {
		try {
			ShoppingItemServiceUtil.deleteItem(itemId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteItem(
		com.liferay.portlet.shopping.model.ShoppingItem item)
		throws RemoteException {
		try {
			ShoppingItemServiceUtil.deleteItem(item);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel[] getFeaturedItems(
		java.lang.String companyId, java.lang.String categoryId, int numOfItems)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingItemServiceUtil.getFeaturedItems(companyId,
					categoryId, numOfItems);

			return (com.liferay.portlet.shopping.model.ShoppingItem[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingItem[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel getItemById(
		java.lang.String itemId) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingItem returnValue = ShoppingItemServiceUtil.getItemById(itemId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel getItemBySKU(
		java.lang.String companyId, java.lang.String sku)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingItem returnValue = ShoppingItemServiceUtil.getItemBySKU(companyId,
					sku);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel[] getItems(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingItemServiceUtil.getItems(companyId);

			return (com.liferay.portlet.shopping.model.ShoppingItem[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingItem[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel[] getItems(
		java.lang.String companyId, java.lang.String categoryId)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingItemServiceUtil.getItems(companyId,
					categoryId);

			return (com.liferay.portlet.shopping.model.ShoppingItem[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingItem[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getItemsSize(java.lang.String companyId)
		throws RemoteException {
		try {
			int returnValue = ShoppingItemServiceUtil.getItemsSize(companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getItemsSize(java.lang.String companyId,
		java.lang.String categoryId) throws RemoteException {
		try {
			int returnValue = ShoppingItemServiceUtil.getItemsSize(companyId,
					categoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel[] getSaleItems(
		java.lang.String companyId, java.lang.String categoryId, int numOfItems)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingItemServiceUtil.getSaleItems(companyId,
					categoryId, numOfItems);

			return (com.liferay.portlet.shopping.model.ShoppingItem[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingItem[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemModel[] search(
		java.lang.String companyId, java.lang.String[] categoryIds,
		java.lang.String keywords, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingItemServiceUtil.search(companyId,
					categoryIds, keywords, begin, end);

			return (com.liferay.portlet.shopping.model.ShoppingItem[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingItem[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int searchSize(java.lang.String companyId,
		java.lang.String[] categoryIds, java.lang.String keywords)
		throws RemoteException {
		try {
			int returnValue = ShoppingItemServiceUtil.searchSize(companyId,
					categoryIds, keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String itemId)
		throws RemoteException {
		try {
			boolean returnValue = ShoppingItemServiceUtil.hasAdmin(itemId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}