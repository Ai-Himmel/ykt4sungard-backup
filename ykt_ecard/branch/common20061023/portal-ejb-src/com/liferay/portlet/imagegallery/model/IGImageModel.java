/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.imagegallery.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.imagegallery.service.persistence.IGImagePK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="IGImageModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.75 $
 *
 */
public class IGImageModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.imagegallery.model.IGImage"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.imagegallery.model.IGImage"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.imagegallery.model.IGImage"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_IMAGEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.imagegallery.model.IGImage.imageId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.imagegallery.model.IGImage.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.imagegallery.model.IGImage.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FOLDERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.imagegallery.model.IGImage.folderId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.imagegallery.model.IGImage.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.imagegallery.model.IGImageModel"));

	public IGImageModel() {
	}

	public IGImageModel(IGImagePK pk) {
		_imageId = pk.imageId;
		_companyId = pk.companyId;
		setNew(true);
	}

	public IGImageModel(String imageId, String companyId, String userId,
		Date createDate, Date modifiedDate, String folderId,
		String description, int height, int width, int size) {
		_imageId = imageId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_folderId = folderId;
		_description = description;
		_height = height;
		_width = width;
		_size = size;
	}

	public IGImagePK getPrimaryKey() {
		return new IGImagePK(_imageId, _companyId);
	}

	public String getImageId() {
		return _imageId;
	}

	public void setImageId(String imageId) {
		if (((imageId == null) && (_imageId != null)) ||
				((imageId != null) && (_imageId == null)) ||
				((imageId != null) && (_imageId != null) &&
				!imageId.equals(_imageId))) {
			if (!XSS_ALLOW_IMAGEID) {
				imageId = Xss.strip(imageId);
			}

			_imageId = imageId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public String getFolderId() {
		return _folderId;
	}

	public void setFolderId(String folderId) {
		if (((folderId == null) && (_folderId != null)) ||
				((folderId != null) && (_folderId == null)) ||
				((folderId != null) && (_folderId != null) &&
				!folderId.equals(_folderId))) {
			if (!XSS_ALLOW_FOLDERID) {
				folderId = Xss.strip(folderId);
			}

			_folderId = folderId;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
			setModified(true);
		}
	}

	public int getHeight() {
		return _height;
	}

	public void setHeight(int height) {
		if (height != _height) {
			_height = height;
			setModified(true);
		}
	}

	public int getWidth() {
		return _width;
	}

	public void setWidth(int width) {
		if (width != _width) {
			_width = width;
			setModified(true);
		}
	}

	public int getSize() {
		return _size;
	}

	public void setSize(int size) {
		if (size != _size) {
			_size = size;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new IGImage(getImageId(), getCompanyId(), getUserId(),
			getCreateDate(), getModifiedDate(), getFolderId(),
			getDescription(), getHeight(), getWidth(), getSize());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		IGImage igImage = (IGImage)obj;
		int value = 0;
		value = getCreateDate().compareTo(igImage.getCreateDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		IGImage igImage = null;

		try {
			igImage = (IGImage)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		IGImagePK pk = igImage.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _imageId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _folderId;
	private String _description;
	private int _height;
	private int _width;
	private int _size;
}