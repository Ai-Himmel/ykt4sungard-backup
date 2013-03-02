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
 * <a href="TagsPropertyUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsPropertyUtil {
	public static com.liferay.portlet.tags.model.TagsProperty create(
		long propertyId) {
		return getPersistence().create(propertyId);
	}

	public static com.liferay.portlet.tags.model.TagsProperty remove(
		long propertyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().remove(propertyId);
	}

	public static com.liferay.portlet.tags.model.TagsProperty remove(
		com.liferay.portlet.tags.model.TagsProperty tagsProperty)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(tagsProperty);
	}

	public static com.liferay.portlet.tags.model.TagsProperty update(
		com.liferay.portlet.tags.model.TagsProperty tagsProperty)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsProperty);
	}

	public static com.liferay.portlet.tags.model.TagsProperty update(
		com.liferay.portlet.tags.model.TagsProperty tagsProperty, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsProperty, merge);
	}

	public static com.liferay.portlet.tags.model.TagsProperty updateImpl(
		com.liferay.portlet.tags.model.TagsProperty tagsProperty, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(tagsProperty, merge);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByPrimaryKey(
		long propertyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByPrimaryKey(propertyId);
	}

	public static com.liferay.portlet.tags.model.TagsProperty fetchByPrimaryKey(
		long propertyId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(propertyId);
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

	public static com.liferay.portlet.tags.model.TagsProperty findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty[] findByCompanyId_PrevAndNext(
		long propertyId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByCompanyId_PrevAndNext(propertyId,
			companyId, obc);
	}

	public static java.util.List findByEntryId(long entryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByEntryId(entryId);
	}

	public static java.util.List findByEntryId(long entryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByEntryId(entryId, begin, end);
	}

	public static java.util.List findByEntryId(long entryId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByEntryId(entryId, begin, end, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByEntryId_First(
		long entryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByEntryId_First(entryId, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByEntryId_Last(
		long entryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByEntryId_Last(entryId, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty[] findByEntryId_PrevAndNext(
		long propertyId, long entryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByEntryId_PrevAndNext(propertyId, entryId,
			obc);
	}

	public static java.util.List findByC_K(long companyId, java.lang.String key)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_K(companyId, key);
	}

	public static java.util.List findByC_K(long companyId,
		java.lang.String key, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_K(companyId, key, begin, end);
	}

	public static java.util.List findByC_K(long companyId,
		java.lang.String key, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_K(companyId, key, begin, end, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByC_K_First(
		long companyId, java.lang.String key,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByC_K_First(companyId, key, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByC_K_Last(
		long companyId, java.lang.String key,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByC_K_Last(companyId, key, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty[] findByC_K_PrevAndNext(
		long propertyId, long companyId, java.lang.String key,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByC_K_PrevAndNext(propertyId, companyId,
			key, obc);
	}

	public static com.liferay.portlet.tags.model.TagsProperty findByE_K(
		long entryId, java.lang.String key)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		return getPersistence().findByE_K(entryId, key);
	}

	public static com.liferay.portlet.tags.model.TagsProperty fetchByE_K(
		long entryId, java.lang.String key)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByE_K(entryId, key);
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

	public static void removeByEntryId(long entryId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByEntryId(entryId);
	}

	public static void removeByC_K(long companyId, java.lang.String key)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_K(companyId, key);
	}

	public static void removeByE_K(long entryId, java.lang.String key)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchPropertyException {
		getPersistence().removeByE_K(entryId, key);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByEntryId(long entryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByEntryId(entryId);
	}

	public static int countByC_K(long companyId, java.lang.String key)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_K(companyId, key);
	}

	public static int countByE_K(long entryId, java.lang.String key)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByE_K(entryId, key);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static TagsPropertyPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(TagsPropertyPersistence persistence) {
		_persistence = persistence;
	}

	private static TagsPropertyUtil _getUtil() {
		if (_util == null) {
			_util = (TagsPropertyUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = TagsPropertyUtil.class.getName();
	private static TagsPropertyUtil _util;
	private TagsPropertyPersistence _persistence;
}