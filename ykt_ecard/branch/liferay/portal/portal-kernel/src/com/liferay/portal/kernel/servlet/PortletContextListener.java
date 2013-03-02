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

import com.liferay.portal.kernel.deploy.hot.HotDeployEvent;
import com.liferay.portal.kernel.deploy.hot.HotDeployUtil;
import com.liferay.portal.kernel.util.PortalInitable;
import com.liferay.portal.kernel.util.PortalInitableUtil;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

/**
 * <a href="PortletContextListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public class PortletContextListener
	implements PortalInitable, ServletContextListener {

	public void portalInit() {
		HotDeployUtil.fireDeployEvent(new HotDeployEvent(_ctx, _classLoader));
	}

	public void contextInitialized(ServletContextEvent event) {
		_classLoader = Thread.currentThread().getContextClassLoader();
		_ctx = event.getServletContext();

		PortalInitableUtil.init(this);
	}

	public void contextDestroyed(ServletContextEvent event) {
		HotDeployUtil.fireUndeployEvent(
			new HotDeployEvent(
				event.getServletContext(),
				Thread.currentThread().getContextClassLoader()));
	}

	private ClassLoader _classLoader;
	private ServletContext _ctx;

}