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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.blogs.CommentsContentException;
import com.liferay.portlet.blogs.model.BlogsComments;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.persistence.BlogsCommentsUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.spring.BlogsCommentsService;
import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;

/**
 * <a href="BlogsCommentsServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsCommentsServiceImpl
	extends PrincipalBean implements BlogsCommentsService {

	// Business methods

	public BlogsComments addComments(String entryId, String content)
		throws PortalException, SystemException {

		_validate(entryId, content);

		User user = getUser();

		String commentsId = Long.toString(CounterServiceUtil.increment(
			BlogsComments.class.getName()));

		BlogsComments comments = BlogsCommentsUtil.create(commentsId);

		Date now = new Date();

		comments.setCompanyId(user.getCompanyId());
		comments.setUserId(user.getUserId());
		comments.setUserName(user.getFullName());
		comments.setCreateDate(now);
		comments.setModifiedDate(now);
		comments.setEntryId(entryId);
		comments.setContent(content);

		BlogsCommentsUtil.update(comments);

		// Update comments count

		BlogsEntryServiceUtil.updateCommentsCount(entryId);

		return comments;
	}

	public void deleteComments(String commentsId)
		throws PortalException, SystemException {

		BlogsComments comments =
			BlogsCommentsUtil.findByPrimaryKey(commentsId);

		BlogsEntry entry =
			BlogsEntryUtil.findByPrimaryKey(comments.getEntryId());

		if (!entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		BlogsCommentsUtil.remove(comments.getCommentsId());
	}

	public BlogsComments getComments(String commentsId)
		throws PortalException, SystemException {

		return BlogsCommentsUtil.findByPrimaryKey(commentsId);
	}

	public List getCommentsList(String entryId) throws SystemException {
		return BlogsCommentsUtil.findByEntryId(entryId);
	}

	// Private methods

	private void _validate(String entryId, String content)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		if (!entry.getCompanyId().equals(getUser().getCompanyId())) {
			throw new PrincipalException();
		}

		if (Validator.isNull(content)) {
			throw new CommentsContentException();
		}
	}

}