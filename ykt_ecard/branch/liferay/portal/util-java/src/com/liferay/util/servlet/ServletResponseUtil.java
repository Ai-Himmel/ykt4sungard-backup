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

import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.FileUtil;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.servlet.http.HttpServletResponse;

import org.apache.commons.codec.net.URLCodec;
import org.apache.commons.lang.CharUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ServletResponseUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ServletResponseUtil {

	public static final String DEFAULT_CONTENT_TYPE =
		"application/octet-stream";

	public static void cleanUp(InputStream is) {
		try {
			if (is != null) {
				is.close();
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}
	}

	public static void cleanUp(OutputStream os) {
		try {
			if (os != null) {
				os.flush();
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		try {
			if (os != null) {
				os.close();
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}
	}

	public static void cleanUp(OutputStream os, InputStream is) {
		cleanUp(os);
		cleanUp(is);
	}

	public static void sendFile(
			HttpServletResponse res, String fileName, byte[] byteArray)
		throws IOException {

		sendFile(res, fileName, byteArray, null);
	}

	public static void sendFile(
			HttpServletResponse res, String fileName, byte[] byteArray,
			String contentType)
		throws IOException {

		setHeaders(res, fileName, contentType);

		write(res, byteArray);
	}

	public static void sendFile(
			HttpServletResponse res, String fileName, InputStream is)
		throws IOException {

		sendFile(res, fileName, is, null);
	}

	public static void sendFile(
			HttpServletResponse res, String fileName, InputStream is,
			String contentType)
		throws IOException {

		setHeaders(res, fileName, contentType);

		write(res, is);
	}

	public static void write(HttpServletResponse res, String s)
		throws IOException {

		write(res, s.getBytes("UTF-8"));
	}

	public static void write(HttpServletResponse res, byte[] byteArray)
		throws IOException {

		write(res, byteArray, 0);
	}

	public static void write(
			HttpServletResponse res, byte[] byteArray, int contentLength)
		throws IOException {

		OutputStream os = null;

		try {

			// LEP-3122

			if (!res.isCommitted() || ServerDetector.isPramati()) {

				// LEP-536

				if (contentLength == 0) {
					contentLength = byteArray.length;
				}

				res.setContentLength(contentLength);

				os = new BufferedOutputStream(res.getOutputStream());

				os.write(byteArray, 0, contentLength);
			}
		}
		finally {
			cleanUp(os);
		}
	}

	public static void write(HttpServletResponse res, InputStream is)
		throws IOException {

		OutputStream os = null;

		try {
			if (!res.isCommitted()) {
				os = new BufferedOutputStream(res.getOutputStream());

				int c = is.read();

				while (c != -1) {
					os.write(c);

					c = is.read();
				}
			}
		}
		finally {
			cleanUp(os, is);
		}
	}

	protected static void setHeaders(
			HttpServletResponse res, String fileName, String contentType)
		throws IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Sending file of type " + contentType);
		}

		// LEP-2201

		if (Validator.isNotNull(contentType)) {
			res.setContentType(contentType);
		}

		res.setHeader(HttpHeaders.CACHE_CONTROL, HttpHeaders.PUBLIC);
		res.setHeader(HttpHeaders.PRAGMA, HttpHeaders.PUBLIC);

		if (Validator.isNotNull(fileName)) {
			String contentDisposition =
				"attachment; filename=\"" + new String(fileName.getBytes("gb2312"), res.getCharacterEncoding()) + "\"";

			// If necessary for non-ASCII characters, encode based on RFC 2184.
			// However, not all browsers support RFC 2184. See LEP-3127.

//			boolean ascii = true;
//
//			for (int i = 0; i < fileName.length(); i++) {
//				if (!CharUtils.isAscii(fileName.charAt(i))) {
//					ascii = false;
//
//					break;
//				}
//			}
//
//			try {
//				if (!ascii) {
//					URLCodec codec = new URLCodec("UTF-8");
//
//					String encodedFileName =
//						StringUtil.replace(codec.encode(fileName), "+", "%20");
//
//					contentDisposition =
//						"attachment; filename*=UTF-8''" + encodedFileName;
//				}
//			}
//			catch (Exception e) {
//				if (_log.isWarnEnabled()) {
//					_log.warn(e);
//				}
//			}

			String extension = GetterUtil.getString(
				FileUtil.getExtension(fileName));

			if (extension.equals("pdf")) {
				contentDisposition = StringUtil.replace(
					contentDisposition, "attachment; ", "inline; ");
			}

			res.setHeader(HttpHeaders.CONTENT_DISPOSITION, contentDisposition);
		}
	}

	private static Log _log = LogFactory.getLog(ServletResponseUtil.class);

}