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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.persistence.BlogsCommentsUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsPropsUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsRefererUtil;
import com.liferay.portlet.blogs.service.spring.BlogsEntryLocalService;
import com.liferay.portlet.blogs.util.Indexer;

import java.io.IOException;

import java.util.Iterator;

/**
 * <a href="BlogsEntryLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsEntryLocalServiceImpl implements BlogsEntryLocalService {

	// Business methods

	public void deleteAll(String userId)
		throws PortalException, SystemException {

		Iterator itr = BlogsEntryUtil.findByUserId(userId).iterator();

		while (itr.hasNext()) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			deleteEntry(entry);
		}
	}

	public void deleteEntry(String entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		deleteEntry(entry);
	}

	public void deleteEntry(BlogsEntry entry)
		throws PortalException, SystemException {

		// Delete comments

		BlogsCommentsUtil.removeByEntryId(entry.getEntryId());

		// Delete props

		BlogsPropsUtil.removeByEntryId(entry.getEntryId());

		// Delete referers

		BlogsRefererUtil.removeByEntryId(entry.getEntryId());

		// Delete entry

		BlogsEntryUtil.remove(entry.getEntryId());

		// Update lucene

		try {
			Indexer.deleteEntry(
				entry.getCompanyId(), entry.getPortletId(), entry.getUserId(),
				entry.getEntryId());
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

}