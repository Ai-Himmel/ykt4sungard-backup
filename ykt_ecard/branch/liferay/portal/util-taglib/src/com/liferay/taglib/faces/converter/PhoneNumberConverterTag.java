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

package com.liferay.taglib.faces.converter;

import com.liferay.taglib.faces.util.JSFTagUtil;

import javax.faces.convert.Converter;
import javax.faces.webapp.ConverterTag;

import javax.servlet.jsp.JspException;

/**
 * <a href="PhoneNumberConverterTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Neil Griffin
 *
 */
public class PhoneNumberConverterTag extends ConverterTag {

	public PhoneNumberConverterTag() {
		setConverterId(PhoneNumberConverter.class.getName());
	}

	public void setUnitedStatesFormat(String unitedStatesFormat) {
		_unitedStatesFormat = unitedStatesFormat;
	}

	public void release() {
		_unitedStatesFormat = null;
	}

	protected Converter createConverter() throws JspException {
		PhoneNumberConverter converter =
			(PhoneNumberConverter)super.createConverter();

		converter.setUnitedStatesFormat(JSFTagUtil.eval(_unitedStatesFormat));

		return converter;
	}

	private String _unitedStatesFormat = "(###) ###-####";

}