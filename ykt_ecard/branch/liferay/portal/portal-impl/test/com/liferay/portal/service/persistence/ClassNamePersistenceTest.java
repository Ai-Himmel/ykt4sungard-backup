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

import com.liferay.portal.NoSuchClassNameException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.ClassName;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="ClassNamePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ClassNamePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ClassNamePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ClassName className = _persistence.create(pk);

		assertNotNull(className);

		assertEquals(className.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ClassName newClassName = addClassName();

		_persistence.remove(newClassName);

		ClassName existingClassName = _persistence.fetchByPrimaryKey(newClassName.getPrimaryKey());

		assertNull(existingClassName);
	}

	public void testUpdateNew() throws Exception {
		addClassName();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ClassName newClassName = _persistence.create(pk);

		newClassName.setValue(randomString());

		_persistence.update(newClassName);

		ClassName existingClassName = _persistence.findByPrimaryKey(newClassName.getPrimaryKey());

		assertEquals(existingClassName.getClassNameId(),
			newClassName.getClassNameId());
		assertEquals(existingClassName.getValue(), newClassName.getValue());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ClassName newClassName = addClassName();

		ClassName existingClassName = _persistence.findByPrimaryKey(newClassName.getPrimaryKey());

		assertEquals(existingClassName, newClassName);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchClassNameException");
		}
		catch (NoSuchClassNameException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ClassName newClassName = addClassName();

		ClassName existingClassName = _persistence.fetchByPrimaryKey(newClassName.getPrimaryKey());

		assertEquals(existingClassName, newClassName);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ClassName missingClassName = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingClassName);
	}

	protected ClassName addClassName() throws Exception {
		long pk = nextLong();

		ClassName className = _persistence.create(pk);

		className.setValue(randomString());

		_persistence.update(className);

		return className;
	}

	private static final String _TX_IMPL = ClassNamePersistence.class.getName() +
		".transaction";
	private ClassNamePersistence _persistence;
}