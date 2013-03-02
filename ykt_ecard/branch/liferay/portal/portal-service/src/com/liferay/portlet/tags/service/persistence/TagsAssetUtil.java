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
 * <a href="TagsAssetUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsAssetUtil {
	public static com.liferay.portlet.tags.model.TagsAsset create(long assetId) {
		return getPersistence().create(assetId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset remove(long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().remove(assetId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset remove(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(tagsAsset);
	}

	public static com.liferay.portlet.tags.model.TagsAsset update(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsAsset);
	}

	public static com.liferay.portlet.tags.model.TagsAsset update(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsAsset, merge);
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateImpl(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(tagsAsset, merge);
	}

	public static com.liferay.portlet.tags.model.TagsAsset findByPrimaryKey(
		long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().findByPrimaryKey(assetId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset fetchByPrimaryKey(
		long assetId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(assetId);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.tags.model.TagsAsset findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.tags.model.TagsAsset findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.tags.model.TagsAsset[] findByCompanyId_PrevAndNext(
		long assetId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().findByCompanyId_PrevAndNext(assetId, companyId,
			obc);
	}

	public static com.liferay.portlet.tags.model.TagsAsset findByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().findByC_C(classNameId, classPK);
	}

	public static com.liferay.portlet.tags.model.TagsAsset fetchByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_C(classNameId, classPK);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		getPersistence().removeByC_C(classNameId, classPK);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C(classNameId, classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getTagsEntries(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().getTagsEntries(pk);
	}

	public static java.util.List getTagsEntries(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().getTagsEntries(pk, begin, end);
	}

	public static java.util.List getTagsEntries(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		return getPersistence().getTagsEntries(pk, begin, end, obc);
	}

	public static int getTagsEntriesSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getTagsEntriesSize(pk);
	}

	public static boolean containsTagsEntry(long pk, long tagsEntryPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsTagsEntry(pk, tagsEntryPK);
	}

	public static boolean containsTagsEntries(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsTagsEntries(pk);
	}

	public static void addTagsEntry(long pk, long tagsEntryPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsEntry(pk, tagsEntryPK);
	}

	public static void addTagsEntry(long pk,
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsEntry(pk, tagsEntry);
	}

	public static void addTagsEntries(long pk, long[] tagsEntryPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsEntries(pk, tagsEntryPKs);
	}

	public static void addTagsEntries(long pk, java.util.List tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsEntries(pk, tagsEntries);
	}

	public static void clearTagsEntries(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException {
		getPersistence().clearTagsEntries(pk);
	}

	public static void removeTagsEntry(long pk, long tagsEntryPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsEntry(pk, tagsEntryPK);
	}

	public static void removeTagsEntry(long pk,
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsEntry(pk, tagsEntry);
	}

	public static void removeTagsEntries(long pk, long[] tagsEntryPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsEntries(pk, tagsEntryPKs);
	}

	public static void removeTagsEntries(long pk, java.util.List tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsEntries(pk, tagsEntries);
	}

	public static void setTagsEntries(long pk, long[] tagsEntryPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().setTagsEntries(pk, tagsEntryPKs);
	}

	public static void setTagsEntries(long pk, java.util.List tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().setTagsEntries(pk, tagsEntries);
	}

	public static TagsAssetPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(TagsAssetPersistence persistence) {
		_persistence = persistence;
	}

	private static TagsAssetUtil _getUtil() {
		if (_util == null) {
			_util = (TagsAssetUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = TagsAssetUtil.class.getName();
	private static TagsAssetUtil _util;
	private TagsAssetPersistence _persistence;
}