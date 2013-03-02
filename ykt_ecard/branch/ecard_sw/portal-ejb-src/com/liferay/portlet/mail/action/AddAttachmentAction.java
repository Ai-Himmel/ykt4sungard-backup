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

package com.liferay.portlet.mail.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.FileUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.StringTokenizer;

import javax.activation.DataHandler;

import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.Multipart;
import javax.mail.Part;
import javax.mail.internet.MimeBodyPart;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletSession;

import javax.servlet.jsp.PageContext;

import org.apache.commons.mail.ByteArrayDataSource;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="AddAttachmentAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class AddAttachmentAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			PortletSession ses = req.getPortletSession();

			UploadPortletRequest uploadReq =
				PortalUtil.getUploadPortletRequest(req);

			Message msg = (Message)ses.getAttribute(
				WebKeys.MAIL_MESSAGE, PortletSession.APPLICATION_SCOPE);
			Multipart multipart = (Multipart)msg.getContent();

			String list = uploadReq.getParameter("attachments_list");

			List temp = new ArrayList();

			if (Validator.isNotNull(list)) {
				StringTokenizer st =
					new StringTokenizer(list, StringPool.COMMA);

				while (st.hasMoreTokens()) {
					String partId = st.nextToken();

					try {
						BodyPart bp =
							multipart.getBodyPart(Integer.parseInt(partId));

						if (bp != null) {
							temp.add(bp);
						}
					}
					catch (NumberFormatException nfe) {
					}
				}
			}

			// Remove all old parts

			while (multipart.getCount() > 1) {
				multipart.removeBodyPart(1);
			}

			// Add selected parts in correct order

			for (int i = 0; i < temp.size(); i++) {
				multipart.addBodyPart((BodyPart)temp.get(i));
			}

			Enumeration enu = uploadReq.getParameterNames();

			while (enu.hasMoreElements()) {
				String fileParamName = (String)enu.nextElement();

				File file = uploadReq.getFile(fileParamName);
				byte[] bytes = FileUtil.getBytes(file);

				if (bytes != null && bytes.length > 0) {
					String contentType = uploadReq.getContentType(
						fileParamName);
					String fileName = uploadReq.getFileName(fileParamName);

					BodyPart part = new MimeBodyPart();
					part.setDataHandler(new DataHandler(
						new ByteArrayDataSource(bytes, contentType)));
					part.setDisposition(Part.ATTACHMENT);
					part.setFileName(fileName);

					multipart.addBodyPart(part);
				}
			}

			ActionUtil.getAttachments(req);

			// Send redirect

			res.sendRedirect(ParamUtil.getString(req, "redirect"));
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			setForward(req, Constants.COMMON_ERROR);
		}
	}

}