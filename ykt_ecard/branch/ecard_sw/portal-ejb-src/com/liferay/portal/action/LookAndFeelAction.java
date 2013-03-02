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

package com.liferay.portal.action;

import com.liferay.portal.model.Group;
import com.liferay.portal.service.spring.GroupServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.CachePortlet;
import com.liferay.util.ParamUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="LookAndFeelAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Javier Bermejo
 * @version $Revision: 1.18 $
 *
 */
public class LookAndFeelAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) && (cmd.equals(Constants.UPDATE))) {
			try {
				_updateLookAndFeel(req);

				return mapping.findForward(Constants.COMMON_REFERER);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else {
			return mapping.findForward("portal.look_and_feel");
		}
	}

	private void _updateLookAndFeel(HttpServletRequest req) throws Exception {
		HttpSession ses = req.getSession();

		String themeId = ParamUtil.getString(req, "theme_id");
		String colorSchemeId = ParamUtil.getString(req, "color_scheme_id");

		Group group = (Group)req.getAttribute(WebKeys.GROUP);

		if (group == null) {
			UserServiceUtil.updateLookAndFeel(themeId, colorSchemeId);
		}
		else {
			GroupServiceUtil.updateLookAndFeel(
				group.getGroupId(), themeId, colorSchemeId);
		}

		CachePortlet.clearResponses(ses);
	}

}