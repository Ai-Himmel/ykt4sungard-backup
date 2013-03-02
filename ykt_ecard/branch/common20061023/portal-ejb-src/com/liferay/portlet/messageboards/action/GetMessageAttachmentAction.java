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

import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBTopic;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePK;
import com.liferay.portlet.messageboards.service.spring.MBMessageServiceUtil;
import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="GetMessageAttachmentAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class GetMessageAttachmentAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			String topicId = ParamUtil.getString(req, "topic_id");
			String messageId = ParamUtil.getString(req, "msg_id");
			String fileName = ParamUtil.getString(req, "msg_attachment");

			// Find topic

			MBTopic topic = MBTopicServiceUtil.getTopic(topicId);

			// Find message

			MBMessage message = MBMessageServiceUtil.getMessage(
				new MBMessagePK(messageId, topic.getTopicId()));

			// Get message attachment

			byte[] byteArray = DLServiceUtil.getFile(
				message.getCompanyId(), Company.SYSTEM,
				message.getAttachmentsDir() + "/" + fileName);

			// Write to HTTP output stream

			HttpServletResponse httpRes =
				((ActionResponseImpl)res).getHttpServletResponse();

			ServletResponseUtil.sendFile(httpRes, fileName, byteArray);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}