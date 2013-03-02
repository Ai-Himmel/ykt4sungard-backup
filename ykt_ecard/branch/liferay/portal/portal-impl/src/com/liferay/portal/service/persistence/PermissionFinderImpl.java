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

package com.liferay.portal.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.impl.PermissionImpl;
import com.liferay.portal.model.impl.PermissionModelImpl;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.util.dao.hibernate.QueryPos;

import java.util.Iterator;
import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="PermissionFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionFinderImpl implements PermissionFinder {

	public static String COUNT_BY_GROUPS_PERMISSIONS =
		PermissionFinder.class.getName() + ".countByGroupsPermissions";

	public static String COUNT_BY_GROUPS_ROLES =
		PermissionFinder.class.getName() + ".countByGroupsRoles";

	public static String COUNT_BY_ROLES_PERMISSIONS =
		PermissionFinder.class.getName() + ".countByRolesPermissions";

	public static String COUNT_BY_USER_GROUP_ROLE =
		PermissionFinder.class.getName() + ".countByUserGroupRole";

	public static String COUNT_BY_USERS_PERMISSIONS =
		PermissionFinder.class.getName() + ".countByUsersPermissions";

	public static String COUNT_BY_USERS_ROLES =
		PermissionFinder.class.getName() + ".countByUsersRoles";

	public static String FIND_BY_A_R =
		PermissionFinder.class.getName() + ".findByA_R";

	public static String FIND_BY_G_R =
		PermissionFinder.class.getName() + ".findByG_R";

	public static String FIND_BY_R_R =
		PermissionFinder.class.getName() + ".findByR_R";

	public static String FIND_BY_U_R =
		PermissionFinder.class.getName() + ".findByU_R";

	public static String FIND_BY_O_G_R =
		PermissionFinder.class.getName() + ".findByO_G_R";

	public static String FIND_BY_U_A_R =
		PermissionFinder.class.getName() + ".findByU_A_R";

	public static String FIND_BY_G_C_N_S_P =
		PermissionFinder.class.getName() + ".findByG_C_N_S_P";

	public static String FIND_BY_U_C_N_S_P =
		PermissionFinder.class.getName() + ".findByU_C_N_S_P";

	public boolean containsPermissions_2(
			List permissions, long userId, List groups, long groupId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = null;

			StringMaker sm = new StringMaker();

			if (groups.size() > 0) {
				sm.append("(");
				sm.append(CustomSQLUtil.get(COUNT_BY_GROUPS_ROLES));
				sm.append(") ");

				sql = sm.toString();

				sql = StringUtil.replace(
					sql, "[$PERMISSION_IDS$]",
					getPermissionIds(permissions, "Roles_Permissions"));
				sql = StringUtil.replace(
					sql, "[$GROUP_IDS$]", getGroupIds(groups, "Groups_Roles"));

				sm = new StringMaker();

				sm.append(sql);

				sm.append("UNION ALL (");
				sm.append(CustomSQLUtil.get(COUNT_BY_GROUPS_PERMISSIONS));
				sm.append(") ");

				sql = sm.toString();

				sql = StringUtil.replace(
					sql, "[$PERMISSION_IDS$]",
					getPermissionIds(permissions, "Groups_Permissions"));
				sql = StringUtil.replace(
					sql, "[$GROUP_IDS$]",
					getGroupIds(groups, "Groups_Permissions"));

				sm = new StringMaker();

				sm.append(sql);

				sm.append("UNION ALL ");
			}

			sm.append("(");
			sm.append(CustomSQLUtil.get(COUNT_BY_USERS_ROLES));
			sm.append(") ");

			sql = sm.toString();

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Roles_Permissions"));

			sm = new StringMaker();

			sm.append(sql);

			sm.append("UNION ALL (");
			sm.append(CustomSQLUtil.get(COUNT_BY_USER_GROUP_ROLE));
			sm.append(") ");

			sql = sm.toString();

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Roles_Permissions"));

			sm = new StringMaker();

			sm.append(sql);

			sm.append("UNION ALL (");
			sm.append(CustomSQLUtil.get(COUNT_BY_USERS_PERMISSIONS));
			sm.append(") ");

			sql = sm.toString();

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Users_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			if (groups.size() > 0) {
				setPermissionIds(qPos, permissions);
				setGroupIds(qPos, groups);
				setPermissionIds(qPos, permissions);
				setGroupIds(qPos, groups);
			}

			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			qPos.add(groupId);
			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				Long count = (Long)itr.next();

				if ((count != null) && (count.intValue() > 0)) {
					return true;
				}
			}

			return false;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsPermissions_4(
			List permissions, long userId, List groups, List roles)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = null;

			StringMaker sm = new StringMaker();

			if (groups.size() > 0) {
				sm.append("(");
				sm.append(CustomSQLUtil.get(COUNT_BY_GROUPS_PERMISSIONS));
				sm.append(") ");

				sql = sm.toString();

				sql = StringUtil.replace(
					sql, "[$PERMISSION_IDS$]",
					getPermissionIds(permissions, "Groups_Permissions"));
				sql = StringUtil.replace(
					sql, "[$GROUP_IDS$]",
					getGroupIds(groups, "Groups_Permissions"));

				sm = new StringMaker();

				sm.append(sql);

				sm.append("UNION ALL ");
			}

			if (roles.size() > 0) {
				sm.append("(");
				sm.append(CustomSQLUtil.get(COUNT_BY_ROLES_PERMISSIONS));
				sm.append(") ");

				sql = sm.toString();

				sql = StringUtil.replace(
					sql, "[$PERMISSION_IDS$]",
					getPermissionIds(permissions, "Roles_Permissions"));
				sql = StringUtil.replace(
					sql, "[$ROLE_IDS$]",
					getRoleIds(roles, "Roles_Permissions"));

				sm = new StringMaker();

				sm.append(sql);

				sm.append("UNION ALL ");
			}

			sm.append("(");
			sm.append(CustomSQLUtil.get(COUNT_BY_USERS_PERMISSIONS));
			sm.append(") ");

			sql = sm.toString();

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Users_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			if (groups.size() > 0) {
				setPermissionIds(qPos, permissions);
				setGroupIds(qPos, groups);
			}

			if (roles.size() > 0) {
				setPermissionIds(qPos, permissions);
				setRoleIds(qPos, roles);
			}

			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				Long count = (Long)itr.next();

				if ((count != null) && (count.intValue() > 0)) {
					return true;
				}
			}

			return false;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByGroupsPermissions(List permissions, List groups)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_GROUPS_PERMISSIONS);

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Groups_Permissions"));
			sql = StringUtil.replace(
				sql, "[$GROUP_IDS$]",
				getGroupIds(groups, "Groups_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setPermissionIds(qPos, permissions);
			setGroupIds(qPos, groups);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Long count = (Long)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByGroupsRoles(List permissions, List groups)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_GROUPS_ROLES);

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Roles_Permissions"));
			sql = StringUtil.replace(
				sql, "[$GROUP_IDS$]", getGroupIds(groups, "Groups_Roles"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setPermissionIds(qPos, permissions);
			setGroupIds(qPos, groups);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Long count = (Long)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByRolesPermissions(List permissions, List roles)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_ROLES_PERMISSIONS);

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Roles_Permissions"));
			sql = StringUtil.replace(
				sql, "[$ROLE_IDS$]", getRoleIds(roles, "Roles_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setPermissionIds(qPos, permissions);
			setRoleIds(qPos, roles);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Long count = (Long)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByUserGroupRole(List permissions, long userId, long groupId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_USER_GROUP_ROLE);

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Roles_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(groupId);
			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Long count = (Long)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByUsersPermissions(List permissions, long userId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_USERS_PERMISSIONS);

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Users_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Long count = (Long)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByUsersRoles(List permissions, long userId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_USERS_ROLES);

			sql = StringUtil.replace(
				sql, "[$PERMISSION_IDS$]",
				getPermissionIds(permissions, "Roles_Permissions"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setPermissionIds(qPos, permissions);
			qPos.add(userId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Long count = (Long)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByA_R(String actionId, long[] resourceIds)
		throws SystemException {

		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
		String finderMethodName = "customFindByA_R";
		String finderParams[] = new String[] {
			String.class.getName(), "[L" + Long.class.getName()
		};
		Object finderArgs[] = new Object[] {
			actionId, StringUtil.merge(ArrayUtil.toObjectArray(resourceIds))
		};

		Object result = FinderCache.getResult(
			finderClassName, finderMethodName, finderParams, finderArgs);

		if (result == null) {
			Session session = null;

			try {
				session = HibernateUtil.openSession();

				String sql = CustomSQLUtil.get(FIND_BY_A_R);

				sql = StringUtil.replace(
					sql, "[$RESOURCE_IDS$]", getResourceIds(resourceIds));

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("Permission_", PermissionImpl.class);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(actionId);
				setResourceIds(qPos, resourceIds);

				List list = q.list();

				FinderCache.putResult(
					finderClassNameCacheEnabled, finderClassName,
					finderMethodName, finderParams, finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				HibernateUtil.closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public List findByG_R(long groupId, long resourceId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_G_R);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(groupId);
			qPos.add(resourceId);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByR_R(long roleId, long resourceId) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_R_R);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(roleId);
			qPos.add(resourceId);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByU_R(long userId, long resourceId) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_U_R);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(userId);
			qPos.add(resourceId);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByO_G_R(long organizationId, long groupId, long resourceId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_O_G_R);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(organizationId);
			qPos.add(groupId);
			qPos.add(resourceId);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByU_A_R(long userId, String[] actionIds, long resourceId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_U_R);

			sql = StringUtil.replace(
				sql, "[$ACTION_IDS$]", getActionIds(actionIds));

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(userId);
			qPos.add(resourceId);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByG_C_N_S_P(
			long groupId, long companyId, String name, int scope,
			String primKey)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_G_C_N_S_P);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(groupId);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(scope);
			qPos.add(primKey);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByU_C_N_S_P(
			long userId, long companyId, String name, int scope, String primKey)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_U_C_N_S_P);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Permission_", PermissionImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(userId);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(scope);
			qPos.add(primKey);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	protected String getActionIds(String[] actionIds) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < actionIds.length; i++) {
			sm.append("Permission_.actionId = ?");

			if ((i + 1) < actionIds.length) {
				sm.append(" OR ");
			}
		}

		return sm.toString();
	}

	protected String getGroupIds(List groups, String table) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < groups.size(); i++) {
			sm.append(table);
			sm.append(".groupId = ?");

			if ((i + 1) < groups.size()) {
				sm.append(" OR ");
			}
		}

		return sm.toString();
	}

	protected String getPermissionIds(List permissions, String table) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < permissions.size(); i++) {
			sm.append(table);
			sm.append(".permissionId = ?");

			if ((i + 1) < permissions.size()) {
				sm.append(" OR ");
			}
		}

		return sm.toString();
	}

	protected String getResourceIds(long[] resourceIds) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < resourceIds.length; i++) {
			sm.append("resourceId = ?");

			if ((i + 1) < resourceIds.length) {
				sm.append(" OR ");
			}
		}

		return sm.toString();
	}

	protected String getRoleIds(List roles, String table) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < roles.size(); i++) {
			sm.append(table);
			sm.append(".roleId = ?");

			if ((i + 1) < roles.size()) {
				sm.append(" OR ");
			}
		}

		return sm.toString();
	}

	protected void setGroupIds(QueryPos qPos, List groups) {
		for (int i = 0; i < groups.size(); i++) {
			Group group = (Group)groups.get(i);

			qPos.add(group.getGroupId());
		}
	}

	protected void setPermissionIds(QueryPos qPos, List permissions) {
		for (int i = 0; i < permissions.size(); i++) {
			Permission permission = (Permission)permissions.get(i);

			qPos.add(permission.getPermissionId());
		}
	}

	protected void setResourceIds(QueryPos qPos, long[] resourceIds) {
		for (int i = 0; i < resourceIds.length; i++) {
			long resourceId = resourceIds[i];

			qPos.add(resourceId);
		}
	}

	protected void setRoleIds(QueryPos qPos, List roles) {
		for (int i = 0; i < roles.size(); i++) {
			Role role = (Role)roles.get(i);

			qPos.add(role.getRoleId());
		}
	}

}