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

package com.liferay.portal.deploy.hot;

import com.liferay.portal.kernel.deploy.hot.HotDeployEvent;
import com.liferay.portal.kernel.deploy.hot.HotDeployException;
import com.liferay.portal.kernel.deploy.hot.HotDeployListener;
import com.liferay.portal.kernel.util.PortalClassLoaderUtil;
import com.liferay.portal.lastmodified.LastModifiedCSS;
import com.liferay.portal.lastmodified.LastModifiedJavaScript;
import com.liferay.portal.service.impl.ThemeLocalUtil;
import com.liferay.portal.velocity.LiferayResourceCacheUtil;
import com.liferay.portal.velocity.VelocityContextPool;
import com.liferay.util.CollectionFactory;
import com.liferay.util.Http;

import java.util.List;
import java.util.Map;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ThemeHotDeployListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 * @author Ivica Cardic
 *
 */
public class ThemeHotDeployListener implements HotDeployListener {

	public void invokeDeploy(HotDeployEvent event) throws HotDeployException {
		String servletContextName = null;

		try {
			ServletContext ctx = event.getServletContext();

			servletContextName = ctx.getServletContextName();

			if (_log.isDebugEnabled()) {
				_log.debug("Invoking deploy for " + servletContextName);
			}

			String[] xmls = new String[] {
				Http.URLtoString(
					ctx.getResource("/WEB-INF/liferay-look-and-feel.xml"))
			};

			if (xmls[0] == null) {
				return;
			}

			if (_log.isInfoEnabled()) {
				_log.info("Registering themes for " + servletContextName);
			}

			List themeIds = ThemeLocalUtil.init(
				servletContextName, ctx, null, true, xmls,
				event.getPluginPackage());

			VelocityContextPool.put(servletContextName, ctx);

			_vars.put(servletContextName, themeIds);

			if (_log.isInfoEnabled()) {
				_log.info(
					"Themes for " + servletContextName +
						" registered successfully");
			}
		}
		catch (Exception e) {
			throw new HotDeployException(
				"Error registering themes for " + servletContextName, e);
		}
	}

	public void invokeUndeploy(HotDeployEvent event) throws HotDeployException {
		String servletContextName = null;

		try {
			ServletContext ctx = event.getServletContext();

			servletContextName = ctx.getServletContextName();

			if (_log.isDebugEnabled()) {
				_log.debug("Invoking undeploy for " + servletContextName);
			}

			List themeIds = (List)_vars.remove(servletContextName);

			if (themeIds != null) {
				if (_log.isInfoEnabled()) {
					_log.info("Unregistering themes for " + servletContextName);
				}

				try {
					ThemeLocalUtil.uninstallThemes(themeIds);
				}
				catch (Exception e1) {
					_log.error(e1.getMessage());
				}
			}
			else {
				return;
			}

			// LEP-2057

			ClassLoader contextClassLoader =
				Thread.currentThread().getContextClassLoader();

			try {
				Thread.currentThread().setContextClassLoader(
					PortalClassLoaderUtil.getClassLoader());

				VelocityContextPool.remove(servletContextName);

				LiferayResourceCacheUtil.clear();

				LastModifiedCSS.clear();
				LastModifiedJavaScript.clear();
			}
			finally {
				Thread.currentThread().setContextClassLoader(
					contextClassLoader);
			}

			if (_log.isInfoEnabled()) {
				_log.info(
					"Themes for " + servletContextName +
						" unregistered successfully");
			}
		}
		catch (Exception e2) {
			throw new HotDeployException(
				"Error unregistering themes for " + servletContextName, e2);
		}
	}

	private static Log _log = LogFactory.getLog(ThemeHotDeployListener.class);

	private static Map _vars = CollectionFactory.getHashMap();

}