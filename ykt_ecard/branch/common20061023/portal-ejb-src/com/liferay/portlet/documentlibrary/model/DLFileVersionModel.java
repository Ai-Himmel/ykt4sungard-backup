/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.documentlibrary.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="DLFileVersionModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.81 $
 *
 */
public class DLFileVersionModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.documentlibrary.model.DLFileVersion"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.documentlibrary.model.DLFileVersion"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileVersion"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileVersion.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_REPOSITORYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileVersion.repositoryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FILENAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileVersion.fileName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileVersion.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileVersion.userName"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.documentlibrary.model.DLFileVersionModel"));

	public DLFileVersionModel() {
	}

	public DLFileVersionModel(DLFileVersionPK pk) {
		_companyId = pk.companyId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
		_version = pk.version;
		setNew(true);
	}

	public DLFileVersionModel(String companyId, String repositoryId,
		String fileName, double version, String userId, String userName,
		Date createDate, int size) {
		_companyId = companyId;
		_repositoryId = repositoryId;
		_fileName = fileName;
		_version = version;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_size = size;
	}

	public DLFileVersionPK getPrimaryKey() {
		return new DLFileVersionPK(_companyId, _repositoryId, _fileName,
			_version);
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getRepositoryId() {
		return _repositoryId;
	}

	public void setRepositoryId(String repositoryId) {
		if (((repositoryId == null) && (_repositoryId != null)) ||
				((repositoryId != null) && (_repositoryId == null)) ||
				((repositoryId != null) && (_repositoryId != null) &&
				!repositoryId.equals(_repositoryId))) {
			if (!XSS_ALLOW_REPOSITORYID) {
				repositoryId = Xss.strip(repositoryId);
			}

			_repositoryId = repositoryId;
			setModified(true);
		}
	}

	public String getFileName() {
		return _fileName;
	}

	public void setFileName(String fileName) {
		if (((fileName == null) && (_fileName != null)) ||
				((fileName != null) && (_fileName == null)) ||
				((fileName != null) && (_fileName != null) &&
				!fileName.equals(_fileName))) {
			if (!XSS_ALLOW_FILENAME) {
				fileName = Xss.strip(fileName);
			}

			_fileName = fileName;
			setModified(true);
		}
	}

	public double getVersion() {
		return _version;
	}

	public void setVersion(double version) {
		if (version != _version) {
			_version = version;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
		}
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			if (!XSS_ALLOW_USERNAME) {
				userName = Xss.strip(userName);
			}

			_userName = userName;
			setModified(true);
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
			setModified(true);
		}
	}

	public int getSize() {
		return _size;
	}

	public void setSize(int size) {
		if (size != _size) {
			_size = size;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new DLFileVersion(getCompanyId(), getRepositoryId(),
			getFileName(), getVersion(), getUserId(), getUserName(),
			getCreateDate(), getSize());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileVersion dlFileVersion = (DLFileVersion)obj;
		int value = 0;
		value = getCompanyId().compareTo(dlFileVersion.getCompanyId());
		value = value * -1;

		if (value != 0) {
			return value;
		}

		value = getRepositoryId().compareTo(dlFileVersion.getRepositoryId());
		value = value * -1;

		if (value != 0) {
			return value;
		}

		value = getFileName().compareTo(dlFileVersion.getFileName());
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

		DLFileVersion dlFileVersion = null;

		try {
			dlFileVersion = (DLFileVersion)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		DLFileVersionPK pk = dlFileVersion.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _companyId;
	private String _repositoryId;
	private String _fileName;
	private double _version;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private int _size;
}