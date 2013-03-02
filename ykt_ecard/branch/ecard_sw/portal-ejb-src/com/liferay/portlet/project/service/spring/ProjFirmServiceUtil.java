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

package com.liferay.portlet.project.service.spring;

/**
 * <a href="ProjFirmServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjFirmServiceUtil {
	public static com.liferay.portlet.project.model.ProjFirm addFirm(
		java.lang.String name, java.lang.String description,
		java.lang.String url)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.addFirm(name, description, url);
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

	public static void addNote(java.lang.String firmId,
		java.lang.String noteContent)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();
			projFirmService.addNote(firmId, noteContent);
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

	public static void deleteFirm(java.lang.String firmId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();
			projFirmService.deleteFirm(firmId);
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

	public static void deleteNote(java.lang.String firmId,
		java.lang.String noteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();
			projFirmService.deleteNote(firmId, noteId);
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

	public static com.liferay.portlet.project.model.ProjFirm getFirm(
		java.lang.String firmId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.getFirm(firmId);
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

	public static java.util.List getFirms()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.getFirms();
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

	public static java.util.List getNotes(java.lang.String firmId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.getNotes(firmId);
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

	public static com.liferay.portlet.project.model.ProjFirm updateFirm(
		java.lang.String firmId, java.lang.String name,
		java.lang.String description, java.lang.String url)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.updateFirm(firmId, name, description, url);
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

	public static boolean hasAdmin()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.hasAdmin();
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

	public static boolean hasAdmin(java.lang.String firmId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjFirmService projFirmService = ProjFirmServiceFactory.getService();

			return projFirmService.hasAdmin(firmId);
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