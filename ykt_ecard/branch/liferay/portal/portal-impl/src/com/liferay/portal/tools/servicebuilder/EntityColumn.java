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

package com.liferay.portal.tools.servicebuilder;

import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.TextFormatter;

/**
 * <a href="EntityColumn.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Charles May
 *
 */
public class EntityColumn implements Cloneable {

	public EntityColumn(String name) {
		this(name, null, null, false, null, null, null, true, true, null,
			 null, null, true);
	}

	public EntityColumn(String name, String dbName, String type,
						boolean primary, String ejbName, String mappingKey,
						String mappingTable, String idType, String idParam,
						boolean convertNull) {

		this(name, dbName, type, primary, ejbName, mappingKey, mappingTable,
			 true, true, null, idType, idParam, convertNull);
	}

	public EntityColumn(String name, String dbName, String type,
						boolean primary, String ejbName, String mappingKey,
						String mappingTable, boolean caseSensitive,
						boolean orderByAscending, String comparator,
						String idType, String idParam, boolean convertNull) {

		_name = name;
		_dbName = dbName;
		_type = type;
		_primary = primary;
		_methodName = TextFormatter.format(name, TextFormatter.G);
		_ejbName = ejbName;
		_mappingKey = mappingKey;
		_mappingTable = mappingTable;
		_caseSensitive = caseSensitive;
		_orderByAscending = orderByAscending;
		_comparator = comparator;
		_idType = idType;
		_idParam = idParam;
		_convertNull = convertNull;
	}

	public String getName() {
		return _name;
	}

	public String getDBName() {
		return _dbName;
	}

	public void setDBName(String dbName) {
		_dbName = dbName;
	}

	public String getType() {
		return _type;
	}

	public boolean isPrimitiveType() {
		if (Character.isLowerCase(_type.charAt(0))) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isCollection() {
		if (_type.equals("Collection")) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isPrimary() {
		return _primary;
	}

	public String getMethodName() {
		return _methodName;
	}

	public String getEJBName() {
		return _ejbName;
	}

	public String getMappingKey() {
		return _mappingKey;
	}

	public String getMappingTable() {
		return _mappingTable;
	}

	public boolean isMappingOneToMany() {
		return Validator.isNotNull(_mappingKey);
	}

	public boolean isMappingManyToMany() {
		return Validator.isNotNull(_mappingTable);
	}

	public boolean isCaseSensitive() {
		return _caseSensitive;
	}

	public void setCaseSensitive(boolean caseSensitive) {
		_caseSensitive = caseSensitive;
	}

	public boolean isOrderByAscending() {
		return _orderByAscending;
	}

	public void setOrderByAscending(boolean orderByAscending) {
		_orderByAscending = orderByAscending;
	}

	public String getComparator() {
		return _comparator;
	}

	public void setComparator(String comparator) {
		_comparator = comparator;
	}

	public String getIdType() {
		return _idType;
	}

	public void setIdType(String idType) {
		_idType = idType;
	}

	public String getIdParam() {
		return _idParam;
	}

	public void setIdParam(String idParam) {
		_idParam = idParam;
	}

	public boolean isConvertNull() {
		return _convertNull;
	}

	public void setConvertNull(boolean convertNull) {
		_convertNull = convertNull;
	}

	public Object clone() {
		return new EntityColumn(
			getName(), getDBName(), getType(), isPrimary(), getEJBName(),
			getMappingKey(), getMappingTable(), isCaseSensitive(),
			isOrderByAscending(), getComparator(), getIdType(), getIdParam(),
			isConvertNull());
	}

	public boolean equals(Object obj) {
		EntityColumn col = (EntityColumn)obj;

		String name = col.getName();

		if (_name.equals(name)) {
			return true;
		}
		else {
			return false;
		}
	}

	private String _name;
	private String _dbName;
	private String _type;
	private boolean _primary;
	private String _methodName;
	private String _ejbName;
	private String _mappingKey;
	private String _mappingTable;
	private boolean _caseSensitive;
	private boolean _orderByAscending;
	private String _comparator;
	private String _idType;
	private String _idParam;
	private boolean _convertNull;

}