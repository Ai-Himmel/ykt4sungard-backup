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
import com.liferay.portal.model.PasswordPolicyRel;
import com.liferay.portal.util.PropsUtil;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="PasswordPolicyRelModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>PasswordPolicyRel</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.PasswordPolicyRel
 * @see com.liferay.portal.service.model.PasswordPolicyRelModel
 * @see com.liferay.portal.service.model.impl.PasswordPolicyRelImpl
 *
 */
public class PasswordPolicyRelModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "PasswordPolicyRel";
	public static final Object[][] TABLE_COLUMNS = {
			{ "passwordPolicyRelId", new Integer(Types.BIGINT) },
			

			{ "passwordPolicyId", new Integer(Types.BIGINT) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) }
		};
	public static final String TABLE_SQL_CREATE = "create table PasswordPolicyRel (passwordPolicyRelId LONG not null primary key,passwordPolicyId LONG,classNameId LONG,classPK LONG)";
	public static final String TABLE_SQL_DROP = "drop table PasswordPolicyRel";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.PasswordPolicyRel"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.PasswordPolicyRel"));

	public PasswordPolicyRelModelImpl() {
	}

	public long getPrimaryKey() {
		return _passwordPolicyRelId;
	}

	public void setPrimaryKey(long pk) {
		setPasswordPolicyRelId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_passwordPolicyRelId);
	}

	public long getPasswordPolicyRelId() {
		return _passwordPolicyRelId;
	}

	public void setPasswordPolicyRelId(long passwordPolicyRelId) {
		if (passwordPolicyRelId != _passwordPolicyRelId) {
			_passwordPolicyRelId = passwordPolicyRelId;
		}
	}

	public long getPasswordPolicyId() {
		return _passwordPolicyId;
	}

	public void setPasswordPolicyId(long passwordPolicyId) {
		if (passwordPolicyId != _passwordPolicyId) {
			_passwordPolicyId = passwordPolicyId;
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

	public PasswordPolicyRel toEscapedModel() {
		if (isEscapedModel()) {
			return (PasswordPolicyRel)this;
		}
		else {
			PasswordPolicyRel model = new PasswordPolicyRelImpl();

			model.setEscapedModel(true);

			model.setPasswordPolicyRelId(getPasswordPolicyRelId());
			model.setPasswordPolicyId(getPasswordPolicyId());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());

			model = (PasswordPolicyRel)Proxy.newProxyInstance(PasswordPolicyRel.class.getClassLoader(),
					new Class[] { PasswordPolicyRel.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PasswordPolicyRelImpl clone = new PasswordPolicyRelImpl();

		clone.setPasswordPolicyRelId(getPasswordPolicyRelId());
		clone.setPasswordPolicyId(getPasswordPolicyId());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PasswordPolicyRelImpl passwordPolicyRel = (PasswordPolicyRelImpl)obj;

		long pk = passwordPolicyRel.getPrimaryKey();

		if (getPrimaryKey() < pk) {
			return -1;
		}
		else if (getPrimaryKey() > pk) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		PasswordPolicyRelImpl passwordPolicyRel = null;

		try {
			passwordPolicyRel = (PasswordPolicyRelImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = passwordPolicyRel.getPrimaryKey();

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

	private long _passwordPolicyRelId;
	private long _passwordPolicyId;
	private long _classNameId;
	private long _classPK;
}