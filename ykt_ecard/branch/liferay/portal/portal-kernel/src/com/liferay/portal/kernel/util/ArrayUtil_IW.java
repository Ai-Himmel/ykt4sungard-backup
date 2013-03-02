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
 * <a href="ArrayUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ArrayUtil_IW {
	public static ArrayUtil_IW getInstance() {
		return _instance;
	}

	public java.lang.Boolean[] append(java.lang.Boolean[] array,
		java.lang.Boolean obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Double[] append(java.lang.Double[] array,
		java.lang.Double obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Float[] append(java.lang.Float[] array, java.lang.Float obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Integer[] append(java.lang.Integer[] array,
		java.lang.Integer obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Long[] append(java.lang.Long[] array, java.lang.Long obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Object[] append(java.lang.Object[] array,
		java.lang.Object obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Object[][] append(java.lang.Object[][] array,
		java.lang.Object[] obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Short[] append(java.lang.Short[] array, java.lang.Short obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.String[] append(java.lang.String[] array,
		java.lang.String obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.String[][] append(java.lang.String[][] array,
		java.lang.String[] obj) {
		return ArrayUtil.append(array, obj);
	}

	public java.lang.Boolean[] append(java.lang.Boolean[] array1,
		java.lang.Boolean[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Double[] append(java.lang.Double[] array1,
		java.lang.Double[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Float[] append(java.lang.Float[] array1,
		java.lang.Float[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Integer[] append(java.lang.Integer[] array1,
		java.lang.Integer[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Long[] append(java.lang.Long[] array1,
		java.lang.Long[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Object[] append(java.lang.Object[] array1,
		java.lang.Object[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Object[][] append(java.lang.Object[][] array1,
		java.lang.Object[][] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.Short[] append(java.lang.Short[] array1,
		java.lang.Short[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.String[] append(java.lang.String[] array1,
		java.lang.String[] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public java.lang.String[][] append(java.lang.String[][] array1,
		java.lang.String[][] array2) {
		return ArrayUtil.append(array1, array2);
	}

	public void combine(java.lang.Object[] array1, java.lang.Object[] array2,
		java.lang.Object[] combinedArray) {
		ArrayUtil.combine(array1, array2, combinedArray);
	}

	public boolean contains(boolean[] array, boolean value) {
		return ArrayUtil.contains(array, value);
	}

	public boolean contains(char[] array, char value) {
		return ArrayUtil.contains(array, value);
	}

	public boolean contains(double[] array, double value) {
		return ArrayUtil.contains(array, value);
	}

	public boolean contains(long[] array, long value) {
		return ArrayUtil.contains(array, value);
	}

	public boolean contains(int[] array, int value) {
		return ArrayUtil.contains(array, value);
	}

	public boolean contains(short[] array, short value) {
		return ArrayUtil.contains(array, value);
	}

	public boolean contains(java.lang.Object[] array, java.lang.Object value) {
		return ArrayUtil.contains(array, value);
	}

	public java.lang.String[] distinct(java.lang.String[] array) {
		return ArrayUtil.distinct(array);
	}

	public java.lang.String[] distinct(java.lang.String[] array,
		java.util.Comparator comparator) {
		return ArrayUtil.distinct(array, comparator);
	}

	public int getLength(java.lang.Object[] array) {
		return ArrayUtil.getLength(array);
	}

	public java.lang.Object getValue(java.lang.Object[] array, int pos) {
		return ArrayUtil.getValue(array, pos);
	}

	public java.lang.String[] removeByPrefix(java.lang.String[] array,
		java.lang.String prefix) {
		return ArrayUtil.removeByPrefix(array, prefix);
	}

	public java.lang.Boolean[] toObjectArray(boolean[] array) {
		return ArrayUtil.toObjectArray(array);
	}

	public java.lang.Double[] toObjectArray(double[] array) {
		return ArrayUtil.toObjectArray(array);
	}

	public java.lang.Float[] toObjectArray(float[] array) {
		return ArrayUtil.toObjectArray(array);
	}

	public java.lang.Integer[] toObjectArray(int[] array) {
		return ArrayUtil.toObjectArray(array);
	}

	public java.lang.Long[] toObjectArray(long[] array) {
		return ArrayUtil.toObjectArray(array);
	}

	public java.lang.Short[] toObjectArray(short[] array) {
		return ArrayUtil.toObjectArray(array);
	}

	private ArrayUtil_IW() {
	}

	private static ArrayUtil_IW _instance = new ArrayUtil_IW();
}