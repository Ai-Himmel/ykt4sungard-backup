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

package com.liferay.portlet.calendar.model;

import com.liferay.portal.model.BaseModel;

import java.util.Date;

/**
 * <a href="CalEventModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>CalEvent</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.calendar.service.model.CalEvent
 * @see com.liferay.portlet.calendar.service.model.impl.CalEventImpl
 * @see com.liferay.portlet.calendar.service.model.impl.CalEventModelImpl
 *
 */
public interface CalEventModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public String getUuid();

	public void setUuid(String uuid);

	public long getEventId();

	public void setEventId(long eventId);

	public long getGroupId();

	public void setGroupId(long groupId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public long getUserId();

	public void setUserId(long userId);

	public String getUserName();

	public void setUserName(String userName);

	public Date getCreateDate();

	public void setCreateDate(Date createDate);

	public Date getModifiedDate();

	public void setModifiedDate(Date modifiedDate);

	public String getTitle();

	public void setTitle(String title);

	public String getDescription();

	public void setDescription(String description);

	public Date getStartDate();

	public void setStartDate(Date startDate);

	public Date getEndDate();

	public void setEndDate(Date endDate);

	public int getDurationHour();

	public void setDurationHour(int durationHour);

	public int getDurationMinute();

	public void setDurationMinute(int durationMinute);

	public boolean getAllDay();

	public boolean isAllDay();

	public void setAllDay(boolean allDay);

	public boolean getTimeZoneSensitive();

	public boolean isTimeZoneSensitive();

	public void setTimeZoneSensitive(boolean timeZoneSensitive);

	public String getType();

	public void setType(String type);

	public boolean getRepeating();

	public boolean isRepeating();

	public void setRepeating(boolean repeating);

	public String getRecurrence();

	public void setRecurrence(String recurrence);

	public String getRemindBy();

	public void setRemindBy(String remindBy);

	public int getFirstReminder();

	public void setFirstReminder(int firstReminder);

	public int getSecondReminder();

	public void setSecondReminder(int secondReminder);

	public CalEvent toEscapedModel();
}