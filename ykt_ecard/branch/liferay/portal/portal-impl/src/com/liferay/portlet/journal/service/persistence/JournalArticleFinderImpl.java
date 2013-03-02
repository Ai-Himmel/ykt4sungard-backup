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

package com.liferay.portlet.journal.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portlet.journal.model.impl.JournalArticleImpl;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.sql.Timestamp;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="JournalArticleFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleFinderImpl implements JournalArticleFinder {

	public static String COUNT_BY_C_G_A_V_T_D_C_T_S_T_D_A_E_R =
		JournalArticleFinder.class.getName() +
			".countByC_G_A_V_T_D_C_T_S_T_D_A_E_R";

	public static String FIND_BY_EXPIRATION_DATE =
		JournalArticleFinder.class.getName() + ".findByExpirationDate";

	public static String FIND_BY_REVIEW_DATE =
		JournalArticleFinder.class.getName() + ".findByReviewDate";

	public static String FIND_BY_C_G_A_V_T_D_C_T_S_T_D_A_E_R =
		JournalArticleFinder.class.getName() +
			".findByC_G_A_V_T_D_C_T_S_T_D_A_E_R";

	public int countByKeywords(
			long companyId, long groupId, String keywords, Double version,
			String type, String structureId, String templateId,
			Date displayDateGT, Date displayDateLT, Boolean approved,
			Boolean expired, Date reviewDate)
		throws SystemException {

		String[] articleIds = null;
		String[] titles = null;
		String[] descriptions = null;
		String[] contents = null;
		boolean andOperator = false;

		if (Validator.isNotNull(keywords)) {
			articleIds = CustomSQLUtil.keywords(keywords, false);
			titles = CustomSQLUtil.keywords(keywords);
			descriptions = CustomSQLUtil.keywords(keywords, false);
			contents = CustomSQLUtil.keywords(keywords, false);
		}
		else {
			andOperator = true;
		}

		return countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			companyId, groupId, articleIds, version, titles, descriptions,
			contents, type, new String[] {structureId},
			new String[] {templateId}, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator);
	}

	public int countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			long companyId, long groupId, String articleId, Double version,
			String title, String description, String content, String type,
			String structureId, String templateId, Date displayDateGT,
			Date displayDateLT, Boolean approved, Boolean expired,
			Date reviewDate, boolean andOperator)
		throws SystemException {

		return countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			companyId, groupId, articleId, version, title, description,
			content, type, new String[] {structureId},
			new String[] {templateId}, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator);
	}

	public int countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			long companyId, long groupId, String articleId, Double version,
			String title, String description, String content, String type,
			String[] structureIds, String[] templateIds, Date displayDateGT,
			Date displayDateLT, Boolean approved, Boolean expired,
			Date reviewDate, boolean andOperator)
		throws SystemException {

		return countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			companyId, groupId, new String[] {articleId}, version,
			new String[] {title}, new String[] {description},
			new String[] {content}, type, structureIds, templateIds,
			displayDateGT, displayDateLT, approved, expired, reviewDate,
			andOperator);
	}

	public int countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			long companyId, long groupId, String[] articleIds, Double version,
			String[] titles, String[] descriptions, String[] contents,
			String type, String[] structureIds, String[] templateIds,
			Date displayDateGT, Date displayDateLT, Boolean approved,
			Boolean expired, Date reviewDate, boolean andOperator)
		throws SystemException {

		articleIds = CustomSQLUtil.keywords(articleIds, false);
		titles = CustomSQLUtil.keywords(titles);
		descriptions = CustomSQLUtil.keywords(descriptions, false);
		contents = CustomSQLUtil.keywords(contents, false);
		structureIds = CustomSQLUtil.keywords(structureIds, false);
		templateIds = CustomSQLUtil.keywords(templateIds, false);
		Timestamp displayDateGT_TS = CalendarUtil.getTimestamp(displayDateGT);
		Timestamp displayDateLT_TS = CalendarUtil.getTimestamp(displayDateLT);
		Timestamp reviewDate_TS = CalendarUtil.getTimestamp(reviewDate);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(
				COUNT_BY_C_G_A_V_T_D_C_T_S_T_D_A_E_R);

			if (groupId <= 0) {
				sql = StringUtil.replace(sql, "(groupId = ?) AND", "");
			}

			sql = CustomSQLUtil.replaceKeywords(
				sql, "articleId", StringPool.LIKE, false, articleIds);

			if (version == null) {
				sql = StringUtil.replace(
					sql, "(version = ?) [$AND_OR_CONNECTOR$]", "");
			}

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(title)", StringPool.LIKE, false, titles);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "description", StringPool.LIKE, false, descriptions);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "content", StringPool.LIKE, false, contents);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "structureId", StringPool.EQUAL, false, structureIds);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "templateId", StringPool.EQUAL, false, templateIds);

			if (approved == null) {
				sql = StringUtil.replace(sql, "(approved = ?) AND", "");
			}

			if (expired == null) {
				sql = StringUtil.replace(sql, "(expired = ?) AND", "");
			}

			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);

			SQLQuery q = session.createSQLQuery(sql);

			q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(companyId);

			if (groupId > 0) {
				qPos.add(groupId);
			}

			qPos.add(articleIds, 2);

			if (version != null) {
				qPos.add(version);
			}

			qPos.add(titles, 2);
			qPos.add(descriptions, 2);
			qPos.add(contents, 2);
			qPos.add(type);
			qPos.add(type);
			qPos.add(structureIds, 2);
			qPos.add(templateIds, 2);
			qPos.add(displayDateGT_TS);
			qPos.add(displayDateGT_TS);
			qPos.add(displayDateLT_TS);
			qPos.add(displayDateLT_TS);

			if (approved != null) {
				qPos.add(approved);
			}

			if (expired != null) {
				qPos.add(expired);
			}

			qPos.add(reviewDate_TS);
			qPos.add(reviewDate_TS);

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

	public List findByExpirationDate(
			Boolean expired, Date expirationDateLT, Date expirationDateGT)
		throws SystemException {

		Timestamp expirationDateLT_TS = CalendarUtil.getTimestamp(
			expirationDateLT);
		Timestamp expirationDateGT_TS = CalendarUtil.getTimestamp(
			expirationDateGT);

		Session session = null;
		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_EXPIRATION_DATE);

			if (expired == null) {
				sql = StringUtil.replace(sql, "(expired = ?) AND", "");
			}

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("JournalArticle", JournalArticleImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			if (expired != null) {
				qPos.add(expired);
			}

			qPos.add(expirationDateGT_TS);
			qPos.add(expirationDateLT_TS);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByKeywords(
			long companyId, long groupId, String keywords, Double version,
			String type, String structureId, String templateId,
			Date displayDateGT, Date displayDateLT, Boolean approved,
			Boolean expired, Date reviewDate, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		String[] articleIds = null;
		String[] titles = null;
		String[] descriptions = null;
		String[] contents = null;
		boolean andOperator = false;

		if (Validator.isNotNull(keywords)) {
			articleIds = CustomSQLUtil.keywords(keywords, false);
			titles = CustomSQLUtil.keywords(keywords);
			descriptions = CustomSQLUtil.keywords(keywords, false);
			contents = CustomSQLUtil.keywords(keywords, false);
		}
		else {
			andOperator = true;
		}

		return findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			companyId, groupId, articleIds, version, titles, descriptions,
			contents, type, new String[] {structureId},
			new String[] {templateId}, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator, begin, end, obc);
	}

	public List findByReviewDate(Date reviewDateLT, Date reviewDateGT)
		throws SystemException {

		Timestamp reviewDateLT_TS = CalendarUtil.getTimestamp(reviewDateLT);
		Timestamp reviewDateGT_TS = CalendarUtil.getTimestamp(reviewDateGT);

		Session session = null;
		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_REVIEW_DATE);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("JournalArticle", JournalArticleImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(reviewDateGT_TS);
			qPos.add(reviewDateLT_TS);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			long companyId, long groupId, String articleId, Double version,
			String title, String description, String content, String type,
			String structureId, String templateId, Date displayDateGT,
			Date displayDateLT, Boolean approved, Boolean expired,
			Date reviewDate, boolean andOperator, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		return findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			companyId, groupId, articleId, version, title, description,
			content, type, new String[] {structureId},
			new String[] {templateId}, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator, begin, end, obc);
	}

	public List findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			long companyId, long groupId, String articleId, Double version,
			String title, String description, String content, String type,
			String[] structureIds, String[] templateIds, Date displayDateGT,
			Date displayDateLT, Boolean approved, Boolean expired,
			Date reviewDate, boolean andOperator, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		return findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			companyId, groupId, new String[] {articleId}, version,
			new String[] {title}, new String[] {description},
			new String[] {content}, type, structureIds, templateIds,
			displayDateGT, displayDateLT, approved, expired, reviewDate,
			andOperator, begin, end, obc);
	}

	public List findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
			long companyId, long groupId, String[] articleIds, Double version,
			String[] titles, String[] descriptions, String[] contents,
			String type, String[] structureIds, String[] templateIds,
			Date displayDateGT, Date displayDateLT, Boolean approved,
			Boolean expired, Date reviewDate, boolean andOperator, int begin,
			int end, OrderByComparator obc)
		throws SystemException {

		articleIds = CustomSQLUtil.keywords(articleIds, false);
		titles = CustomSQLUtil.keywords(titles);
		descriptions = CustomSQLUtil.keywords(descriptions, false);
		contents = CustomSQLUtil.keywords(contents, false);
		structureIds = CustomSQLUtil.keywords(structureIds, false);
		templateIds = CustomSQLUtil.keywords(templateIds, false);
		Timestamp displayDateGT_TS = CalendarUtil.getTimestamp(displayDateGT);
		Timestamp displayDateLT_TS = CalendarUtil.getTimestamp(displayDateLT);
		Timestamp reviewDate_TS = CalendarUtil.getTimestamp(reviewDate);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_C_G_A_V_T_D_C_T_S_T_D_A_E_R);

			if (groupId <= 0) {
				sql = StringUtil.replace(sql, "(groupId = ?) AND", "");
			}

			sql = CustomSQLUtil.replaceKeywords(
				sql, "articleId", StringPool.LIKE, false, articleIds);

			if (version == null) {
				sql = StringUtil.replace(
					sql, "(version = ?) [$AND_OR_CONNECTOR$]", "");
			}

			sql = CustomSQLUtil.replaceKeywords(
				sql, "lower(title)", StringPool.LIKE, false, titles);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "description", StringPool.LIKE, false, descriptions);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "content", StringPool.LIKE, false, contents);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "structureId", StringPool.EQUAL, false, structureIds);
			sql = CustomSQLUtil.replaceKeywords(
				sql, "templateId", StringPool.EQUAL, false, templateIds);

			if (approved == null) {
				sql = StringUtil.replace(sql, "(approved = ?) AND", "");
			}

			if (expired == null) {
				sql = StringUtil.replace(sql, "(expired = ?) AND", "");
			}

			sql = CustomSQLUtil.replaceAndOperator(sql, andOperator);
			sql = CustomSQLUtil.replaceOrderBy(sql, obc);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("JournalArticle", JournalArticleImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(companyId);

			if (groupId > 0) {
				qPos.add(groupId);
			}

			qPos.add(articleIds, 2);

			if (version != null) {
				qPos.add(version);
			}

			qPos.add(titles, 2);
			qPos.add(descriptions, 2);
			qPos.add(contents, 2);
			qPos.add(type);
			qPos.add(type);
			qPos.add(structureIds, 2);
			qPos.add(templateIds, 2);
			qPos.add(displayDateGT_TS);
			qPos.add(displayDateGT_TS);
			qPos.add(displayDateLT_TS);
			qPos.add(displayDateLT_TS);

			if (approved != null) {
				qPos.add(approved);
			}

			if (expired != null) {
				qPos.add(expired);
			}

			qPos.add(reviewDate_TS);
			qPos.add(reviewDate_TS);

			return QueryUtil.list(q, HibernateUtil.getDialect(), begin, end);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

}