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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchSubscriptionException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Subscription;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="SubscriptionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SubscriptionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (SubscriptionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Subscription subscription = _persistence.create(pk);

		assertNotNull(subscription);

		assertEquals(subscription.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Subscription newSubscription = addSubscription();

		_persistence.remove(newSubscription);

		Subscription existingSubscription = _persistence.fetchByPrimaryKey(newSubscription.getPrimaryKey());

		assertNull(existingSubscription);
	}

	public void testUpdateNew() throws Exception {
		addSubscription();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Subscription newSubscription = _persistence.create(pk);

		newSubscription.setCompanyId(nextLong());
		newSubscription.setUserId(nextLong());
		newSubscription.setUserName(randomString());
		newSubscription.setCreateDate(nextDate());
		newSubscription.setModifiedDate(nextDate());
		newSubscription.setClassNameId(nextLong());
		newSubscription.setClassPK(nextLong());
		newSubscription.setFrequency(randomString());

		_persistence.update(newSubscription);

		Subscription existingSubscription = _persistence.findByPrimaryKey(newSubscription.getPrimaryKey());

		assertEquals(existingSubscription.getSubscriptionId(),
			newSubscription.getSubscriptionId());
		assertEquals(existingSubscription.getCompanyId(),
			newSubscription.getCompanyId());
		assertEquals(existingSubscription.getUserId(),
			newSubscription.getUserId());
		assertEquals(existingSubscription.getUserName(),
			newSubscription.getUserName());
		assertEquals(existingSubscription.getCreateDate(),
			newSubscription.getCreateDate());
		assertEquals(existingSubscription.getModifiedDate(),
			newSubscription.getModifiedDate());
		assertEquals(existingSubscription.getClassNameId(),
			newSubscription.getClassNameId());
		assertEquals(existingSubscription.getClassPK(),
			newSubscription.getClassPK());
		assertEquals(existingSubscription.getFrequency(),
			newSubscription.getFrequency());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Subscription newSubscription = addSubscription();

		Subscription existingSubscription = _persistence.findByPrimaryKey(newSubscription.getPrimaryKey());

		assertEquals(existingSubscription, newSubscription);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchSubscriptionException");
		}
		catch (NoSuchSubscriptionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Subscription newSubscription = addSubscription();

		Subscription existingSubscription = _persistence.fetchByPrimaryKey(newSubscription.getPrimaryKey());

		assertEquals(existingSubscription, newSubscription);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Subscription missingSubscription = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingSubscription);
	}

	protected Subscription addSubscription() throws Exception {
		long pk = nextLong();

		Subscription subscription = _persistence.create(pk);

		subscription.setCompanyId(nextLong());
		subscription.setUserId(nextLong());
		subscription.setUserName(randomString());
		subscription.setCreateDate(nextDate());
		subscription.setModifiedDate(nextDate());
		subscription.setClassNameId(nextLong());
		subscription.setClassPK(nextLong());
		subscription.setFrequency(randomString());

		_persistence.update(subscription);

		return subscription;
	}

	private static final String _TX_IMPL = SubscriptionPersistence.class.getName() +
		".transaction";
	private SubscriptionPersistence _persistence;
}