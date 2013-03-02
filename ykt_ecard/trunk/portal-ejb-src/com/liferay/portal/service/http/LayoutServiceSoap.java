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

package com.liferay.portal.service.http;

import com.liferay.portal.service.spring.LayoutServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="LayoutServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class LayoutServiceSoap {
	public static com.liferay.portal.model.LayoutModel addGroupLayout(
		java.lang.String groupId, java.lang.String parentLayoutId,
		java.lang.String name, java.lang.String type) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.addGroupLayout(groupId,
					parentLayoutId, name, type);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutModel addUserLayout(
		java.lang.String parentLayoutId, java.lang.String name,
		java.lang.String type) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.addUserLayout(parentLayoutId,
					name, type);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteLayout(
		com.liferay.portal.service.persistence.LayoutPK pk)
		throws RemoteException {
		try {
			LayoutServiceUtil.deleteLayout(pk);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutModel getLayout(
		com.liferay.portal.service.persistence.LayoutPK pk)
		throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.getLayout(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutModel updateLayout(
		com.liferay.portal.service.persistence.LayoutPK pk,
		java.lang.String name, java.lang.String typeSettings,
		java.lang.String friendlyURL) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateLayout(pk,
					name, typeSettings, friendlyURL);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutModel updateLayout(
		com.liferay.portal.service.persistence.LayoutPK pk,
		java.lang.String typeSettings) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateLayout(pk,
					typeSettings);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWrite(
		com.liferay.portal.service.persistence.LayoutPK pk)
		throws RemoteException {
		try {
			boolean returnValue = LayoutServiceUtil.hasWrite(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}