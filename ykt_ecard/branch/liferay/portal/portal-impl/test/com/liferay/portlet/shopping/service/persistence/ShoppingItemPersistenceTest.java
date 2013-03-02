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

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingItem;

/**
 * <a href="ShoppingItemPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ShoppingItemPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ShoppingItem shoppingItem = _persistence.create(pk);

		assertNotNull(shoppingItem);

		assertEquals(shoppingItem.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ShoppingItem newShoppingItem = addShoppingItem();

		_persistence.remove(newShoppingItem);

		ShoppingItem existingShoppingItem = _persistence.fetchByPrimaryKey(newShoppingItem.getPrimaryKey());

		assertNull(existingShoppingItem);
	}

	public void testUpdateNew() throws Exception {
		addShoppingItem();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ShoppingItem newShoppingItem = _persistence.create(pk);

		newShoppingItem.setCompanyId(nextLong());
		newShoppingItem.setUserId(nextLong());
		newShoppingItem.setUserName(randomString());
		newShoppingItem.setCreateDate(nextDate());
		newShoppingItem.setModifiedDate(nextDate());
		newShoppingItem.setCategoryId(nextLong());
		newShoppingItem.setSku(randomString());
		newShoppingItem.setName(randomString());
		newShoppingItem.setDescription(randomString());
		newShoppingItem.setProperties(randomString());
		newShoppingItem.setFields(randomBoolean());
		newShoppingItem.setFieldsQuantities(randomString());
		newShoppingItem.setMinQuantity(nextInt());
		newShoppingItem.setMaxQuantity(nextInt());
		newShoppingItem.setPrice(nextDouble());
		newShoppingItem.setDiscount(nextDouble());
		newShoppingItem.setTaxable(randomBoolean());
		newShoppingItem.setShipping(nextDouble());
		newShoppingItem.setUseShippingFormula(randomBoolean());
		newShoppingItem.setRequiresShipping(randomBoolean());
		newShoppingItem.setStockQuantity(nextInt());
		newShoppingItem.setFeatured(randomBoolean());
		newShoppingItem.setSale(randomBoolean());
		newShoppingItem.setSmallImage(randomBoolean());
		newShoppingItem.setSmallImageId(nextLong());
		newShoppingItem.setSmallImageURL(randomString());
		newShoppingItem.setMediumImage(randomBoolean());
		newShoppingItem.setMediumImageId(nextLong());
		newShoppingItem.setMediumImageURL(randomString());
		newShoppingItem.setLargeImage(randomBoolean());
		newShoppingItem.setLargeImageId(nextLong());
		newShoppingItem.setLargeImageURL(randomString());

		_persistence.update(newShoppingItem);

		ShoppingItem existingShoppingItem = _persistence.findByPrimaryKey(newShoppingItem.getPrimaryKey());

		assertEquals(existingShoppingItem.getItemId(),
			newShoppingItem.getItemId());
		assertEquals(existingShoppingItem.getCompanyId(),
			newShoppingItem.getCompanyId());
		assertEquals(existingShoppingItem.getUserId(),
			newShoppingItem.getUserId());
		assertEquals(existingShoppingItem.getUserName(),
			newShoppingItem.getUserName());
		assertEquals(existingShoppingItem.getCreateDate(),
			newShoppingItem.getCreateDate());
		assertEquals(existingShoppingItem.getModifiedDate(),
			newShoppingItem.getModifiedDate());
		assertEquals(existingShoppingItem.getCategoryId(),
			newShoppingItem.getCategoryId());
		assertEquals(existingShoppingItem.getSku(), newShoppingItem.getSku());
		assertEquals(existingShoppingItem.getName(), newShoppingItem.getName());
		assertEquals(existingShoppingItem.getDescription(),
			newShoppingItem.getDescription());
		assertEquals(existingShoppingItem.getProperties(),
			newShoppingItem.getProperties());
		assertEquals(existingShoppingItem.getFields(),
			newShoppingItem.getFields());
		assertEquals(existingShoppingItem.getFieldsQuantities(),
			newShoppingItem.getFieldsQuantities());
		assertEquals(existingShoppingItem.getMinQuantity(),
			newShoppingItem.getMinQuantity());
		assertEquals(existingShoppingItem.getMaxQuantity(),
			newShoppingItem.getMaxQuantity());
		assertEquals(existingShoppingItem.getPrice(), newShoppingItem.getPrice());
		assertEquals(existingShoppingItem.getDiscount(),
			newShoppingItem.getDiscount());
		assertEquals(existingShoppingItem.getTaxable(),
			newShoppingItem.getTaxable());
		assertEquals(existingShoppingItem.getShipping(),
			newShoppingItem.getShipping());
		assertEquals(existingShoppingItem.getUseShippingFormula(),
			newShoppingItem.getUseShippingFormula());
		assertEquals(existingShoppingItem.getRequiresShipping(),
			newShoppingItem.getRequiresShipping());
		assertEquals(existingShoppingItem.getStockQuantity(),
			newShoppingItem.getStockQuantity());
		assertEquals(existingShoppingItem.getFeatured(),
			newShoppingItem.getFeatured());
		assertEquals(existingShoppingItem.getSale(), newShoppingItem.getSale());
		assertEquals(existingShoppingItem.getSmallImage(),
			newShoppingItem.getSmallImage());
		assertEquals(existingShoppingItem.getSmallImageId(),
			newShoppingItem.getSmallImageId());
		assertEquals(existingShoppingItem.getSmallImageURL(),
			newShoppingItem.getSmallImageURL());
		assertEquals(existingShoppingItem.getMediumImage(),
			newShoppingItem.getMediumImage());
		assertEquals(existingShoppingItem.getMediumImageId(),
			newShoppingItem.getMediumImageId());
		assertEquals(existingShoppingItem.getMediumImageURL(),
			newShoppingItem.getMediumImageURL());
		assertEquals(existingShoppingItem.getLargeImage(),
			newShoppingItem.getLargeImage());
		assertEquals(existingShoppingItem.getLargeImageId(),
			newShoppingItem.getLargeImageId());
		assertEquals(existingShoppingItem.getLargeImageURL(),
			newShoppingItem.getLargeImageURL());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ShoppingItem newShoppingItem = addShoppingItem();

		ShoppingItem existingShoppingItem = _persistence.findByPrimaryKey(newShoppingItem.getPrimaryKey());

		assertEquals(existingShoppingItem, newShoppingItem);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchItemException");
		}
		catch (NoSuchItemException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ShoppingItem newShoppingItem = addShoppingItem();

		ShoppingItem existingShoppingItem = _persistence.fetchByPrimaryKey(newShoppingItem.getPrimaryKey());

		assertEquals(existingShoppingItem, newShoppingItem);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ShoppingItem missingShoppingItem = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingShoppingItem);
	}

	protected ShoppingItem addShoppingItem() throws Exception {
		long pk = nextLong();

		ShoppingItem shoppingItem = _persistence.create(pk);

		shoppingItem.setCompanyId(nextLong());
		shoppingItem.setUserId(nextLong());
		shoppingItem.setUserName(randomString());
		shoppingItem.setCreateDate(nextDate());
		shoppingItem.setModifiedDate(nextDate());
		shoppingItem.setCategoryId(nextLong());
		shoppingItem.setSku(randomString());
		shoppingItem.setName(randomString());
		shoppingItem.setDescription(randomString());
		shoppingItem.setProperties(randomString());
		shoppingItem.setFields(randomBoolean());
		shoppingItem.setFieldsQuantities(randomString());
		shoppingItem.setMinQuantity(nextInt());
		shoppingItem.setMaxQuantity(nextInt());
		shoppingItem.setPrice(nextDouble());
		shoppingItem.setDiscount(nextDouble());
		shoppingItem.setTaxable(randomBoolean());
		shoppingItem.setShipping(nextDouble());
		shoppingItem.setUseShippingFormula(randomBoolean());
		shoppingItem.setRequiresShipping(randomBoolean());
		shoppingItem.setStockQuantity(nextInt());
		shoppingItem.setFeatured(randomBoolean());
		shoppingItem.setSale(randomBoolean());
		shoppingItem.setSmallImage(randomBoolean());
		shoppingItem.setSmallImageId(nextLong());
		shoppingItem.setSmallImageURL(randomString());
		shoppingItem.setMediumImage(randomBoolean());
		shoppingItem.setMediumImageId(nextLong());
		shoppingItem.setMediumImageURL(randomString());
		shoppingItem.setLargeImage(randomBoolean());
		shoppingItem.setLargeImageId(nextLong());
		shoppingItem.setLargeImageURL(randomString());

		_persistence.update(shoppingItem);

		return shoppingItem;
	}

	private static final String _TX_IMPL = ShoppingItemPersistence.class.getName() +
		".transaction";
	private ShoppingItemPersistence _persistence;
}