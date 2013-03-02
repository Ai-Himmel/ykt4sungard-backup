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
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.util.CollectionFactory;

import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletException;

import javax.servlet.ServletContext;

/**
 * <a href="PortletInstanceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class PortletInstanceFactory {

	public static CachePortlet create(Portlet portlet, ServletContext ctx)
		throws PortletException {

		return _instance._create(portlet, ctx);
	}

	public static void destroy(Portlet portlet) {
		_instance._destroy(portlet);
	}

	private PortletInstanceFactory() {
		_pool = CollectionFactory.getSyncHashMap();
	}

	private CachePortlet _create(Portlet portlet, ServletContext ctx)
		throws PortletException {

		String poolId = PortletInstanceFactory.class.getName();
		if (!portlet.isWARFile()) {
			poolId += "." + portlet.getCompanyId();
		}

		Map map = (Map)_pool.get(poolId);

		if (map == null) {
			map = CollectionFactory.getSyncHashMap();

			_pool.put(poolId, map);
		}

		Map portletInstances = (Map)map.get(portlet.getRootPortletId());

		if (portletInstances == null) {
			portletInstances = CollectionFactory.getSyncHashMap();

			map.put(portlet.getRootPortletId(), portletInstances);
		}

		CachePortlet portletInstance =
			(CachePortlet)portletInstances.get(portlet.getPortletId());

		if (portletInstance == null) {
			PortletConfig portletConfig =
				PortletConfigFactory.create(portlet, ctx);

			if (portlet.isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(portlet.getRootPortletId());

				portletInstance = portlet.init(
					portletConfig, pcw.getPortletInstance());
			}
			else {
				portletInstance = portlet.init(portletConfig);
			}

			portletInstances.put(portlet.getPortletId(), portletInstance);
		}

		return portletInstance;
	}

	private void _destroy(Portlet portlet) {
		String poolId = PortletInstanceFactory.class.getName();
		if (!portlet.isWARFile()) {
			poolId += "." + portlet.getCompanyId();
		}

		Map map = (Map)_pool.get(poolId);

		if (map == null) {
			return;
		}

		Map portletInstances = (Map)map.get(portlet.getRootPortletId());

		if (portletInstances == null) {
			return;
		}

		Iterator itr = portletInstances.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String portletId = (String)entry.getKey();
			CachePortlet portletInstance = (CachePortlet)entry.getValue();

			portletInstance.destroy();
		}

		map.remove(portlet.getRootPortletId());

		if (portlet.isWARFile()) {
			PortletContextWrapper pcw =
				(PortletContextWrapper)PortletContextPool.get(
					portlet.getRootPortletId());

			pcw.removePortletInstance();
		}

		PortletConfigFactory.destroy(portlet);
		PortletContextFactory.destroy(portlet);
	}

	private static PortletInstanceFactory _instance =
		new PortletInstanceFactory();

	private Map _pool;

}