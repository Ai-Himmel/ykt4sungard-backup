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
 * <a href="InputEditorTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputEditorTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:input-editor:name", _name);
		req.setAttribute("liferay-ui:input-editor:editorImpl", _editorImpl);
		req.setAttribute("liferay-ui:input-editor:toolbarSet", _toolbarSet);
		req.setAttribute("liferay-ui:input-editor:initMethod", _initMethod);
		req.setAttribute(
			"liferay-ui:input-editor:onChangeMethod", _onChangeMethod);
		req.setAttribute("liferay-ui:input-editor:height", _height);
		req.setAttribute("liferay-ui:input-editor:width", _width);

		return EVAL_BODY_BUFFERED;
	}

	public void setName(String name) {
		_name = name;
	}

	public void setEditorImpl(String editorImpl) {
		_editorImpl = editorImpl;
	}

	public void setToolbarSet(String toolbarSet) {
		_toolbarSet = toolbarSet;
	}

	public void setInitMethod(String initMethod) {
		_initMethod = initMethod;
	}

	public void setOnChangeMethod(String onChangeMethod) {
		_onChangeMethod = onChangeMethod;
	}

	public void setHeight(String height) {
		_height = height;
	}

	public void setWidth(String width) {
		_width = width;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/input_editor/page.jsp";

	private String _name;
	private String _editorImpl;
	private String _toolbarSet;
	private String _initMethod;
	private String _onChangeMethod;
	private String _height;
	private String _width;

}