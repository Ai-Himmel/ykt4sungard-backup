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

package com.liferay.portlet.network.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.network.service.spring.NetworkAddressServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.LongWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="NetworkAddressServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class NetworkAddressServiceHttp {
	public static com.liferay.portlet.network.model.NetworkAddress addAddress(
		HttpPrincipal httpPrincipal, java.lang.String name,
		java.lang.String url, java.lang.String comments,
		java.lang.String notifyBy, long interval, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = name;

			if (name == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = url;

			if (url == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = comments;

			if (comments == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = notifyBy;

			if (notifyBy == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new LongWrapper(interval);
			Object paramObj5 = new BooleanWrapper(active);
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"addAddress",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.network.model.NetworkAddress)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void checkAddress(HttpPrincipal httpPrincipal,
		com.liferay.portlet.network.model.NetworkAddress address)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = address;

			if (address == null) {
				paramObj0 = new NullWrapper(
						"com.liferay.portlet.network.model.NetworkAddress");
			}

			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"checkAddress", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void checkAddresses(HttpPrincipal httpPrincipal, long interval)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(interval);
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"checkAddresses", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void deleteAddress(HttpPrincipal httpPrincipal,
		java.lang.String addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"deleteAddress", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddress getAddress(
		HttpPrincipal httpPrincipal, java.lang.String addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"getAddress", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.network.model.NetworkAddress)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getAddresses(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"getAddresses", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getAddresses(HttpPrincipal httpPrincipal,
		long interval) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(interval);
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"getAddresses", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getAddresses(HttpPrincipal httpPrincipal,
		long interval, boolean active)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(interval);
			Object paramObj1 = new BooleanWrapper(active);
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"getAddresses", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static int getAddressesSize(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"getAddressesSize", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddress updateAddress(
		HttpPrincipal httpPrincipal, java.lang.String addressId,
		java.lang.String name, java.lang.String url, java.lang.String comments,
		java.lang.String notifyBy, long interval, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = name;

			if (name == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = url;

			if (url == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = comments;

			if (comments == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = notifyBy;

			if (notifyBy == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = new LongWrapper(interval);
			Object paramObj6 = new BooleanWrapper(active);
			MethodWrapper methodWrapper = new MethodWrapper(NetworkAddressServiceUtil.class.getName(),
					"updateAddress",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.network.model.NetworkAddress)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	private static final Log _log = LogFactory.getLog(NetworkAddressServiceHttp.class);
}