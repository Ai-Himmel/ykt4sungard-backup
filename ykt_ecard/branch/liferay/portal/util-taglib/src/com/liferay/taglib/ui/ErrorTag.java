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
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.Html;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.RenderRequest;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="ErrorTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ErrorTag extends TagSupport {

	public int doStartTag() throws JspException {
		try {
			ServletRequest req = pageContext.getRequest();

			RenderRequest renderRequest = (RenderRequest)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_REQUEST);

			req.setAttribute("liferay-ui:error:key", _key);
			req.setAttribute("liferay-ui:error:message", _message);
			req.setAttribute(
				"liferay-ui:error:translateMessage",
				String.valueOf(_translateMessage));
			req.setAttribute("liferay-ui:error:rowBreak", _rowBreak);

			if ((_exception != null) && (Validator.isNull(_message)) &&
				(SessionErrors.contains(renderRequest, _exception.getName()))) {

				PortalIncludeUtil.include(pageContext, getStartPage());

				pageContext.setAttribute(
					"errorException",
					SessionErrors.get(renderRequest, _exception.getName()));

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
			ServletRequest req = pageContext.getRequest();

			RenderRequest renderRequest = (RenderRequest)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_REQUEST);

			boolean includeEndPage = false;

			if (_key == null) {
				if (!SessionErrors.isEmpty(renderRequest)) {
					includeEndPage = true;
				}
			}
			else {
				if (SessionErrors.contains(renderRequest, _key)) {
					includeEndPage = true;
				}
			}

			if (includeEndPage) {
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

	public void setException(Class exception) {
		_exception = exception;

		if (_exception != null) {
			_key = _exception.getName();
		}
	}

	public void setKey(String key) {
		_key = key;
	}

	public void setMessage(String message) {
		_message = message;
	}

	public void setTranslateMessage(boolean translateMessage) {
		_translateMessage = translateMessage;
	}

	public void setRowBreak(String rowBreak) {
		_rowBreak = Html.unescape(rowBreak);
	}

	private static final String _START_PAGE = "/html/taglib/ui/error/start.jsp";

	private static final String _END_PAGE = "/html/taglib/ui/error/end.jsp";

	private String _startPage;
	private String _endPage;
	private Class _exception;
	private String _key;
	private String _message;
	private boolean _translateMessage = true;
	private String _rowBreak = StringPool.BLANK;

}