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

package com.liferay.portal.servlet;

import com.liferay.portal.service.spring.ThemeServiceUtil;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.velocity.VelocityContextPool;

import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ThemeContextListener.java.html"><b><i>View Source </i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.31 $
 *
 */
public class ThemeContextListener implements ServletContextListener {

	public void contextInitialized(ServletContextEvent sce) {
		try {
			ServletContext ctx = sce.getServletContext();

			_servletContextName = StringUtil.replace(
				ctx.getServletContextName(), StringPool.SPACE,
				StringPool.UNDERLINE);

			_log.debug("Servlet context name is " + _servletContextName);

			String[] xmls = new String[] {
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-look-and-feel.xml"))
			};

			_themeIds = ThemeServiceUtil.init(_servletContextName, xmls);

			VelocityContextPool.put(_servletContextName, ctx);
		}
		catch (Exception e2) {
			e2.printStackTrace();
		}
	}

	public void contextDestroyed(ServletContextEvent sce) {
		if (_themeIds != null) {
			Iterator itr = _themeIds.iterator();

			while (itr.hasNext()) {
				String themeId = (String)itr.next();

				try {
					ThemeServiceUtil.uninstallTheme(themeId);
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}

			_themeIds = null;
		}

		VelocityContextPool.remove(_servletContextName);
	}

	private static final Log _log =
		LogFactory.getLog(ThemeContextListener.class);

	private String _servletContextName;
	private List _themeIds;

}