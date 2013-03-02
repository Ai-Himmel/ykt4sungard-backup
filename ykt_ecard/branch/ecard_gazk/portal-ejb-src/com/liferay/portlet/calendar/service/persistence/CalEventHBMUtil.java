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

package com.liferay.portlet.calendar.service.persistence;

/**
 * <a href="CalEventHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventHBMUtil {
	public static com.liferay.portlet.calendar.model.CalEvent model(
		CalEventHBM calEventHBM) {
		com.liferay.portlet.calendar.model.CalEvent calEvent = CalEventPool.get(calEventHBM.getPrimaryKey());

		if (calEvent == null) {
			calEvent = new com.liferay.portlet.calendar.model.CalEvent(calEventHBM.getEventId(),
					calEventHBM.getGroupId(), calEventHBM.getCompanyId(),
					calEventHBM.getUserId(), calEventHBM.getUserName(),
					calEventHBM.getCreateDate(), calEventHBM.getModifiedDate(),
					calEventHBM.getTitle(), calEventHBM.getDescription(),
					calEventHBM.getStartDate(), calEventHBM.getEndDate(),
					calEventHBM.getDurationHour(),
					calEventHBM.getDurationMinute(), calEventHBM.getAllDay(),
					calEventHBM.getTimeZoneSensitive(), calEventHBM.getType(),
					calEventHBM.getLocation(), calEventHBM.getStreet(),
					calEventHBM.getCity(), calEventHBM.getState(),
					calEventHBM.getZip(), calEventHBM.getPhone(),
					calEventHBM.getRepeating(), calEventHBM.getRecurrence(),
					calEventHBM.getRemindBy(), calEventHBM.getFirstReminder(),
					calEventHBM.getSecondReminder());
			CalEventPool.put(calEvent.getPrimaryKey(), calEvent);
		}

		return calEvent;
	}
}