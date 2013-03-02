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
 * <a href="OrganizationFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrganizationFinderUtil {
	public static int countByKeywords(long companyId,
		long parentOrganizationId,
		java.lang.String parentOrganizationComparator,
		java.lang.String keywords, int type, java.lang.Long regionId,
		java.lang.Long countryId, java.util.LinkedHashMap params)
		throws com.liferay.portal.SystemException {
		return getFinder().countByKeywords(companyId, parentOrganizationId,
			parentOrganizationComparator, keywords, type, regionId, countryId,
			params);
	}

	public static int countByC_PO_N_T_S_C_Z_R_C(long companyId,
		long parentOrganizationId,
		java.lang.String parentOrganizationComparator, java.lang.String name,
		int type, java.lang.String street, java.lang.String city,
		java.lang.String zip, java.lang.Long regionId,
		java.lang.Long countryId, java.util.LinkedHashMap params,
		boolean andOperator) throws com.liferay.portal.SystemException {
		return getFinder().countByC_PO_N_T_S_C_Z_R_C(companyId,
			parentOrganizationId, parentOrganizationComparator, name, type,
			street, city, zip, regionId, countryId, params, andOperator);
	}

	public static int countByC_PO_N_T_S_C_Z_R_C(long companyId,
		long parentOrganizationId,
		java.lang.String parentOrganizationComparator,
		java.lang.String[] names, int type, java.lang.String[] streets,
		java.lang.String[] cities, java.lang.String[] zips,
		java.lang.Long regionId, java.lang.Long countryId,
		java.util.LinkedHashMap params, boolean andOperator)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_PO_N_T_S_C_Z_R_C(companyId,
			parentOrganizationId, parentOrganizationComparator, names, type,
			streets, cities, zips, regionId, countryId, params, andOperator);
	}

	public static java.util.List findByKeywords(long companyId,
		long parentOrganizationId,
		java.lang.String parentOrganizationComparator,
		java.lang.String keywords, int type, java.lang.Long regionId,
		java.lang.Long countryId, java.util.LinkedHashMap params, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByKeywords(companyId, parentOrganizationId,
			parentOrganizationComparator, keywords, type, regionId, countryId,
			params, begin, end, obc);
	}

	public static java.util.List findByC_PO_N_T_S_C_Z_R_C(long companyId,
		long parentOrganizationId,
		java.lang.String parentOrganizationComparator, java.lang.String name,
		int type, java.lang.String street, java.lang.String city,
		java.lang.String zip, java.lang.Long regionId,
		java.lang.Long countryId, java.util.LinkedHashMap params,
		boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_PO_N_T_S_C_Z_R_C(companyId,
			parentOrganizationId, parentOrganizationComparator, name, type,
			street, city, zip, regionId, countryId, params, andOperator, begin,
			end, obc);
	}

	public static java.util.List findByC_PO_N_T_S_C_Z_R_C(long companyId,
		long parentOrganizationId,
		java.lang.String parentOrganizationComparator,
		java.lang.String[] names, int type, java.lang.String[] streets,
		java.lang.String[] cities, java.lang.String[] zips,
		java.lang.Long regionId, java.lang.Long countryId,
		java.util.LinkedHashMap params, boolean andOperator, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_PO_N_T_S_C_Z_R_C(companyId,
			parentOrganizationId, parentOrganizationComparator, names, type,
			streets, cities, zips, regionId, countryId, params, andOperator,
			begin, end, obc);
	}

	public static OrganizationFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(OrganizationFinder finder) {
		_finder = finder;
	}

	private static OrganizationFinderUtil _getUtil() {
		if (_util == null) {
			_util = (OrganizationFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = OrganizationFinderUtil.class.getName();
	private static OrganizationFinderUtil _util;
	private OrganizationFinder _finder;
}