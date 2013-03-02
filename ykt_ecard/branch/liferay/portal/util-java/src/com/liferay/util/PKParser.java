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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;

import java.util.Map;

/**
 * <a href="PKParser.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PKParser {

	public PKParser(String pk) {
		if (pk.startsWith(StringPool.OPEN_CURLY_BRACE)) {
			pk = pk.substring(1, pk.length());
		}

		if (pk.endsWith(StringPool.CLOSE_CURLY_BRACE)) {
			pk = pk.substring(0, pk.length() - 1);
		}

		String[] array = StringUtil.split(pk);

		for (int i = 0; i < array.length; i++) {
			String[] kvp = StringUtil.split(array[i], StringPool.EQUAL);

			String key = kvp[0].trim();
			String value = kvp[1].trim();

			_fields.put(key, value);
		}
	}

	public boolean getBoolean(String key) {
		return GetterUtil.getBoolean(getString(key));
	}

	public double getDouble(String key) {
		return GetterUtil.getDouble(getString(key));
	}

	public int getInteger(String key) {
		return GetterUtil.getInteger(getString(key));
	}

	public long getLong(String key) {
		return GetterUtil.getLong(getString(key));
	}

	public short getShort(String key) {
		return GetterUtil.getShort(getString(key));
	}

	public String getString(String key) {
		String value = (String)_fields.get(key);

		if (value == null) {
			return StringPool.BLANK;
		}
		else {
			return value;
		}
	}

	private Map _fields = CollectionFactory.getHashMap();

}