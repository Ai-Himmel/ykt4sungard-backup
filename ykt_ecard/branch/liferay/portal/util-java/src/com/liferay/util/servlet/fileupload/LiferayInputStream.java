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

package com.liferay.util.servlet.fileupload;

import com.liferay.portal.kernel.util.ByteArrayMaker;
import com.liferay.util.servlet.ByteArrayInputStreamWrapper;
import com.liferay.util.servlet.ServletInputStreamWrapper;

import java.io.ByteArrayInputStream;
import java.io.IOException;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LiferayInputStream.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Myunghun Kim
 * @author Brian Wing Shun Chan
 * @author Harry Mark
 *
 */
public class LiferayInputStream extends ServletInputStreamWrapper {

	public LiferayInputStream(HttpServletRequest req) throws IOException {
		super(req.getInputStream());

		_ses = req.getSession();
		_totalSize = req.getContentLength();
	}

	public int read(byte[] b, int off, int len) throws IOException {
		int bytesRead = super.read(b, off, len);

		if (bytesRead > 0) {
			_totalRead += bytesRead;
		}
		else {
			_totalRead = _totalSize;
		}

		int percent = (_totalRead * 100) / _totalSize;

		if (_log.isDebugEnabled()) {
			_log.debug(bytesRead + "/" + _totalRead + "=" + percent);
		}

		_cachedBytes.write(b, off, bytesRead);

		Integer curPercent = (Integer)_ses.getAttribute(
			LiferayFileUpload.PERCENT);

		if ((curPercent == null) || (percent - curPercent.intValue() >= 1)) {
			_ses.setAttribute(LiferayFileUpload.PERCENT, new Integer(percent));
		}

		return bytesRead;
	}

	public ServletInputStream getCachedInputStream() throws IOException {
		return new ByteArrayInputStreamWrapper(
			new ByteArrayInputStream(_cachedBytes.toByteArray()));
	}

	private static Log _log = LogFactory.getLog(LiferayInputStream.class);

	private HttpSession _ses;
	private int _totalRead;
	private int _totalSize;
	private ByteArrayMaker _cachedBytes = new ByteArrayMaker();

}