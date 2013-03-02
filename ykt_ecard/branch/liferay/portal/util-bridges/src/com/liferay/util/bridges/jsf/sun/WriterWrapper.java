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

package com.liferay.util.bridges.jsf.sun;

import com.liferay.portal.kernel.util.StringMaker;

import java.io.IOException;
import java.io.Writer;

/**
 * <a href="WriterWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Myunghun Kim
 *
 */
public class WriterWrapper extends Writer {

	public WriterWrapper(Writer writer) {
		_writer = writer;
	}

	public void close() throws IOException {
		_writer.close();
	}

	public void flush() throws IOException {
	}

	public void write(char cbuf) throws IOException {
		_writer.write(cbuf);
	}

	public void write(char[] cbuf, int off, int len) throws IOException {
		StringMaker sm = new StringMaker();

		sm.append(cbuf, off, len);

		_writer.write(sm.toString());
	}

	public void write(int c) throws IOException {
		_writer.write(c);
	}

	public void write(String str) throws IOException {
		_writer.write(str);
	}

	public void write(String str, int off, int len) throws IOException {
		_writer.write(str, off, len);
	}

	private Writer _writer;

}