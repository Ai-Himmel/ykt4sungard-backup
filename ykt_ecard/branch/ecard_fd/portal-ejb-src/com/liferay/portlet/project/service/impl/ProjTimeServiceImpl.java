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

package com.liferay.portlet.project.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.project.TimeDateException;
import com.liferay.portlet.project.TimeEndDateException;
import com.liferay.portlet.project.TimeStartDateException;
import com.liferay.portlet.project.model.ProjTask;
import com.liferay.portlet.project.model.ProjTime;
import com.liferay.portlet.project.service.persistence.ProjTaskUtil;
import com.liferay.portlet.project.service.persistence.ProjTimeUtil;
import com.liferay.portlet.project.service.spring.ProjTimeService;

import java.util.Date;
import java.util.List;

/**
 * <a href="ProjTimeServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.2 $
 *
 */
public class ProjTimeServiceImpl
	extends PrincipalBean implements ProjTimeService {

	// Business methods

	public ProjTime addTime(
			String taskId, String description, int startMonth, int startDay,
			int startYear, int startHour, int startMin, int endMonth,
			int endDay, int endYear, int endHour, int endMin)
		throws PortalException, SystemException {

		User user = getUser();

		String timeId = Long.toString(CounterServiceUtil.increment(
			ProjTime.class.getName()));

		ProjTime time = ProjTimeUtil.create(timeId);

		Date now = new Date();

		ProjTask task = ProjTaskUtil.findByPrimaryKey(taskId);

		Date startDate = PortalUtil.getDate(
			startYear, startMonth, startDay, startHour, startMin,
			new TimeStartDateException());

		Date endDate = PortalUtil.getDate(
			endYear, endMonth, endDay, endHour, endMin,
			new TimeEndDateException());

		if (startDate.after(endDate)) {
			throw new TimeDateException();
		}

		time.setCompanyId(user.getCompanyId());
		time.setUserId(user.getUserId());
		time.setCreateDate(now);
		time.setModifiedDate(now);
		time.setProjectId(task.getProjectId());
		time.setTaskId(taskId);
		time.setDescription(description);
		time.setStartDate(startDate);
		time.setEndDate(endDate);

		ProjTimeUtil.update(time);

		return time;
	}

	public void deleteTime(String timeId)
		throws PortalException, SystemException {

		ProjTime time = ProjTimeUtil.findByPrimaryKey(timeId);

		if (!time.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		ProjTimeUtil.remove(timeId);
	}

	public List getTimesByCompany(String companyId) throws SystemException {
		return ProjTimeUtil.findByCompanyId(companyId);
	}

	public List getTimesByUser(String userId) throws SystemException {
		return ProjTimeUtil.findByUserId(userId);
	}

	public ProjTime getTime(String timeId)
		throws PortalException, SystemException {

		return ProjTimeUtil.findByPrimaryKey(timeId);
	}

	public ProjTime updateTime(
			String timeId, String description, int startMonth, int startDay,
			int startYear, int startHour, int startMin, int endMonth,
			int endDay, int endYear, int endHour, int endMin)
		throws PortalException, SystemException {

		User user = getUser();

		ProjTime time = ProjTimeUtil.findByPrimaryKey(timeId);

		Date now = new Date();

		Date startDate = PortalUtil.getDate(
			startYear, startMonth, startDay, startHour, startMin,
			new TimeStartDateException());

		Date endDate = PortalUtil.getDate(
			endYear, endMonth, endDay, endHour, endMin,
			new TimeEndDateException());

		if (startDate.after(endDate)) {
			throw new TimeDateException();
		}

		time.setModifiedDate(new Date());
		time.setDescription(description);
		time.setStartDate(startDate);
		time.setEndDate(endDate);

		ProjTimeUtil.update(time);

		return time;
	}

}