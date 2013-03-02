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
 * <a href="DiffTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class DiffTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:diff:sourceName", _sourceName);
		req.setAttribute("liferay-ui:diff:targetName", _targetName);
		req.setAttribute("liferay-ui:diff:diffResults", _diffResults);

		return EVAL_BODY_BUFFERED;
	}

	public void setSourceName(String sourceName) {
		_sourceName = sourceName;
	}

	public void setTargetName(String targetName) {
		_targetName = targetName;
	}

	public void setDiffResults(List[] diffResults) {
		_diffResults = diffResults;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/diff/page.jsp";

	private String _sourceName;
	private String _targetName;
	private List[] _diffResults;

}