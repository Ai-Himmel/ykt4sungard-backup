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

import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="DLFileProfileModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.80 $
 *
 */
public class DLFileProfileModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.documentlibrary.model.DLFileProfile"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.documentlibrary.model.DLFileProfile"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_REPOSITORYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.repositoryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FILENAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.fileName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_VERSIONUSERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.versionUserId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_VERSIONUSERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.versionUserName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_READROLES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.readRoles"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_WRITEROLES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.writeRoles"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileProfile.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.documentlibrary.model.DLFileProfileModel"));

	public DLFileProfileModel() {
	}

	public DLFileProfileModel(DLFileProfilePK pk) {
		_companyId = pk.companyId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
		setNew(true);
	}

	public DLFileProfileModel(String companyId, String repositoryId,
		String fileName, String userId, String userName, String versionUserId,
		String versionUserName, Date createDate, Date modifiedDate,
		String readRoles, String writeRoles, String description,
		double version, int size) {
		_companyId = companyId;
		_repositoryId = repositoryId;
		_fileName = fileName;
		_userId = userId;
		_userName = userName;
		_versionUserId = versionUserId;
		_versionUserName = versionUserName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_readRoles = readRoles;
		_writeRoles = writeRoles;
		_description = description;
		_version = version;
		_size = size;
	}

	public DLFileProfilePK getPrimaryKey() {
		return new DLFileProfilePK(_companyId, _repositoryId, _fileName);
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

	public String getVersionUserId() {
		return _versionUserId;
	}

	public void setVersionUserId(String versionUserId) {
		if (((versionUserId == null) && (_versionUserId != null)) ||
				((versionUserId != null) && (_versionUserId == null)) ||
				((versionUserId != null) && (_versionUserId != null) &&
				!versionUserId.equals(_versionUserId))) {
			if (!XSS_ALLOW_VERSIONUSERID) {
				versionUserId = Xss.strip(versionUserId);
			}

			_versionUserId = versionUserId;
			setModified(true);
		}
	}

	public String getVersionUserName() {
		return _versionUserName;
	}

	public void setVersionUserName(String versionUserName) {
		if (((versionUserName == null) && (_versionUserName != null)) ||
				((versionUserName != null) && (_versionUserName == null)) ||
				((versionUserName != null) && (_versionUserName != null) &&
				!versionUserName.equals(_versionUserName))) {
			if (!XSS_ALLOW_VERSIONUSERNAME) {
				versionUserName = Xss.strip(versionUserName);
			}

			_versionUserName = versionUserName;
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

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
			setModified(true);
		}
	}

	public String getReadRoles() {
		return _readRoles;
	}

	public void setReadRoles(String readRoles) {
		if (((readRoles == null) && (_readRoles != null)) ||
				((readRoles != null) && (_readRoles == null)) ||
				((readRoles != null) && (_readRoles != null) &&
				!readRoles.equals(_readRoles))) {
			if (!XSS_ALLOW_READROLES) {
				readRoles = Xss.strip(readRoles);
			}

			_readRoles = readRoles;
			setModified(true);
		}
	}

	public String getWriteRoles() {
		return _writeRoles;
	}

	public void setWriteRoles(String writeRoles) {
		if (((writeRoles == null) && (_writeRoles != null)) ||
				((writeRoles != null) && (_writeRoles == null)) ||
				((writeRoles != null) && (_writeRoles != null) &&
				!writeRoles.equals(_writeRoles))) {
			if (!XSS_ALLOW_WRITEROLES) {
				writeRoles = Xss.strip(writeRoles);
			}

			_writeRoles = writeRoles;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
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
		return new DLFileProfile(getCompanyId(), getRepositoryId(),
			getFileName(), getUserId(), getUserName(), getVersionUserId(),
			getVersionUserName(), getCreateDate(), getModifiedDate(),
			getReadRoles(), getWriteRoles(), getDescription(), getVersion(),
			getSize());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileProfile dlFileProfile = (DLFileProfile)obj;
		DLFileProfilePK pk = dlFileProfile.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		DLFileProfile dlFileProfile = null;

		try {
			dlFileProfile = (DLFileProfile)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		DLFileProfilePK pk = dlFileProfile.getPrimaryKey();

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
	private String _userId;
	private String _userName;
	private String _versionUserId;
	private String _versionUserName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _readRoles;
	private String _writeRoles;
	private String _description;
	private double _version;
	private int _size;
}