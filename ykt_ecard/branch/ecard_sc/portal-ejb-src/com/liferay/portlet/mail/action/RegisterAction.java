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

import com.liferay.portal.DuplicateUserEmailAddressException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="RegisterAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class RegisterAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			String userName = ParamUtil.getString(req, "user_name");

			User user = PortalUtil.getUser(req);

			String emailAddress = userName + "@" + user.getCompanyMx();

			PortalUtil.updateUser(
				req, res, user.getUserId(), user.getFirstName(),
				user.getMiddleName(), user.getLastName(), user.getNickName(),
				user.isMale(), user.getBirthday(), emailAddress,
				user.getSmsId(), user.getAimId(), user.getIcqId(),
				user.getMsnId(), user.getYmId(), user.getFavoriteActivity(),
				user.getFavoriteBibleVerse(), user.getFavoriteFood(),
				user.getFavoriteMovie(), user.getFavoriteMusic(),
				user.getLanguageId(), user.getTimeZoneId(), user.getThemeId(),
				user.getColorSchemeId(), user.getGreeting(),
				user.getResolution(), user.getComments());

			// Session messages

			SessionMessages.add(req, RegisterAction.class.getName());

			setForward(req, "portlet.mail.register");
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof DuplicateUserEmailAddressException ||
				e instanceof UserEmailAddressException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.mail.register");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
	}

}