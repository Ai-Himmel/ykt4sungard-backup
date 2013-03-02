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

package com.liferay.portlet;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.service.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.util.xml.XMLFormatter;

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

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletPreferencesImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPreferencesImpl
	implements Cloneable, PortletPreferences, Serializable {

	public PortletPreferencesImpl() {
		this(0, 0, 0, 0, null, new HashMap());
	}

	public PortletPreferencesImpl(long companyId, long ownerId, int ownerType,
								  long plid, String portletId,
								  Map preferences) {

		_companyId = companyId;
		_ownerId = ownerId;
		_ownerType = ownerType;
		_plid = plid;
		_portletId = portletId;
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

	public void reset() {
		_preferences.clear();
	}

	public void reset(String key) throws ReadOnlyException {
		if (isReadOnly(key)) {
			throw new ReadOnlyException(key);
		}

		if (_defaultPreferences == null) {
			try {
				if ((_portletId != null) &&
					(!_portletId.equals(PortletKeys.LIFERAY_PORTAL))) {

					_defaultPreferences = PortletPreferencesLocalServiceUtil.
						getDefaultPreferences(_companyId, _portletId);
				}
			}
			catch (Exception e) {
				_log.error(e, e);
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
		if (_portletId == null) {
			throw new UnsupportedOperationException();
		}

		try {
			Portlet portlet = PortletLocalServiceUtil.getPortletById(
				_companyId, _portletId);

			if (!_portletId.equals(PortletKeys.LIFERAY_PORTAL)) {
				PreferencesValidator prefsValidator =
					PortalUtil.getPreferencesValidator(portlet);

				if (prefsValidator != null) {
					prefsValidator.validate(this);
				}
			}

			PortletPreferencesLocalServiceUtil.updatePreferences(
				_ownerId, _ownerType, _plid, _portletId, this);
		}
		catch (PortalException pe) {
			_log.error(pe, pe);

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

		return new PortletPreferencesImpl(
			_companyId, _ownerId, _ownerType, _plid, _portletId,
			preferencesClone);
	}

	protected long getCompanyId() {
		return  _companyId;
	}

	protected long getOwnerId() {
		return _ownerId;
	}

	protected int getOwnerType() {
		return _ownerType;
	}

	protected long getPlid() {
		return _plid;
	}

	protected String getPortletId() {
		return _portletId;
	}

	protected Map getPreferences() {
		return _preferences;
	}

	private String _getActualValue(String value) {
		if ((value == null) || (value.equals(_NULL_VALUE))) {
			return null;
		}
		else {
			return XMLFormatter.fromCompactSafe(value);
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
			return XMLFormatter.toCompactSafe(value);
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

	private static final String _NULL_VALUE = "NULL_VALUE";

	private static Log _log = LogFactory.getLog(PortletPreferencesImpl.class);

	private long _companyId;
	private long _ownerId;
	private int _ownerType;
	private long _plid;
	private String _portletId;
	private Map _preferences;
	private PortletPreferences _defaultPreferences;

}