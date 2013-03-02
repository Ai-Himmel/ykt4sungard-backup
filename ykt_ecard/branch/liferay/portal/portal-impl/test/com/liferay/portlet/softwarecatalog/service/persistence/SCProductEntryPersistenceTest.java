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

import com.liferay.portlet.softwarecatalog.NoSuchProductEntryException;
import com.liferay.portlet.softwarecatalog.model.SCProductEntry;

/**
 * <a href="SCProductEntryPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductEntryPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (SCProductEntryPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		SCProductEntry scProductEntry = _persistence.create(pk);

		assertNotNull(scProductEntry);

		assertEquals(scProductEntry.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		SCProductEntry newSCProductEntry = addSCProductEntry();

		_persistence.remove(newSCProductEntry);

		SCProductEntry existingSCProductEntry = _persistence.fetchByPrimaryKey(newSCProductEntry.getPrimaryKey());

		assertNull(existingSCProductEntry);
	}

	public void testUpdateNew() throws Exception {
		addSCProductEntry();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		SCProductEntry newSCProductEntry = _persistence.create(pk);

		newSCProductEntry.setGroupId(nextLong());
		newSCProductEntry.setCompanyId(nextLong());
		newSCProductEntry.setUserId(nextLong());
		newSCProductEntry.setUserName(randomString());
		newSCProductEntry.setCreateDate(nextDate());
		newSCProductEntry.setModifiedDate(nextDate());
		newSCProductEntry.setName(randomString());
		newSCProductEntry.setType(randomString());
		newSCProductEntry.setTags(randomString());
		newSCProductEntry.setShortDescription(randomString());
		newSCProductEntry.setLongDescription(randomString());
		newSCProductEntry.setPageURL(randomString());
		newSCProductEntry.setAuthor(randomString());
		newSCProductEntry.setRepoGroupId(randomString());
		newSCProductEntry.setRepoArtifactId(randomString());

		_persistence.update(newSCProductEntry);

		SCProductEntry existingSCProductEntry = _persistence.findByPrimaryKey(newSCProductEntry.getPrimaryKey());

		assertEquals(existingSCProductEntry.getProductEntryId(),
			newSCProductEntry.getProductEntryId());
		assertEquals(existingSCProductEntry.getGroupId(),
			newSCProductEntry.getGroupId());
		assertEquals(existingSCProductEntry.getCompanyId(),
			newSCProductEntry.getCompanyId());
		assertEquals(existingSCProductEntry.getUserId(),
			newSCProductEntry.getUserId());
		assertEquals(existingSCProductEntry.getUserName(),
			newSCProductEntry.getUserName());
		assertEquals(existingSCProductEntry.getCreateDate(),
			newSCProductEntry.getCreateDate());
		assertEquals(existingSCProductEntry.getModifiedDate(),
			newSCProductEntry.getModifiedDate());
		assertEquals(existingSCProductEntry.getName(),
			newSCProductEntry.getName());
		assertEquals(existingSCProductEntry.getType(),
			newSCProductEntry.getType());
		assertEquals(existingSCProductEntry.getTags(),
			newSCProductEntry.getTags());
		assertEquals(existingSCProductEntry.getShortDescription(),
			newSCProductEntry.getShortDescription());
		assertEquals(existingSCProductEntry.getLongDescription(),
			newSCProductEntry.getLongDescription());
		assertEquals(existingSCProductEntry.getPageURL(),
			newSCProductEntry.getPageURL());
		assertEquals(existingSCProductEntry.getAuthor(),
			newSCProductEntry.getAuthor());
		assertEquals(existingSCProductEntry.getRepoGroupId(),
			newSCProductEntry.getRepoGroupId());
		assertEquals(existingSCProductEntry.getRepoArtifactId(),
			newSCProductEntry.getRepoArtifactId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		SCProductEntry newSCProductEntry = addSCProductEntry();

		SCProductEntry existingSCProductEntry = _persistence.findByPrimaryKey(newSCProductEntry.getPrimaryKey());

		assertEquals(existingSCProductEntry, newSCProductEntry);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchProductEntryException");
		}
		catch (NoSuchProductEntryException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		SCProductEntry newSCProductEntry = addSCProductEntry();

		SCProductEntry existingSCProductEntry = _persistence.fetchByPrimaryKey(newSCProductEntry.getPrimaryKey());

		assertEquals(existingSCProductEntry, newSCProductEntry);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		SCProductEntry missingSCProductEntry = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingSCProductEntry);
	}

	protected SCProductEntry addSCProductEntry() throws Exception {
		long pk = nextLong();

		SCProductEntry scProductEntry = _persistence.create(pk);

		scProductEntry.setGroupId(nextLong());
		scProductEntry.setCompanyId(nextLong());
		scProductEntry.setUserId(nextLong());
		scProductEntry.setUserName(randomString());
		scProductEntry.setCreateDate(nextDate());
		scProductEntry.setModifiedDate(nextDate());
		scProductEntry.setName(randomString());
		scProductEntry.setType(randomString());
		scProductEntry.setTags(randomString());
		scProductEntry.setShortDescription(randomString());
		scProductEntry.setLongDescription(randomString());
		scProductEntry.setPageURL(randomString());
		scProductEntry.setAuthor(randomString());
		scProductEntry.setRepoGroupId(randomString());
		scProductEntry.setRepoArtifactId(randomString());

		_persistence.update(scProductEntry);

		return scProductEntry;
	}

	private static final String _TX_IMPL = SCProductEntryPersistence.class.getName() +
		".transaction";
	private SCProductEntryPersistence _persistence;
}