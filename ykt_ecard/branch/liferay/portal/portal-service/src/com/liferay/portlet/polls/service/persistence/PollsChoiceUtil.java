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
 * <a href="PollsChoiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsChoiceUtil {
	public static com.liferay.portlet.polls.model.PollsChoice create(
		long choiceId) {
		return getPersistence().create(choiceId);
	}

	public static com.liferay.portlet.polls.model.PollsChoice remove(
		long choiceId)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().remove(choiceId);
	}

	public static com.liferay.portlet.polls.model.PollsChoice remove(
		com.liferay.portlet.polls.model.PollsChoice pollsChoice)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(pollsChoice);
	}

	public static com.liferay.portlet.polls.model.PollsChoice update(
		com.liferay.portlet.polls.model.PollsChoice pollsChoice)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pollsChoice);
	}

	public static com.liferay.portlet.polls.model.PollsChoice update(
		com.liferay.portlet.polls.model.PollsChoice pollsChoice, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pollsChoice, merge);
	}

	public static com.liferay.portlet.polls.model.PollsChoice updateImpl(
		com.liferay.portlet.polls.model.PollsChoice pollsChoice, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(pollsChoice, merge);
	}

	public static com.liferay.portlet.polls.model.PollsChoice findByPrimaryKey(
		long choiceId)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByPrimaryKey(choiceId);
	}

	public static com.liferay.portlet.polls.model.PollsChoice fetchByPrimaryKey(
		long choiceId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(choiceId);
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

	public static com.liferay.portlet.polls.model.PollsChoice findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.polls.model.PollsChoice findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.polls.model.PollsChoice[] findByUuid_PrevAndNext(
		long choiceId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByUuid_PrevAndNext(choiceId, uuid, obc);
	}

	public static java.util.List findByQuestionId(long questionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId(questionId);
	}

	public static java.util.List findByQuestionId(long questionId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId(questionId, begin, end);
	}

	public static java.util.List findByQuestionId(long questionId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId(questionId, begin, end, obc);
	}

	public static com.liferay.portlet.polls.model.PollsChoice findByQuestionId_First(
		long questionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId_First(questionId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsChoice findByQuestionId_Last(
		long questionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId_Last(questionId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsChoice[] findByQuestionId_PrevAndNext(
		long choiceId, long questionId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByQuestionId_PrevAndNext(choiceId,
			questionId, obc);
	}

	public static com.liferay.portlet.polls.model.PollsChoice findByQ_N(
		long questionId, java.lang.String name)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByQ_N(questionId, name);
	}

	public static com.liferay.portlet.polls.model.PollsChoice fetchByQ_N(
		long questionId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByQ_N(questionId, name);
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

	public static void removeByQuestionId(long questionId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByQuestionId(questionId);
	}

	public static void removeByQ_N(long questionId, java.lang.String name)
		throws com.liferay.portlet.polls.NoSuchChoiceException, 
			com.liferay.portal.SystemException {
		getPersistence().removeByQ_N(questionId, name);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByQuestionId(long questionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByQuestionId(questionId);
	}

	public static int countByQ_N(long questionId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByQ_N(questionId, name);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PollsChoicePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PollsChoicePersistence persistence) {
		_persistence = persistence;
	}

	private static PollsChoiceUtil _getUtil() {
		if (_util == null) {
			_util = (PollsChoiceUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PollsChoiceUtil.class.getName();
	private static PollsChoiceUtil _util;
	private PollsChoicePersistence _persistence;
}