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

import com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;
import com.liferay.portlet.softwarecatalog.model.SCProductVersion;

/**
 * <a href="SCProductVersionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductVersionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (SCProductVersionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		SCProductVersion scProductVersion = _persistence.create(pk);

		assertNotNull(scProductVersion);

		assertEquals(scProductVersion.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		SCProductVersion newSCProductVersion = addSCProductVersion();

		_persistence.remove(newSCProductVersion);

		SCProductVersion existingSCProductVersion = _persistence.fetchByPrimaryKey(newSCProductVersion.getPrimaryKey());

		assertNull(existingSCProductVersion);
	}

	public void testUpdateNew() throws Exception {
		addSCProductVersion();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		SCProductVersion newSCProductVersion = _persistence.create(pk);

		newSCProductVersion.setCompanyId(nextLong());
		newSCProductVersion.setUserId(nextLong());
		newSCProductVersion.setUserName(randomString());
		newSCProductVersion.setCreateDate(nextDate());
		newSCProductVersion.setModifiedDate(nextDate());
		newSCProductVersion.setProductEntryId(nextLong());
		newSCProductVersion.setVersion(randomString());
		newSCProductVersion.setChangeLog(randomString());
		newSCProductVersion.setDownloadPageURL(randomString());
		newSCProductVersion.setDirectDownloadURL(randomString());
		newSCProductVersion.setRepoStoreArtifact(randomBoolean());

		_persistence.update(newSCProductVersion);

		SCProductVersion existingSCProductVersion = _persistence.findByPrimaryKey(newSCProductVersion.getPrimaryKey());

		assertEquals(existingSCProductVersion.getProductVersionId(),
			newSCProductVersion.getProductVersionId());
		assertEquals(existingSCProductVersion.getCompanyId(),
			newSCProductVersion.getCompanyId());
		assertEquals(existingSCProductVersion.getUserId(),
			newSCProductVersion.getUserId());
		assertEquals(existingSCProductVersion.getUserName(),
			newSCProductVersion.getUserName());
		assertEquals(existingSCProductVersion.getCreateDate(),
			newSCProductVersion.getCreateDate());
		assertEquals(existingSCProductVersion.getModifiedDate(),
			newSCProductVersion.getModifiedDate());
		assertEquals(existingSCProductVersion.getProductEntryId(),
			newSCProductVersion.getProductEntryId());
		assertEquals(existingSCProductVersion.getVersion(),
			newSCProductVersion.getVersion());
		assertEquals(existingSCProductVersion.getChangeLog(),
			newSCProductVersion.getChangeLog());
		assertEquals(existingSCProductVersion.getDownloadPageURL(),
			newSCProductVersion.getDownloadPageURL());
		assertEquals(existingSCProductVersion.getDirectDownloadURL(),
			newSCProductVersion.getDirectDownloadURL());
		assertEquals(existingSCProductVersion.getRepoStoreArtifact(),
			newSCProductVersion.getRepoStoreArtifact());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		SCProductVersion newSCProductVersion = addSCProductVersion();

		SCProductVersion existingSCProductVersion = _persistence.findByPrimaryKey(newSCProductVersion.getPrimaryKey());

		assertEquals(existingSCProductVersion, newSCProductVersion);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchProductVersionException");
		}
		catch (NoSuchProductVersionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		SCProductVersion newSCProductVersion = addSCProductVersion();

		SCProductVersion existingSCProductVersion = _persistence.fetchByPrimaryKey(newSCProductVersion.getPrimaryKey());

		assertEquals(existingSCProductVersion, newSCProductVersion);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		SCProductVersion missingSCProductVersion = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingSCProductVersion);
	}

	protected SCProductVersion addSCProductVersion() throws Exception {
		long pk = nextLong();

		SCProductVersion scProductVersion = _persistence.create(pk);

		scProductVersion.setCompanyId(nextLong());
		scProductVersion.setUserId(nextLong());
		scProductVersion.setUserName(randomString());
		scProductVersion.setCreateDate(nextDate());
		scProductVersion.setModifiedDate(nextDate());
		scProductVersion.setProductEntryId(nextLong());
		scProductVersion.setVersion(randomString());
		scProductVersion.setChangeLog(randomString());
		scProductVersion.setDownloadPageURL(randomString());
		scProductVersion.setDirectDownloadURL(randomString());
		scProductVersion.setRepoStoreArtifact(randomBoolean());

		_persistence.update(scProductVersion);

		return scProductVersion;
	}

	private static final String _TX_IMPL = SCProductVersionPersistence.class.getName() +
		".transaction";
	private SCProductVersionPersistence _persistence;
}