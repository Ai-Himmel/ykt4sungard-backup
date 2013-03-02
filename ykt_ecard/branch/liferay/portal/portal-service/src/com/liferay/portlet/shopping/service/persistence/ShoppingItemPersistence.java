/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

/**
 * <a href="ShoppingItemPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface ShoppingItemPersistence {
	public com.liferay.portlet.shopping.model.ShoppingItem create(long itemId);

	public com.liferay.portlet.shopping.model.ShoppingItem remove(long itemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem remove(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem update(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem update(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem updateImpl(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findByPrimaryKey(
		long itemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem fetchByPrimaryKey(
		long itemId) throws com.liferay.portal.SystemException;

	public java.util.List findByCategoryId(long categoryId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCategoryId(long categoryId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCategoryId(long categoryId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findByCategoryId_First(
		long categoryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findByCategoryId_Last(
		long categoryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem[] findByCategoryId_PrevAndNext(
		long itemId, long categoryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem fetchBySmallImageId(
		long smallImageId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findByMediumImageId(
		long mediumImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem fetchByMediumImageId(
		long mediumImageId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findByLargeImageId(
		long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem fetchByLargeImageId(
		long largeImageId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem findByC_S(
		long companyId, java.lang.String sku)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public com.liferay.portlet.shopping.model.ShoppingItem fetchByC_S(
		long companyId, java.lang.String sku)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByCategoryId(long categoryId)
		throws com.liferay.portal.SystemException;

	public void removeBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public void removeByMediumImageId(long mediumImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public void removeByLargeImageId(long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public void removeByC_S(long companyId, java.lang.String sku)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByCategoryId(long categoryId)
		throws com.liferay.portal.SystemException;

	public int countBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException;

	public int countByMediumImageId(long mediumImageId)
		throws com.liferay.portal.SystemException;

	public int countByLargeImageId(long largeImageId)
		throws com.liferay.portal.SystemException;

	public int countByC_S(long companyId, java.lang.String sku)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;

	public java.util.List getShoppingItemPrices(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public java.util.List getShoppingItemPrices(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public java.util.List getShoppingItemPrices(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemException;

	public int getShoppingItemPricesSize(long pk)
		throws com.liferay.portal.SystemException;

	public boolean containsShoppingItemPrice(long pk, long shoppingItemPricePK)
		throws com.liferay.portal.SystemException;

	public boolean containsShoppingItemPrices(long pk)
		throws com.liferay.portal.SystemException;
}