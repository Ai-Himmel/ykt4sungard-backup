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
import com.liferay.portal.model.Phone;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="PhoneModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Phone</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Phone
 * @see com.liferay.portal.service.model.PhoneModel
 * @see com.liferay.portal.service.model.impl.PhoneImpl
 *
 */
public class PhoneModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Phone";
	public static final Object[][] TABLE_COLUMNS = {
			{ "phoneId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "number_", new Integer(Types.VARCHAR) },
			

			{ "extension", new Integer(Types.VARCHAR) },
			

			{ "typeId", new Integer(Types.INTEGER) },
			

			{ "primary_", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table Phone (phoneId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,classNameId LONG,classPK LONG,number_ VARCHAR(75) null,extension VARCHAR(75) null,typeId INTEGER,primary_ BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table Phone";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Phone"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Phone"));

	public PhoneModelImpl() {
	}

	public long getPrimaryKey() {
		return _phoneId;
	}

	public void setPrimaryKey(long pk) {
		setPhoneId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_phoneId);
	}

	public long getPhoneId() {
		return _phoneId;
	}

	public void setPhoneId(long phoneId) {
		if (phoneId != _phoneId) {
			_phoneId = phoneId;
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

	public String getNumber() {
		return GetterUtil.getString(_number);
	}

	public void setNumber(String number) {
		if (((number == null) && (_number != null)) ||
				((number != null) && (_number == null)) ||
				((number != null) && (_number != null) &&
				!number.equals(_number))) {
			_number = number;
		}
	}

	public String getExtension() {
		return GetterUtil.getString(_extension);
	}

	public void setExtension(String extension) {
		if (((extension == null) && (_extension != null)) ||
				((extension != null) && (_extension == null)) ||
				((extension != null) && (_extension != null) &&
				!extension.equals(_extension))) {
			_extension = extension;
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

	public Phone toEscapedModel() {
		if (isEscapedModel()) {
			return (Phone)this;
		}
		else {
			Phone model = new PhoneImpl();

			model.setEscapedModel(true);

			model.setPhoneId(getPhoneId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setNumber(Html.escape(getNumber()));
			model.setExtension(Html.escape(getExtension()));
			model.setTypeId(getTypeId());
			model.setPrimary(getPrimary());

			model = (Phone)Proxy.newProxyInstance(Phone.class.getClassLoader(),
					new Class[] { Phone.class }, new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PhoneImpl clone = new PhoneImpl();

		clone.setPhoneId(getPhoneId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setNumber(getNumber());
		clone.setExtension(getExtension());
		clone.setTypeId(getTypeId());
		clone.setPrimary(getPrimary());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PhoneImpl phone = (PhoneImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(), phone.getCreateDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		PhoneImpl phone = null;

		try {
			phone = (PhoneImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = phone.getPrimaryKey();

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

	private long _phoneId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _classNameId;
	private long _classPK;
	private String _number;
	private String _extension;
	private int _typeId;
	private boolean _primary;
}