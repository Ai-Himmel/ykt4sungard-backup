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

package com.liferay.util;

/**
 * <a href="Html_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Html_IW {
	public static Html_IW getInstance() {
		return _instance;
	}

	public java.lang.String escape(java.lang.String text) {
		return Html.escape(text);
	}

	public java.lang.String fromInputSafe(java.lang.String text) {
		return Html.fromInputSafe(text);
	}

	public java.lang.String replaceMsWordCharacters(java.lang.String text) {
		return Html.replaceMsWordCharacters(text);
	}

	public java.lang.String stripBetween(java.lang.String text,
		java.lang.String tag) {
		return Html.stripBetween(text, tag);
	}

	public java.lang.String stripComments(java.lang.String text) {
		return Html.stripComments(text);
	}

	public java.lang.String stripHtml(java.lang.String text) {
		return Html.stripHtml(text);
	}

	public java.lang.String toInputSafe(java.lang.String text) {
		return Html.toInputSafe(text);
	}

	public java.lang.String unescape(java.lang.String text) {
		return Html.unescape(text);
	}

	private Html_IW() {
	}

	private static Html_IW _instance = new Html_IW();
}