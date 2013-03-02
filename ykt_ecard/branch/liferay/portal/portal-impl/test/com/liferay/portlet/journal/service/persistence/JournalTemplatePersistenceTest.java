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

import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.model.JournalTemplate;

/**
 * <a href="JournalTemplatePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalTemplatePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (JournalTemplatePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		JournalTemplate journalTemplate = _persistence.create(pk);

		assertNotNull(journalTemplate);

		assertEquals(journalTemplate.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		JournalTemplate newJournalTemplate = addJournalTemplate();

		_persistence.remove(newJournalTemplate);

		JournalTemplate existingJournalTemplate = _persistence.fetchByPrimaryKey(newJournalTemplate.getPrimaryKey());

		assertNull(existingJournalTemplate);
	}

	public void testUpdateNew() throws Exception {
		addJournalTemplate();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		JournalTemplate newJournalTemplate = _persistence.create(pk);

		newJournalTemplate.setUuid(randomString());
		newJournalTemplate.setGroupId(nextLong());
		newJournalTemplate.setCompanyId(nextLong());
		newJournalTemplate.setUserId(nextLong());
		newJournalTemplate.setUserName(randomString());
		newJournalTemplate.setCreateDate(nextDate());
		newJournalTemplate.setModifiedDate(nextDate());
		newJournalTemplate.setTemplateId(randomString());
		newJournalTemplate.setStructureId(randomString());
		newJournalTemplate.setName(randomString());
		newJournalTemplate.setDescription(randomString());
		newJournalTemplate.setXsl(randomString());
		newJournalTemplate.setLangType(randomString());
		newJournalTemplate.setCacheable(randomBoolean());
		newJournalTemplate.setSmallImage(randomBoolean());
		newJournalTemplate.setSmallImageId(nextLong());
		newJournalTemplate.setSmallImageURL(randomString());

		_persistence.update(newJournalTemplate);

		JournalTemplate existingJournalTemplate = _persistence.findByPrimaryKey(newJournalTemplate.getPrimaryKey());

		assertEquals(existingJournalTemplate.getUuid(),
			newJournalTemplate.getUuid());
		assertEquals(existingJournalTemplate.getId(), newJournalTemplate.getId());
		assertEquals(existingJournalTemplate.getGroupId(),
			newJournalTemplate.getGroupId());
		assertEquals(existingJournalTemplate.getCompanyId(),
			newJournalTemplate.getCompanyId());
		assertEquals(existingJournalTemplate.getUserId(),
			newJournalTemplate.getUserId());
		assertEquals(existingJournalTemplate.getUserName(),
			newJournalTemplate.getUserName());
		assertEquals(existingJournalTemplate.getCreateDate(),
			newJournalTemplate.getCreateDate());
		assertEquals(existingJournalTemplate.getModifiedDate(),
			newJournalTemplate.getModifiedDate());
		assertEquals(existingJournalTemplate.getTemplateId(),
			newJournalTemplate.getTemplateId());
		assertEquals(existingJournalTemplate.getStructureId(),
			newJournalTemplate.getStructureId());
		assertEquals(existingJournalTemplate.getName(),
			newJournalTemplate.getName());
		assertEquals(existingJournalTemplate.getDescription(),
			newJournalTemplate.getDescription());
		assertEquals(existingJournalTemplate.getXsl(),
			newJournalTemplate.getXsl());
		assertEquals(existingJournalTemplate.getLangType(),
			newJournalTemplate.getLangType());
		assertEquals(existingJournalTemplate.getCacheable(),
			newJournalTemplate.getCacheable());
		assertEquals(existingJournalTemplate.getSmallImage(),
			newJournalTemplate.getSmallImage());
		assertEquals(existingJournalTemplate.getSmallImageId(),
			newJournalTemplate.getSmallImageId());
		assertEquals(existingJournalTemplate.getSmallImageURL(),
			newJournalTemplate.getSmallImageURL());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		JournalTemplate newJournalTemplate = addJournalTemplate();

		JournalTemplate existingJournalTemplate = _persistence.findByPrimaryKey(newJournalTemplate.getPrimaryKey());

		assertEquals(existingJournalTemplate, newJournalTemplate);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchTemplateException");
		}
		catch (NoSuchTemplateException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		JournalTemplate newJournalTemplate = addJournalTemplate();

		JournalTemplate existingJournalTemplate = _persistence.fetchByPrimaryKey(newJournalTemplate.getPrimaryKey());

		assertEquals(existingJournalTemplate, newJournalTemplate);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		JournalTemplate missingJournalTemplate = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingJournalTemplate);
	}

	protected JournalTemplate addJournalTemplate() throws Exception {
		long pk = nextLong();

		JournalTemplate journalTemplate = _persistence.create(pk);

		journalTemplate.setUuid(randomString());
		journalTemplate.setGroupId(nextLong());
		journalTemplate.setCompanyId(nextLong());
		journalTemplate.setUserId(nextLong());
		journalTemplate.setUserName(randomString());
		journalTemplate.setCreateDate(nextDate());
		journalTemplate.setModifiedDate(nextDate());
		journalTemplate.setTemplateId(randomString());
		journalTemplate.setStructureId(randomString());
		journalTemplate.setName(randomString());
		journalTemplate.setDescription(randomString());
		journalTemplate.setXsl(randomString());
		journalTemplate.setLangType(randomString());
		journalTemplate.setCacheable(randomBoolean());
		journalTemplate.setSmallImage(randomBoolean());
		journalTemplate.setSmallImageId(nextLong());
		journalTemplate.setSmallImageURL(randomString());

		_persistence.update(journalTemplate);

		return journalTemplate;
	}

	private static final String _TX_IMPL = JournalTemplatePersistence.class.getName() +
		".transaction";
	private JournalTemplatePersistence _persistence;
}