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

package com.liferay.portlet.messageboards.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBTopicServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBTopicServiceHttp {
	public static com.liferay.portlet.messageboards.model.MBTopic addTopic(
		HttpPrincipal httpPrincipal, java.lang.String portletId,
		java.lang.String groupId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description)
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

			Object paramObj2 = readRoles;

			if (readRoles == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = writeRoles;

			if (writeRoles == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = name;

			if (name == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = description;

			if (description == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"addTopic",
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

			return (com.liferay.portlet.messageboards.model.MBTopic)returnObj;
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

	public static void deleteTopic(HttpPrincipal httpPrincipal,
		java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"deleteTopic", new Object[] { paramObj0 });
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

	public static com.liferay.portlet.messageboards.model.MBTopic getTopic(
		HttpPrincipal httpPrincipal, java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"getTopic", new Object[] { paramObj0 });
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

			return (com.liferay.portlet.messageboards.model.MBTopic)returnObj;
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

	public static java.util.List getTopics(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId)
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

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"getTopics",
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

	public static java.util.List getTopics(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
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

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new IntegerWrapper(begin);
			Object paramObj4 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"getTopics",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4
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

	public static int getTopicsSize(HttpPrincipal httpPrincipal,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId)
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

			Object paramObj2 = companyId;

			if (companyId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"getTopicsSize",
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

	public static com.liferay.portlet.messageboards.model.MBMessage postNewThread(
		HttpPrincipal httpPrincipal, java.lang.String topicId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = subject;

			if (subject == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = body;

			if (body == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = files;

			if (files == null) {
				paramObj3 = new NullWrapper("java.util.List");
			}

			Object paramObj4 = new BooleanWrapper(anonymous);
			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"postNewThread",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4
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

			return (com.liferay.portlet.messageboards.model.MBMessage)returnObj;
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

	public static com.liferay.portlet.messageboards.model.MBMessage postReply(
		HttpPrincipal httpPrincipal, java.lang.String topicId,
		java.lang.String threadId, java.lang.String parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = threadId;

			if (threadId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = parentMessageId;

			if (parentMessageId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = subject;

			if (subject == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = body;

			if (body == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = files;

			if (files == null) {
				paramObj5 = new NullWrapper("java.util.List");
			}

			Object paramObj6 = new BooleanWrapper(anonymous);
			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"postReply",
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

			return (com.liferay.portlet.messageboards.model.MBMessage)returnObj;
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

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
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
		java.lang.String[] topicIds, java.lang.String keywords)
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

			Object paramObj3 = topicIds;

			if (topicIds == null) {
				paramObj3 = new NullWrapper("[Ljava.lang.String;");
			}

			Object paramObj4 = keywords;

			if (keywords == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
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

	public static com.liferay.portlet.messageboards.model.MBTopic updateTopic(
		HttpPrincipal httpPrincipal, java.lang.String topicId,
		java.lang.String readRoles, java.lang.String writeRoles,
		java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = readRoles;

			if (readRoles == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = writeRoles;

			if (writeRoles == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = name;

			if (name == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = description;

			if (description == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"updateTopic",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4
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

			return (com.liferay.portlet.messageboards.model.MBTopic)returnObj;
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
		java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
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

	public static boolean hasRead(HttpPrincipal httpPrincipal,
		java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
					"hasRead", new Object[] { paramObj0 });
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

	public static boolean hasWrite(HttpPrincipal httpPrincipal,
		java.lang.String topicId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = topicId;

			if (topicId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(MBTopicServiceUtil.class.getName(),
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

	private static final Log _log = LogFactory.getLog(MBTopicServiceHttp.class);
}