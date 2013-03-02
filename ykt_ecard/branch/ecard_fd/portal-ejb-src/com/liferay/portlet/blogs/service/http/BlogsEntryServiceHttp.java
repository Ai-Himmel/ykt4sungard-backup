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

package com.liferay.portlet.blogs.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BlogsEntryServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryServiceHttp {
	public static com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		HttpPrincipal httpPrincipal, java.lang.String categoryId,
		java.lang.String title, java.lang.String content, int displayMonth,
		int displayDay, int displayYear, int displayHour, int displayMinute,
		boolean sharing, boolean commentable)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = categoryId;

			if (categoryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = title;

			if (title == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = content;

			if (content == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new IntegerWrapper(displayMonth);
			Object paramObj4 = new IntegerWrapper(displayDay);
			Object paramObj5 = new IntegerWrapper(displayYear);
			Object paramObj6 = new IntegerWrapper(displayHour);
			Object paramObj7 = new IntegerWrapper(displayMinute);
			Object paramObj8 = new BooleanWrapper(sharing);
			Object paramObj9 = new BooleanWrapper(commentable);
			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"addEntry",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static void deleteEntry(HttpPrincipal httpPrincipal,
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entryId;

			if (entryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"deleteEntry", new Object[] { paramObj0 });
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

	public static void deleteEntry(HttpPrincipal httpPrincipal,
		com.liferay.portlet.blogs.model.BlogsEntry entry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entry;

			if (entry == null) {
				paramObj0 = new NullWrapper(
						"com.liferay.portlet.blogs.model.BlogsEntry");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"deleteEntry", new Object[] { paramObj0 });
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

	public static com.liferay.portlet.blogs.model.BlogsEntry getEntry(
		HttpPrincipal httpPrincipal, java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entryId;

			if (entryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntry", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static java.util.List getEntries(HttpPrincipal httpPrincipal,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntries",
					new Object[] { paramObj0, paramObj1, paramObj2 });
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

	public static java.util.List getEntries(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String categoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = new IntegerWrapper(begin);
			Object paramObj3 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntries",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });
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

	public static java.util.List getEntries(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = cal;

			if (cal == null) {
				paramObj1 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntries", new Object[] { paramObj0, paramObj1 });
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

	public static java.util.List getEntries(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String categoryId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntries",
					new Object[] { paramObj0, paramObj1, paramObj2 });
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

	public static int getEntriesSize(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = cal;

			if (cal == null) {
				paramObj1 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntriesSize", new Object[] { paramObj0, paramObj1 });
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

	public static int getEntriesSize(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String categoryId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntriesSize",
					new Object[] { paramObj0, paramObj1, paramObj2 });
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

	public static java.lang.String getEntriesXML(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String categoryId,
		java.lang.String type, int begin, int end, java.lang.String findEntryUrl)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = type;

			if (type == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new IntegerWrapper(begin);
			Object paramObj4 = new IntegerWrapper(end);
			Object paramObj5 = findEntryUrl;

			if (findEntryUrl == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getEntriesXML",
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

	public static com.liferay.portlet.blogs.model.BlogsEntry getLatestEntry(
		HttpPrincipal httpPrincipal, java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getLatestEntry", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static com.liferay.portlet.blogs.model.BlogsEntry getLatestEntry(
		HttpPrincipal httpPrincipal, java.lang.String userId,
		java.lang.String categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"getLatestEntry", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static boolean hasEntries(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = cal;

			if (cal == null) {
				paramObj1 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"hasEntries", new Object[] { paramObj0, paramObj1 });
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

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static boolean hasEntries(HttpPrincipal httpPrincipal,
		java.lang.String userId, java.lang.String categoryId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = userId;

			if (userId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"hasEntries",
					new Object[] { paramObj0, paramObj1, paramObj2 });
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

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void reIndex(HttpPrincipal httpPrincipal,
		java.lang.String[] ids) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = ids;

			if (ids == null) {
				paramObj0 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"reIndex", new Object[] { paramObj0 });
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

	public static com.liferay.util.lucene.Hits search(
		HttpPrincipal httpPrincipal, java.lang.String companyId,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String[] blogsUserIds, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = portletId;

			if (portletId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = groupId;

			if (groupId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = blogsUserIds;

			if (blogsUserIds == null) {
				paramObj3 = new NullWrapper("[Ljava.lang.String;");
			}

			Object paramObj4 = keywords;

			if (keywords == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"search",
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

				throw e;
			}

			return (com.liferay.util.lucene.Hits)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry updateEntry(
		HttpPrincipal httpPrincipal, java.lang.String entryId,
		java.lang.String categoryId, java.lang.String title,
		java.lang.String content, int displayMonth, int displayDay,
		int displayYear, int displayHour, int displayMinute, boolean sharing,
		boolean commentable)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entryId;

			if (entryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = categoryId;

			if (categoryId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = title;

			if (title == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = content;

			if (content == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new IntegerWrapper(displayMonth);
			Object paramObj5 = new IntegerWrapper(displayDay);
			Object paramObj6 = new IntegerWrapper(displayYear);
			Object paramObj7 = new IntegerWrapper(displayHour);
			Object paramObj8 = new IntegerWrapper(displayMinute);
			Object paramObj9 = new BooleanWrapper(sharing);
			Object paramObj10 = new BooleanWrapper(commentable);
			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"updateEntry",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static com.liferay.portlet.blogs.model.BlogsEntry updateSharing(
		HttpPrincipal httpPrincipal, java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entryId;

			if (entryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"updateSharing", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static com.liferay.portlet.blogs.model.BlogsEntry updatePropsCount(
		HttpPrincipal httpPrincipal, java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entryId;

			if (entryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"updatePropsCount", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	public static com.liferay.portlet.blogs.model.BlogsEntry updateCommentsCount(
		HttpPrincipal httpPrincipal, java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = entryId;

			if (entryId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(BlogsEntryServiceUtil.class.getName(),
					"updateCommentsCount", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.blogs.model.BlogsEntry)returnObj;
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

	private static final Log _log = LogFactory.getLog(BlogsEntryServiceHttp.class);
}