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

import com.liferay.portal.kernel.servlet.PortalIncludeUtil;
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.BodyContent;
import javax.servlet.jsp.tagext.BodyTagSupport;

/**
 * <a href="IconMenuTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IconMenuTag extends BodyTagSupport {

	public int doStartTag() throws JspException {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:icon-menu:align", _align);
		req.setAttribute(
			"liferay-ui:icon-menu:icon-count", new IntegerWrapper());

		return EVAL_BODY_BUFFERED;
	}

	public int doAfterBody() {
		BodyContent bodyContent = getBodyContent();

		_bodyContentString = bodyContent.getString();

		ServletRequest req = pageContext.getRequest();

		IntegerWrapper iconCount = (IntegerWrapper)req.getAttribute(
			"liferay-ui:icon-menu:icon-count");

		Boolean singleIcon = (Boolean)req.getAttribute(
			"liferay-ui:icon-menu:single-icon");

		if ((iconCount != null) && (iconCount.getValue() == 1) &&
			(singleIcon == null)) {

			bodyContent.clearBody();

			req.setAttribute("liferay-ui:icon-menu:single-icon", Boolean.TRUE);

			return EVAL_BODY_AGAIN;
		}
		else {
			return SKIP_BODY;
		}
	}

	public int doEndTag() throws JspException {
		try {
			ServletRequest req = pageContext.getRequest();

			IntegerWrapper iconCount = (IntegerWrapper)req.getAttribute(
				"liferay-ui:icon-menu:icon-count");

			req.removeAttribute("liferay-ui:icon-menu:icon-count");

			Boolean singleIcon = (Boolean)req.getAttribute(
				"liferay-ui:icon-menu:single-icon");

			req.removeAttribute("liferay-ui:icon-menu:single-icon");

			if ((iconCount != null) && (iconCount.getValue() > 1) &&
				(singleIcon == null)) {

				PortalIncludeUtil.include(pageContext, getStartPage());
			}

			pageContext.getOut().print(_bodyContentString);

			if ((iconCount != null) && (iconCount.getValue() > 1) &&
				(singleIcon == null)) {

				PortalIncludeUtil.include(pageContext, getEndPage());
			}

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

	public void setAlign(String align) {
		_align = align;
	}

	private static final String _START_PAGE =
		"/html/taglib/ui/icon_menu/start.jsp";

	private static final String _END_PAGE = "/html/taglib/ui/icon_menu/end.jsp";

	private String _startPage;
	private String _endPage;
	private String _align = "right";
	private String _bodyContentString = StringPool.BLANK;

}