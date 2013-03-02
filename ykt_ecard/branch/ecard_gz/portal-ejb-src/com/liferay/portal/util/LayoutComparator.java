/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.util;

import com.liferay.portal.model.Layout;
import com.liferay.util.StringPool;
import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

/**
 * <a href="LayoutComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class LayoutComparator extends OrderByComparator {

	public static String ORDER_BY_ASC = "userId ASC, layoutId ASC";

	public static String ORDER_BY_DESC = "userId DESC, layoutId DESC";

	public LayoutComparator() {
		this(false);
	}

	public LayoutComparator(boolean asc) {
		_asc = asc;
	}

	public int compare(Object obj1, Object obj2) {
		Layout layout1 = (Layout)obj1;
		Layout layout2 = (Layout)obj2;

		int value = layout1.getUserId().compareTo(layout2.getUserId());

		if (value != 0) {
			if (_asc) {
				return value;
			}
			else {
				return -value;
			}
		}

		Double layoutId1 = _getDouble(layout1.getLayoutId());
		Double layoutId2 = _getDouble(layout2.getLayoutId());

		value = layoutId1.compareTo(layoutId2);

		if (_asc) {
			return value;
		}
		else {
			return -value;
		}
	}

	public String getOrderBy() {
		if (_asc) {
			return ORDER_BY_ASC;
		}
		else {
			return ORDER_BY_DESC;
		}
	}

	private Double _getDouble(String value) {
		int pos = value.indexOf(StringPool.PERIOD);

		if (pos != -1) {
			int decPlacesCount = value.length() - 1 - pos;
			int decPlacesTotal = 4;

			if (decPlacesTotal > decPlacesCount) {
				FastStringBuffer zeroes = new FastStringBuffer();

				int decPlacesDiff = decPlacesTotal - decPlacesCount;

				for (int i = 0; i < decPlacesDiff; i++) {
					zeroes.append("0");
				}

				value =
					value.substring(0, pos + 1) + zeroes.toString() +
						value.substring(pos + 1, value.length());
			}
		}

		return new Double(value);
	}

	private boolean _asc;

}