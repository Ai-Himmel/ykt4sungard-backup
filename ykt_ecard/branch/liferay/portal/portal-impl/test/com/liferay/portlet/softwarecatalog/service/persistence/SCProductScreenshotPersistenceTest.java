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

package com.liferay.portlet.softwarecatalog.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;
import com.liferay.portlet.softwarecatalog.model.SCProductScreenshot;

/**
 * <a href="SCProductScreenshotPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductScreenshotPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (SCProductScreenshotPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		SCProductScreenshot scProductScreenshot = _persistence.create(pk);

		assertNotNull(scProductScreenshot);

		assertEquals(scProductScreenshot.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		SCProductScreenshot newSCProductScreenshot = addSCProductScreenshot();

		_persistence.remove(newSCProductScreenshot);

		SCProductScreenshot existingSCProductScreenshot = _persistence.fetchByPrimaryKey(newSCProductScreenshot.getPrimaryKey());

		assertNull(existingSCProductScreenshot);
	}

	public void testUpdateNew() throws Exception {
		addSCProductScreenshot();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		SCProductScreenshot newSCProductScreenshot = _persistence.create(pk);

		newSCProductScreenshot.setCompanyId(nextLong());
		newSCProductScreenshot.setGroupId(nextLong());
		newSCProductScreenshot.setProductEntryId(nextLong());
		newSCProductScreenshot.setThumbnailId(nextLong());
		newSCProductScreenshot.setFullImageId(nextLong());
		newSCProductScreenshot.setPriority(nextInt());

		_persistence.update(newSCProductScreenshot);

		SCProductScreenshot existingSCProductScreenshot = _persistence.findByPrimaryKey(newSCProductScreenshot.getPrimaryKey());

		assertEquals(existingSCProductScreenshot.getProductScreenshotId(),
			newSCProductScreenshot.getProductScreenshotId());
		assertEquals(existingSCProductScreenshot.getCompanyId(),
			newSCProductScreenshot.getCompanyId());
		assertEquals(existingSCProductScreenshot.getGroupId(),
			newSCProductScreenshot.getGroupId());
		assertEquals(existingSCProductScreenshot.getProductEntryId(),
			newSCProductScreenshot.getProductEntryId());
		assertEquals(existingSCProductScreenshot.getThumbnailId(),
			newSCProductScreenshot.getThumbnailId());
		assertEquals(existingSCProductScreenshot.getFullImageId(),
			newSCProductScreenshot.getFullImageId());
		assertEquals(existingSCProductScreenshot.getPriority(),
			newSCProductScreenshot.getPriority());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		SCProductScreenshot newSCProductScreenshot = addSCProductScreenshot();

		SCProductScreenshot existingSCProductScreenshot = _persistence.findByPrimaryKey(newSCProductScreenshot.getPrimaryKey());

		assertEquals(existingSCProductScreenshot, newSCProductScreenshot);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail(
				"Missing entity did not throw NoSuchProductScreenshotException");
		}
		catch (NoSuchProductScreenshotException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		SCProductScreenshot newSCProductScreenshot = addSCProductScreenshot();

		SCProductScreenshot existingSCProductScreenshot = _persistence.fetchByPrimaryKey(newSCProductScreenshot.getPrimaryKey());

		assertEquals(existingSCProductScreenshot, newSCProductScreenshot);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		SCProductScreenshot missingSCProductScreenshot = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingSCProductScreenshot);
	}

	protected SCProductScreenshot addSCProductScreenshot()
		throws Exception {
		long pk = nextLong();

		SCProductScreenshot scProductScreenshot = _persistence.create(pk);

		scProductScreenshot.setCompanyId(nextLong());
		scProductScreenshot.setGroupId(nextLong());
		scProductScreenshot.setProductEntryId(nextLong());
		scProductScreenshot.setThumbnailId(nextLong());
		scProductScreenshot.setFullImageId(nextLong());
		scProductScreenshot.setPriority(nextInt());

		_persistence.update(scProductScreenshot);

		return scProductScreenshot;
	}

	private static final String _TX_IMPL = SCProductScreenshotPersistence.class.getName() +
		".transaction";
	private SCProductScreenshotPersistence _persistence;
}