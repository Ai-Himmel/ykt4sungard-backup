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

package com.liferay.portlet.polls.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.polls.NoSuchChoiceException;
import com.liferay.portlet.polls.model.PollsChoice;

/**
 * <a href="PollsChoicePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsChoicePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PollsChoicePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		PollsChoice pollsChoice = _persistence.create(pk);

		assertNotNull(pollsChoice);

		assertEquals(pollsChoice.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		PollsChoice newPollsChoice = addPollsChoice();

		_persistence.remove(newPollsChoice);

		PollsChoice existingPollsChoice = _persistence.fetchByPrimaryKey(newPollsChoice.getPrimaryKey());

		assertNull(existingPollsChoice);
	}

	public void testUpdateNew() throws Exception {
		addPollsChoice();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		PollsChoice newPollsChoice = _persistence.create(pk);

		newPollsChoice.setUuid(randomString());
		newPollsChoice.setQuestionId(nextLong());
		newPollsChoice.setName(randomString());
		newPollsChoice.setDescription(randomString());

		_persistence.update(newPollsChoice);

		PollsChoice existingPollsChoice = _persistence.findByPrimaryKey(newPollsChoice.getPrimaryKey());

		assertEquals(existingPollsChoice.getUuid(), newPollsChoice.getUuid());
		assertEquals(existingPollsChoice.getChoiceId(),
			newPollsChoice.getChoiceId());
		assertEquals(existingPollsChoice.getQuestionId(),
			newPollsChoice.getQuestionId());
		assertEquals(existingPollsChoice.getName(), newPollsChoice.getName());
		assertEquals(existingPollsChoice.getDescription(),
			newPollsChoice.getDescription());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		PollsChoice newPollsChoice = addPollsChoice();

		PollsChoice existingPollsChoice = _persistence.findByPrimaryKey(newPollsChoice.getPrimaryKey());

		assertEquals(existingPollsChoice, newPollsChoice);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchChoiceException");
		}
		catch (NoSuchChoiceException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		PollsChoice newPollsChoice = addPollsChoice();

		PollsChoice existingPollsChoice = _persistence.fetchByPrimaryKey(newPollsChoice.getPrimaryKey());

		assertEquals(existingPollsChoice, newPollsChoice);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		PollsChoice missingPollsChoice = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPollsChoice);
	}

	protected PollsChoice addPollsChoice() throws Exception {
		long pk = nextLong();

		PollsChoice pollsChoice = _persistence.create(pk);

		pollsChoice.setUuid(randomString());
		pollsChoice.setQuestionId(nextLong());
		pollsChoice.setName(randomString());
		pollsChoice.setDescription(randomString());

		_persistence.update(pollsChoice);

		return pollsChoice;
	}

	private static final String _TX_IMPL = PollsChoicePersistence.class.getName() +
		".transaction";
	private PollsChoicePersistence _persistence;
}