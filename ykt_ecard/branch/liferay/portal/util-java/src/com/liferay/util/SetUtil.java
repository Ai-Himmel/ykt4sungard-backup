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

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import java.util.Set;

/**
 * <a href="SetUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SetUtil {

	public static Set fromArray(Object[] array) {
		if ((array == null) || (array.length == 0)) {
			return CollectionFactory.getHashSet();
		}

		Set set = CollectionFactory.getHashSet(array.length);

		for (int i = 0; i < array.length; i++) {
			set.add(array[i]);
		}

		return set;
	}

	public static Set fromFile(String fileName) throws IOException {
		return fromFile(new File(fileName));
	}

	public static Set fromFile(File file) throws IOException {
		Set set = CollectionFactory.getHashSet();

		BufferedReader br = new BufferedReader(new FileReader(file));

		String s = StringPool.BLANK;

		while ((s = br.readLine()) != null) {
			set.add(s);
		}

		br.close();

		return set;
	}

	public static Set fromString(String s) {
		return fromArray(StringUtil.split(s, StringPool.NEW_LINE));
	}

}