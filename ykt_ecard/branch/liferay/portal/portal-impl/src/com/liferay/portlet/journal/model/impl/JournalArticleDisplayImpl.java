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

package com.liferay.portlet.journal.model.impl;

import com.liferay.portlet.journal.model.JournalArticleDisplay;

/**
 * <a href="JournalArticleDisplayImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class JournalArticleDisplayImpl implements JournalArticleDisplay {

	public JournalArticleDisplayImpl(
		long id, long resourcePrimKey, long groupId, long userId,
		String articleId, double version, String title, String description,
		String[] availableLocales, String content, String type,
		String structureId, String templateId, boolean smallImage,
		long smallImageId, String smallImageURL, int numberOfPages,
		int currentPage, boolean paginate, boolean cacheable) {

		_id = id;
		_resourcePrimKey = resourcePrimKey;
		_groupId = groupId;
		_userId = userId;
		_articleId = articleId;
		_version = version;
		_title = title;
		_description = description;
		_availableLocales = availableLocales;
		_content = content;
		_type = type;
		_structureId = structureId;
		_templateId = templateId;
		_smallImage = smallImage;
		_smallImageId = smallImageId;
		_smallImageURL = smallImageURL;
		_numberOfPages = numberOfPages;
		_currentPage = currentPage;
		_paginate = paginate;
		_cacheable = cacheable;
	}

	public long getId() {
		return _id;
	}

	public long getResourcePrimKey() {
		return _resourcePrimKey;
	}

	public long getGroupId() {
		return _groupId;
	}

	public long getUserId() {
		return _userId;
	}

	public String getArticleId() {
		return _articleId;
	}

	public double getVersion() {
		return _version;
	}

	public String getTitle() {
		return _title;
	}

	public String getDescription() {
		return _description;
	}

	public String[] getAvailableLocales() {
		return _availableLocales;
	}

	public String getContent() {
		return _content;
	}

	public void setContent(String content) {
		_content = content;
	}

	public String getType() {
		return _type;
	}

	public String getStructureId() {
		return _structureId;
	}

	public void setStructureId(String structureId) {
		_structureId = structureId;
	}

	public String getTemplateId() {
		return _templateId;
	}

	public void setTemplateId(String templateId) {
		_templateId = templateId;
	}

	public boolean isSmallImage() {
		return _smallImage;
	}

	public void setSmallImage(boolean smallImage) {
		_smallImage = smallImage;
	}

	public long getSmallImageId() {
		return _smallImageId;
	}

	public void setSmallImageId(long smallImageId) {
		_smallImageId = smallImageId;
	}

	public String getSmallImageURL() {
		return _smallImageURL;
	}

	public void setSmallImageURL(String smallImageURL) {
		_smallImageURL = smallImageURL;
	}

	public int getNumberOfPages() {
		return _numberOfPages;
	}

	public void setNumberOfPages(int numberOfPages) {
		_numberOfPages = numberOfPages;
	}

	public int getCurrentPage() {
		return _currentPage;
	}

	public void setCurrentPage(int currentPage) {
		_currentPage = currentPage;
	}

	public boolean isPaginate() {
		return _paginate;
	}

	public void setPaginate(boolean paginate) {
		_paginate = paginate;
	}

	public boolean isCacheable() {
		return _cacheable;
	}

	public void setCacheable(boolean cacheable) {
		_cacheable = cacheable;
	}

	private long _id;
	private long _resourcePrimKey;
	private long _groupId;
	private long _userId;
	private String _articleId;
	private double _version;
	private String _title;
	private String _description;
	private String[] _availableLocales;
	private String _content;
	private String _type;
	private String _structureId;
	private String _templateId;
	private boolean _smallImage;
	private long _smallImageId;
	private String _smallImageURL;
	private int _numberOfPages;
	private int _currentPage;
	private boolean _paginate;
	private boolean _cacheable;

}