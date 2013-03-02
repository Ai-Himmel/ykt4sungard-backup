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
 * <a href="UserFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserFinderUtil {
	public static int countByKeywords(long companyId,
		java.lang.String keywords, java.lang.Boolean active,
		java.util.LinkedHashMap params)
		throws com.liferay.portal.SystemException {
		return getFinder().countByKeywords(companyId, keywords, active, params);
	}

	public static int countByC_FN_MN_LN_SN_EA_A(long companyId,
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String screenName,
		java.lang.String emailAddress, java.lang.Boolean active,
		java.util.LinkedHashMap params, boolean andOperator)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_FN_MN_LN_SN_EA_A(companyId, firstName,
			middleName, lastName, screenName, emailAddress, active, params,
			andOperator);
	}

	public static int countByC_FN_MN_LN_SN_EA_A(long companyId,
		java.lang.String[] firstNames, java.lang.String[] middleNames,
		java.lang.String[] lastNames, java.lang.String[] screenNames,
		java.lang.String[] emailAddresses, java.lang.Boolean active,
		java.util.LinkedHashMap params, boolean andOperator)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_FN_MN_LN_SN_EA_A(companyId, firstNames,
			middleNames, lastNames, screenNames, emailAddresses, active,
			params, andOperator);
	}

	public static java.util.List findByKeywords(long companyId,
		java.lang.String keywords, java.lang.Boolean active,
		java.util.LinkedHashMap params, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByKeywords(companyId, keywords, active, params,
			begin, end, obc);
	}

	public static java.util.List findByC_FN_MN_LN_SN_EA_A(long companyId,
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String screenName,
		java.lang.String emailAddress, java.lang.Boolean active,
		java.util.LinkedHashMap params, boolean andOperator, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_FN_MN_LN_SN_EA_A(companyId, firstName,
			middleName, lastName, screenName, emailAddress, active, params,
			andOperator, begin, end, obc);
	}

	public static java.util.List findByC_FN_MN_LN_SN_EA_A(long companyId,
		java.lang.String[] firstNames, java.lang.String[] middleNames,
		java.lang.String[] lastNames, java.lang.String[] screenNames,
		java.lang.String[] emailAddresses, java.lang.Boolean active,
		java.util.LinkedHashMap params, boolean andOperator, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_FN_MN_LN_SN_EA_A(companyId, firstNames,
			middleNames, lastNames, screenNames, emailAddresses, active,
			params, andOperator, begin, end, obc);
	}

	public static UserFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(UserFinder finder) {
		_finder = finder;
	}

	private static UserFinderUtil _getUtil() {
		if (_util == null) {
			_util = (UserFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = UserFinderUtil.class.getName();
	private static UserFinderUtil _util;
	private UserFinder _finder;
}