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

package com.liferay.portlet.messageboards.service.persistence;

/**
 * <a href="MBMessageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageUtil {
	public static com.liferay.portlet.messageboards.model.MBMessage create(
		long messageId) {
		return getPersistence().create(messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage remove(
		long messageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().remove(messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage remove(
		com.liferay.portlet.messageboards.model.MBMessage mbMessage)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(mbMessage);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage update(
		com.liferay.portlet.messageboards.model.MBMessage mbMessage)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(mbMessage);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage update(
		com.liferay.portlet.messageboards.model.MBMessage mbMessage,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(mbMessage, merge);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateImpl(
		com.liferay.portlet.messageboards.model.MBMessage mbMessage,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(mbMessage, merge);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByPrimaryKey(
		long messageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByPrimaryKey(messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage fetchByPrimaryKey(
		long messageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(messageId);
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

	public static com.liferay.portlet.messageboards.model.MBMessage findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByUuid_PrevAndNext(
		long messageId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByUuid_PrevAndNext(messageId, uuid, obc);
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

	public static com.liferay.portlet.messageboards.model.MBMessage findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByCompanyId_PrevAndNext(
		long messageId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByCompanyId_PrevAndNext(messageId,
			companyId, obc);
	}

	public static java.util.List findByCategoryId(long categoryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCategoryId(categoryId);
	}

	public static java.util.List findByCategoryId(long categoryId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCategoryId(categoryId, begin, end);
	}

	public static java.util.List findByCategoryId(long categoryId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCategoryId(categoryId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByCategoryId_First(
		long categoryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByCategoryId_First(categoryId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByCategoryId_Last(
		long categoryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByCategoryId_Last(categoryId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByCategoryId_PrevAndNext(
		long messageId, long categoryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByCategoryId_PrevAndNext(messageId,
			categoryId, obc);
	}

	public static java.util.List findByThreadId(long threadId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByThreadId(threadId);
	}

	public static java.util.List findByThreadId(long threadId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByThreadId(threadId, begin, end);
	}

	public static java.util.List findByThreadId(long threadId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByThreadId(threadId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByThreadId_First(
		long threadId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByThreadId_First(threadId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByThreadId_Last(
		long threadId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByThreadId_Last(threadId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByThreadId_PrevAndNext(
		long messageId, long threadId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByThreadId_PrevAndNext(messageId, threadId,
			obc);
	}

	public static java.util.List findByC_T(long categoryId, long threadId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_T(categoryId, threadId);
	}

	public static java.util.List findByC_T(long categoryId, long threadId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_T(categoryId, threadId, begin, end);
	}

	public static java.util.List findByC_T(long categoryId, long threadId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_T(categoryId, threadId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByC_T_First(
		long categoryId, long threadId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByC_T_First(categoryId, threadId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByC_T_Last(
		long categoryId, long threadId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByC_T_Last(categoryId, threadId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByC_T_PrevAndNext(
		long messageId, long categoryId, long threadId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByC_T_PrevAndNext(messageId, categoryId,
			threadId, obc);
	}

	public static java.util.List findByT_P(long threadId, long parentMessageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByT_P(threadId, parentMessageId);
	}

	public static java.util.List findByT_P(long threadId, long parentMessageId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByT_P(threadId, parentMessageId, begin, end);
	}

	public static java.util.List findByT_P(long threadId, long parentMessageId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByT_P(threadId, parentMessageId, begin,
			end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByT_P_First(
		long threadId, long parentMessageId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByT_P_First(threadId, parentMessageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage findByT_P_Last(
		long threadId, long parentMessageId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByT_P_Last(threadId, parentMessageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage[] findByT_P_PrevAndNext(
		long messageId, long threadId, long parentMessageId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageException {
		return getPersistence().findByT_P_PrevAndNext(messageId, threadId,
			parentMessageId, obc);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByCategoryId(long categoryId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCategoryId(categoryId);
	}

	public static void removeByThreadId(long threadId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByThreadId(threadId);
	}

	public static void removeByC_T(long categoryId, long threadId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_T(categoryId, threadId);
	}

	public static void removeByT_P(long threadId, long parentMessageId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByT_P(threadId, parentMessageId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByCategoryId(long categoryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCategoryId(categoryId);
	}

	public static int countByThreadId(long threadId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByThreadId(threadId);
	}

	public static int countByC_T(long categoryId, long threadId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_T(categoryId, threadId);
	}

	public static int countByT_P(long threadId, long parentMessageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByT_P(threadId, parentMessageId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static MBMessagePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(MBMessagePersistence persistence) {
		_persistence = persistence;
	}

	private static MBMessageUtil _getUtil() {
		if (_util == null) {
			_util = (MBMessageUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = MBMessageUtil.class.getName();
	private static MBMessageUtil _util;
	private MBMessagePersistence _persistence;
}