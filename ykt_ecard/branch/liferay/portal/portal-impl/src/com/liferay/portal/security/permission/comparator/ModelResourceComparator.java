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

package com.liferay.portal.security.permission.comparator;

import com.liferay.portal.security.permission.ResourceActionsUtil;

import java.io.Serializable;

import java.util.Comparator;
import java.util.Locale;

/**
 * <a href="ModelResourceComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ModelResourceComparator implements Comparator, Serializable {

	public ModelResourceComparator(long companyId, Locale locale) {
		_companyId = companyId;
		_locale = locale;
	}

	public int compare(Object obj1, Object obj2) {
		String resource1 = (String)obj1;
		String resource2 = (String)obj2;

		resource1 = ResourceActionsUtil.getModelResource(
			_companyId, _locale, resource1);
		resource2 = ResourceActionsUtil.getModelResource(
			_companyId, _locale, resource2);

		return resource1.compareTo(resource2);
	}

	private long _companyId;
	private Locale _locale;

}