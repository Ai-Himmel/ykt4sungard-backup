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

package com.liferay.portlet.messageboards.util;

import com.liferay.portal.kernel.util.StringPool;

/**
 * <a href="BBCodeTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class BBCodeTag {

	public BBCodeTag() {
	}

	public String getElement() {
		return _element;
	}

	public void setElement(String element) {
		_element = element;
	}

	public boolean hasElement() {
		if (_element != null) {
			return true;
		}
		else {
			return false;
		}
	}

	public int getEndPos() {
		return _endPos;
	}

	public void setEndPos(int pos) {
		_endPos = pos;
	}

	public String getParameter() {
		return _parameter;
	}

	public void setParameter(String parameter) {
		_parameter = parameter.trim();

		if (_parameter.startsWith(StringPool.APOSTROPHE) ||
			_parameter.startsWith(StringPool.QUOTE)) {

			_parameter = _parameter.substring(1);
		}

		if (_parameter.endsWith(StringPool.APOSTROPHE) ||
			_parameter.endsWith(StringPool.QUOTE)) {

			_parameter = _parameter.substring(0, _parameter.length() - 1);
		}

		_parameter = _parameter.trim();
	}

	public boolean hasParameter() {
		if (_parameter != null) {
			return true;
		}
		else {
			return false;
		}
	}

	public int getStartPos() {
		return _startPos;
	}

	public void setStartPos(int pos) {
		_startPos = pos;
	}

	private String _element;
	private int _endPos;
	private String _parameter;
	private int _startPos;

}