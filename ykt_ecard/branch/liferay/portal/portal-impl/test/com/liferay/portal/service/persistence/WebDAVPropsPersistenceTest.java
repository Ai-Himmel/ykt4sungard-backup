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

import com.liferay.portal.NoSuchWebDAVPropsException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.WebDAVProps;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="WebDAVPropsPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WebDAVPropsPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (WebDAVPropsPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		WebDAVProps webDAVProps = _persistence.create(pk);

		assertNotNull(webDAVProps);

		assertEquals(webDAVProps.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		WebDAVProps newWebDAVProps = addWebDAVProps();

		_persistence.remove(newWebDAVProps);

		WebDAVProps existingWebDAVProps = _persistence.fetchByPrimaryKey(newWebDAVProps.getPrimaryKey());

		assertNull(existingWebDAVProps);
	}

	public void testUpdateNew() throws Exception {
		addWebDAVProps();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		WebDAVProps newWebDAVProps = _persistence.create(pk);

		newWebDAVProps.setCompanyId(nextLong());
		newWebDAVProps.setCreateDate(nextDate());
		newWebDAVProps.setModifiedDate(nextDate());
		newWebDAVProps.setClassNameId(nextLong());
		newWebDAVProps.setClassPK(nextLong());
		newWebDAVProps.setProps(randomString());

		_persistence.update(newWebDAVProps);

		WebDAVProps existingWebDAVProps = _persistence.findByPrimaryKey(newWebDAVProps.getPrimaryKey());

		assertEquals(existingWebDAVProps.getWebDavPropsId(),
			newWebDAVProps.getWebDavPropsId());
		assertEquals(existingWebDAVProps.getCompanyId(),
			newWebDAVProps.getCompanyId());
		assertEquals(existingWebDAVProps.getCreateDate(),
			newWebDAVProps.getCreateDate());
		assertEquals(existingWebDAVProps.getModifiedDate(),
			newWebDAVProps.getModifiedDate());
		assertEquals(existingWebDAVProps.getClassNameId(),
			newWebDAVProps.getClassNameId());
		assertEquals(existingWebDAVProps.getClassPK(),
			newWebDAVProps.getClassPK());
		assertEquals(existingWebDAVProps.getProps(), newWebDAVProps.getProps());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		WebDAVProps newWebDAVProps = addWebDAVProps();

		WebDAVProps existingWebDAVProps = _persistence.findByPrimaryKey(newWebDAVProps.getPrimaryKey());

		assertEquals(existingWebDAVProps, newWebDAVProps);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchWebDAVPropsException");
		}
		catch (NoSuchWebDAVPropsException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		WebDAVProps newWebDAVProps = addWebDAVProps();

		WebDAVProps existingWebDAVProps = _persistence.fetchByPrimaryKey(newWebDAVProps.getPrimaryKey());

		assertEquals(existingWebDAVProps, newWebDAVProps);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		WebDAVProps missingWebDAVProps = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingWebDAVProps);
	}

	protected WebDAVProps addWebDAVProps() throws Exception {
		long pk = nextLong();

		WebDAVProps webDAVProps = _persistence.create(pk);

		webDAVProps.setCompanyId(nextLong());
		webDAVProps.setCreateDate(nextDate());
		webDAVProps.setModifiedDate(nextDate());
		webDAVProps.setClassNameId(nextLong());
		webDAVProps.setClassPK(nextLong());
		webDAVProps.setProps(randomString());

		_persistence.update(webDAVProps);

		return webDAVProps;
	}

	private static final String _TX_IMPL = WebDAVPropsPersistence.class.getName() +
		".transaction";
	private WebDAVPropsPersistence _persistence;
}