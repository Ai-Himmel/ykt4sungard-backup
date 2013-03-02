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

package com.liferay.util.servlet;

import com.liferay.util.servlet.fileupload.LiferayFileUpload;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.portlet.ActionRequest;
import javax.portlet.PortletSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ProgressInputStream.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class ProgressInputStream extends InputStream {

	public ProgressInputStream(ActionRequest req, InputStream is,
							   long totalSize, String progressId)
		throws IOException {

		_ses = req.getPortletSession();
		_is = is;
		_totalSize = totalSize;
		_progressId = progressId;

		initProgress();
	}

	public int available() throws IOException {
		return _is.available();
	}

	public void clearProgress() {
		_ses.removeAttribute(_getPercentAttributeName());
	}

	public void close() throws IOException {
		_is.close();
	}

	public long getTotalRead() {
		return _totalRead;
	}

	public void initProgress() {
		_ses.setAttribute(
			_getPercentAttributeName(), new Integer(0),
			PortletSession.APPLICATION_SCOPE);
	}

	public void mark(int readlimit) {
		_is.mark(readlimit);
	}

	public boolean markSupported() {
		return _is.markSupported();
	}

	public int read() throws IOException {
		return _is.read();
	}

	public int read(byte[] b) throws IOException {
		return read(b, 0, b.length);
	}

	public int read(byte[] b, int off, int len) throws IOException {
		int bytesRead = super.read(b, off, len);

		_updateProgress(bytesRead);

		return bytesRead;
	}

	public void readAll(OutputStream os) throws IOException {
		byte[] buffer = new byte[_DEFAULT_INITIAL_BUFFER_SIZE];

		int len = 0;

		while ((len = read(buffer)) > 0) {
			os.write(buffer, 0, len);
		}

		os.close();
	}

	public void reset() throws IOException {
		_is.reset();
	}

	public long skip(long n) throws IOException {
		long result = _is.skip(n);

		_updateProgress(result);

		return result;
	}

	private String _getPercentAttributeName() {
		return LiferayFileUpload.PERCENT + _progressId;
	}

	private void _updateProgress(long bytesRead) {
		if (bytesRead > 0) {
			_totalRead += bytesRead;
		}
		else {
			_totalRead = _totalSize;
		}

		int percent = (int) ((_totalRead * 100) / _totalSize);

		if (_log.isDebugEnabled()) {
			_log.debug(bytesRead + "/" + _totalRead + "=" + percent);
		}

		Integer curPercent = (Integer)_ses.getAttribute(
			_getPercentAttributeName(), PortletSession.APPLICATION_SCOPE);

		if ((curPercent == null) || (percent - curPercent.intValue() >= 1)) {
			_ses.setAttribute(
				_getPercentAttributeName(), new Integer(percent),
				PortletSession.APPLICATION_SCOPE);
		}
	}

	private static final int _DEFAULT_INITIAL_BUFFER_SIZE = 4 * 1024;

	private static Log _log = LogFactory.getLog(ProgressInputStream.class);

	private PortletSession _ses;
	private InputStream _is;
	private long _totalRead;
	private long _totalSize;
	private String _progressId;

}