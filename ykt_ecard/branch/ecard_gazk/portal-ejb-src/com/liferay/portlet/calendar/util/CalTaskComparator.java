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

package com.liferay.portlet.calendar.util;

import com.liferay.portlet.calendar.model.CalTask;

import java.io.Serializable;

import java.util.Comparator;

/**
 * <a href="CalTaskComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class CalTaskComparator implements Comparator, Serializable {

	public int compare(Object obj1, Object obj2) {
		CalTask task1 = (CalTask)obj1;
		CalTask task2 = (CalTask)obj2;

		int value = 0;

		if ((task1.isNoDueDate() == false) && (task2.isNoDueDate() == true)) {
			value = -1;
		}
		else if ((task1.isNoDueDate() == true) &&
				 (task2.isNoDueDate() == false)) {

			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			value = value * -1;

			return value;
		}

		if (task1.isNoDueDate() == false) {
			value = task1.getDueDate().compareTo(task2.getDueDate());

			if (value != 0) {
				value = value * -1;

				return value;
			}
		}

		value = task1.getTitle().compareTo(task2.getTitle());

		if (value != 0) {
			return value;
		}

		return 0;
	}

}