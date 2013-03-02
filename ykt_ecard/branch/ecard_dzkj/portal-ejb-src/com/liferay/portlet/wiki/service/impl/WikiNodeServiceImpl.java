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

package com.liferay.portlet.wiki.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.NodeNameException;
import com.liferay.portlet.wiki.NodeReadRolesException;
import com.liferay.portlet.wiki.NodeWriteRolesException;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.persistence.WikiNodeUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageUtil;
import com.liferay.portlet.wiki.service.spring.WikiNodeLocalServiceUtil;
import com.liferay.portlet.wiki.service.spring.WikiNodeService;
import com.liferay.portlet.wiki.util.Indexer;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lucene.Hits;

import java.io.IOException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.WhitespaceAnalyzer;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="WikiNodeServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class WikiNodeServiceImpl
	extends PrincipalBean implements WikiNodeService {

	// Business methods

	public WikiNode addNode(
			String readRoles, String writeRoles, String name,
			String description, boolean sharing)
		throws PortalException, SystemException {

		_validate(readRoles, writeRoles, name);

		User user = getUser();

		String nodeId = Long.toString(CounterServiceUtil.increment(
			WikiNode.class.getName()));

		WikiNode node = WikiNodeUtil.create(nodeId);

		Date now = new Date();

		node.setCompanyId(user.getCompanyId());
		node.setUserId(user.getUserId());
		node.setUserName(user.getFullName());
		node.setCreateDate(now);
		node.setModifiedDate(now);
		node.setReadRoles(readRoles);
		node.setWriteRoles(writeRoles);
		node.setName(name);
		node.setDescription(description);
		node.setSharing(sharing);

		WikiNodeUtil.update(node);

		return node;
	}

	public void deleteNode(String nodeId)
		throws PortalException, SystemException {

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		deleteNode(node);
	}

	public void deleteNode(WikiNode node)
		throws PortalException, SystemException {

		if (!hasAdmin(node.getNodeId())) {
			throw new PrincipalException();
		}

		WikiNodeLocalServiceUtil.deleteNode(node);
	}

	public WikiNode getNode(String nodeId)
		throws PortalException, SystemException {

		if (!hasRead(nodeId)) {
			throw new PrincipalException();
		}

		return WikiNodeUtil.findByPrimaryKey(nodeId);
	}

	public List getNodesByCompany() throws PortalException, SystemException {
		List list = WikiNodeUtil.findByC_S(getUser().getCompanyId(), true);

		Iterator itr = list.iterator();

		while (itr.hasNext()) {
			WikiNode node = (WikiNode)itr.next();

			try {
				if (!hasRead(node.getNodeId())) {
					itr.remove();
				}
			}
			catch (NoSuchNodeException nste) {
			}
		}

		return list;
	}

	public List getNodesByUser() throws PortalException, SystemException {
		return WikiNodeUtil.findByU_S(getUserId(), false);
	}

	public void reIndex(String[] ids) throws SystemException {
		try {
			String companyId = ids[0];

			Iterator itr1 = WikiNodeUtil.findByCompanyId(companyId).iterator();

			while (itr1.hasNext()) {
				WikiNode node = (WikiNode)itr1.next();

				String nodeId = node.getNodeId();

				Iterator itr2 = WikiPageUtil.findByNodeId(nodeId).iterator();

				while (itr2.hasNext()) {
					WikiPage page = (WikiPage)itr2.next();

					String portletId = node.getPortletId();
					String groupId = node.getGroupId();
					String title = page.getTitle();
					String content = page.getContent();

					try {
						Indexer.addPage(
							companyId, portletId, groupId, nodeId, title,
							content);
					}
					catch (Exception e1) {

						// Continue indexing even if one page fails

						_log.error(e1.getMessage());
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
	}

	public Hits search(
			String companyId, String portletId, String groupId,
			String[] nodeIds, String keywords)
		throws SystemException {

		try {
			Hits hits = new Hits();

			if (Validator.isNull(keywords)) {
				return hits;
			}

			BooleanQuery booleanQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.PORTLET_ID, portletId);
			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.GROUP_ID, groupId);

			LuceneUtil.addTerm(booleanQuery, LuceneFields.CONTENT, keywords);

			if ((nodeIds != null) && (nodeIds.length > 0)) {
				BooleanQuery nodeIdsQuery = new BooleanQuery();

				for (int i = 0; i < nodeIds.length; i++) {
					nodeIdsQuery.add(new TermQuery(new Term(
						"nodeId", nodeIds[i])), false, false);
				}

				booleanQuery.add(nodeIdsQuery, true, false);
			}

			Searcher searcher = LuceneUtil.getSearcher(companyId);

			Query query = QueryParser.parse(
				booleanQuery.toString(), LuceneFields.CONTENT,
				new WhitespaceAnalyzer());

			hits.recordHits(searcher.search(query));

			return hits;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (ParseException pe) {
			throw new SystemException(pe);
		}
	}

	public WikiNode updateNode(
			String nodeId, String readRoles, String writeRoles, String name,
			String description, boolean sharing)
		throws PortalException, SystemException {

		_validate(readRoles, writeRoles, name);

		if (!hasAdmin(nodeId)) {
			throw new PrincipalException();
		}

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		node.setModifiedDate(new Date());
		node.setReadRoles(readRoles);
		node.setWriteRoles(writeRoles);
		node.setName(name);
		node.setDescription(description);
		node.setSharing(sharing);

		WikiNodeUtil.update(node);

		return node;
	}

	// Permission methods

	public boolean hasAdmin() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.WIKI_ADMIN)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasAdmin(String nodeId)
		throws PortalException, SystemException {

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		if ((node.getUserId().equals(getUserId())) ||
			(getUser().getCompanyId().equals(node.getCompanyId()) &&
			 RoleServiceUtil.hasRole(getUserId(), Role.WIKI_ADMIN))) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasRead(String nodeId)
		throws PortalException, SystemException {

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		if (getUser().getCompanyId().equals(node.getCompanyId()) &&
			RoleServiceUtil.hasRoles(
				getUserId(), StringUtil.split(node.getReadRoles()))) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasWrite(String nodeId)
		throws PortalException, SystemException {

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		if (getUser().getCompanyId().equals(node.getCompanyId()) &&
			RoleServiceUtil.hasRoles(
				getUserId(), StringUtil.split(node.getWriteRoles()))) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private void _validate(String readRoles, String writeRoles, String name)
		throws PortalException, SystemException {

		String[] readRolesArray = StringUtil.split(readRoles);

		if (readRolesArray.length == 0 ||
			!RoleServiceUtil.exists(readRolesArray)) {

			throw new NodeReadRolesException();
		}

		String[] writeRolesArray = StringUtil.split(writeRoles);

		if (writeRolesArray.length == 0 ||
			!RoleServiceUtil.exists(writeRolesArray)) {

			throw new NodeWriteRolesException();
		}

		if (!Validator.isName(name)) {
			throw new NodeNameException();
		}
	}

	private static final Log _log =
		LogFactory.getLog(WikiNodeServiceImpl.class);

}