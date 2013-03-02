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
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UserServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserServiceHttp {
	public static boolean addGroup(HttpPrincipal httpPrincipal,
		java.lang.String userId, com.liferay.portal.model.Group group)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = group;

			if (group == null) {
				paramObj1 = new NullWrapper("com.liferay.portal.model.Group");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addGroup", new Object[] { paramObj0, paramObj1 });
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

	public static boolean addRole(HttpPrincipal httpPrincipal,
		java.lang.String userId, com.liferay.portal.model.Role role)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = role;

			if (role == null) {
				paramObj1 = new NullWrapper("com.liferay.portal.model.Role");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addRole", new Object[] { paramObj0, paramObj1 });
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

	public static com.liferay.portal.model.User addUser(
		HttpPrincipal httpPrincipal, java.lang.String companyId,
		boolean autoUserId, java.lang.String userId, boolean autoPassword,
		java.lang.String password1, java.lang.String password2,
		boolean passwordReset, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String nickName, boolean male, java.util.Date birthday,
		java.lang.String emailAddress, java.util.Locale locale)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new BooleanWrapper(autoUserId);
			Object paramObj2 = userId;

			if (userId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new BooleanWrapper(autoPassword);
			Object paramObj4 = password1;

			if (password1 == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = password2;

			if (password2 == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = new BooleanWrapper(passwordReset);
			Object paramObj7 = firstName;

			if (firstName == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = middleName;

			if (middleName == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = lastName;

			if (lastName == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = nickName;

			if (nickName == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = new BooleanWrapper(male);
			Object paramObj12 = birthday;

			if (birthday == null) {
				paramObj12 = new NullWrapper("java.util.Date");
			}

			Object paramObj13 = emailAddress;

			if (emailAddress == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = locale;

			if (locale == null) {
				paramObj14 = new NullWrapper("java.util.Locale");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addUser",
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static int authenticateByEmailAddress(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String emailAddress,
		java.lang.String password)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = emailAddress;

			if (emailAddress == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = password;

			if (password == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"authenticateByEmailAddress",
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

	public static int authenticateByUserId(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String userId,
		java.lang.String password)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = userId;

			if (userId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = password;

			if (password == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"authenticateByUserId",
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

	public static com.liferay.util.KeyValuePair decryptUserId(
		HttpPrincipal httpPrincipal, java.lang.String companyId,
		java.lang.String userId, java.lang.String password)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = userId;

			if (userId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = password;

			if (password == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"decryptUserId",
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

			return (com.liferay.util.KeyValuePair)returnObj;
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

	public static boolean deleteGroup(HttpPrincipal httpPrincipal,
		java.lang.String userId, com.liferay.portal.model.Group group)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = group;

			if (group == null) {
				paramObj1 = new NullWrapper("com.liferay.portal.model.Group");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"deleteGroup", new Object[] { paramObj0, paramObj1 });
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

	public static boolean deleteRole(HttpPrincipal httpPrincipal,
		java.lang.String userId, com.liferay.portal.model.Role role)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = role;

			if (role == null) {
				paramObj1 = new NullWrapper("com.liferay.portal.model.Role");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"deleteRole", new Object[] { paramObj0, paramObj1 });
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

	public static void deleteUser(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"deleteUser", new Object[] { paramObj0 });
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

	public static java.lang.String encryptUserId(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"encryptUserId", new Object[] { paramObj0 });
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

			return (java.lang.String)returnObj;
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

	public static java.util.List findByAnd_C_FN_MN_LN_EA_M_BD_IM_A(
		HttpPrincipal httpPrincipal, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String emailAddress, java.lang.Boolean male,
		java.util.Date age1, java.util.Date age2, java.lang.String im,
		java.lang.String street1, java.lang.String street2,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String phone, java.lang.String fax, java.lang.String cell)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = firstName;

			if (firstName == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = middleName;

			if (middleName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = lastName;

			if (lastName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = emailAddress;

			if (emailAddress == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = male;

			if (male == null) {
				paramObj4 = new NullWrapper("java.lang.Boolean");
			}

			Object paramObj5 = age1;

			if (age1 == null) {
				paramObj5 = new NullWrapper("java.util.Date");
			}

			Object paramObj6 = age2;

			if (age2 == null) {
				paramObj6 = new NullWrapper("java.util.Date");
			}

			Object paramObj7 = im;

			if (im == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = street1;

			if (street1 == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = street2;

			if (street2 == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = city;

			if (city == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = state;

			if (state == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = zip;

			if (zip == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = phone;

			if (phone == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = fax;

			if (fax == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = cell;

			if (cell == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"findByAnd_C_FN_MN_LN_EA_M_BD_IM_A",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15
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

	public static java.util.List findByC_SMS(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"findByC_SMS", new Object[0]);
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

	public static java.util.List findByOr_C_FN_MN_LN_EA_M_BD_IM_A(
		HttpPrincipal httpPrincipal, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String emailAddress, java.lang.Boolean male,
		java.util.Date age1, java.util.Date age2, java.lang.String im,
		java.lang.String street1, java.lang.String street2,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String phone, java.lang.String fax, java.lang.String cell)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = firstName;

			if (firstName == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = middleName;

			if (middleName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = lastName;

			if (lastName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = emailAddress;

			if (emailAddress == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = male;

			if (male == null) {
				paramObj4 = new NullWrapper("java.lang.Boolean");
			}

			Object paramObj5 = age1;

			if (age1 == null) {
				paramObj5 = new NullWrapper("java.util.Date");
			}

			Object paramObj6 = age2;

			if (age2 == null) {
				paramObj6 = new NullWrapper("java.util.Date");
			}

			Object paramObj7 = im;

			if (im == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = street1;

			if (street1 == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = street2;

			if (street2 == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = city;

			if (city == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = state;

			if (state == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = zip;

			if (zip == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = phone;

			if (phone == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = fax;

			if (fax == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = cell;

			if (cell == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"findByOr_C_FN_MN_LN_EA_M_BD_IM_A",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15
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

	public static java.lang.String getCompanyId(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getCompanyId", new Object[] { paramObj0 });
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

			return (java.lang.String)returnObj;
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

	public static com.liferay.portal.model.User getDefaultUser(
		HttpPrincipal httpPrincipal, java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getDefaultUser", new Object[] { paramObj0 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static java.util.List getGroups(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getGroups", new Object[] { paramObj0 });
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

	public static java.util.List getGroups(HttpPrincipal httpPrincipal,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getGroups",
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

	public static int getGroupsSize(HttpPrincipal httpPrincipal,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getGroupsSize", new Object[] { paramObj0 });
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

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getLayouts(HttpPrincipal httpPrincipal,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getLayouts", new Object[] { paramObj0 });
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

	public static java.util.List getLayouts(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String parentLayoutId)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = parentLayoutId;

			if (parentLayoutId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getLayouts", new Object[] { paramObj0, paramObj1 });
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

	public static int getLayoutsSize(HttpPrincipal httpPrincipal,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getLayoutsSize", new Object[] { paramObj0 });
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

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getProjProjects(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getProjProjects", new Object[] { paramObj0 });
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

	public static java.util.List getProjTasks(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getProjTasks", new Object[] { paramObj0 });
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

	public static java.util.List getRoles(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getRoles", new Object[] { paramObj0 });
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

	public static java.util.List getRoles(HttpPrincipal httpPrincipal,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getRoles", new Object[] { paramObj0, paramObj1, paramObj2 });
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

	public static int getRolesSize(HttpPrincipal httpPrincipal,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getRolesSize", new Object[] { paramObj0 });
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

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portal.model.User getUserByEmailAddress(
		HttpPrincipal httpPrincipal, java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = emailAddress;

			if (emailAddress == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserByEmailAddress", new Object[] { paramObj0 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static com.liferay.portal.model.User getUserById(
		HttpPrincipal httpPrincipal, java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserById", new Object[] { paramObj0 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static com.liferay.portal.model.User getUserById(
		HttpPrincipal httpPrincipal, java.lang.String companyId,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = userId;

			if (userId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserById", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static java.lang.String getUserId(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = emailAddress;

			if (emailAddress == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserId", new Object[] { paramObj0, paramObj1 });
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

			return (java.lang.String)returnObj;
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

	public static int notifyNewUsers(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"notifyNewUsers", new Object[0]);
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

	public static void sendPassword(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = emailAddress;

			if (emailAddress == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"sendPassword", new Object[] { paramObj0, paramObj1 });
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

	public static void setGroups(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupIds;

			if (groupIds == null) {
				paramObj1 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setGroups", new Object[] { paramObj0, paramObj1 });
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

	public static void setLayouts(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String parentLayoutId,
		java.lang.String[] layoutIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = parentLayoutId;

			if (parentLayoutId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = layoutIds;

			if (layoutIds == null) {
				paramObj2 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setLayouts",
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

	public static void setProjProjects(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String[] projProjectIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = projProjectIds;

			if (projProjectIds == null) {
				paramObj1 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setProjProjects", new Object[] { paramObj0, paramObj1 });
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

	public static void setProjProjects(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.util.List projProjects)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = projProjects;

			if (projProjects == null) {
				paramObj1 = new NullWrapper("java.util.List");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setProjProjects", new Object[] { paramObj0, paramObj1 });
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

	public static void setProjTasks(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String[] projTaskIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = projTaskIds;

			if (projTaskIds == null) {
				paramObj1 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setProjTasks", new Object[] { paramObj0, paramObj1 });
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

	public static void setProjTasks(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.util.List projTasks)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = projTasks;

			if (projTasks == null) {
				paramObj1 = new NullWrapper("java.util.List");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setProjTasks", new Object[] { paramObj0, paramObj1 });
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

	public static void setRoles(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = roleIds;

			if (roleIds == null) {
				paramObj1 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setRoles", new Object[] { paramObj0, paramObj1 });
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

	public static com.liferay.portal.model.User updateActive(
		HttpPrincipal httpPrincipal, java.lang.String userId, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new BooleanWrapper(active);
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateActive", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static com.liferay.portal.model.User updateAgreedToTermsOfUse(
		HttpPrincipal httpPrincipal, boolean agreedToTermsOfUse)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new BooleanWrapper(agreedToTermsOfUse);
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateAgreedToTermsOfUse", new Object[] { paramObj0 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static com.liferay.portal.model.User updateLastLogin(
		HttpPrincipal httpPrincipal, java.lang.String loginIP)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = loginIP;

			if (loginIP == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateLastLogin", new Object[] { paramObj0 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static com.liferay.portal.model.User updateLookAndFeel(
		HttpPrincipal httpPrincipal, java.lang.String themeId,
		java.lang.String colorSchemeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = themeId;

			if (themeId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = colorSchemeId;

			if (colorSchemeId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateLookAndFeel", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static void updatePortrait(HttpPrincipal httpPrincipal,
		java.lang.String userId, byte[] bytes)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = bytes;

			if (bytes == null) {
				paramObj1 = new NullWrapper("[B");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updatePortrait", new Object[] { paramObj0, paramObj1 });
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

	public static com.liferay.portal.model.User updateUser(
		HttpPrincipal httpPrincipal, java.lang.String userId,
		java.lang.String password1, java.lang.String password2,
		boolean passwordReset)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = password1;

			if (password1 == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = password2;

			if (password2 == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new BooleanWrapper(passwordReset);
			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateUser",
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static com.liferay.portal.model.User updateUser(
		HttpPrincipal httpPrincipal, java.lang.String userId,
		java.lang.String password, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String nickName, boolean male, java.util.Date birthday,
		java.lang.String emailAddress, java.lang.String smsId,
		java.lang.String aimId, java.lang.String icqId, java.lang.String msnId,
		java.lang.String ymId, java.lang.String favoriteActivity,
		java.lang.String favoriteBibleVerse, java.lang.String favoriteFood,
		java.lang.String favoriteMovie, java.lang.String favoriteMusic,
		java.lang.String languageId, java.lang.String timeZoneId,
		java.lang.String themeId, java.lang.String colorSchemeId,
		java.lang.String greeting, java.lang.String resolution,
		java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = password;

			if (password == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = firstName;

			if (firstName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = middleName;

			if (middleName == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = lastName;

			if (lastName == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = nickName;

			if (nickName == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = new BooleanWrapper(male);
			Object paramObj7 = birthday;

			if (birthday == null) {
				paramObj7 = new NullWrapper("java.util.Date");
			}

			Object paramObj8 = emailAddress;

			if (emailAddress == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = smsId;

			if (smsId == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = aimId;

			if (aimId == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = icqId;

			if (icqId == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = msnId;

			if (msnId == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = ymId;

			if (ymId == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = favoriteActivity;

			if (favoriteActivity == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = favoriteBibleVerse;

			if (favoriteBibleVerse == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = favoriteFood;

			if (favoriteFood == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = favoriteMovie;

			if (favoriteMovie == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = favoriteMusic;

			if (favoriteMusic == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = languageId;

			if (languageId == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = timeZoneId;

			if (timeZoneId == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = themeId;

			if (themeId == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = colorSchemeId;

			if (colorSchemeId == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = greeting;

			if (greeting == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = resolution;

			if (resolution == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = comments;

			if (comments == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateUser",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25
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

			return (com.liferay.portal.model.User)returnObj;
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

	public static boolean hasAdmin(HttpPrincipal httpPrincipal,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"hasAdmin", new Object[] { paramObj0 });
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

	private static final Log _log = LogFactory.getLog(UserServiceHttp.class);
}