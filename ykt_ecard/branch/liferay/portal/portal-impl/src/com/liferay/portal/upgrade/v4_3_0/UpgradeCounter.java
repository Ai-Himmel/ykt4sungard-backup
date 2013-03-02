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

package com.liferay.portal.upgrade.v4_3_0;

import com.liferay.counter.model.Counter;
import com.liferay.counter.service.CounterLocalServiceUtil;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.UpgradeTable;

import java.sql.Types;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeCounter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeCounter extends UpgradeProcess {

	public void upgrade() throws UpgradeException {
		_log.info("Upgrading");

		try {
			doUpgrade();
		}
		catch (Exception e) {
			throw new UpgradeException(e);
		}
	}

	protected void doUpgrade() throws Exception {

		// Counter

		List names = CounterLocalServiceUtil.getNames();

		for (int i = 0; i < names.size(); i++) {
			String name = (String)names.get(i);

			if (name.startsWith("com.liferay.") &&
				!name.equals(Counter.class.getName()) &&
				!name.equals(Permission.class.getName()) &&
				!name.equals(Resource.class.getName()) &&
				!name.equals(ResourceCode.class.getName()) &&
				!name.equals(UserTracker.class.getName())) {

				CounterLocalServiceUtil.reset(name);
			}
		}

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			_TABLE_COUNTER, _COLUMNS_COUNTER);

		upgradeTable.setCreateSQL(_CREATE_COUNTER);

		upgradeTable.updateTable();
	}

	private static final String _TABLE_COUNTER = "Counter";

	private static final Object[][] _COLUMNS_COUNTER = {
		{"name", new Integer(Types.VARCHAR)},
		{"currentId", new Integer(Types.BIGINT)}
	};

	private static final String _CREATE_COUNTER =
		"create table Counter (" +
			"name VARCHAR(75) not null primary key," +
			"currentId LONG" +
		")";

	private static Log _log = LogFactory.getLog(UpgradeCounter.class);

}