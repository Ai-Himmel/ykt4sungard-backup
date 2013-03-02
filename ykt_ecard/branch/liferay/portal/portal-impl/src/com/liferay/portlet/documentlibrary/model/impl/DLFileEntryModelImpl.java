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

package com.liferay.portlet.documentlibrary.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.documentlibrary.model.DLFileEntry;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="DLFileEntryModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>DLFileEntry</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileEntry
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileEntryModel
 * @see com.liferay.portlet.documentlibrary.service.model.impl.DLFileEntryImpl
 *
 */
public class DLFileEntryModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "DLFileEntry";
	public static final Object[][] TABLE_COLUMNS = {
			{ "uuid_", new Integer(Types.VARCHAR) },
			

			{ "fileEntryId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "versionUserId", new Integer(Types.BIGINT) },
			

			{ "versionUserName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "folderId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "title", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "version", new Integer(Types.DOUBLE) },
			

			{ "size_", new Integer(Types.INTEGER) },
			

			{ "readCount", new Integer(Types.INTEGER) },
			

			{ "extraSettings", new Integer(Types.CLOB) }
		};
	public static final String TABLE_SQL_CREATE = "create table DLFileEntry (uuid_ VARCHAR(75) null,fileEntryId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,versionUserId LONG,versionUserName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,folderId LONG,name VARCHAR(300) null,title VARCHAR(300) null,description STRING null,version DOUBLE,size_ INTEGER,readCount INTEGER,extraSettings TEXT null)";
	public static final String TABLE_SQL_DROP = "drop table DLFileEntry";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.documentlibrary.model.DLFileEntry"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.documentlibrary.model.DLFileEntry"));

	public DLFileEntryModelImpl() {
	}

	public long getPrimaryKey() {
		return _fileEntryId;
	}

	public void setPrimaryKey(long pk) {
		setFileEntryId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_fileEntryId);
	}

	public String getUuid() {
		return GetterUtil.getString(_uuid);
	}

	public void setUuid(String uuid) {
		if ((uuid != null) && (uuid != _uuid)) {
			_uuid = uuid;
		}
	}

	public long getFileEntryId() {
		return _fileEntryId;
	}

	public void setFileEntryId(long fileEntryId) {
		if (fileEntryId != _fileEntryId) {
			_fileEntryId = fileEntryId;
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

	public long getVersionUserId() {
		return _versionUserId;
	}

	public void setVersionUserId(long versionUserId) {
		if (versionUserId != _versionUserId) {
			_versionUserId = versionUserId;
		}
	}

	public String getVersionUserName() {
		return GetterUtil.getString(_versionUserName);
	}

	public void setVersionUserName(String versionUserName) {
		if (((versionUserName == null) && (_versionUserName != null)) ||
				((versionUserName != null) && (_versionUserName == null)) ||
				((versionUserName != null) && (_versionUserName != null) &&
				!versionUserName.equals(_versionUserName))) {
			_versionUserName = versionUserName;
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

	public long getFolderId() {
		return _folderId;
	}

	public void setFolderId(long folderId) {
		if (folderId != _folderId) {
			_folderId = folderId;
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

	public double getVersion() {
		return _version;
	}

	public void setVersion(double version) {
		if (version != _version) {
			_version = version;
		}
	}

	public int getSize() {
		return _size;
	}

	public void setSize(int size) {
		if (size != _size) {
			_size = size;
		}
	}

	public int getReadCount() {
		return _readCount;
	}

	public void setReadCount(int readCount) {
		if (readCount != _readCount) {
			_readCount = readCount;
		}
	}

	public String getExtraSettings() {
		return GetterUtil.getString(_extraSettings);
	}

	public void setExtraSettings(String extraSettings) {
		if (((extraSettings == null) && (_extraSettings != null)) ||
				((extraSettings != null) && (_extraSettings == null)) ||
				((extraSettings != null) && (_extraSettings != null) &&
				!extraSettings.equals(_extraSettings))) {
			_extraSettings = extraSettings;
		}
	}

	public DLFileEntry toEscapedModel() {
		if (isEscapedModel()) {
			return (DLFileEntry)this;
		}
		else {
			DLFileEntry model = new DLFileEntryImpl();

			model.setEscapedModel(true);

			model.setUuid(Html.escape(getUuid()));
			model.setFileEntryId(getFileEntryId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setVersionUserId(getVersionUserId());
			model.setVersionUserName(Html.escape(getVersionUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setFolderId(getFolderId());
			model.setName(Html.escape(getName()));
			model.setTitle(Html.escape(getTitle()));
			model.setDescription(Html.escape(getDescription()));
			model.setVersion(getVersion());
			model.setSize(getSize());
			model.setReadCount(getReadCount());
			model.setExtraSettings(Html.escape(getExtraSettings()));

			model = (DLFileEntry)Proxy.newProxyInstance(DLFileEntry.class.getClassLoader(),
					new Class[] { DLFileEntry.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		DLFileEntryImpl clone = new DLFileEntryImpl();

		clone.setUuid(getUuid());
		clone.setFileEntryId(getFileEntryId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setVersionUserId(getVersionUserId());
		clone.setVersionUserName(getVersionUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setFolderId(getFolderId());
		clone.setName(getName());
		clone.setTitle(getTitle());
		clone.setDescription(getDescription());
		clone.setVersion(getVersion());
		clone.setSize(getSize());
		clone.setReadCount(getReadCount());
		clone.setExtraSettings(getExtraSettings());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileEntryImpl dlFileEntry = (DLFileEntryImpl)obj;

		int value = 0;

		if (getFolderId() < dlFileEntry.getFolderId()) {
			value = -1;
		}
		else if (getFolderId() > dlFileEntry.getFolderId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		value = getName().compareTo(dlFileEntry.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		DLFileEntryImpl dlFileEntry = null;

		try {
			dlFileEntry = (DLFileEntryImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = dlFileEntry.getPrimaryKey();

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
	private long _fileEntryId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private long _versionUserId;
	private String _versionUserName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _folderId;
	private String _name;
	private String _title;
	private String _description;
	private double _version;
	private int _size;
	private int _readCount;
	private String _extraSettings;
}