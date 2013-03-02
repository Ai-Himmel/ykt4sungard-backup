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

import com.liferay.portal.NoSuchPortletPreferencesException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PortletPreferencesPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPreferencesPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PortletPreferencesPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		PortletPreferences portletPreferences = _persistence.create(pk);

		assertNotNull(portletPreferences);

		assertEquals(portletPreferences.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		PortletPreferences newPortletPreferences = addPortletPreferences();

		_persistence.remove(newPortletPreferences);

		PortletPreferences existingPortletPreferences = _persistence.fetchByPrimaryKey(newPortletPreferences.getPrimaryKey());

		assertNull(existingPortletPreferences);
	}

	public void testUpdateNew() throws Exception {
		addPortletPreferences();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		PortletPreferences newPortletPreferences = _persistence.create(pk);

		newPortletPreferences.setOwnerId(nextLong());
		newPortletPreferences.setOwnerType(nextInt());
		newPortletPreferences.setPlid(nextLong());
		newPortletPreferences.setPortletId(randomString());
		newPortletPreferences.setPreferences(randomString());

		_persistence.update(newPortletPreferences);

		PortletPreferences existingPortletPreferences = _persistence.findByPrimaryKey(newPortletPreferences.getPrimaryKey());

		assertEquals(existingPortletPreferences.getPortletPreferencesId(),
			newPortletPreferences.getPortletPreferencesId());
		assertEquals(existingPortletPreferences.getOwnerId(),
			newPortletPreferences.getOwnerId());
		assertEquals(existingPortletPreferences.getOwnerType(),
			newPortletPreferences.getOwnerType());
		assertEquals(existingPortletPreferences.getPlid(),
			newPortletPreferences.getPlid());
		assertEquals(existingPortletPreferences.getPortletId(),
			newPortletPreferences.getPortletId());
		assertEquals(existingPortletPreferences.getPreferences(),
			newPortletPreferences.getPreferences());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		PortletPreferences newPortletPreferences = addPortletPreferences();

		PortletPreferences existingPortletPreferences = _persistence.findByPrimaryKey(newPortletPreferences.getPrimaryKey());

		assertEquals(existingPortletPreferences, newPortletPreferences);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail(
				"Missing entity did not throw NoSuchPortletPreferencesException");
		}
		catch (NoSuchPortletPreferencesException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		PortletPreferences newPortletPreferences = addPortletPreferences();

		PortletPreferences existingPortletPreferences = _persistence.fetchByPrimaryKey(newPortletPreferences.getPrimaryKey());

		assertEquals(existingPortletPreferences, newPortletPreferences);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		PortletPreferences missingPortletPreferences = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPortletPreferences);
	}

	protected PortletPreferences addPortletPreferences()
		throws Exception {
		long pk = nextLong();

		PortletPreferences portletPreferences = _persistence.create(pk);

		portletPreferences.setOwnerId(nextLong());
		portletPreferences.setOwnerType(nextInt());
		portletPreferences.setPlid(nextLong());
		portletPreferences.setPortletId(randomString());
		portletPreferences.setPreferences(randomString());

		_persistence.update(portletPreferences);

		return portletPreferences;
	}

	private static final String _TX_IMPL = PortletPreferencesPersistence.class.getName() +
		".transaction";
	private PortletPreferencesPersistence _persistence;
}