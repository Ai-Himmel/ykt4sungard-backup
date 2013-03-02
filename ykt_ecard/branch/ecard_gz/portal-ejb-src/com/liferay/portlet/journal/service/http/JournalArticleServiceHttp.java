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

package com.liferay.portlet.journal.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.DoubleWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JournalArticleServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalArticleServiceHttp {
	public static com.liferay.portlet.journal.model.JournalArticle addArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId,
		boolean autoArticleId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String title,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		int displayMonth, int displayDay, int displayYear, int expMonth,
		int expDay, int expYear, boolean neverExpires,
		java.lang.String articleURL, java.util.Map images)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new BooleanWrapper(autoArticleId);
			Object paramObj2 = portletId;

			if (portletId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = groupId;

			if (groupId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = title;

			if (title == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = content;

			if (content == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = type;

			if (type == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = structureId;

			if (structureId == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = templateId;

			if (templateId == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = new IntegerWrapper(displayMonth);
			Object paramObj10 = new IntegerWrapper(displayDay);
			Object paramObj11 = new IntegerWrapper(displayYear);
			Object paramObj12 = new IntegerWrapper(expMonth);
			Object paramObj13 = new IntegerWrapper(expDay);
			Object paramObj14 = new IntegerWrapper(expYear);
			Object paramObj15 = new BooleanWrapper(neverExpires);
			Object paramObj16 = articleURL;

			if (articleURL == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = images;

			if (images == null) {
				paramObj17 = new NullWrapper("java.util.Map");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"addArticle",
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
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static com.liferay.portlet.journal.model.JournalArticle approveArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId,
		java.lang.String articleURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = articleURL;

			if (articleURL == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"approveArticle", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static void checkArticles(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"checkArticles", new Object[0]);
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

	public static void deleteArticle(HttpPrincipal httpPrincipal,
		java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new DoubleWrapper(version);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"deleteArticle", new Object[] { paramObj0, paramObj1 });
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

	public static com.liferay.portlet.journal.model.JournalArticle getArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticle", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static com.liferay.portlet.journal.model.JournalArticle getArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new DoubleWrapper(version);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticle", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static java.lang.String getArticleContent(
		HttpPrincipal httpPrincipal, java.lang.String articleId,
		java.lang.String languageId, java.lang.String rootPath)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = languageId;

			if (languageId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = rootPath;

			if (rootPath == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticleContent",
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

	public static java.lang.String getArticleContent(
		HttpPrincipal httpPrincipal, java.lang.String articleId,
		double version, java.lang.String languageId, java.lang.String rootPath)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new DoubleWrapper(version);
			Object paramObj2 = languageId;

			if (languageId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = rootPath;

			if (rootPath == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticleContent",
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

	public static java.util.List getArticlesByCompany(
		HttpPrincipal httpPrincipal, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByCompany",
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

	public static java.util.List getArticlesByCompany(
		HttpPrincipal httpPrincipal, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = type;

			if (type == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(approved);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByCompany",
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

	public static java.util.List getArticlesByCompany(
		HttpPrincipal httpPrincipal, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved, int begin, int end)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = type;

			if (type == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(approved);
			Object paramObj5 = new IntegerWrapper(begin);
			Object paramObj6 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByCompany",
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

	public static java.util.List getArticlesByCompany(
		HttpPrincipal httpPrincipal, java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = type;

			if (type == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(approved);
			Object paramObj5 = new IntegerWrapper(begin);
			Object paramObj6 = new IntegerWrapper(end);
			Object paramObj7 = obc;

			if (obc == null) {
				paramObj7 = new NullWrapper(
						"com.liferay.util.dao.hibernate.OrderByComparator");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByCompany",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7
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

	public static int getArticlesByCompanySize(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = type;

			if (type == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(approved);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByCompanySize",
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

	public static java.util.List getArticlesByStructure(
		HttpPrincipal httpPrincipal, java.lang.String structureId, int begin,
		int end) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = structureId;

			if (structureId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByStructure",
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

	public static int getArticlesByStructureSize(HttpPrincipal httpPrincipal,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = structureId;

			if (structureId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByStructureSize", new Object[] { paramObj0 });
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

	public static java.util.List getArticlesByTemplate(
		HttpPrincipal httpPrincipal, java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByTemplate", new Object[] { paramObj0 });
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

	public static java.util.List getArticlesByTemplate(
		HttpPrincipal httpPrincipal, java.lang.String templateId, int begin,
		int end) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByTemplate",
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

	public static int getArticlesByTemplateSize(HttpPrincipal httpPrincipal,
		java.lang.String templateId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByTemplateSize", new Object[] { paramObj0 });
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

	public static java.util.List getArticlesByUser(
		HttpPrincipal httpPrincipal, java.lang.String portletId,
		java.lang.String groupId, java.lang.String type, boolean approved,
		int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = type;

			if (type == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new BooleanWrapper(approved);
			Object paramObj4 = new IntegerWrapper(begin);
			Object paramObj5 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByUser",
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

	public static int getArticlesByUserSize(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = portletId;

			if (portletId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = type;

			if (type == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new BooleanWrapper(approved);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getArticlesByUserSize",
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

	public static com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getLatestArticle", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId,
		java.lang.Boolean approved)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = approved;

			if (approved == null) {
				paramObj1 = new NullWrapper("java.lang.Boolean");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getLatestArticle", new Object[] { paramObj0, paramObj1 });
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

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static double getLatestVersion(HttpPrincipal httpPrincipal,
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"getLatestVersion", new Object[] { paramObj0 });
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

			return ((Double)returnObj).doubleValue();
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

	public static boolean isLatestVersion(HttpPrincipal httpPrincipal,
		java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new DoubleWrapper(version);
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"isLatestVersion", new Object[] { paramObj0, paramObj1 });
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

	public static void reIndex(HttpPrincipal httpPrincipal,
		java.lang.String[] ids) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = ids;

			if (ids == null) {
				paramObj0 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
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
		java.lang.String title, java.lang.String content, java.lang.String type)
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

			Object paramObj3 = title;

			if (title == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = content;

			if (content == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = type;

			if (type == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"search",
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

	public static com.liferay.portlet.journal.model.JournalArticle updateArticle(
		HttpPrincipal httpPrincipal, java.lang.String articleId,
		boolean incrementVersion, java.lang.String title,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		int displayMonth, int displayDay, int displayYear, int expMonth,
		int expDay, int expYear, boolean neverExpires,
		java.lang.String articleURL, java.util.Map images)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = articleId;

			if (articleId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new BooleanWrapper(incrementVersion);
			Object paramObj2 = title;

			if (title == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = content;

			if (content == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = type;

			if (type == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = structureId;

			if (structureId == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = templateId;

			if (templateId == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = new IntegerWrapper(displayMonth);
			Object paramObj8 = new IntegerWrapper(displayDay);
			Object paramObj9 = new IntegerWrapper(displayYear);
			Object paramObj10 = new IntegerWrapper(expMonth);
			Object paramObj11 = new IntegerWrapper(expDay);
			Object paramObj12 = new IntegerWrapper(expYear);
			Object paramObj13 = new BooleanWrapper(neverExpires);
			Object paramObj14 = articleURL;

			if (articleURL == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = images;

			if (images == null) {
				paramObj15 = new NullWrapper("java.util.Map");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"updateArticle",
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

			return (com.liferay.portlet.journal.model.JournalArticle)returnObj;
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

	public static boolean hasAdmin(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"hasAdmin", new Object[0]);
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

	public static boolean hasAdmin(HttpPrincipal httpPrincipal,
		com.liferay.portlet.journal.service.persistence.JournalArticlePK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = pk;

			if (pk == null) {
				paramObj0 = new NullWrapper(
						"com.liferay.portlet.journal.service.persistence.JournalArticlePK");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
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

	public static boolean hasDesigner(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"hasDesigner", new Object[0]);
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

	public static boolean hasEditor(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"hasEditor", new Object[0]);
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

	public static boolean hasWriter(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(JournalArticleServiceUtil.class.getName(),
					"hasWriter", new Object[0]);
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

	private static final Log _log = LogFactory.getLog(JournalArticleServiceHttp.class);
}