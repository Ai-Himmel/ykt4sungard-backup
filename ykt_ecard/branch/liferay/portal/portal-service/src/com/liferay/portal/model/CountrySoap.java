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
 * <a href="CountrySoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.CountryServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.CountryServiceSoap
 *
 */
public class CountrySoap implements Serializable {
	public static CountrySoap toSoapModel(Country model) {
		CountrySoap soapModel = new CountrySoap();

		soapModel.setCountryId(model.getCountryId());
		soapModel.setName(model.getName());
		soapModel.setA2(model.getA2());
		soapModel.setA3(model.getA3());
		soapModel.setNumber(model.getNumber());
		soapModel.setIdd(model.getIdd());
		soapModel.setActive(model.getActive());

		return soapModel;
	}

	public static CountrySoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			Country model = (Country)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (CountrySoap[])soapModels.toArray(new CountrySoap[0]);
	}

	public CountrySoap() {
	}

	public long getPrimaryKey() {
		return _countryId;
	}

	public void setPrimaryKey(long pk) {
		setCountryId(pk);
	}

	public long getCountryId() {
		return _countryId;
	}

	public void setCountryId(long countryId) {
		_countryId = countryId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getA2() {
		return _a2;
	}

	public void setA2(String a2) {
		_a2 = a2;
	}

	public String getA3() {
		return _a3;
	}

	public void setA3(String a3) {
		_a3 = a3;
	}

	public String getNumber() {
		return _number;
	}

	public void setNumber(String number) {
		_number = number;
	}

	public String getIdd() {
		return _idd;
	}

	public void setIdd(String idd) {
		_idd = idd;
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

	private long _countryId;
	private String _name;
	private String _a2;
	private String _a3;
	private String _number;
	private String _idd;
	private boolean _active;
}