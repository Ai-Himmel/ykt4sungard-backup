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

package com.liferay.portlet;

import com.liferay.portal.model.Portlet;
import com.liferay.util.CollectionFactory;

import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;

import javax.servlet.ServletContext;

/**
 * <a href="PortletConfigFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class PortletConfigFactory {

	public static PortletConfig create(Portlet portlet, ServletContext ctx) {
		return _instance._create(portlet, ctx);
	}

	public static void destroy(Portlet portlet) {
		_instance._destroy(portlet);
	}

	private PortletConfigFactory() {
		_pool = CollectionFactory.getSyncHashMap();
	}

	private PortletConfig _create(Portlet portlet, ServletContext ctx) {
		String poolId = PortletConfigFactory.class.getName();
		if (!portlet.isWARFile()) {
			poolId += "." + portlet.getCompanyId();
		}

		Map map = (Map)_pool.get(poolId);

		if (map == null) {
			map = CollectionFactory.getSyncHashMap();

			_pool.put(poolId, map);
		}

		Map portletConfigs = (Map)map.get(portlet.getRootPortletId());

		if (portletConfigs == null) {
			portletConfigs = CollectionFactory.getSyncHashMap();

			map.put(portlet.getRootPortletId(), portletConfigs);
		}

		PortletConfig portletConfig =
			(PortletConfig)portletConfigs.get(portlet.getPortletId());

		if (portletConfig == null) {
			PortletContext portletCtx =
				PortletContextFactory.create(portlet, ctx);

			portletConfig = new PortletConfigImpl(
				portlet.getPortletId(), portletCtx, portlet.getInitParams(),
				portlet.getResourceBundle(), portlet.getPortletInfo());

			portletConfigs.put(portlet.getPortletId(), portletConfig);
		}

		return portletConfig;
	}

	private void _destroy(Portlet portlet) {
		String poolId = PortletConfigFactory.class.getName();
		if (!portlet.isWARFile()) {
			poolId += "." + portlet.getCompanyId();
		}

		Map map = (Map)_pool.get(poolId);

		if (map == null) {
			return;
		}

		map.remove(portlet.getRootPortletId());
	}

	private static PortletConfigFactory _instance = new PortletConfigFactory();

	private Map _pool;

}