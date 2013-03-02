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

package com.liferay.portal.service.spring;

/**
 * <a href="LayoutRemoteServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class LayoutRemoteServiceUtil {
	public static com.liferay.portal.model.Layout addGroupLayout(
		java.lang.String groupId, java.lang.String parentLayoutId,
		java.lang.String name, java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.addGroupLayout(groupId, parentLayoutId,
				name, type);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.Layout addUserLayout(
		java.lang.String userId, java.lang.String parentLayoutId,
		java.lang.String name, java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.addUserLayout(userId, parentLayoutId,
				name, type);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteAll(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();
			layoutRemoteService.deleteAll(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteLayout(
		com.liferay.portal.service.persistence.LayoutPK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();
			layoutRemoteService.deleteLayout(pk);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteLayout(com.liferay.portal.model.Layout layout)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();
			layoutRemoteService.deleteLayout(layout);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.Layout getLayout(
		com.liferay.portal.service.persistence.LayoutPK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.getLayout(pk);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.Layout getLayoutByFriendlyURL(
		java.lang.String groupId, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.getLayoutByFriendlyURL(groupId,
				friendlyURL);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getLayouts(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.getLayouts(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.Layout updateLayout(
		com.liferay.portal.service.persistence.LayoutPK pk,
		java.lang.String name, java.lang.String typeSettings,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.updateLayout(pk, name, typeSettings,
				friendlyURL);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.Layout updateLayout(
		com.liferay.portal.service.persistence.LayoutPK pk,
		java.lang.String typeSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			LayoutRemoteService layoutRemoteService = LayoutRemoteServiceFactory.getService();

			return layoutRemoteService.updateLayout(pk, typeSettings);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}