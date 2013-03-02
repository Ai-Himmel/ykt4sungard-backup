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

import com.liferay.portal.model.impl.OrgGroupPermissionImpl;
import com.liferay.portal.model.impl.OrgLaborImpl;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.DefaultPKMapper;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.PKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.SwapUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.v4_3_0.util.AvailableMappersUtil;
import com.liferay.portal.upgrade.v4_3_0.util.ValueMapperUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeOrganization.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeOrganization extends UpgradeProcess {

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

		// Organization

		PKUpgradeColumnImpl upgradePKColumn = new PKUpgradeColumnImpl(
			"organizationId", true);

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			OrganizationImpl.TABLE_NAME, OrganizationImpl.TABLE_COLUMNS,
			upgradePKColumn);

		upgradeTable.setCreateSQL(OrganizationImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper organizationIdMapper = new DefaultPKMapper(
			upgradePKColumn.getValueMapper());

		AvailableMappersUtil.setOrganizationIdMapper(organizationIdMapper);

		UpgradeColumn upgradeParentOrganizationIdColumn =
			new SwapUpgradeColumnImpl(
				"parentOrganizationId", organizationIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			OrganizationImpl.TABLE_NAME, OrganizationImpl.TABLE_COLUMNS,
			upgradeParentOrganizationIdColumn);

		upgradeTable.updateTable();

		UpgradeColumn upgradeOrganizationIdColumn = new SwapUpgradeColumnImpl(
			"organizationId", organizationIdMapper);

		// OrgGroupPermission

		upgradeTable = new DefaultUpgradeTableImpl(
			OrgGroupPermissionImpl.TABLE_NAME,
			OrgGroupPermissionImpl.TABLE_COLUMNS, upgradeOrganizationIdColumn);

		upgradeTable.setCreateSQL(OrgGroupPermissionImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// OrgLabor

		upgradePKColumn = new PKUpgradeColumnImpl("orgLaborId", true);

		upgradeTable = new DefaultUpgradeTableImpl(
			OrgLaborImpl.TABLE_NAME, OrgLaborImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeOrganizationIdColumn);

		upgradeTable.setCreateSQL(OrgLaborImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapperUtil.persist(
			upgradePKColumn.getValueMapper(), "org-labor-id");
	}

	private static Log _log = LogFactory.getLog(UpgradeOrganization.class);

}