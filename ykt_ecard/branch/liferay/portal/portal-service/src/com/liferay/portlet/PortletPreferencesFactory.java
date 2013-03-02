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
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletPreferencesIds;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.PreferencesValidator;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="PortletPreferencesFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface PortletPreferencesFactory {

	public PortalPreferences getPortalPreferences(HttpServletRequest req)
		throws PortalException, SystemException;

	public PortalPreferences getPortalPreferences(ActionRequest req)
		throws PortalException, SystemException;

	public PortalPreferences getPortalPreferences(RenderRequest req)
		throws PortalException, SystemException;

	public PortletPreferences getPortletPreferences(
			HttpServletRequest req, String portletId)
		throws PortalException, SystemException;

	public PortletPreferencesIds getPortletPreferencesIds(
			HttpServletRequest req, String portletId)
		throws PortalException, SystemException;

	public PortletPreferencesIds getPortletPreferencesIds(
			HttpServletRequest req, Layout selLayout, String portletId)
		throws PortalException, SystemException;

	public PortletPreferences getPortletSetup(
			Layout layout, String portletId)
		throws PortalException, SystemException;

	public PortletPreferences getPortletSetup(
			HttpServletRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException;

	public PortletPreferences getPortletSetup(
			HttpServletRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup, String defaultPreferences)
		throws PortalException, SystemException;

	public PortletPreferences getPortletSetup(
			Layout layout, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup, String defaultPreferences)
		throws PortalException, SystemException;

	public PortletPreferences getPortletSetup(
			ActionRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException;

	public PortletPreferences getPortletSetup(
			RenderRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException;

	public PortletPreferences getPreferences(HttpServletRequest req);

	public PreferencesValidator getPreferencesValidator(Portlet portlet);

}