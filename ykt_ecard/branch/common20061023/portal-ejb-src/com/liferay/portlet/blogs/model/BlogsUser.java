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

package com.liferay.portlet.blogs.model;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserLocalServiceUtil;

import java.util.Date;

/**
 * <a href="BlogsUser.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class BlogsUser extends BlogsUserModel {

	public BlogsUser() {
		super();
	}

	public BlogsUser(String userId) {
		super(userId);
	}

	public BlogsUser(String userId, String companyId, String entryId,
					 Date lastPostDate) {

		super(userId, companyId, entryId, lastPostDate);
	}

	public String getFullName() throws PortalException, SystemException {
		if (_user == null) {
			_user = UserLocalServiceUtil.getUserById(getUserId());
		}

		return _user.getFullName();
	}

	public String getEmailAddress() throws PortalException, SystemException {
		if (_user == null) {
			_user = UserLocalServiceUtil.getUserById(getUserId());
		}

		return _user.getEmailAddress();
	}

	private User _user;

}