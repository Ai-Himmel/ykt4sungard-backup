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

package com.liferay.portal.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.service.spring.AddressServiceUtil;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="AddressServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class AddressServiceHttp {
	public static com.liferay.portal.model.Address addAddress(
		HttpPrincipal httpPrincipal, java.lang.String userId,
		java.lang.String className, java.lang.String classPK,
		java.lang.String description, java.lang.String street1,
		java.lang.String street2, java.lang.String city,
		java.lang.String state, java.lang.String zip, java.lang.String country,
		java.lang.String phone, java.lang.String fax, java.lang.String cell,
		java.lang.String pager, java.lang.String tollFree)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = className;

			if (className == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = classPK;

			if (classPK == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = description;

			if (description == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = street1;

			if (street1 == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = street2;

			if (street2 == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = city;

			if (city == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = state;

			if (state == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = zip;

			if (zip == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = country;

			if (country == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = phone;

			if (phone == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = fax;

			if (fax == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = cell;

			if (cell == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = pager;

			if (pager == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = tollFree;

			if (tollFree == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"addAddress",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14
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

			return (com.liferay.portal.model.Address)returnObj;
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

	public static void deleteAddress(HttpPrincipal httpPrincipal,
		java.lang.String addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
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

	public static com.liferay.portal.model.Address getAddress(
		HttpPrincipal httpPrincipal, java.lang.String addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
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

			return (com.liferay.portal.model.Address)returnObj;
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
		java.lang.String className, java.lang.String classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = className;

			if (className == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = classPK;

			if (classPK == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"getAddresses", new Object[] { paramObj0, paramObj1 });
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

	public static com.liferay.portal.model.Address getPrimaryAddress(
		HttpPrincipal httpPrincipal, java.lang.String className,
		java.lang.String classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = className;

			if (className == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = classPK;

			if (classPK == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"getPrimaryAddress", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portal.model.Address)returnObj;
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

	public static com.liferay.portal.model.Address updateAddress(
		HttpPrincipal httpPrincipal, java.lang.String addressId,
		java.lang.String description, java.lang.String street1,
		java.lang.String street2, java.lang.String city,
		java.lang.String state, java.lang.String zip, java.lang.String country,
		java.lang.String phone, java.lang.String fax, java.lang.String cell,
		java.lang.String pager, java.lang.String tollFree)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = description;

			if (description == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = street1;

			if (street1 == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = street2;

			if (street2 == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = city;

			if (city == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = state;

			if (state == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = zip;

			if (zip == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = country;

			if (country == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = phone;

			if (phone == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = fax;

			if (fax == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = cell;

			if (cell == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = pager;

			if (pager == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = tollFree;

			if (tollFree == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"updateAddress",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12
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

			return (com.liferay.portal.model.Address)returnObj;
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

	public static void updateAddresses(HttpPrincipal httpPrincipal,
		java.lang.String className, java.lang.String classPK,
		java.lang.String[] addressIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = className;

			if (className == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = classPK;

			if (classPK == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = addressIds;

			if (addressIds == null) {
				paramObj2 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"updateAddresses",
					new Object[] { paramObj0, paramObj1, paramObj2 });
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

	public static void updateAddressPriority(HttpPrincipal httpPrincipal,
		java.lang.String className, java.lang.String classPK,
		java.lang.String addressId, boolean priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = className;

			if (className == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = classPK;

			if (classPK == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = addressId;

			if (addressId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new BooleanWrapper(priority);
			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"updateAddressPriority",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });
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

	public static boolean hasWrite(HttpPrincipal httpPrincipal,
		java.lang.String addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = addressId;

			if (addressId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AddressServiceUtil.class.getName(),
					"hasWrite", new Object[] { paramObj0 });
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

			return ((Boolean)returnObj).booleanValue();
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

	private static final Log _log = LogFactory.getLog(AddressServiceHttp.class);
}