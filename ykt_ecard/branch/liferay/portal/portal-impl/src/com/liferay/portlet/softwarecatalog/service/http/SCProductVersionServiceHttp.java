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

package com.liferay.portlet.softwarecatalog.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.http.TunnelUtil;

import com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceUtil;

/**
 * <a href="SCProductVersionServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceUtil</code> service
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
 * @see com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceUtil
 * @see com.liferay.portlet.softwarecatalog.service.http.SCProductVersionServiceSoap
 *
 */
public class SCProductVersionServiceHttp {
	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion addProductVersion(
		HttpPrincipal httpPrincipal, long productEntryId,
		java.lang.String version, java.lang.String changeLog,
		java.lang.String downloadPageURL, java.lang.String directDownloadURL,
		boolean repoStoreArtifact, long[] frameworkVersionIds,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productEntryId);

			Object paramObj1 = version;

			if (version == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = changeLog;

			if (changeLog == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = downloadPageURL;

			if (downloadPageURL == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = directDownloadURL;

			if (directDownloadURL == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = new BooleanWrapper(repoStoreArtifact);

			Object paramObj6 = frameworkVersionIds;

			if (frameworkVersionIds == null) {
				paramObj6 = new NullWrapper("[J");
			}

			Object paramObj7 = new BooleanWrapper(addCommunityPermissions);

			Object paramObj8 = new BooleanWrapper(addGuestPermissions);

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"addProductVersion",
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

			return (com.liferay.portlet.softwarecatalog.model.SCProductVersion)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion addProductVersion(
		HttpPrincipal httpPrincipal, long productEntryId,
		java.lang.String version, java.lang.String changeLog,
		java.lang.String downloadPageURL, java.lang.String directDownloadURL,
		boolean repoStoreArtifact, long[] frameworkVersionIds,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productEntryId);

			Object paramObj1 = version;

			if (version == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = changeLog;

			if (changeLog == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = downloadPageURL;

			if (downloadPageURL == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = directDownloadURL;

			if (directDownloadURL == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = new BooleanWrapper(repoStoreArtifact);

			Object paramObj6 = frameworkVersionIds;

			if (frameworkVersionIds == null) {
				paramObj6 = new NullWrapper("[J");
			}

			Object paramObj7 = communityPermissions;

			if (communityPermissions == null) {
				paramObj7 = new NullWrapper("[Ljava.lang.String;");
			}

			Object paramObj8 = guestPermissions;

			if (guestPermissions == null) {
				paramObj8 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"addProductVersion",
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

			return (com.liferay.portlet.softwarecatalog.model.SCProductVersion)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deleteProductVersion(HttpPrincipal httpPrincipal,
		long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productVersionId);

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"deleteProductVersion", new Object[] { paramObj0 });

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

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion getProductVersion(
		HttpPrincipal httpPrincipal, long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productVersionId);

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"getProductVersion", new Object[] { paramObj0 });

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

			return (com.liferay.portlet.softwarecatalog.model.SCProductVersion)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static java.util.List getProductVersions(
		HttpPrincipal httpPrincipal, long productEntryId, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productEntryId);

			Object paramObj1 = new IntegerWrapper(begin);

			Object paramObj2 = new IntegerWrapper(end);

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"getProductVersions",
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

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static int getProductVersionsCount(HttpPrincipal httpPrincipal,
		long productEntryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productEntryId);

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"getProductVersionsCount", new Object[] { paramObj0 });

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

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductVersion updateProductVersion(
		HttpPrincipal httpPrincipal, long productVersionId,
		java.lang.String version, java.lang.String changeLog,
		java.lang.String downloadPageURL, java.lang.String directDownloadURL,
		boolean repoStoreArtifact, long[] frameworkVersionIds)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(productVersionId);

			Object paramObj1 = version;

			if (version == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = changeLog;

			if (changeLog == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = downloadPageURL;

			if (downloadPageURL == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = directDownloadURL;

			if (directDownloadURL == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = new BooleanWrapper(repoStoreArtifact);

			Object paramObj6 = frameworkVersionIds;

			if (frameworkVersionIds == null) {
				paramObj6 = new NullWrapper("[J");
			}

			MethodWrapper methodWrapper = new MethodWrapper(SCProductVersionServiceUtil.class.getName(),
					"updateProductVersion",
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

			return (com.liferay.portlet.softwarecatalog.model.SCProductVersion)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(SCProductVersionServiceHttp.class);
}