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

package com.liferay.portlet.wiki.service.http;

import com.liferay.portlet.wiki.service.spring.WikiPageServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="WikiPageServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiPageServiceSoap {
	public static void deletePage(java.lang.String nodeId,
		java.lang.String title) throws RemoteException {
		try {
			WikiPageServiceUtil.deletePage(nodeId, title);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean exists(java.lang.String nodeId, java.lang.String title)
		throws RemoteException {
		try {
			boolean returnValue = WikiPageServiceUtil.exists(nodeId, title);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel getHeadPage(
		java.lang.String nodeId, java.lang.String title)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiPage returnValue = WikiPageServiceUtil.getHeadPage(nodeId,
					title);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel[] getHeadPagesByNode(
		java.lang.String nodeId) throws RemoteException {
		try {
			java.util.List returnValue = WikiPageServiceUtil.getHeadPagesByNode(nodeId);

			return (com.liferay.portlet.wiki.model.WikiPage[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiPage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel[] getLinks(
		java.lang.String nodeId, java.lang.String title)
		throws RemoteException {
		try {
			java.util.List returnValue = WikiPageServiceUtil.getLinks(nodeId,
					title);

			return (com.liferay.portlet.wiki.model.WikiPage[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiPage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel[] getOrphans(
		java.lang.String nodeId) throws RemoteException {
		try {
			java.util.List returnValue = WikiPageServiceUtil.getOrphans(nodeId);

			return (com.liferay.portlet.wiki.model.WikiPage[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiPage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel getPage(
		java.lang.String nodeId, java.lang.String title, double version)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiPage returnValue = WikiPageServiceUtil.getPage(nodeId,
					title, version);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel[] getPages(
		java.lang.String nodeId, java.lang.String title, boolean head)
		throws RemoteException {
		try {
			java.util.List returnValue = WikiPageServiceUtil.getPages(nodeId,
					title, head);

			return (com.liferay.portlet.wiki.model.WikiPage[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiPage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel[] getPagesByNode(
		java.lang.String nodeId, boolean head) throws RemoteException {
		try {
			java.util.List returnValue = WikiPageServiceUtil.getPagesByNode(nodeId,
					head);

			return (com.liferay.portlet.wiki.model.WikiPage[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiPage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getPagesSizeByNode(java.lang.String nodeId, boolean head)
		throws RemoteException {
		try {
			int returnValue = WikiPageServiceUtil.getPagesSizeByNode(nodeId,
					head);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel[] getRecentChanges(
		java.lang.String nodeId) throws RemoteException {
		try {
			java.util.List returnValue = WikiPageServiceUtil.getRecentChanges(nodeId);

			return (com.liferay.portlet.wiki.model.WikiPage[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiPage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel lockPage(
		java.lang.String nodeId, java.lang.String title, double version)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiPage returnValue = WikiPageServiceUtil.lockPage(nodeId,
					title, version);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel revertPage(
		java.lang.String nodeId, java.lang.String title, double version)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiPage returnValue = WikiPageServiceUtil.revertPage(nodeId,
					title, version);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void unlockPage(java.lang.String nodeId,
		java.lang.String title) throws RemoteException {
		try {
			WikiPageServiceUtil.unlockPage(nodeId, title);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPageModel updatePage(
		java.lang.String nodeId, java.lang.String title,
		java.lang.String content, java.lang.String format)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiPage returnValue = WikiPageServiceUtil.updatePage(nodeId,
					title, content, format);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}