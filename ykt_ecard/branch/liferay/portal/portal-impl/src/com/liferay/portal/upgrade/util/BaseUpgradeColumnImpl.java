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

package com.liferay.portal.upgrade.util;

/**
 * <a href="BaseUpgradeColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BaseUpgradeColumnImpl implements UpgradeColumn {

	public BaseUpgradeColumnImpl(String name) {
		this(name, null);
	}

	public BaseUpgradeColumnImpl(String name, Integer oldColumnType) {
		_name = name;
		_oldColumnType = oldColumnType;
	}

	public String getName() {
		return _name;
	}

	public boolean isApplicable(String name) {
		if (_name.equals(name)) {
			return true;
		}
		else {
			return false;
		}
	}

	public Integer getOldColumnType(Integer defaultType) {
		if (_oldColumnType == null) {
			return defaultType;
		}
		else {
			return _oldColumnType;
		}
	}

	public Object getOldValue() {
		return _oldValue;
	}

	public void setOldValue(Object oldValue) {
		_oldValue = oldValue;
	}

	public Integer getNewColumnType(Integer defaultType) {
		return defaultType;
	}

	public Object getNewValue() {
		return _newValue;
	}

	public void setNewValue(Object newValue) {
		_newValue = newValue;
	}

	private String _name;
	private Integer _oldColumnType;
	private Object _oldValue;
	private Object _newValue;

}