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

package com.liferay.portal.upgrade.v4_3_5;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.impl.PortletImpl;
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
 * <a href="UpgradePortletId.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradePortletId extends UpgradeProcess {

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

		// This is only tested to work on instanceable portlets

		for (int i = 0; i < _PORTLET_IDS.length; i++) {
			String[] portletIds = _PORTLET_IDS[i];

			String oldRootPortletId = portletIds[0];
			String newRootPortletId = portletIds[1];

			upgradePortlet(oldRootPortletId, newRootPortletId);
			upgradeResource(oldRootPortletId, newRootPortletId);
			upgradeResourceCode(oldRootPortletId, newRootPortletId);
		}
	}

	protected void upgradeLayout(
			long plid, String oldPortletId, String newPortletId)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"select typeSettings from Layout where plid = " + plid);

			rs = ps.executeQuery();

			while (rs.next()) {
				String typeSettings = rs.getString("typeSettings");

				String newTypeSettings = upgradeTypeSettings(
					typeSettings, oldPortletId, newPortletId);

				ps = con.prepareStatement(
					"update Layout set typeSettings = ? where plid = " +
						plid);

				ps.setString(1, newTypeSettings);

				ps.executeUpdate();

				ps.close();
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void upgradePortlet(
			String oldRootPortletId, String newRootPortletId)
		throws Exception {

		runSQL(
			"update Portlet set portletId = '" + newRootPortletId +
				"' where portletId = '" + oldRootPortletId + "'");
	}

	protected void upgradePortletPreferences(
			String oldPortletId, String newPortletId)
		throws Exception {

		runSQL(
			"update PortletPreferences set portletId = '" + newPortletId +
				"' where portletId = '" + oldPortletId + "'");
	}

	protected void upgradeResource(
			String oldRootPortletId, String newRootPortletId)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"select primKey from Resource_ where primKey like ?");

			String primKeyLike =
				"%" + PortletImpl.LAYOUT_SEPARATOR + oldRootPortletId +
					PortletImpl.INSTANCE_SEPARATOR + "%";

			ps.setString(1, primKeyLike);

			rs = ps.executeQuery();

			while (rs.next()) {
				String oldPrimKey = rs.getString("primKey");

				int pos = oldPrimKey.indexOf(PortletImpl.LAYOUT_SEPARATOR);

				long plid = GetterUtil.getLong(
					oldPrimKey.substring(0, pos));

				pos = oldPrimKey.indexOf(PortletImpl.INSTANCE_SEPARATOR);

				String instanceId = oldPrimKey.substring(
					pos + PortletImpl.INSTANCE_SEPARATOR.length());

				String newPrimKey =
					plid + PortletImpl.LAYOUT_SEPARATOR + newRootPortletId +
						PortletImpl.INSTANCE_SEPARATOR +
							instanceId;

				runSQL(
					"update Resource_ set primKey = '" + newPrimKey +
						"' where primKey = '" + oldPrimKey + "'");

				String oldPortletId =
					oldRootPortletId + PortletImpl.INSTANCE_SEPARATOR +
						instanceId;
				String newPortletId =
					newRootPortletId + PortletImpl.INSTANCE_SEPARATOR +
						instanceId;

				upgradeLayout(plid, oldPortletId, newPortletId);
				upgradePortletPreferences(oldPortletId, newPortletId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void upgradeResourceCode(
			String oldRootPortletId, String newRootPortletId)
		throws Exception {

		runSQL(
			"update ResourceCode set name = '" + newRootPortletId +
				"' where name = '" + oldRootPortletId + "'");
	}

	protected String upgradeTypeSettings(
			String typeSettings, String oldPortletId, String newPortletId)
		throws Exception {

		return StringUtil.replace(typeSettings, oldPortletId, newPortletId);
	}

	private static final String[][] _PORTLET_IDS = new String[][] {
		new String[] {
			"94",
			"google_adsense_portlet_WAR_googleadsenseportlet"
		},
		new String[] {
			"95",
			"google_gadget_portlet_WAR_googlegadgetportlet"
		},
		new String[] {
			"96",
			"google_maps_portlet_WAR_googlemapsportlet"
		},
	};

	private static Log _log = LogFactory.getLog(UpgradePortletId.class);

}