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

import com.liferay.portlet.blogs.service.spring.BlogsLinkServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BlogsLinkServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsLinkServiceSoap {
	public static com.liferay.portlet.blogs.model.BlogsLinkModel addLink(
		java.lang.String name, java.lang.String url) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsLink returnValue = BlogsLinkServiceUtil.addLink(name,
					url);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteLink(java.lang.String linkId)
		throws RemoteException {
		try {
			BlogsLinkServiceUtil.deleteLink(linkId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteLink(
		com.liferay.portlet.blogs.model.BlogsLink link)
		throws RemoteException {
		try {
			BlogsLinkServiceUtil.deleteLink(link);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsLinkModel getLink(
		java.lang.String linkId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsLink returnValue = BlogsLinkServiceUtil.getLink(linkId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsLinkModel[] getLinks(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = BlogsLinkServiceUtil.getLinks(userId);

			return (com.liferay.portlet.blogs.model.BlogsLink[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsLink[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getLinksSize(java.lang.String userId)
		throws RemoteException {
		try {
			int returnValue = BlogsLinkServiceUtil.getLinksSize(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsLinkModel updateLink(
		java.lang.String linkId, java.lang.String name, java.lang.String url)
		throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsLink returnValue = BlogsLinkServiceUtil.updateLink(linkId,
					name, url);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}