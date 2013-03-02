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

import com.liferay.portlet.project.service.spring.ProjTimeServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ProjTimeServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTimeServiceSoap {
	public static com.liferay.portlet.project.model.ProjTimeModel addTime(
		java.lang.String taskId, java.lang.String description, int startMonth,
		int startDay, int startYear, int startHour, int startMin, int endMonth,
		int endDay, int endYear, int endHour, int endMin)
		throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjTime returnValue = ProjTimeServiceUtil.addTime(taskId,
					description, startMonth, startDay, startYear, startHour,
					startMin, endMonth, endDay, endYear, endHour, endMin);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteTime(java.lang.String timeId)
		throws RemoteException {
		try {
			ProjTimeServiceUtil.deleteTime(timeId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTimeModel[] getTimesByCompany(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = ProjTimeServiceUtil.getTimesByCompany(companyId);

			return (com.liferay.portlet.project.model.ProjTime[])returnValue.toArray(new com.liferay.portlet.project.model.ProjTime[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTimeModel[] getTimesByUser(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = ProjTimeServiceUtil.getTimesByUser(userId);

			return (com.liferay.portlet.project.model.ProjTime[])returnValue.toArray(new com.liferay.portlet.project.model.ProjTime[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTimeModel getTime(
		java.lang.String timeId) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjTime returnValue = ProjTimeServiceUtil.getTime(timeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTimeModel updateTime(
		java.lang.String timeId, java.lang.String description, int startMonth,
		int startDay, int startYear, int startHour, int startMin, int endMonth,
		int endDay, int endYear, int endHour, int endMin)
		throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjTime returnValue = ProjTimeServiceUtil.updateTime(timeId,
					description, startMonth, startDay, startYear, startHour,
					startMin, endMonth, endDay, endYear, endHour, endMin);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}