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

import com.liferay.taglib.util.IncludeTag;

import javax.servlet.ServletRequest;

/**
 * <a href="InputCheckBoxTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputCheckBoxTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:input-checkbox:formName", _formName);
		req.setAttribute("liferay-ui:input-checkbox:param", _param);
		req.setAttribute(
			"liferay-ui:input-checkbox:defaultValue", _defaultValue);
		req.setAttribute("liferay-ui:input-checkbox:onClick", _onClick);
		req.setAttribute(
			"liferay-ui:input-checkbox:disabled", String.valueOf(_disabled));

		return EVAL_BODY_BUFFERED;
	}

	public void setFormName(String formName) {
		_formName = formName;
	}

	public void setParam(String param) {
		_param = param;
	}

	public void setDefaultValue(boolean defaultValue) {
		_defaultValue = Boolean.valueOf(defaultValue);
	}

	public void setOnClick(String onClick) {
		_onClick = onClick;
	}

	public void setDisabled(boolean disabled) {
		_disabled = disabled;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE =
		"/html/taglib/ui/input_checkbox/page.jsp";

	private String _formName = "fm";
	private String _param;
	private Boolean _defaultValue = Boolean.FALSE;
	private String _onClick;
	private boolean _disabled;

}