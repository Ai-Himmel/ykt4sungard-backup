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
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.LayoutSetImpl;
import com.liferay.portal.model.impl.OrgGroupPermissionImpl;
import com.liferay.portal.model.impl.OrgGroupRoleImpl;
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
import com.liferay.portal.upgrade.v4_3_0.util.ClassNameIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.ClassPKContainer;
import com.liferay.portal.upgrade.v4_3_0.util.ClassPKUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.GroupNameUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.LayoutOwnerIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.LayoutPlidUpgradeColumnImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.CollectionFactory;

import java.sql.Types;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeGroup.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeGroup extends UpgradeProcess {

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

		// Group_

		PKUpgradeColumnImpl upgradePKColumn = new PKUpgradeColumnImpl(
			"groupId", true);

		ClassNameIdUpgradeColumnImpl classNameIdColumn =
			new ClassNameIdUpgradeColumnImpl();

		Map classPKContainers = CollectionFactory.getHashMap();

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(Organization.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getOrganizationIdMapper(), true));

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(User.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getUserIdMapper(), false));

		classPKContainers.put(
			new Long(PortalUtil.getClassNameId(UserGroup.class.getName())),
			new ClassPKContainer(
				AvailableMappersUtil.getUserGroupIdMapper(), true));

		UpgradeColumn upgradeClassPKColumn = new ClassPKUpgradeColumnImpl(
			classNameIdColumn, classPKContainers);

		UpgradeColumn upgradeNameColumn = new GroupNameUpgradeColumnImpl(
			upgradePKColumn, upgradeClassPKColumn);

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			GroupImpl.TABLE_NAME, GroupImpl.TABLE_COLUMNS, upgradePKColumn,
			classNameIdColumn, upgradeClassPKColumn, upgradeNameColumn);

		upgradeTable.setCreateSQL(GroupImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper groupIdMapper = new DefaultPKMapper(
			upgradePKColumn.getValueMapper());

		AvailableMappersUtil.setGroupIdMapper(groupIdMapper);

		UpgradeColumn upgradeGroupIdColumn = new SwapUpgradeColumnImpl(
			"groupId", groupIdMapper);

		// Layout

		UpgradeColumn upgradeLayoutOwnerIdColumn =
			new TempUpgradeColumnImpl("ownerId");

		LayoutOwnerIdUpgradeColumnImpl upgradeLayoutOwnerIdGroupIdColumn =
			new LayoutOwnerIdUpgradeColumnImpl(
				"groupId", upgradeLayoutOwnerIdColumn, groupIdMapper);

		LayoutOwnerIdUpgradeColumnImpl upgradeLayoutOwnerIdPrivateLayoutColumn =
			new LayoutOwnerIdUpgradeColumnImpl(
				"privateLayout", upgradeLayoutOwnerIdColumn, groupIdMapper);

		UpgradeColumn upgradeLayoutIdColumn =
			new TempUpgradeColumnImpl("layoutId");

		PKUpgradeColumnImpl upgradeLayoutPlidColumn =
			new LayoutPlidUpgradeColumnImpl(
				upgradeLayoutOwnerIdColumn, upgradeLayoutOwnerIdGroupIdColumn,
				upgradeLayoutOwnerIdPrivateLayoutColumn, upgradeLayoutIdColumn);

		Object[][] layoutColumns1 = {{"ownerId", new Integer(Types.VARCHAR)}};
		Object[][] layoutColumns2 =
			(Object[][])LayoutImpl.TABLE_COLUMNS.clone();

		Object[][] layoutColumns = ArrayUtil.append(
			layoutColumns1, layoutColumns2);

		upgradeTable = new DefaultUpgradeTableImpl(
			LayoutImpl.TABLE_NAME, layoutColumns, upgradeLayoutOwnerIdColumn,
			upgradeLayoutOwnerIdGroupIdColumn,
			upgradeLayoutOwnerIdPrivateLayoutColumn, upgradeLayoutIdColumn,
			upgradeLayoutPlidColumn);

		String createSQL = LayoutImpl.TABLE_SQL_CREATE;

		createSQL =
			createSQL.substring(0, createSQL.length() - 1) +
				",ownerId VARCHAR(75) null)";

		upgradeTable.setCreateSQL(createSQL);

		upgradeTable.updateTable();

		ValueMapper layoutPlidMapper = upgradeLayoutPlidColumn.getValueMapper();

		AvailableMappersUtil.setLayoutPlidMapper(layoutPlidMapper);

		// LayoutSet

		Object[][] layoutSetColumns1 =
			{{"ownerId", new Integer(Types.VARCHAR)}};
		Object[][] layoutSetColumns2 =
			(Object[][])LayoutSetImpl.TABLE_COLUMNS.clone();

		Object[][] layoutSetColumns = ArrayUtil.append(
			layoutSetColumns1, layoutSetColumns2);

		upgradeTable = new DefaultUpgradeTableImpl(
			LayoutSetImpl.TABLE_NAME, layoutSetColumns,
			new PKUpgradeColumnImpl("layoutSetId", false),
			upgradeGroupIdColumn);

		createSQL = LayoutSetImpl.TABLE_SQL_CREATE;

		createSQL =
			createSQL.substring(0, createSQL.length() - 1) +
				",ownerId VARCHAR(75) null)";

		upgradeTable.setCreateSQL(createSQL);

		upgradeTable.updateTable();

		// OrgGroupPermission

		upgradeTable = new DefaultUpgradeTableImpl(
			OrgGroupPermissionImpl.TABLE_NAME,
			OrgGroupPermissionImpl.TABLE_COLUMNS, upgradeGroupIdColumn);

		upgradeTable.setCreateSQL(OrgGroupPermissionImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// OrgGroupRole

		upgradeTable = new DefaultUpgradeTableImpl(
			OrgGroupRoleImpl.TABLE_NAME, OrgGroupRoleImpl.TABLE_COLUMNS,
			upgradeGroupIdColumn);

		upgradeTable.setCreateSQL(OrgGroupRoleImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// Schema

		runSQL(_UPGRADE_SCHEMA);
	}

	private static final String[] _UPGRADE_SCHEMA = {
		"alter table Layout drop column ownerId",

		"alter table LayoutSet drop column ownerId"
	};

	private static Log _log = LogFactory.getLog(UpgradeGroup.class);

}