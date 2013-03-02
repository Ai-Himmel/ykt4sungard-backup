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

package com.liferay.portlet.addressbook.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.addressbook.ContactEmailAddressException;
import com.liferay.portlet.addressbook.ContactFirstNameException;
import com.liferay.portlet.addressbook.ContactLastNameException;
import com.liferay.portlet.addressbook.DuplicateContactException;
import com.liferay.portlet.addressbook.service.spring.ABContactServiceUtil;
import com.liferay.portlet.addressbook.util.ABUtil;
import com.liferay.portlet.addressbook.util.Importer;
import com.liferay.portlet.addressbook.util.OutlookImporter;
import com.liferay.util.FileUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadException;
import com.liferay.util.servlet.UploadPortletRequest;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ImportAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class ImportAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) && (cmd.equals(Constants.ADD))) {
			try {
				_import(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof ContactEmailAddressException ||
					e instanceof ContactFirstNameException ||
					e instanceof ContactLastNameException ||
					e instanceof DuplicateContactException ||
					e instanceof UploadException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.address_book.import_export");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.address_book.import_export");
		}
	}

	private void _import(ActionRequest req, ActionResponse res)
		throws Exception {

		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		String importerType = ParamUtil.get(
			uploadReq, "importer_type", ABUtil.IE_OUTLOOK);

		byte[] bytes = FileUtil.getBytes(uploadReq.getFile("import_file"));

		if (bytes == null || bytes.length == 0) {
			throw new UploadException();
		}

		Importer importer = null;

		if (importerType.equals(ABUtil.IE_OUTLOOK)) {
			importer = new OutlookImporter();
		}
		else if (importerType.equals(ABUtil.IE_YAHOO)) {
			importer = new OutlookImporter();
		}

		if (importer != null) {
			importer.setData(bytes);

			ABContactServiceUtil.addContacts(importer);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}