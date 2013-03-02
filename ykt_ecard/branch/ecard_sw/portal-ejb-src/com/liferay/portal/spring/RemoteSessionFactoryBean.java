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

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.StringPool;

import com.objectparadigms.framework.locator.LocatorException;
import com.objectparadigms.framework.locator.ServiceLocator;
import com.objectparadigms.framework.locator.ServiceLocatorFactory;

import java.util.Properties;

import javax.naming.Context;
import javax.naming.NamingException;

import org.springframework.ejb.access.SimpleRemoteStatelessSessionProxyFactoryBean;

/**
 * <a href="RemoteSessionFactoryBean.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Rev: $
 *
 */
public class RemoteSessionFactoryBean
	extends SimpleRemoteStatelessSessionProxyFactoryBean {

	public void setJndiName(String jndiName) {
		super.setJndiName(jndiName);

		String applet = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.APPLET);

		String authoritative = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.AUTHORITATIVE);

		String batchsize = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.BATCHSIZE);

		String dnsUrl = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.DNS_URL);

		String initialContextFactory = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.INITIAL_CONTEXT_FACTORY);

		String language = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.LANGUAGE);

		String objectFactories = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.OBJECT_FACTORIES);

		String providerUrl = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.PROVIDER_URL);

		String referral = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.REFERRAL);

		String securityAuthentication = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.SECURITY_AUTHENTICATION);

		String securityCredentials = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.SECURITY_CREDENTIALS);

		String securityPrincipal = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.SECURITY_PRINCIPAL);

		String securityProtocol = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.SECURITY_PROTOCOL);

		String stateFactories = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.STATE_FACTORIES);

		String urlPkgPrefixes = PropsUtil.get(
			jndiName + StringPool.UNDERLINE + Context.URL_PKG_PREFIXES);

		if (applet != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.APPLET, applet);
		}

		if (authoritative != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.AUTHORITATIVE, authoritative);
		}

		if (batchsize != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.BATCHSIZE, batchsize);
		}

		if (dnsUrl != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.DNS_URL, dnsUrl);
		}

		if (initialContextFactory != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(
				Context.INITIAL_CONTEXT_FACTORY, initialContextFactory);
		}

		if (language != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.LANGUAGE, language);
		}

		if (objectFactories != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.OBJECT_FACTORIES, objectFactories);
		}

		if (providerUrl != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.PROVIDER_URL, providerUrl);
		}

		if (referral != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.REFERRAL, referral);
		}

		if (securityAuthentication != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(
				Context.SECURITY_AUTHENTICATION, securityAuthentication);
		}

		if (securityCredentials != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(
				Context.SECURITY_CREDENTIALS, securityCredentials);
		}

		if (securityPrincipal != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.SECURITY_PRINCIPAL, securityPrincipal);
		}

		if (securityProtocol != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.SECURITY_PROTOCOL, securityProtocol);
		}

		if (stateFactories != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.STATE_FACTORIES, stateFactories);
		}

		if (urlPkgPrefixes != null) {
			if (_props == null) {
				_props = new Properties();
			}

			_props.setProperty(Context.URL_PKG_PREFIXES, urlPkgPrefixes);
		}

		setRefreshHomeOnConnectFailure(true);
	}

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

			return serviceLocator.locateHome(getJndiName());
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

		ServiceLocator serviceLocator = null;

		if (_props != null) {
			serviceLocator = serviceLocatorFactory.getLocator(_props);
		}
		else {
			serviceLocator = serviceLocatorFactory.getLocator();
		}

		return serviceLocator;
	}

	private Properties _props;

}