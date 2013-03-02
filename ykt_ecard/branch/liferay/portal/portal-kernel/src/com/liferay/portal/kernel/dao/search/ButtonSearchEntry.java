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

import javax.servlet.jsp.PageContext;

/**
 * <a href="ButtonSearchEntry.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ButtonSearchEntry extends TextSearchEntry {

	public ButtonSearchEntry(
		String align, String valign, String name, String href) {

		this(align, valign, DEFAULT_COLSPAN, name, href);
	}

	public ButtonSearchEntry(
		String align, String valign, int colspan, String name, String href) {

		super(align, valign, colspan, name, href);
	}

	public void print(PageContext pageContext) throws Exception {
		StringMaker sm = new StringMaker();

		sm.append("<input type=\"button\" ");
		sm.append("value=\"");
		sm.append(getName());
		sm.append("\" onClick=\"");
		sm.append(getHref());
		sm.append("\">");

		pageContext.getOut().print(sm.toString());
	}

	public Object clone() {
		return new ButtonSearchEntry(
			getAlign(), getValign(), getColspan(), getName(), getHref());
	}

}