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

package com.liferay.portlet;

import com.liferay.portal.model.Portlet;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.portal.velocity.VelocityContextPool;
import com.liferay.util.CollectionFactory;

import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletContext;

import javax.servlet.ServletContext;

/**
 * <a href="PortletContextFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletContextFactory {

	public static PortletContext create(Portlet portlet, ServletContext ctx) {
		return _instance._create(portlet, ctx);
	}

	public static void destroy(Portlet portlet) {
		_instance._destroy(portlet);
	}

	private PortletContextFactory() {
		_pool = CollectionFactory.getSyncHashMap();
	}

	private PortletContext _create(Portlet portlet, ServletContext ctx) {
		Map portletContexts = (Map)_pool.get(portlet.getRootPortletId());

		if (portletContexts == null) {
			portletContexts = CollectionFactory.getSyncHashMap();

			_pool.put(portlet.getRootPortletId(), portletContexts);
		}

		PortletContext portletContext =
			(PortletContext)portletContexts.get(portlet.getPortletId());

		if (portletContext == null) {
			if (portlet.isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(portlet.getRootPortletId());

				//String mainPath = (String)ctx.getAttribute(WebKeys.MAIN_PATH);

				ctx = pcw.getServletContext();

				// Context path for the portal must be passed to individual
				// portlets

				//ctx.setAttribute(WebKeys.MAIN_PATH, mainPath);
			}

			portletContext = new PortletContextImpl(portlet, ctx);

			VelocityContextPool.put(
				portletContext.getPortletContextName(), ctx);

			portletContexts.put(portlet.getPortletId(), portletContext);
		}

		return portletContext;
	}

	private void _destroy(Portlet portlet) {
		Map portletContexts = (Map)_pool.remove(portlet.getRootPortletId());

		if (portletContexts == null) {
			return;
		}

		Iterator itr = portletContexts.entrySet().iterator();

		if (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			PortletContext portletContext = (PortletContext)entry.getValue();

			VelocityContextPool.remove(portletContext.getPortletContextName());
		}
	}

	private static PortletContextFactory _instance =
		new PortletContextFactory();

	private Map _pool;

}