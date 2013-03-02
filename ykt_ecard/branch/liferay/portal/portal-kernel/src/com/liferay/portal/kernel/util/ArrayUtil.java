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

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="ArrayUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ArrayUtil {

	public static Boolean[] append(Boolean[] array, Boolean obj) {
		Boolean[] newArray = new Boolean[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Double[] append(Double[] array, Double obj) {
		Double[] newArray = new Double[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Float[] append(Float[] array, Float obj) {
		Float[] newArray = new Float[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Integer[] append(Integer[] array, Integer obj) {
		Integer[] newArray = new Integer[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Long[] append(Long[] array, Long obj) {
		Long[] newArray = new Long[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Object[] append(Object[] array, Object obj) {
		Object[] newArray = new Object[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Object[][] append(Object[][] array, Object[] obj) {
		Object[][] newArray = new Object[array.length + 1][];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Short[] append(Short[] array, Short obj) {
		Short[] newArray = new Short[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static String[] append(String[] array, String obj) {
		String[] newArray = new String[array.length + 1];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static String[][] append(String[][] array, String[] obj) {
		String[][] newArray = new String[array.length + 1][];

		System.arraycopy(array, 0, newArray, 0, array.length);

		newArray[newArray.length - 1] = obj;

		return newArray;
	}

	public static Boolean[] append(Boolean[] array1, Boolean[] array2) {
		Boolean[] newArray = new Boolean[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Double[] append(Double[] array1, Double[] array2) {
		Double[] newArray = new Double[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Float[] append(Float[] array1, Float[] array2) {
		Float[] newArray = new Float[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Integer[] append(Integer[] array1, Integer[] array2) {
		Integer[] newArray = new Integer[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Long[] append(Long[] array1, Long[] array2) {
		Long[] newArray = new Long[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Object[] append(Object[] array1, Object[] array2) {
		Object[] newArray = new Object[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Object[][] append(Object[][] array1, Object[][] array2) {
		Object[][] newArray = new Object[array1.length + array2.length][];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static Short[] append(Short[] array1, Short[] array2) {
		Short[] newArray = new Short[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static String[] append(String[] array1, String[] array2) {
		String[] newArray = new String[array1.length + array2.length];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static String[][] append(String[][] array1, String[][] array2) {
		String[][] newArray = new String[array1.length + array2.length][];

		System.arraycopy(array1, 0, newArray, 0, array1.length);
		System.arraycopy(array2, 0, newArray, array1.length, array2.length);

		return newArray;
	}

	public static void combine(
		Object[] array1, Object[] array2, Object[] combinedArray) {

		System.arraycopy(array1, 0, combinedArray, 0, array1.length);

		System.arraycopy(
			array2, 0, combinedArray, array1.length, array2.length);
	}

	public static boolean contains(boolean[] array, boolean value) {
		if ((array == null) || (array.length == 0)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value == array[i]) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean contains(char[] array, char value) {
		if ((array == null) || (array.length == 0)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value == array[i]) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean contains(double[] array, double value) {
		if ((array == null) || (array.length == 0)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value == array[i]) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean contains(long[] array, long value) {
		if ((array == null) || (array.length == 0)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value == array[i]) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean contains(int[] array, int value) {
		if ((array == null) || (array.length == 0)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value == array[i]) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean contains(short[] array, short value) {
		if ((array == null) || (array.length == 0)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value == array[i]) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean contains(Object[] array, Object value) {
		if ((array == null) || (array.length == 0) || (value == null)) {
			return false;
		}
		else {
			for (int i = 0; i < array.length; i++) {
				if (value.equals(array[i])) {
					return true;
				}
			}

			return false;
		}
	}

	public static String[] distinct(String[] array) {
		return distinct(array, null);
	}

	public static String[] distinct(String[] array, Comparator comparator) {
		if ((array == null) || (array.length == 0)) {
			return array;
		}

		Set set = null;

		if (comparator == null) {
			set = new TreeSet();
		}
		else {
			set = new TreeSet(comparator);
		}

		for (int i = 0; i < array.length; i++) {
			Object obj = array[i];

			if (!set.contains(obj)) {
				set.add(obj);
			}
		}

		return (String[])set.toArray(new String[0]);
	}

	public static int getLength(Object[] array) {
		if (array == null) {
			return 0;
		}
		else {
			return array.length;
		}
	}

	public static Object getValue(Object[] array, int pos) {
		if ((array == null) || (array.length <= pos)) {
			return null;
		}
		else {
			return array[pos];
		}
	}

	public static String[] removeByPrefix(String[] array, String prefix) {
		List list = new ArrayList();

		for (int i = 0; i < array.length; i++) {
			String s = array[i];

			if (!s.startsWith(prefix)) {
				list.add(s);
			}
		}

		return (String[])list.toArray(new String[list.size()]);
	}

	public static Boolean[] toObjectArray(boolean[] array) {
		Boolean[] objArray = new Boolean[array.length];

		for (int i = 0; i < array.length; i++) {
			objArray[i] = Boolean.valueOf(array[i]);
		}

		return objArray;
	}

	public static Double[] toObjectArray(double[] array) {
		Double[] objArray = new Double[array.length];

		for (int i = 0; i < array.length; i++) {
			objArray[i] = new Double(array[i]);
		}

		return objArray;
	}

	public static Float[] toObjectArray(float[] array) {
		Float[] objArray = new Float[array.length];

		for (int i = 0; i < array.length; i++) {
			objArray[i] = new Float(array[i]);
		}

		return objArray;
	}

	public static Integer[] toObjectArray(int[] array) {
		Integer[] objArray = new Integer[array.length];

		for (int i = 0; i < array.length; i++) {
			objArray[i] = new Integer(array[i]);
		}

		return objArray;
	}

	public static Long[] toObjectArray(long[] array) {
		Long[] objArray = new Long[array.length];

		for (int i = 0; i < array.length; i++) {
			objArray[i] = new Long(array[i]);
		}

		return objArray;
	}

	public static Short[] toObjectArray(short[] array) {
		Short[] objArray = new Short[array.length];

		for (int i = 0; i < array.length; i++) {
			objArray[i] = new Short(array[i]);
		}

		return objArray;
	}

}