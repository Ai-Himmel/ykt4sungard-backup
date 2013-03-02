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

import com.liferay.portal.kernel.uuid.PortalUUIDUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.util.dao.DataAccess;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeUUID.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeUUID extends UpgradeProcess {

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
		upgradeTable("BlogsEntry", "entryId");
		upgradeTable("BookmarksEntry", "entryId");
		upgradeTable("BookmarksFolder", "folderId");
		upgradeTable("DLFileEntry", "fileEntryId");
		upgradeTable("DLFileShortcut", "fileShortcutId");
		upgradeTable("DLFolder", "folderId");
		upgradeTable("CalEvent", "eventId");
		upgradeTable("IGFolder", "folderId");
		upgradeTable("IGImage", "imageId");
		upgradeTable("JournalArticle", "id_");
		upgradeTable("JournalStructure", "id_");
		upgradeTable("JournalTemplate", "id_");
		upgradeTable("MBCategory", "categoryId");
		upgradeTable("MBMessage", "messageId");
		upgradeTable("PollsChoice", "choiceId");
		upgradeTable("PollsQuestion", "questionId");
		upgradeTable("User_", "userId");
		upgradeTable("WikiNode", "nodeId");
		upgradeTable("WikiPage", "pageId");
	}

	protected void upgradeTable(String tableName, String pkColName)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"SELECT " + pkColName + " FROM " + tableName +
					" WHERE uuid_ IS NULL or uuid_ = ''");

			rs = ps.executeQuery();

			while (rs.next()) {
				long pkColValue = rs.getLong(pkColName);

				String uuid = PortalUUIDUtil.generate();

				ps = con.prepareStatement(
					"UPDATE " + tableName + " SET uuid_ = '" + uuid +
						"' WHERE " + pkColName + " = " + pkColValue);

				ps.executeUpdate();

				ps.close();
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	private static Log _log = LogFactory.getLog(UpgradeUUID.class);

}