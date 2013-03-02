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

package com.liferay.portlet.wiki.service.spring;

/**
 * <a href="WikiPageServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiPageServiceUtil {
	public static final String PORTLET_ID = "36";

	public static void deletePage(java.lang.String nodeId,
		java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();
			wikiPageService.deletePage(nodeId, title);
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

	public static boolean exists(java.lang.String nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.exists(nodeId, title);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.wiki.model.WikiPage getHeadPage(
		java.lang.String nodeId, java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getHeadPage(nodeId, title);
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

	public static java.util.List getHeadPagesByNode(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getHeadPagesByNode(nodeId);
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

	public static java.util.List getLinks(java.lang.String nodeId,
		java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getLinks(nodeId, title);
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

	public static java.util.List getOrphans(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getOrphans(nodeId);
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

	public static com.liferay.portlet.wiki.model.WikiPage getPage(
		java.lang.String nodeId, java.lang.String title, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getPage(nodeId, title, version);
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

	public static java.util.List getPages(java.lang.String nodeId,
		java.lang.String title, boolean head)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getPages(nodeId, title, head);
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

	public static java.util.List getPagesByNode(java.lang.String nodeId,
		boolean head)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getPagesByNode(nodeId, head);
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

	public static int getPagesSizeByNode(java.lang.String nodeId, boolean head)
		throws com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getPagesSizeByNode(nodeId, head);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getRecentChanges(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.getRecentChanges(nodeId);
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

	public static com.liferay.portlet.wiki.model.WikiPage lockPage(
		java.lang.String nodeId, java.lang.String title, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.lockPage(nodeId, title, version);
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

	public static com.liferay.portlet.wiki.model.WikiPage revertPage(
		java.lang.String nodeId, java.lang.String title, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.revertPage(nodeId, title, version);
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

	public static void unlockPage(java.lang.String nodeId,
		java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();
			wikiPageService.unlockPage(nodeId, title);
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

	public static com.liferay.portlet.wiki.model.WikiPage updatePage(
		java.lang.String nodeId, java.lang.String title,
		java.lang.String content, java.lang.String format)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiPageService wikiPageService = WikiPageServiceFactory.getService();

			return wikiPageService.updatePage(nodeId, title, content, format);
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