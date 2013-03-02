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

package com.liferay.portlet.documentlibrary.service.persistence;

/**
 * <a href="DLFileRankPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface DLFileRankPersistence {
	public com.liferay.portlet.documentlibrary.model.DLFileRank create(
		long fileRankId);

	public com.liferay.portlet.documentlibrary.model.DLFileRank remove(
		long fileRankId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank remove(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank update(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank update(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByPrimaryKey(
		long fileRankId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank fetchByPrimaryKey(
		long fileRankId) throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank[] findByUserId_PrevAndNext(
		long fileRankId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public java.util.List findByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException;

	public java.util.List findByF_N(long folderId, java.lang.String name,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findByF_N(long folderId, java.lang.String name,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByF_N_First(
		long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByF_N_Last(
		long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank[] findByF_N_PrevAndNext(
		long fileRankId, long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByC_U_F_N(
		long companyId, long userId, long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public com.liferay.portlet.documentlibrary.model.DLFileRank fetchByC_U_F_N(
		long companyId, long userId, long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException;

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

	public void removeByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException;

	public void removeByC_U_F_N(long companyId, long userId, long folderId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public int countByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException;

	public int countByC_U_F_N(long companyId, long userId, long folderId,
		java.lang.String name) throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}