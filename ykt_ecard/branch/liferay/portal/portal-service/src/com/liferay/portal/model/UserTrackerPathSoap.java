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
 * <a href="UserTrackerPathSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.UserTrackerPathServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.UserTrackerPathServiceSoap
 *
 */
public class UserTrackerPathSoap implements Serializable {
	public static UserTrackerPathSoap toSoapModel(UserTrackerPath model) {
		UserTrackerPathSoap soapModel = new UserTrackerPathSoap();

		soapModel.setUserTrackerPathId(model.getUserTrackerPathId());
		soapModel.setUserTrackerId(model.getUserTrackerId());
		soapModel.setPath(model.getPath());
		soapModel.setPathDate(model.getPathDate());

		return soapModel;
	}

	public static UserTrackerPathSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			UserTrackerPath model = (UserTrackerPath)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (UserTrackerPathSoap[])soapModels.toArray(new UserTrackerPathSoap[0]);
	}

	public UserTrackerPathSoap() {
	}

	public long getPrimaryKey() {
		return _userTrackerPathId;
	}

	public void setPrimaryKey(long pk) {
		setUserTrackerPathId(pk);
	}

	public long getUserTrackerPathId() {
		return _userTrackerPathId;
	}

	public void setUserTrackerPathId(long userTrackerPathId) {
		_userTrackerPathId = userTrackerPathId;
	}

	public long getUserTrackerId() {
		return _userTrackerId;
	}

	public void setUserTrackerId(long userTrackerId) {
		_userTrackerId = userTrackerId;
	}

	public String getPath() {
		return _path;
	}

	public void setPath(String path) {
		_path = path;
	}

	public Date getPathDate() {
		return _pathDate;
	}

	public void setPathDate(Date pathDate) {
		_pathDate = pathDate;
	}

	private long _userTrackerPathId;
	private long _userTrackerId;
	private String _path;
	private Date _pathDate;
}