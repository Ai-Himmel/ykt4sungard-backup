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

import com.liferay.portlet.journal.NoSuchArticleImageException;
import com.liferay.portlet.journal.model.JournalArticleImage;

/**
 * <a href="JournalArticleImagePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleImagePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (JournalArticleImagePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		JournalArticleImage journalArticleImage = _persistence.create(pk);

		assertNotNull(journalArticleImage);

		assertEquals(journalArticleImage.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		JournalArticleImage newJournalArticleImage = addJournalArticleImage();

		_persistence.remove(newJournalArticleImage);

		JournalArticleImage existingJournalArticleImage = _persistence.fetchByPrimaryKey(newJournalArticleImage.getPrimaryKey());

		assertNull(existingJournalArticleImage);
	}

	public void testUpdateNew() throws Exception {
		addJournalArticleImage();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		JournalArticleImage newJournalArticleImage = _persistence.create(pk);

		newJournalArticleImage.setGroupId(nextLong());
		newJournalArticleImage.setArticleId(randomString());
		newJournalArticleImage.setVersion(nextDouble());
		newJournalArticleImage.setElName(randomString());
		newJournalArticleImage.setLanguageId(randomString());
		newJournalArticleImage.setTempImage(randomBoolean());

		_persistence.update(newJournalArticleImage);

		JournalArticleImage existingJournalArticleImage = _persistence.findByPrimaryKey(newJournalArticleImage.getPrimaryKey());

		assertEquals(existingJournalArticleImage.getArticleImageId(),
			newJournalArticleImage.getArticleImageId());
		assertEquals(existingJournalArticleImage.getGroupId(),
			newJournalArticleImage.getGroupId());
		assertEquals(existingJournalArticleImage.getArticleId(),
			newJournalArticleImage.getArticleId());
		assertEquals(existingJournalArticleImage.getVersion(),
			newJournalArticleImage.getVersion());
		assertEquals(existingJournalArticleImage.getElName(),
			newJournalArticleImage.getElName());
		assertEquals(existingJournalArticleImage.getLanguageId(),
			newJournalArticleImage.getLanguageId());
		assertEquals(existingJournalArticleImage.getTempImage(),
			newJournalArticleImage.getTempImage());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		JournalArticleImage newJournalArticleImage = addJournalArticleImage();

		JournalArticleImage existingJournalArticleImage = _persistence.findByPrimaryKey(newJournalArticleImage.getPrimaryKey());

		assertEquals(existingJournalArticleImage, newJournalArticleImage);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchArticleImageException");
		}
		catch (NoSuchArticleImageException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		JournalArticleImage newJournalArticleImage = addJournalArticleImage();

		JournalArticleImage existingJournalArticleImage = _persistence.fetchByPrimaryKey(newJournalArticleImage.getPrimaryKey());

		assertEquals(existingJournalArticleImage, newJournalArticleImage);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		JournalArticleImage missingJournalArticleImage = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingJournalArticleImage);
	}

	protected JournalArticleImage addJournalArticleImage()
		throws Exception {
		long pk = nextLong();

		JournalArticleImage journalArticleImage = _persistence.create(pk);

		journalArticleImage.setGroupId(nextLong());
		journalArticleImage.setArticleId(randomString());
		journalArticleImage.setVersion(nextDouble());
		journalArticleImage.setElName(randomString());
		journalArticleImage.setLanguageId(randomString());
		journalArticleImage.setTempImage(randomBoolean());

		_persistence.update(journalArticleImage);

		return journalArticleImage;
	}

	private static final String _TX_IMPL = JournalArticleImagePersistence.class.getName() +
		".transaction";
	private JournalArticleImagePersistence _persistence;
}