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

package com.liferay.portal.upgrade.v4_4_0.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;

import java.util.HashSet;
import java.util.Set;

/**
 * <a href="DLFolderNameColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class DLFolderNameColumnImpl extends BaseUpgradeColumnImpl {

	public DLFolderNameColumnImpl(
		UpgradeColumn groupIdColumn, UpgradeColumn parentFolderIdColumn) {

		super("name", null);

		_groupIdColumn = groupIdColumn;
		_parentFolderIdColumn = parentFolderIdColumn;
	}

	public Set getDistintNames() {
		return _distinctNames;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		String newName = (String)oldValue;

		while (_distinctNames.contains(_getKey(newName))) {
			_counter++;

			newName = newName + StringPool.SPACE + _counter;
		}

		_distinctNames.add(_getKey(newName));

		return newName;
	}

	private String _getKey(String name) {
		StringMaker sm = new StringMaker();

		sm.append(_groupIdColumn.getOldValue());
		sm.append(StringPool.UNDERLINE);
		sm.append(_parentFolderIdColumn.getOldValue());
		sm.append(StringPool.UNDERLINE);
		sm.append(name);

		return sm.toString();
	}

	private UpgradeColumn _groupIdColumn;
	private UpgradeColumn _parentFolderIdColumn;
	private int _counter = 0;
	private Set _distinctNames = new HashSet();

}