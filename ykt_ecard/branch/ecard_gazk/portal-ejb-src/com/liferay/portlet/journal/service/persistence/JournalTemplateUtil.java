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
 * <a href="JournalTemplateUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalTemplateUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.journal.model.JournalTemplate"),
			"com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.journal.model.JournalTemplate"));

	public static com.liferay.portlet.journal.model.JournalTemplate create(
		java.lang.String templateId) {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(templateId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate remove(
		java.lang.String templateId)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(templateId));
		}

		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = persistence.remove(templateId);

		if (listener != null) {
			listener.onAfterRemove(journalTemplate);
		}

		return journalTemplate;
	}

	public static com.liferay.portlet.journal.model.JournalTemplate update(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = journalTemplate.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(journalTemplate);
			}
			else {
				listener.onBeforeUpdate(journalTemplate);
			}
		}

		journalTemplate = persistence.update(journalTemplate);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(journalTemplate);
			}
			else {
				listener.onAfterUpdate(journalTemplate);
			}
		}

		return journalTemplate;
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByPrimaryKey(
		java.lang.String templateId)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(templateId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByGroupId_PrevAndNext(
		java.lang.String templateId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(templateId, groupId, obc);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByCompanyId_PrevAndNext(
		java.lang.String templateId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(templateId, companyId,
			obc);
	}

	public static java.util.List findByStructureId(java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId(structureId);
	}

	public static java.util.List findByStructureId(
		java.lang.String structureId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId(structureId, begin, end);
	}

	public static java.util.List findByStructureId(
		java.lang.String structureId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId(structureId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByStructureId_First(
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId_First(structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByStructureId_Last(
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId_Last(structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByStructureId_PrevAndNext(
		java.lang.String templateId, java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByStructureId_PrevAndNext(templateId,
			structureId, obc);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId, begin, end);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId, begin,
			end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByP_G_C_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_First(portletId, groupId, companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByP_G_C_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_Last(portletId, groupId, companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByP_G_C_PrevAndNext(
		java.lang.String templateId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_PrevAndNext(templateId, portletId,
			groupId, companyId, obc);
	}

	public static java.util.List findByP_G_S(java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_S(portletId, groupId, structureId);
	}

	public static java.util.List findByP_G_S(java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId, int begin,
		int end) throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_S(portletId, groupId, structureId, begin,
			end);
	}

	public static java.util.List findByP_G_S(java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_S(portletId, groupId, structureId, begin,
			end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByP_G_S_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_S_First(portletId, groupId, structureId,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByP_G_S_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_S_Last(portletId, groupId, structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByP_G_S_PrevAndNext(
		java.lang.String templateId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchTemplateException, 
			com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_S_PrevAndNext(templateId, portletId,
			groupId, structureId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByStructureId(java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByStructureId(structureId);
	}

	public static void removeByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C(portletId, groupId, companyId);
	}

	public static void removeByP_G_S(java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_S(portletId, groupId, structureId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByStructureId(java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByStructureId(structureId);
	}

	public static int countByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C(portletId, groupId, companyId);
	}

	public static int countByP_G_S(java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		JournalTemplatePersistence persistence = (JournalTemplatePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_S(portletId, groupId, structureId);
	}

	private static final Log _log = LogFactory.getLog(JournalTemplateUtil.class);
}