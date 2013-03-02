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

package com.liferay.portlet.softwarecatalog.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.softwarecatalog.model.SCProductEntry;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="SCProductEntryModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>SCProductEntry</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductEntry
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductEntryModel
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductEntryImpl
 *
 */
public class SCProductEntryModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "SCProductEntry";
	public static final Object[][] TABLE_COLUMNS = {
			{ "productEntryId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "type_", new Integer(Types.VARCHAR) },
			

			{ "tags", new Integer(Types.VARCHAR) },
			

			{ "shortDescription", new Integer(Types.VARCHAR) },
			

			{ "longDescription", new Integer(Types.VARCHAR) },
			

			{ "pageURL", new Integer(Types.VARCHAR) },
			

			{ "author", new Integer(Types.VARCHAR) },
			

			{ "repoGroupId", new Integer(Types.VARCHAR) },
			

			{ "repoArtifactId", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table SCProductEntry (productEntryId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,name VARCHAR(75) null,type_ VARCHAR(75) null,tags VARCHAR(300) null,shortDescription STRING null,longDescription STRING null,pageURL STRING null,author VARCHAR(75) null,repoGroupId VARCHAR(75) null,repoArtifactId VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table SCProductEntry";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.softwarecatalog.model.SCProductEntry"),
			true);
	public static final boolean CACHE_ENABLED_SCLICENSES_SCPRODUCTENTRIES = com.liferay.portlet.softwarecatalog.model.impl.SCLicenseModelImpl.CACHE_ENABLED_SCLICENSES_SCPRODUCTENTRIES;
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.softwarecatalog.model.SCProductEntry"));

	public SCProductEntryModelImpl() {
	}

	public long getPrimaryKey() {
		return _productEntryId;
	}

	public void setPrimaryKey(long pk) {
		setProductEntryId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_productEntryId);
	}

	public long getProductEntryId() {
		return _productEntryId;
	}

	public void setProductEntryId(long productEntryId) {
		if (productEntryId != _productEntryId) {
			_productEntryId = productEntryId;
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

	public String getTags() {
		return GetterUtil.getString(_tags);
	}

	public void setTags(String tags) {
		if (((tags == null) && (_tags != null)) ||
				((tags != null) && (_tags == null)) ||
				((tags != null) && (_tags != null) && !tags.equals(_tags))) {
			_tags = tags;
		}
	}

	public String getShortDescription() {
		return GetterUtil.getString(_shortDescription);
	}

	public void setShortDescription(String shortDescription) {
		if (((shortDescription == null) && (_shortDescription != null)) ||
				((shortDescription != null) && (_shortDescription == null)) ||
				((shortDescription != null) && (_shortDescription != null) &&
				!shortDescription.equals(_shortDescription))) {
			_shortDescription = shortDescription;
		}
	}

	public String getLongDescription() {
		return GetterUtil.getString(_longDescription);
	}

	public void setLongDescription(String longDescription) {
		if (((longDescription == null) && (_longDescription != null)) ||
				((longDescription != null) && (_longDescription == null)) ||
				((longDescription != null) && (_longDescription != null) &&
				!longDescription.equals(_longDescription))) {
			_longDescription = longDescription;
		}
	}

	public String getPageURL() {
		return GetterUtil.getString(_pageURL);
	}

	public void setPageURL(String pageURL) {
		if (((pageURL == null) && (_pageURL != null)) ||
				((pageURL != null) && (_pageURL == null)) ||
				((pageURL != null) && (_pageURL != null) &&
				!pageURL.equals(_pageURL))) {
			_pageURL = pageURL;
		}
	}

	public String getAuthor() {
		return GetterUtil.getString(_author);
	}

	public void setAuthor(String author) {
		if (((author == null) && (_author != null)) ||
				((author != null) && (_author == null)) ||
				((author != null) && (_author != null) &&
				!author.equals(_author))) {
			_author = author;
		}
	}

	public String getRepoGroupId() {
		return GetterUtil.getString(_repoGroupId);
	}

	public void setRepoGroupId(String repoGroupId) {
		if (((repoGroupId == null) && (_repoGroupId != null)) ||
				((repoGroupId != null) && (_repoGroupId == null)) ||
				((repoGroupId != null) && (_repoGroupId != null) &&
				!repoGroupId.equals(_repoGroupId))) {
			_repoGroupId = repoGroupId;
		}
	}

	public String getRepoArtifactId() {
		return GetterUtil.getString(_repoArtifactId);
	}

	public void setRepoArtifactId(String repoArtifactId) {
		if (((repoArtifactId == null) && (_repoArtifactId != null)) ||
				((repoArtifactId != null) && (_repoArtifactId == null)) ||
				((repoArtifactId != null) && (_repoArtifactId != null) &&
				!repoArtifactId.equals(_repoArtifactId))) {
			_repoArtifactId = repoArtifactId;
		}
	}

	public SCProductEntry toEscapedModel() {
		if (isEscapedModel()) {
			return (SCProductEntry)this;
		}
		else {
			SCProductEntry model = new SCProductEntryImpl();

			model.setEscapedModel(true);

			model.setProductEntryId(getProductEntryId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setName(Html.escape(getName()));
			model.setType(Html.escape(getType()));
			model.setTags(Html.escape(getTags()));
			model.setShortDescription(Html.escape(getShortDescription()));
			model.setLongDescription(Html.escape(getLongDescription()));
			model.setPageURL(Html.escape(getPageURL()));
			model.setAuthor(Html.escape(getAuthor()));
			model.setRepoGroupId(Html.escape(getRepoGroupId()));
			model.setRepoArtifactId(Html.escape(getRepoArtifactId()));

			model = (SCProductEntry)Proxy.newProxyInstance(SCProductEntry.class.getClassLoader(),
					new Class[] { SCProductEntry.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		SCProductEntryImpl clone = new SCProductEntryImpl();

		clone.setProductEntryId(getProductEntryId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setName(getName());
		clone.setType(getType());
		clone.setTags(getTags());
		clone.setShortDescription(getShortDescription());
		clone.setLongDescription(getLongDescription());
		clone.setPageURL(getPageURL());
		clone.setAuthor(getAuthor());
		clone.setRepoGroupId(getRepoGroupId());
		clone.setRepoArtifactId(getRepoArtifactId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		SCProductEntryImpl scProductEntry = (SCProductEntryImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getModifiedDate(),
				scProductEntry.getModifiedDate());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		value = getName().compareTo(scProductEntry.getName());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		SCProductEntryImpl scProductEntry = null;

		try {
			scProductEntry = (SCProductEntryImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = scProductEntry.getPrimaryKey();

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

	private long _productEntryId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _name;
	private String _type;
	private String _tags;
	private String _shortDescription;
	private String _longDescription;
	private String _pageURL;
	private String _author;
	private String _repoGroupId;
	private String _repoArtifactId;
}