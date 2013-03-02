/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.kingstargroup.ecard.events;

import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.events.LoginPostAction;
import com.liferay.portal.kernel.events.Action;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.LastPath;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;

/**
 * <a href="DefaultLandingPageAction.java.html"><b><i>View Source</i></b></a>
 * 
 * @author Michael Young
 * 
 */
public class PersonnelLandingPageAction extends Action {

	public void run(HttpServletRequest req, HttpServletResponse res)
			throws ActionException {
		String path = PropsValues.DEFAULT_LANDING_PAGE_PATH;
		User user;
		try {
			user = PortalUtil.getUser(req);
			if (user != null) {
				path = "/web/" + user.getScreenName() + "/1";
			}
		} catch (PortalException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SystemException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		if (_log.isInfoEnabled()) {
			_log.info(PropsUtil.DEFAULT_LANDING_PAGE_PATH + StringPool.EQUAL
					+ path);
		}

		if (Validator.isNotNull(path)) {
			LastPath lastPath = new LastPath(StringPool.BLANK, path,
					new HashMap());

			HttpSession ses = req.getSession();

			ses.setAttribute(WebKeys.LAST_PATH, lastPath);
		}

		// The commented code shows how you can programmaticaly set the user's
		// landing page. You can modify this class to utilize a custom alogrithm
		// for forwarding a user to his landing page. See the references to this
		// class in portal.properties.

		/*
		 * Map params = new HashMap();
		 * 
		 * params.put("p_l_id", new String[] {"PRI.1.1"});
		 * 
		 * LastPath lastPath = new LastPath("/c", "/portal/layout", params);
		 * 
		 * ses.setAttribute(WebKeys.LAST_PATH, lastPath);
		 */
	}

	private static Log _log = LogFactory.getLog(LoginPostAction.class);

}