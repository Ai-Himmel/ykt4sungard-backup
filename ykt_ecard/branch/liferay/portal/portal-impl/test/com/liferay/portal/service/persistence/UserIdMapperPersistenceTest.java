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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchUserIdMapperException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.UserIdMapper;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="UserIdMapperPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserIdMapperPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (UserIdMapperPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		UserIdMapper userIdMapper = _persistence.create(pk);

		assertNotNull(userIdMapper);

		assertEquals(userIdMapper.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		UserIdMapper newUserIdMapper = addUserIdMapper();

		_persistence.remove(newUserIdMapper);

		UserIdMapper existingUserIdMapper = _persistence.fetchByPrimaryKey(newUserIdMapper.getPrimaryKey());

		assertNull(existingUserIdMapper);
	}

	public void testUpdateNew() throws Exception {
		addUserIdMapper();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		UserIdMapper newUserIdMapper = _persistence.create(pk);

		newUserIdMapper.setUserId(nextLong());
		newUserIdMapper.setType(randomString());
		newUserIdMapper.setDescription(randomString());
		newUserIdMapper.setExternalUserId(randomString());

		_persistence.update(newUserIdMapper);

		UserIdMapper existingUserIdMapper = _persistence.findByPrimaryKey(newUserIdMapper.getPrimaryKey());

		assertEquals(existingUserIdMapper.getUserIdMapperId(),
			newUserIdMapper.getUserIdMapperId());
		assertEquals(existingUserIdMapper.getUserId(),
			newUserIdMapper.getUserId());
		assertEquals(existingUserIdMapper.getType(), newUserIdMapper.getType());
		assertEquals(existingUserIdMapper.getDescription(),
			newUserIdMapper.getDescription());
		assertEquals(existingUserIdMapper.getExternalUserId(),
			newUserIdMapper.getExternalUserId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		UserIdMapper newUserIdMapper = addUserIdMapper();

		UserIdMapper existingUserIdMapper = _persistence.findByPrimaryKey(newUserIdMapper.getPrimaryKey());

		assertEquals(existingUserIdMapper, newUserIdMapper);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchUserIdMapperException");
		}
		catch (NoSuchUserIdMapperException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		UserIdMapper newUserIdMapper = addUserIdMapper();

		UserIdMapper existingUserIdMapper = _persistence.fetchByPrimaryKey(newUserIdMapper.getPrimaryKey());

		assertEquals(existingUserIdMapper, newUserIdMapper);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		UserIdMapper missingUserIdMapper = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingUserIdMapper);
	}

	protected UserIdMapper addUserIdMapper() throws Exception {
		long pk = nextLong();

		UserIdMapper userIdMapper = _persistence.create(pk);

		userIdMapper.setUserId(nextLong());
		userIdMapper.setType(randomString());
		userIdMapper.setDescription(randomString());
		userIdMapper.setExternalUserId(randomString());

		_persistence.update(userIdMapper);

		return userIdMapper;
	}

	private static final String _TX_IMPL = UserIdMapperPersistence.class.getName() +
		".transaction";
	private UserIdMapperPersistence _persistence;
}