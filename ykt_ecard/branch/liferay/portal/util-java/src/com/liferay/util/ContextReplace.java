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

package com.liferay.util;

import com.liferay.portal.kernel.util.StringUtil;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * <a href="ContextReplace.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ContextReplace implements Cloneable {

	public ContextReplace() {
		this(null);
	}

	public ContextReplace(Map context) {
		if (context != null) {
			_context.putAll(context);

			_updateArrays();
		}
	}

	public void addValue(String key, String value) {
		if ((key != null) && (value != null)) {
			_context.put(key, value);

			_updateArrays();
		}
	}

	public String replace(String text) {
		if (text == null) {
			return null;
		}

		if (_keys.length == 0) {
			return text;
		}

		return StringUtil.replace(text, _keys, _values);
	}

	public Object clone() {
		return new ContextReplace(_context);
	}

	private void _updateArrays() {
		List keys = new ArrayList();
		List values = new ArrayList();

		Iterator itr = _context.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String entryKey = (String)entry.getKey();
			String entryValue = (String)entry.getValue();

			keys.add("${" + entryKey + "}");
			values.add(entryValue);
		}

		_keys = (String[])keys.toArray(new String[0]);
		_values = (String[])values.toArray(new String[0]);
	}

	private Map _context = new LinkedHashMap();
	private String[] _keys = new String[0];
	private String[] _values = new String[0];

}