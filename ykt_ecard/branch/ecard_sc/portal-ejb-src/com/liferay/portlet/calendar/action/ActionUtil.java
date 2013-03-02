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

package com.liferay.portlet.calendar.action;

import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.calendar.NoSuchEventException;
import com.liferay.portlet.calendar.NoSuchTaskException;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.model.CalTask;
import com.liferay.portlet.calendar.service.spring.CalEventServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalTaskServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class ActionUtil {

	public static void getEvent(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getEvent(httpReq);
	}

	public static void getEvent(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getEvent(httpReq);
	}

	public static void getEvent(HttpServletRequest req) throws Exception {
		String eventId = ParamUtil.getString(req, "event_id");

		CalEvent event = null;

		if (Validator.isNotNull(eventId)) {
			try {
				event = CalEventServiceUtil.getEvent(eventId);
			}
			catch (NoSuchEventException nsee) {
			}
		}

		req.setAttribute(WebKeys.CALENDAR_EVENT, event);
	}

	public static void getTask(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getTask(httpReq);
	}

	public static void getTask(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getTask(httpReq);
	}

	public static void getTask(HttpServletRequest req) throws Exception {
		String taskId = ParamUtil.getString(req, "task_id");

		CalTask task = null;

		if (Validator.isNotNull(taskId)) {
			try {
				task = CalTaskServiceUtil.getTask(taskId);
			}
			catch (NoSuchTaskException nste) {
			}
		}

		req.setAttribute(WebKeys.CALENDAR_TASK, task);
	}

}