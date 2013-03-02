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
import java.util.List;

/**
 * <a href="SCLicenseSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.softwarecatalog.service.http.SCLicenseServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.http.SCLicenseServiceSoap
 *
 */
public class SCLicenseSoap implements Serializable {
	public static SCLicenseSoap toSoapModel(SCLicense model) {
		SCLicenseSoap soapModel = new SCLicenseSoap();

		soapModel.setLicenseId(model.getLicenseId());
		soapModel.setName(model.getName());
		soapModel.setUrl(model.getUrl());
		soapModel.setOpenSource(model.getOpenSource());
		soapModel.setActive(model.getActive());
		soapModel.setRecommended(model.getRecommended());

		return soapModel;
	}

	public static SCLicenseSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			SCLicense model = (SCLicense)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (SCLicenseSoap[])soapModels.toArray(new SCLicenseSoap[0]);
	}

	public SCLicenseSoap() {
	}

	public long getPrimaryKey() {
		return _licenseId;
	}

	public void setPrimaryKey(long pk) {
		setLicenseId(pk);
	}

	public long getLicenseId() {
		return _licenseId;
	}

	public void setLicenseId(long licenseId) {
		_licenseId = licenseId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getUrl() {
		return _url;
	}

	public void setUrl(String url) {
		_url = url;
	}

	public boolean getOpenSource() {
		return _openSource;
	}

	public boolean isOpenSource() {
		return _openSource;
	}

	public void setOpenSource(boolean openSource) {
		_openSource = openSource;
	}

	public boolean getActive() {
		return _active;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		_active = active;
	}

	public boolean getRecommended() {
		return _recommended;
	}

	public boolean isRecommended() {
		return _recommended;
	}

	public void setRecommended(boolean recommended) {
		_recommended = recommended;
	}

	private long _licenseId;
	private String _name;
	private String _url;
	private boolean _openSource;
	private boolean _active;
	private boolean _recommended;
}