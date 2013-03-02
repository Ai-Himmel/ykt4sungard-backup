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

import com.liferay.portlet.documentlibrary.model.DLFileVersion;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="DLFileVersionModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>DLFileVersion</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileVersion
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileVersionModel
 * @see com.liferay.portlet.documentlibrary.service.model.impl.DLFileVersionImpl
 *
 */
public class DLFileVersionModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "DLFileVersion";
	public static final Object[][] TABLE_COLUMNS = {
			{ "fileVersionId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "folderId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "version", new Integer(Types.DOUBLE) },
			

			{ "size_", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table DLFileVersion (fileVersionId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,folderId LONG,name VARCHAR(300) null,version DOUBLE,size_ INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table DLFileVersion";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.documentlibrary.model.DLFileVersion"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.documentlibrary.model.DLFileVersion"));

	public DLFileVersionModelImpl() {
	}

	public long getPrimaryKey() {
		return _fileVersionId;
	}

	public void setPrimaryKey(long pk) {
		setFileVersionId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_fileVersionId);
	}

	public long getFileVersionId() {
		return _fileVersionId;
	}

	public void setFileVersionId(long fileVersionId) {
		if (fileVersionId != _fileVersionId) {
			_fileVersionId = fileVersionId;
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

	public DLFileVersion toEscapedModel() {
		if (isEscapedModel()) {
			return (DLFileVersion)this;
		}
		else {
			DLFileVersion model = new DLFileVersionImpl();

			model.setEscapedModel(true);

			model.setFileVersionId(getFileVersionId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setFolderId(getFolderId());
			model.setName(Html.escape(getName()));
			model.setVersion(getVersion());
			model.setSize(getSize());

			model = (DLFileVersion)Proxy.newProxyInstance(DLFileVersion.class.getClassLoader(),
					new Class[] { DLFileVersion.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		DLFileVersionImpl clone = new DLFileVersionImpl();

		clone.setFileVersionId(getFileVersionId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setFolderId(getFolderId());
		clone.setName(getName());
		clone.setVersion(getVersion());
		clone.setSize(getSize());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileVersionImpl dlFileVersion = (DLFileVersionImpl)obj;

		int value = 0;

		if (getFolderId() < dlFileVersion.getFolderId()) {
			value = -1;
		}
		else if (getFolderId() > dlFileVersion.getFolderId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		value = value * -1;

		if (value != 0) {
			return value;
		}

		value = getName().compareTo(dlFileVersion.getName());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		if (getVersion() < dlFileVersion.getVersion()) {
			value = -1;
		}
		else if (getVersion() > dlFileVersion.getVersion()) {
			value = 1;
		}
		else {
			value = 0;
		}

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

		DLFileVersionImpl dlFileVersion = null;

		try {
			dlFileVersion = (DLFileVersionImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = dlFileVersion.getPrimaryKey();

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

	private long _fileVersionId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private long _folderId;
	private String _name;
	private double _version;
	private int _size;
}