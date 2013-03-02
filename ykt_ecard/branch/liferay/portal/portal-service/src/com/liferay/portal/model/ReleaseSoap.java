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

package com.liferay.portal.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="ReleaseSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.ReleaseServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.ReleaseServiceSoap
 *
 */
public class ReleaseSoap implements Serializable {
	public static ReleaseSoap toSoapModel(Release model) {
		ReleaseSoap soapModel = new ReleaseSoap();

		soapModel.setReleaseId(model.getReleaseId());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setBuildNumber(model.getBuildNumber());
		soapModel.setBuildDate(model.getBuildDate());
		soapModel.setVerified(model.getVerified());

		return soapModel;
	}

	public static ReleaseSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			Release model = (Release)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ReleaseSoap[])soapModels.toArray(new ReleaseSoap[0]);
	}

	public ReleaseSoap() {
	}

	public long getPrimaryKey() {
		return _releaseId;
	}

	public void setPrimaryKey(long pk) {
		setReleaseId(pk);
	}

	public long getReleaseId() {
		return _releaseId;
	}

	public void setReleaseId(long releaseId) {
		_releaseId = releaseId;
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

	public int getBuildNumber() {
		return _buildNumber;
	}

	public void setBuildNumber(int buildNumber) {
		_buildNumber = buildNumber;
	}

	public Date getBuildDate() {
		return _buildDate;
	}

	public void setBuildDate(Date buildDate) {
		_buildDate = buildDate;
	}

	public boolean getVerified() {
		return _verified;
	}

	public boolean isVerified() {
		return _verified;
	}

	public void setVerified(boolean verified) {
		_verified = verified;
	}

	private long _releaseId;
	private Date _createDate;
	private Date _modifiedDate;
	private int _buildNumber;
	private Date _buildDate;
	private boolean _verified;
}