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

package com.liferay.portlet.wiki.service.persistence;

/**
 * <a href="WikiPageFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageFinderUtil {
	public static int countByCreateDate(long nodeId, java.util.Date createDate,
		boolean before) throws com.liferay.portal.SystemException {
		return getFinder().countByCreateDate(nodeId, createDate, before);
	}

	public static int countByCreateDate(long nodeId,
		java.sql.Timestamp createDate, boolean before)
		throws com.liferay.portal.SystemException {
		return getFinder().countByCreateDate(nodeId, createDate, before);
	}

	public static java.util.List findByCreateDate(long nodeId,
		java.util.Date createDate, boolean before, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getFinder().findByCreateDate(nodeId, createDate, before, begin,
			end);
	}

	public static java.util.List findByCreateDate(long nodeId,
		java.sql.Timestamp createDate, boolean before, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getFinder().findByCreateDate(nodeId, createDate, before, begin,
			end);
	}

	public static java.util.List findByNoAssets()
		throws com.liferay.portal.SystemException {
		return getFinder().findByNoAssets();
	}

	public static com.liferay.portlet.wiki.model.WikiPage findByUuid_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.wiki.NoSuchPageException {
		return getFinder().findByUuid_G(uuid, groupId);
	}

	public static WikiPageFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(WikiPageFinder finder) {
		_finder = finder;
	}

	private static WikiPageFinderUtil _getUtil() {
		if (_util == null) {
			_util = (WikiPageFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = WikiPageFinderUtil.class.getName();
	private static WikiPageFinderUtil _util;
	private WikiPageFinder _finder;
}