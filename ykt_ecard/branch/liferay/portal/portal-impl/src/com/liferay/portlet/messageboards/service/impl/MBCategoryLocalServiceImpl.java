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

package com.liferay.portlet.messageboards.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.messageboards.CategoryNameException;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.portlet.messageboards.model.impl.MBCategoryImpl;
import com.liferay.portlet.messageboards.service.base.MBCategoryLocalServiceBaseImpl;
import com.liferay.portlet.messageboards.util.Indexer;
import com.liferay.util.lucene.HitsImpl;

import java.io.IOException;

import java.util.ArrayList;
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
 * <a href="MBCategoryLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBCategoryLocalServiceImpl extends MBCategoryLocalServiceBaseImpl {

	public MBCategory addCategory(
			long userId, long plid, long parentCategoryId, String name,
			String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addCategory(
			null, userId, plid, parentCategoryId, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public MBCategory addCategory(
			String uuid, long userId, long plid, long parentCategoryId,
			String name, String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addCategory(
			uuid, userId, plid, parentCategoryId, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public MBCategory addCategory(
			long userId, long plid, long parentCategoryId, String name,
			String description, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		return addCategory(
			null, userId, plid, parentCategoryId, name, description, null, null,
			communityPermissions, guestPermissions);
	}

	public MBCategory addCategory(
			String uuid, long userId, long plid, long parentCategoryId,
			String name, String description, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		// Category

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);
		parentCategoryId = getParentCategoryId(groupId, parentCategoryId);
		Date now = new Date();

		validate(name);

		long categoryId = counterLocalService.increment();

		MBCategory category = mbCategoryPersistence.create(categoryId);

		category.setUuid(uuid);
		category.setGroupId(groupId);
		category.setCompanyId(user.getCompanyId());
		category.setUserId(user.getUserId());
		category.setUserName(user.getFullName());
		category.setCreateDate(now);
		category.setModifiedDate(now);
		category.setParentCategoryId(parentCategoryId);
		category.setName(name);
		category.setDescription(description);

		mbCategoryPersistence.update(category);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addCategoryResources(
				category, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addCategoryResources(
				category, communityPermissions, guestPermissions);
		}

		return category;
	}

	public void addCategoryResources(
			long categoryId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);

		addCategoryResources(
			category, addCommunityPermissions, addGuestPermissions);
	}

	public void addCategoryResources(
			MBCategory category, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			category.getCompanyId(), category.getGroupId(),
			category.getUserId(), MBCategory.class.getName(),
			category.getCategoryId(), false, addCommunityPermissions,
			addGuestPermissions);
	}

	public void addCategoryResources(
			long categoryId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);

		addCategoryResources(category, communityPermissions, guestPermissions);
	}

	public void addCategoryResources(
			MBCategory category, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			category.getCompanyId(), category.getGroupId(),
			category.getUserId(), MBCategory.class.getName(),
			category.getCategoryId(), communityPermissions, guestPermissions);
	}

	public void deleteCategories(long groupId)
		throws PortalException, SystemException {

		Iterator itr = mbCategoryPersistence.findByG_P(
			groupId, MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID).iterator();

		while (itr.hasNext()) {
			MBCategory category = (MBCategory)itr.next();

			deleteCategory(category);
		}
	}

	public void deleteCategory(long categoryId)
		throws PortalException, SystemException {

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);

		deleteCategory(category);
	}

	public void deleteCategory(MBCategory category)
		throws PortalException, SystemException {

		// Categories

		Iterator itr = mbCategoryPersistence.findByG_P(
			category.getGroupId(), category.getCategoryId()).iterator();

		while (itr.hasNext()) {
			MBCategory curCategory = (MBCategory)itr.next();

			deleteCategory(curCategory);
		}

		// Lucene

		try {
			Indexer.deleteMessages(
				category.getCompanyId(), category.getCategoryId());
		}
		catch (IOException ioe) {
			_log.error("Deleting index " + category.getCategoryId(), ioe);
		}
		catch (ParseException pe) {
			_log.error("Deleting index " + category.getCategoryId(), pe);
		}

		// Threads

		mbThreadLocalService.deleteThreads(category.getCategoryId());

		// Resources

		resourceLocalService.deleteResource(
			category.getCompanyId(), MBCategory.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, category.getCategoryId());

		// Category

		mbCategoryPersistence.remove(category.getCategoryId());
	}

	public List getCategories(
			long groupId, long parentCategoryId, int begin, int end)
		throws SystemException {

		return mbCategoryPersistence.findByG_P(
			groupId, parentCategoryId, begin, end);
	}

	public int getCategoriesCount(long groupId) throws SystemException {
		return mbCategoryPersistence.countByGroupId(groupId);
	}

	public int getCategoriesCount(long groupId, long parentCategoryId)
		throws SystemException {

		return mbCategoryPersistence.countByG_P(groupId, parentCategoryId);
	}

	public MBCategory getCategory(long categoryId)
		throws PortalException, SystemException {

		return mbCategoryPersistence.findByPrimaryKey(categoryId);
	}

	public void getSubcategoryIds(
			List categoryIds, long groupId, long categoryId)
		throws SystemException {

		Iterator itr = mbCategoryPersistence.findByG_P(
			groupId, categoryId).iterator();

		while (itr.hasNext()) {
			MBCategory category = (MBCategory)itr.next();

			categoryIds.add(new Long(category.getCategoryId()));

			getSubcategoryIds(
				categoryIds, category.getGroupId(), category.getCategoryId());
		}
	}

	public List getSubscribedCategories(
			long groupId, long userId, int begin, int end)
		throws SystemException {

		return mbCategoryFinder.findByS_G_U(groupId, userId, begin, end);
	}

	public int getSubscribedCategoriesCount(long groupId, long userId)
		throws SystemException {

		return mbCategoryFinder.countByS_G_U(groupId, userId);
	}

	public MBCategory getSystemCategory()
		throws PortalException, SystemException {

		long categoryId = CompanyImpl.SYSTEM;

		MBCategory category = mbCategoryPersistence.fetchByPrimaryKey(
			categoryId);

		if (category == null) {
			category = mbCategoryPersistence.create(categoryId);

			category.setCompanyId(CompanyImpl.SYSTEM);
			category.setUserId(CompanyImpl.SYSTEM);

			mbCategoryPersistence.update(category);
		}

		return category;
	}

	public void reIndex(String[] ids) throws SystemException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		long companyId = GetterUtil.getLong(ids[0]);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			Iterator itr1 = mbCategoryPersistence.findByCompanyId(
				companyId).iterator();

			while (itr1.hasNext()) {
				MBCategory category = (MBCategory)itr1.next();

				long categoryId = category.getCategoryId();

				Iterator itr2 = mbMessagePersistence.findByCategoryId(
					categoryId).iterator();

				while (itr2.hasNext()) {
					MBMessage message = (MBMessage)itr2.next();

					long groupId = category.getGroupId();
					String userName = message.getUserName();
					long threadId = message.getThreadId();
					long messageId = message.getMessageId();
					String title = message.getSubject();
					String content = message.getBody();

					String[] tagsEntries = tagsEntryLocalService.getEntryNames(
						MBMessage.class.getName(), messageId);

					try {
						Document doc = Indexer.getAddMessageDocument(
							companyId, groupId, userName, categoryId, threadId,
							messageId, title, content, tagsEntries);

						writer.addDocument(doc);
					}
					catch (Exception e1) {
						_log.error("Reindexing " + messageId, e1);
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
			long companyId, long groupId, long[] categoryIds, long threadId,
			String keywords)
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

			if ((categoryIds != null) && (categoryIds.length > 0)) {
				BooleanQuery categoryIdsQuery = new BooleanQuery();

				for (int i = 0; i < categoryIds.length; i++) {
					Term term = new Term(
						"categoryId", String.valueOf(categoryIds[i]));
					TermQuery termQuery = new TermQuery(term);

					categoryIdsQuery.add(termQuery, BooleanClause.Occur.SHOULD);
				}

				contextQuery.add(categoryIdsQuery, BooleanClause.Occur.MUST);
			}

			if (threadId > 0) {
				LuceneUtil.addTerm(contextQuery, "threadId", threadId);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.USER_NAME, keywords);
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

	public MBCategory updateCategory(
			long categoryId, long parentCategoryId, String name,
			String description, boolean mergeWithParentCategory)
		throws PortalException, SystemException {

		// Category

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);

		parentCategoryId = getParentCategoryId(category, parentCategoryId);

		validate(name);

		category.setModifiedDate(new Date());
		category.setParentCategoryId(parentCategoryId);
		category.setName(name);
		category.setDescription(description);

		mbCategoryPersistence.update(category);

		// Merge categories

		if (mergeWithParentCategory &&
			(categoryId != parentCategoryId) &&
			(parentCategoryId != MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID)) {

			mergeCategories(category, parentCategoryId);
		}

		return category;
	}

	protected long getParentCategoryId(long groupId, long parentCategoryId)
		throws SystemException {

		if (parentCategoryId != MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID) {
			MBCategory parentCategory = mbCategoryPersistence.fetchByPrimaryKey(
				parentCategoryId);

			if ((parentCategory == null) ||
				(groupId != parentCategory.getGroupId())) {

				parentCategoryId = MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID;
			}
		}

		return parentCategoryId;
	}

	protected long getParentCategoryId(
			MBCategory category, long parentCategoryId)
		throws SystemException {

		if (parentCategoryId == MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID) {
			return parentCategoryId;
		}

		if (category.getCategoryId() == parentCategoryId) {
			return category.getParentCategoryId();
		}
		else {
			MBCategory parentCategory = mbCategoryPersistence.fetchByPrimaryKey(
				parentCategoryId);

			if ((parentCategory == null) ||
				(category.getGroupId() != parentCategory.getGroupId())) {

				return category.getParentCategoryId();
			}

			List subcategoryIds = new ArrayList();

			getSubcategoryIds(
				subcategoryIds, category.getGroupId(),
				category.getCategoryId());

			if (subcategoryIds.contains(new Long(parentCategoryId))) {
				return category.getParentCategoryId();
			}

			return parentCategoryId;
		}
	}

	protected void mergeCategories(MBCategory fromCategory, long toCategoryId)
		throws PortalException, SystemException {

		Iterator itr = mbCategoryPersistence.findByG_P(
			fromCategory.getGroupId(), fromCategory.getCategoryId()).iterator();

		while (itr.hasNext()) {
			MBCategory category = (MBCategory)itr.next();

			mergeCategories(category, toCategoryId);
		}

		Iterator itr1 = mbThreadPersistence.findByCategoryId(
			fromCategory.getCategoryId()).iterator();

		while (itr1.hasNext()) {

			// Thread

			MBThread thread = (MBThread)itr1.next();

			thread.setCategoryId(toCategoryId);

			mbThreadPersistence.update(thread);

			Iterator itr2 = mbMessagePersistence.findByThreadId(
				thread.getThreadId()).iterator();

			while (itr2.hasNext()) {

				// Message

				MBMessage message = (MBMessage)itr2.next();

				message.setCategoryId(toCategoryId);

				mbMessagePersistence.update(message);

				// Lucene

				try {
					if (!fromCategory.isDiscussion()) {
						String[] tagsEntries =
							tagsEntryLocalService.getEntryNames(
								MBMessage.class.getName(),
								message.getMessageId());

						Indexer.updateMessage(
							message.getCompanyId(), fromCategory.getGroupId(),
							message.getUserName(), toCategoryId,
							message.getThreadId(), message.getMessageId(),
							message.getSubject(), message.getBody(),
							tagsEntries);
					}
				}
				catch (IOException ioe) {
					_log.error("Indexing " + message.getMessageId(), ioe);
				}
			}
		}

		mbCategoryPersistence.remove(fromCategory.getCategoryId());
	}

	public void subscribeCategory(long userId, long categoryId)
		throws PortalException, SystemException {

		subscriptionLocalService.addSubscription(
			userId, MBCategory.class.getName(), categoryId);
	}

	public void unsubscribeCategory(long userId, long categoryId)
		throws PortalException, SystemException {

		subscriptionLocalService.deleteSubscription(
			userId, MBCategory.class.getName(), categoryId);
	}

	protected void validate(String name) throws PortalException {
		if (Validator.isNull(name)) {
			throw new CategoryNameException();
		}
	}

	private static Log _log =
		LogFactory.getLog(MBCategoryLocalServiceImpl.class);

}