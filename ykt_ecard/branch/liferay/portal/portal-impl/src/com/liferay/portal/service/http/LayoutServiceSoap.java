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

package com.liferay.portal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.service.LayoutServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="LayoutServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portal.service.LayoutServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portal.model.LayoutSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.Layout</code>,
 * that is translated to a <code>com.liferay.portal.model.LayoutSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.LayoutServiceUtil
 * @see com.liferay.portal.service.http.LayoutServiceHttp
 * @see com.liferay.portal.service.model.LayoutSoap
 *
 */
public class LayoutServiceSoap {
	public static com.liferay.portal.model.LayoutSoap addLayout(long groupId,
		boolean privateLayout, long parentLayoutId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String type, boolean hidden, java.lang.String friendlyURL)
		throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.addLayout(groupId,
					privateLayout, parentLayoutId, name, title, description,
					type, hidden, friendlyURL);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteLayout(long plid) throws RemoteException {
		try {
			LayoutServiceUtil.deleteLayout(plid);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteLayout(long groupId, boolean privateLayout,
		long layoutId) throws RemoteException {
		try {
			LayoutServiceUtil.deleteLayout(groupId, privateLayout, layoutId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getLayoutName(long groupId,
		boolean privateLayout, long layoutId, java.lang.String languageId)
		throws RemoteException {
		try {
			java.lang.String returnValue = LayoutServiceUtil.getLayoutName(groupId,
					privateLayout, layoutId, languageId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutReference[] getLayoutReferences(
		long companyId, java.lang.String portletId, java.lang.String prefsKey,
		java.lang.String prefsValue) throws RemoteException {
		try {
			com.liferay.portal.model.LayoutReference[] returnValue = LayoutServiceUtil.getLayoutReferences(companyId,
					portletId, prefsKey, prefsValue);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void setLayouts(long groupId, boolean privateLayout,
		long parentLayoutId, long[] layoutIds) throws RemoteException {
		try {
			LayoutServiceUtil.setLayouts(groupId, privateLayout,
				parentLayoutId, layoutIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updateLayout(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String typeSettings) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateLayout(groupId,
					privateLayout, layoutId, typeSettings);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updateLookAndFeel(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String themeId, java.lang.String colorSchemeId,
		java.lang.String css, boolean wapTheme) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateLookAndFeel(groupId,
					privateLayout, layoutId, themeId, colorSchemeId, css,
					wapTheme);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updateName(long plid,
		java.lang.String name, java.lang.String languageId)
		throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateName(plid,
					name, languageId);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updateName(long groupId,
		boolean privateLayout, long layoutId, java.lang.String name,
		java.lang.String languageId) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateName(groupId,
					privateLayout, layoutId, name, languageId);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updateParentLayoutId(
		long plid, long parentPlid) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateParentLayoutId(plid,
					parentPlid);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updateParentLayoutId(
		long groupId, boolean privateLayout, long layoutId, long parentLayoutId)
		throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updateParentLayoutId(groupId,
					privateLayout, layoutId, parentLayoutId);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updatePriority(
		long plid, int priority) throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updatePriority(plid,
					priority);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.LayoutSoap updatePriority(
		long groupId, boolean privateLayout, long layoutId, int priority)
		throws RemoteException {
		try {
			com.liferay.portal.model.Layout returnValue = LayoutServiceUtil.updatePriority(groupId,
					privateLayout, layoutId, priority);

			return com.liferay.portal.model.LayoutSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(LayoutServiceSoap.class);
}