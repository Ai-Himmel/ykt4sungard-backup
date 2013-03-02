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

package com.liferay.portal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.UserServiceUtil;

/**
 * <a href="UserServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portal.service.UserServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it requires an
 * additional <code>com.liferay.portal.security.auth.HttpPrincipal</code>
 * parameter.
 * </p>
 *
 * <p>
 * The benefits of using the HTTP utility is that it is fast and allows for
 * tunneling without the cost of serializing to text. The drawback is that it
 * only works with Java.
 * </p>
 *
 * <p>
 * Set the property <code>tunnel.servlet.hosts.allowed</code> in
 * portal.properties to configure security.
 * </p>
 *
 * <p>
 * The HTTP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.security.auth.HttpPrincipal
 * @see com.liferay.portal.service.UserServiceUtil
 * @see com.liferay.portal.service.http.UserServiceSoap
 *
 */
public class UserServiceHttp {
	public static void addGroupUsers(HttpPrincipal httpPrincipal, long groupId,
		long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addGroupUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void addOrganizationUsers(HttpPrincipal httpPrincipal,
		long organizationId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(organizationId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addOrganizationUsers",
					new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void addPasswordPolicyUsers(HttpPrincipal httpPrincipal,
		long passwordPolicyId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(passwordPolicyId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addPasswordPolicyUsers",
					new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void addRoleUsers(HttpPrincipal httpPrincipal, long roleId,
		long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(roleId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addRoleUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void addUserGroupUsers(HttpPrincipal httpPrincipal,
		long userGroupId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userGroupId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addUserGroupUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User addUser(
		HttpPrincipal httpPrincipal, long companyId, boolean autoPassword,
		java.lang.String password1, java.lang.String password2,
		boolean autoScreenName, java.lang.String screenName,
		java.lang.String emailAddress, java.util.Locale locale,
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, int prefixId, int suffixId, boolean male,
		int birthdayMonth, int birthdayDay, int birthdayYear,
		java.lang.String jobTitle, long[] organizationIds, boolean sendEmail)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = new BooleanWrapper(autoPassword);

			Object paramObj2 = password1;

			if (password1 == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = password2;

			if (password2 == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(autoScreenName);

			Object paramObj5 = screenName;

			if (screenName == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = emailAddress;

			if (emailAddress == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = locale;

			if (locale == null) {
				paramObj7 = new NullWrapper("java.util.Locale");
			}

			Object paramObj8 = firstName;

			if (firstName == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = middleName;

			if (middleName == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = lastName;

			if (lastName == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = new IntegerWrapper(prefixId);

			Object paramObj12 = new IntegerWrapper(suffixId);

			Object paramObj13 = new BooleanWrapper(male);

			Object paramObj14 = new IntegerWrapper(birthdayMonth);

			Object paramObj15 = new IntegerWrapper(birthdayDay);

			Object paramObj16 = new IntegerWrapper(birthdayYear);

			Object paramObj17 = jobTitle;

			if (jobTitle == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = organizationIds;

			if (organizationIds == null) {
				paramObj18 = new NullWrapper("[J");
			}

			Object paramObj19 = new BooleanWrapper(sendEmail);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"addUser",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deleteRoleUser(HttpPrincipal httpPrincipal, long roleId,
		long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(roleId);

			Object paramObj1 = new LongWrapper(userId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"deleteRoleUser", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deleteUser(HttpPrincipal httpPrincipal, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"deleteUser", new Object[] { paramObj0 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static long getDefaultUserId(HttpPrincipal httpPrincipal,
		long companyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getDefaultUserId", new Object[] { paramObj0 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return ((Long)returnObj).longValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static java.util.List getGroupUsers(HttpPrincipal httpPrincipal,
		long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getGroupUsers", new Object[] { paramObj0 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static java.util.List getRoleUsers(HttpPrincipal httpPrincipal,
		long roleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(roleId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getRoleUsers", new Object[] { paramObj0 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User getUserByEmailAddress(
		HttpPrincipal httpPrincipal, long companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = emailAddress;

			if (emailAddress == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserByEmailAddress",
					new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User getUserById(
		HttpPrincipal httpPrincipal, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserById", new Object[] { paramObj0 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User getUserByScreenName(
		HttpPrincipal httpPrincipal, long companyId, java.lang.String screenName)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = screenName;

			if (screenName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserByScreenName", new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static long getUserIdByEmailAddress(HttpPrincipal httpPrincipal,
		long companyId, java.lang.String emailAddress)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = emailAddress;

			if (emailAddress == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserIdByEmailAddress",
					new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return ((Long)returnObj).longValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static long getUserIdByScreenName(HttpPrincipal httpPrincipal,
		long companyId, java.lang.String screenName)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = screenName;

			if (screenName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"getUserIdByScreenName",
					new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return ((Long)returnObj).longValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static boolean hasGroupUser(HttpPrincipal httpPrincipal,
		long groupId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new LongWrapper(userId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"hasGroupUser", new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static boolean hasRoleUser(HttpPrincipal httpPrincipal, long roleId,
		long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(roleId);

			Object paramObj1 = new LongWrapper(userId);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"hasRoleUser", new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void setRoleUsers(HttpPrincipal httpPrincipal, long roleId,
		long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(roleId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setRoleUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void setUserGroupUsers(HttpPrincipal httpPrincipal,
		long userGroupId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userGroupId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"setUserGroupUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void unsetGroupUsers(HttpPrincipal httpPrincipal,
		long groupId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"unsetGroupUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void unsetOrganizationUsers(HttpPrincipal httpPrincipal,
		long organizationId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(organizationId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"unsetOrganizationUsers",
					new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void unsetPasswordPolicyUsers(HttpPrincipal httpPrincipal,
		long passwordPolicyId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(passwordPolicyId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"unsetPasswordPolicyUsers",
					new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void unsetRoleUsers(HttpPrincipal httpPrincipal, long roleId,
		long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(roleId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"unsetRoleUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void unsetUserGroupUsers(HttpPrincipal httpPrincipal,
		long userGroupId, long[] userIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userGroupId);

			Object paramObj1 = userIds;

			if (userIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"unsetUserGroupUsers", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User updateActive(
		HttpPrincipal httpPrincipal, long userId, boolean active)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = new BooleanWrapper(active);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateActive", new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User updateAgreedToTermsOfUse(
		HttpPrincipal httpPrincipal, long userId, boolean agreedToTermsOfUse)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = new BooleanWrapper(agreedToTermsOfUse);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateAgreedToTermsOfUse",
					new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User updateLockout(
		HttpPrincipal httpPrincipal, long userId, boolean lockout)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = new BooleanWrapper(lockout);

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateLockout", new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void updateOrganizations(HttpPrincipal httpPrincipal,
		long userId, long[] organizationIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = organizationIds;

			if (organizationIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateOrganizations", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User updatePassword(
		HttpPrincipal httpPrincipal, long userId, java.lang.String password1,
		java.lang.String password2, boolean passwordReset)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

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
					"updatePassword",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void updatePortrait(HttpPrincipal httpPrincipal, long userId,
		byte[] bytes)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = bytes;

			if (bytes == null) {
				paramObj1 = new NullWrapper("[B");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updatePortrait", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User updateUser(
		HttpPrincipal httpPrincipal, long userId, java.lang.String oldPassword,
		boolean passwordReset, java.lang.String screenName,
		java.lang.String emailAddress, java.lang.String languageId,
		java.lang.String timeZoneId, java.lang.String greeting,
		java.lang.String comments, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName, int prefixId,
		int suffixId, boolean male, int birthdayMonth, int birthdayDay,
		int birthdayYear, java.lang.String smsSn, java.lang.String aimSn,
		java.lang.String icqSn, java.lang.String jabberSn,
		java.lang.String msnSn, java.lang.String skypeSn,
		java.lang.String ymSn, java.lang.String jobTitle, long[] organizationIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = oldPassword;

			if (oldPassword == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = new BooleanWrapper(passwordReset);

			Object paramObj3 = screenName;

			if (screenName == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = emailAddress;

			if (emailAddress == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = languageId;

			if (languageId == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = timeZoneId;

			if (timeZoneId == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = greeting;

			if (greeting == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = comments;

			if (comments == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = firstName;

			if (firstName == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = middleName;

			if (middleName == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = lastName;

			if (lastName == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = new IntegerWrapper(prefixId);

			Object paramObj13 = new IntegerWrapper(suffixId);

			Object paramObj14 = new BooleanWrapper(male);

			Object paramObj15 = new IntegerWrapper(birthdayMonth);

			Object paramObj16 = new IntegerWrapper(birthdayDay);

			Object paramObj17 = new IntegerWrapper(birthdayYear);

			Object paramObj18 = smsSn;

			if (smsSn == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = aimSn;

			if (aimSn == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = icqSn;

			if (icqSn == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = jabberSn;

			if (jabberSn == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = msnSn;

			if (msnSn == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = skypeSn;

			if (skypeSn == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = ymSn;

			if (ymSn == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = jobTitle;

			if (jobTitle == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			Object paramObj26 = organizationIds;

			if (organizationIds == null) {
				paramObj26 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateUser",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.User updateUser(
		HttpPrincipal httpPrincipal, long userId, java.lang.String oldPassword,
		java.lang.String newPassword1, java.lang.String newPassword2,
		boolean passwordReset, java.lang.String screenName,
		java.lang.String emailAddress, java.lang.String languageId,
		java.lang.String timeZoneId, java.lang.String greeting,
		java.lang.String comments, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName, int prefixId,
		int suffixId, boolean male, int birthdayMonth, int birthdayDay,
		int birthdayYear, java.lang.String smsSn, java.lang.String aimSn,
		java.lang.String icqSn, java.lang.String jabberSn,
		java.lang.String msnSn, java.lang.String skypeSn,
		java.lang.String ymSn, java.lang.String jobTitle, long[] organizationIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(userId);

			Object paramObj1 = oldPassword;

			if (oldPassword == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = newPassword1;

			if (newPassword1 == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = newPassword2;

			if (newPassword2 == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(passwordReset);

			Object paramObj5 = screenName;

			if (screenName == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = emailAddress;

			if (emailAddress == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = languageId;

			if (languageId == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = timeZoneId;

			if (timeZoneId == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = greeting;

			if (greeting == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = comments;

			if (comments == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = firstName;

			if (firstName == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = middleName;

			if (middleName == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = lastName;

			if (lastName == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = new IntegerWrapper(prefixId);

			Object paramObj15 = new IntegerWrapper(suffixId);

			Object paramObj16 = new BooleanWrapper(male);

			Object paramObj17 = new IntegerWrapper(birthdayMonth);

			Object paramObj18 = new IntegerWrapper(birthdayDay);

			Object paramObj19 = new IntegerWrapper(birthdayYear);

			Object paramObj20 = smsSn;

			if (smsSn == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = aimSn;

			if (aimSn == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = icqSn;

			if (icqSn == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = jabberSn;

			if (jabberSn == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = msnSn;

			if (msnSn == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = skypeSn;

			if (skypeSn == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			Object paramObj26 = ymSn;

			if (ymSn == null) {
				paramObj26 = new NullWrapper("java.lang.String");
			}

			Object paramObj27 = jobTitle;

			if (jobTitle == null) {
				paramObj27 = new NullWrapper("java.lang.String");
			}

			Object paramObj28 = organizationIds;

			if (organizationIds == null) {
				paramObj28 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(UserServiceUtil.class.getName(),
					"updateUser",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26, paramObj27, paramObj28
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.User)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(UserServiceHttp.class);
}