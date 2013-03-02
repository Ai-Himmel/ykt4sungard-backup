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

package com.liferay.portlet.blogs.service.spring;

/**
 * <a href="BlogsLinkServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsLinkServiceUtil {
	public static final String PORTLET_ID = "33";

	public static com.liferay.portlet.blogs.model.BlogsLink addLink(
		java.lang.String name, java.lang.String url)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();

			return blogsLinkService.addLink(name, url);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteLink(java.lang.String linkId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();
			blogsLinkService.deleteLink(linkId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteLink(
		com.liferay.portlet.blogs.model.BlogsLink link)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();
			blogsLinkService.deleteLink(link);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsLink getLink(
		java.lang.String linkId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();

			return blogsLinkService.getLink(linkId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getLinks(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();

			return blogsLinkService.getLinks(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getLinksSize(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();

			return blogsLinkService.getLinksSize(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsLink updateLink(
		java.lang.String linkId, java.lang.String name, java.lang.String url)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsLinkService blogsLinkService = BlogsLinkServiceFactory.getService();

			return blogsLinkService.updateLink(linkId, name, url);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}