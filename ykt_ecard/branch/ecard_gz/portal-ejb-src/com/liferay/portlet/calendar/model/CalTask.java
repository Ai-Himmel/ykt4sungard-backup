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

package com.liferay.portlet.calendar.model;

import java.util.Date;

/**
 * <a href="CalTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class CalTask extends CalTaskModel {

	public static final String[] STATUSES = {
		"new", "in-progress", "completed"
	};

	public static final int STATUS_ANY = -1;

	public static final int STATUS_NEW = 0;

	public static final int STATUS_IN_PROGRESS = 1;

	public static final int STATUS_COMPLETED = 2;

	public static final int[] PRIORITIES = {
		1, 2, 3, 4, 5
	};

	public static final int PRIORITY_ANY = -1;

	public CalTask() {
		super();
	}

	public CalTask(String taskId) {
		super(taskId);
	}

	public CalTask(String taskId, String companyId, String userId,
				   Date createDate, Date modifiedDate, String title,
				   String description, boolean noDueDate, Date dueDate,
				   int priority, int status) {

		super(taskId, companyId, userId, createDate, modifiedDate, title,
			  description, noDueDate, dueDate, priority, status);
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		CalTask calTask = (CalTask)obj;

		int value = 0;

		if (getStatus() < calTask.getStatus()) {
			value = -1;
		}
		else if (getStatus() > calTask.getStatus()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (getPriority() < calTask.getPriority()) {
			value = -1;
		}
		else if (getPriority() > calTask.getPriority()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if ((isNoDueDate() == false) && (calTask.isNoDueDate() == true)) {
			value = -1;
		}
		else if ((isNoDueDate() == true) && (calTask.isNoDueDate() == false)) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (isNoDueDate() == false) {
			value = getDueDate().compareTo(calTask.getDueDate());

			if (value != 0) {
				return value;
			}
		}

		value = getTitle().compareTo(calTask.getTitle());

		if (value != 0) {
			return value;
		}

		return 0;
	}

}