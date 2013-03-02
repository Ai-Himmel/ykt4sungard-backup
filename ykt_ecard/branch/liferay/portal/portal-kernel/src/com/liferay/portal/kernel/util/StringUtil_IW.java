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
 * <a href="StringUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class StringUtil_IW {
	public static StringUtil_IW getInstance() {
		return _instance;
	}

	public java.lang.String add(java.lang.String s, java.lang.String add) {
		return StringUtil.add(s, add);
	}

	public java.lang.String add(java.lang.String s, java.lang.String add,
		java.lang.String delimiter) {
		return StringUtil.add(s, add, delimiter);
	}

	public java.lang.String add(java.lang.String s, java.lang.String add,
		java.lang.String delimiter, boolean allowDuplicates) {
		return StringUtil.add(s, add, delimiter, allowDuplicates);
	}

	public java.lang.String bytesToHexString(byte[] bytes) {
		return StringUtil.bytesToHexString(bytes);
	}

	public boolean contains(java.lang.String s, java.lang.String text) {
		return StringUtil.contains(s, text);
	}

	public boolean contains(java.lang.String s, java.lang.String text,
		java.lang.String delimiter) {
		return StringUtil.contains(s, text, delimiter);
	}

	public int count(java.lang.String s, java.lang.String text) {
		return StringUtil.count(s, text);
	}

	public boolean endsWith(java.lang.String s, char end) {
		return StringUtil.endsWith(s, end);
	}

	public boolean endsWith(java.lang.String s, java.lang.String end) {
		return StringUtil.endsWith(s, end);
	}

	public java.lang.String extractChars(java.lang.String s) {
		return StringUtil.extractChars(s);
	}

	public java.lang.String extractDigits(java.lang.String s) {
		return StringUtil.extractDigits(s);
	}

	public java.lang.String extractFirst(java.lang.String s,
		java.lang.String delimiter) {
		return StringUtil.extractFirst(s, delimiter);
	}

	public java.lang.String extractLast(java.lang.String s,
		java.lang.String delimiter) {
		return StringUtil.extractLast(s, delimiter);
	}

	public java.lang.String highlight(java.lang.String s,
		java.lang.String keywords) {
		return StringUtil.highlight(s, keywords);
	}

	public java.lang.String highlight(java.lang.String s,
		java.lang.String keywords, java.lang.String highlight1,
		java.lang.String highlight2) {
		return StringUtil.highlight(s, keywords, highlight1, highlight2);
	}

	public java.lang.String lowerCase(java.lang.String s) {
		return StringUtil.lowerCase(s);
	}

	public java.lang.String merge(boolean[] array) {
		return StringUtil.merge(array);
	}

	public java.lang.String merge(boolean[] array, java.lang.String delimiter) {
		return StringUtil.merge(array, delimiter);
	}

	public java.lang.String merge(int[] array) {
		return StringUtil.merge(array);
	}

	public java.lang.String merge(int[] array, java.lang.String delimiter) {
		return StringUtil.merge(array, delimiter);
	}

	public java.lang.String merge(long[] array) {
		return StringUtil.merge(array);
	}

	public java.lang.String merge(long[] array, java.lang.String delimiter) {
		return StringUtil.merge(array, delimiter);
	}

	public java.lang.String merge(short[] array) {
		return StringUtil.merge(array);
	}

	public java.lang.String merge(short[] array, java.lang.String delimiter) {
		return StringUtil.merge(array, delimiter);
	}

	public java.lang.String merge(java.util.List list) {
		return StringUtil.merge(list);
	}

	public java.lang.String merge(java.util.List list,
		java.lang.String delimiter) {
		return StringUtil.merge(list, delimiter);
	}

	public java.lang.String merge(java.lang.Object[] array) {
		return StringUtil.merge(array);
	}

	public java.lang.String merge(java.lang.Object[] array,
		java.lang.String delimiter) {
		return StringUtil.merge(array, delimiter);
	}

	public java.lang.String randomize(java.lang.String s) {
		return StringUtil.randomize(s);
	}

	public java.lang.String read(java.lang.ClassLoader classLoader,
		java.lang.String name) throws java.io.IOException {
		return StringUtil.read(classLoader, name);
	}

	public java.lang.String read(java.lang.ClassLoader classLoader,
		java.lang.String name, boolean all) throws java.io.IOException {
		return StringUtil.read(classLoader, name, all);
	}

	public java.lang.String read(java.io.InputStream is)
		throws java.io.IOException {
		return StringUtil.read(is);
	}

	public java.lang.String remove(java.lang.String s, java.lang.String remove) {
		return StringUtil.remove(s, remove);
	}

	public java.lang.String remove(java.lang.String s, java.lang.String remove,
		java.lang.String delimiter) {
		return StringUtil.remove(s, remove, delimiter);
	}

	public java.lang.String replace(java.lang.String s, char oldSub, char newSub) {
		return StringUtil.replace(s, oldSub, newSub);
	}

	public java.lang.String replace(java.lang.String s, char oldSub,
		java.lang.String newSub) {
		return StringUtil.replace(s, oldSub, newSub);
	}

	public java.lang.String replace(java.lang.String s,
		java.lang.String oldSub, java.lang.String newSub) {
		return StringUtil.replace(s, oldSub, newSub);
	}

	public java.lang.String replace(java.lang.String s,
		java.lang.String[] oldSubs, java.lang.String[] newSubs) {
		return StringUtil.replace(s, oldSubs, newSubs);
	}

	public java.lang.String replaceValues(java.lang.String s,
		java.lang.String begin, java.lang.String end, java.util.Map values) {
		return StringUtil.replaceValues(s, begin, end, values);
	}

	public java.lang.String reverse(java.lang.String s) {
		return StringUtil.reverse(s);
	}

	public java.lang.String safePath(java.lang.String path) {
		return StringUtil.safePath(path);
	}

	public java.lang.String shorten(java.lang.String s) {
		return StringUtil.shorten(s);
	}

	public java.lang.String shorten(java.lang.String s, int length) {
		return StringUtil.shorten(s, length);
	}

	public java.lang.String shorten(java.lang.String s, java.lang.String suffix) {
		return StringUtil.shorten(s, suffix);
	}

	public java.lang.String shorten(java.lang.String s, int length,
		java.lang.String suffix) {
		return StringUtil.shorten(s, length, suffix);
	}

	public java.lang.String[] split(java.lang.String s) {
		return StringUtil.split(s);
	}

	public java.lang.String[] split(java.lang.String s,
		java.lang.String delimiter) {
		return StringUtil.split(s, delimiter);
	}

	public boolean[] split(java.lang.String s, boolean x) {
		return StringUtil.split(s, x);
	}

	public boolean[] split(java.lang.String s, java.lang.String delimiter,
		boolean x) {
		return StringUtil.split(s, delimiter, x);
	}

	public double[] split(java.lang.String s, double x) {
		return StringUtil.split(s, x);
	}

	public double[] split(java.lang.String s, java.lang.String delimiter,
		double x) {
		return StringUtil.split(s, delimiter, x);
	}

	public float[] split(java.lang.String s, float x) {
		return StringUtil.split(s, x);
	}

	public float[] split(java.lang.String s, java.lang.String delimiter, float x) {
		return StringUtil.split(s, delimiter, x);
	}

	public int[] split(java.lang.String s, int x) {
		return StringUtil.split(s, x);
	}

	public int[] split(java.lang.String s, java.lang.String delimiter, int x) {
		return StringUtil.split(s, delimiter, x);
	}

	public long[] split(java.lang.String s, long x) {
		return StringUtil.split(s, x);
	}

	public long[] split(java.lang.String s, java.lang.String delimiter, long x) {
		return StringUtil.split(s, delimiter, x);
	}

	public short[] split(java.lang.String s, short x) {
		return StringUtil.split(s, x);
	}

	public short[] split(java.lang.String s, java.lang.String delimiter, short x) {
		return StringUtil.split(s, delimiter, x);
	}

	public boolean startsWith(java.lang.String s, char begin) {
		return StringUtil.startsWith(s, begin);
	}

	public boolean startsWith(java.lang.String s, java.lang.String start) {
		return StringUtil.startsWith(s, start);
	}

	public java.lang.String stripBetween(java.lang.String s,
		java.lang.String begin, java.lang.String end) {
		return StringUtil.stripBetween(s, begin, end);
	}

	public java.lang.String trim(java.lang.String s) {
		return StringUtil.trim(s);
	}

	public java.lang.String trim(java.lang.String s, char c) {
		return StringUtil.trim(s, c);
	}

	public java.lang.String trim(java.lang.String s, char[] exceptions) {
		return StringUtil.trim(s, exceptions);
	}

	public java.lang.String trimLeading(java.lang.String s) {
		return StringUtil.trimLeading(s);
	}

	public java.lang.String trimLeading(java.lang.String s, char c) {
		return StringUtil.trimLeading(s, c);
	}

	public java.lang.String trimLeading(java.lang.String s, char[] exceptions) {
		return StringUtil.trimLeading(s, exceptions);
	}

	public java.lang.String trimTrailing(java.lang.String s) {
		return StringUtil.trimTrailing(s);
	}

	public java.lang.String trimTrailing(java.lang.String s, char c) {
		return StringUtil.trimTrailing(s, c);
	}

	public java.lang.String trimTrailing(java.lang.String s, char[] exceptions) {
		return StringUtil.trimTrailing(s, exceptions);
	}

	public java.lang.String upperCase(java.lang.String s) {
		return StringUtil.upperCase(s);
	}

	public java.lang.String upperCaseFirstLetter(java.lang.String s) {
		return StringUtil.upperCaseFirstLetter(s);
	}

	public java.lang.String wrap(java.lang.String text) {
		return StringUtil.wrap(text);
	}

	public java.lang.String wrap(java.lang.String text, int width,
		java.lang.String lineSeparator) {
		return StringUtil.wrap(text, width, lineSeparator);
	}

	private StringUtil_IW() {
	}

	private static StringUtil_IW _instance = new StringUtil_IW();
}