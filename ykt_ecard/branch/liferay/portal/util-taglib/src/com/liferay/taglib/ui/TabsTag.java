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

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.taglib.util.ParamAncestorTagImpl;

import javax.portlet.PortletURL;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="TabsTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TabsTag extends ParamAncestorTagImpl {

	public int doStartTag() throws JspException {
		try {
			ServletRequest req = getServletRequest();

			req.setAttribute("liferay-ui:tabs:names", _names);

			if ((_tabsValues == null) || (_tabsValues.length < _names.length)) {
				_tabsValues = _names;
			}

			req.setAttribute("liferay-ui:tabs:values", _tabsValues);

			req.setAttribute("liferay-ui:tabs:formName", _formName);
			req.setAttribute("liferay-ui:tabs:param", _param);

			if (_value == null) {
				if (_tabsValues.length > 0) {
					_value = ParamUtil.getString(req, _param, _tabsValues[0]);
				}
			}

			if (Validator.isNull(_value)) {
				if (_tabsValues.length > 0) {
					_value = _tabsValues[0];
				}
				else {
					_value = StringPool.BLANK;
				}
			}

			boolean match = false;

			for (int i = 0; i < _tabsValues.length; i++) {
				if (_value.equals(_tabsValues[i])) {
					match = true;
				}
			}

			if (!match) {
				if (_tabsValues.length > 0) {
					_value = _tabsValues[0];
				}
				else {
					_value = StringPool.BLANK;
				}
			}

			req.setAttribute("liferay-ui:tabs:value", _value);
			req.setAttribute("liferay-ui:tabs:portletURL", _portletURL);
			req.setAttribute("liferay-ui:tabs:url", _url);

			if (_url0 != null) {
				req.setAttribute("liferay-ui:tabs:url0", _url0);
			}

			if (_url1 != null) {
				req.setAttribute("liferay-ui:tabs:url1", _url1);
			}

			if (_url2 != null) {
				req.setAttribute("liferay-ui:tabs:url2", _url2);
			}

			if (_url3 != null) {
				req.setAttribute("liferay-ui:tabs:url3", _url3);
			}

			if (_url4 != null) {
				req.setAttribute("liferay-ui:tabs:url4", _url4);
			}

			if (_url5 != null) {
				req.setAttribute("liferay-ui:tabs:url5", _url5);
			}

			if (_url6 != null) {
				req.setAttribute("liferay-ui:tabs:url6", _url6);
			}

			if (_url7 != null) {
				req.setAttribute("liferay-ui:tabs:url7", _url7);
			}

			if (_url8 != null) {
				req.setAttribute("liferay-ui:tabs:url8", _url8);
			}

			if (_url9 != null) {
				req.setAttribute("liferay-ui:tabs:url9", _url9);
			}

			req.setAttribute("liferay-ui:tabs:backURL", _backURL);
			req.setAttribute(
				"liferay-ui:tabs:refresh", String.valueOf(_refresh));
			req.setAttribute(
				"liferay-ui:tabs:onClick", String.valueOf(_onClick));

			include(getStartPage());

			return EVAL_BODY_INCLUDE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public int doEndTag() throws JspException {
		try {
			ServletRequest req = pageContext.getRequest();

			req.removeAttribute("liferay-ui:tabs:url0");
			req.removeAttribute("liferay-ui:tabs:url1");
			req.removeAttribute("liferay-ui:tabs:url2");
			req.removeAttribute("liferay-ui:tabs:url3");
			req.removeAttribute("liferay-ui:tabs:url4");
			req.removeAttribute("liferay-ui:tabs:url5");
			req.removeAttribute("liferay-ui:tabs:url6");
			req.removeAttribute("liferay-ui:tabs:url7");
			req.removeAttribute("liferay-ui:tabs:url8");
			req.removeAttribute("liferay-ui:tabs:url9");

			include(getEndPage());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
		finally {
			_startPage = null;
			_endPage = null;
			_names = null;
			_namesPos = 0;
			_tabsValues = null;
			_formName = StringPool.BLANK;
			_param = "tabs1";
			_value = null;
			_portletURL = null;
			_url = null;
			_url0 = null;
			_url1 = null;
			_url2 = null;
			_url3 = null;
			_url4 = null;
			_url5 = null;
			_url6 = null;
			_url7 = null;
			_url8 = null;
			_url9 = null;
			_backURL = null;
			_refresh = true;
			_onClick = null;
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

	public void setNames(String names) {
		_names = StringUtil.split(names);
	}

	public void setTabsValues(String tabsValues) {
		_tabsValues = StringUtil.split(tabsValues);
	}

	public void setFormName(String formName) {
		_formName = formName;
	}

	public String getParam() {
		return _param;
	}

	public void setParam(String param) {
		_param = param;
	}

	public void setValue(String value) {
		_value = value;
	}

	public void setPortletURL(PortletURL portletURL) {
		_portletURL = portletURL;
	}

	public void setUrl(String url) {
		_url = url;
	}

	public void setUrl0(String url0) {
		_url0 = url0;
	}

	public void setUrl1(String url1) {
		_url1 = url1;
	}

	public void setUrl2(String url2) {
		_url2 = url2;
	}

	public void setUrl3(String url3) {
		_url3 = url3;
	}

	public void setUrl4(String url4) {
		_url4 = url4;
	}

	public void setUrl5(String url5) {
		_url5 = url5;
	}

	public void setUrl6(String url6) {
		_url6 = url6;
	}

	public void setUrl7(String url7) {
		_url7 = url7;
	}

	public void setUrl8(String url8) {
		_url8 = url8;
	}

	public void setUrl9(String url9) {
		_url9 = url9;
	}

	public void setBackURL(String backURL) {
		_backURL = backURL;
	}

	public boolean isRefresh() {
		return _refresh;
	}

	public void setRefresh(boolean refresh) {
		_refresh = refresh;
	}

	public String getOnClick() {
		return _onClick;
	}

	public void setOnClick(String onClick) {
		_onClick = onClick;
	}

	public String getSectionName() {
		if (_names.length > _namesPos) {
			return _names[_namesPos];
		}
		else {
			return StringPool.BLANK;
		}
	}

	public boolean getSectionSelected() {
		if ((_names.length == 0) ||
			((_names.length > _namesPos) &&
				(_names[_namesPos].equals(_value)))) {

			return true;
		}
		else {
			return false;
		}
	}

	public void incrementSection() {
		_namesPos++;
	}

	private static final String _START_PAGE = "/html/taglib/ui/tabs/start.jsp";

	private static final String _END_PAGE = "/html/taglib/ui/tabs/end.jsp";

	private String _startPage;
	private String _endPage;
	private String[] _names;
	private int _namesPos;
	private String[] _tabsValues;
	private String _formName;
	private String _param = "tabs1";
	private String _value;
	private PortletURL _portletURL;
	private String _url;
	private String _url0;
	private String _url1;
	private String _url2;
	private String _url3;
	private String _url4;
	private String _url5;
	private String _url6;
	private String _url7;
	private String _url8;
	private String _url9;
	private String _backURL;
	private boolean _refresh = true;
	private String _onClick;

}