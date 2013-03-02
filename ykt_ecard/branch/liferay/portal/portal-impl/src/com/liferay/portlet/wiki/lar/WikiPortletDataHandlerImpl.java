/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portlet.wiki.lar;

import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.NoSuchPageException;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.WikiNodeLocalServiceUtil;
import com.liferay.portlet.wiki.service.WikiPageLocalServiceUtil;
import com.liferay.portlet.wiki.service.persistence.WikiNodeUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageFinderUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.MapUtil;

import com.thoughtworks.xstream.XStream;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="WikiPortletDataHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class WikiPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Nodes

			if (!context.addPrimaryKey(
					WikiPortletDataHandlerImpl.class, "deleteData")) {

				WikiNodeLocalServiceUtil.deleteNodes(context.getGroupId());
			}
			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public String exportData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = DocumentHelper.createDocument();

			Element root = doc.addElement("wiki-data");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Nodes

			List nodes = WikiNodeUtil.findByGroupId(context.getGroupId());

			List pages = new ArrayList();

			Iterator itr = nodes.iterator();

			while (itr.hasNext()) {
				WikiNode node = (WikiNode)itr.next();

				if (context.addPrimaryKey(
						WikiNode.class, node.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					node.setUserUuid(node.getUserUuid());

					List nodePages = WikiPageUtil.findByNodeId(
						node.getNodeId());

					pages.addAll(nodePages);
				}
			}

			String xml = xStream.toXML(nodes);

			Element el = root.addElement("wiki-nodes");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Pages

			itr = pages.iterator();

			while (itr.hasNext()) {
				WikiPage page = (WikiPage)itr.next();

				if (context.addPrimaryKey(
						WikiPage.class, page.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					page.setUserUuid(page.getUserUuid());

					if (context.getBooleanParameter(_NAMESPACE, "comments")) {
						context.addComments(
							WikiPage.class,
							new Long(page.getResourcePrimKey()));
					}

					if (context.getBooleanParameter(_NAMESPACE, "tags")) {
						context.addTagsEntries(
							WikiPage.class,
							new Long(page.getResourcePrimKey()));
					}
				}
			}

			xml = xStream.toXML(pages);

			el = root.addElement("wiki-pages");

			tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			return doc.asXML();
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public PortletDataHandlerControl[] getExportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {
			_nodesAndPages, _comments, _tags
		};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {
			_nodesAndPages, _comments, _tags
		};
	}

	public PortletPreferences importData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs, String data)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = PortalUtil.readDocumentFromXML(data);

			Element root = doc.getRootElement();

			// Nodes

			Element el = root.element("wiki-nodes").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map nodePKs = CollectionFactory.getHashMap();

			List nodes = (List)xStream.fromXML(tempDoc.asXML());

			Iterator itr = nodes.iterator();

			while (itr.hasNext()) {
				WikiNode node = (WikiNode)itr.next();

				importNode(context, nodePKs, node);
			}

			// Pages

			el = root.element("wiki-pages").element("list");

			tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			List pages = (List)xStream.fromXML(tempDoc.asXML());

			itr = pages.iterator();

			while (itr.hasNext()) {
				WikiPage page = (WikiPage)itr.next();

				importPage(context, nodePKs, page);
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected void importNode(
			PortletDataContext context, Map nodePKs, WikiNode node)
		throws Exception {

		long userId = context.getUserId(node.getUserUuid());
		long plid = context.getPlid();

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		WikiNode existingNode = null;

		if (context.getDataStrategy().equals(
				PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

			existingNode = WikiNodeUtil.fetchByUUID_G(
				node.getUuid(), context.getGroupId());

			if (existingNode == null) {
				existingNode = WikiNodeLocalServiceUtil.addNode(
					node.getUuid(), userId, plid, node.getName(),
					node.getDescription(), addCommunityPermissions,
					addGuestPermissions);
			}
			else {
				existingNode = WikiNodeLocalServiceUtil.updateNode(
					existingNode.getNodeId(), node.getName(),
					node.getDescription());
			}
		}
		else {
			existingNode = WikiNodeLocalServiceUtil.addNode(
				userId, plid, node.getName(), node.getDescription(),
				addCommunityPermissions, addGuestPermissions);
		}

		nodePKs.put(node.getPrimaryKeyObj(), existingNode.getPrimaryKeyObj());
	}

	protected void importPage(
			PortletDataContext context, Map nodePKs, WikiPage page)
		throws Exception {

		long userId = context.getUserId(page.getUserUuid());
		long nodeId = MapUtil.getLong(
			nodePKs, page.getNodeId(), page.getNodeId());

		String[] tagsEntries = null;

		if (context.getBooleanParameter(_NAMESPACE, "tags")) {
			tagsEntries = context.getTagsEntries(
				WikiPage.class, page.getPrimaryKeyObj());
		}

		WikiPage existingPage = null;

		try {
			WikiNodeUtil.findByPrimaryKey(nodeId);

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				try {
					existingPage = WikiPageFinderUtil.findByUuid_G(
						page.getUuid(), context.getGroupId());

					existingPage = WikiPageLocalServiceUtil.updatePage(
						userId, nodeId, existingPage.getTitle(),
						page.getContent(), page.getFormat(), tagsEntries);
				}
				catch (NoSuchPageException nspe) {
					existingPage = WikiPageLocalServiceUtil.addPage(
						page.getUuid(), userId, nodeId, page.getTitle(),
						page.getVersion(), page.getContent(), page.getFormat(),
						page.getHead(), tagsEntries);
				}
			}
			else {
				existingPage = WikiPageLocalServiceUtil.addPage(
					userId, nodeId, page.getTitle(), page.getVersion(),
					page.getContent(), page.getFormat(), page.getHead(),
					tagsEntries);
			}

			if (context.getBooleanParameter(_NAMESPACE, "comments")) {
				context.importComments(
					WikiPage.class, new Long(page.getResourcePrimKey()),
					new Long(existingPage.getResourcePrimKey()),
					context.getGroupId());
			}

			if (context.getBooleanParameter(_NAMESPACE, "ratings")) {
				context.importRatingsEntries(
					WikiPage.class, new Long(page.getResourcePrimKey()),
					new Long(existingPage.getResourcePrimKey()));
			}
		}
		catch (NoSuchNodeException nsne) {
			_log.error(
				"Could not find the node for page " +
					page.getPageId());
		}
	}

	private static final String _NAMESPACE = "wiki";

	private static final PortletDataHandlerBoolean _nodesAndPages =
		new PortletDataHandlerBoolean(
			_NAMESPACE, "nodes-and-pages", true, true);

	private static final PortletDataHandlerBoolean _comments =
		new PortletDataHandlerBoolean(_NAMESPACE, "comments");

	private static final PortletDataHandlerBoolean _tags =
		new PortletDataHandlerBoolean(_NAMESPACE, "tags");

	private static Log _log =
		LogFactory.getLog(WikiPortletDataHandlerImpl.class);

}