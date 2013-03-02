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

package com.liferay.portlet.tags.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.DoubleWrapper;
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.http.TunnelUtil;

import com.liferay.portlet.tags.service.TagsAssetServiceUtil;

/**
 * <a href="TagsAssetServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portlet.tags.service.TagsAssetServiceUtil</code> service
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
 * @see com.liferay.portlet.tags.service.TagsAssetServiceUtil
 * @see com.liferay.portlet.tags.service.http.TagsAssetServiceSoap
 *
 */
public class TagsAssetServiceHttp {
	public static void deleteAsset(HttpPrincipal httpPrincipal, long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(assetId);

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"deleteAsset", new Object[] { paramObj0 });

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

	public static com.liferay.portlet.tags.model.TagsAsset getAsset(
		HttpPrincipal httpPrincipal, long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(assetId);

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getAsset", new Object[] { paramObj0 });

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

			return (com.liferay.portlet.tags.model.TagsAsset)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static java.lang.String getAssetsRSS(HttpPrincipal httpPrincipal,
		long groupId, long[] classNameIds, long[] entryIds, long[] notEntryIds,
		boolean andOperator, java.lang.String orderByCol1,
		java.lang.String orderByCol2, java.lang.String orderByType1,
		java.lang.String orderByType2, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = classNameIds;

			if (classNameIds == null) {
				paramObj1 = new NullWrapper("[J");
			}

			Object paramObj2 = entryIds;

			if (entryIds == null) {
				paramObj2 = new NullWrapper("[J");
			}

			Object paramObj3 = notEntryIds;

			if (notEntryIds == null) {
				paramObj3 = new NullWrapper("[J");
			}

			Object paramObj4 = new BooleanWrapper(andOperator);

			Object paramObj5 = orderByCol1;

			if (orderByCol1 == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = orderByCol2;

			if (orderByCol2 == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = orderByType1;

			if (orderByType1 == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = orderByType2;

			if (orderByType2 == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = new BooleanWrapper(excludeZeroViewCount);

			Object paramObj10 = publishDate;

			if (publishDate == null) {
				paramObj10 = new NullWrapper("java.util.Date");
			}

			Object paramObj11 = expirationDate;

			if (expirationDate == null) {
				paramObj11 = new NullWrapper("java.util.Date");
			}

			Object paramObj12 = new IntegerWrapper(max);

			Object paramObj13 = type;

			if (type == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = new DoubleWrapper(version);

			Object paramObj15 = displayStyle;

			if (displayStyle == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = feedURL;

			if (feedURL == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = entryURL;

			if (entryURL == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getAssetsRSS",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17
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

			return (java.lang.String)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetType[] getAssetTypes(
		HttpPrincipal httpPrincipal, java.lang.String languageId)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = languageId;

			if (languageId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getAssetTypes", new Object[] { paramObj0 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.tags.model.TagsAssetType[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] getCompanyAssetDisplays(
		HttpPrincipal httpPrincipal, long companyId, int begin, int end,
		java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = new IntegerWrapper(begin);

			Object paramObj2 = new IntegerWrapper(end);

			Object paramObj3 = languageId;

			if (languageId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getCompanyAssetDisplays",
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

			return (com.liferay.portlet.tags.model.TagsAssetDisplay[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static java.util.List getCompanyAssets(HttpPrincipal httpPrincipal,
		long companyId, int begin, int end)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = new IntegerWrapper(begin);

			Object paramObj2 = new IntegerWrapper(end);

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getCompanyAssets",
					new Object[] { paramObj0, paramObj1, paramObj2 });

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

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static int getCompanyAssetsCount(HttpPrincipal httpPrincipal,
		long companyId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getCompanyAssetsCount", new Object[] { paramObj0 });

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

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static java.lang.String getCompanyAssetsRSS(
		HttpPrincipal httpPrincipal, long companyId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = new IntegerWrapper(max);

			Object paramObj2 = type;

			if (type == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new DoubleWrapper(version);

			Object paramObj4 = displayStyle;

			if (displayStyle == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = feedURL;

			if (feedURL == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = entryURL;

			if (entryURL == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"getCompanyAssetsRSS",
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

			return (java.lang.String)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.tags.model.TagsAsset incrementViewCounter(
		HttpPrincipal httpPrincipal, java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = className;

			if (className == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new LongWrapper(classPK);

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"incrementViewCounter",
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

			return (com.liferay.portlet.tags.model.TagsAsset)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] searchAssetDisplays(
		HttpPrincipal httpPrincipal, long companyId,
		java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = keywords;

			if (keywords == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = languageId;

			if (languageId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new IntegerWrapper(begin);

			Object paramObj5 = new IntegerWrapper(end);

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"searchAssetDisplays",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5
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

			return (com.liferay.portlet.tags.model.TagsAssetDisplay[])returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static int searchAssetDisplaysCount(HttpPrincipal httpPrincipal,
		long companyId, java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = keywords;

			if (keywords == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = languageId;

			if (languageId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"searchAssetDisplaysCount",
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

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateAsset(
		HttpPrincipal httpPrincipal, long groupId, java.lang.String className,
		long classPK, java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(groupId);

			Object paramObj1 = className;

			if (className == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = new LongWrapper(classPK);

			Object paramObj3 = entryNames;

			if (entryNames == null) {
				paramObj3 = new NullWrapper("[Ljava.lang.String;");
			}

			Object paramObj4 = startDate;

			if (startDate == null) {
				paramObj4 = new NullWrapper("java.util.Date");
			}

			Object paramObj5 = endDate;

			if (endDate == null) {
				paramObj5 = new NullWrapper("java.util.Date");
			}

			Object paramObj6 = publishDate;

			if (publishDate == null) {
				paramObj6 = new NullWrapper("java.util.Date");
			}

			Object paramObj7 = expirationDate;

			if (expirationDate == null) {
				paramObj7 = new NullWrapper("java.util.Date");
			}

			Object paramObj8 = mimeType;

			if (mimeType == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = title;

			if (title == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = description;

			if (description == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = summary;

			if (summary == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = url;

			if (url == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = new IntegerWrapper(height);

			Object paramObj14 = new IntegerWrapper(width);

			Object paramObj15 = priority;

			if (priority == null) {
				paramObj15 = new NullWrapper("java.lang.Integer");
			}

			MethodWrapper methodWrapper = new MethodWrapper(TagsAssetServiceUtil.class.getName(),
					"updateAsset",
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
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.tags.model.TagsAsset)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(TagsAssetServiceHttp.class);
}