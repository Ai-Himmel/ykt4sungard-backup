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

package com.liferay.taglib.faces.validator;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.Validator;

import java.util.Locale;

import javax.faces.application.FacesMessage;
import javax.faces.component.StateHolder;
import javax.faces.component.UIComponent;
import javax.faces.context.ExternalContext;
import javax.faces.context.FacesContext;
import javax.faces.validator.ValidatorException;

import org.apache.commons.validator.EmailValidator;

/**
 * <a href="EmailAddressValidator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Neil Griffin
 *
 */
public class EmailAddressValidator
	implements StateHolder, javax.faces.validator.Validator {

	public void restoreState(FacesContext facesContext, Object obj) {
	}

	public Object saveState(FacesContext facesContext) {
		return null;
	}

	public void validate(
			FacesContext facesContext, UIComponent uiComponent, Object obj)
		throws ValidatorException {

		ExternalContext externalContext = facesContext.getExternalContext();

		Locale locale = externalContext.getRequestLocale();

		if (obj instanceof String) {
			String emailAddress = (String)obj;

			if (Validator.isNotNull(emailAddress)) {
				if (!EmailValidator.getInstance().isValid(emailAddress)) {
					String summary = LanguageUtil.get(
						locale, "please-enter-a-valid-email-address");

					FacesMessage facesMessage = new FacesMessage(
						FacesMessage.SEVERITY_ERROR, summary, null);

					throw new ValidatorException(facesMessage);
				}
			}
		}
		else {
			String summary = LanguageUtil.format(
				locale,
				"validator-expected-type-string,-but-instead-received-type-x",
				obj.getClass().getName());

			FacesMessage facesMessage = new FacesMessage(
				FacesMessage.SEVERITY_ERROR, summary, null);

			throw new ValidatorException(facesMessage);
		}
	}

	public boolean isTransient() {
		return _transient;
	}

	public void setTransient(boolean value) {
		_transient = value;
	}

	private boolean _transient;

}