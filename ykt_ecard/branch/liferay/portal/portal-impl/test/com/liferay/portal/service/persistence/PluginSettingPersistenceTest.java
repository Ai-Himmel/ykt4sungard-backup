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

import com.liferay.portal.NoSuchPluginSettingException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PluginSettingPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PluginSettingPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PluginSettingPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		PluginSetting pluginSetting = _persistence.create(pk);

		assertNotNull(pluginSetting);

		assertEquals(pluginSetting.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		PluginSetting newPluginSetting = addPluginSetting();

		_persistence.remove(newPluginSetting);

		PluginSetting existingPluginSetting = _persistence.fetchByPrimaryKey(newPluginSetting.getPrimaryKey());

		assertNull(existingPluginSetting);
	}

	public void testUpdateNew() throws Exception {
		addPluginSetting();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		PluginSetting newPluginSetting = _persistence.create(pk);

		newPluginSetting.setCompanyId(nextLong());
		newPluginSetting.setPluginId(randomString());
		newPluginSetting.setPluginType(randomString());
		newPluginSetting.setRoles(randomString());
		newPluginSetting.setActive(randomBoolean());

		_persistence.update(newPluginSetting);

		PluginSetting existingPluginSetting = _persistence.findByPrimaryKey(newPluginSetting.getPrimaryKey());

		assertEquals(existingPluginSetting.getPluginSettingId(),
			newPluginSetting.getPluginSettingId());
		assertEquals(existingPluginSetting.getCompanyId(),
			newPluginSetting.getCompanyId());
		assertEquals(existingPluginSetting.getPluginId(),
			newPluginSetting.getPluginId());
		assertEquals(existingPluginSetting.getPluginType(),
			newPluginSetting.getPluginType());
		assertEquals(existingPluginSetting.getRoles(),
			newPluginSetting.getRoles());
		assertEquals(existingPluginSetting.getActive(),
			newPluginSetting.getActive());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		PluginSetting newPluginSetting = addPluginSetting();

		PluginSetting existingPluginSetting = _persistence.findByPrimaryKey(newPluginSetting.getPrimaryKey());

		assertEquals(existingPluginSetting, newPluginSetting);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPluginSettingException");
		}
		catch (NoSuchPluginSettingException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		PluginSetting newPluginSetting = addPluginSetting();

		PluginSetting existingPluginSetting = _persistence.fetchByPrimaryKey(newPluginSetting.getPrimaryKey());

		assertEquals(existingPluginSetting, newPluginSetting);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		PluginSetting missingPluginSetting = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPluginSetting);
	}

	protected PluginSetting addPluginSetting() throws Exception {
		long pk = nextLong();

		PluginSetting pluginSetting = _persistence.create(pk);

		pluginSetting.setCompanyId(nextLong());
		pluginSetting.setPluginId(randomString());
		pluginSetting.setPluginType(randomString());
		pluginSetting.setRoles(randomString());
		pluginSetting.setActive(randomBoolean());

		_persistence.update(pluginSetting);

		return pluginSetting;
	}

	private static final String _TX_IMPL = PluginSettingPersistence.class.getName() +
		".transaction";
	private PluginSettingPersistence _persistence;
}