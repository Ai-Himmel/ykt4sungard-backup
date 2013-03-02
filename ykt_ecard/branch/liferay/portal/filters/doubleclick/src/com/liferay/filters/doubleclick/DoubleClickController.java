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

package com.liferay.filters.doubleclick;

import com.liferay.util.servlet.filters.CacheResponse;
import com.liferay.util.servlet.filters.CacheResponseData;
import com.liferay.util.servlet.filters.CacheResponseUtil;

import java.io.IOException;
import java.io.Serializable;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="DoubleClickController.java.html"><b><i>View Source</i></b></a>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 *
 */
public class DoubleClickController implements Serializable {

	public void control(
			HttpServletRequest req, HttpServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		boolean firstRequest = false;

		CacheResponse cacheResponse = null;

		synchronized (this) {
			if (_cacheResponse == null) {
				firstRequest = true;

				_cacheResponse = new CacheResponse(
					res, DoubleClickFilter.ENCODING);
				_throwable = null;
			}

			cacheResponse = _cacheResponse;
		}

		if (firstRequest) {
			try {
				chain.doFilter(req, _cacheResponse);
			}
			catch (Throwable t) {
				_throwable = t;
			}
			finally {
				synchronized (this) {
					_cacheResponse = null;

					notifyAll();
				}
			}
		}
		else {
			synchronized (this) {
				while (_cacheResponse != null) {
					try {
						wait();
					}
					catch (InterruptedException ie) {
						Thread.currentThread().interrupt();
					}
				}
			}
		}

		if (_throwable != null) {
			try {
				throw _throwable;
			}
			catch (IOException ioe) {
				throw ioe;
			}
			catch (ServletException se) {
				throw se;
			}
			catch (RuntimeException re) {
				throw re;
			}
			catch (Error e) {
				throw e;
			}
			catch (Throwable t) {
				throw new RuntimeException(t);
			}
		}

		CacheResponseData data = new CacheResponseData(
			cacheResponse.getData(), cacheResponse.getContentType(),
			cacheResponse.getHeaders());

		CacheResponseUtil.write(res, data);
	}

    private CacheResponse _cacheResponse;
    private Throwable _throwable;

}