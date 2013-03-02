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
import com.liferay.portal.model.ServiceComponent;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="ServiceComponentModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ServiceComponent</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.ServiceComponent
 * @see com.liferay.portal.service.model.ServiceComponentModel
 * @see com.liferay.portal.service.model.impl.ServiceComponentImpl
 *
 */
public class ServiceComponentModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ServiceComponent";
	public static final Object[][] TABLE_COLUMNS = {
			{ "serviceComponentId", new Integer(Types.BIGINT) },
			

			{ "buildNamespace", new Integer(Types.VARCHAR) },
			

			{ "buildNumber", new Integer(Types.BIGINT) },
			

			{ "buildDate", new Integer(Types.BIGINT) },
			

			{ "data_", new Integer(Types.CLOB) }
		};
	public static final String TABLE_SQL_CREATE = "create table ServiceComponent (serviceComponentId LONG not null primary key,buildNamespace VARCHAR(75) null,buildNumber LONG,buildDate LONG,data_ TEXT null)";
	public static final String TABLE_SQL_DROP = "drop table ServiceComponent";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.ServiceComponent"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.ServiceComponent"));

	public ServiceComponentModelImpl() {
	}

	public long getPrimaryKey() {
		return _serviceComponentId;
	}

	public void setPrimaryKey(long pk) {
		setServiceComponentId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_serviceComponentId);
	}

	public long getServiceComponentId() {
		return _serviceComponentId;
	}

	public void setServiceComponentId(long serviceComponentId) {
		if (serviceComponentId != _serviceComponentId) {
			_serviceComponentId = serviceComponentId;
		}
	}

	public String getBuildNamespace() {
		return GetterUtil.getString(_buildNamespace);
	}

	public void setBuildNamespace(String buildNamespace) {
		if (((buildNamespace == null) && (_buildNamespace != null)) ||
				((buildNamespace != null) && (_buildNamespace == null)) ||
				((buildNamespace != null) && (_buildNamespace != null) &&
				!buildNamespace.equals(_buildNamespace))) {
			_buildNamespace = buildNamespace;
		}
	}

	public long getBuildNumber() {
		return _buildNumber;
	}

	public void setBuildNumber(long buildNumber) {
		if (buildNumber != _buildNumber) {
			_buildNumber = buildNumber;
		}
	}

	public long getBuildDate() {
		return _buildDate;
	}

	public void setBuildDate(long buildDate) {
		if (buildDate != _buildDate) {
			_buildDate = buildDate;
		}
	}

	public String getData() {
		return GetterUtil.getString(_data);
	}

	public void setData(String data) {
		if (((data == null) && (_data != null)) ||
				((data != null) && (_data == null)) ||
				((data != null) && (_data != null) && !data.equals(_data))) {
			_data = data;
		}
	}

	public ServiceComponent toEscapedModel() {
		if (isEscapedModel()) {
			return (ServiceComponent)this;
		}
		else {
			ServiceComponent model = new ServiceComponentImpl();

			model.setEscapedModel(true);

			model.setServiceComponentId(getServiceComponentId());
			model.setBuildNamespace(Html.escape(getBuildNamespace()));
			model.setBuildNumber(getBuildNumber());
			model.setBuildDate(getBuildDate());
			model.setData(Html.escape(getData()));

			model = (ServiceComponent)Proxy.newProxyInstance(ServiceComponent.class.getClassLoader(),
					new Class[] { ServiceComponent.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ServiceComponentImpl clone = new ServiceComponentImpl();

		clone.setServiceComponentId(getServiceComponentId());
		clone.setBuildNamespace(getBuildNamespace());
		clone.setBuildNumber(getBuildNumber());
		clone.setBuildDate(getBuildDate());
		clone.setData(getData());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ServiceComponentImpl serviceComponent = (ServiceComponentImpl)obj;

		int value = 0;

		value = getBuildNamespace().compareTo(serviceComponent.getBuildNamespace());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		if (getBuildNumber() < serviceComponent.getBuildNumber()) {
			value = -1;
		}
		else if (getBuildNumber() > serviceComponent.getBuildNumber()) {
			value = 1;
		}
		else {
			value = 0;
		}

		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ServiceComponentImpl serviceComponent = null;

		try {
			serviceComponent = (ServiceComponentImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = serviceComponent.getPrimaryKey();

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

	private long _serviceComponentId;
	private String _buildNamespace;
	private long _buildNumber;
	private long _buildDate;
	private String _data;
}