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
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Address;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="AddressModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Address</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Address
 * @see com.liferay.portal.service.model.AddressModel
 * @see com.liferay.portal.service.model.impl.AddressImpl
 *
 */
public class AddressModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Address";
	public static final Object[][] TABLE_COLUMNS = {
			{ "addressId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "street1", new Integer(Types.VARCHAR) },
			

			{ "street2", new Integer(Types.VARCHAR) },
			

			{ "street3", new Integer(Types.VARCHAR) },
			

			{ "city", new Integer(Types.VARCHAR) },
			

			{ "zip", new Integer(Types.VARCHAR) },
			

			{ "regionId", new Integer(Types.BIGINT) },
			

			{ "countryId", new Integer(Types.BIGINT) },
			

			{ "typeId", new Integer(Types.INTEGER) },
			

			{ "mailing", new Integer(Types.BOOLEAN) },
			

			{ "primary_", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table Address (addressId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,classNameId LONG,classPK LONG,street1 VARCHAR(75) null,street2 VARCHAR(75) null,street3 VARCHAR(75) null,city VARCHAR(75) null,zip VARCHAR(75) null,regionId LONG,countryId LONG,typeId INTEGER,mailing BOOLEAN,primary_ BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table Address";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Address"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Address"));

	public AddressModelImpl() {
	}

	public long getPrimaryKey() {
		return _addressId;
	}

	public void setPrimaryKey(long pk) {
		setAddressId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_addressId);
	}

	public long getAddressId() {
		return _addressId;
	}

	public void setAddressId(long addressId) {
		if (addressId != _addressId) {
			_addressId = addressId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		if (classNameId != _classNameId) {
			_classNameId = classNameId;
		}
	}

	public long getClassPK() {
		return _classPK;
	}

	public void setClassPK(long classPK) {
		if (classPK != _classPK) {
			_classPK = classPK;
		}
	}

	public String getStreet1() {
		return GetterUtil.getString(_street1);
	}

	public void setStreet1(String street1) {
		if (((street1 == null) && (_street1 != null)) ||
				((street1 != null) && (_street1 == null)) ||
				((street1 != null) && (_street1 != null) &&
				!street1.equals(_street1))) {
			_street1 = street1;
		}
	}

	public String getStreet2() {
		return GetterUtil.getString(_street2);
	}

	public void setStreet2(String street2) {
		if (((street2 == null) && (_street2 != null)) ||
				((street2 != null) && (_street2 == null)) ||
				((street2 != null) && (_street2 != null) &&
				!street2.equals(_street2))) {
			_street2 = street2;
		}
	}

	public String getStreet3() {
		return GetterUtil.getString(_street3);
	}

	public void setStreet3(String street3) {
		if (((street3 == null) && (_street3 != null)) ||
				((street3 != null) && (_street3 == null)) ||
				((street3 != null) && (_street3 != null) &&
				!street3.equals(_street3))) {
			_street3 = street3;
		}
	}

	public String getCity() {
		return GetterUtil.getString(_city);
	}

	public void setCity(String city) {
		if (((city == null) && (_city != null)) ||
				((city != null) && (_city == null)) ||
				((city != null) && (_city != null) && !city.equals(_city))) {
			_city = city;
		}
	}

	public String getZip() {
		return GetterUtil.getString(_zip);
	}

	public void setZip(String zip) {
		if (((zip == null) && (_zip != null)) ||
				((zip != null) && (_zip == null)) ||
				((zip != null) && (_zip != null) && !zip.equals(_zip))) {
			_zip = zip;
		}
	}

	public long getRegionId() {
		return _regionId;
	}

	public void setRegionId(long regionId) {
		if (regionId != _regionId) {
			_regionId = regionId;
		}
	}

	public long getCountryId() {
		return _countryId;
	}

	public void setCountryId(long countryId) {
		if (countryId != _countryId) {
			_countryId = countryId;
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

	public boolean getMailing() {
		return _mailing;
	}

	public boolean isMailing() {
		return _mailing;
	}

	public void setMailing(boolean mailing) {
		if (mailing != _mailing) {
			_mailing = mailing;
		}
	}

	public boolean getPrimary() {
		return _primary;
	}

	public boolean isPrimary() {
		return _primary;
	}

	public void setPrimary(boolean primary) {
		if (primary != _primary) {
			_primary = primary;
		}
	}

	public Address toEscapedModel() {
		if (isEscapedModel()) {
			return (Address)this;
		}
		else {
			Address model = new AddressImpl();

			model.setEscapedModel(true);

			model.setAddressId(getAddressId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setStreet1(Html.escape(getStreet1()));
			model.setStreet2(Html.escape(getStreet2()));
			model.setStreet3(Html.escape(getStreet3()));
			model.setCity(Html.escape(getCity()));
			model.setZip(Html.escape(getZip()));
			model.setRegionId(getRegionId());
			model.setCountryId(getCountryId());
			model.setTypeId(getTypeId());
			model.setMailing(getMailing());
			model.setPrimary(getPrimary());

			model = (Address)Proxy.newProxyInstance(Address.class.getClassLoader(),
					new Class[] { Address.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		AddressImpl clone = new AddressImpl();

		clone.setAddressId(getAddressId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setStreet1(getStreet1());
		clone.setStreet2(getStreet2());
		clone.setStreet3(getStreet3());
		clone.setCity(getCity());
		clone.setZip(getZip());
		clone.setRegionId(getRegionId());
		clone.setCountryId(getCountryId());
		clone.setTypeId(getTypeId());
		clone.setMailing(getMailing());
		clone.setPrimary(getPrimary());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		AddressImpl address = (AddressImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(), address.getCreateDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		AddressImpl address = null;

		try {
			address = (AddressImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = address.getPrimaryKey();

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

	private long _addressId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _classNameId;
	private long _classPK;
	private String _street1;
	private String _street2;
	private String _street3;
	private String _city;
	private String _zip;
	private long _regionId;
	private long _countryId;
	private int _typeId;
	private boolean _mailing;
	private boolean _primary;
}