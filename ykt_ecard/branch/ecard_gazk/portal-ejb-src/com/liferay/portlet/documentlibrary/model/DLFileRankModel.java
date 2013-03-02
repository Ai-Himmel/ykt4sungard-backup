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

import com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="DLFileRankModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class DLFileRankModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.documentlibrary.model.DLFileRank"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.documentlibrary.model.DLFileRank"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileRank"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileRank.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileRank.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_REPOSITORYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileRank.repositoryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FILENAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.documentlibrary.model.DLFileRank.fileName"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.documentlibrary.model.DLFileRankModel"));

	public DLFileRankModel() {
	}

	public DLFileRankModel(DLFileRankPK pk) {
		_companyId = pk.companyId;
		_userId = pk.userId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
		setNew(true);
	}

	public DLFileRankModel(String companyId, String userId,
		String repositoryId, String fileName, Date createDate) {
		_companyId = companyId;
		_userId = userId;
		_repositoryId = repositoryId;
		_fileName = fileName;
		_createDate = createDate;
	}

	public DLFileRankPK getPrimaryKey() {
		return new DLFileRankPK(_companyId, _userId, _repositoryId, _fileName);
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

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new DLFileRank(getCompanyId(), getUserId(), getRepositoryId(),
			getFileName(), getCreateDate());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		DLFileRank dlFileRank = (DLFileRank)obj;
		int value = 0;
		value = getCreateDate().compareTo(dlFileRank.getCreateDate());
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

		DLFileRank dlFileRank = null;

		try {
			dlFileRank = (DLFileRank)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		DLFileRankPK pk = dlFileRank.getPrimaryKey();

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
	private String _userId;
	private String _repositoryId;
	private String _fileName;
	private Date _createDate;
}