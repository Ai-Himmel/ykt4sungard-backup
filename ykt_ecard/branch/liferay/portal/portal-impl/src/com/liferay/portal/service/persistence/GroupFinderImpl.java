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

import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.model.UserGroupRole;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.GroupModelImpl;
import com.liferay.portal.model.impl.LayoutSetModelImpl;
import com.liferay.portal.model.impl.PermissionModelImpl;
import com.liferay.portal.model.impl.ResourceCodeModelImpl;
import com.liferay.portal.model.impl.ResourceModelImpl;
import com.liferay.portal.model.impl.RoleModelImpl;
import com.liferay.portal.model.impl.UserGroupRoleModelImpl;
import com.liferay.portal.model.impl.UserModelImpl;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="GroupFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupFinderImpl implements GroupFinder {

	public static String COUNT_BY_GROUP_ID =
		GroupFinder.class.getName() + ".countByGroupId";

	public static String COUNT_BY_C_N_D =
		GroupFinder.class.getName() + ".countByC_N_D";

	public static String FIND_BY_C_N =
		GroupFinder.class.getName() + ".findByC_N";

	public static String FIND_BY_C_N_D =
		GroupFinder.class.getName() + ".findByC_N_D";

	public static String JOIN_BY_ACTIVE =
		GroupFinder.class.getName() + ".joinByActive";

	public static String JOIN_BY_CREATOR_USER_ID =
		GroupFinder.class.getName() + ".joinByCreatorUserId";

	public static String JOIN_BY_GROUPS_ORGS =
		GroupFinder.class.getName() + ".joinByGroupsOrgs";

	public static String JOIN_BY_GROUPS_ROLES =
		GroupFinder.class.getName() + ".joinByGroupsRoles";

	public static String JOIN_BY_GROUPS_USER_GROUPS =
		GroupFinder.class.getName() + ".joinByGroupsUserGroups";

	public static String JOIN_BY_LAYOUT_SET =
		GroupFinder.class.getName() + ".joinByLayoutSet";

	public static String JOIN_BY_PAGE_COUNT =
		GroupFinder.class.getName() + ".joinByPageCount";

	public static String JOIN_BY_ROLE_PERMISSIONS =
		GroupFinder.class.getName() + ".joinByRolePermissions";

	public static String JOIN_BY_TYPE =
		GroupFinder.class.getName() + ".joinByType";

	public static String JOIN_BY_USER_GROUP_ROLE =
		GroupFinder.class.getName() + ".joinByUserGroupRole";

	public static String JOIN_BY_USERS_GROUPS =
		GroupFinder.class.getName() + ".joinByUsersGroups";

	public int countByG_U(long groupId, long userId) throws SystemException {
		String finderSQL = Group.class.getName();
		boolean[] finderClassNamesCacheEnabled = new boolean[] {
			GroupModelImpl.CACHE_ENABLED,
			GroupModelImpl.CACHE_ENABLED_GROUPS_ORGS,
			GroupModelImpl.CACHE_ENABLED_GROUPS_USERGROUPS,
			UserModelImpl.CACHE_ENABLED_USERS_GROUPS,
			UserModelImpl.CACHE_ENABLED_USERS_ORGS,
			UserModelImpl.CACHE_ENABLED_USERS_USERGROUPS
		};
		String[] finderClassNames = new String[] {
			Group.class.getName(), "Groups_Orgs", "Groups_UserGroups",
			"Users_Groups", "Users_Orgs", "Users_UserGroups"
		};
		String finderMethodName = "customCountByG_U";
		String finderParams[] = new String[] {
			Long.class.getName(), Long.class.getName()
		};
		Object finderArgs[] = new Object[] {
			new Long(groupId), new Long(userId)
		};

		Object result = null;

		if (!ArrayUtil.contains(finderClassNamesCacheEnabled, false)) {
			result = FinderCache.getResult(
				finderSQL, finderClassNames, finderMethodName, finderParams,
				finderArgs);
		}

		if (result == null) {
			Long userIdObj = new Long(userId);

			LinkedHashMap params1 = new LinkedHashMap();

			params1.put("usersGroups", userIdObj);

			LinkedHashMap params2 = new LinkedHashMap();

			params2.put("groupsOrgs", userIdObj);

			LinkedHashMap params3 = new LinkedHashMap();

			params3.put("groupsUserGroups", userIdObj);

			Session session = null;

			try {
				session = HibernateUtil.openSession();

				int count = countByGroupId(session, groupId, params1);
				count += countByGroupId(session, groupId, params2);
				count += countByGroupId(session, groupId, params3);

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

	public int countByC_N_D(
			long companyId, String name, String description,
			LinkedHashMap params)
		throws SystemException {

		name = StringUtil.lowerCase(name);
		description = StringUtil.lowerCase(description);

		if (params == null) {
			params = new LinkedHashMap();
		}

		Long userId = (Long)params.get("usersGroups");

		LinkedHashMap params1 = params;

		LinkedHashMap params2 = new LinkedHashMap();

		params2.putAll(params1);

		if (userId != null) {
			params2.remove("usersGroups");
			params2.put("groupsOrgs", userId);
		}

		LinkedHashMap params3 = new LinkedHashMap();

		params3.putAll(params1);

		if (userId != null) {
			params3.remove("usersGroups");
			params3.put("groupsUserGroups", userId);
		}

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			int count = countByC_N_D(
				session, companyId, name, description, params1);

			if (Validator.isNotNull(userId)) {
				count += countByC_N_D(
					session, companyId, name, description, params2);

				count += countByC_N_D(
					session, companyId, name, description, params3);
			}

			return count;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public Group findByC_N(long companyId, String name)
		throws NoSuchGroupException, SystemException {

		name = StringUtil.lowerCase(name);

		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
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

				q.addEntity("Group_", GroupImpl.class);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(companyId);
				qPos.add(name);

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					Group group = (Group)itr.next();

					FinderCache.putResult(
						finderClassNameCacheEnabled, finderClassName,
						finderMethodName, finderParams, finderArgs, group);

					return group;
				}
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				HibernateUtil.closeSession(session);
			}

			StringMaker sm = new StringMaker();

			sm.append("No Group exists with the key {companyId=");
			sm.append(companyId);
			sm.append(", name=");
			sm.append(name);
			sm.append("}");

			throw new NoSuchGroupException(sm.toString());
		}
		else {
			return (Group)result;
		}
	}

	public List findByC_N_D(
			long companyId, String name, String description,
			LinkedHashMap params, int begin, int end, OrderByComparator obc)
		throws SystemException {

		name = StringUtil.lowerCase(name);
		description = StringUtil.lowerCase(description);

		if (params == null) {
			params = new LinkedHashMap();
		}

		Long userId = (Long)params.get("usersGroups");

		LinkedHashMap params1 = params;

		LinkedHashMap params2 = new LinkedHashMap();

		params2.putAll(params1);

		if (userId != null) {
			params2.remove("usersGroups");
			params2.put("groupsOrgs", userId);
		}

		LinkedHashMap params3 = new LinkedHashMap();

		params3.putAll(params1);

		if (userId != null) {
			params3.remove("usersGroups");
			params3.put("groupsUserGroups", userId);
		}

		StringMaker sm = new StringMaker();

		sm.append("(");

		sm.append(CustomSQLUtil.get(FIND_BY_C_N_D));

		String sql = sm.toString();

		sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params1));
		sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params1));

		sm = new StringMaker();

		sm.append(sql);

		sm.append(")");

		if (Validator.isNotNull(userId)) {
			sm.append(" UNION (");

			sm.append(CustomSQLUtil.get(FIND_BY_C_N_D));

			sql = sm.toString();

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params2));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params2));

			sm = new StringMaker();

			sm.append(sql);

			sm.append(") UNION (");

			sm.append(CustomSQLUtil.get(FIND_BY_C_N_D));

			sql = sm.toString();

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params3));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params3));

			sm = new StringMaker();

			sm.append(sql);

			sm.append(")");
		}

		sql = sm.toString();
		sql = CustomSQLUtil.replaceOrderBy(sql, obc);

		String finderSQL = sql;
		boolean[] finderClassNamesCacheEnabled = new boolean[] {
			GroupModelImpl.CACHE_ENABLED, LayoutSetModelImpl.CACHE_ENABLED,
			PermissionModelImpl.CACHE_ENABLED, ResourceModelImpl.CACHE_ENABLED,
			ResourceCodeModelImpl.CACHE_ENABLED,
			UserGroupRoleModelImpl.CACHE_ENABLED,
			GroupModelImpl.CACHE_ENABLED_GROUPS_ORGS,
			GroupModelImpl.CACHE_ENABLED_GROUPS_ROLES,
			GroupModelImpl.CACHE_ENABLED_GROUPS_USERGROUPS,
			RoleModelImpl.CACHE_ENABLED_ROLES_PERMISSIONS,
			UserModelImpl.CACHE_ENABLED_USERS_GROUPS,
			UserModelImpl.CACHE_ENABLED_USERS_ORGS,
			UserModelImpl.CACHE_ENABLED_USERS_USERGROUPS
		};
		String[] finderClassNames = new String[] {
			Group.class.getName(), LayoutSet.class.getName(),
			Permission.class.getName(), Resource.class.getName(),
			ResourceCode.class.getName(), UserGroupRole.class.getName(),
			"Groups_Orgs", "Groups_Roles", "Groups_UserGroups",
			"Roles_Permissions", "Users_Groups", "Users_Orgs",
			"Users_UserGroups"
		};
		String finderMethodName = "customFindByC_N_D";
		String finderParams[] = new String[] {
			Long.class.getName(), String.class.getName(),
			String.class.getName(), LinkedHashMap.class.getName(),
			String.class.getName(), String.class.getName()
		};
		Object finderArgs[] = new Object[] {
			new Long(companyId), name, description, params.toString(),
			String.valueOf(begin), String.valueOf(end)
		};

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

				SQLQuery q = session.createSQLQuery(sql);

				q.addScalar("groupId", Hibernate.STRING);

				QueryPos qPos = QueryPos.getInstance(q);

				setJoin(qPos, params1);
				qPos.add(companyId);
				qPos.add(name);
				qPos.add(name);
				qPos.add(description);
				qPos.add(description);

				if (Validator.isNotNull(userId)) {
					setJoin(qPos, params2);
					qPos.add(companyId);
					qPos.add(name);
					qPos.add(name);
					qPos.add(description);
					qPos.add(description);

					setJoin(qPos, params3);
					qPos.add(companyId);
					qPos.add(name);
					qPos.add(name);
					qPos.add(description);
					qPos.add(description);
				}

				List list = new ArrayList();

				Iterator itr = QueryUtil.iterate(
					q, HibernateUtil.getDialect(), begin, end);

				while (itr.hasNext()) {
					long groupId = GetterUtil.getLong((String)itr.next());

					Group group = GroupUtil.findByPrimaryKey(groupId);

					list.add(group);
				}

				FinderCache.putResult(
					finderSQL, finderClassNamesCacheEnabled, finderClassNames,
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

	protected int countByGroupId(
			Session session, long groupId, LinkedHashMap params)
		throws SystemException {

		String sql = CustomSQLUtil.get(COUNT_BY_GROUP_ID);

		sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
		sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));

		SQLQuery q = session.createSQLQuery(sql);

		q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

		QueryPos qPos = QueryPos.getInstance(q);

		setJoin(qPos, params);
		qPos.add(groupId);

		Iterator itr = q.list().iterator();

		if (itr.hasNext()) {
			Long count = (Long)itr.next();

			if (count != null) {
				return count.intValue();
			}
		}

		return 0;
	}

	protected int countByC_N_D(
			Session session, long companyId, String name, String description,
			LinkedHashMap params)
		throws SystemException {

		String sql = CustomSQLUtil.get(COUNT_BY_C_N_D);

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

		Iterator itr = q.list().iterator();

		if (itr.hasNext()) {
			Long count = (Long)itr.next();

			if (count != null) {
				return count.intValue();
			}
		}

		return 0;
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

		if (key.equals("groupsOrgs")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_ORGS);
		}
		else if (key.equals("groupsRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_ROLES);
		}
		else if (key.equals("groupsUserGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_USER_GROUPS);
		}
		else if (key.equals("layoutSet")) {
			join = CustomSQLUtil.get(JOIN_BY_LAYOUT_SET);
		}
		else if (key.equals("pageCount")) {
			join = CustomSQLUtil.get(JOIN_BY_PAGE_COUNT);
		}
		else if (key.equals("rolePermissions")) {
			join = CustomSQLUtil.get(JOIN_BY_ROLE_PERMISSIONS);
		}
		else if (key.equals("userGroupRole")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUP_ROLE);
		}
		else if (key.equals("usersGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_GROUPS);
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
				sm.append(getWhere(key, value));
			}
		}

		return sm.toString();
	}

	protected String getWhere(String key, Object value) {
		String join = StringPool.BLANK;

		if (key.equals("active")) {
			join = CustomSQLUtil.get(JOIN_BY_ACTIVE);
		}
		else if (key.equals("creatorUserId")) {
			join = CustomSQLUtil.get(JOIN_BY_CREATOR_USER_ID);
		}
		else if (key.equals("groupsOrgs")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_ORGS);
		}
		else if (key.equals("groupsRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_ROLES);
		}
		else if (key.equals("groupsUserGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_USER_GROUPS);
		}
		else if (key.equals("layoutSet")) {
			join = CustomSQLUtil.get(JOIN_BY_LAYOUT_SET);
		}
		else if (key.equals("pageCount")) {
			join = CustomSQLUtil.get(JOIN_BY_PAGE_COUNT);
		}
		else if (key.equals("rolePermissions")) {
			join = CustomSQLUtil.get(JOIN_BY_ROLE_PERMISSIONS);
		}
		else if (key.equals("type")) {
			join = CustomSQLUtil.get(JOIN_BY_TYPE);
		}
		else if (key.equals("types")) {
			List types = (List)value;

			StringMaker sm = new StringMaker();

			sm.append("WHERE (");

			for (int i = 0; i < types.size(); i++) {
				sm.append("(Group_.type_ = ?) ");

				if ((i + 1) < types.size()) {
					sm.append("OR ");
				}
			}

			sm.append(")");

			join = sm.toString();
		}
		else if (key.equals("userGroupRole")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUP_ROLE);
		}
		else if (key.equals("usersGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_GROUPS);
		}

		if (Validator.isNotNull(join)) {
			int pos = join.indexOf("WHERE");

			if (pos != -1) {
				StringMaker sm = new StringMaker();

				sm.append(join.substring(pos + 5, join.length()));
				sm.append(" AND ");

				join = sm.toString();
			}
		}

		return join;
	}

	protected void setJoin(QueryPos qPos, LinkedHashMap params) {
		if (params != null) {
			Iterator itr = params.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				String key = (String)entry.getKey();

				if (key.equals("active") || key.equals("layoutSet")) {
					Boolean value = (Boolean)entry.getValue();

					qPos.add(value);
				}
				else if (key.equals("pageCount")) {
				}
				else if (key.equals("rolePermissions")) {
					List values = (List)entry.getValue();

					for (int i = 0; i < values.size(); i++) {
						Object value = values.get(i);

						if (value instanceof Integer) {
							Integer valueInteger = (Integer)value;

							qPos.add(valueInteger);
						}
						else if (value instanceof Long) {
							Long valueLong = (Long)value;

							qPos.add(valueLong);
						}
						else if (value instanceof String) {
							String valueString = (String)value;

							qPos.add(valueString);
						}
					}
				}
				else if (key.equals("types")) {
					List values = (List)entry.getValue();

					for (int i = 0; i < values.size(); i++) {
						Integer value = (Integer)values.get(i);

						qPos.add(value);
					}
				}
				else if (key.equals("userGroupRole")) {
					List values = (List)entry.getValue();

					Long userId = (Long)values.get(0);
					Long roleId = (Long)values.get(1);

					qPos.add(userId);
					qPos.add(roleId);
				}
				else {
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

}