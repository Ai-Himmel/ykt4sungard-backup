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

import com.liferay.portlet.shopping.NoSuchCartException;
import com.liferay.portlet.shopping.model.ShoppingCart;

/**
 * <a href="ShoppingCartPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCartPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ShoppingCartPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ShoppingCart shoppingCart = _persistence.create(pk);

		assertNotNull(shoppingCart);

		assertEquals(shoppingCart.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ShoppingCart newShoppingCart = addShoppingCart();

		_persistence.remove(newShoppingCart);

		ShoppingCart existingShoppingCart = _persistence.fetchByPrimaryKey(newShoppingCart.getPrimaryKey());

		assertNull(existingShoppingCart);
	}

	public void testUpdateNew() throws Exception {
		addShoppingCart();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ShoppingCart newShoppingCart = _persistence.create(pk);

		newShoppingCart.setGroupId(nextLong());
		newShoppingCart.setCompanyId(nextLong());
		newShoppingCart.setUserId(nextLong());
		newShoppingCart.setUserName(randomString());
		newShoppingCart.setCreateDate(nextDate());
		newShoppingCart.setModifiedDate(nextDate());
		newShoppingCart.setItemIds(randomString());
		newShoppingCart.setCouponCodes(randomString());
		newShoppingCart.setAltShipping(nextInt());
		newShoppingCart.setInsure(randomBoolean());

		_persistence.update(newShoppingCart);

		ShoppingCart existingShoppingCart = _persistence.findByPrimaryKey(newShoppingCart.getPrimaryKey());

		assertEquals(existingShoppingCart.getCartId(),
			newShoppingCart.getCartId());
		assertEquals(existingShoppingCart.getGroupId(),
			newShoppingCart.getGroupId());
		assertEquals(existingShoppingCart.getCompanyId(),
			newShoppingCart.getCompanyId());
		assertEquals(existingShoppingCart.getUserId(),
			newShoppingCart.getUserId());
		assertEquals(existingShoppingCart.getUserName(),
			newShoppingCart.getUserName());
		assertEquals(existingShoppingCart.getCreateDate(),
			newShoppingCart.getCreateDate());
		assertEquals(existingShoppingCart.getModifiedDate(),
			newShoppingCart.getModifiedDate());
		assertEquals(existingShoppingCart.getItemIds(),
			newShoppingCart.getItemIds());
		assertEquals(existingShoppingCart.getCouponCodes(),
			newShoppingCart.getCouponCodes());
		assertEquals(existingShoppingCart.getAltShipping(),
			newShoppingCart.getAltShipping());
		assertEquals(existingShoppingCart.getInsure(),
			newShoppingCart.getInsure());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ShoppingCart newShoppingCart = addShoppingCart();

		ShoppingCart existingShoppingCart = _persistence.findByPrimaryKey(newShoppingCart.getPrimaryKey());

		assertEquals(existingShoppingCart, newShoppingCart);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchCartException");
		}
		catch (NoSuchCartException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ShoppingCart newShoppingCart = addShoppingCart();

		ShoppingCart existingShoppingCart = _persistence.fetchByPrimaryKey(newShoppingCart.getPrimaryKey());

		assertEquals(existingShoppingCart, newShoppingCart);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ShoppingCart missingShoppingCart = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingShoppingCart);
	}

	protected ShoppingCart addShoppingCart() throws Exception {
		long pk = nextLong();

		ShoppingCart shoppingCart = _persistence.create(pk);

		shoppingCart.setGroupId(nextLong());
		shoppingCart.setCompanyId(nextLong());
		shoppingCart.setUserId(nextLong());
		shoppingCart.setUserName(randomString());
		shoppingCart.setCreateDate(nextDate());
		shoppingCart.setModifiedDate(nextDate());
		shoppingCart.setItemIds(randomString());
		shoppingCart.setCouponCodes(randomString());
		shoppingCart.setAltShipping(nextInt());
		shoppingCart.setInsure(randomBoolean());

		_persistence.update(shoppingCart);

		return shoppingCart;
	}

	private static final String _TX_IMPL = ShoppingCartPersistence.class.getName() +
		".transaction";
	private ShoppingCartPersistence _persistence;
}