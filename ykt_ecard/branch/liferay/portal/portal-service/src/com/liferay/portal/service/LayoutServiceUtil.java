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

package com.liferay.portal.service;


/**
 * <a href="LayoutServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.LayoutService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.LayoutServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.LayoutService
 * @see com.liferay.portal.service.LayoutServiceFactory
 *
 */
public class LayoutServiceUtil {
	public static com.liferay.portal.model.Layout addLayout(long groupId,
		boolean privateLayout, long parentLayoutId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String type, boolean hidden, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.addLayout(groupId, privateLayout, parentLayoutId,
			name, title, description, type, hidden, friendlyURL);
	}

	public static com.liferay.portal.model.Layout addLayout(long groupId,
		boolean privateLayout, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.addLayout(groupId, privateLayout, parentLayoutId,
			localeNamesMap, localeTitlesMap, description, type, hidden,
			friendlyURL);
	}

	public static void deleteLayout(long plid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.deleteLayout(plid);
	}

	public static void deleteLayout(long groupId, boolean privateLayout,
		long layoutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.deleteLayout(groupId, privateLayout, layoutId);
	}

	public static java.lang.String getLayoutName(long groupId,
		boolean privateLayout, long layoutId, java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.getLayoutName(groupId, privateLayout, layoutId,
			languageId);
	}

	public static com.liferay.portal.model.LayoutReference[] getLayoutReferences(
		long companyId, java.lang.String portletId, java.lang.String prefsKey,
		java.lang.String prefsValue)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.getLayoutReferences(companyId, portletId,
			prefsKey, prefsValue);
	}

	public static byte[] exportLayouts(long groupId, boolean privateLayout,
		java.util.Map parameterMap)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.exportLayouts(groupId, privateLayout, parameterMap);
	}

	public static byte[] exportLayouts(long groupId, boolean privateLayout,
		long[] layoutIds, java.util.Map parameterMap)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.exportLayouts(groupId, privateLayout, layoutIds,
			parameterMap);
	}

	public static byte[] exportPortletInfo(long plid,
		java.lang.String portletId, java.util.Map parameterMap)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.exportPortletInfo(plid, portletId, parameterMap);
	}

	public static void importLayouts(long groupId, boolean privateLayout,
		java.util.Map parameterMap, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.importLayouts(groupId, privateLayout, parameterMap, file);
	}

	public static void importLayouts(long groupId, boolean privateLayout,
		java.util.Map parameterMap, java.io.InputStream is)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.importLayouts(groupId, privateLayout, parameterMap, is);
	}

	public static void importPortletInfo(long plid, java.lang.String portletId,
		java.util.Map parameterMap, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.importPortletInfo(plid, portletId, parameterMap, file);
	}

	public static void importPortletInfo(long plid, java.lang.String portletId,
		java.util.Map parameterMap, java.io.InputStream is)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.importPortletInfo(plid, portletId, parameterMap, is);
	}

	public static void setLayouts(long groupId, boolean privateLayout,
		long parentLayoutId, long[] layoutIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		layoutService.setLayouts(groupId, privateLayout, parentLayoutId,
			layoutIds);
	}

	public static com.liferay.portal.model.Layout updateLayout(long groupId,
		boolean privateLayout, long layoutId, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateLayout(groupId, privateLayout, layoutId,
			parentLayoutId, localeNamesMap, localeTitlesMap, description, type,
			hidden, friendlyURL);
	}

	public static com.liferay.portal.model.Layout updateLayout(long groupId,
		boolean privateLayout, long layoutId, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL, java.lang.Boolean iconImage,
		byte[] iconBytes)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateLayout(groupId, privateLayout, layoutId,
			parentLayoutId, localeNamesMap, localeTitlesMap, description, type,
			hidden, friendlyURL, iconImage, iconBytes);
	}

	public static com.liferay.portal.model.Layout updateLayout(long groupId,
		boolean privateLayout, long layoutId, java.lang.String typeSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateLayout(groupId, privateLayout, layoutId,
			typeSettings);
	}

	public static com.liferay.portal.model.Layout updateLookAndFeel(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String themeId, java.lang.String colorSchemeId,
		java.lang.String css, boolean wapTheme)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateLookAndFeel(groupId, privateLayout,
			layoutId, themeId, colorSchemeId, css, wapTheme);
	}

	public static com.liferay.portal.model.Layout updateName(long plid,
		java.lang.String name, java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateName(plid, name, languageId);
	}

	public static com.liferay.portal.model.Layout updateName(long groupId,
		boolean privateLayout, long layoutId, java.lang.String name,
		java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateName(groupId, privateLayout, layoutId, name,
			languageId);
	}

	public static com.liferay.portal.model.Layout updateParentLayoutId(
		long plid, long parentPlid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateParentLayoutId(plid, parentPlid);
	}

	public static com.liferay.portal.model.Layout updateParentLayoutId(
		long groupId, boolean privateLayout, long layoutId, long parentLayoutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updateParentLayoutId(groupId, privateLayout,
			layoutId, parentLayoutId);
	}

	public static com.liferay.portal.model.Layout updatePriority(long plid,
		int priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updatePriority(plid, priority);
	}

	public static com.liferay.portal.model.Layout updatePriority(long groupId,
		boolean privateLayout, long layoutId, int priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		LayoutService layoutService = LayoutServiceFactory.getService();

		return layoutService.updatePriority(groupId, privateLayout, layoutId,
			priority);
	}
}