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

package com.liferay.portal.util.comparator;

import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.model.Layout;

/**
 * <a href="LayoutPriorityComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutPriorityComparator extends OrderByComparator {

	public static String ORDER_BY_ASC = "priority ASC";

	public LayoutPriorityComparator(Layout layout, boolean lessThan) {
		_layout = layout;
		_lessThan = lessThan;
	}

	public int compare(Object obj1, Object obj2) {
		Layout layout1 = (Layout)obj1;
		Layout layout2 = (Layout)obj2;

		int priority1 = layout1.getPriority();
		int priority2 = layout2.getPriority();

		if (priority1 > priority2) {
			return 1;
		}
		else if (priority1 < priority2) {
			return -1;
		}
		else {
			if (_layout.equals(layout1)) {
				if (_lessThan) {
					return 1;
				}
				else {
					return -1;
				}
			}
			else if (_layout.equals(layout2)) {
				if (_lessThan) {
					return -1;
				}
				else {
					return 1;
				}
			}

			return 0;
		}
	}

	public String getOrderBy() {
		return ORDER_BY_ASC;
	}

	private Layout _layout;
	private boolean _lessThan;

}