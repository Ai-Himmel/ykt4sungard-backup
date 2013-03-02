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

package com.liferay.portlet.tags.service.persistence;

/**
 * <a href="TagsAssetPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface TagsAssetPersistence {
	public com.liferay.portlet.tags.model.TagsAsset create(long assetId);

	public com.liferay.portlet.tags.model.TagsAsset remove(long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public com.liferay.portlet.tags.model.TagsAsset remove(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset update(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset update(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset updateImpl(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset findByPrimaryKey(
		long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public com.liferay.portlet.tags.model.TagsAsset fetchByPrimaryKey(
		long assetId) throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public com.liferay.portlet.tags.model.TagsAsset findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public com.liferay.portlet.tags.model.TagsAsset[] findByCompanyId_PrevAndNext(
		long assetId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public com.liferay.portlet.tags.model.TagsAsset findByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public com.liferay.portlet.tags.model.TagsAsset fetchByC_C(
		long classNameId, long classPK)
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

	public void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public void removeByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public int countByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;

	public java.util.List getTagsEntries(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public java.util.List getTagsEntries(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public java.util.List getTagsEntries(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public int getTagsEntriesSize(long pk)
		throws com.liferay.portal.SystemException;

	public boolean containsTagsEntry(long pk, long tagsEntryPK)
		throws com.liferay.portal.SystemException;

	public boolean containsTagsEntries(long pk)
		throws com.liferay.portal.SystemException;

	public void addTagsEntry(long pk, long tagsEntryPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void addTagsEntry(long pk,
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void addTagsEntries(long pk, long[] tagsEntryPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void addTagsEntries(long pk, java.util.List tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void clearTagsEntries(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException;

	public void removeTagsEntry(long pk, long tagsEntryPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void removeTagsEntry(long pk,
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void removeTagsEntries(long pk, long[] tagsEntryPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void removeTagsEntries(long pk, java.util.List tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void setTagsEntries(long pk, long[] tagsEntryPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;

	public void setTagsEntries(long pk, java.util.List tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException;
}