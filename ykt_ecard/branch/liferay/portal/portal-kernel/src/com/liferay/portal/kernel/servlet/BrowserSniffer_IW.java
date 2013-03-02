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

package com.liferay.portal.kernel.servlet;

/**
 * <a href="BrowserSniffer_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BrowserSniffer_IW {
	public static BrowserSniffer_IW getInstance() {
		return _instance;
	}

	public boolean acceptsGzip(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.acceptsGzip(req);
	}

	public boolean is_ie(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie(req);
	}

	public boolean is_ie_4(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie_4(req);
	}

	public boolean is_ie_5(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie_5(req);
	}

	public boolean is_ie_5_5(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie_5_5(req);
	}

	public boolean is_ie_5_5_up(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie_5_5_up(req);
	}

	public boolean is_ie_6(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie_6(req);
	}

	public boolean is_ie_7(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ie_7(req);
	}

	public boolean is_linux(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_linux(req);
	}

	public boolean is_mozilla(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_mozilla(req);
	}

	public boolean is_mozilla_1_3_up(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_mozilla_1_3_up(req);
	}

	public boolean is_ns_4(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_ns_4(req);
	}

	public boolean is_rtf(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_rtf(req);
	}

	public boolean is_safari(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_safari(req);
	}

	public boolean is_wap_xhtml(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_wap_xhtml(req);
	}

	public boolean is_wml(javax.servlet.http.HttpServletRequest req) {
		return BrowserSniffer.is_wml(req);
	}

	private BrowserSniffer_IW() {
	}

	private static BrowserSniffer_IW _instance = new BrowserSniffer_IW();
}