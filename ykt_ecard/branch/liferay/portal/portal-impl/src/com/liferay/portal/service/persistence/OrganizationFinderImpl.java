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
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
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
 * <a href="OrganizationFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class OrganizationFinderImpl implements OrganizationFinder {

	public static String COUNT_BY_C_PO_N_S_C_Z_R_C =
		OrganizationFinder.class.getName() + ".countByC_PO_N_S_C_Z_R_C";

	public static String COUNT_BY_C_PO_N_L_S_C_Z_R_C =
		OrganizationFinder.class.getName() + ".countByC_PO_N_L_S_C_Z_R_C";

	public static String FIND_BY_C_PO_N_S_C_Z_R_C =
		OrganizationFinder.class.getName() + ".findByC_PO_N_S_C_Z_R_C";

	public static String FIND_BY_C_PO_N_L_S_C_Z_R_C =
		OrganizationFinder.class.getName() + ".findByC_PO_N_L_S_C_Z_R_C";

	public static String JOIN_BY_GROUPS_PERMISSIONS =
		OrganizationFinder.class.getName() + ".joinByGroupsPermissions";

	public static String JOIN_BY_ORGANIZATIONS_GROUPS =
		OrganizationFinder.class.getName() + ".joinByOrganizationsGroups";

	public static String JOIN_BY_ORGANIZATIONS_PASSWORD_POLICIES =
		OrganizationFinder.class.getName() +
			".joinByOrganizationsPasswordPolicies";

	public static String JOIN_BY_ORGANIZATIONS_ROLES =
		OrganizationFinder.class.getName() + ".joinByOrganizationsRoles";

	public static String JOIN_BY_ORGANIZATIONS_USERS =
		OrganizationFinder.class.getName() + ".joinByOrganizationsUsers";

	public static String JOIN_BY_ORG_GROUP_PERMISSION =
		OrganizationFinder.class.getName() + ".joinByOrgGroupPermission";

	public int countByKeywords(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String keywords,
			int type, Long regionId, Long countryId,
			LinkedHashMap params)
		throws SystemException {

		String[] names = null;
		String[] streets = null;
		String[] cities = null;
		String[] zips = null;
		boolean andOperator = false;

		if (Validator.isNotNull(keywords)) {
			names = CustomSQLUtil.keywords(keywords);
			streets = CustomSQLUtil.keywords(keywords);
			cities = CustomSQLUtil.keywords(keywords);
			zips = CustomSQLUtil.keywords(keywords);
		}
		else {
			andOperator = true;
		}

		return countByC_PO_N_T_S_C_Z_R_C(
			companyId, parentOrganizationId, parentOrganizationComparator,
			names, type, streets, cities, zips, regionId, countryId, params,
			andOperator);
	}

	public int countByC_PO_N_T_S_C_Z_R_C(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String name, int type,
			String street, String city, String zip, Long regionId,
			Long countryId, LinkedHashMap params, boolean andOperator)
		throws SystemException {

		return countByC_PO_N_T_S_C_Z_R_C(
			companyId, parentOrganizationId, parentOrganizationComparator,
			new String[] {name}, type, new String[] {street},
			new String[] {city}, new String[] {zip}, regionId, countryId,
			params, andOperator);
	}

	public int countByC_PO_N_T_S_C_Z_R_C(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String[] names,
			int type, String[] streets, String[] cities, String[] zips,
			Long regionId, Long countryId, LinkedHashMap params,
			boolean andOperator)
		throws SystemException {

		names = CustomSQLUtil.keywords(names);
		streets = CustomSQLUtil.keywords(streets);
		cities = CustomSQLUtil.keywords(cities);
		zips = CustomSQLUtil.keywords(zips);

		if (params != null) {
			Long resourceId = (Long)params.get("permissionsResourceId");
			Long groupId = (Long)params.get("permissionsGroupId");

			if (Validator.isNotNull(groupId) &&
					Validator.isNotNull(resourceId)) {

				return countByPermissions(
					companyId, parentOrganizationId,
					parentOrganizationComparator, names, type, streets,
					cities, zips, regionId, countryId, resourceId.longValue(),
					groupId.longValue(), andOperator);
			}
		}

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = null;

			if (type == OrganizationImpl.TYPE_LOCATION ||
				type == OrganizationImpl.TYPE_REGULAR) {

				sql = CustomSQLUtil.get(COUNT_BY_C_PO_N_L_S_C_Z_R_C);
			}
			else {
				sql = CustomSQLUtil.get(COUNT_BY_C_PO_N_S_C_Z_R_C);
			}

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Organization_.name)", StringPool.LIKE, false,
				names);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street1)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street2)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street3)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.city)", StringPool.LIKE, false,
				cities);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.zip)", StringPool.LIKE, true,
				zips);

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));
			sql = StringUtil.replace(
				sql, "[$PARENT_ORGANIZATION_ID_COMPARATOR$]",
				parentOrganizationComparator);
			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(parentOrganizationId);

			if (type == OrganizationImpl.TYPE_LOCATION) {
				qPos.add(true);
			}
			else if (type == OrganizationImpl.TYPE_REGULAR) {
				qPos.add(false);
			}

			qPos.add(names, 2);
			qPos.add(streets, 6);

			if (regionId != null) {
				qPos.add(regionId);
				qPos.add(regionId);
			}

			if (countryId != null) {
				qPos.add(countryId);
				qPos.add(countryId);
			}

			qPos.add(cities, 2);
			qPos.add(zips, 2);

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
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String keywords,
			int type, Long regionId, Long countryId,
			LinkedHashMap params, int begin, int end, OrderByComparator obc)
		throws SystemException {

		String[] names = null;
		String[] streets = null;
		String[] cities = null;
		String[] zips = null;
		boolean andOperator = false;

		if (Validator.isNotNull(keywords)) {
			names = CustomSQLUtil.keywords(keywords);
			streets = CustomSQLUtil.keywords(keywords);
			cities = CustomSQLUtil.keywords(keywords);
			zips = CustomSQLUtil.keywords(keywords);
		}
		else {
			andOperator = true;
		}

		return findByC_PO_N_T_S_C_Z_R_C(
			companyId, parentOrganizationId, parentOrganizationComparator,
			names, type, streets, cities, zips, regionId, countryId, params,
			andOperator, begin, end, obc);
	}

	public List findByC_PO_N_T_S_C_Z_R_C(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String name, int type,
			String street, String city, String zip, Long regionId,
			Long countryId, LinkedHashMap params, boolean andOperator,
			int begin, int end, OrderByComparator obc)
		throws SystemException {

		return findByC_PO_N_T_S_C_Z_R_C(
			companyId, parentOrganizationId, parentOrganizationComparator,
			new String[] {name}, type, new String[] {street},
			new String[] {city}, new String[] {zip}, regionId, countryId,
			params, andOperator, begin, end, obc);
	}

	public List findByC_PO_N_T_S_C_Z_R_C(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String[] names,
			int type, String[] streets, String[] cities, String[] zips,
			Long regionId, Long countryId, LinkedHashMap params,
			boolean andOperator, int begin, int end, OrderByComparator obc)
		throws SystemException {

		names = CustomSQLUtil.keywords(names);
		streets = CustomSQLUtil.keywords(streets);
		cities = CustomSQLUtil.keywords(cities);
		zips = CustomSQLUtil.keywords(zips);

		if (params != null) {
			Long resourceId = (Long)params.get("permissionsResourceId");
			Long groupId = (Long)params.get("permissionsGroupId");

			if (Validator.isNotNull(groupId) &&
					Validator.isNotNull(resourceId)) {

				return findByPermissions(
					companyId, parentOrganizationId,
					parentOrganizationComparator, names, type, streets,
					cities, zips, regionId, countryId, resourceId.longValue(),
					groupId.longValue(), andOperator, begin, end, obc);
			}
		}

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = null;

			if (type == OrganizationImpl.TYPE_LOCATION ||
				type == OrganizationImpl.TYPE_REGULAR) {

				sql = CustomSQLUtil.get(FIND_BY_C_PO_N_L_S_C_Z_R_C);
			}
			else {
				sql = CustomSQLUtil.get(FIND_BY_C_PO_N_S_C_Z_R_C);
			}

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Organization_.name)", StringPool.LIKE, false,
				names);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street1)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street2)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street3)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.city)", StringPool.LIKE, false,
				cities);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.zip)", StringPool.LIKE, true,
				zips);

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(params));
			sql = StringUtil.replace(sql, "[$WHERE$]", getWhere(params));
			sql = StringUtil.replace(
				sql, "[$PARENT_ORGANIZATION_ID_COMPARATOR$]",
				parentOrganizationComparator);
			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);
			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar("orgId", Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, params);
			qPos.add(companyId);
			qPos.add(parentOrganizationId);

			if (type == OrganizationImpl.TYPE_LOCATION) {
				qPos.add(true);
			}
			else if (type == OrganizationImpl.TYPE_REGULAR) {
				qPos.add(false);
			}

			qPos.add(names, 2);
			qPos.add(streets, 6);

			if (regionId != null) {
				qPos.add(regionId);
				qPos.add(regionId);
			}

			if (countryId != null) {
				qPos.add(countryId);
				qPos.add(countryId);
			}

			qPos.add(cities, 2);
			qPos.add(zips, 2);

			List list = new ArrayList();

			Iterator itr = QueryUtil.iterate(
				q, HibernateUtil.getDialect(), begin, end);

			while (itr.hasNext()) {
				Long organizationId = (Long)itr.next();

				Organization organization = OrganizationUtil.findByPrimaryKey(
					organizationId.longValue());

				list.add(organization);
			}

			return list;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	protected int countByPermissions(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String[] names,
			int type, String[] streets, String[] cities, String[] zips,
			Long regionId, Long countryId, long resourceId, long groupId,
			boolean andOperator)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			StringMaker sm = new StringMaker();

			sm.append("(");

			if (type == OrganizationImpl.TYPE_LOCATION ||
				type == OrganizationImpl.TYPE_REGULAR) {

				sm.append(CustomSQLUtil.get(COUNT_BY_C_PO_N_L_S_C_Z_R_C));
			}
			else {
				sm.append(CustomSQLUtil.get(COUNT_BY_C_PO_N_S_C_Z_R_C));
			}

			String sql = sm.toString();

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(
				sql, "[$JOIN$]", getJoin("groupsPermissions"));
			sql = StringUtil.replace(
				sql, "[$WHERE$]", getWhere("groupsPermissions"));

			sm = new StringMaker();

			sm.append(sql);

			sm.append(") UNION (");

			if (type == OrganizationImpl.TYPE_LOCATION ||
				type == OrganizationImpl.TYPE_REGULAR) {

				sm.append(CustomSQLUtil.get(COUNT_BY_C_PO_N_L_S_C_Z_R_C));
			}
			else {
				sm.append(CustomSQLUtil.get(COUNT_BY_C_PO_N_S_C_Z_R_C));
			}

			sql = sm.toString();

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(
				sql, "[$JOIN$]", getJoin("orgGroupPermission"));
			sql = StringUtil.replace(
				sql, "[$WHERE$]", getWhere("orgGroupPermission"));
			sql = StringUtil.replace(
				sql, "[$PARENT_ORGANIZATION_ID_COMPARATOR$]",
				parentOrganizationComparator);
			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);

			sm = new StringMaker();

			sm.append(sql);

			sm.append(")");

			sql = sm.toString();

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Organization_.name)", StringPool.LIKE, false,
				names);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street1)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street2)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street3)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.city)", StringPool.LIKE, false,
				cities);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.zip)", StringPool.LIKE, true,
				zips);

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			for (int i = 0; i < 2; i++) {
				qPos.add(resourceId);

				if (i == 1) {
					qPos.add(groupId);
				}

				qPos.add(companyId);
				qPos.add(parentOrganizationId);

				if (type == OrganizationImpl.TYPE_LOCATION) {
					qPos.add(true);
				}
				else if (type == OrganizationImpl.TYPE_REGULAR) {
					qPos.add(false);
				}

				qPos.add(names, 2);
				qPos.add(streets, 6);

				if (regionId != null) {
					qPos.add(regionId);
					qPos.add(regionId);
				}

				if (countryId != null) {
					qPos.add(countryId);
					qPos.add(countryId);
				}

				qPos.add(cities, 2);
				qPos.add(zips, 2);
			}

			int count = 0;

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				Long l = (Long)itr.next();

				if (l != null) {
					count += l.intValue();
				}
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

	protected List findByPermissions(
			long companyId, long parentOrganizationId,
			String parentOrganizationComparator, String[] names,
			int type, String[] streets, String[] cities, String[] zips,
			Long regionId, Long countryId, long resourceId, long groupId,
			boolean andOperator, int begin, int end, OrderByComparator obc)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			StringMaker sm = new StringMaker();

			sm.append("(");

			if (type == OrganizationImpl.TYPE_LOCATION ||
				type == OrganizationImpl.TYPE_REGULAR) {

				sm.append(CustomSQLUtil.get(FIND_BY_C_PO_N_L_S_C_Z_R_C));
			}
			else {
				sm.append(CustomSQLUtil.get(FIND_BY_C_PO_N_S_C_Z_R_C));
			}

			String sql = sm.toString();

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(
				sql, "[$JOIN$]", getJoin("groupsPermissions"));
			sql = StringUtil.replace(
				sql, "[$WHERE$]", getWhere("groupsPermissions"));

			sm = new StringMaker();

			sm.append(sql);

			sm.append(") UNION (");

			if (type == OrganizationImpl.TYPE_LOCATION ||
				type == OrganizationImpl.TYPE_REGULAR) {

				sm.append(CustomSQLUtil.get(FIND_BY_C_PO_N_L_S_C_Z_R_C));
			}
			else {
				sm.append(CustomSQLUtil.get(FIND_BY_C_PO_N_S_C_Z_R_C));
			}

			sql = sm.toString();

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = StringUtil.replace(
				sql, "[$JOIN$]", getJoin("orgGroupPermission"));
			sql = StringUtil.replace(
				sql, "[$WHERE$]", getWhere("orgGroupPermission"));
			sql = StringUtil.replace(
				sql, "[$PARENT_ORGANIZATION_ID_COMPARATOR$]",
				parentOrganizationComparator);
			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);

			sm = new StringMaker();

			sm.append(sql);

			sm.append(") ");

			sql = sm.toString();

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Organization_.name)", StringPool.LIKE, false,
				names);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street1)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street2)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.street3)", StringPool.LIKE, true,
				streets);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.city)", StringPool.LIKE, false,
				cities);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(Address.zip)", StringPool.LIKE, true,
				zips);

			if (regionId == null) {
				sql = StringUtil.replace(sql, REGION_ID_SQL, StringPool.BLANK);
			}

			if (countryId == null) {
				sql = StringUtil.replace(sql, COUNTRY_ID_SQL, StringPool.BLANK);
			}

			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar("orgId", Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			for (int i = 0; i < 2; i++) {
				qPos.add(resourceId);

				if (i == 1) {
					qPos.add(groupId);
				}

				qPos.add(companyId);
				qPos.add(parentOrganizationId);

				if (type == OrganizationImpl.TYPE_LOCATION) {
					qPos.add(true);
				}
				else if (type == OrganizationImpl.TYPE_REGULAR) {
					qPos.add(false);
				}

				qPos.add(names, 2);
				qPos.add(streets, 6);

				if (regionId != null) {
					qPos.add(regionId);
					qPos.add(regionId);
				}

				if (countryId != null) {
					qPos.add(countryId);
					qPos.add(countryId);
				}

				qPos.add(cities, 2);
				qPos.add(zips, 2);
			}

			List list = new ArrayList();

			Iterator itr = QueryUtil.iterate(
				q, HibernateUtil.getDialect(), begin, end);

			while (itr.hasNext()) {
				Long organizationId = (Long)itr.next();

				Organization organization = OrganizationUtil.findByPrimaryKey(
					organizationId.longValue());

				list.add(organization);
			}

			return list;
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

		if (key.equals("groupsPermissions")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_PERMISSIONS);
		}
		else if (key.equals("organizationsGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_GROUPS);
		}
		else if (key.equals("organizationsPasswordPolicies")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_PASSWORD_POLICIES);
		}
		else if (key.equals("organizationsRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_ROLES);
		}
		else if (key.equals("organizationsUsers")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_USERS);
		}
		else if (key.equals("orgGroupPermission")) {
			join = CustomSQLUtil.get(JOIN_BY_ORG_GROUP_PERMISSION);
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

	protected String getWhere(String key) {
		return getWhere(key, null);
	}

	protected String getWhere(String key, Object value) {
		String join = StringPool.BLANK;

		if (key.equals("groupsPermissions")) {
			join = CustomSQLUtil.get(JOIN_BY_GROUPS_PERMISSIONS);
		}
		else if (key.equals("organizations")) {
			Long[] organizationIds = (Long[])value;

			StringMaker sm = new StringMaker();

			sm.append("WHERE (");

			for (int i = 0; i < organizationIds.length; i++) {
				sm.append("(Organization_.organizationId = ?) ");

				if ((i + 1) < organizationIds.length) {
					sm.append("OR ");
				}
			}

			sm.append(")");

			join = sm.toString();
		}
		else if (key.equals("organizationsGroups")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_GROUPS);
		}
		else if (key.equals("organizationsPasswordPolicies")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_PASSWORD_POLICIES);
		}
		else if (key.equals("organizationsRoles")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_ROLES);
		}
		else if (key.equals("organizationsUsers")) {
			join = CustomSQLUtil.get(JOIN_BY_ORGANIZATIONS_USERS);
		}
		else if (key.equals("orgGroupPermission")) {
			join = CustomSQLUtil.get(JOIN_BY_ORG_GROUP_PERMISSION);
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
			}
		}
	}

	protected static String COUNTRY_ID_SQL =
		"((Organization_.countryId = ?) OR (Address.countryId = ?)) " +
			"[$AND_OR_CONNECTOR$]";

	protected static String REGION_ID_SQL =
		"((Organization_.regionId = ?) OR (Address.regionId = ?)) " +
			"[$AND_OR_CONNECTOR$]";

}