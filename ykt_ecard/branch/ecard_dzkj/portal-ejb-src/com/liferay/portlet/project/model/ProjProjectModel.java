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

package com.liferay.portlet.project.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="ProjProjectModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class ProjProjectModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.project.model.ProjProject"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.project.model.ProjProject"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_PROJECTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.projectId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FIRMID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.firmId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CODE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.code"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjProject.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.project.model.ProjProjectModel"));

	public ProjProjectModel() {
	}

	public ProjProjectModel(String projectId) {
		_projectId = projectId;
		setNew(true);
	}

	public ProjProjectModel(String projectId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate, String firmId,
		String code, String name, String description) {
		_projectId = projectId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_firmId = firmId;
		_code = code;
		_name = name;
		_description = description;
	}

	public String getPrimaryKey() {
		return _projectId;
	}

	public String getProjectId() {
		return _projectId;
	}

	public void setProjectId(String projectId) {
		if (((projectId == null) && (_projectId != null)) ||
				((projectId != null) && (_projectId == null)) ||
				((projectId != null) && (_projectId != null) &&
				!projectId.equals(_projectId))) {
			if (!XSS_ALLOW_PROJECTID) {
				projectId = Xss.strip(projectId);
			}

			_projectId = projectId;
			setModified(true);
		}
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

	public String getFirmId() {
		return _firmId;
	}

	public void setFirmId(String firmId) {
		if (((firmId == null) && (_firmId != null)) ||
				((firmId != null) && (_firmId == null)) ||
				((firmId != null) && (_firmId != null) &&
				!firmId.equals(_firmId))) {
			if (!XSS_ALLOW_FIRMID) {
				firmId = Xss.strip(firmId);
			}

			_firmId = firmId;
			setModified(true);
		}
	}

	public String getCode() {
		return _code;
	}

	public void setCode(String code) {
		if (((code == null) && (_code != null)) ||
				((code != null) && (_code == null)) ||
				((code != null) && (_code != null) && !code.equals(_code))) {
			if (!XSS_ALLOW_CODE) {
				code = Xss.strip(code);
			}

			_code = code;
			setModified(true);
		}
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			if (!XSS_ALLOW_NAME) {
				name = Xss.strip(name);
			}

			_name = name;
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

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ProjProject(getProjectId(), getCompanyId(), getUserId(),
			getUserName(), getCreateDate(), getModifiedDate(), getFirmId(),
			getCode(), getName(), getDescription());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ProjProject projProject = (ProjProject)obj;
		int value = 0;
		value = getName().toLowerCase().compareTo(projProject.getName()
															 .toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ProjProject projProject = null;

		try {
			projProject = (ProjProject)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = projProject.getPrimaryKey();

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

	private String _projectId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _firmId;
	private String _code;
	private String _name;
	private String _description;
}