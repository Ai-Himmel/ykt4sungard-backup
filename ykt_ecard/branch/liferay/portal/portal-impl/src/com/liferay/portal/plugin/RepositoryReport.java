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

package com.liferay.portal.plugin;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * <a href="RepositoryReport.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class RepositoryReport {

	public static final String SUCCESS = "success";

	public void addSuccess(String repositoryURL) {
		_reportMap.put(repositoryURL, SUCCESS);
	}

	public void addError(String repositoryURL, PluginPackageException ppe) {
		StringMaker sm = new StringMaker();

		if (Validator.isNotNull(ppe.getMessage())) {
			sm.append(ppe.getMessage());
		}

		if ((ppe.getCause() != null) &&
			Validator.isNull(ppe.getCause().getMessage())) {

			sm.append(ppe.getCause().getMessage());
		}

		if (sm.length() == 0) {
			sm.append(ppe.toString());
		}

		_reportMap.put(repositoryURL, sm.toString());
	}

	public Set getRepositoryURLs() {
		return _reportMap.keySet();
	}

	public Object getState(String repositoryURL) {
		return _reportMap.get(repositoryURL);
	}

	public String toString() {
		StringMaker sm = new StringMaker();

		Iterator itr = getRepositoryURLs().iterator();

		while (itr.hasNext()) {
			String repositoryURL = (String)itr.next();

			sm.append(repositoryURL);
			sm.append(": ");
			sm.append(_reportMap.get(repositoryURL));
		}

		return sm.toString();
	}

	private Map _reportMap = new TreeMap();

}