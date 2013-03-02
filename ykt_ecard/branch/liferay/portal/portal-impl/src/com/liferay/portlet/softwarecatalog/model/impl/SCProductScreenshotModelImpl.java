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

package com.liferay.portlet.softwarecatalog.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.softwarecatalog.model.SCProductScreenshot;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="SCProductScreenshotModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>SCProductScreenshot</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductScreenshot
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductScreenshotModel
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductScreenshotImpl
 *
 */
public class SCProductScreenshotModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "SCProductScreenshot";
	public static final Object[][] TABLE_COLUMNS = {
			{ "productScreenshotId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "productEntryId", new Integer(Types.BIGINT) },
			

			{ "thumbnailId", new Integer(Types.BIGINT) },
			

			{ "fullImageId", new Integer(Types.BIGINT) },
			

			{ "priority", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table SCProductScreenshot (productScreenshotId LONG not null primary key,companyId LONG,groupId LONG,productEntryId LONG,thumbnailId LONG,fullImageId LONG,priority INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table SCProductScreenshot";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.softwarecatalog.model.SCProductScreenshot"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.softwarecatalog.model.SCProductScreenshot"));

	public SCProductScreenshotModelImpl() {
	}

	public long getPrimaryKey() {
		return _productScreenshotId;
	}

	public void setPrimaryKey(long pk) {
		setProductScreenshotId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_productScreenshotId);
	}

	public long getProductScreenshotId() {
		return _productScreenshotId;
	}

	public void setProductScreenshotId(long productScreenshotId) {
		if (productScreenshotId != _productScreenshotId) {
			_productScreenshotId = productScreenshotId;
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

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public long getProductEntryId() {
		return _productEntryId;
	}

	public void setProductEntryId(long productEntryId) {
		if (productEntryId != _productEntryId) {
			_productEntryId = productEntryId;
		}
	}

	public long getThumbnailId() {
		return _thumbnailId;
	}

	public void setThumbnailId(long thumbnailId) {
		if (thumbnailId != _thumbnailId) {
			_thumbnailId = thumbnailId;
		}
	}

	public long getFullImageId() {
		return _fullImageId;
	}

	public void setFullImageId(long fullImageId) {
		if (fullImageId != _fullImageId) {
			_fullImageId = fullImageId;
		}
	}

	public int getPriority() {
		return _priority;
	}

	public void setPriority(int priority) {
		if (priority != _priority) {
			_priority = priority;
		}
	}

	public SCProductScreenshot toEscapedModel() {
		if (isEscapedModel()) {
			return (SCProductScreenshot)this;
		}
		else {
			SCProductScreenshot model = new SCProductScreenshotImpl();

			model.setEscapedModel(true);

			model.setProductScreenshotId(getProductScreenshotId());
			model.setCompanyId(getCompanyId());
			model.setGroupId(getGroupId());
			model.setProductEntryId(getProductEntryId());
			model.setThumbnailId(getThumbnailId());
			model.setFullImageId(getFullImageId());
			model.setPriority(getPriority());

			model = (SCProductScreenshot)Proxy.newProxyInstance(SCProductScreenshot.class.getClassLoader(),
					new Class[] { SCProductScreenshot.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		SCProductScreenshotImpl clone = new SCProductScreenshotImpl();

		clone.setProductScreenshotId(getProductScreenshotId());
		clone.setCompanyId(getCompanyId());
		clone.setGroupId(getGroupId());
		clone.setProductEntryId(getProductEntryId());
		clone.setThumbnailId(getThumbnailId());
		clone.setFullImageId(getFullImageId());
		clone.setPriority(getPriority());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		SCProductScreenshotImpl scProductScreenshot = (SCProductScreenshotImpl)obj;

		int value = 0;

		if (getProductEntryId() < scProductScreenshot.getProductEntryId()) {
			value = -1;
		}
		else if (getProductEntryId() > scProductScreenshot.getProductEntryId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (getPriority() < scProductScreenshot.getPriority()) {
			value = -1;
		}
		else if (getPriority() > scProductScreenshot.getPriority()) {
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

		SCProductScreenshotImpl scProductScreenshot = null;

		try {
			scProductScreenshot = (SCProductScreenshotImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = scProductScreenshot.getPrimaryKey();

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

	private long _productScreenshotId;
	private long _companyId;
	private long _groupId;
	private long _productEntryId;
	private long _thumbnailId;
	private long _fullImageId;
	private int _priority;
}