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

package com.liferay.portal.spring;

import com.objectparadigms.framework.locator.LocatorException;
import com.objectparadigms.framework.locator.ServiceLocator;
import com.objectparadigms.framework.locator.ServiceLocatorFactory;

import javax.naming.NamingException;

import org.springframework.ejb.access.LocalStatelessSessionProxyFactoryBean;

/**
 * <a href="LocalSessionFactoryBean.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Rev: $
 *
 */
public class LocalSessionFactoryBean
	extends LocalStatelessSessionProxyFactoryBean {

	protected void refreshHome() throws NamingException {
		try {
			ServiceLocator serviceLocator = _getServiceLocator();

			serviceLocator.flush();
		}
		catch (LocatorException le) {
			throw _getNamingException(le);
		}

		super.refreshHome();
	}

	protected Object lookup() throws NamingException {
		try {
			ServiceLocator serviceLocator = _getServiceLocator();

			return serviceLocator.locateLocalHome(getJndiName());
		}
		catch (LocatorException le) {
			throw _getNamingException(le);
		}
	}

	private NamingException _getNamingException(LocatorException le) {
		Throwable cause = le.getCause();

		NamingException ne = null;

		if (cause instanceof NamingException) {
			ne = (NamingException)cause;
		}
		else {
			ne = new NamingException(le.getMessage());

			ne.setRootCause(cause);
		}

		return ne;
	}

	private ServiceLocator _getServiceLocator() throws LocatorException {
		ServiceLocatorFactory serviceLocatorFactory =
			ServiceLocatorFactory.getInstance();

		ServiceLocator serviceLocator = serviceLocatorFactory.getLocator();

		return serviceLocator;
	}

}