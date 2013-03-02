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
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletPreferencesIds;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.PreferencesValidator;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="PortletPreferencesFactoryUtil.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPreferencesFactoryUtil {

	public static PortalPreferences getPortalPreferences(HttpServletRequest req)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortalPreferences(req);
	}

	public static PortalPreferences getPortalPreferences(ActionRequest req)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortalPreferences(req);
	}

	public static PortalPreferences getPortalPreferences(RenderRequest req)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortalPreferences(req);
	}

	public static PortletPreferences getPortletPreferences(
			HttpServletRequest req, String portletId)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletPreferences(
			req, portletId);
	}

	public static PortletPreferencesFactory getPortletPreferencesFactory() {
		return _getUtil()._portletPreferencesFactory;
	}

	public static PortletPreferencesIds getPortletPreferencesIds(
			HttpServletRequest req, String portletId)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletPreferencesIds(
			req, portletId);
	}

	public static PortletPreferencesIds getPortletPreferencesIds(
			HttpServletRequest req, Layout selLayout, String portletId)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletPreferencesIds(
			req, selLayout, portletId);
	}

	public static PortletPreferences getPortletSetup(
			Layout layout, String portletId)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletSetup(
			layout, portletId);
	}

	public static PortletPreferences getPortletSetup(
			HttpServletRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletSetup(
			req, portletId, uniquePerLayout, uniquePerGroup);
	}

	public static PortletPreferences getPortletSetup(
			HttpServletRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup, String defaultPreferences)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletSetup(
			req, portletId, uniquePerLayout, uniquePerGroup,
			defaultPreferences);
	}

	public static PortletPreferences getPortletSetup(
			Layout layout, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup, String defaultPreferences)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletSetup(
			layout, portletId, uniquePerLayout, uniquePerGroup,
			defaultPreferences);
	}

	public static PortletPreferences getPortletSetup(
			ActionRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletSetup(
			req, portletId, uniquePerLayout, uniquePerGroup);
	}

	public static PortletPreferences getPortletSetup(
			RenderRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException {

		return getPortletPreferencesFactory().getPortletSetup(
			req, portletId, uniquePerLayout, uniquePerGroup);
	}

	public static PortletPreferences getPreferences(HttpServletRequest req) {
		return getPortletPreferencesFactory().getPreferences(req);
	}

	public static PreferencesValidator getPreferencesValidator(
		Portlet portlet) {

		return getPortletPreferencesFactory().getPreferencesValidator(portlet);
	}

	public void setPortletPreferencesFactory(
		PortletPreferencesFactory portletPreferencesFactory) {

		_portletPreferencesFactory = portletPreferencesFactory;
	}

	private static PortletPreferencesFactoryUtil _getUtil() {
		if (_util == null) {
			_util =
				(PortletPreferencesFactoryUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL =
		PortletPreferencesFactoryUtil.class.getName();

	private static PortletPreferencesFactoryUtil _util;

	private PortletPreferencesFactory _portletPreferencesFactory;

}