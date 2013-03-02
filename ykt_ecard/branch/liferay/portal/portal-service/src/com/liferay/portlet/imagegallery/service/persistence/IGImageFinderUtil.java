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

package com.liferay.portlet.imagegallery.service.persistence;

/**
 * <a href="IGImageFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IGImageFinderUtil {
	public static int countByFolderIds(java.util.List folderIds)
		throws com.liferay.portal.SystemException {
		return getFinder().countByFolderIds(folderIds);
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getFinder().countByGroupId(groupId);
	}

	public static int countByG_U(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		return getFinder().countByG_U(groupId, userId);
	}

	public static java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getFinder().findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByNoAssets()
		throws com.liferay.portal.SystemException {
		return getFinder().findByNoAssets();
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByUuid_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getFinder().findByUuid_G(uuid, groupId);
	}

	public static java.util.List findByG_U(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getFinder().findByG_U(groupId, userId, begin, end);
	}

	public static IGImageFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(IGImageFinder finder) {
		_finder = finder;
	}

	private static IGImageFinderUtil _getUtil() {
		if (_util == null) {
			_util = (IGImageFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = IGImageFinderUtil.class.getName();
	private static IGImageFinderUtil _util;
	private IGImageFinder _finder;
}