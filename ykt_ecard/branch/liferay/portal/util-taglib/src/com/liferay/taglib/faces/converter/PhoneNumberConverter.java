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

import com.liferay.portal.kernel.language.LanguageUtil;

import java.util.Locale;

import javax.faces.application.FacesMessage;
import javax.faces.component.StateHolder;
import javax.faces.component.UIComponent;
import javax.faces.context.ExternalContext;
import javax.faces.context.FacesContext;
import javax.faces.convert.Converter;
import javax.faces.convert.ConverterException;

/**
 * <a href="PhoneNumberConverter.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class is a JSF converter that can be used to convert phone numbers.
 * Since phone numbers in the United States of America always have 10 digits,
 * this converter provides automatic conversion of 10 digit phone numbers to
 * a desired format. The format is specified by the unitedStatesFormat
 * component attribute.
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class PhoneNumberConverter implements Converter, StateHolder {

	public boolean isTransient() {
		return _transient;
	}

	public void setTransient(boolean value) {
		_transient = value;
	}

	public String getUnitedStatesFormat() {
		return _unitedStatesFormat;
	}

	public void setUnitedStatesFormat(String unitedStatesFormat) {
		_unitedStatesFormat = unitedStatesFormat;
	}

	public Object getAsObject(
		FacesContext facesContext, UIComponent uiComponent, String value) {

		if (value != null) {
			StringBuffer integerChars = new StringBuffer();
			StringBuffer invalidChars = new StringBuffer();

			for (int i = 0; i < value.length(); i++) {
				char curChar = value.charAt(i);

				if (Character.isDigit(curChar)) {
					integerChars.append(curChar);
				}
				else if ((curChar != '-') && (curChar != '(') &&
						 (curChar != ')') && (curChar != '.') &&
						 (curChar != '+') && (curChar != ' ')) {

					invalidChars.append(curChar);
				}
			}

			if (invalidChars.length() > 0) {
				ExternalContext externalContext =
					facesContext.getExternalContext();

				Locale locale = externalContext.getRequestLocale();

				String summary = LanguageUtil.get(
					locale, "the-following-are-invalid-characters");

				summary += " " + invalidChars.toString();

				FacesMessage facesMessage = new FacesMessage(
					FacesMessage.SEVERITY_ERROR, summary, null);

				throw new ConverterException(facesMessage);
			}
			else if ((integerChars.length() == 10)) {
				StringBuffer unitedStatesPhoneNumber = new StringBuffer();

				int integerDigitIndex = 0;

				for (int i = 0; i < _unitedStatesFormat.length(); i++) {
					char curChar = _unitedStatesFormat.charAt(i);

					if (curChar == '#') {
						unitedStatesPhoneNumber.append(
							integerChars.charAt(integerDigitIndex++));
					}
					else {
						unitedStatesPhoneNumber.append(curChar);
					}
				}

				return unitedStatesPhoneNumber.toString();
			}
		}

		return value;
	}

	public String getAsString(
		FacesContext facesContext, UIComponent uiComponent, Object value)
		throws ConverterException {

		// ICE-1537

		return (String)value;
	}

	public void restoreState(FacesContext facesContext, Object obj) {
		Object[] values = (Object[])obj;

		_unitedStatesFormat = (String)values[0];
	}

	public Object saveState(FacesContext facesContext) {
		Object[] values = new Object[1];

		values[0] = _unitedStatesFormat;

		return values;
	}

	private boolean _transient;
	private String _unitedStatesFormat;

}