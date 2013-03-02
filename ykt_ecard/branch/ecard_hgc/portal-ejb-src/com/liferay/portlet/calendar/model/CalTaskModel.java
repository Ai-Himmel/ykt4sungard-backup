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

package com.liferay.portlet.calendar.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="CalTaskModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Rev: $
 *
 */
public class CalTaskModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.calendar.model.CalTask"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.calendar.model.CalTask"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalTask"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_TASKID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalTask.taskId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalTask.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalTask.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TITLE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalTask.title"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalTask.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.calendar.model.CalTaskModel"));

	public CalTaskModel() {
	}

	public CalTaskModel(String taskId) {
		_taskId = taskId;
		setNew(true);
	}

	public CalTaskModel(String taskId, String companyId, String userId,
		Date createDate, Date modifiedDate, String title, String description,
		boolean noDueDate, Date dueDate, int priority, int status) {
		_taskId = taskId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_title = title;
		_description = description;
		_noDueDate = noDueDate;
		_dueDate = dueDate;
		_priority = priority;
		_status = status;
	}

	public String getPrimaryKey() {
		return _taskId;
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

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			if (!XSS_ALLOW_TITLE) {
				title = Xss.strip(title);
			}

			_title = title;
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

	public boolean getNoDueDate() {
		return _noDueDate;
	}

	public boolean isNoDueDate() {
		return _noDueDate;
	}

	public void setNoDueDate(boolean noDueDate) {
		if (noDueDate != _noDueDate) {
			_noDueDate = noDueDate;
			setModified(true);
		}
	}

	public Date getDueDate() {
		return _dueDate;
	}

	public void setDueDate(Date dueDate) {
		if (((dueDate == null) && (_dueDate != null)) ||
				((dueDate != null) && (_dueDate == null)) ||
				((dueDate != null) && (_dueDate != null) &&
				!dueDate.equals(_dueDate))) {
			_dueDate = dueDate;
			setModified(true);
		}
	}

	public int getPriority() {
		return _priority;
	}

	public void setPriority(int priority) {
		if (priority != _priority) {
			_priority = priority;
			setModified(true);
		}
	}

	public int getStatus() {
		return _status;
	}

	public void setStatus(int status) {
		if (status != _status) {
			_status = status;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new CalTask(getTaskId(), getCompanyId(), getUserId(),
			getCreateDate(), getModifiedDate(), getTitle(), getDescription(),
			getNoDueDate(), getDueDate(), getPriority(), getStatus());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		CalTask calTask = (CalTask)obj;
		String pk = calTask.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		CalTask calTask = null;

		try {
			calTask = (CalTask)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = calTask.getPrimaryKey();

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

	private String _taskId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _title;
	private String _description;
	private boolean _noDueDate;
	private Date _dueDate;
	private int _priority;
	private int _status;
}