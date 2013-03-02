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

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;

import javax.faces.context.FacesContext;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletPreferencesManagedBean.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Neil Griffin
 *
 */
public class PortletPreferencesManagedBean {

	public PortletPreferencesManagedBean() {

		// Store the portlet preferences as a bean property because of ICE-1625.
		// When using normal JSF, this constructor will get called each time a
		// request is made. This is a little inefficient, but it's a coding
		// tradeoff to make things work with both normal JSF and ICEfaces 1.6.0.

		FacesContext facesContext = FacesContext.getCurrentInstance();

		_portletPreferences =
			JSFPortletUtil.getPortletPreferences(facesContext);

		// Portlet preferences are backed by a map of string arrays. This makes
		// the JSP syntax a little funky, so in order to make the syntax easier,
		// copy each name and its first value into a new map where the name and
		// value are both strings.

		_preferences = new HashMap();

		Enumeration enu = _portletPreferences.getNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();
			String value = _portletPreferences.getValue(name, null);

			_preferences.put(name, value);

			if (_log.isDebugEnabled()) {
				_log.debug("{name=" + name + ", value=" + value + "}");
			}
		}
	}

	public Map getPreferences() {
		return _preferences;
	}

	public String resetDefaultValues() {
		try {
			Enumeration enu = _portletPreferences.getNames();

			while (enu.hasMoreElements()) {
				String name = (String)enu.nextElement();

				if (!_portletPreferences.isReadOnly(name)) {
					_portletPreferences.reset(name);

					String value = _portletPreferences.getValue(name, null);

					_preferences.put(name, value);

					_portletPreferences.store();
				}
			}

			addInfoMessage("you-have-successfully-reset-your-preferences");

			return ActionOutcomes.SUCCESS;
		}
		catch (Exception e) {
			_log.error(e, e);

			addErrorMessage(
				"an-error-occurred-while-resetting-your-preferences");

			return ActionOutcomes.FAILURE;
		}
	}

	public String submit() {
		try {
			Enumeration enu = _portletPreferences.getNames();

			while (enu.hasMoreElements()) {
				String name = (String)enu.nextElement();

				if (!_portletPreferences.isReadOnly(name)) {
					String value = (String)_preferences.get(name);

					_portletPreferences.setValue(name, value);
				}
			}

			_portletPreferences.store();

			addInfoMessage("you-have-successfully-updated-your-preferences");

			return ActionOutcomes.SUCCESS;
		}
		catch (Exception e) {
			_log.error(e, e);

			addErrorMessage(
				"an-error-occurred-while-updating-your-preferences");

			return ActionOutcomes.FAILURE;
		}
	}

	protected void addErrorMessage(String key) {
		FacesContext facesContext = FacesContext.getCurrentInstance();

		FacesMessageUtil.error(facesContext, key);
	}

	protected void addInfoMessage(String key) {
		FacesContext facesContext = FacesContext.getCurrentInstance();

		FacesMessageUtil.info(facesContext, key);
	}

	private static Log _log =
		LogFactory.getLog(PortletPreferencesManagedBean.class);

	private PortletPreferences _portletPreferences;
	private Map _preferences;

}