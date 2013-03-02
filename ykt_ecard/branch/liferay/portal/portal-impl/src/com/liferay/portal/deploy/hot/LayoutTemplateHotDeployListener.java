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
import com.liferay.portal.kernel.util.ObjectValuePair;
import com.liferay.portal.service.impl.LayoutTemplateLocalUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.Http;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LayoutTemplateHotDeployListener.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 * @author Ivica Cardic
 *
 */
public class LayoutTemplateHotDeployListener implements HotDeployListener {

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
					ctx.getResource("/WEB-INF/liferay-layout-templates.xml"))
			};

			if (xmls[0] == null) {
				return;
			}

			if (_log.isInfoEnabled()) {
				_log.info(
					"Registering layout templates for " + servletContextName);
			}

			List layoutTemplateIds = LayoutTemplateLocalUtil.init(
				servletContextName, ctx, xmls, event.getPluginPackage());

			_vars.put(servletContextName, layoutTemplateIds);

			if (_log.isInfoEnabled()) {
				_log.info(
					"Layout templates for " + servletContextName +
						" registered successfully");
			}
		}
		catch (Exception e) {
			throw new HotDeployException(
				"Error registering layout templates for " + servletContextName,
				e);
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

			List layoutTemplateIds = (List)_vars.get(servletContextName);

			if (layoutTemplateIds != null) {
				if (_log.isInfoEnabled()) {
					_log.info(
						"Unregistering layout templates for " +
							servletContextName);
				}

				Iterator itr = layoutTemplateIds.iterator();

				while (itr.hasNext()) {
					ObjectValuePair ovp = (ObjectValuePair)itr.next();

					String layoutTemplateId = (String)ovp.getKey();
					Boolean standard = (Boolean)ovp.getValue();

					try {
						LayoutTemplateLocalUtil.uninstallLayoutTemplate(
							layoutTemplateId, standard.booleanValue());
					}
					catch (Exception e1) {
						_log.error(e1.getMessage());
					}
				}

				layoutTemplateIds = null;

				if (_log.isInfoEnabled()) {
					_log.info(
						"Layout templates for " + servletContextName +
							" unregistered successfully");
				}
			}
		}
		catch (Exception e2) {
			throw new HotDeployException(
				"Error unregistering layout templates for " +
					servletContextName,
				e2);
		}
	}

	private static Log _log =
		LogFactory.getLog(LayoutTemplateHotDeployListener.class);

	private static Map _vars = CollectionFactory.getHashMap();

}