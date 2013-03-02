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

package com.liferay.util.servlet;

/**
 * <a href="Header.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class Header {

	public static final int INTEGER_TYPE = 1;

	public static final int DATE_TYPE = 2;

	public static final int STRING_TYPE = 3;

	public long getDateValue() {
		return _dateValue;
	}

	public void setDateValue(long dateValue) {
		_dateValue = dateValue;
	}

	public int getIntValue() {
		return _intValue;
	}

	public void setIntValue(int intValue) {
		_intValue = intValue;
	}

	public String getStringValue() {
		return _stringValue;
	}

	public void setStringValue(String stringValue) {
		_stringValue = stringValue;
	}

	public int getType() {
		return _type;
	}

	public void setType(int type) {
		_type = type;
	}

	private int _intValue;
	private long _dateValue;
	private String _stringValue;
	private int _type;

}