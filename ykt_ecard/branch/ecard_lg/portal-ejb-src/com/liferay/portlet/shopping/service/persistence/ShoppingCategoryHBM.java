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

package com.liferay.portlet.shopping.service.persistence;

import java.util.Date;

/**
 * <a href="ShoppingCategoryHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCategoryHBM {
	protected ShoppingCategoryHBM() {
	}

	protected ShoppingCategoryHBM(String categoryId) {
		_categoryId = categoryId;
	}

	protected ShoppingCategoryHBM(String categoryId, String companyId,
		Date createDate, Date modifiedDate, String parentCategoryId, String name) {
		_categoryId = categoryId;
		_companyId = companyId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_parentCategoryId = parentCategoryId;
		_name = name;
	}

	public String getPrimaryKey() {
		return _categoryId;
	}

	protected void setPrimaryKey(String pk) {
		_categoryId = pk;
	}

	protected String getCategoryId() {
		return _categoryId;
	}

	protected void setCategoryId(String categoryId) {
		_categoryId = categoryId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
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

	protected String getParentCategoryId() {
		return _parentCategoryId;
	}

	protected void setParentCategoryId(String parentCategoryId) {
		_parentCategoryId = parentCategoryId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	private String _categoryId;
	private String _companyId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _parentCategoryId;
	private String _name;
}