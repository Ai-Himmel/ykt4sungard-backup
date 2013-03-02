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
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="PageIteratorTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PageIteratorTag extends TagSupport {

	public int doStartTag() throws JspException {
		try {
			_pages = (int)Math.ceil((double)_total / _delta);

			ServletRequest req = pageContext.getRequest();

			req.setAttribute("liferay-ui:page-iterator:formName", _formName);
			req.setAttribute("liferay-ui:page-iterator:curParam", _curParam);
			req.setAttribute(
				"liferay-ui:page-iterator:curValue", String.valueOf(_curValue));
			req.setAttribute(
				"liferay-ui:page-iterator:delta", String.valueOf(_delta));
			req.setAttribute("liferay-ui:page-iterator:jsCall", _jsCall);
			req.setAttribute(
				"liferay-ui:page-iterator:maxPages", String.valueOf(_maxPages));
			req.setAttribute("liferay-ui:page-iterator:target", _target);
			req.setAttribute(
				"liferay-ui:page-iterator:total", String.valueOf(_total));
			req.setAttribute("liferay-ui:page-iterator:url", _url);
			req.setAttribute("liferay-ui:page-iterator:urlAnchor", _urlAnchor);
			req.setAttribute(
				"liferay-ui:page-iterator:pages", String.valueOf(_pages));
			req.setAttribute("liferay-ui:page-iterator:type", _type);

			PortalIncludeUtil.include(pageContext, getStartPage());

			return EVAL_BODY_INCLUDE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public int doEndTag() throws JspException {
		try {
			if (_pages > 1) {
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

	public void setFormName(String formName) {
		_formName = formName;
	}

	public void setCurParam(String curParam) {
		_curParam = curParam;
	}

	public void setCurValue(int curValue) {
		_curValue = curValue;
	}

	public void setDelta(int delta) {
		_delta = delta;
	}

	public void setJsCall(String jsCall) {
		_jsCall = jsCall;
	}

	public void setMaxPages(int maxPages) {
		_maxPages = maxPages;
	}

	public void setTarget(String target) {
		_target = target;
	}

	public void setTotal(int total) {
		_total = total;
	}

	public void setType(String type) {
		_type = type;
	}

	public void setUrl(String url) {
		_url = url;
		_urlAnchor = StringPool.BLANK;

		int pos = _url.indexOf("#");

		if (pos != -1) {
			_url = url.substring(0, pos);
			_urlAnchor = url.substring(pos, url.length());
		}

		if (_url.indexOf("?") == -1) {
			_url += "?";
		}
		else if (!_url.endsWith("&")) {
			_url += "&";
		}
	}

	private static final String _START_PAGE =
		"/html/taglib/ui/page_iterator/start.jsp";

	private static final String _END_PAGE =
		"/html/taglib/ui/page_iterator/end.jsp";

	private String _startPage;
	private String _endPage;
	private String _formName = "fm";
	private String _curParam;
	private int _curValue;
	private int _delta = 10;
	private String _jsCall;
	private int _maxPages = 10;
	private String _target = "_self";
	private int _total;
	private String _type = "regular";
	private String _url;
	private String _urlAnchor;
	private int _pages;

}