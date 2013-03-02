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

package com.liferay.portlet.tasks;

import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.JSPPortlet;
import com.liferay.portlet.calendar.model.CalTask;
import com.liferay.portlet.calendar.service.spring.CalTaskServiceUtil;

import java.io.IOException;

import java.util.Collections;
import java.util.List;

import javax.portlet.PortletException;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="TasksPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class TasksPortlet extends JSPPortlet {

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		try {
			List taskList = CalTaskServiceUtil.getTasks(
				CalTask.PRIORITY_ANY, CalTask.STATUS_NEW);

			taskList.addAll(CalTaskServiceUtil.getTasks(
				CalTask.PRIORITY_ANY, CalTask.STATUS_IN_PROGRESS));

			Collections.sort(taskList);

			req.setAttribute(WebKeys.TASK_LIST, taskList);
		}
		catch (Exception e) {
			throw new PortletException(e);
		}

		super.doView(req, res);
	}

}