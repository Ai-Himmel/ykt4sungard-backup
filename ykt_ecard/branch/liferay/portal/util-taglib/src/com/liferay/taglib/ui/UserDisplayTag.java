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

package com.liferay.taglib.ui;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.kernel.servlet.PortalIncludeUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="UserDisplayTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserDisplayTag extends TagSupport {

	public int doStartTag() throws JspException {
		try {
			ServletRequest req = pageContext.getRequest();

			req.setAttribute(
				"liferay-ui:user-display:user-id", String.valueOf(_userId));
			req.setAttribute("liferay-ui:user-display:user-name", _userName);

			User user = null;

			try {
				user = UserLocalServiceUtil.getUserById(_userId);

				req.setAttribute("liferay-ui:user-display:user", user);

				pageContext.setAttribute("userDisplay", user);
			}
			catch (NoSuchUserException usue) {
				req.removeAttribute("liferay-ui:user-display:user");

				pageContext.removeAttribute("userDisplay");
			}

			req.setAttribute("liferay-ui:user-display:url", _url);
			req.setAttribute(
				"liferay-ui:user-display:displayStyle",
				String.valueOf(_displayStyle));

			PortalIncludeUtil.include(pageContext, getStartPage());

			if (user != null) {
				return EVAL_BODY_INCLUDE;
			}
			else {
				return SKIP_BODY;
			}
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public int doEndTag() throws JspException {
		try {
			PortalIncludeUtil.include(pageContext, getEndPage());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public String getStartPage() {
		if (Validator.isNull(_startPage)) {
			return _START_PAGE;
		}
		else {
			return _startPage;
		}
	}

	public void setStartPage(String startPage) {
		_startPage = startPage;
	}

	public String getEndPage() {
		if (Validator.isNull(_endPage)) {
			return _END_PAGE;
		}
		else {
			return _endPage;
		}
	}

	public void setEndPage(String endPage) {
		_endPage = endPage;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public void setUserName(String userName) {
		_userName = userName;
	}

	public void setUrl(String url) {
		_url = url;
	}

	public void setDisplayStyle(int displayStyle) {
		_displayStyle = displayStyle;
	}

	private static final String _START_PAGE =
		"/html/taglib/ui/user_display/start.jsp";

	private static final String _END_PAGE =
		"/html/taglib/ui/user_display/end.jsp";

	private String _startPage;
	private String _endPage;
	private long _userId;
	private String _userName;
	private String _url;
	private int _displayStyle = 1;

}