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

import com.liferay.portlet.journal.service.spring.JournalTemplateServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JournalTemplateServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalTemplateServiceHttp {
	public static com.liferay.portlet.journal.model.JournalTemplate addTemplate(
		HttpPrincipal httpPrincipal, java.lang.String templateId,
		boolean autoTemplateId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String structureId,
		java.lang.String name, java.lang.String description,
		java.lang.String xsl, boolean formatXsl, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new BooleanWrapper(autoTemplateId);
			Object paramObj2 = portletId;

			if (portletId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = groupId;

			if (groupId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = structureId;

			if (structureId == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = name;

			if (name == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = description;

			if (description == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = xsl;

			if (xsl == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = new BooleanWrapper(formatXsl);
			Object paramObj9 = new BooleanWrapper(smallImage);
			Object paramObj10 = smallImageURL;

			if (smallImageURL == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = smallFile;

			if (smallFile == null) {
				paramObj11 = new NullWrapper("java.io.File");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"addTemplate",
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
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.journal.model.JournalTemplate)returnObj;
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

	public static void deleteTemplate(HttpPrincipal httpPrincipal,
		java.lang.String templateId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"deleteTemplate", new Object[] { paramObj0 });
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

	public static com.liferay.portlet.journal.model.JournalTemplate getTemplate(
		HttpPrincipal httpPrincipal, java.lang.String templateId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"getTemplate", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.journal.model.JournalTemplate)returnObj;
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

	public static java.util.List getTemplates(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
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

			Object paramObj3 = new IntegerWrapper(begin);
			Object paramObj4 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"getTemplates",
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

	public static java.util.List getTemplates(HttpPrincipal httpPrincipal,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = structureId;

			if (structureId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"getTemplates", new Object[] { paramObj0 });
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

	public static java.util.List getTemplates(HttpPrincipal httpPrincipal,
		java.lang.String structureId, int begin, int end)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = structureId;

			if (structureId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"getTemplates",
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

	public static int getTemplatesSize(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
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

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"getTemplatesSize",
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

	public static int getTemplatesSize(HttpPrincipal httpPrincipal,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = structureId;

			if (structureId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"getTemplatesSize", new Object[] { paramObj0 });
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

	public static com.liferay.portlet.journal.model.JournalTemplate updateTemplate(
		HttpPrincipal httpPrincipal, java.lang.String templateId,
		java.lang.String name, java.lang.String description,
		java.lang.String xsl, boolean formatXsl, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = templateId;

			if (templateId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = name;

			if (name == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = description;

			if (description == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = xsl;

			if (xsl == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new BooleanWrapper(formatXsl);
			Object paramObj5 = new BooleanWrapper(smallImage);
			Object paramObj6 = smallImageURL;

			if (smallImageURL == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = smallFile;

			if (smallFile == null) {
				paramObj7 = new NullWrapper("java.io.File");
			}

			MethodWrapper methodWrapper = new MethodWrapper(JournalTemplateServiceUtil.class.getName(),
					"updateTemplate",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7
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

			return (com.liferay.portlet.journal.model.JournalTemplate)returnObj;
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

	private static final Log _log = LogFactory.getLog(JournalTemplateServiceHttp.class);
}