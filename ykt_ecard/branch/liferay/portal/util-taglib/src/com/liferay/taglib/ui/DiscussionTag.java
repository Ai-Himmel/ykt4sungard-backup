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
 * <a href="DiscussionTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class DiscussionTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:discussion:formName", _formName);
		req.setAttribute("liferay-ui:discussion:formAction", _formAction);
		req.setAttribute("liferay-ui:discussion:className", _className);
		req.setAttribute(
			"liferay-ui:discussion:classPK", String.valueOf(_classPK));
		req.setAttribute(
			"liferay-ui:discussion:userId", String.valueOf(_userId));
		req.setAttribute("liferay-ui:discussion:subject", _subject);
		req.setAttribute("liferay-ui:discussion:redirect", _redirect);

		return EVAL_BODY_BUFFERED;
	}

	public void setFormName(String formName) {
		_formName = formName;
	}

	public void setFormAction(String formAction) {
		_formAction = formAction;
	}

	public void setClassName(String className) {
		_className = className;
	}

	public void setClassPK(long classPK) {
		_classPK = classPK;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public void setSubject(String subject) {
		_subject = subject;
	}

	public void setRedirect(String redirect) {
		_redirect = redirect;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/discussion/page.jsp";

	private String _formName = "fm";
	private String _formAction;
	private String _className;
	private long _classPK;
	private long _userId;
	private String _subject;
	private String _redirect;

}