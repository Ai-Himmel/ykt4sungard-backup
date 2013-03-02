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

import com.liferay.portlet.shopping.NoSuchItemFieldException;
import com.liferay.portlet.shopping.model.ShoppingItemField;

/**
 * <a href="ShoppingItemFieldPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemFieldPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ShoppingItemFieldPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ShoppingItemField shoppingItemField = _persistence.create(pk);

		assertNotNull(shoppingItemField);

		assertEquals(shoppingItemField.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ShoppingItemField newShoppingItemField = addShoppingItemField();

		_persistence.remove(newShoppingItemField);

		ShoppingItemField existingShoppingItemField = _persistence.fetchByPrimaryKey(newShoppingItemField.getPrimaryKey());

		assertNull(existingShoppingItemField);
	}

	public void testUpdateNew() throws Exception {
		addShoppingItemField();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ShoppingItemField newShoppingItemField = _persistence.create(pk);

		newShoppingItemField.setItemId(nextLong());
		newShoppingItemField.setName(randomString());
		newShoppingItemField.setValues(randomString());
		newShoppingItemField.setDescription(randomString());

		_persistence.update(newShoppingItemField);

		ShoppingItemField existingShoppingItemField = _persistence.findByPrimaryKey(newShoppingItemField.getPrimaryKey());

		assertEquals(existingShoppingItemField.getItemFieldId(),
			newShoppingItemField.getItemFieldId());
		assertEquals(existingShoppingItemField.getItemId(),
			newShoppingItemField.getItemId());
		assertEquals(existingShoppingItemField.getName(),
			newShoppingItemField.getName());
		assertEquals(existingShoppingItemField.getValues(),
			newShoppingItemField.getValues());
		assertEquals(existingShoppingItemField.getDescription(),
			newShoppingItemField.getDescription());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ShoppingItemField newShoppingItemField = addShoppingItemField();

		ShoppingItemField existingShoppingItemField = _persistence.findByPrimaryKey(newShoppingItemField.getPrimaryKey());

		assertEquals(existingShoppingItemField, newShoppingItemField);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchItemFieldException");
		}
		catch (NoSuchItemFieldException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ShoppingItemField newShoppingItemField = addShoppingItemField();

		ShoppingItemField existingShoppingItemField = _persistence.fetchByPrimaryKey(newShoppingItemField.getPrimaryKey());

		assertEquals(existingShoppingItemField, newShoppingItemField);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ShoppingItemField missingShoppingItemField = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingShoppingItemField);
	}

	protected ShoppingItemField addShoppingItemField()
		throws Exception {
		long pk = nextLong();

		ShoppingItemField shoppingItemField = _persistence.create(pk);

		shoppingItemField.setItemId(nextLong());
		shoppingItemField.setName(randomString());
		shoppingItemField.setValues(randomString());
		shoppingItemField.setDescription(randomString());

		_persistence.update(shoppingItemField);

		return shoppingItemField;
	}

	private static final String _TX_IMPL = ShoppingItemFieldPersistence.class.getName() +
		".transaction";
	private ShoppingItemFieldPersistence _persistence;
}