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

package com.liferay.portlet.blogs.service.impl;

import com.liferay.portal.SystemException;
import com.liferay.portlet.blogs.NoSuchUserException;
import com.liferay.portlet.blogs.model.BlogsUser;
import com.liferay.portlet.blogs.service.persistence.BlogsUserUtil;
import com.liferay.portlet.blogs.service.spring.BlogsUserLocalService;

import java.util.Date;

/**
 * <a href="BlogsUserLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsUserLocalServiceImpl implements BlogsUserLocalService {

	// Business methods

	public void deleteUser(String userId) throws SystemException {
		try {
			BlogsUserUtil.remove(userId);
		}
		catch (NoSuchUserException nsue) {
		}
	}

	public BlogsUser updateUser(String userId, String companyId, String entryId)
		throws SystemException {

		BlogsUser user = null;

		try {
			user = BlogsUserUtil.findByPrimaryKey(userId);
		}
		catch (NoSuchUserException nsue) {
			user = BlogsUserUtil.create(userId);
		}

		user.setCompanyId(companyId);
		user.setEntryId(entryId);
		user.setLastPostDate(new Date());

		BlogsUserUtil.update(user);

		return user;
	}

}