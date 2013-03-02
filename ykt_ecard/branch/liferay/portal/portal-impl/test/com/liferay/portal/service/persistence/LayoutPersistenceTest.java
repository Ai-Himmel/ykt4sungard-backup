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

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="LayoutPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (LayoutPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Layout layout = _persistence.create(pk);

		assertNotNull(layout);

		assertEquals(layout.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Layout newLayout = addLayout();

		_persistence.remove(newLayout);

		Layout existingLayout = _persistence.fetchByPrimaryKey(newLayout.getPrimaryKey());

		assertNull(existingLayout);
	}

	public void testUpdateNew() throws Exception {
		addLayout();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Layout newLayout = _persistence.create(pk);

		newLayout.setGroupId(nextLong());
		newLayout.setCompanyId(nextLong());
		newLayout.setPrivateLayout(randomBoolean());
		newLayout.setLayoutId(nextLong());
		newLayout.setParentLayoutId(nextLong());
		newLayout.setName(randomString());
		newLayout.setTitle(randomString());
		newLayout.setDescription(randomString());
		newLayout.setType(randomString());
		newLayout.setTypeSettings(randomString());
		newLayout.setHidden(randomBoolean());
		newLayout.setFriendlyURL(randomString());
		newLayout.setIconImage(randomBoolean());
		newLayout.setIconImageId(nextLong());
		newLayout.setThemeId(randomString());
		newLayout.setColorSchemeId(randomString());
		newLayout.setWapThemeId(randomString());
		newLayout.setWapColorSchemeId(randomString());
		newLayout.setCss(randomString());
		newLayout.setPriority(nextInt());
		newLayout.setDlFolderId(nextLong());

		_persistence.update(newLayout);

		Layout existingLayout = _persistence.findByPrimaryKey(newLayout.getPrimaryKey());

		assertEquals(existingLayout.getPlid(), newLayout.getPlid());
		assertEquals(existingLayout.getGroupId(), newLayout.getGroupId());
		assertEquals(existingLayout.getCompanyId(), newLayout.getCompanyId());
		assertEquals(existingLayout.getPrivateLayout(),
			newLayout.getPrivateLayout());
		assertEquals(existingLayout.getLayoutId(), newLayout.getLayoutId());
		assertEquals(existingLayout.getParentLayoutId(),
			newLayout.getParentLayoutId());
		assertEquals(existingLayout.getName(), newLayout.getName());
		assertEquals(existingLayout.getTitle(), newLayout.getTitle());
		assertEquals(existingLayout.getDescription(), newLayout.getDescription());
		assertEquals(existingLayout.getType(), newLayout.getType());
		assertEquals(existingLayout.getTypeSettings(),
			newLayout.getTypeSettings());
		assertEquals(existingLayout.getHidden(), newLayout.getHidden());
		assertEquals(existingLayout.getFriendlyURL(), newLayout.getFriendlyURL());
		assertEquals(existingLayout.getIconImage(), newLayout.getIconImage());
		assertEquals(existingLayout.getIconImageId(), newLayout.getIconImageId());
		assertEquals(existingLayout.getThemeId(), newLayout.getThemeId());
		assertEquals(existingLayout.getColorSchemeId(),
			newLayout.getColorSchemeId());
		assertEquals(existingLayout.getWapThemeId(), newLayout.getWapThemeId());
		assertEquals(existingLayout.getWapColorSchemeId(),
			newLayout.getWapColorSchemeId());
		assertEquals(existingLayout.getCss(), newLayout.getCss());
		assertEquals(existingLayout.getPriority(), newLayout.getPriority());
		assertEquals(existingLayout.getDlFolderId(), newLayout.getDlFolderId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Layout newLayout = addLayout();

		Layout existingLayout = _persistence.findByPrimaryKey(newLayout.getPrimaryKey());

		assertEquals(existingLayout, newLayout);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchLayoutException");
		}
		catch (NoSuchLayoutException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Layout newLayout = addLayout();

		Layout existingLayout = _persistence.fetchByPrimaryKey(newLayout.getPrimaryKey());

		assertEquals(existingLayout, newLayout);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Layout missingLayout = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingLayout);
	}

	protected Layout addLayout() throws Exception {
		long pk = nextLong();

		Layout layout = _persistence.create(pk);

		layout.setGroupId(nextLong());
		layout.setCompanyId(nextLong());
		layout.setPrivateLayout(randomBoolean());
		layout.setLayoutId(nextLong());
		layout.setParentLayoutId(nextLong());
		layout.setName(randomString());
		layout.setTitle(randomString());
		layout.setDescription(randomString());
		layout.setType(randomString());
		layout.setTypeSettings(randomString());
		layout.setHidden(randomBoolean());
		layout.setFriendlyURL(randomString());
		layout.setIconImage(randomBoolean());
		layout.setIconImageId(nextLong());
		layout.setThemeId(randomString());
		layout.setColorSchemeId(randomString());
		layout.setWapThemeId(randomString());
		layout.setWapColorSchemeId(randomString());
		layout.setCss(randomString());
		layout.setPriority(nextInt());
		layout.setDlFolderId(nextLong());

		_persistence.update(layout);

		return layout;
	}

	private static final String _TX_IMPL = LayoutPersistence.class.getName() +
		".transaction";
	private LayoutPersistence _persistence;
}