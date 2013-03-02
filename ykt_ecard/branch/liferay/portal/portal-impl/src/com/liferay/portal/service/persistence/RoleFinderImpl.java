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

import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.impl.GroupModelImpl;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.model.impl.RoleModelImpl;
import com.liferay.portal.model.impl.UserModelImpl;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="RoleFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RoleFinderImpl implements RoleFinder {

	public static String COUNT_BY_C_N_D_T =
		RoleFinder.class.getName() + ".countByC_N_D_T";

	public static String COUNT_BY_COMMUNITY =
		RoleFinder.class.getName() + ".countByCommunity";

	public static String COUNT_BY_ORGANIZATION =
		RoleFinder.class.getName() + ".countByOrganization";

	public static String COUNT_BY_USER =
		RoleFinder.class.getName() + ".countByUser";

	public static String COUNT_BY_USER_GROUP =
		RoleFinder.class.getName() + ".countByUserGroup";

	public static String FIND_BY_USER_GROUP_ROLE =
		RoleFinder.class.getName() + ".findByUserGroupRole";

	public static String FIND_BY_C_N =
		RoleFinder.class.getName() + ".findByC_N";

	public static String FIND_BY_U_G =
		RoleFinder.class.getName() + ".findByU_G";

	public static String FIND_BY_C_N_D_T =
		RoleFinder.class.getName() + ".findByC_N_D_T";

	public static String FIND_BY_C_N_S_P =
		RoleFinder.class.getName() + ".findByC_N_S_P";

	public static String JOIN_BY_ROLES_PERMISSIONS =
		RoleFinder.class.getName() + ".joinByRolesPermissions";

	public static String JOIN_BY_USERS_ROLES =
		RoleFinder.class.getName() + ".joinByUsersRoles";

	public int countByR_U(long roleId, long userId) throws SystemException {
		String finderSQL = Role.class.getName();
		boolean[] finderClassNamesCacheEnabled = new boolean[] {
			GroupModelImpl.CACHE_ENABLED, RoleModelImpl.CACHE_ENABLED,
			GroupModelImpl.CACHE_ENABLED_GROUPS_ROLES,
			UserModelImpl.CACHE_ENABLED_USERS_GROUPS,
			UserModelImpl.CACHE_ENABLED_USERS_ORGS,
			UserModelImpl.CACHE_ENABLED_USERS_ROLES,
			UserModelImpl.CACHE_ENABLED_USERS_USERGROUPS
		};
		String[] finderClassNames = new String[] {
			Group.class.getName(), Role.class.getName(), "Groups_Roles",
			"Users_Groups", "Users_Orgs", "Users_Roles", "Users_UserGroups"
		};
		String finderMethodName = "customCountByR_U";
		String finderParams[] = new String[] {
			Long.class.getName(), Long.class.getName()
		};
		Object finderArgs[] = new Object[] {new Long(roleId), new Long(userId)};

		Object result = null;

		if (!ArrayUtil.contains(finderClassNamesCacheEnabled, false)) {
			result = FinderCache.getResult(
				finderSQL, finderClassNames, finderMethodName, finderParams,
				finderArgs);
		}

		if (result == null) {
			Session session = null;

			try {
				session = HibernateUtil.openSession();

				StringMaker sm = new StringMaker();

				sm.append("(");
				sm.append(CustomSQLUtil.get(COUNT_BY_COMMUNITY));
				sm.append(") UNION (");
				sm.append(CustomSQLUtil.get(COUNT_BY_ORGANIZATION));
				sm.append(") UNION (");
				sm.append(CustomSQLUtil.get(COUNT_BY_USER));
				sm.append(") UNION (");
				sm.append(CustomSQLUtil.get(COUNT_BY_USER_GROUP));
				sm.append(")");

				SQLQuery q = session.createSQLQuery(sm.toString());

				q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

				QueryPos qPos = QueryPos.getInstance(q);

				for (int i = 0; i < 4; i++) {
					qPos.add(roleId);
					qPos.add(userId);
				}

				int count = 0;

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					Long l = (Long)itr.next();

					if (l != null) {
						count += l.intValue();
					}
				}

				FinderCache.putResult(
					finderSQL, finderClassNamesCacheEnabled, finderClassNames,
					finderMethodName, finderParams, finderArgs,
					new Long(count));

				return count;
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				HibernateUtil.closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	public int countByC_N_D_T(
			long companyId, String name, String description, Integer type,
			LinkedHashMap params)
		throws SystemException {

		name = StringUtil.lowerCase(name);
		description = StringUtil.lowerCase(description);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_C_N_D_T);

			if (type == null) {
				sql = StringUtil.replace(sql, "AND (Role_.type_ = ?)", "");
			}

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(name);
			qPos.add(description);
			qPos.add(description);

			if (type != null) {
				qPos.add(type);
			}

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

	public List findByUserGroupRole(long userId, long groupId)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_USER_GROUP_ROLE);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Role_", RoleImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(userId);
			qPos.add(groupId);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public Role findByC_N(long companyId, String name)
		throws NoSuchRoleException, SystemException {

		name = StringUtil.lowerCase(name);

		boolean finderClassNameCacheEnabled = RoleModelImpl.CACHE_ENABLED;
		String finderClassName = Role.class.getName();
		String finderMethodName = "customFindByC_N";
		String finderParams[] = new String[] {
			Long.class.getName(), String.class.getName()
		};
		Object finderArgs[] = new Object[] {new Long(companyId), name};

		Object result = FinderCache.getResult(
			finderClassName, finderMethodName, finderParams, finderArgs);

		if (result == null) {
			Session session = null;

			try {
				session = HibernateUtil.openSession();

				String sql = CustomSQLUtil.get(FIND_BY_C_N);

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("Role_", RoleImpl.class);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(companyId);
				qPos.add(name);

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					Role role = (Role)itr.next();

					FinderCache.putResult(
						finderClassNameCacheEnabled, finderClassName,
						finderMethodName, finderParams, finderArgs, role);

					return role;
				}
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				HibernateUtil.closeSession(session);
			}

			throw new NoSuchRoleException(
				"No Role exists with the key {companyId=" + companyId +
					", name=" + name + "}");
		}
		else {
			return (Role)result;
		}
	}

	public List findByU_G(long userId, long groupId) throws SystemException {
		return findByU_G(userId, new long[] {groupId});
	}

	public List findByU_G(long userId, long[] groupIds) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_U_G);

			sql = StringUtil.replace(
				sql, "[$GROUP_IDS$]", getGroupIds(groupIds, "Groups_Roles"));

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Role_", RoleImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(userId);
			setGroupIds(qPos, groupIds);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByU_G(long userId, List groups) throws SystemException {
		long[] groupIds = new long[groups.size()];

		for (int i = 0; i < groups.size(); i++) {
			Group group = (Group)groups.get(i);

			groupIds[i] = group.getGroupId();
		}

		return findByU_G(userId, groupIds);
	}

	public List findByC_N_D_T(
			long companyId, String name, String description, Integer type,
			LinkedHashMap params, int begin, int end, OrderByComparator obc)
		throws SystemException {

		name = StringUtil.lowerCase(name);
		description = StringUtil.lowerCase(description);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_C_N_D_T);

			if (type == null) {
				sql = StringUtil.replace(sql, "AND (Role_.type_ = ?)", "");
			}

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));
			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("Role_", RoleImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(name);
			qPos.add(description);
			qPos.add(description);

			if (type != null) {
				qPos.add(type);
			}

			return QueryUtil.list(q, HibernateUtil.getDialect(), begin, end);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public Map findByC_N_S_P(
			long companyId, String name, int scope, String primKey)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_C_N_S_P);

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar("roleName", Hibernate.STRING);
			q.addScalar("actionId", Hibernate.STRING);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(companyId);
			qPos.add(name);
			qPos.add(scope);
			qPos.add(primKey);

			Map roleMap = new HashMap();

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				Object[] array = (Object[])itr.next();

				String roleName = (String)array[0];
				String actionId = (String)array[1];

				List roleList = (List)roleMap.get(roleName);

				if (roleList == null) {
					roleList = new ArrayList();
				}

				roleList.add(actionId);

				roleMap.put(roleName, roleList);
			}

			return roleMap;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	protected String getGroupIds(long[] groupIds, String table) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < groupIds.length; i++) {
			sm.append(table);
			sm.append(".groupId = ?");

			if ((i + 1) < groupIds.length) {
				sm.append(" OR ");
			}
		}

		return sm.toString();
	}

	protected void setGroupIds(QueryPos qPos, long[] groupIds) {
		for (int i = 0; i < groupIds.length; i++) {
			qPos.add(groupIds[i]);
		}
	}

	protected String getJoin(LinkedHashMap params) {
		if (params == null) {
			return StringPool.BLANK;
		}

		StringMaker sm = new StringMaker();

		Iterator itr = params.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			Object value = entry.getValue();

			if (Validator.isNotNull(value)) {
				sm.append(getJoin(key));
			}
		}

		return sm.toString();
	}

	protected String getJoin(String key) {
		String join = StringPool.BLANK;

		if (key.equals("permissionsResourceId")) {
			join = CustomSQLUtil.get(JOIN_BY_ROLES_PERMISSIONS);
		}
		else if (key.equals("usersRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_ROLES);
		}

		if (Validator.isNotNull(join)) {
			int pos = join.indexOf("WHERE");

			if (pos != -1) {
				join = join.substring(0, pos);
			}
		}

		return join;
	}

	protected String getWhere(LinkedHashMap params) {
		if (params == null) {
			return StringPool.BLANK;
		}

		StringMaker sm = new StringMaker();

		Iterator itr = params.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			Object value = entry.getValue();

			if (Validator.isNotNull(value)) {
				sm.append(getWhere(key));
			}
		}

		return sm.toString();
	}

	protected String getWhere(String key) {
		String join = StringPool.BLANK;

		if (key.equals("permissionsResourceId")) {
			join = CustomSQLUtil.get(JOIN_BY_ROLES_PERMISSIONS);
		}
		else if (key.equals("usersRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_ROLES);
		}

		if (Validator.isNotNull(join)) {
			int pos = join.indexOf("WHERE");

			if (pos != -1) {
				join = join.substring(pos + 5, join.length()) + " AND ";
			}
		}

		return join;
	}

	protected void setJoin(QueryPos qPos, LinkedHashMap params) {
		if (params != null) {
			Iterator itr = params.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				Object value = entry.getValue();

				if (value instanceof Long) {
					Long valueLong = (Long)value;

					if (Validator.isNotNull(valueLong)) {
						qPos.add(valueLong);
					}
				}
				else if (value instanceof String) {
					String valueString = (String)value;

					if (Validator.isNotNull(valueString)) {
						qPos.add(valueString);
					}
				}
			}
		}
	}

}