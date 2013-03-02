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

package com.liferay.portlet.softwarecatalog.model;

import com.liferay.portal.model.BaseModel;

import java.util.Date;

/**
 * <a href="SCProductEntryModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>SCProductEntry</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductEntry
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductEntryImpl
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductEntryModelImpl
 *
 */
public interface SCProductEntryModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public long getProductEntryId();

	public void setProductEntryId(long productEntryId);

	public long getGroupId();

	public void setGroupId(long groupId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public long getUserId();

	public void setUserId(long userId);

	public String getUserName();

	public void setUserName(String userName);

	public Date getCreateDate();

	public void setCreateDate(Date createDate);

	public Date getModifiedDate();

	public void setModifiedDate(Date modifiedDate);

	public String getName();

	public void setName(String name);

	public String getType();

	public void setType(String type);

	public String getTags();

	public void setTags(String tags);

	public String getShortDescription();

	public void setShortDescription(String shortDescription);

	public String getLongDescription();

	public void setLongDescription(String longDescription);

	public String getPageURL();

	public void setPageURL(String pageURL);

	public String getAuthor();

	public void setAuthor(String author);

	public String getRepoGroupId();

	public void setRepoGroupId(String repoGroupId);

	public String getRepoArtifactId();

	public void setRepoArtifactId(String repoArtifactId);

	public SCProductEntry toEscapedModel();
}