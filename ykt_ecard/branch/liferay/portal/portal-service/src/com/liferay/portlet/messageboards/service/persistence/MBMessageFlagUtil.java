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
 * <a href="MBMessageFlagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageFlagUtil {
	public static com.liferay.portlet.messageboards.model.MBMessageFlag create(
		long messageFlagId) {
		return getPersistence().create(messageFlagId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag remove(
		long messageFlagId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().remove(messageFlagId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag remove(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(mbMessageFlag);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag update(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(mbMessageFlag);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag update(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(mbMessageFlag, merge);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag updateImpl(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(mbMessageFlag, merge);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByPrimaryKey(
		long messageFlagId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByPrimaryKey(messageFlagId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag fetchByPrimaryKey(
		long messageFlagId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(messageFlagId);
	}

	public static java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId);
	}

	public static java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag[] findByUserId_PrevAndNext(
		long messageFlagId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByUserId_PrevAndNext(messageFlagId, userId,
			obc);
	}

	public static java.util.List findByMessageId(long messageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByMessageId(messageId);
	}

	public static java.util.List findByMessageId(long messageId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByMessageId(messageId, begin, end);
	}

	public static java.util.List findByMessageId(long messageId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByMessageId(messageId, begin, end, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByMessageId_First(
		long messageId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByMessageId_First(messageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByMessageId_Last(
		long messageId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByMessageId_Last(messageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag[] findByMessageId_PrevAndNext(
		long messageFlagId, long messageId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByMessageId_PrevAndNext(messageFlagId,
			messageId, obc);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag findByU_M(
		long userId, long messageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		return getPersistence().findByU_M(userId, messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag fetchByU_M(
		long userId, long messageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByU_M(userId, messageId);
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

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeByMessageId(long messageId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByMessageId(messageId);
	}

	public static void removeByU_M(long userId, long messageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException {
		getPersistence().removeByU_M(userId, messageId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countByMessageId(long messageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByMessageId(messageId);
	}

	public static int countByU_M(long userId, long messageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByU_M(userId, messageId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static MBMessageFlagPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(MBMessageFlagPersistence persistence) {
		_persistence = persistence;
	}

	private static MBMessageFlagUtil _getUtil() {
		if (_util == null) {
			_util = (MBMessageFlagUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = MBMessageFlagUtil.class.getName();
	private static MBMessageFlagUtil _util;
	private MBMessageFlagPersistence _persistence;
}