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

package com.liferay.portlet.tags.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.tags.model.TagsAsset;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="TagsAssetModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>TagsAsset</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.model.TagsAsset
 * @see com.liferay.portlet.tags.service.model.TagsAssetModel
 * @see com.liferay.portlet.tags.service.model.impl.TagsAssetImpl
 *
 */
public class TagsAssetModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "TagsAsset";
	public static final Object[][] TABLE_COLUMNS = {
			{ "assetId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "startDate", new Integer(Types.TIMESTAMP) },
			

			{ "endDate", new Integer(Types.TIMESTAMP) },
			

			{ "publishDate", new Integer(Types.TIMESTAMP) },
			

			{ "expirationDate", new Integer(Types.TIMESTAMP) },
			

			{ "mimeType", new Integer(Types.VARCHAR) },
			

			{ "title", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "summary", new Integer(Types.VARCHAR) },
			

			{ "url", new Integer(Types.VARCHAR) },
			

			{ "height", new Integer(Types.INTEGER) },
			

			{ "width", new Integer(Types.INTEGER) },
			

			{ "priority", new Integer(Types.DOUBLE) },
			

			{ "viewCount", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table TagsAsset (assetId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,classNameId LONG,classPK LONG,startDate DATE null,endDate DATE null,publishDate DATE null,expirationDate DATE null,mimeType VARCHAR(75) null,title VARCHAR(300) null,description STRING null,summary STRING null,url STRING null,height INTEGER,width INTEGER,priority DOUBLE,viewCount INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table TagsAsset";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.tags.model.TagsAsset"),
			true);
	public static final boolean CACHE_ENABLED_TAGSASSETS_TAGSENTRIES = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.TagsAssets_TagsEntries"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.tags.model.TagsAsset"));

	public TagsAssetModelImpl() {
	}

	public long getPrimaryKey() {
		return _assetId;
	}

	public void setPrimaryKey(long pk) {
		setAssetId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_assetId);
	}

	public long getAssetId() {
		return _assetId;
	}

	public void setAssetId(long assetId) {
		if (assetId != _assetId) {
			_assetId = assetId;
		}
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		if (classNameId != _classNameId) {
			_classNameId = classNameId;
		}
	}

	public long getClassPK() {
		return _classPK;
	}

	public void setClassPK(long classPK) {
		if (classPK != _classPK) {
			_classPK = classPK;
		}
	}

	public Date getStartDate() {
		return _startDate;
	}

	public void setStartDate(Date startDate) {
		if (((startDate == null) && (_startDate != null)) ||
				((startDate != null) && (_startDate == null)) ||
				((startDate != null) && (_startDate != null) &&
				!startDate.equals(_startDate))) {
			_startDate = startDate;
		}
	}

	public Date getEndDate() {
		return _endDate;
	}

	public void setEndDate(Date endDate) {
		if (((endDate == null) && (_endDate != null)) ||
				((endDate != null) && (_endDate == null)) ||
				((endDate != null) && (_endDate != null) &&
				!endDate.equals(_endDate))) {
			_endDate = endDate;
		}
	}

	public Date getPublishDate() {
		return _publishDate;
	}

	public void setPublishDate(Date publishDate) {
		if (((publishDate == null) && (_publishDate != null)) ||
				((publishDate != null) && (_publishDate == null)) ||
				((publishDate != null) && (_publishDate != null) &&
				!publishDate.equals(_publishDate))) {
			_publishDate = publishDate;
		}
	}

	public Date getExpirationDate() {
		return _expirationDate;
	}

	public void setExpirationDate(Date expirationDate) {
		if (((expirationDate == null) && (_expirationDate != null)) ||
				((expirationDate != null) && (_expirationDate == null)) ||
				((expirationDate != null) && (_expirationDate != null) &&
				!expirationDate.equals(_expirationDate))) {
			_expirationDate = expirationDate;
		}
	}

	public String getMimeType() {
		return GetterUtil.getString(_mimeType);
	}

	public void setMimeType(String mimeType) {
		if (((mimeType == null) && (_mimeType != null)) ||
				((mimeType != null) && (_mimeType == null)) ||
				((mimeType != null) && (_mimeType != null) &&
				!mimeType.equals(_mimeType))) {
			_mimeType = mimeType;
		}
	}

	public String getTitle() {
		return GetterUtil.getString(_title);
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			_title = title;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
		}
	}

	public String getSummary() {
		return GetterUtil.getString(_summary);
	}

	public void setSummary(String summary) {
		if (((summary == null) && (_summary != null)) ||
				((summary != null) && (_summary == null)) ||
				((summary != null) && (_summary != null) &&
				!summary.equals(_summary))) {
			_summary = summary;
		}
	}

	public String getUrl() {
		return GetterUtil.getString(_url);
	}

	public void setUrl(String url) {
		if (((url == null) && (_url != null)) ||
				((url != null) && (_url == null)) ||
				((url != null) && (_url != null) && !url.equals(_url))) {
			_url = url;
		}
	}

	public int getHeight() {
		return _height;
	}

	public void setHeight(int height) {
		if (height != _height) {
			_height = height;
		}
	}

	public int getWidth() {
		return _width;
	}

	public void setWidth(int width) {
		if (width != _width) {
			_width = width;
		}
	}

	public double getPriority() {
		return _priority;
	}

	public void setPriority(double priority) {
		if (priority != _priority) {
			_priority = priority;
		}
	}

	public int getViewCount() {
		return _viewCount;
	}

	public void setViewCount(int viewCount) {
		if (viewCount != _viewCount) {
			_viewCount = viewCount;
		}
	}

	public TagsAsset toEscapedModel() {
		if (isEscapedModel()) {
			return (TagsAsset)this;
		}
		else {
			TagsAsset model = new TagsAssetImpl();

			model.setEscapedModel(true);

			model.setAssetId(getAssetId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setStartDate(getStartDate());
			model.setEndDate(getEndDate());
			model.setPublishDate(getPublishDate());
			model.setExpirationDate(getExpirationDate());
			model.setMimeType(Html.escape(getMimeType()));
			model.setTitle(Html.escape(getTitle()));
			model.setDescription(Html.escape(getDescription()));
			model.setSummary(Html.escape(getSummary()));
			model.setUrl(Html.escape(getUrl()));
			model.setHeight(getHeight());
			model.setWidth(getWidth());
			model.setPriority(getPriority());
			model.setViewCount(getViewCount());

			model = (TagsAsset)Proxy.newProxyInstance(TagsAsset.class.getClassLoader(),
					new Class[] { TagsAsset.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		TagsAssetImpl clone = new TagsAssetImpl();

		clone.setAssetId(getAssetId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setStartDate(getStartDate());
		clone.setEndDate(getEndDate());
		clone.setPublishDate(getPublishDate());
		clone.setExpirationDate(getExpirationDate());
		clone.setMimeType(getMimeType());
		clone.setTitle(getTitle());
		clone.setDescription(getDescription());
		clone.setSummary(getSummary());
		clone.setUrl(getUrl());
		clone.setHeight(getHeight());
		clone.setWidth(getWidth());
		clone.setPriority(getPriority());
		clone.setViewCount(getViewCount());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		TagsAssetImpl tagsAsset = (TagsAssetImpl)obj;

		long pk = tagsAsset.getPrimaryKey();

		if (getPrimaryKey() < pk) {
			return -1;
		}
		else if (getPrimaryKey() > pk) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		TagsAssetImpl tagsAsset = null;

		try {
			tagsAsset = (TagsAssetImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = tagsAsset.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private long _assetId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _classNameId;
	private long _classPK;
	private Date _startDate;
	private Date _endDate;
	private Date _publishDate;
	private Date _expirationDate;
	private String _mimeType;
	private String _title;
	private String _description;
	private String _summary;
	private String _url;
	private int _height;
	private int _width;
	private double _priority;
	private int _viewCount;
}