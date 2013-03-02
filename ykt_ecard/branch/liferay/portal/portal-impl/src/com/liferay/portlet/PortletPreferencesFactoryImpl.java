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
import com.liferay.portal.kernel.portlet.LiferayPortletMode;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletPreferencesIds;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.security.permission.PermissionThreadLocal;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.service.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.service.permission.LayoutPermissionUtil;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.PreferencesValidator;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

/**
 * <a href="PortletPreferencesFactoryImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPreferencesFactoryImpl
	implements PortletPreferencesFactory {

	public PortalPreferences getPortalPreferences(HttpServletRequest req)
		throws PortalException, SystemException {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long ownerId = themeDisplay.getUserId();
		int ownerType = PortletKeys.PREFS_OWNER_TYPE_USER;
		long plid = PortletKeys.PREFS_PLID_SHARED;
		String portletId = PortletKeys.LIFERAY_PORTAL;

		PortalPreferences portalPrefs = null;

		if (themeDisplay.isSignedIn()) {
			PortletPreferencesImpl prefsImpl = (PortletPreferencesImpl)
				PortletPreferencesLocalServiceUtil.getPreferences(
					themeDisplay.getCompanyId(), ownerId, ownerType, plid,
					portletId);

			portalPrefs = new PortalPreferencesImpl(
				prefsImpl, themeDisplay.isSignedIn());
		}
		else {
			HttpSession ses = req.getSession();

			portalPrefs = (PortalPreferences)ses.getAttribute(
				WebKeys.PORTAL_PREFERENCES);

			if (portalPrefs == null) {
				PortletPreferencesImpl prefsImpl = (PortletPreferencesImpl)
					PortletPreferencesLocalServiceUtil.getPreferences(
						themeDisplay.getCompanyId(), ownerId, ownerType, plid,
						portletId);

				prefsImpl = (PortletPreferencesImpl)prefsImpl.clone();

				portalPrefs = new PortalPreferencesImpl(
					prefsImpl, themeDisplay.isSignedIn());

				ses.setAttribute(WebKeys.PORTAL_PREFERENCES, portalPrefs);
			}
		}

		return portalPrefs;
	}

	public PortalPreferences getPortalPreferences(ActionRequest req)
		throws PortalException, SystemException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getPortalPreferences(httpReq);
	}

	public PortalPreferences getPortalPreferences(RenderRequest req)
		throws PortalException, SystemException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getPortalPreferences(httpReq);
	}

	public PortletPreferences getPortletPreferences(
			HttpServletRequest req, String portletId)
		throws PortalException, SystemException {

		PortletPreferencesIds portletPreferencesIds = getPortletPreferencesIds(
			req, portletId);

		return PortletPreferencesLocalServiceUtil.getPreferences(
			portletPreferencesIds);
	}

	public PortletPreferencesIds getPortletPreferencesIds(
			HttpServletRequest req, String portletId)
		throws PortalException, SystemException {

		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		return getPortletPreferencesIds(req, layout, portletId);
	}

	public PortletPreferencesIds getPortletPreferencesIds(
			HttpServletRequest req, Layout selLayout, String portletId)
		throws PortalException, SystemException {

		// Below is a list of  the possible combinations, where we specify the
		// the owner id, the layout id, portlet id, and the function.

		// liferay.com.1, SHARED, PORTAL, preference is scoped per user across
		// the entire portal

		// COMPANY.liferay.com, SHARED, 56_INSTANCE_abcd, preference is scoped
		// per portlet and company and is shared across all layouts

		// GROUP.10, SHARED, 56_INSTANCE_abcd, preference is scoped per portlet
		// and group and is shared across all layouts

		// USER.liferay.com.1, SHARED, 56_INSTANCE_abcd, preference is scoped
		// per portlet and user and is shared across all layouts

		// PUB.10, 3, 56_INSTANCE_abcd, preference is scoped per portlet, group,
		// and layout

		// PUB.10.USER.liferay.com.1, 3, 56_INSTANCE_abcd, preference is scoped
		// per portlet, user, and layout

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		Layout layout = themeDisplay.getLayout();
		LayoutTypePortlet layoutTypePortlet =
			themeDisplay.getLayoutTypePortlet();
		PermissionChecker permissionChecker =
			PermissionThreadLocal.getPermissionChecker();

		Portlet portlet = PortletLocalServiceUtil.getPortletById(
			themeDisplay.getCompanyId(), portletId);

		long ownerId = 0;
		int ownerType = 0;
		long plid = 0;

		boolean modeEditGuest = false;

		String portletMode = ParamUtil.getString(req, "p_p_mode");

		if (portletMode.equals(LiferayPortletMode.EDIT_GUEST.toString()) ||
			layoutTypePortlet.hasModeEditGuestPortletId(portletId)) {

			modeEditGuest = true;
		}

		if (modeEditGuest) {
			boolean hasUpdateLayoutPermission = LayoutPermissionUtil.contains(
				permissionChecker, layout, ActionKeys.UPDATE);

			if (!layout.isPrivateLayout() && hasUpdateLayoutPermission) {
			}
			else {

				// Only users with the correct permissions can update guest
				// preferences

				throw new PrincipalException();
			}
		}

		if (portlet.isPreferencesCompanyWide()) {
			ownerId = themeDisplay.getCompanyId();
			ownerType = PortletKeys.PREFS_OWNER_TYPE_COMPANY;
			plid = PortletKeys.PREFS_PLID_SHARED;
		}
		else {
			if (portlet.isPreferencesUniquePerLayout()) {
				ownerId = PortletKeys.PREFS_OWNER_ID_DEFAULT;
				ownerType = PortletKeys.PREFS_OWNER_TYPE_LAYOUT;
				plid = selLayout.getPlid();

				if (portlet.isPreferencesOwnedByGroup()) {
				}
				else {
					long userId = PortalUtil.getUserId(req);

					if ((userId <= 0) || modeEditGuest) {
						userId = UserLocalServiceUtil.getDefaultUserId(
							themeDisplay.getCompanyId());
					}

					ownerId = userId;
					ownerType = PortletKeys.PREFS_OWNER_TYPE_USER;
				}
			}
			else {
				plid = PortletKeys.PREFS_PLID_SHARED;

				if (portlet.isPreferencesOwnedByGroup()) {
					ownerId = selLayout.getGroupId();
					ownerType = PortletKeys.PREFS_OWNER_TYPE_GROUP;
				}
				else {
					long userId = PortalUtil.getUserId(req);

					if ((userId <= 0) || modeEditGuest) {
						userId = UserLocalServiceUtil.getDefaultUserId(
							themeDisplay.getCompanyId());
					}

					ownerId = userId;
					ownerType = PortletKeys.PREFS_OWNER_TYPE_USER;
				}
			}
		}

		return new PortletPreferencesIds(
			themeDisplay.getCompanyId(), ownerId, ownerType, plid, portletId);
	}

	public PortletPreferences getPortletSetup(
			Layout layout, String portletId)
		throws PortalException, SystemException {

		long ownerId = PortletKeys.PREFS_OWNER_ID_DEFAULT;
		int ownerType = PortletKeys.PREFS_OWNER_TYPE_LAYOUT;

		return PortletPreferencesLocalServiceUtil.getPreferences(
			layout.getCompanyId(), ownerId, ownerType, layout.getPlid(),
			portletId);
	}

	public PortletPreferences getPortletSetup(
			HttpServletRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException {

		return getPortletSetup(
			req, portletId, uniquePerLayout, uniquePerGroup, null);
	}

	public PortletPreferences getPortletSetup(
			HttpServletRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup, String defaultPreferences)
		throws PortalException, SystemException {

		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		return getPortletSetup(
			layout, portletId, uniquePerLayout, uniquePerGroup,
			defaultPreferences);
	}

	public PortletPreferences getPortletSetup(
			Layout layout, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup, String defaultPreferences)
		throws PortalException, SystemException {

		long ownerId = PortletKeys.PREFS_OWNER_ID_DEFAULT;
		int ownerType = PortletKeys.PREFS_OWNER_TYPE_LAYOUT;
		long plid = layout.getPlid();

		if (!uniquePerLayout) {
			plid = PortletKeys.PREFS_PLID_SHARED;

			if (uniquePerGroup) {
				ownerId = layout.getGroupId();
				ownerType = PortletKeys.PREFS_OWNER_TYPE_GROUP;
			}
			else {
				ownerId = layout.getCompanyId();
				ownerType = PortletKeys.PREFS_OWNER_TYPE_COMPANY;
			}
		}

		return PortletPreferencesLocalServiceUtil.getPreferences(
			layout.getCompanyId(), ownerId, ownerType, plid, portletId,
			defaultPreferences);
	}

	public PortletPreferences getPortletSetup(
			ActionRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getPortletSetup(
			httpReq, portletId, uniquePerLayout, uniquePerGroup);
	}

	public PortletPreferences getPortletSetup(
			RenderRequest req, String portletId, boolean uniquePerLayout,
			boolean uniquePerGroup)
		throws PortalException, SystemException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getPortletSetup(
			httpReq, portletId, uniquePerLayout, uniquePerGroup);
	}

	public PortletPreferences getPreferences(HttpServletRequest req) {
		RenderRequest renderRequest = (RenderRequest)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_REQUEST);

		PortletPreferences prefs = null;

		if (renderRequest != null) {
			PortletPreferencesWrapper prefsWrapper =
				(PortletPreferencesWrapper)renderRequest.getPreferences();

			prefs = prefsWrapper.getPreferencesImpl();
		}

		return prefs;
	}

	public PreferencesValidator getPreferencesValidator(Portlet portlet) {
		if (portlet.isWARFile()) {
			PortletContextWrapper pcw =
				PortletContextPool.get(portlet.getRootPortletId());

			return pcw.getPreferencesValidatorInstance();
		}
		else {
			PreferencesValidator prefsValidator = null;

			if (Validator.isNotNull(portlet.getPreferencesValidator())) {
				prefsValidator =
					(PreferencesValidator)InstancePool.get(
						portlet.getPreferencesValidator());
			}

			return prefsValidator;
		}
	}

}