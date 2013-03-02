/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portlet.softwarecatalog.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="SCProductVersionSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.softwarecatalog.service.http.SCProductVersionServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.http.SCProductVersionServiceSoap
 *
 */
public class SCProductVersionSoap implements Serializable {
	public static SCProductVersionSoap toSoapModel(SCProductVersion model) {
		SCProductVersionSoap soapModel = new SCProductVersionSoap();

		soapModel.setProductVersionId(model.getProductVersionId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setProductEntryId(model.getProductEntryId());
		soapModel.setVersion(model.getVersion());
		soapModel.setChangeLog(model.getChangeLog());
		soapModel.setDownloadPageURL(model.getDownloadPageURL());
		soapModel.setDirectDownloadURL(model.getDirectDownloadURL());
		soapModel.setRepoStoreArtifact(model.getRepoStoreArtifact());

		return soapModel;
	}

	public static SCProductVersionSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			SCProductVersion model = (SCProductVersion)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (SCProductVersionSoap[])soapModels.toArray(new SCProductVersionSoap[0]);
	}

	public SCProductVersionSoap() {
	}

	public long getPrimaryKey() {
		return _productVersionId;
	}

	public void setPrimaryKey(long pk) {
		setProductVersionId(pk);
	}

	public long getProductVersionId() {
		return _productVersionId;
	}

	public void setProductVersionId(long productVersionId) {
		_productVersionId = productVersionId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		_userName = userName;
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	public long getProductEntryId() {
		return _productEntryId;
	}

	public void setProductEntryId(long productEntryId) {
		_productEntryId = productEntryId;
	}

	public String getVersion() {
		return _version;
	}

	public void setVersion(String version) {
		_version = version;
	}

	public String getChangeLog() {
		return _changeLog;
	}

	public void setChangeLog(String changeLog) {
		_changeLog = changeLog;
	}

	public String getDownloadPageURL() {
		return _downloadPageURL;
	}

	public void setDownloadPageURL(String downloadPageURL) {
		_downloadPageURL = downloadPageURL;
	}

	public String getDirectDownloadURL() {
		return _directDownloadURL;
	}

	public void setDirectDownloadURL(String directDownloadURL) {
		_directDownloadURL = directDownloadURL;
	}

	public boolean getRepoStoreArtifact() {
		return _repoStoreArtifact;
	}

	public boolean isRepoStoreArtifact() {
		return _repoStoreArtifact;
	}

	public void setRepoStoreArtifact(boolean repoStoreArtifact) {
		_repoStoreArtifact = repoStoreArtifact;
	}

	private long _productVersionId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _productEntryId;
	private String _version;
	private String _changeLog;
	private String _downloadPageURL;
	private String _directDownloadURL;
	private boolean _repoStoreArtifact;
}