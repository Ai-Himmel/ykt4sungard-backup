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

package com.liferay.portlet.polls.service.persistence;

/**
 * <a href="PollsQuestionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsQuestionUtil {
	public static com.liferay.portlet.polls.model.PollsQuestion create(
		long questionId) {
		return getPersistence().create(questionId);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion remove(
		long questionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().remove(questionId);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion remove(
		com.liferay.portlet.polls.model.PollsQuestion pollsQuestion)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(pollsQuestion);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion update(
		com.liferay.portlet.polls.model.PollsQuestion pollsQuestion)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pollsQuestion);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion update(
		com.liferay.portlet.polls.model.PollsQuestion pollsQuestion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(pollsQuestion, merge);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion updateImpl(
		com.liferay.portlet.polls.model.PollsQuestion pollsQuestion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(pollsQuestion, merge);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion findByPrimaryKey(
		long questionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByPrimaryKey(questionId);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion fetchByPrimaryKey(
		long questionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(questionId);
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

	public static com.liferay.portlet.polls.model.PollsQuestion findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion[] findByUuid_PrevAndNext(
		long questionId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByUuid_PrevAndNext(questionId, uuid, obc);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion fetchByUUID_G(
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

	public static com.liferay.portlet.polls.model.PollsQuestion findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsQuestion[] findByGroupId_PrevAndNext(
		long questionId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.polls.NoSuchQuestionException {
		return getPersistence().findByGroupId_PrevAndNext(questionId, groupId,
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
			com.liferay.portlet.polls.NoSuchQuestionException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
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

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PollsQuestionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PollsQuestionPersistence persistence) {
		_persistence = persistence;
	}

	private static PollsQuestionUtil _getUtil() {
		if (_util == null) {
			_util = (PollsQuestionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PollsQuestionUtil.class.getName();
	private static PollsQuestionUtil _util;
	private PollsQuestionPersistence _persistence;
}