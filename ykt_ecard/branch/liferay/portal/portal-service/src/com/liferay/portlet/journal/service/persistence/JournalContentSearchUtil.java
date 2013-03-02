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
 * <a href="JournalContentSearchUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalContentSearchUtil {
	public static com.liferay.portlet.journal.model.JournalContentSearch create(
		long contentSearchId) {
		return getPersistence().create(contentSearchId);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch remove(
		long contentSearchId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().remove(contentSearchId);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch remove(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(journalContentSearch);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch update(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(journalContentSearch);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch update(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(journalContentSearch, merge);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch updateImpl(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(journalContentSearch, merge);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByPrimaryKey(
		long contentSearchId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByPrimaryKey(contentSearchId);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch fetchByPrimaryKey(
		long contentSearchId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(contentSearchId);
	}

	public static java.util.List findByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, privateLayout);
	}

	public static java.util.List findByG_P(long groupId, boolean privateLayout,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, privateLayout, begin, end);
	}

	public static java.util.List findByG_P(long groupId, boolean privateLayout,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, privateLayout, begin, end,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_First(
		long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_First(groupId, privateLayout, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_Last(
		long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_Last(groupId, privateLayout, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_PrevAndNext(contentSearchId, groupId,
			privateLayout, obc);
	}

	public static java.util.List findByG_A(long groupId,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, articleId);
	}

	public static java.util.List findByG_A(long groupId,
		java.lang.String articleId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, articleId, begin, end);
	}

	public static java.util.List findByG_A(long groupId,
		java.lang.String articleId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A(groupId, articleId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_A_First(
		long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_A_First(groupId, articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_A_Last(
		long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_A_Last(groupId, articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch[] findByG_A_PrevAndNext(
		long contentSearchId, long groupId, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_A_PrevAndNext(contentSearchId, groupId,
			articleId, obc);
	}

	public static java.util.List findByG_P_L(long groupId,
		boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_L(groupId, privateLayout, layoutId);
	}

	public static java.util.List findByG_P_L(long groupId,
		boolean privateLayout, long layoutId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_L(groupId, privateLayout, layoutId,
			begin, end);
	}

	public static java.util.List findByG_P_L(long groupId,
		boolean privateLayout, long layoutId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_L(groupId, privateLayout, layoutId,
			begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_First(
		long groupId, boolean privateLayout, long layoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_First(groupId, privateLayout,
			layoutId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_Last(
		long groupId, boolean privateLayout, long layoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_Last(groupId, privateLayout,
			layoutId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_L_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		long layoutId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_PrevAndNext(contentSearchId,
			groupId, privateLayout, layoutId, obc);
	}

	public static java.util.List findByG_P_A(long groupId,
		boolean privateLayout, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_A(groupId, privateLayout, articleId);
	}

	public static java.util.List findByG_P_A(long groupId,
		boolean privateLayout, java.lang.String articleId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_A(groupId, privateLayout, articleId,
			begin, end);
	}

	public static java.util.List findByG_P_A(long groupId,
		boolean privateLayout, java.lang.String articleId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_A(groupId, privateLayout, articleId,
			begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_A_First(
		long groupId, boolean privateLayout, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_A_First(groupId, privateLayout,
			articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_A_Last(
		long groupId, boolean privateLayout, java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_A_Last(groupId, privateLayout,
			articleId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_A_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		java.lang.String articleId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_A_PrevAndNext(contentSearchId,
			groupId, privateLayout, articleId, obc);
	}

	public static java.util.List findByG_P_L_P(long groupId,
		boolean privateLayout, long layoutId, java.lang.String portletId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_L_P(groupId, privateLayout, layoutId,
			portletId);
	}

	public static java.util.List findByG_P_L_P(long groupId,
		boolean privateLayout, long layoutId, java.lang.String portletId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_L_P(groupId, privateLayout, layoutId,
			portletId, begin, end);
	}

	public static java.util.List findByG_P_L_P(long groupId,
		boolean privateLayout, long layoutId, java.lang.String portletId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_L_P(groupId, privateLayout, layoutId,
			portletId, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_P_First(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_P_First(groupId, privateLayout,
			layoutId, portletId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_P_Last(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_P_Last(groupId, privateLayout,
			layoutId, portletId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch[] findByG_P_L_P_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_P_PrevAndNext(contentSearchId,
			groupId, privateLayout, layoutId, portletId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch findByG_P_L_P_A(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		return getPersistence().findByG_P_L_P_A(groupId, privateLayout,
			layoutId, portletId, articleId);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch fetchByG_P_L_P_A(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_P_L_P_A(groupId, privateLayout,
			layoutId, portletId, articleId);
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

	public static void removeByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P(groupId, privateLayout);
	}

	public static void removeByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_A(groupId, articleId);
	}

	public static void removeByG_P_L(long groupId, boolean privateLayout,
		long layoutId) throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P_L(groupId, privateLayout, layoutId);
	}

	public static void removeByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P_A(groupId, privateLayout, articleId);
	}

	public static void removeByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P_L_P(groupId, privateLayout, layoutId,
			portletId);
	}

	public static void removeByG_P_L_P_A(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchContentSearchException {
		getPersistence().removeByG_P_L_P_A(groupId, privateLayout, layoutId,
			portletId, articleId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P(groupId, privateLayout);
	}

	public static int countByG_A(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A(groupId, articleId);
	}

	public static int countByG_P_L(long groupId, boolean privateLayout,
		long layoutId) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_L(groupId, privateLayout, layoutId);
	}

	public static int countByG_P_A(long groupId, boolean privateLayout,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_A(groupId, privateLayout, articleId);
	}

	public static int countByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_L_P(groupId, privateLayout,
			layoutId, portletId);
	}

	public static int countByG_P_L_P_A(long groupId, boolean privateLayout,
		long layoutId, java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_L_P_A(groupId, privateLayout,
			layoutId, portletId, articleId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static JournalContentSearchPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(JournalContentSearchPersistence persistence) {
		_persistence = persistence;
	}

	private static JournalContentSearchUtil _getUtil() {
		if (_util == null) {
			_util = (JournalContentSearchUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = JournalContentSearchUtil.class.getName();
	private static JournalContentSearchUtil _util;
	private JournalContentSearchPersistence _persistence;
}