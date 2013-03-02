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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.NullSafeProperties;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.util.dao.DataAccess;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeLayout.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class UpgradeLayout extends UpgradeProcess {

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
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"select plid, typeSettings from Layout where type_ = " +
					"'link_to_layout'");

			rs = ps.executeQuery();

			while (rs.next()) {
				long plid = rs.getLong("plid");
				String typeSettings = rs.getString("typeSettings");

				String newTypeSettings = upgradeTypeSettings(typeSettings);

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

	protected String upgradeTypeSettings(String typeSettings) throws Exception {
		Properties props = new NullSafeProperties();

		PropertiesUtil.load(props, typeSettings);

		long linkToPlid = GetterUtil.getLong(props.getProperty("linkToPlid"));

		if (linkToPlid > 0) {
			Layout layout = LayoutLocalServiceUtil.getLayout(linkToPlid);

			props.remove("linkToPlid");
			props.put("groupId", String.valueOf(layout.getGroupId()));
			props.put(
				"privateLayout", String.valueOf(layout.isPrivateLayout()));
			props.put("linkToLayoutId", String.valueOf(layout.getLayoutId()));
		}

		return PropertiesUtil.toString(props);
	}

	private static Log _log = LogFactory.getLog(UpgradeLayout.class);

}