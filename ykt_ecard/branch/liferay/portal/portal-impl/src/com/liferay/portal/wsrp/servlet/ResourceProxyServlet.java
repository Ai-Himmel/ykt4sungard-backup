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

package com.liferay.portal.wsrp.servlet;

import com.liferay.portal.model.Company;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.util.Encryptor;

import java.io.InputStream;
import java.io.OutputStream;

import java.net.URL;
import java.net.URLConnection;

import java.security.Key;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.wsrp4j.producer.util.Base64;

/**
 * <a href="ResourceProxyServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class ResourceProxyServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res) {
		String targetUrl = req.getParameter("url");
		String cookie = req.getParameter("cookie");

		if (targetUrl != null) {
			try {
				long companyId = PortalInstances.getCompanyId(req);

				Company company = CompanyLocalServiceUtil.getCompanyById(
						companyId);

				Key key = company.getKeyObj();

				targetUrl = Encryptor.decryptRaw(key, Base64.decode(targetUrl));

				URL url = new URL(targetUrl);
				URLConnection con = url.openConnection();

				cookie = Encryptor.decryptRaw(key, Base64.decode(cookie));

				con.setRequestProperty("Cookie", cookie);

				con.connect();

				res.setContentType(con.getContentType());
				res.setContentLength(con.getContentLength());

				InputStream in = con.getInputStream();
				OutputStream out = res.getOutputStream();

				int next;

				while ((next = in.read()) != -1) {
					out.write(next);
				}

				out.flush();
				out.close();
			}
			catch (Exception e) {
				_log.warn(e);
			}
		}
	}

	private static Log _log = LogFactory.getLog(ResourceProxyServlet.class);

}