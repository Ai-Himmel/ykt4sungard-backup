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

package com.liferay.portlet.journal.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.journal.NoSuchContentSearchException;
import com.liferay.portlet.journal.model.JournalContentSearch;

/**
 * <a href="JournalContentSearchPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalContentSearchPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (JournalContentSearchPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		JournalContentSearch journalContentSearch = _persistence.create(pk);

		assertNotNull(journalContentSearch);

		assertEquals(journalContentSearch.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		JournalContentSearch newJournalContentSearch = addJournalContentSearch();

		_persistence.remove(newJournalContentSearch);

		JournalContentSearch existingJournalContentSearch = _persistence.fetchByPrimaryKey(newJournalContentSearch.getPrimaryKey());

		assertNull(existingJournalContentSearch);
	}

	public void testUpdateNew() throws Exception {
		addJournalContentSearch();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		JournalContentSearch newJournalContentSearch = _persistence.create(pk);

		newJournalContentSearch.setGroupId(nextLong());
		newJournalContentSearch.setCompanyId(nextLong());
		newJournalContentSearch.setPrivateLayout(randomBoolean());
		newJournalContentSearch.setLayoutId(nextLong());
		newJournalContentSearch.setPortletId(randomString());
		newJournalContentSearch.setArticleId(randomString());

		_persistence.update(newJournalContentSearch);

		JournalContentSearch existingJournalContentSearch = _persistence.findByPrimaryKey(newJournalContentSearch.getPrimaryKey());

		assertEquals(existingJournalContentSearch.getContentSearchId(),
			newJournalContentSearch.getContentSearchId());
		assertEquals(existingJournalContentSearch.getGroupId(),
			newJournalContentSearch.getGroupId());
		assertEquals(existingJournalContentSearch.getCompanyId(),
			newJournalContentSearch.getCompanyId());
		assertEquals(existingJournalContentSearch.getPrivateLayout(),
			newJournalContentSearch.getPrivateLayout());
		assertEquals(existingJournalContentSearch.getLayoutId(),
			newJournalContentSearch.getLayoutId());
		assertEquals(existingJournalContentSearch.getPortletId(),
			newJournalContentSearch.getPortletId());
		assertEquals(existingJournalContentSearch.getArticleId(),
			newJournalContentSearch.getArticleId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		JournalContentSearch newJournalContentSearch = addJournalContentSearch();

		JournalContentSearch existingJournalContentSearch = _persistence.findByPrimaryKey(newJournalContentSearch.getPrimaryKey());

		assertEquals(existingJournalContentSearch, newJournalContentSearch);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchContentSearchException");
		}
		catch (NoSuchContentSearchException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		JournalContentSearch newJournalContentSearch = addJournalContentSearch();

		JournalContentSearch existingJournalContentSearch = _persistence.fetchByPrimaryKey(newJournalContentSearch.getPrimaryKey());

		assertEquals(existingJournalContentSearch, newJournalContentSearch);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		JournalContentSearch missingJournalContentSearch = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingJournalContentSearch);
	}

	protected JournalContentSearch addJournalContentSearch()
		throws Exception {
		long pk = nextLong();

		JournalContentSearch journalContentSearch = _persistence.create(pk);

		journalContentSearch.setGroupId(nextLong());
		journalContentSearch.setCompanyId(nextLong());
		journalContentSearch.setPrivateLayout(randomBoolean());
		journalContentSearch.setLayoutId(nextLong());
		journalContentSearch.setPortletId(randomString());
		journalContentSearch.setArticleId(randomString());

		_persistence.update(journalContentSearch);

		return journalContentSearch;
	}

	private static final String _TX_IMPL = JournalContentSearchPersistence.class.getName() +
		".transaction";
	private JournalContentSearchPersistence _persistence;
}