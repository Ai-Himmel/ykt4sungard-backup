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

package com.liferay.portlet;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.persistence.PortletPreferencesPK;
import com.liferay.portal.service.spring.PortletPreferencesServiceUtil;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.util.PortalUtil;

import java.io.IOException;
import java.io.Serializable;

import java.util.Collections;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletPreferences;
import javax.portlet.PreferencesValidator;
import javax.portlet.ReadOnlyException;
import javax.portlet.ValidatorException;

/**
 * <a href="PortletPreferencesImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.25 $
 *
 */
public class PortletPreferencesImpl
	implements Cloneable, PortletPreferences, Serializable {

	public PortletPreferencesImpl() {
		this(null, null, new HashMap());
	}

	public PortletPreferencesImpl(String companyId, PortletPreferencesPK pk,
								  Map preferences) {

		_companyId = companyId;
		_pk = pk;
		_preferences = preferences;
	}

	public Map getMap() {
		Map map = new HashMap();

		Iterator itr = _preferences.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			Preference preference = (Preference)entry.getValue();

			map.put(key, _getActualValues(preference.getValues()));
		}

		return Collections.unmodifiableMap(map);
	}

	public Enumeration getNames() {
		return Collections.enumeration(_preferences.keySet());
	}

	public String getValue(String key, String def) {
		if (key == null) {
			throw new IllegalArgumentException();
		}

		Preference preference = (Preference)_preferences.get(key);

		String[] values = null;
		if (preference != null) {
			values = preference.getValues();
		}

		if (values != null && values.length > 0) {
			return _getActualValue(values[0]);
		}
		else {
			return _getActualValue(def);
		}
	}

	public void setValue(String key, String value) throws ReadOnlyException {
		if (key == null) {
			throw new IllegalArgumentException();
		}

		value = _getXmlSafeValue(value);

		Preference preference = (Preference)_preferences.get(key);

		if (preference == null) {
			preference = new Preference(key, value);

			_preferences.put(key, preference);
		}

		if (preference.isReadOnly()) {
			throw new ReadOnlyException(key);
		}
		else {
			preference.setValues(new String[] {value});
		}
	}

	public String[] getValues(String key, String[] def) {
		if (key == null) {
			throw new IllegalArgumentException();
		}

		Preference preference = (Preference)_preferences.get(key);

		String[] values = null;
		if (preference != null) {
			values = preference.getValues();
		}

		if (values != null && values.length > 0) {
			return _getActualValues(values);
		}
		else {
			return _getActualValues(def);
		}
	}

	public void setValues(String key, String[] values)
		throws ReadOnlyException {

		if (key == null) {
			throw new IllegalArgumentException();
		}

		values = _getXmlSafeValues(values);

		Preference preference = (Preference)_preferences.get(key);

		if (preference == null) {
			preference = new Preference(key, values);

			_preferences.put(key, preference);
		}

		if (preference.isReadOnly()) {
			throw new ReadOnlyException(key);
		}
		else {
			preference.setValues(values);
		}
	}

	public boolean isReadOnly(String key) {
		if (key == null) {
			throw new IllegalArgumentException();
		}

		Preference preference = (Preference)_preferences.get(key);

		if (preference != null && preference.isReadOnly()) {
			return true;
		}
		else {
			return false;
		}
	}

	public void reset(String key) throws ReadOnlyException {
		if (isReadOnly(key)) {
			throw new ReadOnlyException(key);
		}

		if (_defaultPreferences == null) {
			try {
				_defaultPreferences =
					PortletPreferencesServiceUtil.getDefaultPreferences(
						_companyId, _pk.portletId);
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}

		String[] defaultValues = null;

		if (_defaultPreferences != null) {
			defaultValues = _defaultPreferences.getValues(key, defaultValues);
		}

		if (defaultValues != null) {
			setValues(key, defaultValues);
		}
		else {
			_preferences.remove(key);
		}
	}

	public void store() throws IOException, ValidatorException {
		if (_pk == null) {
			throw new UnsupportedOperationException();
		}

		try {
			Portlet portlet =
				PortletServiceUtil.getPortletById(_companyId, _pk.portletId);

			PreferencesValidator prefsValidator =
				PortalUtil.getPreferencesValidator(portlet);

			if (prefsValidator != null) {
				prefsValidator.validate(this);
			}

			PortletPreferencesServiceUtil.updatePreferences(_pk, this);
		}
		catch (PortalException pe) {
			pe.printStackTrace();

			throw new IOException(pe.getMessage());
		}
		catch (SystemException se) {
			throw new IOException(se.getMessage());
		}
	}

	public Object clone() {
		Map preferencesClone = new HashMap();

		Iterator itr = _preferences.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			Preference preference = (Preference)entry.getValue();

			preferencesClone.put(key, preference.clone());
		}

		return new PortletPreferencesImpl(_companyId, _pk, preferencesClone);
	}

	protected String getCompanyId() {
		return  _companyId;
	}

	protected PortletPreferencesPK getPrimaryKey() {
		return _pk;
	}

	protected Map getPreferences() {
		return _preferences;
	}

	private String _getActualValue(String value) {
		if (value.equals(_NULL_VALUE)) {
			return null;
		}
		else {
			return value;
		}
	}

	private String[] _getActualValues(String[] values) {
		if (values == null) {
			return null;
		}

		if ((values.length == 1) && (_getActualValue(values[0]) == null)) {
			return null;
		}

		String[] actualValues = new String[values.length];

		System.arraycopy(values, 0, actualValues, 0, values.length);

		for (int i = 0; i < actualValues.length; i++) {
			actualValues[i] = _getActualValue(actualValues[i]);
		}

		return actualValues;
	}

	private String _getXmlSafeValue(String value) {
		if (value == null) {
			return _NULL_VALUE;
		}
		else {
			return value;
		}
	}

	private String[] _getXmlSafeValues(String[] values) {
		if (values == null) {
			return new String[] {
					_getXmlSafeValue(null)
				};
		}

		String[] xmlSafeValues = new String[values.length];

		System.arraycopy(values, 0, xmlSafeValues, 0, values.length);

		for (int i = 0; i < xmlSafeValues.length; i++) {
			if (xmlSafeValues[i] == null) {
				xmlSafeValues[i] = _getXmlSafeValue(xmlSafeValues[i]);
			}
		}

		return xmlSafeValues;
	}

	private static String _NULL_VALUE = "NULL_VALUE";

	private String _companyId = null;
	private PortletPreferencesPK _pk = null;
	private Map _preferences = null;
	private PortletPreferences _defaultPreferences = null;

}