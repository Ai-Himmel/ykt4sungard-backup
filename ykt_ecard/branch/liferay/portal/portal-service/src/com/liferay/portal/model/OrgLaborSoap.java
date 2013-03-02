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
 * <a href="OrgLaborSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.OrgLaborServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.OrgLaborServiceSoap
 *
 */
public class OrgLaborSoap implements Serializable {
	public static OrgLaborSoap toSoapModel(OrgLabor model) {
		OrgLaborSoap soapModel = new OrgLaborSoap();

		soapModel.setOrgLaborId(model.getOrgLaborId());
		soapModel.setOrganizationId(model.getOrganizationId());
		soapModel.setTypeId(model.getTypeId());
		soapModel.setSunOpen(model.getSunOpen());
		soapModel.setSunClose(model.getSunClose());
		soapModel.setMonOpen(model.getMonOpen());
		soapModel.setMonClose(model.getMonClose());
		soapModel.setTueOpen(model.getTueOpen());
		soapModel.setTueClose(model.getTueClose());
		soapModel.setWedOpen(model.getWedOpen());
		soapModel.setWedClose(model.getWedClose());
		soapModel.setThuOpen(model.getThuOpen());
		soapModel.setThuClose(model.getThuClose());
		soapModel.setFriOpen(model.getFriOpen());
		soapModel.setFriClose(model.getFriClose());
		soapModel.setSatOpen(model.getSatOpen());
		soapModel.setSatClose(model.getSatClose());

		return soapModel;
	}

	public static OrgLaborSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			OrgLabor model = (OrgLabor)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (OrgLaborSoap[])soapModels.toArray(new OrgLaborSoap[0]);
	}

	public OrgLaborSoap() {
	}

	public long getPrimaryKey() {
		return _orgLaborId;
	}

	public void setPrimaryKey(long pk) {
		setOrgLaborId(pk);
	}

	public long getOrgLaborId() {
		return _orgLaborId;
	}

	public void setOrgLaborId(long orgLaborId) {
		_orgLaborId = orgLaborId;
	}

	public long getOrganizationId() {
		return _organizationId;
	}

	public void setOrganizationId(long organizationId) {
		_organizationId = organizationId;
	}

	public int getTypeId() {
		return _typeId;
	}

	public void setTypeId(int typeId) {
		_typeId = typeId;
	}

	public int getSunOpen() {
		return _sunOpen;
	}

	public void setSunOpen(int sunOpen) {
		_sunOpen = sunOpen;
	}

	public int getSunClose() {
		return _sunClose;
	}

	public void setSunClose(int sunClose) {
		_sunClose = sunClose;
	}

	public int getMonOpen() {
		return _monOpen;
	}

	public void setMonOpen(int monOpen) {
		_monOpen = monOpen;
	}

	public int getMonClose() {
		return _monClose;
	}

	public void setMonClose(int monClose) {
		_monClose = monClose;
	}

	public int getTueOpen() {
		return _tueOpen;
	}

	public void setTueOpen(int tueOpen) {
		_tueOpen = tueOpen;
	}

	public int getTueClose() {
		return _tueClose;
	}

	public void setTueClose(int tueClose) {
		_tueClose = tueClose;
	}

	public int getWedOpen() {
		return _wedOpen;
	}

	public void setWedOpen(int wedOpen) {
		_wedOpen = wedOpen;
	}

	public int getWedClose() {
		return _wedClose;
	}

	public void setWedClose(int wedClose) {
		_wedClose = wedClose;
	}

	public int getThuOpen() {
		return _thuOpen;
	}

	public void setThuOpen(int thuOpen) {
		_thuOpen = thuOpen;
	}

	public int getThuClose() {
		return _thuClose;
	}

	public void setThuClose(int thuClose) {
		_thuClose = thuClose;
	}

	public int getFriOpen() {
		return _friOpen;
	}

	public void setFriOpen(int friOpen) {
		_friOpen = friOpen;
	}

	public int getFriClose() {
		return _friClose;
	}

	public void setFriClose(int friClose) {
		_friClose = friClose;
	}

	public int getSatOpen() {
		return _satOpen;
	}

	public void setSatOpen(int satOpen) {
		_satOpen = satOpen;
	}

	public int getSatClose() {
		return _satClose;
	}

	public void setSatClose(int satClose) {
		_satClose = satClose;
	}

	private long _orgLaborId;
	private long _organizationId;
	private int _typeId;
	private int _sunOpen;
	private int _sunClose;
	private int _monOpen;
	private int _monClose;
	private int _tueOpen;
	private int _tueClose;
	private int _wedOpen;
	private int _wedClose;
	private int _thuOpen;
	private int _thuClose;
	private int _friOpen;
	private int _friClose;
	private int _satOpen;
	private int _satClose;
}