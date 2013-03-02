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

import java.util.List;

import javax.servlet.ServletRequest;

/**
 * <a href="InputMoveBoxesTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputMoveBoxesTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:input-move-boxes:formName", _formName);
		req.setAttribute("liferay-ui:input-move-boxes:leftTitle", _leftTitle);
		req.setAttribute("liferay-ui:input-move-boxes:rightTitle", _rightTitle);
		req.setAttribute(
			"liferay-ui:input-move-boxes:leftBoxName", _leftBoxName);
		req.setAttribute(
			"liferay-ui:input-move-boxes:rightBoxName", _rightBoxName);
		req.setAttribute(
			"liferay-ui:input-move-boxes:leftOnChange", _leftOnChange);
		req.setAttribute(
			"liferay-ui:input-move-boxes:rightOnChange", _rightOnChange);
		req.setAttribute(
			"liferay-ui:input-move-boxes:leftReorder", _leftReorder);
		req.setAttribute(
			"liferay-ui:input-move-boxes:rightReorder", _rightReorder);
		req.setAttribute("liferay-ui:input-move-boxes:leftList", _leftList);
		req.setAttribute("liferay-ui:input-move-boxes:rightList", _rightList);

		return EVAL_BODY_BUFFERED;
	}

	public void setFormName(String formName) {
		_formName = formName;
	}

	public void setLeftTitle(String leftTitle) {
		_leftTitle = leftTitle;
	}

	public void setRightTitle(String rightTitle) {
		_rightTitle = rightTitle;
	}

	public void setLeftBoxName(String leftBoxName) {
		_leftBoxName = leftBoxName;
	}

	public void setRightBoxName(String rightBoxName) {
		_rightBoxName = rightBoxName;
	}

	public void setLeftOnChange(String leftOnChange) {
		_leftOnChange = leftOnChange;
	}

	public void setRightOnChange(String rightOnChange) {
		_rightOnChange = rightOnChange;
	}

	public void setLeftReorder(String leftReorder) {
		_leftReorder = leftReorder;
	}

	public void setRightReorder(String rightReorder) {
		_rightReorder = rightReorder;
	}

	public void setLeftList(List leftList) {
		_leftList = leftList;
	}

	public void setRightList(List rightList) {
		_rightList = rightList;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE =
		"/html/taglib/ui/input_move_boxes/page.jsp";

	private String _formName = "fm";
	private String _leftTitle;
	private String _rightTitle;
	private String _leftBoxName;
	private String _rightBoxName;
	private String _leftOnChange;
	private String _rightOnChange;
	private String _leftReorder;
	private String _rightReorder;
	private List _leftList;
	private List _rightList;

}