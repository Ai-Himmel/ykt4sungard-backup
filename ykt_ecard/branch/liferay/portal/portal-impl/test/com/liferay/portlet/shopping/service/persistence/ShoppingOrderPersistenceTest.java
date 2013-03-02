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

import com.liferay.portlet.shopping.NoSuchOrderException;
import com.liferay.portlet.shopping.model.ShoppingOrder;

/**
 * <a href="ShoppingOrderPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingOrderPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ShoppingOrderPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ShoppingOrder shoppingOrder = _persistence.create(pk);

		assertNotNull(shoppingOrder);

		assertEquals(shoppingOrder.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ShoppingOrder newShoppingOrder = addShoppingOrder();

		_persistence.remove(newShoppingOrder);

		ShoppingOrder existingShoppingOrder = _persistence.fetchByPrimaryKey(newShoppingOrder.getPrimaryKey());

		assertNull(existingShoppingOrder);
	}

	public void testUpdateNew() throws Exception {
		addShoppingOrder();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ShoppingOrder newShoppingOrder = _persistence.create(pk);

		newShoppingOrder.setGroupId(nextLong());
		newShoppingOrder.setCompanyId(nextLong());
		newShoppingOrder.setUserId(nextLong());
		newShoppingOrder.setUserName(randomString());
		newShoppingOrder.setCreateDate(nextDate());
		newShoppingOrder.setModifiedDate(nextDate());
		newShoppingOrder.setNumber(randomString());
		newShoppingOrder.setTax(nextDouble());
		newShoppingOrder.setShipping(nextDouble());
		newShoppingOrder.setAltShipping(randomString());
		newShoppingOrder.setRequiresShipping(randomBoolean());
		newShoppingOrder.setInsure(randomBoolean());
		newShoppingOrder.setInsurance(nextDouble());
		newShoppingOrder.setCouponCodes(randomString());
		newShoppingOrder.setCouponDiscount(nextDouble());
		newShoppingOrder.setBillingFirstName(randomString());
		newShoppingOrder.setBillingLastName(randomString());
		newShoppingOrder.setBillingEmailAddress(randomString());
		newShoppingOrder.setBillingCompany(randomString());
		newShoppingOrder.setBillingStreet(randomString());
		newShoppingOrder.setBillingCity(randomString());
		newShoppingOrder.setBillingState(randomString());
		newShoppingOrder.setBillingZip(randomString());
		newShoppingOrder.setBillingCountry(randomString());
		newShoppingOrder.setBillingPhone(randomString());
		newShoppingOrder.setShipToBilling(randomBoolean());
		newShoppingOrder.setShippingFirstName(randomString());
		newShoppingOrder.setShippingLastName(randomString());
		newShoppingOrder.setShippingEmailAddress(randomString());
		newShoppingOrder.setShippingCompany(randomString());
		newShoppingOrder.setShippingStreet(randomString());
		newShoppingOrder.setShippingCity(randomString());
		newShoppingOrder.setShippingState(randomString());
		newShoppingOrder.setShippingZip(randomString());
		newShoppingOrder.setShippingCountry(randomString());
		newShoppingOrder.setShippingPhone(randomString());
		newShoppingOrder.setCcName(randomString());
		newShoppingOrder.setCcType(randomString());
		newShoppingOrder.setCcNumber(randomString());
		newShoppingOrder.setCcExpMonth(nextInt());
		newShoppingOrder.setCcExpYear(nextInt());
		newShoppingOrder.setCcVerNumber(randomString());
		newShoppingOrder.setComments(randomString());
		newShoppingOrder.setPpTxnId(randomString());
		newShoppingOrder.setPpPaymentStatus(randomString());
		newShoppingOrder.setPpPaymentGross(nextDouble());
		newShoppingOrder.setPpReceiverEmail(randomString());
		newShoppingOrder.setPpPayerEmail(randomString());
		newShoppingOrder.setSendOrderEmail(randomBoolean());
		newShoppingOrder.setSendShippingEmail(randomBoolean());

		_persistence.update(newShoppingOrder);

		ShoppingOrder existingShoppingOrder = _persistence.findByPrimaryKey(newShoppingOrder.getPrimaryKey());

		assertEquals(existingShoppingOrder.getOrderId(),
			newShoppingOrder.getOrderId());
		assertEquals(existingShoppingOrder.getGroupId(),
			newShoppingOrder.getGroupId());
		assertEquals(existingShoppingOrder.getCompanyId(),
			newShoppingOrder.getCompanyId());
		assertEquals(existingShoppingOrder.getUserId(),
			newShoppingOrder.getUserId());
		assertEquals(existingShoppingOrder.getUserName(),
			newShoppingOrder.getUserName());
		assertEquals(existingShoppingOrder.getCreateDate(),
			newShoppingOrder.getCreateDate());
		assertEquals(existingShoppingOrder.getModifiedDate(),
			newShoppingOrder.getModifiedDate());
		assertEquals(existingShoppingOrder.getNumber(),
			newShoppingOrder.getNumber());
		assertEquals(existingShoppingOrder.getTax(), newShoppingOrder.getTax());
		assertEquals(existingShoppingOrder.getShipping(),
			newShoppingOrder.getShipping());
		assertEquals(existingShoppingOrder.getAltShipping(),
			newShoppingOrder.getAltShipping());
		assertEquals(existingShoppingOrder.getRequiresShipping(),
			newShoppingOrder.getRequiresShipping());
		assertEquals(existingShoppingOrder.getInsure(),
			newShoppingOrder.getInsure());
		assertEquals(existingShoppingOrder.getInsurance(),
			newShoppingOrder.getInsurance());
		assertEquals(existingShoppingOrder.getCouponCodes(),
			newShoppingOrder.getCouponCodes());
		assertEquals(existingShoppingOrder.getCouponDiscount(),
			newShoppingOrder.getCouponDiscount());
		assertEquals(existingShoppingOrder.getBillingFirstName(),
			newShoppingOrder.getBillingFirstName());
		assertEquals(existingShoppingOrder.getBillingLastName(),
			newShoppingOrder.getBillingLastName());
		assertEquals(existingShoppingOrder.getBillingEmailAddress(),
			newShoppingOrder.getBillingEmailAddress());
		assertEquals(existingShoppingOrder.getBillingCompany(),
			newShoppingOrder.getBillingCompany());
		assertEquals(existingShoppingOrder.getBillingStreet(),
			newShoppingOrder.getBillingStreet());
		assertEquals(existingShoppingOrder.getBillingCity(),
			newShoppingOrder.getBillingCity());
		assertEquals(existingShoppingOrder.getBillingState(),
			newShoppingOrder.getBillingState());
		assertEquals(existingShoppingOrder.getBillingZip(),
			newShoppingOrder.getBillingZip());
		assertEquals(existingShoppingOrder.getBillingCountry(),
			newShoppingOrder.getBillingCountry());
		assertEquals(existingShoppingOrder.getBillingPhone(),
			newShoppingOrder.getBillingPhone());
		assertEquals(existingShoppingOrder.getShipToBilling(),
			newShoppingOrder.getShipToBilling());
		assertEquals(existingShoppingOrder.getShippingFirstName(),
			newShoppingOrder.getShippingFirstName());
		assertEquals(existingShoppingOrder.getShippingLastName(),
			newShoppingOrder.getShippingLastName());
		assertEquals(existingShoppingOrder.getShippingEmailAddress(),
			newShoppingOrder.getShippingEmailAddress());
		assertEquals(existingShoppingOrder.getShippingCompany(),
			newShoppingOrder.getShippingCompany());
		assertEquals(existingShoppingOrder.getShippingStreet(),
			newShoppingOrder.getShippingStreet());
		assertEquals(existingShoppingOrder.getShippingCity(),
			newShoppingOrder.getShippingCity());
		assertEquals(existingShoppingOrder.getShippingState(),
			newShoppingOrder.getShippingState());
		assertEquals(existingShoppingOrder.getShippingZip(),
			newShoppingOrder.getShippingZip());
		assertEquals(existingShoppingOrder.getShippingCountry(),
			newShoppingOrder.getShippingCountry());
		assertEquals(existingShoppingOrder.getShippingPhone(),
			newShoppingOrder.getShippingPhone());
		assertEquals(existingShoppingOrder.getCcName(),
			newShoppingOrder.getCcName());
		assertEquals(existingShoppingOrder.getCcType(),
			newShoppingOrder.getCcType());
		assertEquals(existingShoppingOrder.getCcNumber(),
			newShoppingOrder.getCcNumber());
		assertEquals(existingShoppingOrder.getCcExpMonth(),
			newShoppingOrder.getCcExpMonth());
		assertEquals(existingShoppingOrder.getCcExpYear(),
			newShoppingOrder.getCcExpYear());
		assertEquals(existingShoppingOrder.getCcVerNumber(),
			newShoppingOrder.getCcVerNumber());
		assertEquals(existingShoppingOrder.getComments(),
			newShoppingOrder.getComments());
		assertEquals(existingShoppingOrder.getPpTxnId(),
			newShoppingOrder.getPpTxnId());
		assertEquals(existingShoppingOrder.getPpPaymentStatus(),
			newShoppingOrder.getPpPaymentStatus());
		assertEquals(existingShoppingOrder.getPpPaymentGross(),
			newShoppingOrder.getPpPaymentGross());
		assertEquals(existingShoppingOrder.getPpReceiverEmail(),
			newShoppingOrder.getPpReceiverEmail());
		assertEquals(existingShoppingOrder.getPpPayerEmail(),
			newShoppingOrder.getPpPayerEmail());
		assertEquals(existingShoppingOrder.getSendOrderEmail(),
			newShoppingOrder.getSendOrderEmail());
		assertEquals(existingShoppingOrder.getSendShippingEmail(),
			newShoppingOrder.getSendShippingEmail());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ShoppingOrder newShoppingOrder = addShoppingOrder();

		ShoppingOrder existingShoppingOrder = _persistence.findByPrimaryKey(newShoppingOrder.getPrimaryKey());

		assertEquals(existingShoppingOrder, newShoppingOrder);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchOrderException");
		}
		catch (NoSuchOrderException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ShoppingOrder newShoppingOrder = addShoppingOrder();

		ShoppingOrder existingShoppingOrder = _persistence.fetchByPrimaryKey(newShoppingOrder.getPrimaryKey());

		assertEquals(existingShoppingOrder, newShoppingOrder);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ShoppingOrder missingShoppingOrder = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingShoppingOrder);
	}

	protected ShoppingOrder addShoppingOrder() throws Exception {
		long pk = nextLong();

		ShoppingOrder shoppingOrder = _persistence.create(pk);

		shoppingOrder.setGroupId(nextLong());
		shoppingOrder.setCompanyId(nextLong());
		shoppingOrder.setUserId(nextLong());
		shoppingOrder.setUserName(randomString());
		shoppingOrder.setCreateDate(nextDate());
		shoppingOrder.setModifiedDate(nextDate());
		shoppingOrder.setNumber(randomString());
		shoppingOrder.setTax(nextDouble());
		shoppingOrder.setShipping(nextDouble());
		shoppingOrder.setAltShipping(randomString());
		shoppingOrder.setRequiresShipping(randomBoolean());
		shoppingOrder.setInsure(randomBoolean());
		shoppingOrder.setInsurance(nextDouble());
		shoppingOrder.setCouponCodes(randomString());
		shoppingOrder.setCouponDiscount(nextDouble());
		shoppingOrder.setBillingFirstName(randomString());
		shoppingOrder.setBillingLastName(randomString());
		shoppingOrder.setBillingEmailAddress(randomString());
		shoppingOrder.setBillingCompany(randomString());
		shoppingOrder.setBillingStreet(randomString());
		shoppingOrder.setBillingCity(randomString());
		shoppingOrder.setBillingState(randomString());
		shoppingOrder.setBillingZip(randomString());
		shoppingOrder.setBillingCountry(randomString());
		shoppingOrder.setBillingPhone(randomString());
		shoppingOrder.setShipToBilling(randomBoolean());
		shoppingOrder.setShippingFirstName(randomString());
		shoppingOrder.setShippingLastName(randomString());
		shoppingOrder.setShippingEmailAddress(randomString());
		shoppingOrder.setShippingCompany(randomString());
		shoppingOrder.setShippingStreet(randomString());
		shoppingOrder.setShippingCity(randomString());
		shoppingOrder.setShippingState(randomString());
		shoppingOrder.setShippingZip(randomString());
		shoppingOrder.setShippingCountry(randomString());
		shoppingOrder.setShippingPhone(randomString());
		shoppingOrder.setCcName(randomString());
		shoppingOrder.setCcType(randomString());
		shoppingOrder.setCcNumber(randomString());
		shoppingOrder.setCcExpMonth(nextInt());
		shoppingOrder.setCcExpYear(nextInt());
		shoppingOrder.setCcVerNumber(randomString());
		shoppingOrder.setComments(randomString());
		shoppingOrder.setPpTxnId(randomString());
		shoppingOrder.setPpPaymentStatus(randomString());
		shoppingOrder.setPpPaymentGross(nextDouble());
		shoppingOrder.setPpReceiverEmail(randomString());
		shoppingOrder.setPpPayerEmail(randomString());
		shoppingOrder.setSendOrderEmail(randomBoolean());
		shoppingOrder.setSendShippingEmail(randomBoolean());

		_persistence.update(shoppingOrder);

		return shoppingOrder;
	}

	private static final String _TX_IMPL = ShoppingOrderPersistence.class.getName() +
		".transaction";
	private ShoppingOrderPersistence _persistence;
}