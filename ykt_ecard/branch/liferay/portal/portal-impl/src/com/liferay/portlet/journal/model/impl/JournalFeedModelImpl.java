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

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.journal.model.JournalFeed;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="JournalFeedModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>JournalFeed</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.model.JournalFeed
 * @see com.liferay.portlet.journal.service.model.JournalFeedModel
 * @see com.liferay.portlet.journal.service.model.impl.JournalFeedImpl
 *
 */
public class JournalFeedModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "JournalFeed";
	public static final Object[][] TABLE_COLUMNS = {
			{ "uuid_", new Integer(Types.VARCHAR) },
			

			{ "id_", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "feedId", new Integer(Types.VARCHAR) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "type_", new Integer(Types.VARCHAR) },
			

			{ "structureId", new Integer(Types.VARCHAR) },
			

			{ "templateId", new Integer(Types.VARCHAR) },
			

			{ "rendererTemplateId", new Integer(Types.VARCHAR) },
			

			{ "delta", new Integer(Types.INTEGER) },
			

			{ "orderByCol", new Integer(Types.VARCHAR) },
			

			{ "orderByType", new Integer(Types.VARCHAR) },
			

			{ "targetLayoutFriendlyUrl", new Integer(Types.VARCHAR) },
			

			{ "targetPortletId", new Integer(Types.VARCHAR) },
			

			{ "contentField", new Integer(Types.VARCHAR) },
			

			{ "feedType", new Integer(Types.VARCHAR) },
			

			{ "feedVersion", new Integer(Types.DOUBLE) }
		};
	public static final String TABLE_SQL_CREATE = "create table JournalFeed (uuid_ VARCHAR(75) null,id_ LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,feedId VARCHAR(75) null,name VARCHAR(75) null,description STRING null,type_ VARCHAR(75) null,structureId VARCHAR(75) null,templateId VARCHAR(75) null,rendererTemplateId VARCHAR(75) null,delta INTEGER,orderByCol VARCHAR(75) null,orderByType VARCHAR(75) null,targetLayoutFriendlyUrl VARCHAR(75) null,targetPortletId VARCHAR(75) null,contentField VARCHAR(75) null,feedType VARCHAR(75) null,feedVersion DOUBLE)";
	public static final String TABLE_SQL_DROP = "drop table JournalFeed";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.journal.model.JournalFeed"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.journal.model.JournalFeed"));

	public JournalFeedModelImpl() {
	}

	public long getPrimaryKey() {
		return _id;
	}

	public void setPrimaryKey(long pk) {
		setId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_id);
	}

	public String getUuid() {
		return GetterUtil.getString(_uuid);
	}

	public void setUuid(String uuid) {
		if ((uuid != null) && (uuid != _uuid)) {
			_uuid = uuid;
		}
	}

	public long getId() {
		return _id;
	}

	public void setId(long id) {
		if (id != _id) {
			_id = id;
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

	public String getFeedId() {
		return GetterUtil.getString(_feedId);
	}

	public void setFeedId(String feedId) {
		if (((feedId == null) && (_feedId != null)) ||
				((feedId != null) && (_feedId == null)) ||
				((feedId != null) && (_feedId != null) &&
				!feedId.equals(_feedId))) {
			_feedId = feedId;
		}
	}

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
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

	public String getType() {
		return GetterUtil.getString(_type);
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			_type = type;
		}
	}

	public String getStructureId() {
		return GetterUtil.getString(_structureId);
	}

	public void setStructureId(String structureId) {
		if (((structureId == null) && (_structureId != null)) ||
				((structureId != null) && (_structureId == null)) ||
				((structureId != null) && (_structureId != null) &&
				!structureId.equals(_structureId))) {
			_structureId = structureId;
		}
	}

	public String getTemplateId() {
		return GetterUtil.getString(_templateId);
	}

	public void setTemplateId(String templateId) {
		if (((templateId == null) && (_templateId != null)) ||
				((templateId != null) && (_templateId == null)) ||
				((templateId != null) && (_templateId != null) &&
				!templateId.equals(_templateId))) {
			_templateId = templateId;
		}
	}

	public String getRendererTemplateId() {
		return GetterUtil.getString(_rendererTemplateId);
	}

	public void setRendererTemplateId(String rendererTemplateId) {
		if (((rendererTemplateId == null) && (_rendererTemplateId != null)) ||
				((rendererTemplateId != null) && (_rendererTemplateId == null)) ||
				((rendererTemplateId != null) && (_rendererTemplateId != null) &&
				!rendererTemplateId.equals(_rendererTemplateId))) {
			_rendererTemplateId = rendererTemplateId;
		}
	}

	public int getDelta() {
		return _delta;
	}

	public void setDelta(int delta) {
		if (delta != _delta) {
			_delta = delta;
		}
	}

	public String getOrderByCol() {
		return GetterUtil.getString(_orderByCol);
	}

	public void setOrderByCol(String orderByCol) {
		if (((orderByCol == null) && (_orderByCol != null)) ||
				((orderByCol != null) && (_orderByCol == null)) ||
				((orderByCol != null) && (_orderByCol != null) &&
				!orderByCol.equals(_orderByCol))) {
			_orderByCol = orderByCol;
		}
	}

	public String getOrderByType() {
		return GetterUtil.getString(_orderByType);
	}

	public void setOrderByType(String orderByType) {
		if (((orderByType == null) && (_orderByType != null)) ||
				((orderByType != null) && (_orderByType == null)) ||
				((orderByType != null) && (_orderByType != null) &&
				!orderByType.equals(_orderByType))) {
			_orderByType = orderByType;
		}
	}

	public String getTargetLayoutFriendlyUrl() {
		return GetterUtil.getString(_targetLayoutFriendlyUrl);
	}

	public void setTargetLayoutFriendlyUrl(String targetLayoutFriendlyUrl) {
		if (((targetLayoutFriendlyUrl == null) &&
				(_targetLayoutFriendlyUrl != null)) ||
				((targetLayoutFriendlyUrl != null) &&
				(_targetLayoutFriendlyUrl == null)) ||
				((targetLayoutFriendlyUrl != null) &&
				(_targetLayoutFriendlyUrl != null) &&
				!targetLayoutFriendlyUrl.equals(_targetLayoutFriendlyUrl))) {
			_targetLayoutFriendlyUrl = targetLayoutFriendlyUrl;
		}
	}

	public String getTargetPortletId() {
		return GetterUtil.getString(_targetPortletId);
	}

	public void setTargetPortletId(String targetPortletId) {
		if (((targetPortletId == null) && (_targetPortletId != null)) ||
				((targetPortletId != null) && (_targetPortletId == null)) ||
				((targetPortletId != null) && (_targetPortletId != null) &&
				!targetPortletId.equals(_targetPortletId))) {
			_targetPortletId = targetPortletId;
		}
	}

	public String getContentField() {
		return GetterUtil.getString(_contentField);
	}

	public void setContentField(String contentField) {
		if (((contentField == null) && (_contentField != null)) ||
				((contentField != null) && (_contentField == null)) ||
				((contentField != null) && (_contentField != null) &&
				!contentField.equals(_contentField))) {
			_contentField = contentField;
		}
	}

	public String getFeedType() {
		return GetterUtil.getString(_feedType);
	}

	public void setFeedType(String feedType) {
		if (((feedType == null) && (_feedType != null)) ||
				((feedType != null) && (_feedType == null)) ||
				((feedType != null) && (_feedType != null) &&
				!feedType.equals(_feedType))) {
			_feedType = feedType;
		}
	}

	public double getFeedVersion() {
		return _feedVersion;
	}

	public void setFeedVersion(double feedVersion) {
		if (feedVersion != _feedVersion) {
			_feedVersion = feedVersion;
		}
	}

	public JournalFeed toEscapedModel() {
		if (isEscapedModel()) {
			return (JournalFeed)this;
		}
		else {
			JournalFeed model = new JournalFeedImpl();

			model.setEscapedModel(true);

			model.setUuid(Html.escape(getUuid()));
			model.setId(getId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setFeedId(getFeedId());
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));
			model.setType(Html.escape(getType()));
			model.setStructureId(getStructureId());
			model.setTemplateId(getTemplateId());
			model.setRendererTemplateId(Html.escape(getRendererTemplateId()));
			model.setDelta(getDelta());
			model.setOrderByCol(Html.escape(getOrderByCol()));
			model.setOrderByType(Html.escape(getOrderByType()));
			model.setTargetLayoutFriendlyUrl(Html.escape(
					getTargetLayoutFriendlyUrl()));
			model.setTargetPortletId(Html.escape(getTargetPortletId()));
			model.setContentField(Html.escape(getContentField()));
			model.setFeedType(Html.escape(getFeedType()));
			model.setFeedVersion(getFeedVersion());

			model = (JournalFeed)Proxy.newProxyInstance(JournalFeed.class.getClassLoader(),
					new Class[] { JournalFeed.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		JournalFeedImpl clone = new JournalFeedImpl();

		clone.setUuid(getUuid());
		clone.setId(getId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setFeedId(getFeedId());
		clone.setName(getName());
		clone.setDescription(getDescription());
		clone.setType(getType());
		clone.setStructureId(getStructureId());
		clone.setTemplateId(getTemplateId());
		clone.setRendererTemplateId(getRendererTemplateId());
		clone.setDelta(getDelta());
		clone.setOrderByCol(getOrderByCol());
		clone.setOrderByType(getOrderByType());
		clone.setTargetLayoutFriendlyUrl(getTargetLayoutFriendlyUrl());
		clone.setTargetPortletId(getTargetPortletId());
		clone.setContentField(getContentField());
		clone.setFeedType(getFeedType());
		clone.setFeedVersion(getFeedVersion());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		JournalFeedImpl journalFeed = (JournalFeedImpl)obj;

		int value = 0;

		value = getFeedId().compareTo(journalFeed.getFeedId());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		JournalFeedImpl journalFeed = null;

		try {
			journalFeed = (JournalFeedImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = journalFeed.getPrimaryKey();

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

	private String _uuid;
	private long _id;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _feedId;
	private String _name;
	private String _description;
	private String _type;
	private String _structureId;
	private String _templateId;
	private String _rendererTemplateId;
	private int _delta;
	private String _orderByCol;
	private String _orderByType;
	private String _targetLayoutFriendlyUrl;
	private String _targetPortletId;
	private String _contentField;
	private String _feedType;
	private double _feedVersion;
}