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

import com.liferay.portlet.wiki.service.spring.WikiNodeServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="WikiNodeServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiNodeServiceSoap {
	public static com.liferay.portlet.wiki.model.WikiNodeModel addNode(
		java.lang.String readRoles, java.lang.String writeRoles,
		java.lang.String name, java.lang.String description, boolean sharing)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiNode returnValue = WikiNodeServiceUtil.addNode(readRoles,
					writeRoles, name, description, sharing);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteNode(java.lang.String nodeId)
		throws RemoteException {
		try {
			WikiNodeServiceUtil.deleteNode(nodeId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteNode(com.liferay.portlet.wiki.model.WikiNode node)
		throws RemoteException {
		try {
			WikiNodeServiceUtil.deleteNode(node);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiNodeModel getNode(
		java.lang.String nodeId) throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiNode returnValue = WikiNodeServiceUtil.getNode(nodeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiNodeModel[] getNodesByCompany()
		throws RemoteException {
		try {
			java.util.List returnValue = WikiNodeServiceUtil.getNodesByCompany();

			return (com.liferay.portlet.wiki.model.WikiNode[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiNode[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiNodeModel[] getNodesByUser()
		throws RemoteException {
		try {
			java.util.List returnValue = WikiNodeServiceUtil.getNodesByUser();

			return (com.liferay.portlet.wiki.model.WikiNode[])returnValue.toArray(new com.liferay.portlet.wiki.model.WikiNode[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void reIndex(java.lang.String[] ids)
		throws RemoteException {
		try {
			WikiNodeServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String[] nodeIds,
		java.lang.String keywords) throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = WikiNodeServiceUtil.search(companyId,
					portletId, groupId, nodeIds, keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.wiki.model.WikiNodeModel updateNode(
		java.lang.String nodeId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description, boolean sharing)
		throws RemoteException {
		try {
			com.liferay.portlet.wiki.model.WikiNode returnValue = WikiNodeServiceUtil.updateNode(nodeId,
					readRoles, writeRoles, name, description, sharing);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin() throws RemoteException {
		try {
			boolean returnValue = WikiNodeServiceUtil.hasAdmin();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String nodeId)
		throws RemoteException {
		try {
			boolean returnValue = WikiNodeServiceUtil.hasAdmin(nodeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRead(java.lang.String nodeId)
		throws RemoteException {
		try {
			boolean returnValue = WikiNodeServiceUtil.hasRead(nodeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWrite(java.lang.String nodeId)
		throws RemoteException {
		try {
			boolean returnValue = WikiNodeServiceUtil.hasWrite(nodeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}