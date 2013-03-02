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

import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Location;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.TempUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.v4_3_0.util.AvailableMappersUtil;
import com.liferay.portal.upgrade.v4_3_0.util.ClassPKContainer;
import com.liferay.portal.upgrade.v4_3_0.util.MBMessageIdMapper;
import com.liferay.portal.upgrade.v4_3_0.util.ResourceCodeIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.ResourcePrimKeyUpgradeColumnImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFileShortcut;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.polls.model.PollsQuestion;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.util.CollectionFactory;

import java.sql.Types;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeResource.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeResource extends UpgradeProcess {

	public void upgrade() throws UpgradeException {
		_log.info("Upgrading");

		try {
			doUpgrade();
		}
		catch (Exception e) {
			throw new UpgradeException(e);
		}
	}

	protected Map getClassPKContainers() {
		Map classPKContainers = CollectionFactory.getHashMap();

		// BlogsEntry

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(BlogsEntry.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getBlogsEntryIdMapper(), true));

		// BookmarksEntry

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(BookmarksEntry.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getBookmarksEntryIdMapper(), true));

		// BookmarksFolder

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(
				BookmarksFolder.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getBookmarksFolderIdMapper(), true));

		// CalEvent

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(CalEvent.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getCalEventIdMapper(), true));

		// DLFileEntry

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(DLFileEntry.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getDLFileEntryIdMapper(), false));

		// DLFileShortcut

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(DLFileShortcut.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getDLFileShortcutIdMapper(), true));

		// DLFolder

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(DLFolder.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getDLFolderIdMapper(), true));

		// Group

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(Group.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getGroupIdMapper(), true));

		// IGFolder

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(IGFolder.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getIGFolderIdMapper(), true));

		// IGImage

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(IGImage.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getIGImageIdMapper(), false));

		// JournalArticle

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(JournalArticle.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getJournalArticleIdMapper(), false));

		// JournalStructure

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(
				JournalStructure.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getJournalStructureIdMapper(), false));

		// JournalTemplate

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(
				JournalTemplate.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getJournalTemplateIdMapper(), false));

		// Layout

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(Layout.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getLayoutPlidMapper(), false));

		// Location

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(Location.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getOrganizationIdMapper(), true));

		// MBCategory

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(MBCategory.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getMBCategoryIdMapper(), true));

		// MBMessage

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(MBMessage.class.getName())),
			new ClassPKContainer(
				new MBMessageIdMapper(
					AvailableMappersUtil.getMBMessageIdMapper()),
				false));

		// Organization

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(Organization.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getOrganizationIdMapper(), true));

		// PollsQuestion

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(PollsQuestion.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getPollsQuestionIdMapper(), true));

		// Role

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(Role.class.getName())),
			new ClassPKContainer(AvailableMappersUtil.getRoleIdMapper(), true));

		// ShoppingCategory

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(
				ShoppingCategory.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getShoppingCategoryIdMapper(), true));

		// ShoppingItem

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(ShoppingItem.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getShoppingItemIdMapper(), true));

		// User

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(User.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getUserIdMapper(), false));

		// UserGroup

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(UserGroup.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getUserGroupIdMapper(), true));

		// WikiNode

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(WikiNode.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getWikiNodeIdMapper(), true));

		// WikiPage

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(WikiPage.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getWikiPageIdMapper(), false));

		return classPKContainers;
	}

	protected void doUpgrade() throws Exception {

		// Resource

		Object[][] resourceColumns1 = {
			{"companyId", new Integer(Types.BIGINT)},
			{"name", new Integer(Types.VARCHAR)},
			{"scope", new Integer(Types.VARCHAR)}
		};
		Object[][] resourceColumns2 =
			(Object[][])ResourceImpl.TABLE_COLUMNS.clone();

		Object[][] resourceColumns = ArrayUtil.append(
			resourceColumns1, resourceColumns2);

		UpgradeColumn companyIdColumn = new TempUpgradeColumnImpl("companyId");

		UpgradeColumn nameColumn = new TempUpgradeColumnImpl("name");

		UpgradeColumn scopeColumn = new TempUpgradeColumnImpl("scope");

		ResourceCodeIdUpgradeColumnImpl codeIdColumn =
			new ResourceCodeIdUpgradeColumnImpl(
				companyIdColumn, nameColumn, scopeColumn);

		UpgradeColumn primKeyColumn = new ResourcePrimKeyUpgradeColumnImpl(
			nameColumn, codeIdColumn, AvailableMappersUtil.getGroupIdMapper(),
			getClassPKContainers(), AvailableMappersUtil.getLayoutPlidMapper());

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			ResourceImpl.TABLE_NAME, resourceColumns, companyIdColumn,
			nameColumn, scopeColumn, codeIdColumn, primKeyColumn);

		String createSQL = ResourceImpl.TABLE_SQL_CREATE;

		createSQL =
			createSQL.substring(0, createSQL.length() - 1) +
				",companyId VARCHAR(75) null, name VARCHAR(75) null, " +
					"scope VARCHAR(75) null)";

		upgradeTable.setCreateSQL(createSQL);

		upgradeTable.updateTable();

		// Schema

		runSQL(_UPGRADE_SCHEMA);
	}

	private static final String[] _UPGRADE_SCHEMA = {
		"alter table Resource_ drop column companyId",
		"alter table Resource_ drop column name",
		"alter table Resource_ drop column scope"
	};

	private static Log _log = LogFactory.getLog(UpgradeResource.class);

}