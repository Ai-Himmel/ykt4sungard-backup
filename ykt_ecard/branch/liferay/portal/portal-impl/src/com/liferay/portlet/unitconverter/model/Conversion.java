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

package com.liferay.portlet.unitconverter.model;

/**
 * <a href="Conversion.java.html"><b><i>View Source</i></b></a>
 *
 * @author James Lefeu
 *
 */
public class Conversion {

	public Conversion(int type, int fromId, int toId,
					  double fromValue) {
		_type = type;
		_fromId = fromId;
		_toId = toId;
		_fromValue = fromValue;
	}

	public Conversion(int type, int fromId, int toId,
					  double fromValue, double toValue) {
		_type = type;
		_fromId = fromId;
		_toId = toId;
		_fromValue = fromValue;
		_toValue = toValue;
	}

	public int getType() {
		return _type;
	}

	public int getFromId() {
		return _fromId;
	}

	public int getToId() {
		return _toId;
	}

	public double getFromValue() {
		return _fromValue;
	}

	public void setFromValue(double fromValue) {
		_fromValue = fromValue;
	}

	public double getToValue() {
		return _toValue;
	}

	public void setToValue(double toValue) {
		_toValue = toValue;
	}

	private int _type;
	private int _fromId;
	private int _toId;
	private double _fromValue;
	private double _toValue;

}