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

package com.liferay.portlet.blogs.service.persistence;

/**
 * <a href="BlogsEntryHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryHBMUtil {
	public static com.liferay.portlet.blogs.model.BlogsEntry model(
		BlogsEntryHBM blogsEntryHBM) {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = BlogsEntryPool.get(blogsEntryHBM.getPrimaryKey());

		if (blogsEntry == null) {
			blogsEntry = new com.liferay.portlet.blogs.model.BlogsEntry(blogsEntryHBM.getEntryId(),
					blogsEntryHBM.getCompanyId(), blogsEntryHBM.getUserId(),
					blogsEntryHBM.getCreateDate(),
					blogsEntryHBM.getModifiedDate(),
					blogsEntryHBM.getCategoryId(), blogsEntryHBM.getTitle(),
					blogsEntryHBM.getContent(), blogsEntryHBM.getDisplayDate(),
					blogsEntryHBM.getSharing(), blogsEntryHBM.getCommentable(),
					blogsEntryHBM.getPropsCount(),
					blogsEntryHBM.getCommentsCount());
			BlogsEntryPool.put(blogsEntry.getPrimaryKey(), blogsEntry);
		}

		return blogsEntry;
	}
}