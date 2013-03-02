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

package com.liferay.portal.kernel.dao.search;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;

import javax.servlet.jsp.PageContext;

/**
 * <a href="TextSearchEntry.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TextSearchEntry extends SearchEntry {

	public TextSearchEntry(String align, String valign, String name) {
		this(align, valign, DEFAULT_COLSPAN, name, null);
	}

	public TextSearchEntry(
		String align, String valign, int colspan, String name) {

		this(align, valign, colspan, name, null);
	}

	public TextSearchEntry(
		String align, String valign, String name, String href) {

		this(align, valign, DEFAULT_COLSPAN, name, href, null, null);
	}

	public TextSearchEntry(
		String align, String valign, int colspan, String name, String href) {

		this(align, valign, colspan, name, href, null, null);
	}

	public TextSearchEntry(
		String align, String valign, String name, String href, String target,
		String title) {

		this(align, valign, DEFAULT_COLSPAN, name, href, null, null);
	}

	public TextSearchEntry(
		String align, String valign, int colspan, String name, String href,
		String target, String title) {

		super(align, valign, colspan);

		_name = name;
		_href = href;
		_target = target;
		_title = title;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getHref() {
		return _href;
	}

	public void setHref(String href) {
		_href = href;
	}

	public String getTarget() {
		return _target;
	}

	public void setTarget(String target) {
		_target = target;
	}

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		_title = title;
	}

	public void print(PageContext pageContext) throws Exception {
		if (_href == null) {
			pageContext.getOut().print(_name);
		}
		else {
			StringMaker sm = new StringMaker();

			sm.append("<a href=\"");
			sm.append(_href);
			sm.append("\"");

			if (Validator.isNotNull(_target)) {
				sm.append(" target=\"");
				sm.append(_target);
				sm.append("\"");
			}

			if (Validator.isNotNull(_title)) {
				sm.append(" title=\"");
				sm.append(_title);
				sm.append("\"");
			}

			sm.append(">");
			sm.append(_name);
			sm.append("</a>");

			pageContext.getOut().print(sm.toString());
		}
	}

	public Object clone() {
		return new TextSearchEntry(
			getAlign(), getValign(), getColspan(), getName(), getHref(),
			getTarget(), getTitle());
	}

	private String _name;
	private String _href;
	private String _target;
	private String _title;

}