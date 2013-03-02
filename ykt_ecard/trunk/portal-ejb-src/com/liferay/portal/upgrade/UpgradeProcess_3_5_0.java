/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.upgrade;

import com.liferay.portal.SystemException;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.GlobalPool;
import com.liferay.portal.service.spring.AddressLocalServiceUtil;
import com.liferay.portal.service.spring.ImageLocalServiceUtil;
import com.liferay.portal.service.spring.PropertiesServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.PropertiesUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.dao.DataAccess;
import com.liferay.util.lang.FastStringBuffer;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

import java.util.List;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeProcess_3_5_0.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class UpgradeProcess_3_5_0 implements UpgradeProcess {

	public void upgrade(int buildNumber) throws UpgradeException {

		// Version 3.2.0 has build number 1831

		if (buildNumber > 1831) {
			return;
		}

		_log.info("Upgrading");

		try {

			// Companies reference Accounts

			_updateCompany();

			// Users reference Contacts and no longer have skin images

			_updateUser();

			// Layouts can have children

			_updateLayout();
		}
		/*catch (PortalException pe) {
			throw new UpgradeException(pe.getCause());
		}*/
		catch (SystemException se) {
			se.printStackTrace();

			_log.warn(se.getMessage());
			//throw new UpgradeException(se.getCause());
		}
	}

	private String _getCompanyIdByGroupId(String groupId)
		throws SystemException {

		String companyId = null;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT companyId FROM Group_ WHERE groupId = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, groupId);

			rs = ps.executeQuery();

			while (rs.next()) {
				companyId = rs.getString("companyId");
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return companyId;
	}

	private String _getCompanyIdByUserId(String userId) throws SystemException {
		String companyId = null;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT companyId FROM User_ WHERE userId = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, userId);

			rs = ps.executeQuery();

			while (rs.next()) {
				companyId = rs.getString("companyId");
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return companyId;
	}

	private void _updateCompany() throws SystemException {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT * FROM Company");

			ps = con.prepareStatement(query.toString());

			rs = ps.executeQuery();

			while (rs.next()) {
				String companyId = rs.getString("companyId");
				String name = rs.getString("name");
				String type = rs.getString("type_");
				String size = rs.getString("size_");
				String street = rs.getString("street");
				String city = rs.getString("city");
				String state = rs.getString("state");
				String zip = rs.getString("zip");
				String phone = rs.getString("phone");
				String fax = rs.getString("fax");
				String emailAddress = rs.getString("emailAddress");
				String authType = rs.getString("authType");
				boolean autoLogin = rs.getBoolean("autoLogin");
				boolean strangers = rs.getBoolean("strangers");

				/*Account account = AccountLocalServiceUtil.addCompany(
					companyId, name, type, size, emailAddress);*/

				/*AddressLocalServiceUtil.deleteAll( // not needed, remove later
					companyId, Account.class.getName(), account.getAccountId());

				AddressLocalServiceUtil.addAddress(
					account.getUserId(), Account.class.getName(),
					account.getAccountId(), StringPool.BLANK, street,
					StringPool.BLANK, city, state, zip, "USA", phone,
					fax, StringPool.BLANK, StringPool.BLANK, StringPool.BLANK);*/

				Properties propertiesObj =
					PropertiesServiceUtil.getPortalProperties(companyId);

				propertiesObj.setProperty(
					PropsUtil.COMPANY_SECURITY_AUTH_TYPE, authType);
				propertiesObj.setProperty(
					PropsUtil.COMPANY_SECURITY_AUTO_LOGIN,
					Boolean.toString(autoLogin));
				propertiesObj.setProperty(
					PropsUtil.COMPANY_SECURITY_STRANGERS,
					Boolean.toString(strangers));

				PropertiesServiceUtil.updatePortalProperties(
					companyId, propertiesObj);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	private void _updateLayout() throws SystemException {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT * FROM Layout");

			ps = con.prepareStatement(query.toString());

			rs = ps.executeQuery();

			while (rs.next()) {
				String layoutId = rs.getString("layoutId");
				String userId = rs.getString("userId");
				String parentLayoutId = rs.getString("parentLayoutId");
				String columnOrder = rs.getString("columnOrder");
				String narrow1 = rs.getString("narrow1");
				String narrow2 = rs.getString("narrow2");
				String wide = rs.getString("wide");
				String stateMax = rs.getString("stateMax");
				String stateMin = rs.getString("stateMin");
				String modeEdit = rs.getString("modeEdit");
				String modeHelp = rs.getString("modeHelp");
				String type = Layout.TYPE_PORTLET;
				int priority = 0;

				String companyId = null;

				if (Layout.isGroup(layoutId)) {
					String groupId = Layout.getGroupId(layoutId);

					companyId = _getCompanyIdByGroupId(groupId);
				}
				else {
					companyId = _getCompanyIdByUserId(userId);
				}

				parentLayoutId = GetterUtil.getString(
					parentLayoutId, Layout.DEFAULT_PARENT_LAYOUT_ID);

				Properties props = new Properties();

				props.setProperty(
					LayoutTypePortlet.COLUMN_ORDER,
					StringUtil.replace(
						GetterUtil.getString(columnOrder), "w", "w1"));
				props.setProperty(
					LayoutTypePortlet.NARROW_1, GetterUtil.getString(narrow1));
				props.setProperty(
					LayoutTypePortlet.NARROW_2, GetterUtil.getString(narrow2));
				props.setProperty(
					LayoutTypePortlet.WIDE_1, GetterUtil.getString(wide));
				props.setProperty(
					LayoutTypePortlet.STATE_MAX,
					GetterUtil.getString(stateMax));
				props.setProperty(
					LayoutTypePortlet.STATE_MIN,
					GetterUtil.getString(stateMin));
				props.setProperty(
					LayoutTypePortlet.MODE_EDIT,
					GetterUtil.getString(modeEdit));
				props.setProperty(
					LayoutTypePortlet.MODE_HELP,
					GetterUtil.getString(modeHelp));

				String typeSettings = PropertiesUtil.toString(props);

				FastStringBuffer update = new FastStringBuffer();
				update.append("UPDATE Layout SET ");
				update.append("companyId = ?, parentLayoutId = ?, type_ = ?, ");
				update.append("typeSettings = ?, priority = ? WHERE ");
				update.append("layoutId = ? AND userId = ?");

				ps = con.prepareStatement(update.toString());

				ps.setString(1, companyId);
				ps.setString(2, parentLayoutId);
				ps.setString(3, type);
				ps.setString(4, typeSettings);
				ps.setInt(5, priority);
				ps.setString(6, layoutId);
				ps.setString(7, userId);

				ps.executeUpdate();
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		GlobalPool.clear();
	}

	private void _updateUser() throws SystemException {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT * FROM User_");

			ps = con.prepareStatement(query.toString());

			rs = ps.executeQuery();

			while (rs.next()) {
				String userId = rs.getString("userId");
				String companyId = rs.getString("companyId");
				String firstName = rs.getString("firstName");
				String middleName = rs.getString("middleName");
				String lastName = rs.getString("lastName");
				String nickName = rs.getString("nickName");
				boolean male = rs.getBoolean("male");
				Timestamp birthday = rs.getTimestamp("birthday");
				String emailAddress = rs.getString("emailAddress");
				String smsId = rs.getString("smsId");
				String aimId = rs.getString("aimId");
				String icqId = rs.getString("icqId");
				String msnId = rs.getString("msnId");
				String ymId = rs.getString("ymId");
				String timeZoneId = rs.getString("timeZoneId");

				/*Contact contact = ContactLocalServiceUtil.addUser(
					userId, firstName, middleName, lastName, nickName, male,
					birthday, emailAddress, smsId, aimId, icqId, msnId, ymId,
					timeZoneId);*/

				List addresses = AddressLocalServiceUtil.getAddresses(
					companyId, User.class.getName(), userId);

				/*AddressLocalServiceUtil.deleteAll(
					companyId, User.class.getName(), userId);

				AddressLocalServiceUtil.deleteAll( // not needed, remove later
					companyId, Contact.class.getName(), contact.getContactId());

				for (int i = 0; i < addresses.size(); i++) {
					Address address = (Address)addresses.get(i);

					AddressLocalServiceUtil.addAddress(
						userId, Contact.class.getName(), contact.getContactId(),
						address.getDescription(), address.getStreet1(),
						address.getStreet2(), address.getCity(),
						address.getState(), address.getZip(),
						address.getCountry(), address.getPhone(),
						address.getFax(), address.getCell(), address.getPager(),
						address.getTollFree());
				}*/

				ImageLocalServiceUtil.deleteByImageId(userId + ".");
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	private static final Log _log =
		LogFactory.getLog(UpgradeProcess_3_5_0.class);

}