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

package com.liferay.portlet.myaccount.action;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.UserPortraitException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.liferay.util.servlet.UploadException;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.commons.fileupload.disk.DiskFileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.portlet.PortletFileUpload;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="UploadPortraitAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class UploadPortraitAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			_uploadPortraitAction(req, res);
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof UploadException ||
				e instanceof UserPortraitException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.my_account.change_portrait");
			}
			else if (e != null &&
					 e instanceof NoSuchUserException ||
					 e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.my_account.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
	}

	private void _testRequest(ActionRequest req) throws Exception {

		// Check if the given request is a multipart request

		boolean isMultiPartContent = PortletFileUpload.isMultipartContent(req);

		if (isMultiPartContent) {
			_log.info("The given request is a multipart request");
		}
		else {
			_log.info("The given request is NOT a multipart request");
		}

		// Check for the number of file items

		DiskFileItemFactory factory = new DiskFileItemFactory();

		PortletFileUpload upload = new PortletFileUpload(factory);

		List fileItems = upload.parseRequest(req);

		_log.info(
			"Apache commons upload was able to parse " + fileItems.size() +
				" items");

		for (int i = 0; i < fileItems.size(); i++) {
			DiskFileItem fileItem = (DiskFileItem)fileItems.get(i);

			_log.info("Item " + i + " fileItem");
		}

		// Read directly from the portlet input stream

		InputStream in = req.getPortletInputStream();

		if (in != null) {
			ByteArrayOutputStream out = new ByteArrayOutputStream();

			int c = -1;

			try {
				while ((c = in.read()) != -1) {
					out.write(c);
				}
			}
			finally {
				in.close();
			}

			byte[] bytes = out.toByteArray();

			_log.info(
				"Byte array size from the raw input stream is " + bytes.length);
		}
	}

	private void _uploadPortraitAction(ActionRequest req, ActionResponse res)
		throws Exception {

		//_testRequest(req);

		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		byte[] bytes = FileUtil.getBytes(uploadReq.getFile("file_name"));

		if (bytes == null || bytes.length == 0) {
			throw new UploadException();
		}

		User user = PortalUtil.getSelectedUser(uploadReq);

		UserServiceUtil.updatePortrait(user.getUserId(), bytes);

		// Session messages

		SessionMessages.add(
			uploadReq, UploadPortraitAction.class.getName());

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private static final Log _log =
		LogFactory.getLog(UploadPortraitAction.class);

}