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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.OrgLabor;
import com.liferay.portal.util.PropsUtil;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="OrgLaborModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>OrgLabor</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.OrgLabor
 * @see com.liferay.portal.service.model.OrgLaborModel
 * @see com.liferay.portal.service.model.impl.OrgLaborImpl
 *
 */
public class OrgLaborModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "OrgLabor";
	public static final Object[][] TABLE_COLUMNS = {
			{ "orgLaborId", new Integer(Types.BIGINT) },
			

			{ "organizationId", new Integer(Types.BIGINT) },
			

			{ "typeId", new Integer(Types.INTEGER) },
			

			{ "sunOpen", new Integer(Types.INTEGER) },
			

			{ "sunClose", new Integer(Types.INTEGER) },
			

			{ "monOpen", new Integer(Types.INTEGER) },
			

			{ "monClose", new Integer(Types.INTEGER) },
			

			{ "tueOpen", new Integer(Types.INTEGER) },
			

			{ "tueClose", new Integer(Types.INTEGER) },
			

			{ "wedOpen", new Integer(Types.INTEGER) },
			

			{ "wedClose", new Integer(Types.INTEGER) },
			

			{ "thuOpen", new Integer(Types.INTEGER) },
			

			{ "thuClose", new Integer(Types.INTEGER) },
			

			{ "friOpen", new Integer(Types.INTEGER) },
			

			{ "friClose", new Integer(Types.INTEGER) },
			

			{ "satOpen", new Integer(Types.INTEGER) },
			

			{ "satClose", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table OrgLabor (orgLaborId LONG not null primary key,organizationId LONG,typeId INTEGER,sunOpen INTEGER,sunClose INTEGER,monOpen INTEGER,monClose INTEGER,tueOpen INTEGER,tueClose INTEGER,wedOpen INTEGER,wedClose INTEGER,thuOpen INTEGER,thuClose INTEGER,friOpen INTEGER,friClose INTEGER,satOpen INTEGER,satClose INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table OrgLabor";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.OrgLabor"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.OrgLabor"));

	public OrgLaborModelImpl() {
	}

	public long getPrimaryKey() {
		return _orgLaborId;
	}

	public void setPrimaryKey(long pk) {
		setOrgLaborId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_orgLaborId);
	}

	public long getOrgLaborId() {
		return _orgLaborId;
	}

	public void setOrgLaborId(long orgLaborId) {
		if (orgLaborId != _orgLaborId) {
			_orgLaborId = orgLaborId;
		}
	}

	public long getOrganizationId() {
		return _organizationId;
	}

	public void setOrganizationId(long organizationId) {
		if (organizationId != _organizationId) {
			_organizationId = organizationId;
		}
	}

	public int getTypeId() {
		return _typeId;
	}

	public void setTypeId(int typeId) {
		if (typeId != _typeId) {
			_typeId = typeId;
		}
	}

	public int getSunOpen() {
		return _sunOpen;
	}

	public void setSunOpen(int sunOpen) {
		if (sunOpen != _sunOpen) {
			_sunOpen = sunOpen;
		}
	}

	public int getSunClose() {
		return _sunClose;
	}

	public void setSunClose(int sunClose) {
		if (sunClose != _sunClose) {
			_sunClose = sunClose;
		}
	}

	public int getMonOpen() {
		return _monOpen;
	}

	public void setMonOpen(int monOpen) {
		if (monOpen != _monOpen) {
			_monOpen = monOpen;
		}
	}

	public int getMonClose() {
		return _monClose;
	}

	public void setMonClose(int monClose) {
		if (monClose != _monClose) {
			_monClose = monClose;
		}
	}

	public int getTueOpen() {
		return _tueOpen;
	}

	public void setTueOpen(int tueOpen) {
		if (tueOpen != _tueOpen) {
			_tueOpen = tueOpen;
		}
	}

	public int getTueClose() {
		return _tueClose;
	}

	public void setTueClose(int tueClose) {
		if (tueClose != _tueClose) {
			_tueClose = tueClose;
		}
	}

	public int getWedOpen() {
		return _wedOpen;
	}

	public void setWedOpen(int wedOpen) {
		if (wedOpen != _wedOpen) {
			_wedOpen = wedOpen;
		}
	}

	public int getWedClose() {
		return _wedClose;
	}

	public void setWedClose(int wedClose) {
		if (wedClose != _wedClose) {
			_wedClose = wedClose;
		}
	}

	public int getThuOpen() {
		return _thuOpen;
	}

	public void setThuOpen(int thuOpen) {
		if (thuOpen != _thuOpen) {
			_thuOpen = thuOpen;
		}
	}

	public int getThuClose() {
		return _thuClose;
	}

	public void setThuClose(int thuClose) {
		if (thuClose != _thuClose) {
			_thuClose = thuClose;
		}
	}

	public int getFriOpen() {
		return _friOpen;
	}

	public void setFriOpen(int friOpen) {
		if (friOpen != _friOpen) {
			_friOpen = friOpen;
		}
	}

	public int getFriClose() {
		return _friClose;
	}

	public void setFriClose(int friClose) {
		if (friClose != _friClose) {
			_friClose = friClose;
		}
	}

	public int getSatOpen() {
		return _satOpen;
	}

	public void setSatOpen(int satOpen) {
		if (satOpen != _satOpen) {
			_satOpen = satOpen;
		}
	}

	public int getSatClose() {
		return _satClose;
	}

	public void setSatClose(int satClose) {
		if (satClose != _satClose) {
			_satClose = satClose;
		}
	}

	public OrgLabor toEscapedModel() {
		if (isEscapedModel()) {
			return (OrgLabor)this;
		}
		else {
			OrgLabor model = new OrgLaborImpl();

			model.setEscapedModel(true);

			model.setOrgLaborId(getOrgLaborId());
			model.setOrganizationId(getOrganizationId());
			model.setTypeId(getTypeId());
			model.setSunOpen(getSunOpen());
			model.setSunClose(getSunClose());
			model.setMonOpen(getMonOpen());
			model.setMonClose(getMonClose());
			model.setTueOpen(getTueOpen());
			model.setTueClose(getTueClose());
			model.setWedOpen(getWedOpen());
			model.setWedClose(getWedClose());
			model.setThuOpen(getThuOpen());
			model.setThuClose(getThuClose());
			model.setFriOpen(getFriOpen());
			model.setFriClose(getFriClose());
			model.setSatOpen(getSatOpen());
			model.setSatClose(getSatClose());

			model = (OrgLabor)Proxy.newProxyInstance(OrgLabor.class.getClassLoader(),
					new Class[] { OrgLabor.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		OrgLaborImpl clone = new OrgLaborImpl();

		clone.setOrgLaborId(getOrgLaborId());
		clone.setOrganizationId(getOrganizationId());
		clone.setTypeId(getTypeId());
		clone.setSunOpen(getSunOpen());
		clone.setSunClose(getSunClose());
		clone.setMonOpen(getMonOpen());
		clone.setMonClose(getMonClose());
		clone.setTueOpen(getTueOpen());
		clone.setTueClose(getTueClose());
		clone.setWedOpen(getWedOpen());
		clone.setWedClose(getWedClose());
		clone.setThuOpen(getThuOpen());
		clone.setThuClose(getThuClose());
		clone.setFriOpen(getFriOpen());
		clone.setFriClose(getFriClose());
		clone.setSatOpen(getSatOpen());
		clone.setSatClose(getSatClose());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		OrgLaborImpl orgLabor = (OrgLaborImpl)obj;

		int value = 0;

		if (getOrganizationId() < orgLabor.getOrganizationId()) {
			value = -1;
		}
		else if (getOrganizationId() > orgLabor.getOrganizationId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (getTypeId() < orgLabor.getTypeId()) {
			value = -1;
		}
		else if (getTypeId() > orgLabor.getTypeId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		OrgLaborImpl orgLabor = null;

		try {
			orgLabor = (OrgLaborImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = orgLabor.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
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