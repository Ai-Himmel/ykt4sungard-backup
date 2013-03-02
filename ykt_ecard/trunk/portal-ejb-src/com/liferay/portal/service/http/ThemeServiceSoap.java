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

import com.liferay.portal.service.spring.ThemeServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ThemeServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ThemeServiceSoap {
	public static com.liferay.portal.model.Theme getTheme(
		java.lang.String themeId) throws RemoteException {
		try {
			com.liferay.portal.model.Theme returnValue = ThemeServiceUtil.getTheme(themeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.util.List getThemes() throws RemoteException {
		try {
			java.util.List returnValue = ThemeServiceUtil.getThemes();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.util.List init(java.lang.String[] xmls)
		throws RemoteException {
		try {
			java.util.List returnValue = ThemeServiceUtil.init(xmls);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.util.List init(java.lang.String servletContextName,
		java.lang.String[] xmls) throws RemoteException {
		try {
			java.util.List returnValue = ThemeServiceUtil.init(servletContextName,
					xmls);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void uninstallTheme(java.lang.String themeId)
		throws RemoteException {
		try {
			ThemeServiceUtil.uninstallTheme(themeId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}