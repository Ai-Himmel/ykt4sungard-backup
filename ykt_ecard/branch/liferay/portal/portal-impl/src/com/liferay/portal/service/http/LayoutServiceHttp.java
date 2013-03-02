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
import com.liferay.portal.service.LayoutServiceUtil;

/**
 * <a href="LayoutServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portal.service.LayoutServiceUtil</code> service
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
 * @see com.liferay.portal.service.LayoutServiceUtil
 * @see com.liferay.portal.service.http.LayoutServiceSoap
 *
 */
public class LayoutServiceHttp {
	public static com.liferay.portal.model.Layout addLayout(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long parentLayoutId, java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(parentLayoutId);

			Object paramObj3 = name;

			if (name == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = title;

			if (title == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = description;

			if (description == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = type;

			if (type == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = new BooleanWrapper(hidden);

			Object paramObj8 = friendlyURL;

			if (friendlyURL == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"addLayout",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout addLayout(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long parentLayoutId, java.util.Map localeNamesMap,
		java.util.Map localeTitlesMap, java.lang.String description,
		java.lang.String type, boolean hidden, java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(parentLayoutId);

			Object paramObj3 = localeNamesMap;

			if (localeNamesMap == null) {
				paramObj3 = new NullWrapper("java.util.Map");
			}

			Object paramObj4 = localeTitlesMap;

			if (localeTitlesMap == null) {
				paramObj4 = new NullWrapper("java.util.Map");
			}

			Object paramObj5 = description;

			if (description == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = type;

			if (type == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = new BooleanWrapper(hidden);

			Object paramObj8 = friendlyURL;

			if (friendlyURL == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"addLayout",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deleteLayout(HttpPrincipal httpPrincipal, long plid)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"deleteLayout", new Object[] { paramObj0 });

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

	public static void deleteLayout(HttpPrincipal httpPrincipal, long groupId,
		boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"deleteLayout",
					new Object[] { paramObj0, paramObj1, paramObj2 });

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

	public static java.lang.String getLayoutName(HttpPrincipal httpPrincipal,
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = languageId;

			if (languageId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"getLayoutName",
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

			return (java.lang.String)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.LayoutReference[] getLayoutReferences(
		HttpPrincipal httpPrincipal, long companyId,
		java.lang.String portletId, java.lang.String prefsKey,
		java.lang.String prefsValue) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = prefsKey;

			if (prefsKey == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = prefsValue;

			if (prefsValue == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"getLayoutReferences",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.LayoutReference[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static byte[] exportLayouts(HttpPrincipal httpPrincipal,
		long groupId, boolean privateLayout, java.util.Map parameterMap)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = parameterMap;

			if (parameterMap == null) {
				paramObj2 = new NullWrapper("java.util.Map");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"exportLayouts",
					new Object[] { paramObj0, paramObj1, paramObj2 });

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

			return (byte[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static byte[] exportLayouts(HttpPrincipal httpPrincipal,
		long groupId, boolean privateLayout, long[] layoutIds,
		java.util.Map parameterMap)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = layoutIds;

			if (layoutIds == null) {
				paramObj2 = new NullWrapper("[J");
			}

			Object paramObj3 = parameterMap;

			if (parameterMap == null) {
				paramObj3 = new NullWrapper("java.util.Map");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"exportLayouts",
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

			return (byte[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static byte[] exportPortletInfo(HttpPrincipal httpPrincipal,
		long plid, java.lang.String portletId, java.util.Map parameterMap)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = parameterMap;

			if (parameterMap == null) {
				paramObj2 = new NullWrapper("java.util.Map");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"exportPortletInfo",
					new Object[] { paramObj0, paramObj1, paramObj2 });

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

			return (byte[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void importLayouts(HttpPrincipal httpPrincipal, long groupId,
		boolean privateLayout, java.util.Map parameterMap, java.io.File file)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = parameterMap;

			if (parameterMap == null) {
				paramObj2 = new NullWrapper("java.util.Map");
			}

			Object paramObj3 = file;

			if (file == null) {
				paramObj3 = new NullWrapper("java.io.File");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"importLayouts",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

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

	public static void importLayouts(HttpPrincipal httpPrincipal, long groupId,
		boolean privateLayout, java.util.Map parameterMap,
		java.io.InputStream is)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = parameterMap;

			if (parameterMap == null) {
				paramObj2 = new NullWrapper("java.util.Map");
			}

			Object paramObj3 = is;

			if (is == null) {
				paramObj3 = new NullWrapper("java.io.InputStream");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"importLayouts",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

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

	public static void importPortletInfo(HttpPrincipal httpPrincipal,
		long plid, java.lang.String portletId, java.util.Map parameterMap,
		java.io.File file)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = parameterMap;

			if (parameterMap == null) {
				paramObj2 = new NullWrapper("java.util.Map");
			}

			Object paramObj3 = file;

			if (file == null) {
				paramObj3 = new NullWrapper("java.io.File");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"importPortletInfo",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

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

	public static void importPortletInfo(HttpPrincipal httpPrincipal,
		long plid, java.lang.String portletId, java.util.Map parameterMap,
		java.io.InputStream is)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = parameterMap;

			if (parameterMap == null) {
				paramObj2 = new NullWrapper("java.util.Map");
			}

			Object paramObj3 = is;

			if (is == null) {
				paramObj3 = new NullWrapper("java.io.InputStream");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"importPortletInfo",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

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

	public static void setLayouts(HttpPrincipal httpPrincipal, long groupId,
		boolean privateLayout, long parentLayoutId, long[] layoutIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(parentLayoutId);

			Object paramObj3 = layoutIds;

			if (layoutIds == null) {
				paramObj3 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"setLayouts",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });

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

	public static com.liferay.portal.model.Layout updateLayout(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, long parentLayoutId, java.util.Map localeNamesMap,
		java.util.Map localeTitlesMap, java.lang.String description,
		java.lang.String type, boolean hidden, java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = new LongWrapper(parentLayoutId);

			Object paramObj4 = localeNamesMap;

			if (localeNamesMap == null) {
				paramObj4 = new NullWrapper("java.util.Map");
			}

			Object paramObj5 = localeTitlesMap;

			if (localeTitlesMap == null) {
				paramObj5 = new NullWrapper("java.util.Map");
			}

			Object paramObj6 = description;

			if (description == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = type;

			if (type == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = new BooleanWrapper(hidden);

			Object paramObj9 = friendlyURL;

			if (friendlyURL == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateLayout",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateLayout(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, long parentLayoutId, java.util.Map localeNamesMap,
		java.util.Map localeTitlesMap, java.lang.String description,
		java.lang.String type, boolean hidden, java.lang.String friendlyURL,
		java.lang.Boolean iconImage, byte[] iconBytes)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = new LongWrapper(parentLayoutId);

			Object paramObj4 = localeNamesMap;

			if (localeNamesMap == null) {
				paramObj4 = new NullWrapper("java.util.Map");
			}

			Object paramObj5 = localeTitlesMap;

			if (localeTitlesMap == null) {
				paramObj5 = new NullWrapper("java.util.Map");
			}

			Object paramObj6 = description;

			if (description == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = type;

			if (type == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = new BooleanWrapper(hidden);

			Object paramObj9 = friendlyURL;

			if (friendlyURL == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = iconImage;

			if (iconImage == null) {
				paramObj10 = new NullWrapper("java.lang.Boolean");
			}

			Object paramObj11 = iconBytes;

			if (iconBytes == null) {
				paramObj11 = new NullWrapper("[B");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateLayout",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateLayout(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, java.lang.String typeSettings)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = typeSettings;

			if (typeSettings == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateLayout",
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateLookAndFeel(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, java.lang.String themeId,
		java.lang.String colorSchemeId, java.lang.String css, boolean wapTheme)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = themeId;

			if (themeId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = colorSchemeId;

			if (colorSchemeId == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = css;

			if (css == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = new BooleanWrapper(wapTheme);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateLookAndFeel",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateName(
		HttpPrincipal httpPrincipal, long plid, java.lang.String name,
		java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = name;

			if (name == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = languageId;

			if (languageId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateName",
					new Object[] { paramObj0, paramObj1, paramObj2 });

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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateName(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, java.lang.String name, java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = name;

			if (name == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = languageId;

			if (languageId == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateName",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateParentLayoutId(
		HttpPrincipal httpPrincipal, long plid, long parentPlid)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new LongWrapper(parentPlid);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateParentLayoutId",
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updateParentLayoutId(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, long parentLayoutId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = new LongWrapper(parentLayoutId);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updateParentLayoutId",
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updatePriority(
		HttpPrincipal httpPrincipal, long plid, int priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new IntegerWrapper(priority);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updatePriority", new Object[] { paramObj0, paramObj1 });

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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Layout updatePriority(
		HttpPrincipal httpPrincipal, long groupId, boolean privateLayout,
		long layoutId, int priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = new BooleanWrapper(privateLayout);

			Object paramObj2 = new LongWrapper(layoutId);

			Object paramObj3 = new IntegerWrapper(priority);

			MethodWrapper methodWrapper = new MethodWrapper(LayoutServiceUtil.class.getName(),
					"updatePriority",
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

			return (com.liferay.portal.model.Layout)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(LayoutServiceHttp.class);
}