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
 * <a href="JournalArticleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleUtil {
	public static com.liferay.portlet.journal.model.JournalArticle create(
		long id) {
		return getPersistence().create(id);
	}

	public static com.liferay.portlet.journal.model.JournalArticle remove(
		long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().remove(id);
	}

	public static com.liferay.portlet.journal.model.JournalArticle remove(
		com.liferay.portlet.journal.model.JournalArticle journalArticle)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(journalArticle);
	}

	public static com.liferay.portlet.journal.model.JournalArticle update(
		com.liferay.portlet.journal.model.JournalArticle journalArticle)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(journalArticle);
	}

	public static com.liferay.portlet.journal.model.JournalArticle update(
		com.liferay.portlet.journal.model.JournalArticle journalArticle,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(journalArticle, merge);
	}

	public static com.liferay.portlet.journal.model.JournalArticle updateImpl(
		com.liferay.portlet.journal.model.JournalArticle journalArticle,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(journalArticle, merge);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByPrimaryKey(
		long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByPrimaryKey(id);
	}

	public static com.liferay.portlet.journal.model.JournalArticle fetchByPrimaryKey(
		long id) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(id);
	}

	public static java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByUuid_PrevAndNext(
		long id, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByUuid_PrevAndNext(id, uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.journal.model.JournalArticle fetchByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByUUID_G(uuid, groupId);
	}

	public static java.util.List findByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByGroupId_PrevAndNext(
		long id, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByGroupId_PrevAndNext(id, groupId, obc);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByCompanyId_PrevAndNext(
		long id, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByCompanyId_PrevAndNext(id, companyId, obc);
	}

	public static java.util.List findBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySmallImageId(smallImageId);
	}

	public static java.util.List findBySmallImageId(long smallImageId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findBySmallImageId(smallImageId, begin, end);
	}

	public static java.util.List findBySmallImageId(long smallImageId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySmallImageId(smallImageId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findBySmallImageId_First(
		long smallImageId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findBySmallImageId_First(smallImageId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findBySmallImageId_Last(
		long smallImageId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findBySmallImageId_Last(smallImageId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findBySmallImageId_PrevAndNext(
		long id, long smallImageId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findBySmallImageId_PrevAndNext(id,
			smallImageId, obc);
	}

	public static java.util.List findByG_A(long groupId,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, articleId);
	}

	public static java.util.List findByG_A(long groupId,
		java.lang.String articleId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, articleId, begin, end);
	}

	public static java.util.List findByG_A(long groupId,
		java.lang.String articleId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, articleId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_A_First(
		long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_First(groupId, articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_A_Last(
		long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_Last(groupId, articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByG_A_PrevAndNext(
		long id, long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_PrevAndNext(id, groupId, articleId,
			obc);
	}

	public static java.util.List findByG_S(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_S(groupId, structureId);
	}

	public static java.util.List findByG_S(long groupId,
		java.lang.String structureId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_S(groupId, structureId, begin, end);
	}

	public static java.util.List findByG_S(long groupId,
		java.lang.String structureId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_S(groupId, structureId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_S_First(
		long groupId, java.lang.String structureId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_S_First(groupId, structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_S_Last(
		long groupId, java.lang.String structureId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_S_Last(groupId, structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByG_S_PrevAndNext(
		long id, long groupId, java.lang.String structureId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_S_PrevAndNext(id, groupId, structureId,
			obc);
	}

	public static java.util.List findByG_T(long groupId,
		java.lang.String templateId) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_T(groupId, templateId);
	}

	public static java.util.List findByG_T(long groupId,
		java.lang.String templateId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_T(groupId, templateId, begin, end);
	}

	public static java.util.List findByG_T(long groupId,
		java.lang.String templateId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_T(groupId, templateId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_T_First(
		long groupId, java.lang.String templateId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_T_First(groupId, templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_T_Last(
		long groupId, java.lang.String templateId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_T_Last(groupId, templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByG_T_PrevAndNext(
		long id, long groupId, java.lang.String templateId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_T_PrevAndNext(id, groupId, templateId,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_A_V(
		long groupId, java.lang.String articleId, double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_V(groupId, articleId, version);
	}

	public static com.liferay.portlet.journal.model.JournalArticle fetchByG_A_V(
		long groupId, java.lang.String articleId, double version)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_A_V(groupId, articleId, version);
	}

	public static java.util.List findByG_A_A(long groupId,
		java.lang.String articleId, boolean approved)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A_A(groupId, articleId, approved);
	}

	public static java.util.List findByG_A_A(long groupId,
		java.lang.String articleId, boolean approved, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A_A(groupId, articleId, approved,
			begin, end);
	}

	public static java.util.List findByG_A_A(long groupId,
		java.lang.String articleId, boolean approved, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A_A(groupId, articleId, approved,
			begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_A_A_First(
		long groupId, java.lang.String articleId, boolean approved,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_A_First(groupId, articleId, approved,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByG_A_A_Last(
		long groupId, java.lang.String articleId, boolean approved,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_A_Last(groupId, articleId, approved,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByG_A_A_PrevAndNext(
		long id, long groupId, java.lang.String articleId, boolean approved,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		return getPersistence().findByG_A_A_PrevAndNext(id, groupId, articleId,
			approved, obc);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUuid(uuid);
	}

	public static void removeByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeBySmallImageId(smallImageId);
	}

	public static void removeByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_A(groupId, articleId);
	}

	public static void removeByG_S(long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_S(groupId, structureId);
	}

	public static void removeByG_T(long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_T(groupId, templateId);
	}

	public static void removeByG_A_V(long groupId, java.lang.String articleId,
		double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleException {
		getPersistence().removeByG_A_V(groupId, articleId, version);
	}

	public static void removeByG_A_A(long groupId, java.lang.String articleId,
		boolean approved) throws com.liferay.portal.SystemException {
		getPersistence().removeByG_A_A(groupId, articleId, approved);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUUID_G(uuid, groupId);
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countBySmallImageId(smallImageId);
	}

	public static int countByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A(groupId, articleId);
	}

	public static int countByG_S(long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_S(groupId, structureId);
	}

	public static int countByG_T(long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_T(groupId, templateId);
	}

	public static int countByG_A_V(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A_V(groupId, articleId, version);
	}

	public static int countByG_A_A(long groupId, java.lang.String articleId,
		boolean approved) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A_A(groupId, articleId, approved);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static JournalArticlePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(JournalArticlePersistence persistence) {
		_persistence = persistence;
	}

	private static JournalArticleUtil _getUtil() {
		if (_util == null) {
			_util = (JournalArticleUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = JournalArticleUtil.class.getName();
	private static JournalArticleUtil _util;
	private JournalArticlePersistence _persistence;
}