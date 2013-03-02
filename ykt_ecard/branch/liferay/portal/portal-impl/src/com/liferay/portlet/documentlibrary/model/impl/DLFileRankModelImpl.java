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
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.documentlibrary.model.DLFileRank;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="DLFileRankModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>DLFileRank</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileRank
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileRankModel
 * @see com.liferay.portlet.documentlibrary.service.model.impl.DLFileRankImpl
 *
 */
public class DLFileRankModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "DLFileRank";
	public static final Object[][] TABLE_COLUMNS = {
			{ "fileRankId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "folderId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table DLFileRank (fileRankId LONG not null primary key,companyId LONG,userId LONG,createDate DATE null,folderId LONG,name VARCHAR(300) null)";
	public static final String TABLE_SQL_DROP = "drop table DLFileRank";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.documentlibrary.model.DLFileRank"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.documentlibrary.model.DLFileRank"));

	public DLFileRankModelImpl() {
	}

	public long getPrimaryKey() {
		return _fileRankId;
	}

	public void setPrimaryKey(long pk) {
		setFileRankId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_fileRankId);
	}

	public long getFileRankId() {
		return _fileRankId;
	}

	public void setFileRankId(long fileRankId) {
		if (fileRankId != _fileRankId) {
			_fileRankId = fileRankId;
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

	public DLFileRank toEscapedModel() {
		if (isEscapedModel()) {
			return (DLFileRank)this;
		}
		else {
			DLFileRank model = new DLFileRankImpl();

			model.setEscapedModel(true);

			model.setFileRankId(getFileRankId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setCreateDate(getCreateDate());
			model.setFolderId(getFolderId());
			model.setName(Html.escape(getName()));

			model = (DLFileRank)Proxy.newProxyInstance(DLFileRank.class.getClassLoader(),
					new Class[] { DLFileRank.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		DLFileRankImpl clone = new DLFileRankImpl();

		clone.setFileRankId(getFileRankId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setCreateDate(getCreateDate());
		clone.setFolderId(getFolderId());
		clone.setName(getName());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileRankImpl dlFileRank = (DLFileRankImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(), dlFileRank.getCreateDate());

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

		DLFileRankImpl dlFileRank = null;

		try {
			dlFileRank = (DLFileRankImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = dlFileRank.getPrimaryKey();

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

	private long _fileRankId;
	private long _companyId;
	private long _userId;
	private Date _createDate;
	private long _folderId;
	private String _name;
}