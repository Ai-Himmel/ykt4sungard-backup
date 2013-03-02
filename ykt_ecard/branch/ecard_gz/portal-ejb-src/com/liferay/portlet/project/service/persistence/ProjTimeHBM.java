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

package com.liferay.portlet.project.service.persistence;

import java.util.Date;

/**
 * <a href="ProjTimeHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTimeHBM {
	protected ProjTimeHBM() {
	}

	protected ProjTimeHBM(String timeId) {
		_timeId = timeId;
	}

	protected ProjTimeHBM(String timeId, String companyId, String userId,
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

	protected void setPrimaryKey(String pk) {
		_timeId = pk;
	}

	protected String getTimeId() {
		return _timeId;
	}

	protected void setTimeId(String timeId) {
		_timeId = timeId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getUserName() {
		return _userName;
	}

	protected void setUserName(String userName) {
		_userName = userName;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getProjectId() {
		return _projectId;
	}

	protected void setProjectId(String projectId) {
		_projectId = projectId;
	}

	protected String getTaskId() {
		return _taskId;
	}

	protected void setTaskId(String taskId) {
		_taskId = taskId;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected Date getStartDate() {
		return _startDate;
	}

	protected void setStartDate(Date startDate) {
		_startDate = startDate;
	}

	protected Date getEndDate() {
		return _endDate;
	}

	protected void setEndDate(Date endDate) {
		_endDate = endDate;
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