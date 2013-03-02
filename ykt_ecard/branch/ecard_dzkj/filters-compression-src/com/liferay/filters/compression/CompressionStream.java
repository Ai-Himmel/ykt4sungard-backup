/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.util.zip.GZIPOutputStream;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="CompressionStream.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Jayson Falkner
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class CompressionStream extends ServletOutputStream {

	public CompressionStream(HttpServletResponse res) throws IOException {
		super();

		_res = res;
		_output = res.getOutputStream();
		_bufferedOutput = new ByteArrayOutputStream();
		_closed = false;
	}

	public void close() throws IOException {
		if (_closed) {
			throw new IOException();
		}

		if (_bufferedOutput instanceof ByteArrayOutputStream) {
			ByteArrayOutputStream baos = (ByteArrayOutputStream)_bufferedOutput;

			ByteArrayOutputStream compressedContent =
				new ByteArrayOutputStream();

			GZIPOutputStream gzipOutput =
				new GZIPOutputStream(compressedContent);

			gzipOutput.write(baos.toByteArray());
			gzipOutput.finish();

			byte[] compressedBytes = compressedContent.toByteArray();

			_res.setContentLength(compressedBytes.length);
			_res.addHeader(_CONTENT_ENCODING, _GZIP);

			_output.write(compressedBytes);
			_output.flush();
			_output.close();

			_closed = true;
		}
		else if (_bufferedOutput instanceof GZIPOutputStream) {
			GZIPOutputStream gzipOutput = (GZIPOutputStream)_bufferedOutput;

			gzipOutput.finish();

			_output.flush();
			_output.close();

			_closed = true;
		}
	}

	public void flush() throws IOException {
		if (_closed) {
			throw new IOException();
		}

		_bufferedOutput.flush();
	}

	public void write(int b) throws IOException {
		if (_closed) {
			throw new IOException();
		}

		_checkBufferSize(1);

		_bufferedOutput.write((byte)b);
	}

	public void write(byte b[]) throws IOException {
		write(b, 0, b.length);
	}

	public void write(byte b[], int off, int len) throws IOException {
		if (_closed) {
			throw new IOException();
		}

		_checkBufferSize(len);

		_bufferedOutput.write(b, off, len);
	}

	public boolean closed() {
		return _closed;
	}

	public void reset() {
	}

	private void _checkBufferSize(int length) throws IOException {
		if (_bufferedOutput instanceof ByteArrayOutputStream) {
			ByteArrayOutputStream baos = (ByteArrayOutputStream)_bufferedOutput;

			if (baos.size() + length > _BUFFER_SIZE) {
				_res.addHeader(_CONTENT_ENCODING, _GZIP);

				GZIPOutputStream gzipOutput = new GZIPOutputStream(_output);

				gzipOutput.write(baos.toByteArray());

				_bufferedOutput = gzipOutput;
			}
		}
	}

	private static final String _CONTENT_ENCODING = "Content-Encoding";
	private static final String _GZIP = "gzip";
	private static final int _BUFFER_SIZE = 50000;

	private HttpServletResponse _res = null;
	private ServletOutputStream _output = null;
	private OutputStream _bufferedOutput = null;
	private boolean _closed = false;

}