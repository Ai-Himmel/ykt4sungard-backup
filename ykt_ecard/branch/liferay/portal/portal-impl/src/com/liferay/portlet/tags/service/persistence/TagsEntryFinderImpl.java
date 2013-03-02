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

package com.liferay.portlet.tags.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portlet.tags.model.impl.TagsEntryImpl;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.Iterator;
import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="TagsEntryFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsEntryFinderImpl implements TagsEntryFinder {

	public static String COUNT_BY_C_N_P =
		TagsEntryFinder.class.getName() + ".countByC_N_P";

	public static String FIND_BY_C_N_P =
		TagsEntryFinder.class.getName() + ".findByC_N_P";

	public int countByC_N_P(long companyId, String name, String[] properties)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(COUNT_BY_C_N_P);

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(properties));

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, properties);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(name);

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

	public List findByC_N_P(long companyId, String name, String[] properties)
		throws SystemException {

		return findByC_N_P(
			companyId, name, properties, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List findByC_N_P(
			long companyId, String name, String[] properties, int begin,
			int end)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_C_N_P);

			sql = StringUtil.replace(sql, "[$JOIN$]", getJoin(properties));

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("TagsEntry", TagsEntryImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			setJoin(qPos, properties);
			qPos.add(companyId);
			qPos.add(name);
			qPos.add(name);

			return QueryUtil.list(q, HibernateUtil.getDialect(), begin, end);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	protected String getJoin(String[] properties) {
		if (properties.length == 0) {
			return StringPool.BLANK;
		}
		else {
			StringMaker sm = new StringMaker();

			sm.append(" INNER JOIN TagsProperty ON ");
			sm.append(" (TagsProperty.entryId = TagsEntry.entryId) AND ");

			for (int i = 0; i < properties.length; i++) {
				sm.append("(TagsProperty.key_ = ? AND ");
				sm.append("TagsProperty.value = ?) ");

				if ((i + 1) < properties.length) {
					sm.append(" AND ");
				}
			}

			return sm.toString();
		}
	}

	protected void setJoin(QueryPos qPos, String[] properties) {
		for (int i = 0; i < properties.length; i++) {
			String[] property = StringUtil.split(
				properties[i], StringPool.COLON);

			String key = StringPool.BLANK;

			if (property.length > 0) {
				key = GetterUtil.getString(property[0]);
			}

			String value = StringPool.BLANK;

			if (property.length > 1) {
				value = GetterUtil.getString(property[1]);
			}

			qPos.add(key);
			qPos.add(value);
		}
	}

}