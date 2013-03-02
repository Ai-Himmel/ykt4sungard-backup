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

package com.liferay.portlet.wiki.service.persistence;

import java.util.Date;

/**
 * <a href="WikiNodeHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiNodeHBM {
	protected WikiNodeHBM() {
	}

	protected WikiNodeHBM(String nodeId) {
		_nodeId = nodeId;
	}

	protected WikiNodeHBM(String nodeId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate, String readRoles,
		String writeRoles, String name, String description, boolean sharing,
		Date lastPostDate) {
		_nodeId = nodeId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_readRoles = readRoles;
		_writeRoles = writeRoles;
		_name = name;
		_description = description;
		_sharing = sharing;
		_lastPostDate = lastPostDate;
	}

	public String getPrimaryKey() {
		return _nodeId;
	}

	protected void setPrimaryKey(String pk) {
		_nodeId = pk;
	}

	protected String getNodeId() {
		return _nodeId;
	}

	protected void setNodeId(String nodeId) {
		_nodeId = nodeId;
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

	protected String getReadRoles() {
		return _readRoles;
	}

	protected void setReadRoles(String readRoles) {
		_readRoles = readRoles;
	}

	protected String getWriteRoles() {
		return _writeRoles;
	}

	protected void setWriteRoles(String writeRoles) {
		_writeRoles = writeRoles;
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

	protected boolean getSharing() {
		return _sharing;
	}

	protected void setSharing(boolean sharing) {
		_sharing = sharing;
	}

	protected Date getLastPostDate() {
		return _lastPostDate;
	}

	protected void setLastPostDate(Date lastPostDate) {
		_lastPostDate = lastPostDate;
	}

	private String _nodeId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _readRoles;
	private String _writeRoles;
	private String _name;
	private String _description;
	private boolean _sharing;
	private Date _lastPostDate;
}