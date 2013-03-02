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

import com.liferay.portal.NoSuchUserGroupException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.UserGroupImpl;
import com.liferay.portal.model.impl.UserGroupModelImpl;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="UserGroupFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class UserGroupFinderImpl implements UserGroupFinder {

	public static String COUNT_BY_C_N_D =
		UserGroupFinder.class.getName() + ".countByC_N_D";

	public static String FIND_BY_C_N =
		UserGroupFinder.class.getName() + ".findByC_N";

	public static String FIND_BY_C_N_D =
		UserGroupFinder.class.getName() + ".findByC_N_D";

	public static String JOIN_BY_GROUPS_PERMISSIONS =
		UserGroupFinder.class.getName() + ".joinByGroupsPermissions";

	public static String JOIN_BY_USER_GROUPS_GROUPS =
		UserGroupFinder.class.getName() + ".joinByUserGroupsGroups";

	public static String JOIN_BY_USER_GROUPS_ROLES =
		UserGroupFinder.class.getName() + ".joinByUserGroupsRoles";

	public int countByC_N_D(
			long companyId, String name, String description,
			LinkedHashMap params)
		throws SystemException {

		name = StringUtil.lowerCase(name);
		description = StringUtil.lowerCase(description);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

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
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public UserGroup findByC_N(long companyId, String name)
		throws NoSuchUserGroupException, SystemException {

		name = StringUtil.lowerCase(name);

		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
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

				q.addEntity("UserGroup", UserGroupImpl.class);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(companyId);
				qPos.add(name);

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					UserGroup userGroup = (UserGroup)itr.next();

					FinderCache.putResult(
						finderClassNameCacheEnabled, finderClassName,
						finderMethodName, finderParams, finderArgs, userGroup);

					return userGroup;
				}
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				HibernateUtil.closeSession(session);
			}

			throw new NoSuchUserGroupException(
				"No UserGroup exists with the key {companyId=" + companyId +
					", name=" + name + "}");
		}
		else {
			return (UserGroup)result;
		}
	}

	public List findByC_N_D(
			long companyId, String name, String description,
			LinkedHashMap params, int begin, int end, OrderByComparator obc)
		throws SystemException {

		name = StringUtil.lowerCase(name);
		description = StringUtil.lowerCase(description);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_C_N_D);

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));
			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("UserGroup", UserGroupImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(name);
			qPos.add(description);
			qPos.add(description);

			return QueryUtil.list(q, HibernateUtil.getDialect(), begin, end);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
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
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_PERMISSIONS);
		}
		else if (key.equals("userGroupsGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUPS_GROUPS);
		}
		else if (key.equals("userGroupsRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUPS_ROLES);
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
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_PERMISSIONS);
		}
		else if (key.equals("userGroupsGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUPS_GROUPS);
		}
		else if (key.equals("userGroupsRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUPS_ROLES);
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