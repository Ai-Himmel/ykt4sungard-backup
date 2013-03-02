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

package com.liferay.common.taglib;

import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="PageIteratorTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.13 $
 *
 */
public class PageIteratorTag extends TagSupport {

	public int doStartTag() throws JspTagException {
		int _pages = (int)Math.ceil((double)_total / _delta);

		if (_pages <= 1) {
			return EVAL_BODY_INCLUDE;
		}

		FastStringBuffer sb = new FastStringBuffer();

		sb.append("<font class=\"").append(_className).append(
			"\" size=\"").append(_fontSize).append("\">");

		if ((_curValue == 1) && (_pages > 1)) {
			sb.append("<span class=\"").append(_className).append(
				"-neg-alert\">");
			sb.append(_leftArrowImage);
			sb.append("</span>");
		}

		if ((_curValue > 1) && (_pages > 1)) {
			sb.append("<a class=\"").append(_className).append("\" href=\"");

			if (Validator.isNotNull(_url)) {
				sb.append(_url).append(_curParam).append("=").append(
					_curValue - 1).append(_urlAnchor);
			}
			else {
				sb.append("javascript: document.").append(_formName).append(
					".").append(_curParam).append(".value = '").append(
						_curValue - 1).append("'; ").append(_jsCall);
			}

			sb.append("\" target=\"").append(_target).append("\">");
			sb.append("<span class=\"").append(_className).append(
				"-neg-alert\">");
			sb.append(_leftArrowImage);
			sb.append("</span>");
			sb.append("</a>");
		}

		sb.append("&nbsp;&nbsp;&nbsp;");

		int pageStart = 1;
		int pageEnd = _maxPages;

		if (_curValue > 1) {
			pageStart = _curValue - _maxPages + 1;
			pageEnd = _curValue + _maxPages - 1;
		}

		if (pageStart < 1) {
			pageStart = 1;
		}

		int divisions = _total / _delta;
		if (_total % _delta > 0) {
			divisions++;
		}

		if (pageEnd > divisions) {
			pageEnd = divisions;
		}

		for (int i = pageStart; i <= pageEnd; i++) {
			if (_curValue == i) {
				sb.append("[ ").append(i).append(" ]");
			}
			else {
				sb.append("<a class=\"").append(_className).append(
					"\" href=\"");

				if (Validator.isNotNull(_url)) {
					sb.append(_url).append(_curParam).append("=").append(
						i).append(_urlAnchor);
				}
				else {
					sb.append("javascript: document.").append(_formName).append(
						".").append(_curParam).append(".value = '").append(
							i).append("'; ").append(_jsCall);
				}

				sb.append("\" target=\"").append(_target).append("\"><u>");
				sb.append(i);
				sb.append("</u></a>");
			}

			sb.append("&nbsp;&nbsp;&nbsp;");
		}

		if ((_curValue < _pages) && (_pages > 1)) {
			sb.append("<a class=\"").append(_className).append("\" href=\"");

			if (Validator.isNotNull(_url)) {
				sb.append(_url).append(_curParam).append("=").append(
					_curValue + 1).append(_urlAnchor);
			}
			else {
				sb.append("javascript: document.").append(_formName).append(
					".").append(_curParam).append(".value = '").append(
						_curValue + 1).append("'; ").append(_jsCall);
			}

			sb.append("\" target=\"").append(_target).append("\">");
			sb.append("<span class=\"").append(_className).append(
				"-neg-alert\">");
			sb.append(_rightArrowImage);
			sb.append("</span>");
			sb.append("</a>");
		}

		if ((_curValue == _pages) && (_pages > 1)) {
			sb.append("<span class=\"").append(_className).append(
				"-neg-alert\">");
			sb.append(_rightArrowImage);
			sb.append("</span>");
		}

		sb.append("</font><br>");

		try {
			pageContext.getOut().print(sb.toString());
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}

		return EVAL_BODY_INCLUDE;
	}

	public int doEndTag() throws JspTagException {
		try {
			pageContext.getOut().print("</a>");
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}

		return EVAL_PAGE;
	}

	public void setClassName(String className) {
		_className = className;
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

	public void setFontSize(int fontSize) {
		_fontSize = fontSize;
	}

	public void setFormName(String formName) {
		_formName = formName;
	}

	public void setJsCall(String jsCall) {
		_jsCall = jsCall;
	}

	public void setLeftArrowImage(String leftArrowImage) {
		_leftArrowImage =
			"<img border=\"0\" hspace=\"0\" src=\"" +
				leftArrowImage + "\" vspace=\"0\">";
	}

	public void setMaxPages(int maxPages) {
		_maxPages = maxPages;
	}

	public void setRightArrowImage(String rightArrowImage) {
		_rightArrowImage =
			"<img border=\"0\" hspace=\"0\" src=\"" +
				rightArrowImage + "\" vspace=\"0\">";
	}

	public void setTarget(String target) {
		_target = target;
	}

	public void setTotal(int total) {
		_total = total;
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

	private String _className;
	private String _curParam;
	private int _curValue;
	private int _delta = 10;
	private int _fontSize = 1;
	private String _formName;
	private String _jsCall;
	private String _leftArrowImage = "&#171;&#171;";
	private int _maxPages = 10;
	private String _rightArrowImage = "&#187;&#187;";
	private String _target = "_self";
	private int _total;
	private String _url;
	private String _urlAnchor;

}