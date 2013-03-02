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
 * <a href="UserGroupFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserGroupFinderUtil {
	public static int countByC_N_D(long companyId, java.lang.String name,
		java.lang.String description, java.util.LinkedHashMap params)
		throws com.liferay.portal.SystemException {
		return getFinder().countByC_N_D(companyId, name, description, params);
	}

	public static com.liferay.portal.model.UserGroup findByC_N(long companyId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getFinder().findByC_N(companyId, name);
	}

	public static java.util.List findByC_N_D(long companyId,
		java.lang.String name, java.lang.String description,
		java.util.LinkedHashMap params, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getFinder().findByC_N_D(companyId, name, description, params,
			begin, end, obc);
	}

	public static UserGroupFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(UserGroupFinder finder) {
		_finder = finder;
	}

	private static UserGroupFinderUtil _getUtil() {
		if (_util == null) {
			_util = (UserGroupFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = UserGroupFinderUtil.class.getName();
	private static UserGroupFinderUtil _util;
	private UserGroupFinder _finder;
}