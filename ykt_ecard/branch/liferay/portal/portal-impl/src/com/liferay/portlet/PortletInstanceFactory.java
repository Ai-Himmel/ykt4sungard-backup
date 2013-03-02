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
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.util.CollectionFactory;

import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletException;
import javax.portlet.UnavailableException;

import javax.servlet.ServletContext;

/**
 * <a href="PortletInstanceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
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

		boolean instanceable = false;

		if ((portlet.isInstanceable()) &&
			(PortletImpl.getInstanceId(portlet.getPortletId()) != null)) {

			instanceable = true;
		}

		Map portletInstances = (Map)_pool.get(portlet.getRootPortletId());

		if (portletInstances == null) {
			portletInstances = CollectionFactory.getSyncHashMap();

			_pool.put(portlet.getRootPortletId(), portletInstances);
		}

		CachePortlet instanceCachePortletInstance = null;

		if (instanceable) {
			instanceCachePortletInstance = (CachePortlet)portletInstances.get(
				portlet.getPortletId());
		}

		CachePortlet rootCachePortletInstance = null;

		if (instanceCachePortletInstance == null) {
			rootCachePortletInstance = (CachePortlet)portletInstances.get(
				portlet.getRootPortletId());

			if (rootCachePortletInstance == null) {
				PortletConfig portletConfig =
					PortletConfigFactory.create(portlet, ctx);

				if (portlet.isWARFile()) {
					PortletContextWrapper pcw =
						PortletContextPool.get(portlet.getRootPortletId());

					rootCachePortletInstance = _init(
						portlet, portletConfig, pcw.getPortletInstance());
				}
				else {
					rootCachePortletInstance = _init(portlet, portletConfig);
				}

				portletInstances.put(
					portlet.getRootPortletId(), rootCachePortletInstance);
			}
		}

		if (instanceable) {
			if (instanceCachePortletInstance == null) {
				javax.portlet.Portlet portletInstance =
					rootCachePortletInstance.getPortletInstance();

				PortletConfig portletConfig =
					PortletConfigFactory.create(portlet, ctx);

				PortletContext portletCtx = portletConfig.getPortletContext();
				Integer expCache = rootCachePortletInstance.getExpCache();
				boolean facesPortlet =
					rootCachePortletInstance.isFacesPortlet();
				boolean strutsPortlet =
					rootCachePortletInstance.isStrutsPortlet();
				boolean strutsBridgePortlet =
					rootCachePortletInstance.isStrutsBridgePortlet();

				instanceCachePortletInstance = new CachePortlet(
					portletInstance, portletConfig, portletCtx, expCache,
					facesPortlet, strutsPortlet, strutsBridgePortlet);

				portletInstances.put(
					portlet.getPortletId(), instanceCachePortletInstance);
			}
		}
		else {
			if (rootCachePortletInstance != null) {
				instanceCachePortletInstance = rootCachePortletInstance;
			}
		}

		return instanceCachePortletInstance;
	}

	private void _destroy(Portlet portlet) {
		Map portletInstances = (Map)_pool.get(portlet.getRootPortletId());

		if (portletInstances == null) {
			return;
		}

		Iterator itr = portletInstances.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String portletId = (String)entry.getKey();
			CachePortlet cachePortletInstance = (CachePortlet)entry.getValue();

			if (PortletImpl.getInstanceId(portletId) == null) {
				cachePortletInstance.destroy();

				break;
			}
		}

		_pool.remove(portlet.getRootPortletId());

		if (portlet.isWARFile()) {
			PortletContextWrapper pcw =
				(PortletContextWrapper)PortletContextPool.get(
					portlet.getRootPortletId());

			pcw.removePortletInstance();
		}

		PortletConfigFactory.destroy(portlet);
		PortletContextFactory.destroy(portlet);

		PortletLocalServiceUtil.destroyPortlet(portlet);
	}

	private CachePortlet _init(Portlet portlet, PortletConfig portletConfig)
		throws PortletException {

		return _init(portlet, portletConfig, null);
	}

	private CachePortlet _init(
			Portlet portlet, PortletConfig portletConfig,
			javax.portlet.Portlet portletInstance)
		throws PortletException {

		CachePortlet cachePortlet = null;

		try {
			if (portletInstance == null) {
				portletInstance = (javax.portlet.Portlet)
					Class.forName(portlet.getPortletClass()).newInstance();
			}

			cachePortlet = new CachePortlet(
				portletInstance, portletConfig.getPortletContext(),
				portlet.getExpCache());

			cachePortlet.init(portletConfig);
		}
		catch (ClassNotFoundException cnofe) {
			throw new UnavailableException(cnofe.getMessage());
		}
		catch (InstantiationException ie) {
			throw new UnavailableException(ie.getMessage());
		}
		catch (IllegalAccessException iae) {
			throw new UnavailableException(iae.getMessage());
		}

		return cachePortlet;
	}

	private static PortletInstanceFactory _instance =
		new PortletInstanceFactory();

	private Map _pool;

}