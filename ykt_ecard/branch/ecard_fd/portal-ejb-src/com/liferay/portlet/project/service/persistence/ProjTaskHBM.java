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
import java.util.Set;

/**
 * <a href="ProjTaskHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTaskHBM {
	protected ProjTaskHBM() {
	}

	protected ProjTaskHBM(String taskId) {
		_taskId = taskId;
	}

	protected ProjTaskHBM(String taskId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate, String projectId,
		String name, String description, String comments,
		int estimatedDuration, Date estimatedEndDate, int actualDuration,
		Date actualEndDate, int status) {
		_taskId = taskId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_projectId = projectId;
		_name = name;
		_description = description;
		_comments = comments;
		_estimatedDuration = estimatedDuration;
		_estimatedEndDate = estimatedEndDate;
		_actualDuration = actualDuration;
		_actualEndDate = actualEndDate;
		_status = status;
	}

	public String getPrimaryKey() {
		return _taskId;
	}

	protected void setPrimaryKey(String pk) {
		_taskId = pk;
	}

	protected String getTaskId() {
		return _taskId;
	}

	protected void setTaskId(String taskId) {
		_taskId = taskId;
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

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected String getComments() {
		return _comments;
	}

	protected void setComments(String comments) {
		_comments = comments;
	}

	protected int getEstimatedDuration() {
		return _estimatedDuration;
	}

	protected void setEstimatedDuration(int estimatedDuration) {
		_estimatedDuration = estimatedDuration;
	}

	protected Date getEstimatedEndDate() {
		return _estimatedEndDate;
	}

	protected void setEstimatedEndDate(Date estimatedEndDate) {
		_estimatedEndDate = estimatedEndDate;
	}

	protected int getActualDuration() {
		return _actualDuration;
	}

	protected void setActualDuration(int actualDuration) {
		_actualDuration = actualDuration;
	}

	protected Date getActualEndDate() {
		return _actualEndDate;
	}

	protected void setActualEndDate(Date actualEndDate) {
		_actualEndDate = actualEndDate;
	}

	protected int getStatus() {
		return _status;
	}

	protected void setStatus(int status) {
		_status = status;
	}

	protected Set getUsers() {
		return _users;
	}

	protected void setUsers(Set users) {
		_users = users;
	}

	private String _taskId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _projectId;
	private String _name;
	private String _description;
	private String _comments;
	private int _estimatedDuration;
	private Date _estimatedEndDate;
	private int _actualDuration;
	private Date _actualEndDate;
	private int _status;
	private Set _users;
}