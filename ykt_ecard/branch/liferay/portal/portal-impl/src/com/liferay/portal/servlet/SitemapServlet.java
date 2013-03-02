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

package com.liferay.portal.servlet;

import com.liferay.portal.NoSuchLayoutSetException;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.service.LayoutSetLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.SitemapUtil;

import java.io.IOException;
import java.io.OutputStreamWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="SitemapServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class SitemapServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		OutputStreamWriter out = null;

		try {
			String host = PortalUtil.getHost(req);

			long groupId = ParamUtil.getLong(req, "groupId");
			boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");

			LayoutSet layoutSet = null;

			if (groupId > 0) {
				layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(
					groupId, privateLayout);
			}
			else {
				layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(host);
			}

			String portalURL = PortalUtil.getPortalURL(
				host, req.getServerPort(), req.isSecure());

			String mainPath = PortalUtil.PATH_MAIN;

			String sitemap = SitemapUtil.getSitemap(
				layoutSet.getGroupId(), layoutSet.isPrivateLayout(),
				portalURL + mainPath);

			if (!res.isCommitted()) {
				res.setContentType(ContentTypes.TEXT_XML_UTF8);

				out = new OutputStreamWriter(res.getOutputStream());

				out.write(sitemap);
			}
		}
		catch (NoSuchLayoutSetException e) {
			PortalUtil.sendError(
				HttpServletResponse.SC_NOT_FOUND, e, req, res);
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e, e);
			}

			PortalUtil.sendError(
				HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e, req, res);
		}
		finally {
			if (out != null) {
				out.flush();
				out.close();
			}
		}
	}

	private static Log _log = LogFactory.getLog(SitemapServlet.class);

}