/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JournalArticleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalArticleUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.journal.model.JournalArticle"),
			"com.liferay.portlet.journal.service.persistence.JournalArticlePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.journal.model.JournalArticle"));

	public static com.liferay.portlet.journal.model.JournalArticle create(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK) {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(journalArticlePK);
	}

	public static com.liferay.portlet.journal.model.JournalArticle remove(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(journalArticlePK));
		}

		com.liferay.portlet.journal.model.JournalArticle journalArticle = persistence.remove(journalArticlePK);

		if (listener != null) {
			listener.onAfterRemove(journalArticle);
		}

		return journalArticle;
	}

	public static com.liferay.portlet.journal.model.JournalArticle update(
		com.liferay.portlet.journal.model.JournalArticle journalArticle)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = journalArticle.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(journalArticle);
			}
			else {
				listener.onBeforeUpdate(journalArticle);
			}
		}

		journalArticle = persistence.update(journalArticle);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(journalArticle);
			}
			else {
				listener.onAfterUpdate(journalArticle);
			}
		}

		return journalArticle;
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByPrimaryKey(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(journalArticlePK);
	}

	public static java.util.List findByArticleId(java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByArticleId(articleId);
	}

	public static java.util.List findByArticleId(java.lang.String articleId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByArticleId(articleId, begin, end);
	}

	public static java.util.List findByArticleId(java.lang.String articleId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByArticleId(articleId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByArticleId_First(
		java.lang.String articleId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByArticleId_First(articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByArticleId_Last(
		java.lang.String articleId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByArticleId_Last(articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByArticleId_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String articleId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByArticleId_PrevAndNext(journalArticlePK,
			articleId, obc);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByGroupId_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(journalArticlePK, groupId,
			obc);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByCompanyId_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(journalArticlePK,
			companyId, obc);
	}

	public static java.util.List findByStructureId(java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId(structureId);
	}

	public static java.util.List findByStructureId(
		java.lang.String structureId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId(structureId, begin, end);
	}

	public static java.util.List findByStructureId(
		java.lang.String structureId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId(structureId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByStructureId_First(
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId_First(structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByStructureId_Last(
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId_Last(structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByStructureId_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId_PrevAndNext(journalArticlePK,
			structureId, obc);
	}

	public static java.util.List findByTemplateId(java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTemplateId(templateId);
	}

	public static java.util.List findByTemplateId(java.lang.String templateId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTemplateId(templateId, begin, end);
	}

	public static java.util.List findByTemplateId(java.lang.String templateId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTemplateId(templateId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByTemplateId_First(
		java.lang.String templateId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTemplateId_First(templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByTemplateId_Last(
		java.lang.String templateId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTemplateId_Last(templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByTemplateId_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String templateId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTemplateId_PrevAndNext(journalArticlePK,
			templateId, obc);
	}

	public static java.util.List findByA_A(java.lang.String articleId,
		boolean approved) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByA_A(articleId, approved);
	}

	public static java.util.List findByA_A(java.lang.String articleId,
		boolean approved, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByA_A(articleId, approved, begin, end);
	}

	public static java.util.List findByA_A(java.lang.String articleId,
		boolean approved, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByA_A(articleId, approved, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByA_A_First(
		java.lang.String articleId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByA_A_First(articleId, approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByA_A_Last(
		java.lang.String articleId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByA_A_Last(articleId, approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByA_A_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String articleId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByA_A_PrevAndNext(journalArticlePK, articleId,
			approved, obc);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId, begin, end);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId, begin,
			end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_First(portletId, groupId, companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_Last(portletId, groupId, companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_PrevAndNext(journalArticlePK, portletId,
			groupId, companyId, obc);
	}

	public static java.util.List findByP_G_C_T(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T(portletId, groupId, companyId, type);
	}

	public static java.util.List findByP_G_C_T(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T(portletId, groupId, companyId, type,
			begin, end);
	}

	public static java.util.List findByP_G_C_T(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T(portletId, groupId, companyId, type,
			begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_First(portletId, groupId, companyId,
			type, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_Last(portletId, groupId, companyId,
			type, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_T_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_PrevAndNext(journalArticlePK,
			portletId, groupId, companyId, type, obc);
	}

	public static java.util.List findByP_G_C_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_A(portletId, groupId, companyId, approved);
	}

	public static java.util.List findByP_G_C_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, boolean approved,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_A(portletId, groupId, companyId,
			approved, begin, end);
	}

	public static java.util.List findByP_G_C_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, boolean approved,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_A(portletId, groupId, companyId,
			approved, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_A_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_A_First(portletId, groupId, companyId,
			approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_A_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_A_Last(portletId, groupId, companyId,
			approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_A_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_A_PrevAndNext(journalArticlePK,
			portletId, groupId, companyId, approved, obc);
	}

	public static java.util.List findByP_G_C_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_A(portletId, groupId, companyId, type,
			approved);
	}

	public static java.util.List findByP_G_C_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_A(portletId, groupId, companyId, type,
			approved, begin, end);
	}

	public static java.util.List findByP_G_C_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_A(portletId, groupId, companyId, type,
			approved, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_A_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_A_First(portletId, groupId, companyId,
			type, approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_A_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_A_Last(portletId, groupId, companyId,
			type, approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_T_A_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_T_A_PrevAndNext(journalArticlePK,
			portletId, groupId, companyId, type, approved, obc);
	}

	public static java.util.List findByP_G_U_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_A(portletId, groupId, userId, approved);
	}

	public static java.util.List findByP_G_U_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId, boolean approved,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_A(portletId, groupId, userId, approved,
			begin, end);
	}

	public static java.util.List findByP_G_U_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId, boolean approved,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_A(portletId, groupId, userId, approved,
			begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_U_A_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String userId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_A_First(portletId, groupId, userId,
			approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_U_A_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String userId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_A_Last(portletId, groupId, userId,
			approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByP_G_U_A_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String userId, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_A_PrevAndNext(journalArticlePK,
			portletId, groupId, userId, approved, obc);
	}

	public static java.util.List findByP_G_U_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_T_A(portletId, groupId, userId, type,
			approved);
	}

	public static java.util.List findByP_G_U_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type, boolean approved, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_T_A(portletId, groupId, userId, type,
			approved, begin, end);
	}

	public static java.util.List findByP_G_U_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type, boolean approved, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_T_A(portletId, groupId, userId, type,
			approved, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_U_T_A_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String userId, java.lang.String type, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_T_A_First(portletId, groupId, userId,
			type, approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle findByP_G_U_T_A_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String userId, java.lang.String type, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_T_A_Last(portletId, groupId, userId,
			type, approved, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticle[] findByP_G_U_T_A_PrevAndNext(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK journalArticlePK,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String userId, java.lang.String type, boolean approved,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchArticleException, 
			com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_U_T_A_PrevAndNext(journalArticlePK,
			portletId, groupId, userId, type, approved, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByArticleId(java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByArticleId(articleId);
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByStructureId(java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByStructureId(structureId);
	}

	public static void removeByTemplateId(java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByTemplateId(templateId);
	}

	public static void removeByA_A(java.lang.String articleId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByA_A(articleId, approved);
	}

	public static void removeByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C(portletId, groupId, companyId);
	}

	public static void removeByP_G_C_T(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C_T(portletId, groupId, companyId, type);
	}

	public static void removeByP_G_C_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C_A(portletId, groupId, companyId, approved);
	}

	public static void removeByP_G_C_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C_T_A(portletId, groupId, companyId, type,
			approved);
	}

	public static void removeByP_G_U_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_U_A(portletId, groupId, userId, approved);
	}

	public static void removeByP_G_U_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_U_T_A(portletId, groupId, userId, type, approved);
	}

	public static int countByArticleId(java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByArticleId(articleId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByStructureId(java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByStructureId(structureId);
	}

	public static int countByTemplateId(java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByTemplateId(templateId);
	}

	public static int countByA_A(java.lang.String articleId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByA_A(articleId, approved);
	}

	public static int countByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C(portletId, groupId, companyId);
	}

	public static int countByP_G_C_T(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C_T(portletId, groupId, companyId, type);
	}

	public static int countByP_G_C_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C_A(portletId, groupId, companyId,
			approved);
	}

	public static int countByP_G_C_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C_T_A(portletId, groupId, companyId,
			type, approved);
	}

	public static int countByP_G_U_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_U_A(portletId, groupId, userId, approved);
	}

	public static int countByP_G_U_T_A(java.lang.String portletId,
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		JournalArticlePersistence persistence = (JournalArticlePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_U_T_A(portletId, groupId, userId, type,
			approved);
	}

	private static final Log _log = LogFactory.getLog(JournalArticleUtil.class);
}