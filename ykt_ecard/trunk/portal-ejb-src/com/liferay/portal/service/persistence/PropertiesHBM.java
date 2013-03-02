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

package com.liferay.portal.service.persistence;

/**
 * <a href="PropertiesHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class PropertiesHBM {
	protected PropertiesHBM() {
	}

	protected PropertiesHBM(PropertiesPK pk) {
		_companyId = pk.companyId;
		_type = pk.type;
	}

	protected PropertiesHBM(String companyId, String type, String properties) {
		_companyId = companyId;
		_type = type;
		_properties = properties;
	}

	public PropertiesPK getPrimaryKey() {
		return new PropertiesPK(_companyId, _type);
	}

	protected void setPrimaryKey(PropertiesPK pk) {
		_companyId = pk.companyId;
		_type = pk.type;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getType() {
		return _type;
	}

	protected void setType(String type) {
		_type = type;
	}

	protected String getProperties() {
		return _properties;
	}

	protected void setProperties(String properties) {
		_properties = properties;
	}

	private String _companyId;
	private String _type;
	private String _properties;
}