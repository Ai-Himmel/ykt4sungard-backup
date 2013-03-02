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

package com.liferay.portlet.wiki.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.wiki.NoSuchPageResourceException;
import com.liferay.portlet.wiki.model.WikiPageResource;

/**
 * <a href="WikiPageResourcePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageResourcePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (WikiPageResourcePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		WikiPageResource wikiPageResource = _persistence.create(pk);

		assertNotNull(wikiPageResource);

		assertEquals(wikiPageResource.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		WikiPageResource newWikiPageResource = addWikiPageResource();

		_persistence.remove(newWikiPageResource);

		WikiPageResource existingWikiPageResource = _persistence.fetchByPrimaryKey(newWikiPageResource.getPrimaryKey());

		assertNull(existingWikiPageResource);
	}

	public void testUpdateNew() throws Exception {
		addWikiPageResource();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		WikiPageResource newWikiPageResource = _persistence.create(pk);

		newWikiPageResource.setNodeId(nextLong());
		newWikiPageResource.setTitle(randomString());

		_persistence.update(newWikiPageResource);

		WikiPageResource existingWikiPageResource = _persistence.findByPrimaryKey(newWikiPageResource.getPrimaryKey());

		assertEquals(existingWikiPageResource.getResourcePrimKey(),
			newWikiPageResource.getResourcePrimKey());
		assertEquals(existingWikiPageResource.getNodeId(),
			newWikiPageResource.getNodeId());
		assertEquals(existingWikiPageResource.getTitle(),
			newWikiPageResource.getTitle());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		WikiPageResource newWikiPageResource = addWikiPageResource();

		WikiPageResource existingWikiPageResource = _persistence.findByPrimaryKey(newWikiPageResource.getPrimaryKey());

		assertEquals(existingWikiPageResource, newWikiPageResource);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPageResourceException");
		}
		catch (NoSuchPageResourceException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		WikiPageResource newWikiPageResource = addWikiPageResource();

		WikiPageResource existingWikiPageResource = _persistence.fetchByPrimaryKey(newWikiPageResource.getPrimaryKey());

		assertEquals(existingWikiPageResource, newWikiPageResource);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		WikiPageResource missingWikiPageResource = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingWikiPageResource);
	}

	protected WikiPageResource addWikiPageResource() throws Exception {
		long pk = nextLong();

		WikiPageResource wikiPageResource = _persistence.create(pk);

		wikiPageResource.setNodeId(nextLong());
		wikiPageResource.setTitle(randomString());

		_persistence.update(wikiPageResource);

		return wikiPageResource;
	}

	private static final String _TX_IMPL = WikiPageResourcePersistence.class.getName() +
		".transaction";
	private WikiPageResourcePersistence _persistence;
}