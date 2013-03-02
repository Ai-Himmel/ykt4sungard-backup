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
import com.liferay.portal.model.WebDAVProps;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="WebDAVPropsModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>WebDAVProps</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.WebDAVProps
 * @see com.liferay.portal.service.model.WebDAVPropsModel
 * @see com.liferay.portal.service.model.impl.WebDAVPropsImpl
 *
 */
public class WebDAVPropsModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "WebDAVProps";
	public static final Object[][] TABLE_COLUMNS = {
			{ "webDavPropsId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "props", new Integer(Types.CLOB) }
		};
	public static final String TABLE_SQL_CREATE = "create table WebDAVProps (webDavPropsId LONG not null primary key,companyId LONG,createDate DATE null,modifiedDate DATE null,classNameId LONG,classPK LONG,props TEXT null)";
	public static final String TABLE_SQL_DROP = "drop table WebDAVProps";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.WebDAVProps"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.WebDAVProps"));

	public WebDAVPropsModelImpl() {
	}

	public long getPrimaryKey() {
		return _webDavPropsId;
	}

	public void setPrimaryKey(long pk) {
		setWebDavPropsId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_webDavPropsId);
	}

	public long getWebDavPropsId() {
		return _webDavPropsId;
	}

	public void setWebDavPropsId(long webDavPropsId) {
		if (webDavPropsId != _webDavPropsId) {
			_webDavPropsId = webDavPropsId;
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

	public String getProps() {
		return GetterUtil.getString(_props);
	}

	public void setProps(String props) {
		if (((props == null) && (_props != null)) ||
				((props != null) && (_props == null)) ||
				((props != null) && (_props != null) && !props.equals(_props))) {
			_props = props;
		}
	}

	public WebDAVProps toEscapedModel() {
		if (isEscapedModel()) {
			return (WebDAVProps)this;
		}
		else {
			WebDAVProps model = new WebDAVPropsImpl();

			model.setEscapedModel(true);

			model.setWebDavPropsId(getWebDavPropsId());
			model.setCompanyId(getCompanyId());
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setProps(Html.escape(getProps()));

			model = (WebDAVProps)Proxy.newProxyInstance(WebDAVProps.class.getClassLoader(),
					new Class[] { WebDAVProps.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		WebDAVPropsImpl clone = new WebDAVPropsImpl();

		clone.setWebDavPropsId(getWebDavPropsId());
		clone.setCompanyId(getCompanyId());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setProps(getProps());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		WebDAVPropsImpl webDAVProps = (WebDAVPropsImpl)obj;

		long pk = webDAVProps.getPrimaryKey();

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

		WebDAVPropsImpl webDAVProps = null;

		try {
			webDAVProps = (WebDAVPropsImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = webDAVProps.getPrimaryKey();

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

	private long _webDavPropsId;
	private long _companyId;
	private Date _createDate;
	private Date _modifiedDate;
	private long _classNameId;
	private long _classPK;
	private String _props;
}