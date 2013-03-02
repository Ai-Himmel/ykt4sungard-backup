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
 * <a href="MBMessageFlagPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface MBMessageFlagPersistence {
	public com.liferay.portlet.messageboards.model.MBMessageFlag create(
		long messageFlagId);

	public com.liferay.portlet.messageboards.model.MBMessageFlag remove(
		long messageFlagId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag remove(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag update(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag update(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag updateImpl(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag findByPrimaryKey(
		long messageFlagId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag fetchByPrimaryKey(
		long messageFlagId) throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag[] findByUserId_PrevAndNext(
		long messageFlagId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public java.util.List findByMessageId(long messageId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByMessageId(long messageId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByMessageId(long messageId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag findByMessageId_First(
		long messageId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag findByMessageId_Last(
		long messageId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag[] findByMessageId_PrevAndNext(
		long messageFlagId, long messageId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag findByU_M(
		long userId, long messageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public com.liferay.portlet.messageboards.model.MBMessageFlag fetchByU_M(
		long userId, long messageId) throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public void removeByMessageId(long messageId)
		throws com.liferay.portal.SystemException;

	public void removeByU_M(long userId, long messageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.messageboards.NoSuchMessageFlagException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public int countByMessageId(long messageId)
		throws com.liferay.portal.SystemException;

	public int countByU_M(long userId, long messageId)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}