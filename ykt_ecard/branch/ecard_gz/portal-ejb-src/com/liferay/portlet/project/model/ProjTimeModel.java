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
 * <a href="ProjTimeModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class ProjTimeModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.project.model.ProjTime"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.project.model.ProjTime"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_TIMEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.timeId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PROJECTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.projectId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TASKID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.taskId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.project.model.ProjTime.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.project.model.ProjTimeModel"));

	public ProjTimeModel() {
	}

	public ProjTimeModel(String timeId) {
		_timeId = timeId;
		setNew(true);
	}

	public ProjTimeModel(String timeId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate, String projectId,
		String taskId, String description, Date startDate, Date endDate) {
		_timeId = timeId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_projectId = projectId;
		_taskId = taskId;
		_description = description;
		_startDate = startDate;
		_endDate = endDate;
	}

	public String getPrimaryKey() {
		return _timeId;
	}

	public String getTimeId() {
		return _timeId;
	}

	public void setTimeId(String timeId) {
		if (((timeId == null) && (_timeId != null)) ||
				((timeId != null) && (_timeId == null)) ||
				((timeId != null) && (_timeId != null) &&
				!timeId.equals(_timeId))) {
			if (!XSS_ALLOW_TIMEID) {
				timeId = Xss.strip(timeId);
			}

			_timeId = timeId;
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

	public String getTaskId() {
		return _taskId;
	}

	public void setTaskId(String taskId) {
		if (((taskId == null) && (_taskId != null)) ||
				((taskId != null) && (_taskId == null)) ||
				((taskId != null) && (_taskId != null) &&
				!taskId.equals(_taskId))) {
			if (!XSS_ALLOW_TASKID) {
				taskId = Xss.strip(taskId);
			}

			_taskId = taskId;
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

	public Date getStartDate() {
		return _startDate;
	}

	public void setStartDate(Date startDate) {
		if (((startDate == null) && (_startDate != null)) ||
				((startDate != null) && (_startDate == null)) ||
				((startDate != null) && (_startDate != null) &&
				!startDate.equals(_startDate))) {
			_startDate = startDate;
			setModified(true);
		}
	}

	public Date getEndDate() {
		return _endDate;
	}

	public void setEndDate(Date endDate) {
		if (((endDate == null) && (_endDate != null)) ||
				((endDate != null) && (_endDate == null)) ||
				((endDate != null) && (_endDate != null) &&
				!endDate.equals(_endDate))) {
			_endDate = endDate;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ProjTime(getTimeId(), getCompanyId(), getUserId(),
			getUserName(), getCreateDate(), getModifiedDate(), getProjectId(),
			getTaskId(), getDescription(), getStartDate(), getEndDate());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ProjTime projTime = (ProjTime)obj;
		String pk = projTime.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ProjTime projTime = null;

		try {
			projTime = (ProjTime)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = projTime.getPrimaryKey();

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

	private String _timeId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _projectId;
	private String _taskId;
	private String _description;
	private Date _startDate;
	private Date _endDate;
}