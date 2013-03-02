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

package com.liferay.util.servlet.filters;

import com.liferay.portal.kernel.util.ByteArrayMaker;
import com.liferay.util.CollectionFactory;
import com.liferay.util.servlet.Header;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServletResponseWrapper;

/**
 * <a href="CacheResponse.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class CacheResponse extends HttpServletResponseWrapper {

	public CacheResponse(HttpServletResponse res, String encoding) {
		super(res);

		_encoding = encoding;
	}

	public void addDateHeader(String name, long value) {
		List values = (List)_headers.get(name);

		if (values == null) {
			values = new ArrayList();

			_headers.put(name, values);
		}

		Header header = new Header();

		header.setType(Header.DATE_TYPE);
		header.setDateValue(value);

		values.add(header);
	}

	public void addHeader(String name, String value) {
		List values = (List)_headers.get(name);

		if (values == null) {
			values = new ArrayList();

			_headers.put(name, values);
		}

		Header header = new Header();

		header.setType(Header.STRING_TYPE);
		header.setStringValue(value);

		values.add(header);
	}

	public void addIntHeader(String name, int value) {
		List values = (List)_headers.get(name);

		if (values == null) {
			values = new ArrayList();

			_headers.put(name, values);
		}

		Header header = new Header();

		header.setType(Header.INTEGER_TYPE);
		header.setIntValue(value);

		values.add(header);
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

	public String getContentType() {
		return _contentType;
	}

	public byte[] getData() {
		finishResponse();

		return _bam.toByteArray();
	}

	public Map getHeaders() {
		return _headers;
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
			_stream, _encoding));

		return _writer;
	}

	public boolean isCommitted() {
		if (_writer != null) {
			return true;
		}

		if ((_stream != null) && _stream.isClosed()) {
            return true;
        }

        return super.isCommitted();
    }

	public void setContentType(String contentType) {
		_contentType = contentType;

		super.setContentType(contentType);
	}

	public void setDateHeader(String name, long value) {
		List values = new ArrayList();

		_headers.put(name, values);

		Header header = new Header();

		header.setType(Header.DATE_TYPE);
		header.setDateValue(value);

		values.add(header);
	}

	public void setHeader(String name, String value) {
		List values = new ArrayList();

		_headers.put(name, values);

		Header header = new Header();

		header.setType(Header.STRING_TYPE);
		header.setStringValue(value);

		values.add(header);
	}

	public void setIntHeader(String name, int value) {
		List values = new ArrayList();

		_headers.put(name, values);

		Header header = new Header();

		header.setType(Header.INTEGER_TYPE);
		header.setIntValue(value);

		values.add(header);
	}

	private CacheResponseStream _createOutputStream() throws IOException {
		return new CacheResponseStream(_bam);
	}

	private String _encoding;
	private ByteArrayMaker _bam = new ByteArrayMaker();
	private CacheResponseStream _stream;
	private PrintWriter _writer;
	private String _contentType;
	private Map _headers = CollectionFactory.getHashMap();

}