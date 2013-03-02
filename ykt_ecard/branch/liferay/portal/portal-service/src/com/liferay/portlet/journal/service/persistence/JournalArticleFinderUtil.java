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

/**
 * <a href="JournalArticleFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleFinderUtil {
	public static int countByKeywords(long companyId, long groupId,
		java.lang.String keywords, java.lang.Double version,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate)
		throws com.liferay.portal.SystemException {
		return getFinder().countByKeywords(companyId, groupId, keywords,
			version, type, structureId, templateId, displayDateGT,
			displayDateLT, approved, expired, reviewDate);
	}

	public static int countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(long companyId,
		long groupId, java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(companyId,
			groupId, articleId, version, title, description, content, type,
			structureId, templateId, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator);
	}

	public static int countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(long companyId,
		long groupId, java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String[] structureIds, java.lang.String[] templateIds,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(companyId,
			groupId, articleId, version, title, description, content, type,
			structureIds, templateIds, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator);
	}

	public static int countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(long companyId,
		long groupId, java.lang.String[] articleIds, java.lang.Double version,
		java.lang.String[] titles, java.lang.String[] descriptions,
		java.lang.String[] contents, java.lang.String type,
		java.lang.String[] structureIds, java.lang.String[] templateIds,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_G_A_V_T_D_C_T_S_T_D_A_E_R(companyId,
			groupId, articleIds, version, titles, descriptions, contents, type,
			structureIds, templateIds, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator);
	}

	public static java.util.List findByExpirationDate(
		java.lang.Boolean expired, java.util.Date expirationDateLT,
		java.util.Date expirationDateGT)
		throws com.liferay.portal.SystemException {
		return getFinder().findByExpirationDate(expired, expirationDateLT,
			expirationDateGT);
	}

	public static java.util.List findByKeywords(long companyId, long groupId,
		java.lang.String keywords, java.lang.Double version,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByKeywords(companyId, groupId, keywords,
			version, type, structureId, templateId, displayDateGT,
			displayDateLT, approved, expired, reviewDate, begin, end, obc);
	}

	public static java.util.List findByReviewDate(java.util.Date reviewDateLT,
		java.util.Date reviewDateGT) throws com.liferay.portal.SystemException {
		return getFinder().findByReviewDate(reviewDateLT, reviewDateGT);
	}

	public static java.util.List findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
		long companyId, long groupId, java.lang.String articleId,
		java.lang.Double version, java.lang.String title,
		java.lang.String description, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate,
		boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(companyId,
			groupId, articleId, version, title, description, content, type,
			structureId, templateId, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator, begin, end, obc);
	}

	public static java.util.List findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
		long companyId, long groupId, java.lang.String articleId,
		java.lang.Double version, java.lang.String title,
		java.lang.String description, java.lang.String content,
		java.lang.String type, java.lang.String[] structureIds,
		java.lang.String[] templateIds, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate,
		boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(companyId,
			groupId, articleId, version, title, description, content, type,
			structureIds, templateIds, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator, begin, end, obc);
	}

	public static java.util.List findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(
		long companyId, long groupId, java.lang.String[] articleIds,
		java.lang.Double version, java.lang.String[] titles,
		java.lang.String[] descriptions, java.lang.String[] contents,
		java.lang.String type, java.lang.String[] structureIds,
		java.lang.String[] templateIds, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate,
		boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_G_A_V_T_D_C_T_S_T_D_A_E_R(companyId,
			groupId, articleIds, version, titles, descriptions, contents, type,
			structureIds, templateIds, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator, begin, end, obc);
	}

	public static JournalArticleFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(JournalArticleFinder finder) {
		_finder = finder;
	}

	private static JournalArticleFinderUtil _getUtil() {
		if (_util == null) {
			_util = (JournalArticleFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = JournalArticleFinderUtil.class.getName();
	private static JournalArticleFinderUtil _util;
	private JournalArticleFinder _finder;
}