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
 * <a href="JournalContentSearchPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface JournalContentSearchPersistence {
	public com.liferay.portlet.journal.model.JournalContentSearch create(
		long contentSearchId);

	public com.liferay.portlet.journal.model.JournalContentSearch remove(
		long contentSearchId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch remove(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch update(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch update(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch updateImpl(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByPrimaryKey(
		long contentSearchId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch fetchByPrimaryKey(
		long contentSearchId) throws com.liferay.portal.SystemException;

	public java.util.List findByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_P(long groupId, boolean privateLayout,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findByG_P(long groupId, boolean privateLayout,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_First(
		long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_Last(
		long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public java.util.List findByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_A(long groupId, java.lang.String articleId,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findByG_A(long groupId, java.lang.String articleId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_A_First(
		long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_A_Last(
		long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch[] findByG_A_PrevAndNext(
		long contentSearchId, long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public java.util.List findByG_P_L(long groupId, boolean privateLayout,
		long layoutId) throws com.liferay.portal.SystemException;

	public java.util.List findByG_P_L(long groupId, boolean privateLayout,
		long layoutId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_P_L(long groupId, boolean privateLayout,
		long layoutId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_First(
		long groupId, boolean privateLayout, long layoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_Last(
		long groupId, boolean privateLayout, long layoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_L_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		long layoutId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public java.util.List findByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId) throws com.liferay.portal.SystemException;

	public java.util.List findByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_A_First(
		long groupId, boolean privateLayout, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_A_Last(
		long groupId, boolean privateLayout, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_A_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public java.util.List findByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_P_First(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_P_Last(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_L_P_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_P_A(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public com.liferay.portlet.journal.model.JournalContentSearch fetchByG_P_L_P_A(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId, java.lang.String articleId)
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

	public void removeByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException;

	public void removeByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException;

	public void removeByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException;

	public void removeByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId) throws com.liferay.portal.SystemException;

	public void removeByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId)
		throws com.liferay.portal.SystemException;

	public void removeByG_P_L_P_A(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException;

	public int countByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException;

	public int countByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException;

	public int countByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId) throws com.liferay.portal.SystemException;

	public int countByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId)
		throws com.liferay.portal.SystemException;

	public int countByG_P_L_P_A(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}