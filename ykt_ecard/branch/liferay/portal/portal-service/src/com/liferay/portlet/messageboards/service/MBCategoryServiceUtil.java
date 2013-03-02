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

package com.liferay.portlet.messageboards.service;


/**
 * <a href="MBCategoryServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.messageboards.service.MBCategoryService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.messageboards.service.MBCategoryServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBCategoryService
 * @see com.liferay.portlet.messageboards.service.MBCategoryServiceFactory
 *
 */
public class MBCategoryServiceUtil {
	public static com.liferay.portlet.messageboards.model.MBCategory addCategory(
		long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		return mbCategoryService.addCategory(plid, parentCategoryId, name,
			description, communityPermissions, guestPermissions);
	}

	public static void deleteCategory(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		mbCategoryService.deleteCategory(categoryId);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory getCategory(
		long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		return mbCategoryService.getCategory(categoryId);
	}

	public static java.util.List getCategories(long groupId,
		long parentCategoryId, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		return mbCategoryService.getCategories(groupId, parentCategoryId,
			begin, end);
	}

	public static int getCategoriesCount(long groupId, long parentCategoryId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		return mbCategoryService.getCategoriesCount(groupId, parentCategoryId);
	}

	public static void subscribeCategory(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		mbCategoryService.subscribeCategory(categoryId);
	}

	public static void unsubscribeCategory(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		mbCategoryService.unsubscribeCategory(categoryId);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory updateCategory(
		long categoryId, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean mergeWithParentCategory)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBCategoryService mbCategoryService = MBCategoryServiceFactory.getService();

		return mbCategoryService.updateCategory(categoryId, parentCategoryId,
			name, description, mergeWithParentCategory);
	}
}