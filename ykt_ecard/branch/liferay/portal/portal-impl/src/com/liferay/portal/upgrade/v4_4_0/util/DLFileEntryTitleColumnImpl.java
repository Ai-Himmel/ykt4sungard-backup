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
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portlet.documentlibrary.model.impl.DLFileEntryImpl;
import com.liferay.util.FileUtil;

import java.util.Set;

/**
 * <a href="DLFileEntryTitleColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class DLFileEntryTitleColumnImpl extends BaseUpgradeColumnImpl {

	public DLFileEntryTitleColumnImpl(
		UpgradeColumn groupIdColumn, UpgradeColumn folderIdColumn,
		UpgradeColumn nameColumn, Set distinctTitles) {

		super("title", null);

		_groupIdColumn = groupIdColumn;
		_folderIdColumn = folderIdColumn;
		_nameColumn = nameColumn;
		_distinctTitles = distinctTitles;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		String newTitle = (String)oldValue;

		String name = (String)_nameColumn.getOldValue();
		String extension = FileUtil.getExtension(name);

		newTitle = DLFileEntryImpl.stripExtension(name, newTitle);

		while (_distinctTitles.contains(_getKey(newTitle, extension))) {
			_counter++;

			StringMaker sm = new StringMaker();

			sm.append(newTitle);
			sm.append(StringPool.SPACE);
			sm.append(_counter);

			newTitle = sm.toString();
		}

		_distinctTitles.add(_getKey(newTitle, extension));

		return newTitle;
	}

	private String _getKey(String title, String extension) {
		StringMaker sm = new StringMaker();

		sm.append(_groupIdColumn.getOldValue());
		sm.append(StringPool.UNDERLINE);
		sm.append(_folderIdColumn.getOldValue());
		sm.append(StringPool.UNDERLINE);
		sm.append(title);

		if (Validator.isNotNull(extension)) {
			sm.append(StringPool.PERIOD);
			sm.append(extension);
		}

		return sm.toString();
	}

	private UpgradeColumn _groupIdColumn;
	private UpgradeColumn _folderIdColumn;
	private UpgradeColumn _nameColumn;
	private int _counter = 0;
	private Set _distinctTitles;

}