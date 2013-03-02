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

import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="GroupPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (GroupPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Group group = _persistence.create(pk);

		assertNotNull(group);

		assertEquals(group.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Group newGroup = addGroup();

		_persistence.remove(newGroup);

		Group existingGroup = _persistence.fetchByPrimaryKey(newGroup.getPrimaryKey());

		assertNull(existingGroup);
	}

	public void testUpdateNew() throws Exception {
		addGroup();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Group newGroup = _persistence.create(pk);

		newGroup.setCompanyId(nextLong());
		newGroup.setCreatorUserId(nextLong());
		newGroup.setClassNameId(nextLong());
		newGroup.setClassPK(nextLong());
		newGroup.setParentGroupId(nextLong());
		newGroup.setLiveGroupId(nextLong());
		newGroup.setName(randomString());
		newGroup.setDescription(randomString());
		newGroup.setType(nextInt());
		newGroup.setTypeSettings(randomString());
		newGroup.setFriendlyURL(randomString());
		newGroup.setActive(randomBoolean());

		_persistence.update(newGroup);

		Group existingGroup = _persistence.findByPrimaryKey(newGroup.getPrimaryKey());

		assertEquals(existingGroup.getGroupId(), newGroup.getGroupId());
		assertEquals(existingGroup.getCompanyId(), newGroup.getCompanyId());
		assertEquals(existingGroup.getCreatorUserId(),
			newGroup.getCreatorUserId());
		assertEquals(existingGroup.getClassNameId(), newGroup.getClassNameId());
		assertEquals(existingGroup.getClassPK(), newGroup.getClassPK());
		assertEquals(existingGroup.getParentGroupId(),
			newGroup.getParentGroupId());
		assertEquals(existingGroup.getLiveGroupId(), newGroup.getLiveGroupId());
		assertEquals(existingGroup.getName(), newGroup.getName());
		assertEquals(existingGroup.getDescription(), newGroup.getDescription());
		assertEquals(existingGroup.getType(), newGroup.getType());
		assertEquals(existingGroup.getTypeSettings(), newGroup.getTypeSettings());
		assertEquals(existingGroup.getFriendlyURL(), newGroup.getFriendlyURL());
		assertEquals(existingGroup.getActive(), newGroup.getActive());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Group newGroup = addGroup();

		Group existingGroup = _persistence.findByPrimaryKey(newGroup.getPrimaryKey());

		assertEquals(existingGroup, newGroup);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchGroupException");
		}
		catch (NoSuchGroupException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Group newGroup = addGroup();

		Group existingGroup = _persistence.fetchByPrimaryKey(newGroup.getPrimaryKey());

		assertEquals(existingGroup, newGroup);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Group missingGroup = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingGroup);
	}

	protected Group addGroup() throws Exception {
		long pk = nextLong();

		Group group = _persistence.create(pk);

		group.setCompanyId(nextLong());
		group.setCreatorUserId(nextLong());
		group.setClassNameId(nextLong());
		group.setClassPK(nextLong());
		group.setParentGroupId(nextLong());
		group.setLiveGroupId(nextLong());
		group.setName(randomString());
		group.setDescription(randomString());
		group.setType(nextInt());
		group.setTypeSettings(randomString());
		group.setFriendlyURL(randomString());
		group.setActive(randomBoolean());

		_persistence.update(group);

		return group;
	}

	private static final String _TX_IMPL = GroupPersistence.class.getName() +
		".transaction";
	private GroupPersistence _persistence;
}