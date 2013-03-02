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

package com.liferay.portlet.blogs.servlet;

import com.liferay.portal.model.Company;
import com.liferay.portal.service.spring.CompanyLocalServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;

import java.io.IOException;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="BlogsServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class BlogsServlet extends HttpServlet {

	public void init(ServletConfig sc) throws ServletException {
		synchronized (BlogsServlet.class) {
			super.init(sc);

			ServletContext ctx = getServletContext();

			_companyId = ctx.getInitParameter("company_id");

			try {
				_company = CompanyLocalServiceUtil.getCompany(_companyId);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			String rootPath = GetterUtil.getString(
				ctx.getInitParameter("root_path"), StringPool.SLASH);
			if (rootPath.equals(StringPool.SLASH)) {
				rootPath = StringPool.BLANK;
			}

			_mainPath = rootPath + "/c";
		}
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		try {
			String blogsUserId = ParamUtil.getString(req, "blogs_user_id");
			String categoryId = ParamUtil.getString(req, "category_id");
			String type = ParamUtil.getString(req, "type");

			String findEntryUrl =
				"http://" + _company.getPortalURL() + _mainPath +
					"/blogs/find_entry?";

			String entriesXml = BlogsEntryServiceUtil.getEntriesXML(
				blogsUserId, categoryId, type, 0, 20, findEntryUrl);

			res.setContentType(Constants.TEXT_XML);

			res.getOutputStream().print(entriesXml);
			res.getOutputStream().flush();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private String _companyId;
	private Company _company;
	private String _mainPath;

}