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

package com.liferay.portal.upgrade.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.tools.comparator.ColumnsComparator;
import com.liferay.portal.upgrade.StagnantRowException;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * <a href="DefaultUpgradeTableImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Bruno Farache
 *
 */
public class DefaultUpgradeTableImpl
	extends BaseUpgradeTableImpl implements UpgradeTable {

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns) {
		this(tableName, columns, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1) {

		this(tableName, columns, upgradeColumn1, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2) {

		this(tableName, columns, upgradeColumn1, upgradeColumn2, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			upgradeColumn4, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4,
								   UpgradeColumn upgradeColumn5) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			upgradeColumn4, upgradeColumn5, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4,
								   UpgradeColumn upgradeColumn5,
								   UpgradeColumn upgradeColumn6) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			upgradeColumn4, upgradeColumn5, upgradeColumn6, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4,
								   UpgradeColumn upgradeColumn5,
								   UpgradeColumn upgradeColumn6,
								   UpgradeColumn upgradeColumn7) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			upgradeColumn4, upgradeColumn5, upgradeColumn6, upgradeColumn7,
			null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4,
								   UpgradeColumn upgradeColumn5,
								   UpgradeColumn upgradeColumn6,
								   UpgradeColumn upgradeColumn7,
								   UpgradeColumn upgradeColumn8) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			upgradeColumn4, upgradeColumn5, upgradeColumn6, upgradeColumn7,
			upgradeColumn8, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4,
								   UpgradeColumn upgradeColumn5,
								   UpgradeColumn upgradeColumn6,
								   UpgradeColumn upgradeColumn7,
								   UpgradeColumn upgradeColumn8,
								   UpgradeColumn upgradeColumn9) {

		this(
			tableName, columns, upgradeColumn1, upgradeColumn2, upgradeColumn3,
			upgradeColumn4, upgradeColumn5, upgradeColumn6, upgradeColumn7,
			upgradeColumn8, upgradeColumn9, null);
	}

	public DefaultUpgradeTableImpl(String tableName, Object[][] columns,
								   UpgradeColumn upgradeColumn1,
								   UpgradeColumn upgradeColumn2,
								   UpgradeColumn upgradeColumn3,
								   UpgradeColumn upgradeColumn4,
								   UpgradeColumn upgradeColumn5,
								   UpgradeColumn upgradeColumn6,
								   UpgradeColumn upgradeColumn7,
								   UpgradeColumn upgradeColumn8,
								   UpgradeColumn upgradeColumn9,
								   UpgradeColumn upgradeColumn10) {

		super(tableName);

		// Sort the column names to ensure they're sorted based on the
		// constructor's list of columns to upgrade. This is needed if you
		// use TempUpgradeColumnImpl and need to ensure a column's temporary
		// value is populated in the correct order.

		columns = (Object[][])columns.clone();

		List sortedColumnNames = new ArrayList();

		getSortedColumnName(sortedColumnNames, upgradeColumn1);
		getSortedColumnName(sortedColumnNames, upgradeColumn2);
		getSortedColumnName(sortedColumnNames, upgradeColumn3);
		getSortedColumnName(sortedColumnNames, upgradeColumn4);
		getSortedColumnName(sortedColumnNames, upgradeColumn5);
		getSortedColumnName(sortedColumnNames, upgradeColumn6);
		getSortedColumnName(sortedColumnNames, upgradeColumn7);
		getSortedColumnName(sortedColumnNames, upgradeColumn8);
		getSortedColumnName(sortedColumnNames, upgradeColumn9);
		getSortedColumnName(sortedColumnNames, upgradeColumn10);

		if (sortedColumnNames.size() > 0) {
			Arrays.sort(columns, new ColumnsComparator(sortedColumnNames));
		}

		setColumns(columns);

		_upgradeColumns = new UpgradeColumn[columns.length];

		prepareUpgradeColumns(upgradeColumn1);
		prepareUpgradeColumns(upgradeColumn2);
		prepareUpgradeColumns(upgradeColumn3);
		prepareUpgradeColumns(upgradeColumn4);
		prepareUpgradeColumns(upgradeColumn5);
		prepareUpgradeColumns(upgradeColumn6);
		prepareUpgradeColumns(upgradeColumn7);
		prepareUpgradeColumns(upgradeColumn8);
		prepareUpgradeColumns(upgradeColumn9);
		prepareUpgradeColumns(upgradeColumn10);
	}

	public String getExportedData(ResultSet rs) throws Exception {
		StringMaker sm = new StringMaker();

		Object[][] columns = getColumns();

		for (int i = 0; i < columns.length; i++) {
			boolean last = false;

			if ((i + 1) == columns.length) {
				last = true;
			}

			if (_upgradeColumns[i] == null) {
				appendColumn(
					sm, rs, (String)columns[i][0], (Integer)columns[i][1],
					last);
			}
			else {
				try {
					Integer columnType = _upgradeColumns[i].getOldColumnType(
						(Integer)columns[i][1]);

					Object oldValue = getValue(
						rs, (String)columns[i][0], columnType);

					_upgradeColumns[i].setOldValue(oldValue);

					Object newValue = _upgradeColumns[i].getNewValue(oldValue);

					_upgradeColumns[i].setNewValue(newValue);

					appendColumn(sm, newValue, last);
				}
				catch (StagnantRowException sre) {
					_upgradeColumns[i].setNewValue(null);

					throw new StagnantRowException(
						"Column " + columns[i][0] + " with value " +
							sre.getMessage(),
						sre);
				}
			}
		}

		return sm.toString();
	}

	public void setColumn(
			PreparedStatement ps, int index, Integer type, String value)
		throws Exception {

		if (_upgradeColumns[index] != null) {
			if (getCreateSQL() == null) {
				type = _upgradeColumns[index].getOldColumnType(type);
			}
			else {
				type = _upgradeColumns[index].getNewColumnType(type);
			}
		}

		super.setColumn(ps, index, type, value);
	}

	protected void getSortedColumnName(
		List sortedColumnNames, UpgradeColumn upgradeColumn) {

		if (upgradeColumn == null) {
			return;
		}

		String name = upgradeColumn.getName();

		if (Validator.isNotNull(name)) {
			sortedColumnNames.add(name);
		}
	}

	protected void prepareUpgradeColumns(UpgradeColumn upgradeColumn) {
		if (upgradeColumn == null) {
			return;
		}

		Object[][] columns = getColumns();

		for (int i = 0; i < columns.length; i++) {
			String name = (String)columns[i][0];

			if (upgradeColumn.isApplicable(name)) {
				_upgradeColumns[i] = upgradeColumn;
			}
		}
	}

	private UpgradeColumn[] _upgradeColumns;

}