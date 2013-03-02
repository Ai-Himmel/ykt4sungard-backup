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

package com.liferay.portal.model;

import java.io.Serializable;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * <a href="PortletCategory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletCategory implements Serializable {

	public PortletCategory() {
		this("root");
	}

	public PortletCategory(String name) {
		_name = name;
		_categories = new HashMap();
		_portlets = new HashSet();
	}

	public String getName() {
		return _name;
	}

	public Collection getCategories() {
		return Collections.unmodifiableCollection(_categories.values());
	}

	public void addCategory(PortletCategory portletCategory) {
		_categories.put(portletCategory.getName(), portletCategory);
	}

	public PortletCategory getCategory(String name) {
		return (PortletCategory)_categories.get(name);
	}

	public Set getPortlets() {
		return _portlets;
	}

	public void merge(PortletCategory newPortletCategory) {
		_merge(this, newPortletCategory);
	}

	public void separate(Set portletIds) {
		Iterator itr = _categories.values().iterator();

		while (itr.hasNext()) {
			PortletCategory category = (PortletCategory)itr.next();

			category.separate(portletIds);
		}

		itr = _portlets.iterator();

		while (itr.hasNext()) {
			String portletId = (String)itr.next();

			if (portletIds.contains(portletId)) {
				itr.remove();
			}
		}
	}

	private void _merge(
		PortletCategory portletCategory1, PortletCategory portletCategory2) {

		Iterator itr = portletCategory2.getCategories().iterator();

		while (itr.hasNext()) {
			PortletCategory curCategory2 = (PortletCategory)itr.next();

			PortletCategory curCategory1 =
				portletCategory1.getCategory(curCategory2.getName());

			if (curCategory1 != null) {
				_merge(curCategory1, curCategory2);
			}
			else {
				portletCategory1.addCategory(curCategory2);
			}
		}

		Set portlets1 = portletCategory1.getPortlets();
		Set portlets2 = portletCategory2.getPortlets();

		portlets1.addAll(portlets2);
	}

	private String _name;
	private Map _categories;
	private Set _portlets;

}