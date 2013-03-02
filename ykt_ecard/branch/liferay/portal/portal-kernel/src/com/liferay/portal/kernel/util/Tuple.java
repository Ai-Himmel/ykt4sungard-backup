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

package com.liferay.portal.kernel.util;

/**
 * <a href="Tuple.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class Tuple {

	public Tuple(Object obj0, Object obj1) {
		_array = new Object[] {obj0, obj1};
	}

	public Tuple(Object obj0, Object obj1, Object obj2) {
		_array = new Object[] {obj0, obj1, obj2};
	}

	public Tuple(Object obj0, Object obj1, Object obj2, Object obj3) {
		_array = new Object[] {obj0, obj1, obj2, obj3};
	}

	public Tuple(Object[] array) {
		_array = array;
	}

	public Object getObject(int i) {
		return _array[i];
	}

	public boolean equals(Object obj) {
		if (!(obj instanceof Tuple)) {
			return false;
		}

		Tuple tuple = (Tuple)obj;

		if (tuple._array.length != _array.length) {
			return false;
		}

		for (int i = 0; i < _array.length; i++) {
			if ((tuple._array != null) && (_array[i] != null) &&
				(!_array[i].equals(tuple._array[i]))) {

				return false;
			}
			else if ((tuple._array[i] == null) || (_array[i] == null)) {
				return false;
			}
		}

		return true;
	}

	public int hashCode() {
		int hashCode = 0;

		for (int i = 0; i < _array.length; i++) {
			hashCode = hashCode ^ _array[i].hashCode();
		}

		return hashCode;
	}

	private Object[] _array;

}