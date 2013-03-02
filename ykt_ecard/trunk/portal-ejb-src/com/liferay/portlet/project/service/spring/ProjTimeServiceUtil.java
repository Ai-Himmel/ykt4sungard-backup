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
 * <a href="ProjTimeServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTimeServiceUtil {
	public static com.liferay.portlet.project.model.ProjTime addTime(
		java.lang.String taskId, java.lang.String description, int startMonth,
		int startDay, int startYear, int startHour, int startMin, int endMonth,
		int endDay, int endYear, int endHour, int endMin)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTimeService projTimeService = ProjTimeServiceFactory.getService();

			return projTimeService.addTime(taskId, description, startMonth,
				startDay, startYear, startHour, startMin, endMonth, endDay,
				endYear, endHour, endMin);
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

	public static void deleteTime(java.lang.String timeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTimeService projTimeService = ProjTimeServiceFactory.getService();
			projTimeService.deleteTime(timeId);
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

	public static java.util.List getTimesByCompany(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			ProjTimeService projTimeService = ProjTimeServiceFactory.getService();

			return projTimeService.getTimesByCompany(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getTimesByUser(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			ProjTimeService projTimeService = ProjTimeServiceFactory.getService();

			return projTimeService.getTimesByUser(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.project.model.ProjTime getTime(
		java.lang.String timeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTimeService projTimeService = ProjTimeServiceFactory.getService();

			return projTimeService.getTime(timeId);
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

	public static com.liferay.portlet.project.model.ProjTime updateTime(
		java.lang.String timeId, java.lang.String description, int startMonth,
		int startDay, int startYear, int startHour, int startMin, int endMonth,
		int endDay, int endYear, int endHour, int endMin)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTimeService projTimeService = ProjTimeServiceFactory.getService();

			return projTimeService.updateTime(timeId, description, startMonth,
				startDay, startYear, startHour, startMin, endMonth, endDay,
				endYear, endHour, endMin);
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