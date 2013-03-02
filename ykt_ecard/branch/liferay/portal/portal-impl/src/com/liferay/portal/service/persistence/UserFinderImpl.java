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
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.impl.UserImpl;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
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
 * <a href="UserFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jon Steer
 *
 */
public class UserFinderImpl implements UserFinder {

	public static String COUNT_BY_C_FN_MN_LN_SN_EA_A =
		UserFinder.class.getName() + ".countByC_FN_MN_LN_SN_EA_A";

	public static String FIND_BY_C_FN_MN_LN_SN_EA_A =
		UserFinder.class.getName() + ".findByC_FN_MN_LN_SN_EA_A";

	public static String JOIN_BY_PERMISSION =
		UserFinder.class.getName() + ".joinByPermission";

	public static String JOIN_BY_USER_GROUP_ROLE =
		UserFinder.class.getName() + ".joinByUserGroupRole";

	public static String JOIN_BY_USERS_GROUPS =
		UserFinder.class.getName() + ".joinByUsersGroups";

	public static String JOIN_BY_USERS_ORGS =
		UserFinder.class.getName() + ".joinByUsersOrgs";

	public static String JOIN_BY_USERS_PASSWORD_POLICIES =
		UserFinder.class.getName() + ".joinByUsersPasswordPolicies";

	public static String JOIN_BY_USERS_ROLES =
		UserFinder.class.getName() + ".joinByUsersRoles";

	public static String JOIN_BY_USERS_USER_GROUPS =
		UserFinder.class.getName() + ".joinByUsersUserGroups";

	public int countByKeywords(
			long companyId, String keywords, Boolean active,
			LinkedHashMap params)
		throws SystemException {

		String[] firstNames = null;
		String[] middleNames = null;
		String[] lastNames = null;
		String[] screenNames = null;
		String[] emailAddresses = null;
		boolean andOperator = false;

		if (Validator.isNotNull(keywords)) {
			firstNames = CustomSQLUtil.keywords(keywords);
			middleNames = CustomSQLUtil.keywords(keywords);
			lastNames = CustomSQLUtil.keywords(keywords);
			screenNames = CustomSQLUtil.keywords(keywords);
			emailAddresses = CustomSQLUtil.keywords(keywords);
		}
		else {
			andOperator = true;
		}

		return countByC_FN_MN_LN_SN_EA_A(
			companyId, firstNames, middleNames, lastNames, screenNames,
			emailAddresses, active, params, andOperator);
	}

	public int countByC_FN_MN_LN_SN_EA_A(
			long companyId, String firstName, String middleName,
			String lastName, String screenName, String emailAddress,
			Boolean active, LinkedHashMap params, boolean andOperator)
		throws SystemException {

		return countByC_FN_MN_LN_SN_EA_A(
			companyId, new String[] {firstName}, new String[] {middleName},
			new String[] {lastName}, new String[] {screenName},
			new String[] {emailAddress}, active, params, andOperator);
	}

