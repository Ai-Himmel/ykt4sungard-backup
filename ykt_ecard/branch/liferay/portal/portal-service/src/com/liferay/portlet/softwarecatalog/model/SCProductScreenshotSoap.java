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

package com.liferay.portlet.softwarecatalog.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="SCProductScreenshotSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.softwarecatalog.service.http.SCProductScreenshotServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.http.SCProductScreenshotServiceSoap
 *
 */
public class SCProductScreenshotSoap implements Serializable {
	public static SCProductScreenshotSoap toSoapModel(SCProductScreenshot model) {
		SCProductScreenshotSoap soapModel = new SCProductScreenshotSoap();

		soapModel.setProductScreenshotId(model.getProductScreenshotId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setProductEntryId(model.getProductEntryId());
		soapModel.setThumbnailId(model.getThumbnailId());
		soapModel.setFullImageId(model.getFullImageId());
		soapModel.setPriority(model.getPriority());

		return soapModel;
	}

	public static SCProductScreenshotSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			SCProductScreenshot model = (SCProductScreenshot)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (SCProductScreenshotSoap[])soapModels.toArray(new SCProductScreenshotSoap[0]);
	}

	public SCProductScreenshotSoap() {
	}

	public long getPrimaryKey() {
		return _productScreenshotId;
	}

	public void setPrimaryKey(long pk) {
		setProductScreenshotId(pk);
	}

	public long getProductScreenshotId() {
		return _productScreenshotId;
	}

	public void setProductScreenshotId(long productScreenshotId) {
		_productScreenshotId = productScreenshotId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		_groupId = groupId;
	}

	public long getProductEntryId() {
		return _productEntryId;
	}

	public void setProductEntryId(long productEntryId) {
		_productEntryId = productEntryId;
	}

	public long getThumbnailId() {
		return _thumbnailId;
	}

	public void setThumbnailId(long thumbnailId) {
		_thumbnailId = thumbnailId;
	}

	public long getFullImageId() {
		return _fullImageId;
	}

	public void setFullImageId(long fullImageId) {
		_fullImageId = fullImageId;
	}

	public int getPriority() {
		return _priority;
	}

	public void setPriority(int priority) {
		_priority = priority;
	}

	private long _productScreenshotId;
	private long _companyId;
	private long _groupId;
	private long _productEntryId;
	private long _thumbnailId;
	private long _fullImageId;
	private int _priority;
}