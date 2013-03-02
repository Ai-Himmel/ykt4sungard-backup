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
import java.util.List;

/**
 * <a href="ServiceComponentSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.ServiceComponentServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.ServiceComponentServiceSoap
 *
 */
public class ServiceComponentSoap implements Serializable {
	public static ServiceComponentSoap toSoapModel(ServiceComponent model) {
		ServiceComponentSoap soapModel = new ServiceComponentSoap();

		soapModel.setServiceComponentId(model.getServiceComponentId());
		soapModel.setBuildNamespace(model.getBuildNamespace());
		soapModel.setBuildNumber(model.getBuildNumber());
		soapModel.setBuildDate(model.getBuildDate());
		soapModel.setData(model.getData());

		return soapModel;
	}

	public static ServiceComponentSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			ServiceComponent model = (ServiceComponent)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ServiceComponentSoap[])soapModels.toArray(new ServiceComponentSoap[0]);
	}

	public ServiceComponentSoap() {
	}

	public long getPrimaryKey() {
		return _serviceComponentId;
	}

	public void setPrimaryKey(long pk) {
		setServiceComponentId(pk);
	}

	public long getServiceComponentId() {
		return _serviceComponentId;
	}

	public void setServiceComponentId(long serviceComponentId) {
		_serviceComponentId = serviceComponentId;
	}

	public String getBuildNamespace() {
		return _buildNamespace;
	}

	public void setBuildNamespace(String buildNamespace) {
		_buildNamespace = buildNamespace;
	}

	public long getBuildNumber() {
		return _buildNumber;
	}

	public void setBuildNumber(long buildNumber) {
		_buildNumber = buildNumber;
	}

	public long getBuildDate() {
		return _buildDate;
	}

	public void setBuildDate(long buildDate) {
		_buildDate = buildDate;
	}

	public String getData() {
		return _data;
	}

	public void setData(String data) {
		_data = data;
	}

	private long _serviceComponentId;
	private String _buildNamespace;
	private long _buildNumber;
	private long _buildDate;
	private String _data;
}