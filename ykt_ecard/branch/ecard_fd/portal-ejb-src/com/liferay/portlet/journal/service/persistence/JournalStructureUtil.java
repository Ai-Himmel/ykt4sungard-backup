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
 * <a href="JournalStructureUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalStructureUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.journal.model.JournalStructure"),
			"com.liferay.portlet.journal.service.persistence.JournalStructurePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.journal.model.JournalStructure"));

	public static com.liferay.portlet.journal.model.JournalStructure create(
		java.lang.String structureId) {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(structureId);
	}

	public static com.liferay.portlet.journal.model.JournalStructure remove(
		java.lang.String structureId)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(structureId));
		}

		com.liferay.portlet.journal.model.JournalStructure journalStructure = persistence.remove(structureId);

		if (listener != null) {
			listener.onAfterRemove(journalStructure);
		}

		return journalStructure;
	}

	public static com.liferay.portlet.journal.model.JournalStructure update(
		com.liferay.portlet.journal.model.JournalStructure journalStructure)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = journalStructure.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(journalStructure);
			}
			else {
				listener.onBeforeUpdate(journalStructure);
			}
		}

		journalStructure = persistence.update(journalStructure);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(journalStructure);
			}
			else {
				listener.onAfterUpdate(journalStructure);
			}
		}

		return journalStructure;
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByPrimaryKey(
		java.lang.String structureId)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(structureId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure[] findByGroupId_PrevAndNext(
		java.lang.String structureId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(structureId, groupId, obc);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure[] findByCompanyId_PrevAndNext(
		java.lang.String structureId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(structureId, companyId,
			obc);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId, begin, end);
	}

	public static java.util.List findByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C(portletId, groupId, companyId, begin,
			end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByP_G_C_First(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_First(portletId, groupId, companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure findByP_G_C_Last(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_Last(portletId, groupId, companyId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalStructure[] findByP_G_C_PrevAndNext(
		java.lang.String structureId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.journal.NoSuchStructureException, 
			com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByP_G_C_PrevAndNext(structureId, portletId,
			groupId, companyId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByP_G_C(portletId, groupId, companyId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByP_G_C(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		JournalStructurePersistence persistence = (JournalStructurePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByP_G_C(portletId, groupId, companyId);
	}

	private static final Log _log = LogFactory.getLog(JournalStructureUtil.class);
}