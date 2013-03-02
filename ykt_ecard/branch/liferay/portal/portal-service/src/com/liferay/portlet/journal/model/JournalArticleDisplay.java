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

package com.liferay.portlet.journal.model;

import java.io.Serializable;

/**
 * <a href="JournalArticleDisplay.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public interface JournalArticleDisplay extends Serializable {

	public long getId();

	public long getResourcePrimKey();

	public long getGroupId();

	public long getUserId();

	public String getArticleId();

	public double getVersion();

	public String getTitle();

	public String getDescription();

	public String[] getAvailableLocales();

	public String getContent();

	public void setContent(String content);

	public String getType();

	public String getStructureId();

	public void setStructureId(String structureId);

	public String getTemplateId();

	public void setTemplateId(String templateId);

	public boolean isSmallImage();

	public void setSmallImage(boolean smallImage);

	public long getSmallImageId();

	public void setSmallImageId(long smallImageId);

	public String getSmallImageURL();

	public void setSmallImageURL(String smallImageURL);

	public int getNumberOfPages();

	public void setNumberOfPages(int numberOfPages);

	public int getCurrentPage();

	public void setCurrentPage(int currentPage);

	public boolean isPaginate();

	public void setPaginate(boolean paginate);

	public boolean isCacheable();

	public void setCacheable(boolean cacheable);

}