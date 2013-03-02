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

import com.liferay.counter.service.CounterLocalServiceUtil;
import com.liferay.documentlibrary.service.DLLocalServiceUtil;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.util.ValueMapperFactory;
import com.liferay.portal.upgrade.v4_3_0.util.AvailableMappersUtil;
import com.liferay.portal.upgrade.v4_3_0.util.WebIdUtil;
import com.liferay.portal.util.PortletKeys;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeCompany.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeCompany extends UpgradeProcess {

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
		ValueMapper companyIdMapper = ValueMapperFactory.getValueMapper();

		AvailableMappersUtil.setCompanyIdMapper(companyIdMapper);

		String[] webIds = WebIdUtil.getWebIds();

		long[] companyIds = new long[webIds.length];

		for (int i = 0; i < webIds.length; i++) {
			String webId = webIds[i];

			long companyId = upgradeWebId(webId);

			companyIds[i] = companyId;

			companyIdMapper.mapValue(webId, new Long(companyId));
		}

		// Delay checking of Lucene and Document Library. See LEP-3492.

		for (int i = 0; i < companyIds.length; i++) {
			long companyId = companyIds[i];

			LuceneUtil.checkLuceneDir(companyId);

			DLLocalServiceUtil.checkRoot(companyId);
		}

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			CompanyImpl.TABLE_NAME, CompanyImpl.TABLE_COLUMNS);

		upgradeTable.setCreateSQL(CompanyImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		runSQL(
			"update PortletPreferences set ownerId = '0', ownerType = " +
				PortletKeys.PREFS_OWNER_TYPE_COMPANY +
					" where ownerId = 'COMPANY.LIFERAY_PORTAL'");
	}

	protected String getUpdateSQL(
		String tableName, long companyId, String webId) {

		String updateSQL =
			"update " + tableName + " set companyId = '" + companyId +
				"' where companyId = '" + webId + "'";

		if (_log.isDebugEnabled()) {
			_log.debug(updateSQL);
		}

		return updateSQL;
	}

	protected long upgradeWebId(String webId) throws Exception {
		long companyId = CounterLocalServiceUtil.increment();

		for (int j = 0; j < _TABLES.length; j++) {
			runSQL(getUpdateSQL(_TABLES[j], companyId, webId));
		}

		long accountId = CounterLocalServiceUtil.increment();

		runSQL(
			"update Account_ set accountId = '" + accountId +
				"', companyId = '" + companyId + "' where accountId = '" +
					webId + "'");

		runSQL(
			"update Address set classPK = '" + accountId +
				"' where classNameId = '" + Account.class.getName() +
					"' and classPK = '" + webId + "'");

		ValueMapper imageIdMapper = AvailableMappersUtil.getImageIdMapper();

		Long logoId = (Long)imageIdMapper.getNewValue(webId);

		runSQL(
			"update Company set accountId = " + accountId + ", logoId = " +
				logoId.longValue() + " where webId = '" + webId + "'");

		runSQL(
			"update Contact_ set companyId = '" + companyId +
				"', accountId = '" + accountId + "' where contactId = '" +
					webId + ".default'");

		runSQL(
			"update Contact_ set accountId = '" + accountId +
				"' where accountId = '" + webId + "'");

		runSQL(
			"update EmailAddress set classPK = '" + accountId +
				"' where classNameId = '" + Account.class.getName() +
					"' and classPK = '" + webId + "'");

		runSQL(
			"update Phone set classPK = '" + accountId +
				"' where classNameId = '" + Account.class.getName() +
					"' and classPK = '" + webId + "'");

		runSQL(
			"update Resource_ set primKey = '" + companyId +
				"' where scope = 'company' and primKey = '" + webId + "'");

		runSQL(
			"update User_ set companyId = '" + companyId +
				"', defaultUser = TRUE where userId = '" + webId + ".default'");

		runSQL(
			"update Website set classPK = '" + accountId +
				"' where classNameId = '" + Account.class.getName() +
					"' and classPK = '" + webId + "'");

		return companyId;
	}

	private static final String[] _TABLES = new String[] {
		"Account_", "Address", "BlogsEntry", "BookmarksEntry",
		"BookmarksFolder", "CalEvent", "Company", "Contact_", "DLFileRank",
		"DLFileShortcut", "DLFileVersion", "DLFolder", "EmailAddress", "Group_",
		"IGFolder", "Layout", "LayoutSet", "MBCategory", "Organization_",
		"Permission_", "Phone", "PollsQuestion", "Portlet", "RatingsEntry",
		"Resource_", "Role_", "ShoppingCart", "ShoppingCategory",
		"ShoppingCoupon", "ShoppingItem", "ShoppingOrder", "Subscription",
		"UserGroup", "User_", "Website", "WikiNode", "WikiPage"
	};

	private static Log _log = LogFactory.getLog(UpgradeCompany.class);

}