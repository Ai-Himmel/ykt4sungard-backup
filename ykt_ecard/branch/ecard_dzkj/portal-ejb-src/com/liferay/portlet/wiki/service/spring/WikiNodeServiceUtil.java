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
 * <a href="WikiNodeServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiNodeServiceUtil {
	public static final String PORTLET_ID = "36";

	public static com.liferay.portlet.wiki.model.WikiNode addNode(
		java.lang.String readRoles, java.lang.String writeRoles,
		java.lang.String name, java.lang.String description, boolean sharing)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.addNode(readRoles, writeRoles, name,
				description, sharing);
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

	public static void deleteNode(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();
			wikiNodeService.deleteNode(nodeId);
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

	public static void deleteNode(com.liferay.portlet.wiki.model.WikiNode node)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();
			wikiNodeService.deleteNode(node);
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

	public static com.liferay.portlet.wiki.model.WikiNode getNode(
		java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.getNode(nodeId);
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

	public static java.util.List getNodesByCompany()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.getNodesByCompany();
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

	public static java.util.List getNodesByUser()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.getNodesByUser();
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

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();
			wikiNodeService.reIndex(ids);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String[] nodeIds,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.search(companyId, portletId, groupId,
				nodeIds, keywords);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.wiki.model.WikiNode updateNode(
		java.lang.String nodeId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description, boolean sharing)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.updateNode(nodeId, readRoles, writeRoles,
				name, description, sharing);
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

	public static boolean hasAdmin()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.hasAdmin();
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

	public static boolean hasAdmin(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.hasAdmin(nodeId);
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

	public static boolean hasRead(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.hasRead(nodeId);
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

	public static boolean hasWrite(java.lang.String nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			WikiNodeService wikiNodeService = WikiNodeServiceFactory.getService();

			return wikiNodeService.hasWrite(nodeId);
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