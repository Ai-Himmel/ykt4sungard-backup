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
import com.liferay.portal.upgrade.util.LazyPKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.PKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.SwapUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.v4_3_0.util.AvailableMappersUtil;
import com.liferay.portal.upgrade.v4_3_0.util.ClassNameIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.ClassPKContainer;
import com.liferay.portal.upgrade.v4_3_0.util.ClassPKUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.MBCategoryIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.MBMessageAttachmentsUpgradeColumnImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.messageboards.model.impl.MBCategoryImpl;
import com.liferay.portlet.messageboards.model.impl.MBDiscussionImpl;
import com.liferay.portlet.messageboards.model.impl.MBMessageFlagImpl;
import com.liferay.portlet.messageboards.model.impl.MBMessageImpl;
import com.liferay.portlet.messageboards.model.impl.MBStatsUserImpl;
import com.liferay.portlet.messageboards.model.impl.MBThreadImpl;
import com.liferay.util.CollectionFactory;

import java.sql.Types;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeMessageBoards.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeMessageBoards extends UpgradeProcess {

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

		// MBCategory

		UpgradeColumn upgradeCompanyIdColumn = new SwapUpgradeColumnImpl(
			"companyId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getCompanyIdMapper());

		UpgradeColumn upgradeGroupIdColumn = new SwapUpgradeColumnImpl(
			"groupId", AvailableMappersUtil.getGroupIdMapper());

		UpgradeColumn upgradeUserIdColumn = new SwapUpgradeColumnImpl(
			"userId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		PKUpgradeColumnImpl upgradePKColumn =
			new MBCategoryIdUpgradeColumnImpl();

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			MBCategoryImpl.TABLE_NAME, MBCategoryImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeGroupIdColumn, upgradeUserIdColumn);

		upgradeTable.setCreateSQL(MBCategoryImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper categoryIdMapper = new DefaultPKMapper(
			upgradePKColumn.getValueMapper());

		AvailableMappersUtil.setMBCategoryIdMapper(categoryIdMapper);

		UpgradeColumn upgradeParentCategoryIdColumn = new SwapUpgradeColumnImpl(
			"parentCategoryId", categoryIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			MBCategoryImpl.TABLE_NAME, MBCategoryImpl.TABLE_COLUMNS,
			upgradeParentCategoryIdColumn);

		upgradeTable.updateTable();

		UpgradeColumn upgradeCategoryIdColumn = new SwapUpgradeColumnImpl(
			"categoryId", categoryIdMapper);

		// MBMessage

		upgradePKColumn = new PKUpgradeColumnImpl("messageId", true);

		PKUpgradeColumnImpl upgradeThreadIdPKColumn =
			new LazyPKUpgradeColumnImpl("threadId");

		UpgradeColumn upgradeAttachmentsColumn =
			new MBMessageAttachmentsUpgradeColumnImpl(
				upgradePKColumn, upgradeCompanyIdColumn,
			upgradeThreadIdPKColumn);

		upgradeTable = new DefaultUpgradeTableImpl(
			MBMessageImpl.TABLE_NAME, MBMessageImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeCompanyIdColumn, upgradeUserIdColumn,
			upgradeCategoryIdColumn, upgradeThreadIdPKColumn,
			upgradeAttachmentsColumn);

		upgradeTable.setCreateSQL(MBMessageImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper messageIdMapper = new DefaultPKMapper(
			upgradePKColumn.getValueMapper());

		AvailableMappersUtil.setMBMessageIdMapper(messageIdMapper);

		ValueMapper threadIdMapper = upgradeThreadIdPKColumn.getValueMapper();

		AvailableMappersUtil.setMBThreadIdMapper(threadIdMapper);

		UpgradeColumn upgradeParentMessageIdColumn = new SwapUpgradeColumnImpl(
			"parentMessageId", messageIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			MBMessageImpl.TABLE_NAME, MBMessageImpl.TABLE_COLUMNS,
			upgradeParentMessageIdColumn);

		upgradeTable.updateTable();

		UpgradeColumn upgradeMessageIdColumn = new SwapUpgradeColumnImpl(
			"messageId", messageIdMapper);

		UpgradeColumn upgradeRootMessageIdColumn = new SwapUpgradeColumnImpl(
			"rootMessageId", messageIdMapper);

		// MBMessageFlag

		upgradePKColumn = new PKUpgradeColumnImpl("messageFlagId", true);

		upgradeTable = new DefaultUpgradeTableImpl(
			MBMessageFlagImpl.TABLE_NAME, MBMessageFlagImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeUserIdColumn, upgradeMessageIdColumn);

		upgradeTable.setCreateSQL(MBMessageFlagImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// MBStatsUser

		upgradeTable = new DefaultUpgradeTableImpl(
			MBStatsUserImpl.TABLE_NAME, MBStatsUserImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("statsUserId", false),
			upgradeGroupIdColumn, upgradeUserIdColumn);

		upgradeTable.setCreateSQL(MBStatsUserImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// MBThread

		UpgradeColumn upgradeThreadIdColumn = new SwapUpgradeColumnImpl(
			"threadId", threadIdMapper);

		UpgradeColumn upgradeLastPostByUserIdColumn = new SwapUpgradeColumnImpl(
			"lastPostByUserId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		upgradeTable = new DefaultUpgradeTableImpl(
			MBThreadImpl.TABLE_NAME, MBThreadImpl.TABLE_COLUMNS,
			upgradeThreadIdColumn, upgradeCategoryIdColumn,
			upgradeRootMessageIdColumn, upgradeLastPostByUserIdColumn);

		upgradeTable.setCreateSQL(MBThreadImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// MBDiscussion

		ClassNameIdUpgradeColumnImpl classNameIdColumn =
			new ClassNameIdUpgradeColumnImpl();

		Map classPKContainers = CollectionFactory.getHashMap();

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(BlogsEntry.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getBlogsEntryIdMapper(), true));

		UpgradeColumn upgradeClassPKColumn = new ClassPKUpgradeColumnImpl(
			classNameIdColumn, classPKContainers);

		upgradeTable = new DefaultUpgradeTableImpl(
			MBDiscussionImpl.TABLE_NAME, MBDiscussionImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("discussionId", false),
			classNameIdColumn, upgradeClassPKColumn, upgradeThreadIdColumn);

		upgradeTable.setCreateSQL(MBDiscussionImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();
	}

	private static Log _log = LogFactory.getLog(UpgradeMessageBoards.class);

}