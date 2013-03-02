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

package com.liferay.portlet.calendar.service.persistence;

/**
 * <a href="CalEventFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalEventFinderUtil {
	public static java.util.List findByG_SD(long groupId,
		java.util.Date startDateGT, java.util.Date startDateLT,
		boolean timeZoneSensitive) throws com.liferay.portal.SystemException {
		return getFinder().findByG_SD(groupId, startDateGT, startDateLT,
			timeZoneSensitive);
	}

	public static java.util.List findByRemindBy()
		throws com.liferay.portal.SystemException {
		return getFinder().findByRemindBy();
	}

	public static CalEventFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(CalEventFinder finder) {
		_finder = finder;
	}

	private static CalEventFinderUtil _getUtil() {
		if (_util == null) {
			_util = (CalEventFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CalEventFinderUtil.class.getName();
	private static CalEventFinderUtil _util;
	private CalEventFinder _finder;
}