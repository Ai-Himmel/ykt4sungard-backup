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

package com.liferay.portlet.messageboards.action;

import com.liferay.documentlibrary.FileNameException;
import com.liferay.documentlibrary.FileSizeException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.messageboards.MessageBodyException;
import com.liferay.portlet.messageboards.MessageSubjectException;
import com.liferay.portlet.messageboards.NoSuchTopicException;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.ObjectValuePair;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.util.ArrayList;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletURL;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="PostNewThreadAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class PostNewThreadAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if (Validator.isNull(cmd)) {
			setForward(req, "portlet.message_boards.post_new_thread");
		}
		else {
			try {
				_postNewThread(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTopicException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.message_boards.error");
				}
				else if (e != null &&
						 e instanceof FileNameException ||
						 e instanceof FileSizeException || 
						 e instanceof MessageBodyException ||
						 e instanceof MessageSubjectException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.message_boards.post_new_thread");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
	}

	private void _postNewThread(ActionRequest req, ActionResponse res)
		throws Exception {

		String topicId = ParamUtil.getString(req, "topic_id");
		String subject = ParamUtil.getString(req, "msg_subject");
		String body = ParamUtil.getString(req, "msg_body");
		boolean attachments = ParamUtil.get(req, "msg_attachments", false);

		List files = new ArrayList();

		if (attachments) {
			UploadPortletRequest uploadReq =
				PortalUtil.getUploadPortletRequest(req);

			for (int i = 1; i <= 5; i++) {
				File file = uploadReq.getFile("msg_file_" + i);
				String fileName = uploadReq.getFileName("msg_file_" + i);
				byte[] bytes = FileUtil.getBytes(file);

				if (bytes != null && bytes.length > 0) {
					ObjectValuePair ovp = new ObjectValuePair(fileName, bytes);

					files.add(ovp);
				}
			}
		}

		boolean anonymous = ParamUtil.get(req, "msg_anonymous", false);

		// Post new thread

		MBMessage message = MBTopicServiceUtil.postNewThread(
			topicId, subject, body, files, anonymous);

		// Send redirect

		PortletURL portletURL = ((ActionResponseImpl)res).createRenderURL();

		portletURL.setParameter(
			"struts_action", "/message_boards/view_message");
		portletURL.setParameter("topic_id", topicId);
		portletURL.setParameter("msg_id", message.getMessageId());

		res.sendRedirect(portletURL.toString());
	}

}