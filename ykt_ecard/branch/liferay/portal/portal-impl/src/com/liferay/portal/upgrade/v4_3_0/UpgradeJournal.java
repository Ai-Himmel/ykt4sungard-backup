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

import com.liferay.portal.model.impl.CompanyImpl;
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
import com.liferay.portal.upgrade.v4_3_0.util.JournalArticleContentUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalArticlePKUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalArticleResourcePrimKeyUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalStructurePKUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalStructureXSDUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalTemplatePKUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalTemplateSmallImageIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.JournalTemplateXSLUpgradeColumnImpl;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.journal.model.impl.JournalArticleImpl;
import com.liferay.portlet.journal.model.impl.JournalStructureImpl;
import com.liferay.portlet.journal.model.impl.JournalTemplateImpl;

import java.sql.Types;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeJournal.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeJournal extends UpgradeProcess {

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

		// JournalArticle

		UpgradeColumn upgradeCompanyIdColumn = new SwapUpgradeColumnImpl(
			"companyId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getCompanyIdMapper());

		UpgradeColumn upgradeGroupIdColumn = new SwapUpgradeColumnImpl(
			"groupId", AvailableMappersUtil.getGroupIdMapper());

		UpgradeColumn upgradeUserIdColumn = new SwapUpgradeColumnImpl(
			"userId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		UpgradeColumn upgradeApprovedByUserIdColumn = new SwapUpgradeColumnImpl(
			"approvedByUserId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		JournalArticlePKUpgradeColumnImpl upgradeArticlePKColumn =
			new JournalArticlePKUpgradeColumnImpl(
				upgradeCompanyIdColumn, upgradeGroupIdColumn);

		UpgradeColumn upgradeArticleResourcePrimKeyColumn =
			new JournalArticleResourcePrimKeyUpgradeColumnImpl(
				upgradeArticlePKColumn);

		UpgradeColumn upgradeArticleIdColumn =
			new TempUpgradeColumnImpl("articleId");

		UpgradeColumn upgradeVersionColumn =
			new TempUpgradeColumnImpl("version", new Integer(Types.DOUBLE));

		UpgradeColumn upgradeStructureIdColumn =
			new TempUpgradeColumnImpl("structureId");

		UpgradeColumn upgradeContentColumn =
			new JournalArticleContentUpgradeColumnImpl(
				upgradeCompanyIdColumn, upgradeGroupIdColumn,
				upgradeArticleIdColumn, upgradeVersionColumn,
				upgradeStructureIdColumn,
				AvailableMappersUtil.getImageIdMapper());

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			JournalArticleImpl.TABLE_NAME, JournalArticleImpl.TABLE_COLUMNS,
			upgradeCompanyIdColumn, upgradeGroupIdColumn, upgradeUserIdColumn,
			upgradeApprovedByUserIdColumn, upgradeArticlePKColumn,
			upgradeArticleResourcePrimKeyColumn, upgradeArticleIdColumn,
			upgradeVersionColumn, upgradeStructureIdColumn,
			upgradeContentColumn);

		upgradeTable.setCreateSQL(JournalArticleImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper articleIdMapper = new DefaultPKMapper(
			upgradeArticlePKColumn.getValueMapper());

		AvailableMappersUtil.setJournalArticleIdMapper(articleIdMapper);

		// JournalStructure

		PKUpgradeColumnImpl upgradeStructurePKColumn =
			new JournalStructurePKUpgradeColumnImpl(
				upgradeCompanyIdColumn, upgradeGroupIdColumn);

		UpgradeColumn upgradeXSDColumn =
			new JournalStructureXSDUpgradeColumnImpl();

		upgradeTable = new DefaultUpgradeTableImpl(
			JournalStructureImpl.TABLE_NAME, JournalStructureImpl.TABLE_COLUMNS,
			upgradeCompanyIdColumn, upgradeGroupIdColumn,
			upgradeStructurePKColumn, upgradeUserIdColumn, upgradeXSDColumn);

		upgradeTable.setCreateSQL(JournalStructureImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper structureIdMapper = new DefaultPKMapper(
			upgradeStructurePKColumn.getValueMapper());

		AvailableMappersUtil.setJournalStructureIdMapper(structureIdMapper);

		// JournalTemplate

		PKUpgradeColumnImpl upgradeTemplatePKColumn =
			new JournalTemplatePKUpgradeColumnImpl(
				upgradeCompanyIdColumn, upgradeGroupIdColumn);

		UpgradeColumn upgradeTemplateIdColumn =
			new TempUpgradeColumnImpl("templateId");

		UpgradeColumn upgradeXSLColumn =
			new JournalTemplateXSLUpgradeColumnImpl(upgradeTemplateIdColumn);

		UpgradeColumn upgradeSmallImageIdColumn =
			new JournalTemplateSmallImageIdUpgradeColumnImpl(
				upgradeCompanyIdColumn, upgradeGroupIdColumn,
				upgradeTemplatePKColumn,
				AvailableMappersUtil.getImageIdMapper());

		upgradeTable = new DefaultUpgradeTableImpl(
			JournalTemplateImpl.TABLE_NAME, JournalTemplateImpl.TABLE_COLUMNS,
			upgradeCompanyIdColumn, upgradeGroupIdColumn,
			upgradeTemplatePKColumn, upgradeUserIdColumn,
			upgradeTemplateIdColumn, upgradeXSLColumn,
			upgradeSmallImageIdColumn);

		upgradeTable.setCreateSQL(JournalTemplateImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper templateIdMapper = new DefaultPKMapper(
			upgradeTemplatePKColumn.getValueMapper());

		AvailableMappersUtil.setJournalTemplateIdMapper(templateIdMapper);

		// JournalContentSearch

		PropsUtil.set(
			CompanyImpl.SYSTEM,
			PropsUtil.JOURNAL_SYNC_CONTENT_SEARCH_ON_STARTUP, "true");
	}

	private static Log _log = LogFactory.getLog(UpgradeJournal.class);

}