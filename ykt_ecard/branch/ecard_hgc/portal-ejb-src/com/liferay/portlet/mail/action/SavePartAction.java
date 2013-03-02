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

import com.liferay.portal.util.Constants;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.Multipart;
import javax.mail.Part;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="SavePartAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class SavePartAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String folderName = req.getParameter("folder_name");
			int msgNum = Integer.parseInt(req.getParameter("msg_num"));
			int partNum = Integer.parseInt(req.getParameter("msg_part"));

			Folder folder = MailUtil.getFolder(req, folderName);
			Message msg = folder.getMessage(msgNum);

      		Part part = null;

			if (partNum < 0) {
				part = msg;
			}
			else {
				Multipart multipart = (Multipart)msg.getContent();
				part = multipart.getBodyPart(partNum);
			}

			String contentType = part.getContentType();

			if (part.isMimeType("message/rfc822")) {
				part = (Part)part.getContent();
				contentType = Constants.TEXT_HTML;
			}

			ByteArrayOutputStream out = new ByteArrayOutputStream();
			InputStream in = part.getInputStream();

			int c = in.read();

			while (c != -1) {
				out.write(c);
				c = in.read();
			}

			in.close();
			out.close();

			String fileName = part.getFileName();
			byte[] byteArray = out.toByteArray();

			ServletResponseUtil.sendFile(res, fileName, byteArray, contentType);

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}