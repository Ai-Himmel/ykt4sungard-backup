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

import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.DefaultPKMapper;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.PKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.SwapUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.TempUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.v4_3_0.util.AvailableMappersUtil;
import com.liferay.portal.upgrade.v4_3_0.util.DLFileEntryIdUpgradeColumnImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFileEntryImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFileRankImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFileShortcutImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFileVersionImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;

import java.sql.Types;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeDocumentLibrary.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
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

		UpgradeColumn upgradeCompanyIdColumn = new SwapUpgradeColumnImpl(
			"companyId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getCompanyIdMapper());

		UpgradeColumn upgradeGroupIdColumn = new SwapUpgradeColumnImpl(
			"groupId", AvailableMappersUtil.getGroupIdMapper());

		UpgradeColumn upgradeUserIdColumn = new SwapUpgradeColumnImpl(
			"userId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		PKUpgradeColumnImpl upgradePKColumn = new PKUpgradeColumnImpl(
			"folderId", true);

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			DLFolderImpl.TABLE_NAME, DLFolderImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeGroupIdColumn, upgradeUserIdColumn);

		upgradeTable.setCreateSQL(DLFolderImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper folderIdMapper = new DefaultPKMapper(
			upgradePKColumn.getValueMapper());

		AvailableMappersUtil.setDLFolderIdMapper(folderIdMapper);

		UpgradeColumn upgradeParentFolderIdColumn = new SwapUpgradeColumnImpl(
			"parentFolderId", folderIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			DLFolderImpl.TABLE_NAME, DLFolderImpl.TABLE_COLUMNS,
			upgradeParentFolderIdColumn);

		upgradeTable.updateTable();

		UpgradeColumn upgradeFolderIdColumn = new SwapUpgradeColumnImpl(
			"folderId", folderIdMapper);

		UpgradeColumn upgradeToFolderIdColumn = new SwapUpgradeColumnImpl(
			"toFolderId", folderIdMapper);

		// DLFileEntry

		UpgradeColumn upgradeNameColumn = new TempUpgradeColumnImpl("name");

		PKUpgradeColumnImpl fileEntryIdColumn =
			new DLFileEntryIdUpgradeColumnImpl(
				upgradeCompanyIdColumn, upgradeFolderIdColumn,
				upgradeNameColumn);

		UpgradeColumn upgradeVersionUserIdColumn = new SwapUpgradeColumnImpl(
			"versionUserId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		upgradeTable = new DefaultUpgradeTableImpl(
			DLFileEntryImpl.TABLE_NAME, DLFileEntryImpl.TABLE_COLUMNS,
			upgradeCompanyIdColumn, upgradeFolderIdColumn, upgradeNameColumn,
			fileEntryIdColumn, upgradeUserIdColumn, upgradeVersionUserIdColumn);

		upgradeTable.setCreateSQL(DLFileEntryImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper fileEntryIdMapper = fileEntryIdColumn.getValueMapper();

		AvailableMappersUtil.setDLFileEntryIdMapper(fileEntryIdMapper);

		// DLFileRank

		upgradeTable = new DefaultUpgradeTableImpl(
			DLFileRankImpl.TABLE_NAME, DLFileRankImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("fileRankId", false),
			upgradeUserIdColumn, upgradeFolderIdColumn);

		upgradeTable.setCreateSQL(DLFileRankImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// DLFileShortcut

		upgradePKColumn = new PKUpgradeColumnImpl("fileShortcutId", true);

		upgradeTable = new DefaultUpgradeTableImpl(
			DLFileShortcutImpl.TABLE_NAME, DLFileShortcutImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeUserIdColumn, upgradeFolderIdColumn,
			upgradeToFolderIdColumn);

		upgradeTable.setCreateSQL(DLFileShortcutImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper fileShortcutIdMapper = upgradePKColumn.getValueMapper();

		AvailableMappersUtil.setDLFileShortcutIdMapper(fileShortcutIdMapper);

		// DLFileVersion

		upgradeTable = new DefaultUpgradeTableImpl(
			DLFileVersionImpl.TABLE_NAME, DLFileVersionImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("fileVersionId", false),
			upgradeUserIdColumn, upgradeFolderIdColumn);

		upgradeTable.setCreateSQL(DLFileVersionImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();
	}

	private static Log _log = LogFactory.getLog(UpgradeDocumentLibrary.class);

}