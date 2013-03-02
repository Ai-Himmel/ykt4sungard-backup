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

package com.liferay.portlet.documentlibrary.service.persistence;

import java.util.Date;

/**
 * <a href="DLFileVersionHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileVersionHBM {
	protected DLFileVersionHBM() {
	}

	protected DLFileVersionHBM(DLFileVersionPK pk) {
		_companyId = pk.companyId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
		_version = pk.version;
	}

	protected DLFileVersionHBM(String companyId, String repositoryId,
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

	protected void setPrimaryKey(DLFileVersionPK pk) {
		_companyId = pk.companyId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
		_version = pk.version;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getRepositoryId() {
		return _repositoryId;
	}

	protected void setRepositoryId(String repositoryId) {
		_repositoryId = repositoryId;
	}

	protected String getFileName() {
		return _fileName;
	}

	protected void setFileName(String fileName) {
		_fileName = fileName;
	}

	protected double getVersion() {
		return _version;
	}

	protected void setVersion(double version) {
		_version = version;
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

	protected int getSize() {
		return _size;
	}

	protected void setSize(int size) {
		_size = size;
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