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
 * <a href="JournalTemplateUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalTemplateUtil {
	public static com.liferay.portlet.journal.model.JournalTemplate create(
		long id) {
		return getPersistence().create(id);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate remove(
		long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().remove(id);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate remove(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(journalTemplate);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate update(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(journalTemplate);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate update(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(journalTemplate, merge);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate updateImpl(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(journalTemplate, merge);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByPrimaryKey(
		long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByPrimaryKey(id);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate fetchByPrimaryKey(
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

	public static com.liferay.portlet.journal.model.JournalTemplate findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByUuid_PrevAndNext(
		long id, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByUuid_PrevAndNext(id, uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate fetchByUUID_G(
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

	public static com.liferay.portlet.journal.model.JournalTemplate findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByGroupId_PrevAndNext(
		long id, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByGroupId_PrevAndNext(id, groupId, obc);
	}

	public static java.util.List findByTemplateId(java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByTemplateId(templateId);
	}

	public static java.util.List findByTemplateId(java.lang.String templateId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByTemplateId(templateId, begin, end);
	}

	public static java.util.List findByTemplateId(java.lang.String templateId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByTemplateId(templateId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByTemplateId_First(
		java.lang.String templateId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByTemplateId_First(templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByTemplateId_Last(
		java.lang.String templateId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByTemplateId_Last(templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByTemplateId_PrevAndNext(
		long id, java.lang.String templateId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByTemplateId_PrevAndNext(id, templateId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findBySmallImageId(smallImageId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate fetchBySmallImageId(
		long smallImageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchBySmallImageId(smallImageId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByG_T(
		long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByG_T(groupId, templateId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate fetchByG_T(
		long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_T(groupId, templateId);
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

	public static com.liferay.portlet.journal.model.JournalTemplate findByG_S_First(
		long groupId, java.lang.String structureId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByG_S_First(groupId, structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate findByG_S_Last(
		long groupId, java.lang.String structureId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByG_S_Last(groupId, structureId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate[] findByG_S_PrevAndNext(
		long id, long groupId, java.lang.String structureId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		return getPersistence().findByG_S_PrevAndNext(id, groupId, structureId,
			obc);
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
			com.liferay.portlet.journal.NoSuchTemplateException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByTemplateId(java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByTemplateId(templateId);
	}

	public static void removeBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		getPersistence().removeBySmallImageId(smallImageId);
	}

	public static void removeByG_T(long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchTemplateException {
		getPersistence().removeByG_T(groupId, templateId);
	}

	public static void removeByG_S(long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_S(groupId, structureId);
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

	public static int countByTemplateId(java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByTemplateId(templateId);
	}

	public static int countBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countBySmallImageId(smallImageId);
	}

	public static int countByG_T(long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_T(groupId, templateId);
	}

	public static int countByG_S(long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_S(groupId, structureId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static JournalTemplatePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(JournalTemplatePersistence persistence) {
		_persistence = persistence;
	}

	private static JournalTemplateUtil _getUtil() {
		if (_util == null) {
			_util = (JournalTemplateUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = JournalTemplateUtil.class.getName();
	private static JournalTemplateUtil _util;
	private JournalTemplatePersistence _persistence;
}