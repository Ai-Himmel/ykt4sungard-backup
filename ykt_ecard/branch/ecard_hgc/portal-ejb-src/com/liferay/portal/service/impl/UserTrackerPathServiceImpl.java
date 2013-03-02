/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.service.persistence.UserTrackerUtil;
import com.liferay.portal.service.spring.UserTrackerPathLocalServiceUtil;
import com.liferay.portal.service.spring.UserTrackerPathService;

import java.util.List;

/**
 * <a href="UserTrackerPathServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class UserTrackerPathServiceImpl
	extends PrincipalBean implements UserTrackerPathService {

	// Business methods

	public List getUserTrackerPaths(String userTrackerId, int begin, int end)
		throws PortalException, SystemException {

		UserTracker userTracker =
			UserTrackerUtil.findByPrimaryKey(userTrackerId);

		if (!hasAdministrator(userTracker.getCompanyId())) {
			throw new PrincipalException();
		}

		return UserTrackerPathLocalServiceUtil.getUserTrackerPaths(
			userTrackerId, begin, end);
	}

}