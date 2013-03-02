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
 * <a href="TagsEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsEntryUtil {
	public static com.liferay.portlet.tags.model.TagsEntry create(long entryId) {
		return getPersistence().create(entryId);
	}

	public static com.liferay.portlet.tags.model.TagsEntry remove(long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		return getPersistence().remove(entryId);
	}

	public static com.liferay.portlet.tags.model.TagsEntry remove(
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(tagsEntry);
	}

	public static com.liferay.portlet.tags.model.TagsEntry update(
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsEntry);
	}

	public static com.liferay.portlet.tags.model.TagsEntry update(
		com.liferay.portlet.tags.model.TagsEntry tagsEntry, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsEntry, merge);
	}

	public static com.liferay.portlet.tags.model.TagsEntry updateImpl(
		com.liferay.portlet.tags.model.TagsEntry tagsEntry, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(tagsEntry, merge);
	}

	public static com.liferay.portlet.tags.model.TagsEntry findByPrimaryKey(
		long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		return getPersistence().findByPrimaryKey(entryId);
	}

	public static com.liferay.portlet.tags.model.TagsEntry fetchByPrimaryKey(
		long entryId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(entryId);
	}

	public static com.liferay.portlet.tags.model.TagsEntry findByC_N(
		long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		return getPersistence().findByC_N(companyId, name);
	}

	public static com.liferay.portlet.tags.model.TagsEntry fetchByC_N(
		long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_N(companyId, name);
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

	public static void removeByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeByC_N(companyId, name);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_N(companyId, name);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getTagsAssets(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		return getPersistence().getTagsAssets(pk);
	}

	public static java.util.List getTagsAssets(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		return getPersistence().getTagsAssets(pk, begin, end);
	}

	public static java.util.List getTagsAssets(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		return getPersistence().getTagsAssets(pk, begin, end, obc);
	}

	public static int getTagsAssetsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getTagsAssetsSize(pk);
	}

	public static boolean containsTagsAsset(long pk, long tagsAssetPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsTagsAsset(pk, tagsAssetPK);
	}

	public static boolean containsTagsAssets(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsTagsAssets(pk);
	}

	public static void addTagsAsset(long pk, long tagsAssetPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsAsset(pk, tagsAssetPK);
	}

	public static void addTagsAsset(long pk,
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsAsset(pk, tagsAsset);
	}

	public static void addTagsAssets(long pk, long[] tagsAssetPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsAssets(pk, tagsAssetPKs);
	}

	public static void addTagsAssets(long pk, java.util.List tagsAssets)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().addTagsAssets(pk, tagsAssets);
	}

	public static void clearTagsAssets(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().clearTagsAssets(pk);
	}

	public static void removeTagsAsset(long pk, long tagsAssetPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsAsset(pk, tagsAssetPK);
	}

	public static void removeTagsAsset(long pk,
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsAsset(pk, tagsAsset);
	}

	public static void removeTagsAssets(long pk, long[] tagsAssetPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsAssets(pk, tagsAssetPKs);
	}

	public static void removeTagsAssets(long pk, java.util.List tagsAssets)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().removeTagsAssets(pk, tagsAssets);
	}

	public static void setTagsAssets(long pk, long[] tagsAssetPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().setTagsAssets(pk, tagsAssetPKs);
	}

	public static void setTagsAssets(long pk, java.util.List tagsAssets)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException {
		getPersistence().setTagsAssets(pk, tagsAssets);
	}

	public static TagsEntryPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(TagsEntryPersistence persistence) {
		_persistence = persistence;
	}

	private static TagsEntryUtil _getUtil() {
		if (_util == null) {
			_util = (TagsEntryUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = TagsEntryUtil.class.getName();
	private static TagsEntryUtil _util;
	private TagsEntryPersistence _persistence;
}