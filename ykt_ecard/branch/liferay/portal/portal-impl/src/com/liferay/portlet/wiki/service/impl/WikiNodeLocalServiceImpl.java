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

package com.liferay.portlet.wiki.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.wiki.NodeNameException;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.base.WikiNodeLocalServiceBaseImpl;
import com.liferay.portlet.wiki.util.Indexer;
import com.liferay.util.lucene.HitsImpl;

import java.io.IOException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="WikiNodeLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Charles May
 *
 */
public class WikiNodeLocalServiceImpl extends WikiNodeLocalServiceBaseImpl {

	public WikiNode addNode(
			long userId, long plid, String name, String description,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addNode(
			null, userId, plid, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public WikiNode addNode(
			String uuid, long userId, long plid, String name,
			String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addNode(
			uuid, userId, plid, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public WikiNode addNode(
			long userId, long plid, String name, String description,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		return addNode(
			null, userId, plid, name, description, null, null,
			communityPermissions, guestPermissions);
	}

	public WikiNode addNode(
			String uuid, long userId, long plid, String name,
			String description, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		// Node

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);
		Date now = new Date();

		validate(name);

		long nodeId = counterLocalService.increment();

		WikiNode node = wikiNodePersistence.create(nodeId);

		node.setUuid(uuid);
		node.setGroupId(groupId);
		node.setCompanyId(user.getCompanyId());
		node.setUserId(user.getUserId());
		node.setUserName(user.getFullName());
		node.setCreateDate(now);
		node.setModifiedDate(now);
		node.setName(name);
		node.setDescription(description);

		wikiNodePersistence.update(node);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addNodeResources(
				node, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addNodeResources(node, communityPermissions, guestPermissions);
		}

		return node;
	}

	public void addNodeResources(
			long nodeId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);

		addNodeResources(node, addCommunityPermissions, addGuestPermissions);
	}

	public void addNodeResources(
			WikiNode node, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			node.getCompanyId(), node.getGroupId(),	node.getUserId(),
			WikiNode.class.getName(), node.getNodeId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addNodeResources(
			long nodeId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);

		addNodeResources(node, communityPermissions, guestPermissions);
	}

	public void addNodeResources(
			WikiNode node, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			node.getCompanyId(), node.getGroupId(),	node.getUserId(),
			WikiNode.class.getName(), node.getNodeId(), communityPermissions,
			guestPermissions);
	}

	public void deleteNode(long nodeId)
		throws PortalException, SystemException {

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);

		deleteNode(node);
	}

	public void deleteNode(WikiNode node)
		throws PortalException, SystemException {

		// Lucene

		try {
			Indexer.deletePages(node.getCompanyId(), node.getNodeId());
		}
		catch (IOException ioe) {
			_log.error("Deleting index " + node.getNodeId(), ioe);
		}
		catch (ParseException pe) {
			_log.error("Deleting index " + node.getNodeId(), pe);
		}

		// Pages

		wikiPageLocalService.deletePages(node.getNodeId());

		// Resources

		resourceLocalService.deleteResource(
			node.getCompanyId(), WikiNode.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, node.getNodeId());

		// Node

		wikiNodePersistence.remove(node.getNodeId());
	}

	public void deleteNodes(long groupId)
		throws PortalException, SystemException {

		Iterator itr = wikiNodePersistence.findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			WikiNode node = (WikiNode)itr.next();

			deleteNode(node);
		}
	}

	public WikiNode getNode(long nodeId)
		throws PortalException, SystemException {

		return wikiNodePersistence.findByPrimaryKey(nodeId);
	}

	public List getNodes(long groupId) throws SystemException {
		return wikiNodePersistence.findByGroupId(groupId);
	}

	public List getNodes(long groupId, int begin, int end)
		throws SystemException {

		return wikiNodePersistence.findByGroupId(groupId, begin, end);
	}

	public int getNodesCount(long groupId) throws SystemException {
		return wikiNodePersistence.countByGroupId(groupId);
	}

	public void reIndex(String[] ids) throws SystemException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		long companyId = GetterUtil.getLong(ids[0]);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			Iterator itr1 = wikiNodePersistence.findByCompanyId(
				companyId).iterator();

			while (itr1.hasNext()) {
				WikiNode node = (WikiNode)itr1.next();

				long nodeId = node.getNodeId();

				Iterator itr2 = wikiPagePersistence.findByNodeId(
					nodeId).iterator();

				while (itr2.hasNext()) {
					WikiPage page = (WikiPage)itr2.next();

					long groupId = node.getGroupId();
					String title = page.getTitle();
					String content = page.getContent();

					String[] tagsEntries = tagsEntryLocalService.getEntryNames(
						WikiPage.class.getName(), page.getResourcePrimKey());

					try {
						Document doc = Indexer.getAddPageDocument(
							companyId, groupId, nodeId, title, content,
							tagsEntries);

						writer.addDocument(doc);
					}
					catch (Exception e1) {
						_log.error("Reindexing " + page.getPrimaryKey(), e1);
					}
				}
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e2) {
			throw new SystemException(e2);
		}
		finally {
			try {
				if (writer != null) {
					LuceneUtil.write(companyId);
				}
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
	}

	public Hits search(
			long companyId, long groupId, long[] nodeIds, String keywords)
		throws SystemException {

		Searcher searcher = null;

		try {
			HitsImpl hits = new HitsImpl();

			BooleanQuery contextQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				contextQuery, LuceneFields.PORTLET_ID, Indexer.PORTLET_ID);

			if (groupId > 0) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.GROUP_ID, groupId);
			}

			if ((nodeIds != null) && (nodeIds.length > 0)) {
				BooleanQuery nodeIdsQuery = new BooleanQuery();

				for (int i = 0; i < nodeIds.length; i++) {
					Term term = new Term("nodeId", String.valueOf(nodeIds[i]));
					TermQuery termQuery = new TermQuery(term);

					nodeIdsQuery.add(termQuery, BooleanClause.Occur.SHOULD);
				}

				contextQuery.add(nodeIdsQuery, BooleanClause.Occur.MUST);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(searchQuery, LuceneFields.TITLE, keywords);
				LuceneUtil.addTerm(searchQuery, LuceneFields.CONTENT, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.TAG_ENTRY, keywords);
			}

			BooleanQuery fullQuery = new BooleanQuery();

			fullQuery.add(contextQuery, BooleanClause.Occur.MUST);

			if (searchQuery.clauses().size() > 0) {
				fullQuery.add(searchQuery, BooleanClause.Occur.MUST);
			}

			searcher = LuceneUtil.getSearcher(companyId);

			hits.recordHits(searcher.search(fullQuery), searcher);

			return hits;
		}
		catch (Exception e) {
			return LuceneUtil.closeSearcher(searcher, keywords, e);
		}
	}

	public WikiNode updateNode(long nodeId, String name, String description)
		throws PortalException, SystemException {

		validate(name);

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);

		node.setModifiedDate(new Date());
		node.setName(name);
		node.setDescription(description);

		wikiNodePersistence.update(node);

		return node;
	}

	protected void validate(String name) throws PortalException {
		if (!Validator.isName(name)) {
			throw new NodeNameException();
		}
	}

	private static Log _log = LogFactory.getLog(WikiNodeLocalServiceImpl.class);

}