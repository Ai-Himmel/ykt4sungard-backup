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

package com.liferay.portlet.imagegallery.service.impl;

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
import com.liferay.portlet.imagegallery.FolderNameException;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.model.impl.IGFolderImpl;
import com.liferay.portlet.imagegallery.service.base.IGFolderLocalServiceBaseImpl;
import com.liferay.portlet.imagegallery.util.Indexer;
import com.liferay.util.lucene.HitsImpl;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="IGFolderLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IGFolderLocalServiceImpl extends IGFolderLocalServiceBaseImpl {

	public IGFolder addFolder(
			long userId, long plid, long parentFolderId, String name,
			String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFolder(
			null, userId, plid, parentFolderId, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public IGFolder addFolder(
			String uuid, long userId, long plid, long parentFolderId,
			String name, String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFolder(
			uuid, userId, plid, parentFolderId, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public IGFolder addFolder(
			long userId, long plid, long parentFolderId, String name,
			String description, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		return addFolder(
			null, userId, plid, parentFolderId, name, description, null, null,
			communityPermissions, guestPermissions);
	}

	public IGFolder addFolder(
			String uuid, long userId, long plid, long parentFolderId,
			String name, String description, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		long groupId = PortalUtil.getPortletGroupId(plid);

		return addFolderToGroup(
			uuid, userId, groupId, parentFolderId, name, description,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public IGFolder addFolderToGroup(
			String uuid, long userId, long groupId, long parentFolderId,
			String name, String description, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		// Folder

		User user = userPersistence.findByPrimaryKey(userId);
		parentFolderId = getParentFolderId(groupId, parentFolderId);
		Date now = new Date();

		validate(name);

		long folderId = counterLocalService.increment();

		IGFolder folder = igFolderPersistence.create(folderId);

		folder.setUuid(uuid);
		folder.setGroupId(groupId);
		folder.setCompanyId(user.getCompanyId());
		folder.setUserId(user.getUserId());
		folder.setCreateDate(now);
		folder.setModifiedDate(now);
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);
		folder.setDescription(description);

		igFolderPersistence.update(folder);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addFolderResources(
				folder, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addFolderResources(folder, communityPermissions, guestPermissions);
		}

		return folder;
	}

	public void addFolderResources(
			long folderId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		IGFolder folder = igFolderPersistence.findByPrimaryKey(folderId);

		addFolderResources(
			folder, addCommunityPermissions, addGuestPermissions);
	}

	public void addFolderResources(
			IGFolder folder, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			folder.getCompanyId(), folder.getGroupId(), folder.getUserId(),
			IGFolder.class.getName(), folder.getFolderId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addFolderResources(
			long folderId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		IGFolder folder = igFolderPersistence.findByPrimaryKey(folderId);

		addFolderResources(folder, communityPermissions, guestPermissions);
	}

	public void addFolderResources(
			IGFolder folder, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			folder.getCompanyId(), folder.getGroupId(), folder.getUserId(),
			IGFolder.class.getName(), folder.getFolderId(),
			communityPermissions, guestPermissions);
	}

	public void deleteFolder(long folderId)
		throws PortalException, SystemException {

		IGFolder folder = igFolderPersistence.findByPrimaryKey(folderId);

		deleteFolder(folder);
	}

	public void deleteFolder(IGFolder folder)
		throws PortalException, SystemException {

		// Folders

		Iterator itr = igFolderPersistence.findByG_P(
			folder.getGroupId(), folder.getFolderId()).iterator();

		while (itr.hasNext()) {
			IGFolder curFolder = (IGFolder)itr.next();

			deleteFolder(curFolder);
		}

		// Images

		igImageLocalService.deleteImages(folder.getFolderId());

		// Resources

		resourceLocalService.deleteResource(
			folder.getCompanyId(), IGFolder.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, folder.getFolderId());

		// Folder

		igFolderPersistence.remove(folder.getFolderId());
	}

	public void deleteFolders(long groupId)
		throws PortalException, SystemException {

		Iterator itr = igFolderPersistence.findByG_P(
			groupId, IGFolderImpl.DEFAULT_PARENT_FOLDER_ID).iterator();

		while (itr.hasNext()) {
			IGFolder folder = (IGFolder)itr.next();

			deleteFolder(folder);
		}
	}

	public IGFolder getFolder(long folderId)
		throws PortalException, SystemException {

		return igFolderPersistence.findByPrimaryKey(folderId);
	}

	public List getFolders(long groupId) throws SystemException {
		return igFolderPersistence.findByGroupId(groupId);
	}

	public List getFolders(long groupId, long parentFolderId)
		throws SystemException {

		return igFolderPersistence.findByG_P(groupId, parentFolderId);
	}

	public List getFolders(
			long groupId, long parentFolderId, int begin, int end)
		throws SystemException {

		return igFolderPersistence.findByG_P(
			groupId, parentFolderId, begin, end);
	}

	public int getFoldersCount(long groupId, long parentFolderId)
		throws SystemException {

		return igFolderPersistence.countByG_P(groupId, parentFolderId);
	}

	public void getSubfolderIds(
			List folderIds, long groupId, long folderId)
		throws SystemException {

		Iterator itr = igFolderPersistence.findByG_P(
			groupId, folderId).iterator();

		while (itr.hasNext()) {
			IGFolder folder = (IGFolder)itr.next();

			folderIds.add(new Long(folder.getFolderId()));

			getSubfolderIds(
				folderIds, folder.getGroupId(), folder.getFolderId());
		}
	}

	public void reIndex(String[] ids) throws SystemException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		long companyId = GetterUtil.getLong(ids[0]);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			Iterator itr1 = igFolderPersistence.findByCompanyId(
				companyId).iterator();

			while (itr1.hasNext()) {
				IGFolder folder = (IGFolder)itr1.next();

				long folderId = folder.getFolderId();

				Iterator itr2 = igImagePersistence.findByFolderId(
					folderId).iterator();

				while (itr2.hasNext()) {
					IGImage image = (IGImage)itr2.next();

					long groupId = folder.getGroupId();
					long imageId = image.getImageId();
					String description = image.getDescription();

					String[] tagsEntries = tagsEntryLocalService.getEntryNames(
						IGImage.class.getName(), imageId);

					try {
						Document doc = Indexer.getAddImageDocument(
							companyId, groupId, folderId, imageId, description,
							tagsEntries);

						writer.addDocument(doc);
					}
					catch (Exception e1) {
						_log.error("Reindexing " + imageId, e1);
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
			long companyId, long groupId, long[] folderIds, String keywords)
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

			if ((folderIds != null) && (folderIds.length > 0)) {
				BooleanQuery folderIdsQuery = new BooleanQuery();

				for (int i = 0; i < folderIds.length; i++) {
					Term term = new Term(
						"folderId", String.valueOf(folderIds[i]));
					TermQuery termQuery = new TermQuery(term);

					folderIdsQuery.add(termQuery, BooleanClause.Occur.SHOULD);
				}

				contextQuery.add(folderIdsQuery, BooleanClause.Occur.MUST);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.DESCRIPTION, keywords);
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

	public IGFolder updateFolder(
			long folderId, long parentFolderId, String name, String description,
			boolean mergeWithParentFolder)
		throws PortalException, SystemException {

		// Folder

		IGFolder folder = igFolderPersistence.findByPrimaryKey(folderId);

		parentFolderId = getParentFolderId(folder, parentFolderId);

		validate(name);

		folder.setModifiedDate(new Date());
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);
		folder.setDescription(description);

		igFolderPersistence.update(folder);

		// Merge folders

		if (mergeWithParentFolder && (folderId != parentFolderId) &&
			(parentFolderId != IGFolderImpl.DEFAULT_PARENT_FOLDER_ID)) {

			mergeFolders(folder, parentFolderId);
		}

		return folder;
	}

	protected long getParentFolderId(long groupId, long parentFolderId)
		throws SystemException {

		if (parentFolderId != IGFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			IGFolder parentFolder = igFolderPersistence.fetchByPrimaryKey(
				parentFolderId);

			if ((parentFolder == null) ||
				(groupId != parentFolder.getGroupId())) {

				parentFolderId = IGFolderImpl.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return parentFolderId;
	}

	protected long getParentFolderId(IGFolder folder, long parentFolderId)
		throws SystemException {

		if (parentFolderId == IGFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			return parentFolderId;
		}

		if (folder.getFolderId() == parentFolderId) {
			return folder.getParentFolderId();
		}
		else {
			IGFolder parentFolder = igFolderPersistence.fetchByPrimaryKey(
				parentFolderId);

			if ((parentFolder == null) ||
				(folder.getGroupId() != parentFolder.getGroupId())) {

				return folder.getParentFolderId();
			}

			List subfolderIds = new ArrayList();

			getSubfolderIds(
				subfolderIds, folder.getGroupId(), folder.getFolderId());

			if (subfolderIds.contains(new Long(parentFolderId))) {
				return folder.getParentFolderId();
			}

			return parentFolderId;
		}
	}

	protected void mergeFolders(IGFolder fromFolder, long toFolderId)
		throws PortalException, SystemException {

		Iterator itr = igFolderPersistence.findByG_P(
			fromFolder.getGroupId(), fromFolder.getFolderId()).iterator();

		while (itr.hasNext()) {
			IGFolder folder = (IGFolder)itr.next();

			mergeFolders(folder, toFolderId);
		}

		itr = igImagePersistence.findByFolderId(
			fromFolder.getFolderId()).iterator();

		while (itr.hasNext()) {

			// Image

			IGImage image = (IGImage)itr.next();

			image.setFolderId(toFolderId);

			igImagePersistence.update(image);
		}

		igFolderPersistence.remove(fromFolder.getFolderId());
	}

	protected void validate(String name) throws PortalException {
		if ((Validator.isNull(name)) || (name.indexOf("\\\\") != -1) ||
			(name.indexOf("//") != -1)) {

			throw new FolderNameException();
		}
	}

	private static Log _log = LogFactory.getLog(IGFolderLocalServiceImpl.class);

}