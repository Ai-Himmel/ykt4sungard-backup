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

package com.objectparadigms.framework.ejbfactory;

import com.objectparadigms.framework.ejbfactory.config.EJBConfig;
import com.objectparadigms.framework.ejbfactory.config.EJBFactoryConfig;
import com.objectparadigms.framework.locator.LocatorException;
import com.objectparadigms.framework.locator.ServiceLocator;
import com.objectparadigms.framework.locator.ServiceLocatorFactory;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

import java.rmi.RemoteException;

import java.util.HashMap;
import java.util.Map;

import javax.ejb.EJBHome;
import javax.ejb.EJBObject;

/**
 * <a href="EJBFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael C. Han
 * @version $Revision: 1.5 $
 *
 */
public class EJBFactory {
	public static final String LOG_CATEGORY = EJBFactory.class.getName();
	private static EJBFactory instance;
	private EJBFactoryConfig config;
	private Map locators;
	private Map remoteCache;

	private EJBFactory() {
		config = EJBFactoryConfig.getInstance();
		locators = new HashMap();
		remoteCache = new HashMap();
	}

	public static synchronized EJBFactory getInstance() {
		if (instance == null) {
			instance = new EJBFactory();
		}

		return instance;
	}

	public EJBObject getRemote(String name) throws CreationException {
		return getRemote(name, 0);
	}

	public synchronized void clear() {
		locators.clear();
		remoteCache.clear();
	}

	public synchronized void remove(String name) {
		remoteCache.remove(name);
	}

	private EJBObject getRemote(String name, int numRetries)
		throws CreationException {
		EJBConfig ejb = config.getEJB(name);
		EJBObject obj = null;

		//if ejb is cacheable, attempt to resolve it from cache first
		if (ejb.isCachable()) {
			synchronized (this) {
				obj = (EJBObject)remoteCache.get(name);
			}

			if (obj != null) {
				return obj;
			}
		}

		//retrieve the locator for the proper EJB container
		String container = ejb.getContainerName();
		ServiceLocator locator = (ServiceLocator)locators.get(container);

		try {
			if (locator == null) {
				locator = ServiceLocatorFactory.getInstance().getLocator(config.getContainer(
							container).getJndiProps());

				synchronized (this) {
					locators.put(container, locator);
				}
			}

			//locate the EJBHome
			EJBHome home = locator.locateHome(name);
			Method method = ejb.getCreateMethod();
			obj = (EJBObject)method.invoke(home, new Object[0]);

			Class remoteClass = home.getEJBMetaData().getRemoteInterfaceClass();

			if (ejb.hasCustomProxy()) {
				Class customHandlerClass = ejb.getProxyClass();

				try {
					EJBInvocationHandler customHandler = (EJBInvocationHandler)customHandlerClass.newInstance();
					customHandler.setDelegate(obj);
					obj = (EJBObject)Proxy.newProxyInstance(remoteClass.getClassLoader(),
							new Class[] { remoteClass }, customHandler);
				}
				catch (Exception e) {
					throw new CreationException("Unable to instantiate custom proxy: ",
						e);
				}
			}

			if (ejb.isCachable()) {
				//if cacheable, we want a cached handler to remove the cached reference if we have a RemoteException
				InvocationHandler cachedHandler = new CachedRemoteHandle(obj,
						name);
				obj = (EJBObject)Proxy.newProxyInstance(remoteClass.getClassLoader(),
						new Class[] { remoteClass }, cachedHandler);

				synchronized (this) {
					remoteCache.put(name, obj);
				}
			}

			return obj;
		}
		catch (InvocationTargetException e) {
			return retry(name, locator, numRetries, e.getTargetException());
		}
		catch (LocatorException le) {
			return retry(name, locator, numRetries++, le);
		}
		catch (RemoteException re) {
			return retry(name, locator, numRetries++, re);
		}
		catch (IllegalAccessException iae) {
			throw new CreationException("Unable to create requested object: " +
				name, iae);
		}
	}

	private EJBObject retry(String name, ServiceLocator locator, int retries,
		Throwable e) throws CreationException {
		if (retries <= config.getRetries()) {
			try {
				//we need to retry, thus first flush the locator and then retry
				locator.flush();
			}
			catch (LocatorException le) {
				throw new CreationException("Unable to re-establish context: ",
					le);
			}

			return getRemote(name, retries++);
		}

		throw new CreationException("Unable to create requested object: " +
			name, e);
	}

	private class CachedRemoteHandle implements InvocationHandler {
		private Object delegate;
		private String name;

		public CachedRemoteHandle(Object delegate, String name) {
			this.name = name;
			this.delegate = delegate;
		}

		public Object invoke(Object proxy, Method method, Object[] args)
			throws Throwable {
			Object obj = null;

			try {
				obj = method.invoke(delegate, args);
			}
			catch (InvocationTargetException ite) {
				if (ite.getTargetException() instanceof RemoteException) {
					remove(name);
					throw ite.getTargetException();
				}
			}

			return obj;
		}
	}
}