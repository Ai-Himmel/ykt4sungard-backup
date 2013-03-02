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

package com.liferay.portal.service.persistence;

/**
 * <a href="RegionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RegionUtil {
	public static com.liferay.portal.model.Region create(long regionId) {
		return getPersistence().create(regionId);
	}

	public static com.liferay.portal.model.Region remove(long regionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().remove(regionId);
	}

	public static com.liferay.portal.model.Region remove(
		com.liferay.portal.model.Region region)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(region);
	}

	public static com.liferay.portal.model.Region update(
		com.liferay.portal.model.Region region)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(region);
	}

	public static com.liferay.portal.model.Region update(
		com.liferay.portal.model.Region region, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(region, merge);
	}

	public static com.liferay.portal.model.Region updateImpl(
		com.liferay.portal.model.Region region, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(region, merge);
	}

	public static com.liferay.portal.model.Region findByPrimaryKey(
		long regionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByPrimaryKey(regionId);
	}

	public static com.liferay.portal.model.Region fetchByPrimaryKey(
		long regionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(regionId);
	}

	public static java.util.List findByCountryId(long countryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCountryId(countryId);
	}

	public static java.util.List findByCountryId(long countryId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCountryId(countryId, begin, end);
	}

	public static java.util.List findByCountryId(long countryId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCountryId(countryId, begin, end, obc);
	}

	public static com.liferay.portal.model.Region findByCountryId_First(
		long countryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByCountryId_First(countryId, obc);
	}

	public static com.liferay.portal.model.Region findByCountryId_Last(
		long countryId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByCountryId_Last(countryId, obc);
	}

	public static com.liferay.portal.model.Region[] findByCountryId_PrevAndNext(
		long regionId, long countryId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByCountryId_PrevAndNext(regionId,
			countryId, obc);
	}

	public static java.util.List findByActive(boolean active)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByActive(active);
	}

	public static java.util.List findByActive(boolean active, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByActive(active, begin, end);
	}

	public static java.util.List findByActive(boolean active, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByActive(active, begin, end, obc);
	}

	public static com.liferay.portal.model.Region findByActive_First(
		boolean active, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByActive_First(active, obc);
	}

	public static com.liferay.portal.model.Region findByActive_Last(
		boolean active, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByActive_Last(active, obc);
	}

	public static com.liferay.portal.model.Region[] findByActive_PrevAndNext(
		long regionId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByActive_PrevAndNext(regionId, active, obc);
	}

	public static java.util.List findByC_A(long countryId, boolean active)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_A(countryId, active);
	}

	public static java.util.List findByC_A(long countryId, boolean active,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_A(countryId, active, begin, end);
	}

	public static java.util.List findByC_A(long countryId, boolean active,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_A(countryId, active, begin, end, obc);
	}

	public static com.liferay.portal.model.Region findByC_A_First(
		long countryId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByC_A_First(countryId, active, obc);
	}

	public static com.liferay.portal.model.Region findByC_A_Last(
		long countryId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByC_A_Last(countryId, active, obc);
	}

	public static com.liferay.portal.model.Region[] findByC_A_PrevAndNext(
		long regionId, long countryId, boolean active,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRegionException {
		return getPersistence().findByC_A_PrevAndNext(regionId, countryId,
			active, obc);
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

	public static void removeByCountryId(long countryId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCountryId(countryId);
	}

	public static void removeByActive(boolean active)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByActive(active);
	}

	public static void removeByC_A(long countryId, boolean active)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_A(countryId, active);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCountryId(long countryId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCountryId(countryId);
	}

	public static int countByActive(boolean active)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByActive(active);
	}

	public static int countByC_A(long countryId, boolean active)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_A(countryId, active);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static RegionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(RegionPersistence persistence) {
		_persistence = persistence;
	}

	private static RegionUtil _getUtil() {
		if (_util == null) {
			_util = (RegionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = RegionUtil.class.getName();
	private static RegionUtil _util;
	private RegionPersistence _persistence;
}