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

package com.liferay.portal.kernel.plugin;

import java.util.Comparator;

/**
 * <a href="PluginPackageNameAndContextComparator.java.html"><b><i>View Source
 * </i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class PluginPackageNameAndContextComparator implements Comparator {

	public int compare(Object obj1, Object obj2) {
		if (!(obj1 instanceof PluginPackage)) {
			return -1;
		}

		if (!(obj2 instanceof PluginPackage)) {
			return 1;
		}

		PluginPackage package1 = (PluginPackage)obj1;
		PluginPackage package2 = (PluginPackage)obj2;

		int result = package1.getName().compareTo(package2.getName());

		if (result == 0) {
			result = package1.getContext().compareTo(package2.getContext());
		}

		return result;
	}

}