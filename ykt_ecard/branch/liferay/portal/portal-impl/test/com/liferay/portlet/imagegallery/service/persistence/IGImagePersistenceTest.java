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

package com.liferay.portlet.imagegallery.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.imagegallery.NoSuchImageException;
import com.liferay.portlet.imagegallery.model.IGImage;

/**
 * <a href="IGImagePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IGImagePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (IGImagePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		IGImage igImage = _persistence.create(pk);

		assertNotNull(igImage);

		assertEquals(igImage.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		IGImage newIGImage = addIGImage();

		_persistence.remove(newIGImage);

		IGImage existingIGImage = _persistence.fetchByPrimaryKey(newIGImage.getPrimaryKey());

		assertNull(existingIGImage);
	}

	public void testUpdateNew() throws Exception {
		addIGImage();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		IGImage newIGImage = _persistence.create(pk);

		newIGImage.setUuid(randomString());
		newIGImage.setCompanyId(nextLong());
		newIGImage.setUserId(nextLong());
		newIGImage.setCreateDate(nextDate());
		newIGImage.setModifiedDate(nextDate());
		newIGImage.setFolderId(nextLong());
		newIGImage.setDescription(randomString());
		newIGImage.setSmallImageId(nextLong());
		newIGImage.setLargeImageId(nextLong());

		_persistence.update(newIGImage);

		IGImage existingIGImage = _persistence.findByPrimaryKey(newIGImage.getPrimaryKey());

		assertEquals(existingIGImage.getUuid(), newIGImage.getUuid());
		assertEquals(existingIGImage.getImageId(), newIGImage.getImageId());
		assertEquals(existingIGImage.getCompanyId(), newIGImage.getCompanyId());
		assertEquals(existingIGImage.getUserId(), newIGImage.getUserId());
		assertEquals(existingIGImage.getCreateDate(), newIGImage.getCreateDate());
		assertEquals(existingIGImage.getModifiedDate(),
			newIGImage.getModifiedDate());
		assertEquals(existingIGImage.getFolderId(), newIGImage.getFolderId());
		assertEquals(existingIGImage.getDescription(),
			newIGImage.getDescription());
		assertEquals(existingIGImage.getSmallImageId(),
			newIGImage.getSmallImageId());
		assertEquals(existingIGImage.getLargeImageId(),
			newIGImage.getLargeImageId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		IGImage newIGImage = addIGImage();

		IGImage existingIGImage = _persistence.findByPrimaryKey(newIGImage.getPrimaryKey());

		assertEquals(existingIGImage, newIGImage);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchImageException");
		}
		catch (NoSuchImageException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		IGImage newIGImage = addIGImage();

		IGImage existingIGImage = _persistence.fetchByPrimaryKey(newIGImage.getPrimaryKey());

		assertEquals(existingIGImage, newIGImage);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		IGImage missingIGImage = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingIGImage);
	}

	protected IGImage addIGImage() throws Exception {
		long pk = nextLong();

		IGImage igImage = _persistence.create(pk);

		igImage.setUuid(randomString());
		igImage.setCompanyId(nextLong());
		igImage.setUserId(nextLong());
		igImage.setCreateDate(nextDate());
		igImage.setModifiedDate(nextDate());
		igImage.setFolderId(nextLong());
		igImage.setDescription(randomString());
		igImage.setSmallImageId(nextLong());
		igImage.setLargeImageId(nextLong());

		_persistence.update(igImage);

		return igImage;
	}

	private static final String _TX_IMPL = IGImagePersistence.class.getName() +
		".transaction";
	private IGImagePersistence _persistence;
}