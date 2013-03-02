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

import com.liferay.portal.model.Group;
import com.liferay.portal.model.Location;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.util.dao.DataAccess;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradePermission.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradePermission extends UpgradeProcess {

	public void upgrade() throws UpgradeException {
		_log.info("Upgrading");

		try {
			doUpgrade();
		}
		catch (Exception e) {
			throw new UpgradeException(e);
		}
	}

	protected void deletePermissionByActionIdAndResourceName(
			String actionId, String resourceName)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(_GET_PERMISSION_SQL);

			ps.setString(1, actionId);
			ps.setString(2, resourceName);

			rs = ps.executeQuery();

			while (rs.next()) {
				long permissionId = rs.getLong("permissionId");

				deletePermissionByPermissionId(permissionId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void deletePermissionByPermissionId(long permissionId)
		throws Exception {

		runSQL(
			"delete from Permission_ where permissionId = " + permissionId);
		runSQL(
			"delete from Groups_Permissions where permissionId = " +
				permissionId);
		runSQL(
			"delete from Roles_Permissions where permissionId = " +
				permissionId);
		runSQL(
			"delete from Users_Permissions where permissionId = " +
				permissionId);
	}

	protected void deletePermissionByResourceId(long resourceId)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"select permissionId from Permission_ where resourceId = ?");

			ps.setLong(1, resourceId);

			rs = ps.executeQuery();

			while (rs.next()) {
				long permissionId = rs.getLong("permissionId");

				deletePermissionByPermissionId(permissionId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void deleteResource(long codeId) throws Exception {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"select resourceId from Resource_ where codeId = ?");

			ps.setLong(1, codeId);

			rs = ps.executeQuery();

			while (rs.next()) {
				long resourceId = rs.getLong("resourceId");

				deletePermissionByResourceId(resourceId);

				runSQL(
					"delete from Resource_ where resourceId = " + resourceId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void deleteResourceCode(String resourceName)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(
				"select codeId from ResourceCode where name = ?");

			ps.setString(1, resourceName);

			rs = ps.executeQuery();

			while (rs.next()) {
				long codeId = rs.getLong("codeId");

				deleteResource(codeId);

				runSQL(
					"delete from ResourceCode where name = '" + resourceName +
						"'");
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void deleteRolesPermissions(String roleName) throws Exception {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(_GET_ROLES_PERMISSIONS_SQL);

			ps.setString(1, roleName);

			rs = ps.executeQuery();

			while (rs.next()) {
				long roleId = rs.getLong("roleId");

				runSQL(
					"delete from Roles_Permissions where roleId = " + roleId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void deleteUsersPermissions(int scope) throws Exception {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(_GET_USERS_PERMISSIONS_SQL);

			ps.setLong(1, scope);

			rs = ps.executeQuery();

			while (rs.next()) {
				long permissionId = rs.getLong("permissionId");

				runSQL(
					"delete from Users_Permissions where permissionId = " +
						permissionId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	protected void doUpgrade() throws Exception {
		runSQL("delete from OrgGroupPermission");

		for (int i = 0; i < _DELETE_PERMISSIONS.length; i++) {
			Object[] permission = _DELETE_PERMISSIONS[i];

			String actionId = (String)permission[0];
			String resourceName = ((Class)permission[1]).getName();

			deletePermissionByActionIdAndResourceName(actionId, resourceName);
		}

		for (int i = 0; i < _UPDATE_PERMISSIONS.length; i++) {
			Object[] permission = _UPDATE_PERMISSIONS[i];

			String oldActionId = (String)permission[0];
			String newActionId = (String)permission[1];
			String resourceName = ((Class)permission[2]).getName();

			updatePermission(oldActionId, newActionId, resourceName);
		}

		deleteResourceCode("com.liferay.portlet.blogs.model.BlogsCategory");

		deleteRolesPermissions("Community Administrator");
		deleteRolesPermissions("Community Owner");
		deleteRolesPermissions("Organization Administrator");

		deleteUsersPermissions(ResourceImpl.SCOPE_GROUP);
	}

	protected void updatePermission(
			String oldActionId, String newActionId, String resourceName)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(_GET_PERMISSION_SQL);

			ps.setString(1, oldActionId);
			ps.setString(2, resourceName);

			rs = ps.executeQuery();

			while (rs.next()) {
				long permissionId = rs.getLong("permissionId");

				runSQL(
					"update Permission_ set actionId = '" + newActionId +
						"' where permissionId = " + permissionId);
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

	private static final String _GET_PERMISSION_SQL =
		"select Permission_.permissionId from Permission_ inner join " +
			"Resource_ on Resource_.resourceId = Permission_.resourceId " +
				"inner join ResourceCode on ResourceCode.codeId = " +
					"Resource_.codeId where Permission_.actionId = ? and " +
						"ResourceCode.name = ?";

	private static final String _GET_ROLES_PERMISSIONS_SQL =
		"select Roles_Permissions.roleId from Roles_Permissions inner join " +
			"Role_ on Role_.roleId = Roles_Permissions.roleId where " +
				"Role_.name = ?";

	private static final String _GET_USERS_PERMISSIONS_SQL =
		"select Users_Permissions.permissionId from Users_Permissions inner " +
			"join Permission_ on Permission_.permissionId = " +
				"Users_Permissions.permissionId inner join Resource_ on " +
					"Resource_.resourceId = Permission_.resourceId inner " +
						"join ResourceCode on ResourceCode.codeId = " +
							"Resource_.codeId where ResourceCode.scope = ?";

	private static Object[][] _DELETE_PERMISSIONS = new Object[][] {
		new Object[] {
			"ADMINISTRATE", Group.class
		},
		new Object[] {
			"ADD_USER", Location.class
		},
		new Object[] {
			"ADD_USER", Organization.class
		},
		new Object[] {
			"DELETE_USER", Location.class
		},
		new Object[] {
			"DELETE_USER", Organization.class
		},
		new Object[] {
			"PERMISSIONS_USER", Location.class
		},
		new Object[] {
			"PERMISSIONS_USER", Organization.class
		},
		new Object[] {
			"UPDATE_USER", Location.class
		},
		new Object[] {
			"UPDATE_USER", Organization.class
		},
		new Object[] {
			"VIEW_USER", Location.class
		},
		new Object[] {
			"VIEW_USER", Organization.class
		}
	};

	private static Object[][] _UPDATE_PERMISSIONS = new Object[][] {
		new Object[] {
			"ADD_CATEGORY", "ADD_SUBCATEGORY", MBCategory.class
		},
		new Object[] {
			"ADD_CATEGORY", "ADD_SUBCATEGORY", ShoppingCategory.class
		},
		new Object[] {
			"ADD_FOLDER", "ADD_SUBFOLDER", DLFolder.class
		},
		new Object[] {
			"ADD_FOLDER", "ADD_SUBFOLDER", IGFolder.class
		},
		new Object[] {
			"ADD_FOLDER", "ADD_SUBFOLDER", BookmarksFolder.class
		},
		new Object[] {
			"ADD_LOCATION", "MANAGE_SUBORGANIZATIONS", Organization.class
		},
		new Object[] {
			"ADD_PERMISSIONS", "DEFINE_PERMISSIONS", Role.class
		},
		new Object[] {
			"ADD_USER", "MANAGE_USERS", Location.class
		},
		new Object[] {
			"ADD_USER", "MANAGE_USERS", Organization.class
		},
		new Object[] {
			"ASSIGN_USERS", "ASSIGN_MEMBERS", Group.class
		},
		new Object[] {
			"ASSIGN_USERS", "ASSIGN_MEMBERS", Role.class
		},
		new Object[] {
			"ASSIGN_USERS", "ASSIGN_MEMBERS", UserGroup.class
		}
	};

	private static Log _log = LogFactory.getLog(UpgradePermission.class);

}