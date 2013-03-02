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

package com.liferay.portal.wsrp.util.comparator;

import java.util.Comparator;

import oasis.names.tc.wsrp.v1.types.PortletDescription;

/**
 * <a href="PortletDescriptionComparator.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Michael Young
 *
 */
public class PortletDescriptionComparator implements Comparator {

	public int compare(Object o1, Object o2) {
		PortletDescription pd1 = (PortletDescription) o1;
		PortletDescription pd2 = (PortletDescription) o2;

		String str1 = "";
		String str2 = "";

		try {
			str1 = pd1.getTitle().getValue();
		}
		catch (NullPointerException e) {
		}

		try {
			str2 = pd2.getTitle().getValue();
		}
		catch (NullPointerException e) {
		}

		return str1.compareToIgnoreCase(str2);
	}

}