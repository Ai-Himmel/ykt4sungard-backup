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

import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.model.WikiNode;

/**
 * <a href="WikiNodePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiNodePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (WikiNodePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		WikiNode wikiNode = _persistence.create(pk);

		assertNotNull(wikiNode);

		assertEquals(wikiNode.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		WikiNode newWikiNode = addWikiNode();

		_persistence.remove(newWikiNode);

		WikiNode existingWikiNode = _persistence.fetchByPrimaryKey(newWikiNode.getPrimaryKey());

		assertNull(existingWikiNode);
	}

	public void testUpdateNew() throws Exception {
		addWikiNode();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		WikiNode newWikiNode = _persistence.create(pk);

		newWikiNode.setUuid(randomString());
		newWikiNode.setGroupId(nextLong());
		newWikiNode.setCompanyId(nextLong());
		newWikiNode.setUserId(nextLong());
		newWikiNode.setUserName(randomString());
		newWikiNode.setCreateDate(nextDate());
		newWikiNode.setModifiedDate(nextDate());
		newWikiNode.setName(randomString());
		newWikiNode.setDescription(randomString());
		newWikiNode.setLastPostDate(nextDate());

		_persistence.update(newWikiNode);

		WikiNode existingWikiNode = _persistence.findByPrimaryKey(newWikiNode.getPrimaryKey());

		assertEquals(existingWikiNode.getUuid(), newWikiNode.getUuid());
		assertEquals(existingWikiNode.getNodeId(), newWikiNode.getNodeId());
		assertEquals(existingWikiNode.getGroupId(), newWikiNode.getGroupId());
		assertEquals(existingWikiNode.getCompanyId(), newWikiNode.getCompanyId());
		assertEquals(existingWikiNode.getUserId(), newWikiNode.getUserId());
		assertEquals(existingWikiNode.getUserName(), newWikiNode.getUserName());
		assertEquals(existingWikiNode.getCreateDate(),
			newWikiNode.getCreateDate());
		assertEquals(existingWikiNode.getModifiedDate(),
			newWikiNode.getModifiedDate());
		assertEquals(existingWikiNode.getName(), newWikiNode.getName());
		assertEquals(existingWikiNode.getDescription(),
			newWikiNode.getDescription());
		assertEquals(existingWikiNode.getLastPostDate(),
			newWikiNode.getLastPostDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		WikiNode newWikiNode = addWikiNode();

		WikiNode existingWikiNode = _persistence.findByPrimaryKey(newWikiNode.getPrimaryKey());

		assertEquals(existingWikiNode, newWikiNode);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchNodeException");
		}
		catch (NoSuchNodeException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		WikiNode newWikiNode = addWikiNode();

		WikiNode existingWikiNode = _persistence.fetchByPrimaryKey(newWikiNode.getPrimaryKey());

		assertEquals(existingWikiNode, newWikiNode);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		WikiNode missingWikiNode = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingWikiNode);
	}

	protected WikiNode addWikiNode() throws Exception {
		long pk = nextLong();

		WikiNode wikiNode = _persistence.create(pk);

		wikiNode.setUuid(randomString());
		wikiNode.setGroupId(nextLong());
		wikiNode.setCompanyId(nextLong());
		wikiNode.setUserId(nextLong());
		wikiNode.setUserName(randomString());
		wikiNode.setCreateDate(nextDate());
		wikiNode.setModifiedDate(nextDate());
		wikiNode.setName(randomString());
		wikiNode.setDescription(randomString());
		wikiNode.setLastPostDate(nextDate());

		_persistence.update(wikiNode);

		return wikiNode;
	}

	private static final String _TX_IMPL = WikiNodePersistence.class.getName() +
		".transaction";
	private WikiNodePersistence _persistence;
}