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
 * <a href="JournalArticleImagePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface JournalArticleImagePersistence {
	public com.liferay.portlet.journal.model.JournalArticleImage create(
		long articleImageId);

	public com.liferay.portlet.journal.model.JournalArticleImage remove(
		long articleImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage remove(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage update(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage update(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage updateImpl(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage,
		boolean merge) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByPrimaryKey(
		long articleImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage fetchByPrimaryKey(
		long articleImageId) throws com.liferay.portal.SystemException;

	public java.util.List findByGroupId(long groupId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByGroupId(long groupId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage[] findByGroupId_PrevAndNext(
		long articleImageId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public java.util.List findByTempImage(boolean tempImage)
		throws com.liferay.portal.SystemException;

	public java.util.List findByTempImage(boolean tempImage, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByTempImage(boolean tempImage, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByTempImage_First(
		boolean tempImage, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByTempImage_Last(
		boolean tempImage, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage[] findByTempImage_PrevAndNext(
		long articleImageId, boolean tempImage,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public java.util.List findByG_A_V(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException;

	public java.util.List findByG_A_V(long groupId, java.lang.String articleId,
		double version, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_A_V(long groupId, java.lang.String articleId,
		double version, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByG_A_V_First(
		long groupId, java.lang.String articleId, double version,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByG_A_V_Last(
		long groupId, java.lang.String articleId, double version,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage[] findByG_A_V_PrevAndNext(
		long articleImageId, long groupId, java.lang.String articleId,
		double version, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage findByG_A_V_E_L(
		long groupId, java.lang.String articleId, double version,
		java.lang.String elName, java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public com.liferay.portlet.journal.model.JournalArticleImage fetchByG_A_V_E_L(
		long groupId, java.lang.String articleId, double version,
		java.lang.String elName, java.lang.String languageId)
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

	public void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException;

	public void removeByTempImage(boolean tempImage)
		throws com.liferay.portal.SystemException;

	public void removeByG_A_V(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException;

	public void removeByG_A_V_E_L(long groupId, java.lang.String articleId,
		double version, java.lang.String elName, java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchArticleImageException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException;

	public int countByTempImage(boolean tempImage)
		throws com.liferay.portal.SystemException;

	public int countByG_A_V(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException;

	public int countByG_A_V_E_L(long groupId, java.lang.String articleId,
		double version, java.lang.String elName, java.lang.String languageId)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}