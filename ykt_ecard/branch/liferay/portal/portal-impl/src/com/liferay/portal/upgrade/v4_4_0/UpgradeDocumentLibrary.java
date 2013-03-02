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

package com.liferay.portal.upgrade.v4_4_0;

import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.TempUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.v4_4_0.util.DLFileEntryTitleColumnImpl;
import com.liferay.portal.upgrade.v4_4_0.util.DLFolderNameColumnImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFileEntryModelImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderModelImpl;

import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeDocumentLibrary.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class UpgradeDocumentLibrary extends UpgradeProcess {

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

		// DLFolder

		UpgradeColumn groupIdColumn = new TempUpgradeColumnImpl("groupId");

		UpgradeColumn parentFolderIdColumn = new TempUpgradeColumnImpl(
			"parentFolderId");

		DLFolderNameColumnImpl dlFolderNameColumn = new DLFolderNameColumnImpl(
			groupIdColumn, parentFolderIdColumn);

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			DLFolderModelImpl.TABLE_NAME, DLFolderModelImpl.TABLE_COLUMNS,
			groupIdColumn, parentFolderIdColumn, dlFolderNameColumn);

		upgradeTable.updateTable();

		Set distinctNames = dlFolderNameColumn.getDistintNames();

		// DLFileEntry

		UpgradeColumn folderIdColumn = new TempUpgradeColumnImpl("folderId");

		UpgradeColumn nameColumn = new TempUpgradeColumnImpl("name");

		BaseUpgradeColumnImpl dlFileEntryTitleColumn =
			new DLFileEntryTitleColumnImpl(
				groupIdColumn, folderIdColumn, nameColumn, distinctNames);

		upgradeTable = new DefaultUpgradeTableImpl(
			DLFileEntryModelImpl.TABLE_NAME, DLFileEntryModelImpl.TABLE_COLUMNS,
			folderIdColumn, nameColumn, dlFileEntryTitleColumn);

		upgradeTable.updateTable();
	}

	private static Log _log = LogFactory.getLog(UpgradeDocumentLibrary.class);

}