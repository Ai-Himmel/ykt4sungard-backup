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

import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import javax.mail.Folder;

import javax.portlet.PortletConfig;
import javax.portlet.PortletException;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ViewFolderAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class ViewFolderAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			PortletSession ses = req.getPortletSession();

			User user = PortalUtil.getUser(req);

			if (user.hasCompanyMx()) {
				String folderName = req.getParameter("folder_name");
				Folder folder = MailUtil.getFolder(req, folderName);

				ses.setAttribute(
					WebKeys.MAIL_FOLDER, folder,
					PortletSession.APPLICATION_SCOPE);

				// Play wav if Inbox received new mail

				if (folder.getName().equals(MailUtil.MAIL_INBOX_NAME)) {
					int unreadMsgCount = folder.getUnreadMessageCount();

					if (unreadMsgCount > 0) {
						Integer msgCount = (Integer)ses.getAttribute(
							WebKeys.MAIL_UNREAD_MESSAGE_COUNT,
							PortletSession.APPLICATION_SCOPE);

						if ((msgCount == null) || (msgCount.intValue() == 0)) {
							PortletPreferences prefs = req.getPreferences();

							int newMailNotification =
								GetterUtil.getInteger(prefs.getValue(
									"new-mail-notification", StringPool.BLANK));

							if (newMailNotification != 0) {
								req.setAttribute(
									WebKeys.MAIL_GOT_MAIL, Boolean.TRUE);
							}
						}
					}

					ses.setAttribute(
						WebKeys.MAIL_UNREAD_MESSAGE_COUNT,
						new Integer(unreadMsgCount),
						PortletSession.APPLICATION_SCOPE);
				}
			}

			if (req.getWindowState().equals(WindowState.NORMAL)) {
				return mapping.findForward("portlet.mail.view");
			}
			else {
				PortletPreferences prefs = req.getPreferences();

				String forwardAddress = prefs.getValue(
					"forward-address", StringPool.BLANK);

				if ((!user.hasCompanyMx()) ||
					(Validator.isNotNull(forwardAddress))) {

					return mapping.findForward("portlet.mail.view");
				}
				else {
					return mapping.findForward("portlet.mail.view_folder");
				}
			}
		}
		catch (Exception e) {
			throw new PortletException(e);
		}
	}

}