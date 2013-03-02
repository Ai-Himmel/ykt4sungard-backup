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

import com.liferay.portal.model.BaseModel;

import java.util.Date;

/**
 * <a href="JournalArticleModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>JournalArticle</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.model.JournalArticle
 * @see com.liferay.portlet.journal.service.model.impl.JournalArticleImpl
 * @see com.liferay.portlet.journal.service.model.impl.JournalArticleModelImpl
 *
 */
public interface JournalArticleModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public String getUuid();

	public void setUuid(String uuid);

	public long getId();

	public void setId(long id);

	public long getResourcePrimKey();

	public void setResourcePrimKey(long resourcePrimKey);

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

	public String getArticleId();

	public void setArticleId(String articleId);

	public double getVersion();

	public void setVersion(double version);

	public String getTitle();

	public void setTitle(String title);

	public String getDescription();

	public void setDescription(String description);

	public String getContent();

	public void setContent(String content);

	public String getType();

	public void setType(String type);

	public String getStructureId();

	public void setStructureId(String structureId);

	public String getTemplateId();

	public void setTemplateId(String templateId);

	public Date getDisplayDate();

	public void setDisplayDate(Date displayDate);

	public boolean getApproved();

	public boolean isApproved();

	public void setApproved(boolean approved);

	public long getApprovedByUserId();

	public void setApprovedByUserId(long approvedByUserId);

	public String getApprovedByUserName();

	public void setApprovedByUserName(String approvedByUserName);

	public Date getApprovedDate();

	public void setApprovedDate(Date approvedDate);

	public boolean getExpired();

	public boolean isExpired();

	public void setExpired(boolean expired);

	public Date getExpirationDate();

	public void setExpirationDate(Date expirationDate);

	public Date getReviewDate();

	public void setReviewDate(Date reviewDate);

	public boolean getIndexable();

	public boolean isIndexable();

	public void setIndexable(boolean indexable);

	public boolean getSmallImage();

	public boolean isSmallImage();

	public void setSmallImage(boolean smallImage);

	public long getSmallImageId();

	public void setSmallImageId(long smallImageId);

	public String getSmallImageURL();

	public void setSmallImageURL(String smallImageURL);

	public JournalArticle toEscapedModel();
}