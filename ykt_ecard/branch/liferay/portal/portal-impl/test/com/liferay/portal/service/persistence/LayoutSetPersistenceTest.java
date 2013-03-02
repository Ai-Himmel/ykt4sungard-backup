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

import com.liferay.portal.NoSuchLayoutSetException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="LayoutSetPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutSetPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (LayoutSetPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		LayoutSet layoutSet = _persistence.create(pk);

		assertNotNull(layoutSet);

		assertEquals(layoutSet.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		LayoutSet newLayoutSet = addLayoutSet();

		_persistence.remove(newLayoutSet);

		LayoutSet existingLayoutSet = _persistence.fetchByPrimaryKey(newLayoutSet.getPrimaryKey());

		assertNull(existingLayoutSet);
	}

	public void testUpdateNew() throws Exception {
		addLayoutSet();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		LayoutSet newLayoutSet = _persistence.create(pk);

		newLayoutSet.setGroupId(nextLong());
		newLayoutSet.setCompanyId(nextLong());
		newLayoutSet.setPrivateLayout(randomBoolean());
		newLayoutSet.setLogo(randomBoolean());
		newLayoutSet.setLogoId(nextLong());
		newLayoutSet.setThemeId(randomString());
		newLayoutSet.setColorSchemeId(randomString());
		newLayoutSet.setWapThemeId(randomString());
		newLayoutSet.setWapColorSchemeId(randomString());
		newLayoutSet.setCss(randomString());
		newLayoutSet.setPageCount(nextInt());
		newLayoutSet.setVirtualHost(randomString());

		_persistence.update(newLayoutSet);

		LayoutSet existingLayoutSet = _persistence.findByPrimaryKey(newLayoutSet.getPrimaryKey());

		assertEquals(existingLayoutSet.getLayoutSetId(),
			newLayoutSet.getLayoutSetId());
		assertEquals(existingLayoutSet.getGroupId(), newLayoutSet.getGroupId());
		assertEquals(existingLayoutSet.getCompanyId(),
			newLayoutSet.getCompanyId());
		assertEquals(existingLayoutSet.getPrivateLayout(),
			newLayoutSet.getPrivateLayout());
		assertEquals(existingLayoutSet.getLogo(), newLayoutSet.getLogo());
		assertEquals(existingLayoutSet.getLogoId(), newLayoutSet.getLogoId());
		assertEquals(existingLayoutSet.getThemeId(), newLayoutSet.getThemeId());
		assertEquals(existingLayoutSet.getColorSchemeId(),
			newLayoutSet.getColorSchemeId());
		assertEquals(existingLayoutSet.getWapThemeId(),
			newLayoutSet.getWapThemeId());
		assertEquals(existingLayoutSet.getWapColorSchemeId(),
			newLayoutSet.getWapColorSchemeId());
		assertEquals(existingLayoutSet.getCss(), newLayoutSet.getCss());
		assertEquals(existingLayoutSet.getPageCount(),
			newLayoutSet.getPageCount());
		assertEquals(existingLayoutSet.getVirtualHost(),
			newLayoutSet.getVirtualHost());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		LayoutSet newLayoutSet = addLayoutSet();

		LayoutSet existingLayoutSet = _persistence.findByPrimaryKey(newLayoutSet.getPrimaryKey());

		assertEquals(existingLayoutSet, newLayoutSet);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchLayoutSetException");
		}
		catch (NoSuchLayoutSetException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		LayoutSet newLayoutSet = addLayoutSet();

		LayoutSet existingLayoutSet = _persistence.fetchByPrimaryKey(newLayoutSet.getPrimaryKey());

		assertEquals(existingLayoutSet, newLayoutSet);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		LayoutSet missingLayoutSet = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingLayoutSet);
	}

	protected LayoutSet addLayoutSet() throws Exception {
		long pk = nextLong();

		LayoutSet layoutSet = _persistence.create(pk);

		layoutSet.setGroupId(nextLong());
		layoutSet.setCompanyId(nextLong());
		layoutSet.setPrivateLayout(randomBoolean());
		layoutSet.setLogo(randomBoolean());
		layoutSet.setLogoId(nextLong());
		layoutSet.setThemeId(randomString());
		layoutSet.setColorSchemeId(randomString());
		layoutSet.setWapThemeId(randomString());
		layoutSet.setWapColorSchemeId(randomString());
		layoutSet.setCss(randomString());
		layoutSet.setPageCount(nextInt());
		layoutSet.setVirtualHost(randomString());

		_persistence.update(layoutSet);

		return layoutSet;
	}

	private static final String _TX_IMPL = LayoutSetPersistence.class.getName() +
		".transaction";
	private LayoutSetPersistence _persistence;
}