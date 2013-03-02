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
 * <a href="JournalArticleImageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleImageUtil {
	public static com.liferay.portlet.journal.model.JournalArticleImage create(
		long articleImageId) {
		return getPersistence().create(articleImageId);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage remove(
		long articleImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().remove(articleImageId);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage remove(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(journalArticleImage);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage update(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(journalArticleImage);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage update(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(journalArticleImage, merge);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage updateImpl(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(journalArticleImage, merge);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByPrimaryKey(
		long articleImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByPrimaryKey(articleImageId);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage fetchByPrimaryKey(
		long articleImageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(articleImageId);
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

	public static com.liferay.portlet.journal.model.JournalArticleImage findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage[] findByGroupId_PrevAndNext(
		long articleImageId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByGroupId_PrevAndNext(articleImageId,
			groupId, obc);
	}

	public static java.util.List findByTempImage(boolean tempImage)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByTempImage(tempImage);
	}

	public static java.util.List findByTempImage(boolean tempImage, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByTempImage(tempImage, begin, end);
	}

	public static java.util.List findByTempImage(boolean tempImage, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByTempImage(tempImage, begin, end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByTempImage_First(
		boolean tempImage, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByTempImage_First(tempImage, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByTempImage_Last(
		boolean tempImage, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByTempImage_Last(tempImage, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage[] findByTempImage_PrevAndNext(
		long articleImageId, boolean tempImage,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByTempImage_PrevAndNext(articleImageId,
			tempImage, obc);
	}

	public static java.util.List findByG_A_V(long groupId,
		java.lang.String articleId, double version)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A_V(groupId, articleId, version);
	}

	public static java.util.List findByG_A_V(long groupId,
		java.lang.String articleId, double version, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A_V(groupId, articleId, version, begin,
			end);
	}

	public static java.util.List findByG_A_V(long groupId,
		java.lang.String articleId, double version, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_A_V(groupId, articleId, version, begin,
			end, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByG_A_V_First(
		long groupId, java.lang.String articleId, double version,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByG_A_V_First(groupId, articleId, version,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByG_A_V_Last(
		long groupId, java.lang.String articleId, double version,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByG_A_V_Last(groupId, articleId, version,
			obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage[] findByG_A_V_PrevAndNext(
		long articleImageId, long groupId, java.lang.String articleId,
		double version, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByG_A_V_PrevAndNext(articleImageId,
			groupId, articleId, version, obc);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage findByG_A_V_E_L(
		long groupId, java.lang.String articleId, double version,
		java.lang.String elName, java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		return getPersistence().findByG_A_V_E_L(groupId, articleId, version,
			elName, languageId);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage fetchByG_A_V_E_L(
		long groupId, java.lang.String articleId, double version,
		java.lang.String elName, java.lang.String languageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_A_V_E_L(groupId, articleId, version,
			elName, languageId);
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

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByTempImage(boolean tempImage)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByTempImage(tempImage);
	}

	public static void removeByG_A_V(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException {
		getPersistence().removeByG_A_V(groupId, articleId, version);
	}

	public static void removeByG_A_V_E_L(long groupId,
		java.lang.String articleId, double version, java.lang.String elName,
		java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException {
		getPersistence().removeByG_A_V_E_L(groupId, articleId, version, elName,
			languageId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByTempImage(boolean tempImage)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByTempImage(tempImage);
	}

	public static int countByG_A_V(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A_V(groupId, articleId, version);
	}

	public static int countByG_A_V_E_L(long groupId,
		java.lang.String articleId, double version, java.lang.String elName,
		java.lang.String languageId) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_A_V_E_L(groupId, articleId, version,
			elName, languageId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static JournalArticleImagePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(JournalArticleImagePersistence persistence) {
		_persistence = persistence;
	}

	private static JournalArticleImageUtil _getUtil() {
		if (_util == null) {
			_util = (JournalArticleImageUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = JournalArticleImageUtil.class.getName();
	private static JournalArticleImageUtil _util;
	private JournalArticleImagePersistence _persistence;
}