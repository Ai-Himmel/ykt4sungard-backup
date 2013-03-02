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
import com.liferay.portal.model.Permission;

/**
 * <a href="PermissionComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class PermissionComparator extends OrderByComparator {

	public static String ORDER_BY_DESC = "permissionId DESC";

	public int compare(Object obj1, Object obj2) {
		Permission perm1 = (Permission)obj1;
		Permission perm2 = (Permission)obj2;

		long permissionId1 = perm1.getPermissionId();
		long permissionId2 = perm2.getPermissionId();

		if (permissionId1 > permissionId2) {
			return -1;
		}
		else if (permissionId1 < permissionId2) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public String getOrderBy() {
		return ORDER_BY_DESC;
	}

}