	public int countByC_FN_MN_LN_SN_EA_A(
			long companyId, String[] firstNames, String[] middleNames,
			String[] lastNames, String[] screenNames, String[] emailAddresses,
			Boolean active, LinkedHashMap params, boolean andOperator)
		throws SystemException {

		firstNames = CustomSQLUtil.keywords(firstNames);
		middleNames = CustomSQLUtil.keywords(middleNames);
		lastNames = CustomSQLUtil.keywords(lastNames);
		screenNames = CustomSQLUtil.keywords(screenNames);
		emailAddresses = CustomSQLUtil.keywords(emailAddresses);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_C_FN_MN_LN_SN_EA_A);

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Contact_.firstName)", StringPool.LIKE, false,
				firstNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Contact_.middleName)", StringPool.LIKE, false,
				middleNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Contact_.lastName)", StringPool.LIKE, false,
				lastNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(User_.screenName)", StringPool.LIKE, false,
				screenNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(User_.emailAddress)", StringPool.LIKE, true,
				emailAddresses);

			if (active == null) {
				sql = StringUtil.replace(sql, ACTIVE_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));
			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(false);
			qPos.add(firstNames, 2);
			qPos.add(middleNames, 2);
			qPos.add(lastNames, 2);
			qPos.add(screenNames, 2);
			qPos.add(emailAddresses, 2);

			if (active != null) {
				qPos.add(active);
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

	public List findByKeywords(
			long companyId, String keywords, Boolean active,
			LinkedHashMap params, int begin, int end, OrderByComparator obc)
		throws SystemException {

		String[] firstNames = null;
		String[] middleNames = null;
		String[] lastNames = null;
		String[] screenNames = null;
		String[] emailAddresses = null;
		boolean andOperator = false;

		if (Validator.isNotNull(keywords)) {
			firstNames = CustomSQLUtil.keywords(keywords);
			middleNames = CustomSQLUtil.keywords(keywords);
			lastNames = CustomSQLUtil.keywords(keywords);
			screenNames = CustomSQLUtil.keywords(keywords);
			emailAddresses = CustomSQLUtil.keywords(keywords);
		}
		else {
			andOperator = true;
		}

		return findByC_FN_MN_LN_SN_EA_A(
			companyId, firstNames, middleNames, lastNames, screenNames,
			emailAddresses, active, params, andOperator, begin, end, obc);
	}

	public List findByC_FN_MN_LN_SN_EA_A(
			long companyId, String firstName, String middleName,
			String lastName, String screenName, String emailAddress,
			Boolean active, LinkedHashMap params, boolean andOperator,
			int begin, int end, OrderByComparator obc)
		throws SystemException {

		return findByC_FN_MN_LN_SN_EA_A(
			companyId, new String[] {firstName}, new String[] {middleName},
			new String[] {lastName}, new String[] {screenName},
			new String[] {emailAddress}, active, params, andOperator, begin,
			end, obc);
	}

	public List findByC_FN_MN_LN_SN_EA_A(
			long companyId, String[] firstNames, String[] middleNames,
			String[] lastNames, String[] screenNames, String[] emailAddresses,
			Boolean active, LinkedHashMap params, boolean andOperator,
			int begin, int end, OrderByComparator obc)
		throws SystemException {

		firstNames = CustomSQLUtil.keywords(firstNames);
		middleNames = CustomSQLUtil.keywords(middleNames);
		lastNames = CustomSQLUtil.keywords(lastNames);
		screenNames = CustomSQLUtil.keywords(screenNames);
		emailAddresses = CustomSQLUtil.keywords(emailAddresses);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_C_FN_MN_LN_SN_EA_A);

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Contact_.firstName)", StringPool.LIKE, false,
				firstNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Contact_.middleName)", StringPool.LIKE, false,
				middleNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Contact_.lastName)", StringPool.LIKE, false,
				lastNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(User_.screenName)", StringPool.LIKE, false,
				screenNames);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(User_.emailAddress)", StringPool.LIKE, true,
				emailAddresses);

			if (active == null) {
				sql = StringUtil.replace(sql, ACTIVE_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));
			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);
			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("User_", UserImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(false);
			qPos.add(firstNames, 2);
			qPos.add(middleNames, 2);
			qPos.add(lastNames, 2);
			qPos.add(screenNames, 2);
			qPos.add(emailAddresses, 2);

			if (active != null) {
				qPos.add(active);
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

		if (key.equals("permission")) {
			join = CustomSQLUtil.get(JOIN_BY_PERMISSION);
		}
		else if (key.equals("userGroupRole")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUP_ROLE);
		}
		else if (key.equals("usersGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_GROUPS);
		}
		else if (key.equals("usersOrgs")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_ORGS);
		}
		else if (key.equals("usersPasswordPolicies")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_PASSWORD_POLICIES);
		}
		else if (key.equals("usersRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_ROLES);
		}
		else if (key.equals("usersUserGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_USER_GROUPS);
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

		if (key.equals("permission")) {
			join = CustomSQLUtil.get(JOIN_BY_PERMISSION);
		}
		else if (key.equals("userGroupRole")) {
			join = CustomSQLUtil.get(JOIN_BY_USER_GROUP_ROLE);
		}
		else if (key.equals("usersGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_GROUPS);
		}
		else if (key.equals("usersOrgs")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_ORGS);

			if (value instanceof Long[]) {
				Long[] organizationIds = (Long[])value;

				StringMaker sm = new StringMaker();

				sm.append("WHERE (");

				for (int i = 0; i < organizationIds.length; i++) {
					sm.append("(Users_Orgs.organizationId = ?) ");

					if ((i + 1) < organizationIds.length) {
						sm.append("OR ");
					}
				}

				sm.append(")");

				join = sm.toString();
			}
		}
		else if (key.equals("usersPasswordPolicies")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_PASSWORD_POLICIES);
		}
		else if (key.equals("usersRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_ROLES);
		}
		else if (key.equals("usersUserGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_USERS_USER_GROUPS);
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
				else if (value instanceof Long[]) {
					Long[] valueArray = (Long[])value;

					for (int i = 0; i < valueArray.length; i++) {
						if (Validator.isNotNull(valueArray[i])) {
							qPos.add(valueArray[i]);
						}
					}
				}
				else if (value instanceof String) {
					String valueString = (String)value;

					if (Validator.isNotNull(valueString)) {
						qPos.add(valueString);
					}
				}
				else if (value instanceof String[]) {
					String[] valueArray = (String[])value;

					for (int i = 0; i < valueArray.length; i++) {
						if (Validator.isNotNull(valueArray[i])) {
							qPos.add(valueArray[i]);
						}
					}
				}
			}
		}
	}

	protected static String ACTIVE_SQL = "AND (User_.active_ = ?)";

}