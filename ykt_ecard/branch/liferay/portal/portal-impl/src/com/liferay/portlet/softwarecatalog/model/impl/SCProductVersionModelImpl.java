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

import com.liferay.portlet.softwarecatalog.model.SCProductVersion;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="SCProductVersionModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>SCProductVersion</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductVersion
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductVersionModel
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductVersionImpl
 *
 */
public class SCProductVersionModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "SCProductVersion";
	public static final Object[][] TABLE_COLUMNS = {
			{ "productVersionId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "productEntryId", new Integer(Types.BIGINT) },
			

			{ "version", new Integer(Types.VARCHAR) },
			

			{ "changeLog", new Integer(Types.VARCHAR) },
			

			{ "downloadPageURL", new Integer(Types.VARCHAR) },
			

			{ "directDownloadURL", new Integer(Types.VARCHAR) },
			

			{ "repoStoreArtifact", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table SCProductVersion (productVersionId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,productEntryId LONG,version VARCHAR(75) null,changeLog STRING null,downloadPageURL STRING null,directDownloadURL VARCHAR(2000) null,repoStoreArtifact BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table SCProductVersion";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.softwarecatalog.model.SCProductVersion"),
			true);
	public static final boolean CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS = com.liferay.portlet.softwarecatalog.model.impl.SCFrameworkVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.softwarecatalog.model.SCProductVersion"));

	public SCProductVersionModelImpl() {
	}

	public long getPrimaryKey() {
		return _productVersionId;
	}

	public void setPrimaryKey(long pk) {
		setProductVersionId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_productVersionId);
	}

	public long getProductVersionId() {
		return _productVersionId;
	}

	public void setProductVersionId(long productVersionId) {
		if (productVersionId != _productVersionId) {
			_productVersionId = productVersionId;
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

	public long getProductEntryId() {
		return _productEntryId;
	}

	public void setProductEntryId(long productEntryId) {
		if (productEntryId != _productEntryId) {
			_productEntryId = productEntryId;
		}
	}

	public String getVersion() {
		return GetterUtil.getString(_version);
	}

	public void setVersion(String version) {
		if (((version == null) && (_version != null)) ||
				((version != null) && (_version == null)) ||
				((version != null) && (_version != null) &&
				!version.equals(_version))) {
			_version = version;
		}
	}

	public String getChangeLog() {
		return GetterUtil.getString(_changeLog);
	}

	public void setChangeLog(String changeLog) {
		if (((changeLog == null) && (_changeLog != null)) ||
				((changeLog != null) && (_changeLog == null)) ||
				((changeLog != null) && (_changeLog != null) &&
				!changeLog.equals(_changeLog))) {
			_changeLog = changeLog;
		}
	}

	public String getDownloadPageURL() {
		return GetterUtil.getString(_downloadPageURL);
	}

	public void setDownloadPageURL(String downloadPageURL) {
		if (((downloadPageURL == null) && (_downloadPageURL != null)) ||
				((downloadPageURL != null) && (_downloadPageURL == null)) ||
				((downloadPageURL != null) && (_downloadPageURL != null) &&
				!downloadPageURL.equals(_downloadPageURL))) {
			_downloadPageURL = downloadPageURL;
		}
	}

	public String getDirectDownloadURL() {
		return GetterUtil.getString(_directDownloadURL);
	}

	public void setDirectDownloadURL(String directDownloadURL) {
		if (((directDownloadURL == null) && (_directDownloadURL != null)) ||
				((directDownloadURL != null) && (_directDownloadURL == null)) ||
				((directDownloadURL != null) && (_directDownloadURL != null) &&
				!directDownloadURL.equals(_directDownloadURL))) {
			_directDownloadURL = directDownloadURL;
		}
	}

	public boolean getRepoStoreArtifact() {
		return _repoStoreArtifact;
	}

	public boolean isRepoStoreArtifact() {
		return _repoStoreArtifact;
	}

	public void setRepoStoreArtifact(boolean repoStoreArtifact) {
		if (repoStoreArtifact != _repoStoreArtifact) {
			_repoStoreArtifact = repoStoreArtifact;
		}
	}

	public SCProductVersion toEscapedModel() {
		if (isEscapedModel()) {
			return (SCProductVersion)this;
		}
		else {
			SCProductVersion model = new SCProductVersionImpl();

			model.setEscapedModel(true);

			model.setProductVersionId(getProductVersionId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setProductEntryId(getProductEntryId());
			model.setVersion(Html.escape(getVersion()));
			model.setChangeLog(Html.escape(getChangeLog()));
			model.setDownloadPageURL(Html.escape(getDownloadPageURL()));
			model.setDirectDownloadURL(Html.escape(getDirectDownloadURL()));
			model.setRepoStoreArtifact(getRepoStoreArtifact());

			model = (SCProductVersion)Proxy.newProxyInstance(SCProductVersion.class.getClassLoader(),
					new Class[] { SCProductVersion.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		SCProductVersionImpl clone = new SCProductVersionImpl();

		clone.setProductVersionId(getProductVersionId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setProductEntryId(getProductEntryId());
		clone.setVersion(getVersion());
		clone.setChangeLog(getChangeLog());
		clone.setDownloadPageURL(getDownloadPageURL());
		clone.setDirectDownloadURL(getDirectDownloadURL());
		clone.setRepoStoreArtifact(getRepoStoreArtifact());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		SCProductVersionImpl scProductVersion = (SCProductVersionImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(),
				scProductVersion.getCreateDate());

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

		SCProductVersionImpl scProductVersion = null;

		try {
			scProductVersion = (SCProductVersionImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = scProductVersion.getPrimaryKey();

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

	private long _productVersionId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _productEntryId;
	private String _version;
	private String _changeLog;
	private String _downloadPageURL;
	private String _directDownloadURL;
	private boolean _repoStoreArtifact;
}