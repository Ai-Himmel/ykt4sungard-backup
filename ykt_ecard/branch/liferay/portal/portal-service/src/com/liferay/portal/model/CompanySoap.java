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
 * <a href="CompanySoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.CompanyServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.CompanyServiceSoap
 *
 */
public class CompanySoap implements Serializable {
	public static CompanySoap toSoapModel(Company model) {
		CompanySoap soapModel = new CompanySoap();

		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setAccountId(model.getAccountId());
		soapModel.setWebId(model.getWebId());
		soapModel.setKey(model.getKey());
		soapModel.setVirtualHost(model.getVirtualHost());
		soapModel.setMx(model.getMx());
		soapModel.setLogoId(model.getLogoId());

		return soapModel;
	}

	public static CompanySoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			Company model = (Company)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (CompanySoap[])soapModels.toArray(new CompanySoap[0]);
	}

	public CompanySoap() {
	}

	public long getPrimaryKey() {
		return _companyId;
	}

	public void setPrimaryKey(long pk) {
		setCompanyId(pk);
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getAccountId() {
		return _accountId;
	}

	public void setAccountId(long accountId) {
		_accountId = accountId;
	}

	public String getWebId() {
		return _webId;
	}

	public void setWebId(String webId) {
		_webId = webId;
	}

	public String getKey() {
		return _key;
	}

	public void setKey(String key) {
		_key = key;
	}

	public String getVirtualHost() {
		return _virtualHost;
	}

	public void setVirtualHost(String virtualHost) {
		_virtualHost = virtualHost;
	}

	public String getMx() {
		return _mx;
	}

	public void setMx(String mx) {
		_mx = mx;
	}

	public long getLogoId() {
		return _logoId;
	}

	public void setLogoId(long logoId) {
		_logoId = logoId;
	}

	private long _companyId;
	private long _accountId;
	private String _webId;
	private String _key;
	private String _virtualHost;
	private String _mx;
	private long _logoId;
}