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

import com.liferay.portal.NoSuchRegionException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Region;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="RegionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RegionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (RegionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Region region = _persistence.create(pk);

		assertNotNull(region);

		assertEquals(region.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Region newRegion = addRegion();

		_persistence.remove(newRegion);

		Region existingRegion = _persistence.fetchByPrimaryKey(newRegion.getPrimaryKey());

		assertNull(existingRegion);
	}

	public void testUpdateNew() throws Exception {
		addRegion();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Region newRegion = _persistence.create(pk);

		newRegion.setCountryId(nextLong());
		newRegion.setRegionCode(randomString());
		newRegion.setName(randomString());
		newRegion.setActive(randomBoolean());

		_persistence.update(newRegion);

		Region existingRegion = _persistence.findByPrimaryKey(newRegion.getPrimaryKey());

		assertEquals(existingRegion.getRegionId(), newRegion.getRegionId());
		assertEquals(existingRegion.getCountryId(), newRegion.getCountryId());
		assertEquals(existingRegion.getRegionCode(), newRegion.getRegionCode());
		assertEquals(existingRegion.getName(), newRegion.getName());
		assertEquals(existingRegion.getActive(), newRegion.getActive());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Region newRegion = addRegion();

		Region existingRegion = _persistence.findByPrimaryKey(newRegion.getPrimaryKey());

		assertEquals(existingRegion, newRegion);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchRegionException");
		}
		catch (NoSuchRegionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Region newRegion = addRegion();

		Region existingRegion = _persistence.fetchByPrimaryKey(newRegion.getPrimaryKey());

		assertEquals(existingRegion, newRegion);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Region missingRegion = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingRegion);
	}

	protected Region addRegion() throws Exception {
		long pk = nextLong();

		Region region = _persistence.create(pk);

		region.setCountryId(nextLong());
		region.setRegionCode(randomString());
		region.setName(randomString());
		region.setActive(randomBoolean());

		_persistence.update(region);

		return region;
	}

	private static final String _TX_IMPL = RegionPersistence.class.getName() +
		".transaction";
	private RegionPersistence _persistence;
}