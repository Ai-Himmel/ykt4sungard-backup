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

package com.liferay.filters.compression;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServletResponseWrapper;

/**
 * <a href="CompressionResponse.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jayson Falkner
 * @author Brian Wing Shun Chan
 *
 */
public class CompressionResponse extends HttpServletResponseWrapper {

	public CompressionResponse(HttpServletResponse res) {
		super(res);

		_res = res;
	}

	public void finishResponse() {
		try {
			if (_writer != null) {
				_writer.close();
			}
			else if (_stream != null) {
				_stream.close();
			}
		}
		catch (IOException e) {
		}
	}

	public void flushBuffer() throws IOException {
		if (_stream != null) {
			_stream.flush();
		}
	}

	public ServletOutputStream getOutputStream() throws IOException {
		if (_writer != null) {
			throw new IllegalStateException();
		}

		if (_stream == null) {
			_stream = _createOutputStream();
		}

		return _stream;
	}

	public PrintWriter getWriter() throws IOException {
		if (_writer != null) {
			return _writer;
		}

		if (_stream != null) {
			throw new IllegalStateException();
		}

		_stream = _createOutputStream();

		_writer = new PrintWriter(new OutputStreamWriter(
			//_stream, _res.getCharacterEncoding()));
			_stream, CompressionFilter.ENCODING));

		return _writer;
	}

	private ServletOutputStream _createOutputStream() throws IOException {
		return new CompressionStream(_res);
	}

	private HttpServletResponse _res = null;
	private ServletOutputStream _stream = null;
	private PrintWriter _writer = null;

}