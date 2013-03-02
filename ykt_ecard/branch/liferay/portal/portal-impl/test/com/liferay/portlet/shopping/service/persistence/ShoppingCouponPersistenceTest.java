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

import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.model.ShoppingCoupon;

/**
 * <a href="ShoppingCouponPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCouponPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ShoppingCouponPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ShoppingCoupon shoppingCoupon = _persistence.create(pk);

		assertNotNull(shoppingCoupon);

		assertEquals(shoppingCoupon.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ShoppingCoupon newShoppingCoupon = addShoppingCoupon();

		_persistence.remove(newShoppingCoupon);

		ShoppingCoupon existingShoppingCoupon = _persistence.fetchByPrimaryKey(newShoppingCoupon.getPrimaryKey());

		assertNull(existingShoppingCoupon);
	}

	public void testUpdateNew() throws Exception {
		addShoppingCoupon();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ShoppingCoupon newShoppingCoupon = _persistence.create(pk);

		newShoppingCoupon.setGroupId(nextLong());
		newShoppingCoupon.setCompanyId(nextLong());
		newShoppingCoupon.setUserId(nextLong());
		newShoppingCoupon.setUserName(randomString());
		newShoppingCoupon.setCreateDate(nextDate());
		newShoppingCoupon.setModifiedDate(nextDate());
		newShoppingCoupon.setCode(randomString());
		newShoppingCoupon.setName(randomString());
		newShoppingCoupon.setDescription(randomString());
		newShoppingCoupon.setStartDate(nextDate());
		newShoppingCoupon.setEndDate(nextDate());
		newShoppingCoupon.setActive(randomBoolean());
		newShoppingCoupon.setLimitCategories(randomString());
		newShoppingCoupon.setLimitSkus(randomString());
		newShoppingCoupon.setMinOrder(nextDouble());
		newShoppingCoupon.setDiscount(nextDouble());
		newShoppingCoupon.setDiscountType(randomString());

		_persistence.update(newShoppingCoupon);

		ShoppingCoupon existingShoppingCoupon = _persistence.findByPrimaryKey(newShoppingCoupon.getPrimaryKey());

		assertEquals(existingShoppingCoupon.getCouponId(),
			newShoppingCoupon.getCouponId());
		assertEquals(existingShoppingCoupon.getGroupId(),
			newShoppingCoupon.getGroupId());
		assertEquals(existingShoppingCoupon.getCompanyId(),
			newShoppingCoupon.getCompanyId());
		assertEquals(existingShoppingCoupon.getUserId(),
			newShoppingCoupon.getUserId());
		assertEquals(existingShoppingCoupon.getUserName(),
			newShoppingCoupon.getUserName());
		assertEquals(existingShoppingCoupon.getCreateDate(),
			newShoppingCoupon.getCreateDate());
		assertEquals(existingShoppingCoupon.getModifiedDate(),
			newShoppingCoupon.getModifiedDate());
		assertEquals(existingShoppingCoupon.getCode(),
			newShoppingCoupon.getCode());
		assertEquals(existingShoppingCoupon.getName(),
			newShoppingCoupon.getName());
		assertEquals(existingShoppingCoupon.getDescription(),
			newShoppingCoupon.getDescription());
		assertEquals(existingShoppingCoupon.getStartDate(),
			newShoppingCoupon.getStartDate());
		assertEquals(existingShoppingCoupon.getEndDate(),
			newShoppingCoupon.getEndDate());
		assertEquals(existingShoppingCoupon.getActive(),
			newShoppingCoupon.getActive());
		assertEquals(existingShoppingCoupon.getLimitCategories(),
			newShoppingCoupon.getLimitCategories());
		assertEquals(existingShoppingCoupon.getLimitSkus(),
			newShoppingCoupon.getLimitSkus());
		assertEquals(existingShoppingCoupon.getMinOrder(),
			newShoppingCoupon.getMinOrder());
		assertEquals(existingShoppingCoupon.getDiscount(),
			newShoppingCoupon.getDiscount());
		assertEquals(existingShoppingCoupon.getDiscountType(),
			newShoppingCoupon.getDiscountType());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ShoppingCoupon newShoppingCoupon = addShoppingCoupon();

		ShoppingCoupon existingShoppingCoupon = _persistence.findByPrimaryKey(newShoppingCoupon.getPrimaryKey());

		assertEquals(existingShoppingCoupon, newShoppingCoupon);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchCouponException");
		}
		catch (NoSuchCouponException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ShoppingCoupon newShoppingCoupon = addShoppingCoupon();

		ShoppingCoupon existingShoppingCoupon = _persistence.fetchByPrimaryKey(newShoppingCoupon.getPrimaryKey());

		assertEquals(existingShoppingCoupon, newShoppingCoupon);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ShoppingCoupon missingShoppingCoupon = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingShoppingCoupon);
	}

	protected ShoppingCoupon addShoppingCoupon() throws Exception {
		long pk = nextLong();

		ShoppingCoupon shoppingCoupon = _persistence.create(pk);

		shoppingCoupon.setGroupId(nextLong());
		shoppingCoupon.setCompanyId(nextLong());
		shoppingCoupon.setUserId(nextLong());
		shoppingCoupon.setUserName(randomString());
		shoppingCoupon.setCreateDate(nextDate());
		shoppingCoupon.setModifiedDate(nextDate());
		shoppingCoupon.setCode(randomString());
		shoppingCoupon.setName(randomString());
		shoppingCoupon.setDescription(randomString());
		shoppingCoupon.setStartDate(nextDate());
		shoppingCoupon.setEndDate(nextDate());
		shoppingCoupon.setActive(randomBoolean());
		shoppingCoupon.setLimitCategories(randomString());
		shoppingCoupon.setLimitSkus(randomString());
		shoppingCoupon.setMinOrder(nextDouble());
		shoppingCoupon.setDiscount(nextDouble());
		shoppingCoupon.setDiscountType(randomString());

		_persistence.update(shoppingCoupon);

		return shoppingCoupon;
	}

	private static final String _TX_IMPL = ShoppingCouponPersistence.class.getName() +
		".transaction";
	private ShoppingCouponPersistence _persistence;
}