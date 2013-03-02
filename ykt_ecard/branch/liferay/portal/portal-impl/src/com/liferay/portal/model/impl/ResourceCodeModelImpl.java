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
import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="ResourceCodeModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ResourceCode</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.ResourceCode
 * @see com.liferay.portal.service.model.ResourceCodeModel
 * @see com.liferay.portal.service.model.impl.ResourceCodeImpl
 *
 */
public class ResourceCodeModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ResourceCode";
	public static final Object[][] TABLE_COLUMNS = {
			{ "codeId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "scope", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table ResourceCode (codeId LONG not null primary key,companyId LONG,name VARCHAR(300) null,scope INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table ResourceCode";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.ResourceCode"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.ResourceCode"));

	public ResourceCodeModelImpl() {
	}

	public long getPrimaryKey() {
		return _codeId;
	}

	public void setPrimaryKey(long pk) {
		setCodeId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_codeId);
	}

	public long getCodeId() {
		return _codeId;
	}

	public void setCodeId(long codeId) {
		if (codeId != _codeId) {
			_codeId = codeId;
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

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
		}
	}

	public int getScope() {
		return _scope;
	}

	public void setScope(int scope) {
		if (scope != _scope) {
			_scope = scope;
		}
	}

	public ResourceCode toEscapedModel() {
		if (isEscapedModel()) {
			return (ResourceCode)this;
		}
		else {
			ResourceCode model = new ResourceCodeImpl();

			model.setEscapedModel(true);

			model.setCodeId(getCodeId());
			model.setCompanyId(getCompanyId());
			model.setName(Html.escape(getName()));
			model.setScope(getScope());

			model = (ResourceCode)Proxy.newProxyInstance(ResourceCode.class.getClassLoader(),
					new Class[] { ResourceCode.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ResourceCodeImpl clone = new ResourceCodeImpl();

		clone.setCodeId(getCodeId());
		clone.setCompanyId(getCompanyId());
		clone.setName(getName());
		clone.setScope(getScope());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ResourceCodeImpl resourceCode = (ResourceCodeImpl)obj;

		long pk = resourceCode.getPrimaryKey();

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

		ResourceCodeImpl resourceCode = null;

		try {
			resourceCode = (ResourceCodeImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = resourceCode.getPrimaryKey();

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

	private long _codeId;
	private long _companyId;
	private String _name;
	private int _scope;
}