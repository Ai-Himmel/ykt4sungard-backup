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

package com.liferay.portal.upgrade.util;

import com.liferay.portal.upgrade.StagnantRowException;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

/**
 * <a href="MemoryValueMapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Brian Wing Shun Chan
 *
 */
public class MemoryValueMapper implements ValueMapper {

	public MemoryValueMapper() {
		this(new LinkedHashSet());
	}

	public MemoryValueMapper(Set exceptions) {
		_map = new LinkedHashMap();
		_exceptions = exceptions;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		Object value = _map.get(oldValue);

		if (value == null) {
			if (_exceptions.contains(oldValue)) {
				value = oldValue;
			}
			else {
				throw new StagnantRowException(String.valueOf(oldValue));
			}
		}

		return value;
	}

	public void mapValue(Object oldValue, Object newValue) throws Exception {
		_map.put(oldValue, newValue);
	}

	public void appendException(Object exception) {
		_exceptions.add(exception);
	}

	public Iterator iterator() throws Exception {
		return _map.keySet().iterator();
	}

	public int size() throws Exception {
		return _map.size();
	}

	public Map getMap() {
		return _map;
	}

	private Map _map;
	private Set _exceptions;

}