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

package com.liferay.portal.kernel.util;

import java.io.Serializable;

import java.util.Comparator;

/**
 * <a href="StringComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class StringComparator implements Comparator, Serializable {

	public StringComparator() {
		this(true, false);
	}

	public StringComparator(boolean asc, boolean caseSensitive) {
		_asc = asc;
		_caseSensitive = caseSensitive;
	}

	public int compare(Object obj1, Object obj2) {
		String s1 = (String)obj1;
		String s2 = (String)obj2;

		if (s1 == null) {
			s1 = StringPool.BLANK;
		}

		if (s2 == null) {
			s2 = StringPool.BLANK;
		}

		if (!_asc) {
			String temp = s1;

			s1 = s2;
			s2 = temp;
		}

		if (_caseSensitive) {
			return s1.compareTo(s2);
		}
		else {
			return s1.compareToIgnoreCase(s2);
		}
	}

	private boolean _asc;
	private boolean _caseSensitive;

}