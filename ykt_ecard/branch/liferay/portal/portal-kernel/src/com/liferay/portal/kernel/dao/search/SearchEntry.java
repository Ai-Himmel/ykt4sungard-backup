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

import javax.servlet.jsp.PageContext;

/**
 * <a href="SearchEntry.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class SearchEntry implements Cloneable {

	public static final String DEFAULT_ALIGN = "left";

	public static final String DEFAULT_VALIGN = "middle";

	public static final int DEFAULT_COLSPAN = 1;

	public SearchEntry() {
		this(DEFAULT_ALIGN, DEFAULT_VALIGN, DEFAULT_COLSPAN);
	}

	public SearchEntry(String align, String valign, int colspan) {
		_align = align;
		_valign = valign;
		_colspan = colspan;
	}

	public String getAlign() {
		return _align;
	}

	public void setAlign(String align) {
		_align = align;
	}

	public String getValign() {
		return _valign;
	}

	public void setValign(String valign) {
		_valign = valign;
	}

	public int getColspan() {
		return _colspan;
	}

	public void setColspan(int colspan) {
		_colspan = colspan;
	}

	public abstract void print(PageContext pageContext) throws Exception;

	private String _align;
	private String _valign;
	private int _colspan;

}