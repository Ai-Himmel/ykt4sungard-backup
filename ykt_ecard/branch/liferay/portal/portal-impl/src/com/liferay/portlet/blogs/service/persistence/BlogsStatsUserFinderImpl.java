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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portlet.blogs.model.impl.BlogsStatsUserImpl;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="BlogsStatsUserFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsStatsUserFinderImpl implements BlogsStatsUserFinder {

	public static String COUNT_BY_ORGANIZATION_IDS =
		BlogsStatsUserFinder.class.getName() + ".countByOrganizationIds";

	public static String FIND_BY_ORGANIZATION_IDS =
		BlogsStatsUserFinder.class.getName() + ".findByOrganizationIds";

	public int countByOrganizationId(long organizationId)
		throws SystemException {

		List organizationIds = new ArrayList();

		organizationIds.add(new Long(organizationId));

		return countByOrganizationIds(organizationIds);
	}

	public int countByOrganizationIds(List organizationIds)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_ORGANIZATION_IDS);

			sql = StringUtil.replace(
				sql, "[$ORGANIZATION_ID$]",
				getOrganizationIds(organizationIds));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			for (int i = 0; i < organizationIds.size(); i++) {
				Long organizationId = (Long)organizationIds.get(i);

				qPos.add(organizationId);
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

	public List findByOrganizationId(
			long organizationId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		List organizationIds = new ArrayList();

		organizationIds.add(new Long(organizationId));

		return findByOrganizationIds(organizationIds, begin, end, obc);
	}

	public List findByOrganizationIds(
			List organizationIds, int begin, int end, OrderByComparator obc)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_ORGANIZATION_IDS);

			sql = StringUtil.replace(
				sql, "[$ORGANIZATION_ID$]",
				getOrganizationIds(organizationIds));
			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("BlogsStatsUser", BlogsStatsUserImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			for (int i = 0; i < organizationIds.size(); i++) {
				Long organizationId = (Long)organizationIds.get(i);

				qPos.add(organizationId);
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

	protected String getOrganizationIds(List organizationIds) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < organizationIds.size(); i++) {
			sm.append("Users_Orgs.organizationId = ? ");

			if ((i + 1) != organizationIds.size()) {
				sm.append("OR ");
			}
		}

		return sm.toString();
	}

}