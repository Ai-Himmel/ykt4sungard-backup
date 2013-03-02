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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.PortletPreferencesPK;
import com.liferay.portal.service.spring.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.service.spring.PortletPreferencesService;
import com.liferay.portlet.PortletPreferencesImpl;

/**
 * <a href="PortletPreferencesServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class PortletPreferencesServiceImpl
	extends PrincipalBean implements PortletPreferencesService {

	// Business methods

	public javax.portlet.PortletPreferences getDefaultPreferences(
			String companyId, String portletId)
		throws PortalException, SystemException {

		return PortletPreferencesLocalServiceUtil.getDefaultPreferences(
			companyId, portletId);
	}

	public javax.portlet.PortletPreferences getPreferences(
			String companyId, PortletPreferencesPK pk)
		throws PortalException, SystemException {

		return PortletPreferencesLocalServiceUtil.getPreferences(companyId, pk);
	}

	public void updatePreferences(
			PortletPreferencesPK pk, PortletPreferencesImpl prefs)
		throws PortalException, SystemException {

		PortletPreferencesLocalServiceUtil.updatePreferences(pk, prefs);
	}

}