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

package com.liferay.portlet.calendar.service.persistence;

import java.util.Date;

/**
 * <a href="CalTaskHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalTaskHBM {
	protected CalTaskHBM() {
	}

	protected CalTaskHBM(String taskId) {
		_taskId = taskId;
	}

	protected CalTaskHBM(String taskId, String companyId, String userId,
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

	protected String getTitle() {
		return _title;
	}

	protected void setTitle(String title) {
		_title = title;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected boolean getNoDueDate() {
		return _noDueDate;
	}

	protected void setNoDueDate(boolean noDueDate) {
		_noDueDate = noDueDate;
	}

	protected Date getDueDate() {
		return _dueDate;
	}

	protected void setDueDate(Date dueDate) {
		_dueDate = dueDate;
	}

	protected int getPriority() {
		return _priority;
	}

	protected void setPriority(int priority) {
		_priority = priority;
	}

	protected int getStatus() {
		return _status;
	}

	protected void setStatus(int status) {
		_status = status;
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