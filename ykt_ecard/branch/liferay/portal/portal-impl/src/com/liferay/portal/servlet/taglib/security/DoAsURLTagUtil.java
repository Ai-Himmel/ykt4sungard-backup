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

package com.liferay.portal.servlet.taglib.security;

import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Layout;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.Encryptor;
import com.liferay.util.Http;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="DoAsURLTagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DoAsURLTagUtil extends TagSupport {

	public static String doEndTag(
			long doAsUserId, String var, boolean writeOutput,
			PageContext pageContext)
		throws JspException {

		try {
			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			Company company = themeDisplay.getCompany();
			Layout layout = themeDisplay.getLayout();

			String doAsURL = PortalUtil.getLayoutURL(
				layout, themeDisplay, false);

			if (doAsUserId <= 0) {
				doAsUserId = company.getDefaultUser().getUserId();
			}

			String encDoAsUserId = Encryptor.encrypt(
				company.getKeyObj(), String.valueOf(doAsUserId));

			doAsURL = Http.addParameter(doAsURL, "doAsUserId", encDoAsUserId);

			if (Validator.isNotNull(var)) {
				pageContext.setAttribute(var, doAsURL);
			}
			else if (writeOutput) {
				pageContext.getOut().print(doAsURL);
			}

			return doAsURL;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

}