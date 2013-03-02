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

import com.liferay.portlet.polls.NoSuchVoteException;
import com.liferay.portlet.polls.model.PollsVote;

/**
 * <a href="PollsVotePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsVotePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PollsVotePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		PollsVote pollsVote = _persistence.create(pk);

		assertNotNull(pollsVote);

		assertEquals(pollsVote.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		PollsVote newPollsVote = addPollsVote();

		_persistence.remove(newPollsVote);

		PollsVote existingPollsVote = _persistence.fetchByPrimaryKey(newPollsVote.getPrimaryKey());

		assertNull(existingPollsVote);
	}

	public void testUpdateNew() throws Exception {
		addPollsVote();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		PollsVote newPollsVote = _persistence.create(pk);

		newPollsVote.setUserId(nextLong());
		newPollsVote.setQuestionId(nextLong());
		newPollsVote.setChoiceId(nextLong());
		newPollsVote.setVoteDate(nextDate());

		_persistence.update(newPollsVote);

		PollsVote existingPollsVote = _persistence.findByPrimaryKey(newPollsVote.getPrimaryKey());

		assertEquals(existingPollsVote.getVoteId(), newPollsVote.getVoteId());
		assertEquals(existingPollsVote.getUserId(), newPollsVote.getUserId());
		assertEquals(existingPollsVote.getQuestionId(),
			newPollsVote.getQuestionId());
		assertEquals(existingPollsVote.getChoiceId(), newPollsVote.getChoiceId());
		assertEquals(existingPollsVote.getVoteDate(), newPollsVote.getVoteDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		PollsVote newPollsVote = addPollsVote();

		PollsVote existingPollsVote = _persistence.findByPrimaryKey(newPollsVote.getPrimaryKey());

		assertEquals(existingPollsVote, newPollsVote);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchVoteException");
		}
		catch (NoSuchVoteException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		PollsVote newPollsVote = addPollsVote();

		PollsVote existingPollsVote = _persistence.fetchByPrimaryKey(newPollsVote.getPrimaryKey());

		assertEquals(existingPollsVote, newPollsVote);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		PollsVote missingPollsVote = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPollsVote);
	}

	protected PollsVote addPollsVote() throws Exception {
		long pk = nextLong();

		PollsVote pollsVote = _persistence.create(pk);

		pollsVote.setUserId(nextLong());
		pollsVote.setQuestionId(nextLong());
		pollsVote.setChoiceId(nextLong());
		pollsVote.setVoteDate(nextDate());

		_persistence.update(pollsVote);

		return pollsVote;
	}

	private static final String _TX_IMPL = PollsVotePersistence.class.getName() +
		".transaction";
	private PollsVotePersistence _persistence;
}