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

package com.liferay.portlet.imagegallery.service.persistence;

import java.util.Date;

/**
 * <a href="IGImageHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGImageHBM {
	protected IGImageHBM() {
	}

	protected IGImageHBM(IGImagePK pk) {
		_imageId = pk.imageId;
		_companyId = pk.companyId;
	}

	protected IGImageHBM(String imageId, String companyId, String userId,
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

	protected void setPrimaryKey(IGImagePK pk) {
		_imageId = pk.imageId;
		_companyId = pk.companyId;
	}

	protected String getImageId() {
		return _imageId;
	}

	protected void setImageId(String imageId) {
		_imageId = imageId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getFolderId() {
		return _folderId;
	}

	protected void setFolderId(String folderId) {
		_folderId = folderId;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected int getHeight() {
		return _height;
	}

	protected void setHeight(int height) {
		_height = height;
	}

	protected int getWidth() {
		return _width;
	}

	protected void setWidth(int width) {
		_width = width;
	}

	protected int getSize() {
		return _size;
	}

	protected void setSize(int size) {
		_size = size;
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