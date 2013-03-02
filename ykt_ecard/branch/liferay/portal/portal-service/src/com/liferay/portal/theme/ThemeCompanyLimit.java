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

package com.liferay.portal.theme;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * <a href="ThemeCompanyLimit.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeCompanyLimit implements Serializable {

	public ThemeCompanyLimit() {
		_includes = new ArrayList();
		_excludes = new ArrayList();
	}

	public List getIncludes() {
		return _includes;
	}

	public void setIncludes(List includes) {
		_includes = includes;
	}

	public boolean isIncluded(long companyId) {
		return _matches(_includes, companyId);
	}

	public List getExcludes() {
		return _excludes;
	}

	public void setExcludes(List excludes) {
		_excludes = excludes;
	}

	public boolean isExcluded(long companyId) {
		return _matches(_excludes, companyId);
	}

	private boolean _matches(List themeCompanyIds, long companyId) {
		for (int i = 0; i < themeCompanyIds.size(); i++) {
			ThemeCompanyId themeCompanyId =
				(ThemeCompanyId)themeCompanyIds.get(i);

			String themeCompanyIdValue = themeCompanyId.getValue();

			if (themeCompanyId.isPattern()) {
				Pattern pattern = Pattern.compile(themeCompanyIdValue);
				Matcher matcher = pattern.matcher(String.valueOf(companyId));

				if (matcher.matches()) {
					return true;
				}
			}
			else {
				Long themeCompanyIdValueLong = new Long(0);

				try {
					themeCompanyIdValueLong = new Long(themeCompanyIdValue);
				}
				catch (Exception e) {
				}

				if (themeCompanyIdValueLong.longValue() == companyId) {
					return true;
				}
			}
		}

		return false;
	}

	private List _includes;
	private List _excludes;

}