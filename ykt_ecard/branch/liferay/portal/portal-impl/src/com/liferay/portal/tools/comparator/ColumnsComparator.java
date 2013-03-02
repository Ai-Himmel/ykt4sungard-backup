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

package com.liferay.portal.tools.comparator;

import java.util.Comparator;
import java.util.List;

/**
 * <a href="ColumnsComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ColumnsComparator implements Comparator {

	public ColumnsComparator(String columnName) {
		this(new String[] {columnName});
	}

	public ColumnsComparator(List columnNames) {
		this((String[])columnNames.toArray(new String[0]));
	}

	public ColumnsComparator(String[] columnNames) {
		_columnNames = columnNames;
	}

	public int compare(Object obj1, Object obj2) {
		Object[] column1 = (Object[])obj1;
		Object[] column2 = (Object[])obj2;

		String columnName1 = (String)column1[0];
		String columnName2 = (String)column2[0];

		int x = -1;

		for (int i = 0; i < _columnNames.length; i++) {
			if (_columnNames[i].equals(columnName1)) {
				x = i;

				break;
			}
		}

		int y = -1;

		for (int i = 0; i < _columnNames.length; i++) {
			if (_columnNames[i].equals(columnName2)) {
				y = i;

				break;
			}
		}

		if ((x == -1) && (y > -1)) {
			return 1;
		}
		else if ((x > -1) && (y == -1)) {
			return -1;
		}
		else if ((x > -1) && (y > -1)) {
			if (x < y) {
				return -1;
			}
			else if (x > y) {
				return 1;
			}
		}

		return 0;
	}

	private String[] _columnNames;

}