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

import com.liferay.portlet.journal.NoSuchFeedException;
import com.liferay.portlet.journal.model.JournalFeed;

/**
 * <a href="JournalFeedPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalFeedPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (JournalFeedPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		JournalFeed journalFeed = _persistence.create(pk);

		assertNotNull(journalFeed);

		assertEquals(journalFeed.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		JournalFeed newJournalFeed = addJournalFeed();

		_persistence.remove(newJournalFeed);

		JournalFeed existingJournalFeed = _persistence.fetchByPrimaryKey(newJournalFeed.getPrimaryKey());

		assertNull(existingJournalFeed);
	}

	public void testUpdateNew() throws Exception {
		addJournalFeed();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		JournalFeed newJournalFeed = _persistence.create(pk);

		newJournalFeed.setUuid(randomString());
		newJournalFeed.setGroupId(nextLong());
		newJournalFeed.setCompanyId(nextLong());
		newJournalFeed.setUserId(nextLong());
		newJournalFeed.setUserName(randomString());
		newJournalFeed.setCreateDate(nextDate());
		newJournalFeed.setModifiedDate(nextDate());
		newJournalFeed.setFeedId(randomString());
		newJournalFeed.setName(randomString());
		newJournalFeed.setDescription(randomString());
		newJournalFeed.setType(randomString());
		newJournalFeed.setStructureId(randomString());
		newJournalFeed.setTemplateId(randomString());
		newJournalFeed.setRendererTemplateId(randomString());
		newJournalFeed.setDelta(nextInt());
		newJournalFeed.setOrderByCol(randomString());
		newJournalFeed.setOrderByType(randomString());
		newJournalFeed.setTargetLayoutFriendlyUrl(randomString());
		newJournalFeed.setTargetPortletId(randomString());
		newJournalFeed.setContentField(randomString());
		newJournalFeed.setFeedType(randomString());
		newJournalFeed.setFeedVersion(nextDouble());

		_persistence.update(newJournalFeed);

		JournalFeed existingJournalFeed = _persistence.findByPrimaryKey(newJournalFeed.getPrimaryKey());

		assertEquals(existingJournalFeed.getUuid(), newJournalFeed.getUuid());
		assertEquals(existingJournalFeed.getId(), newJournalFeed.getId());
		assertEquals(existingJournalFeed.getGroupId(),
			newJournalFeed.getGroupId());
		assertEquals(existingJournalFeed.getCompanyId(),
			newJournalFeed.getCompanyId());
		assertEquals(existingJournalFeed.getUserId(), newJournalFeed.getUserId());
		assertEquals(existingJournalFeed.getUserName(),
			newJournalFeed.getUserName());
		assertEquals(existingJournalFeed.getCreateDate(),
			newJournalFeed.getCreateDate());
		assertEquals(existingJournalFeed.getModifiedDate(),
			newJournalFeed.getModifiedDate());
		assertEquals(existingJournalFeed.getFeedId(), newJournalFeed.getFeedId());
		assertEquals(existingJournalFeed.getName(), newJournalFeed.getName());
		assertEquals(existingJournalFeed.getDescription(),
			newJournalFeed.getDescription());
		assertEquals(existingJournalFeed.getType(), newJournalFeed.getType());
		assertEquals(existingJournalFeed.getStructureId(),
			newJournalFeed.getStructureId());
		assertEquals(existingJournalFeed.getTemplateId(),
			newJournalFeed.getTemplateId());
		assertEquals(existingJournalFeed.getRendererTemplateId(),
			newJournalFeed.getRendererTemplateId());
		assertEquals(existingJournalFeed.getDelta(), newJournalFeed.getDelta());
		assertEquals(existingJournalFeed.getOrderByCol(),
			newJournalFeed.getOrderByCol());
		assertEquals(existingJournalFeed.getOrderByType(),
			newJournalFeed.getOrderByType());
		assertEquals(existingJournalFeed.getTargetLayoutFriendlyUrl(),
			newJournalFeed.getTargetLayoutFriendlyUrl());
		assertEquals(existingJournalFeed.getTargetPortletId(),
			newJournalFeed.getTargetPortletId());
		assertEquals(existingJournalFeed.getContentField(),
			newJournalFeed.getContentField());
		assertEquals(existingJournalFeed.getFeedType(),
			newJournalFeed.getFeedType());
		assertEquals(existingJournalFeed.getFeedVersion(),
			newJournalFeed.getFeedVersion());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		JournalFeed newJournalFeed = addJournalFeed();

		JournalFeed existingJournalFeed = _persistence.findByPrimaryKey(newJournalFeed.getPrimaryKey());

		assertEquals(existingJournalFeed, newJournalFeed);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchFeedException");
		}
		catch (NoSuchFeedException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		JournalFeed newJournalFeed = addJournalFeed();

		JournalFeed existingJournalFeed = _persistence.fetchByPrimaryKey(newJournalFeed.getPrimaryKey());

		assertEquals(existingJournalFeed, newJournalFeed);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		JournalFeed missingJournalFeed = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingJournalFeed);
	}

	protected JournalFeed addJournalFeed() throws Exception {
		long pk = nextLong();

		JournalFeed journalFeed = _persistence.create(pk);

		journalFeed.setUuid(randomString());
		journalFeed.setGroupId(nextLong());
		journalFeed.setCompanyId(nextLong());
		journalFeed.setUserId(nextLong());
		journalFeed.setUserName(randomString());
		journalFeed.setCreateDate(nextDate());
		journalFeed.setModifiedDate(nextDate());
		journalFeed.setFeedId(randomString());
		journalFeed.setName(randomString());
		journalFeed.setDescription(randomString());
		journalFeed.setType(randomString());
		journalFeed.setStructureId(randomString());
		journalFeed.setTemplateId(randomString());
		journalFeed.setRendererTemplateId(randomString());
		journalFeed.setDelta(nextInt());
		journalFeed.setOrderByCol(randomString());
		journalFeed.setOrderByType(randomString());
		journalFeed.setTargetLayoutFriendlyUrl(randomString());
		journalFeed.setTargetPortletId(randomString());
		journalFeed.setContentField(randomString());
		journalFeed.setFeedType(randomString());
		journalFeed.setFeedVersion(nextDouble());

		_persistence.update(journalFeed);

		return journalFeed;
	}

	private static final String _TX_IMPL = JournalFeedPersistence.class.getName() +
		".transaction";
	private JournalFeedPersistence _persistence;
}