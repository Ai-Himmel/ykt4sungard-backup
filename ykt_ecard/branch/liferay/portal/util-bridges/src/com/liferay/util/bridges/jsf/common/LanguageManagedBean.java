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

package com.liferay.util.bridges.jsf.common;

import com.liferay.portal.kernel.language.LanguageUtil;

import java.util.Collection;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import javax.faces.context.FacesContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LanguageManagedBean.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class serves as a bridge between the JSF Expression Language (EL)
 * and Liferay's Language.properties resource bundle.
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class LanguageManagedBean implements Map {

	public LanguageManagedBean() {

		// LEP-3275

		FacesContext facesContext = FacesContext.getCurrentInstance();

		_companyId = JSFPortletUtil.getCompanyId(facesContext);

		if (_companyId == 0) {
			_log.error("Unable to determine company id from facesContext");
		}
	}

	public void clear() {
		throw new UnsupportedOperationException();
	}

	public boolean containsKey(Object key) {
		throw new UnsupportedOperationException();
	}

	public boolean containsValue(Object value) {
		throw new UnsupportedOperationException();
	}

	public boolean isEmpty() {
		throw new UnsupportedOperationException();
	}

	public Set entrySet() {
		throw new UnsupportedOperationException();
	}

	public Object get(Object key) {
		Object value = null;

		if (key != null) {
			FacesContext facesContext = FacesContext.getCurrentInstance();

			Locale locale = facesContext.getViewRoot().getLocale();

			if (locale == null) {
				locale = facesContext.getApplication().getDefaultLocale();
			}

			value = LanguageUtil.get(_companyId, locale, key.toString());

			if (_log.isDebugEnabled()) {
				_log.debug(
					"{companyId=" + _companyId + ", locale=" + locale +
						", key=" + key + ", value=" + value);
			}
		}

		return value;
	}

	public Set keySet() {
		throw new UnsupportedOperationException();
	}

	public Object put(Object key, Object value) {
		throw new UnsupportedOperationException();
	}

	public void putAll(Map map) {
		throw new UnsupportedOperationException();
	}

	public Object remove(Object key) {
		throw new UnsupportedOperationException();
	}

	public int size() {
		throw new UnsupportedOperationException();
	}

	public Collection values() {
		throw new UnsupportedOperationException();
	}

	private static Log _log = LogFactory.getLog(LanguageManagedBean.class);

	private long _companyId = 0;

}