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

package com.liferay.portlet.project.service.http;

import com.liferay.portlet.project.service.spring.ProjFirmServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ProjFirmServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjFirmServiceSoap {
	public static com.liferay.portlet.project.model.ProjFirmModel addFirm(
		java.lang.String name, java.lang.String description,
		java.lang.String url) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjFirm returnValue = ProjFirmServiceUtil.addFirm(name,
					description, url);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void addNote(java.lang.String firmId,
		java.lang.String noteContent) throws RemoteException {
		try {
			ProjFirmServiceUtil.addNote(firmId, noteContent);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFirm(java.lang.String firmId)
		throws RemoteException {
		try {
			ProjFirmServiceUtil.deleteFirm(firmId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteNote(java.lang.String firmId,
		java.lang.String noteId) throws RemoteException {
		try {
			ProjFirmServiceUtil.deleteNote(firmId, noteId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjFirmModel getFirm(
		java.lang.String firmId) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjFirm returnValue = ProjFirmServiceUtil.getFirm(firmId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjFirmModel[] getFirms()
		throws RemoteException {
		try {
			java.util.List returnValue = ProjFirmServiceUtil.getFirms();

			return (com.liferay.portlet.project.model.ProjFirm[])returnValue.toArray(new com.liferay.portlet.project.model.ProjFirm[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjFirmModel[] getNotes(
		java.lang.String firmId) throws RemoteException {
		try {
			java.util.List returnValue = ProjFirmServiceUtil.getNotes(firmId);

			return (com.liferay.portlet.project.model.ProjFirm[])returnValue.toArray(new com.liferay.portlet.project.model.ProjFirm[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjFirmModel updateFirm(
		java.lang.String firmId, java.lang.String name,
		java.lang.String description, java.lang.String url)
		throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjFirm returnValue = ProjFirmServiceUtil.updateFirm(firmId,
					name, description, url);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin() throws RemoteException {
		try {
			boolean returnValue = ProjFirmServiceUtil.hasAdmin();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String firmId)
		throws RemoteException {
		try {
			boolean returnValue = ProjFirmServiceUtil.hasAdmin(firmId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}