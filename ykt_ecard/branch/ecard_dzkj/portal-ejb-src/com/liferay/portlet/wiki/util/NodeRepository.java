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

package com.liferay.portlet.wiki.util;

import com.efsol.friki.BasicDriver;

import com.liferay.portlet.wiki.service.spring.WikiPageServiceUtil;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.stringtree.util.tract.Tract;

/**
 * <a href="NodeRepository.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class NodeRepository extends BasicDriver {

	public NodeRepository(String nodeId) {
		_nodeId = nodeId;
		_names = new HashMap();
	}

	public Tract get(String name) {
		return null;
	}

	public void put(String name, Tract page) {
	}

	public String backup(String name) {
		return name;
	}

	public boolean contains(String name) {
		boolean exists = false;

		try {
			Boolean existsObj = (Boolean)_names.get(name);

			if (existsObj == null) {
				existsObj = new Boolean(
					WikiPageServiceUtil.exists(_nodeId, name));

				_names.put(name, existsObj);
			}

			exists = existsObj.booleanValue();
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return exists;
	}

	public Iterator allPageNames() {
		return _names.keySet().iterator();
	}

	public Map getTitles() {
		return _names;
	}

	private String _nodeId;
	private Map _names;

}