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

package com.liferay.util.diff;

import com.liferay.util.diff.DiffResult;
import com.liferay.util.diff.DiffUtil;

import java.io.StringReader;

import java.util.ArrayList;
import java.util.List;

import junit.framework.TestCase;

/**
 * <a href="DiffTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class DiffTest extends TestCase {

	public void testOne() {
		StringReader reader1 = new StringReader("liferay");
		StringReader reader2 = new StringReader("liferay");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testTwo() {
		StringReader reader1 = new StringReader("liferay");
		StringReader reader2 = new StringReader("LifeRay");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		List changedLines = new ArrayList();

		changedLines.add(
			DiffUtil.OPEN_DEL + "l" + DiffUtil.CLOSE_DEL + "ife" +
				DiffUtil.OPEN_DEL + "r" + DiffUtil.CLOSE_DEL + "ay");

		expectedSource.add(new DiffResult(0, changedLines));

		changedLines = new ArrayList();

		changedLines.add(
			DiffUtil.OPEN_INS + "L" + DiffUtil.CLOSE_INS + "ife" +
				DiffUtil.OPEN_INS + "R" + DiffUtil.CLOSE_INS + "ay");

		expectedTarget.add(new DiffResult(0, changedLines));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testThree() {
		StringReader reader1 = new StringReader("aaa");
		StringReader reader2 = new StringReader("bbb");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		expectedTarget.add(
			new DiffResult(0, DiffUtil.OPEN_INS + "bbb" + DiffUtil.CLOSE_INS));

		expectedSource.add(
			new DiffResult(0, DiffUtil.OPEN_DEL + "aaa" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testFour() {
		StringReader reader1 = new StringReader("rahab");
		StringReader reader2 = new StringReader("boaz");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		expectedTarget.add(
			new DiffResult(0, DiffUtil.OPEN_INS + "boaz" + DiffUtil.CLOSE_INS));

		expectedSource.add(
			new DiffResult(
				0, DiffUtil.OPEN_DEL + "rahab" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testFive() {
		StringReader reader1 = new StringReader("aaa\nbbb");
		StringReader reader2 = new StringReader("ccc\naaa");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		expectedTarget.add(
			new DiffResult(0, DiffUtil.OPEN_INS + "ccc" + DiffUtil.CLOSE_INS));

		List changedLines = new ArrayList();

		changedLines.add("aaa");
		changedLines.add(DiffUtil.OPEN_DEL + "bbb" + DiffUtil.CLOSE_DEL);

		expectedSource.add(new DiffResult(1, changedLines));

		changedLines = new ArrayList();

		changedLines.add("aaa");
		changedLines.add(DiffUtil.CONTEXT_LINE);

		expectedTarget.add(new DiffResult(1, changedLines));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testSix() {
		StringReader reader1 = new StringReader("ccc\naaa");
		StringReader reader2 = new StringReader("aaa\nbbb");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(
			new DiffResult(0, DiffUtil.OPEN_DEL + "ccc" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		List changedLines = new ArrayList();

		changedLines.add("aaa");
		changedLines.add(DiffUtil.CONTEXT_LINE);

		expectedSource.add(new DiffResult(1, changedLines));

		changedLines = new ArrayList();

		changedLines.add("aaa");
		changedLines.add(DiffUtil.OPEN_INS + "bbb" + DiffUtil.CLOSE_INS);

		expectedTarget.add(new DiffResult(1, changedLines));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testSeven() {
		StringReader reader1 = new StringReader("ccc\naaa\nbbe");
		StringReader reader2 = new StringReader("aaa\nbbb");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		List changedLines = new ArrayList();

		expectedSource.add(
			new DiffResult(0, DiffUtil.OPEN_DEL + "ccc" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		changedLines = new ArrayList();

		changedLines.add("bb" + DiffUtil.OPEN_DEL + "e" + DiffUtil.CLOSE_DEL);
		expectedSource.add(new DiffResult(2, changedLines));

		changedLines = new ArrayList();

		changedLines.add("bb" + DiffUtil.OPEN_INS + "b" + DiffUtil.CLOSE_INS);
		expectedTarget.add(new DiffResult(1, changedLines));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testEight() {
		StringReader reader1 = new StringReader("add\nbbb\nccc");
		StringReader reader2 = new StringReader("bbb\nccc\naee");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(
			new DiffResult(0, DiffUtil.OPEN_DEL + "add" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		List changedLines = new ArrayList();

		changedLines.add("bbb");
		changedLines.add("ccc");
		changedLines.add(DiffUtil.CONTEXT_LINE);
		expectedSource.add(new DiffResult(2, changedLines));

		changedLines = new ArrayList();

		changedLines.add("bbb");
		changedLines.add("ccc");
		changedLines.add(DiffUtil.OPEN_INS + "aee" + DiffUtil.CLOSE_INS);
		expectedTarget.add(new DiffResult(2, changedLines));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testNine() {
		StringReader reader1 = new StringReader("abcd");
		StringReader reader2 = new StringReader("abcdee");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(new DiffResult(0, "abcd"));

		expectedTarget.add(
			new DiffResult(
				0, "abcd" + DiffUtil.OPEN_INS + "ee" + DiffUtil.CLOSE_INS));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testTen() {
		StringReader reader1 = new StringReader("abcd");
		StringReader reader2 = new StringReader("abcdeee");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		expectedTarget.add(
			new DiffResult(
				0, DiffUtil.OPEN_INS + "abcdeee" + DiffUtil.CLOSE_INS));

		expectedSource.add(
			new DiffResult(0, DiffUtil.OPEN_DEL + "abcd" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testEleven() {
		StringReader reader1 = new StringReader("aaa\nbbb\nfff");
		StringReader reader2 = new StringReader("ccc\nada\nbeb");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(new DiffResult(0, DiffUtil.CONTEXT_LINE));

		expectedTarget.add(
			new DiffResult(
				0, DiffUtil.OPEN_INS + "ccc" + DiffUtil.CLOSE_INS));

		expectedSource.add(
			new DiffResult(
				0, "a" + DiffUtil.OPEN_DEL + "a" + DiffUtil.CLOSE_DEL + "a"));

		expectedTarget.add(
			new DiffResult(
				1, "a" + DiffUtil.OPEN_INS + "d" + DiffUtil.CLOSE_INS + "a"));

		expectedSource.add(
			new DiffResult(
				1, "b" + DiffUtil.OPEN_DEL + "b" + DiffUtil.CLOSE_DEL + "b"));

		expectedTarget.add(
			new DiffResult(
				2, "b" + DiffUtil.OPEN_INS + "e" + DiffUtil.CLOSE_INS + "b"));

		expectedSource.add(
			new DiffResult(2, DiffUtil.OPEN_DEL + "fff" + DiffUtil.CLOSE_DEL));

		expectedTarget.add(new DiffResult(2, DiffUtil.CONTEXT_LINE));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

	public void testTwelve() {
		StringReader reader1 = new StringReader("ada");
		StringReader reader2 = new StringReader("aaa\nccc");

		List[] results = DiffUtil.diff(reader1, reader2);

		List expectedSource = new ArrayList();
		List expectedTarget = new ArrayList();

		expectedSource.add(
			new DiffResult(
				0, "a" + DiffUtil.OPEN_DEL + "d" + DiffUtil.CLOSE_DEL + "a"));

		expectedTarget.add(
			new DiffResult(
				0, "a" + DiffUtil.OPEN_INS + "a" + DiffUtil.CLOSE_INS + "a"));

		expectedSource.add(new DiffResult(1, DiffUtil.CONTEXT_LINE));

		expectedTarget.add(
			new DiffResult(1, DiffUtil.OPEN_INS + "ccc" + DiffUtil.CLOSE_INS));

		assertEquals(results[0], expectedSource);
		assertEquals(results[1], expectedTarget);
	}

}