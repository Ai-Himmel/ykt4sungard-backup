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

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.taglib.util.ParamAncestorTagImpl;

import javax.portlet.RenderResponse;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="SectionTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SectionTag extends ParamAncestorTagImpl {

	public int doStartTag() throws JspException {
		_tabsTag = (TabsTag)findAncestorWithClass(this, TabsTag.class);

		if (_tabsTag == null) {
			throw new JspException();
		}

		try {
			ServletRequest req = pageContext.getRequest();

			RenderResponse renderResponse = (RenderResponse)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_RESPONSE);

			String namespace = StringPool.BLANK;

			if (renderResponse != null) {
				namespace = renderResponse.getNamespace();
			}

			String sectionParam = _tabsTag.getParam();
			String sectionName = _tabsTag.getSectionName();
			_sectionSelected = Boolean.valueOf(_tabsTag.getSectionSelected());
			String sectionScroll = namespace + sectionParam + "TabsScroll";
			String sectionRedirectParams =
				"&scroll=" + sectionScroll + "&" + sectionParam + "=" +
					sectionName;

			_tabsTag.incrementSection();

			req.setAttribute("liferay-ui:section:param", sectionParam);
			req.setAttribute("liferay-ui:section:name", sectionName);
			req.setAttribute("liferay-ui:section:selected", _sectionSelected);
			req.setAttribute("liferay-ui:section:scroll", sectionScroll);

			pageContext.setAttribute("sectionSelected", _sectionSelected);
			pageContext.setAttribute("sectionParam", sectionParam);
			pageContext.setAttribute("sectionName", sectionName);
			pageContext.setAttribute("sectionScroll", sectionScroll);
			pageContext.setAttribute(
				"sectionRedirectParams", sectionRedirectParams);

			if (!_tabsTag.isRefresh() || _sectionSelected.booleanValue()) {
				if (!_tabsTag.isRefresh()) {
					include(getStartPage());
				}

				return EVAL_BODY_INCLUDE;
			}
			else {
				return EVAL_PAGE;
			}
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public int doEndTag() throws JspException {
		try {
			if (!_tabsTag.isRefresh() || _sectionSelected.booleanValue()) {
				if (!_tabsTag.isRefresh()) {
					include(getEndPage());
				}

				return EVAL_BODY_INCLUDE;
			}
			else {
				return EVAL_PAGE;
			}
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

	private static final String _START_PAGE =
		"/html/taglib/ui/section/start.jsp";

	private static final String _END_PAGE = "/html/taglib/ui/section/end.jsp";

	private String _startPage;
	private String _endPage;
	private TabsTag _tabsTag = null;
	private Boolean _sectionSelected = Boolean.FALSE;

}