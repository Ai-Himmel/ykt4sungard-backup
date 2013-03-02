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
 * <a href="DLFileRankHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileRankHBM {
	protected DLFileRankHBM() {
	}

	protected DLFileRankHBM(DLFileRankPK pk) {
		_companyId = pk.companyId;
		_userId = pk.userId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
	}

	protected DLFileRankHBM(String companyId, String userId,
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

	protected void setPrimaryKey(DLFileRankPK pk) {
		_companyId = pk.companyId;
		_userId = pk.userId;
		_repositoryId = pk.repositoryId;
		_fileName = pk.fileName;
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

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	private String _companyId;
	private String _userId;
	private String _repositoryId;
	private String _fileName;
	private Date _createDate;
}