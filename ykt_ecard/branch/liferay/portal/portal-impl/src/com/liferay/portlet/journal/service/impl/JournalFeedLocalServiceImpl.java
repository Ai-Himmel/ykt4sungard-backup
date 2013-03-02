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

package com.liferay.portlet.journal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.journal.DuplicateFeedIdException;
import com.liferay.portlet.journal.FeedContentFieldException;
import com.liferay.portlet.journal.FeedDescriptionException;
import com.liferay.portlet.journal.FeedIdException;
import com.liferay.portlet.journal.FeedNameException;
import com.liferay.portlet.journal.FeedTargetLayoutFriendlyUrlException;
import com.liferay.portlet.journal.NoSuchFeedException;
import com.liferay.portlet.journal.model.JournalFeed;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.impl.JournalFeedImpl;
import com.liferay.portlet.journal.service.base.JournalFeedLocalServiceBaseImpl;
import com.liferay.util.RSSUtil;

import java.util.Date;
import java.util.List;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.XPath;

/**
 * <a href="JournalFeedLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class JournalFeedLocalServiceImpl
	extends JournalFeedLocalServiceBaseImpl {

	public JournalFeed addFeed(
			long userId, long plid, String feedId, boolean autoFeedId,
			String name, String description, String type, String structureId,
			String templateId, String rendererTemplateId, int delta,
			String orderByCol, String orderByType,
			String targetLayoutFriendlyUrl, String targetPortletId,
			String contentField, String feedType, double feedVersion,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFeed(
			null, userId, plid, feedId, autoFeedId, name, description, type,
			structureId, templateId, rendererTemplateId, delta, orderByCol,
			orderByType, targetLayoutFriendlyUrl, targetPortletId, contentField,
			feedType, feedVersion, Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public JournalFeed addFeed(
			long userId, long plid, String feedId, boolean autoFeedId,
			String name, String description, String type, String structureId,
			String templateId, String rendererTemplateId, int delta,
			String orderByCol, String orderByType,
			String targetLayoutFriendlyUrl, String targetPortletId,
			String contentField, String feedType, double feedVersion,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		return addFeed(
			null, userId, plid, feedId, autoFeedId, name, description, type,
			structureId, templateId, rendererTemplateId, delta, orderByCol,
			orderByType, targetLayoutFriendlyUrl, targetPortletId, contentField,
			feedType, feedVersion, null, null, communityPermissions,
			guestPermissions);
	}

	public JournalFeed addFeed(
			String uuid, long userId, long plid, String feedId,
			boolean autoFeedId, String name, String description, String type,
			String structureId, String templateId, String rendererTemplateId,
			int delta, String orderByCol, String orderByType,
			String targetLayoutFriendlyUrl, String targetPortletId,
			String contentField, String feedType, double feedVersion,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFeed(
			uuid, userId, plid, feedId, autoFeedId, name, description, type,
			structureId, templateId, rendererTemplateId, delta, orderByCol,
			orderByType, targetLayoutFriendlyUrl, targetPortletId, contentField,
			feedType, feedVersion, Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public JournalFeed addFeed(
			String uuid, long userId, long plid, String feedId,
			boolean autoFeedId, String name, String description, String type,
			String structureId, String templateId, String rendererTemplateId,
			int delta, String orderByCol, String orderByType,
			String targetLayoutFriendlyUrl, String targetPortletId,
			String contentField, String feedType, double feedVersion,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		return addFeed(
			uuid, userId, plid, feedId, autoFeedId, name, description, type,
			structureId, templateId, rendererTemplateId, delta, orderByCol,
			orderByType,targetLayoutFriendlyUrl, targetPortletId, contentField,
			feedType, feedVersion, null, null, communityPermissions,
			guestPermissions);
	}

	public JournalFeed addFeed(
			String uuid, long userId, long plid, String feedId,
			boolean autoFeedId, String name, String description, String type,
			String structureId, String templateId, String rendererTemplateId,
			int delta, String orderByCol, String orderByType,
			String targetLayoutFriendlyUrl, String targetPortletId,
			String contentField, String feedType, double feedVersion,
			Boolean addCommunityPermissions, Boolean addGuestPermissions,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		long groupId = PortalUtil.getPortletGroupId(plid);

		return addFeedToGroup(
			uuid, userId, groupId, feedId, autoFeedId, name, description, type,
			structureId, templateId, rendererTemplateId, delta, orderByCol,
			orderByType, targetLayoutFriendlyUrl, targetPortletId, contentField,
			feedType, feedVersion, addCommunityPermissions, addGuestPermissions,
			communityPermissions, guestPermissions);
	}

	public JournalFeed addFeedToGroup(
			String uuid, long userId, long groupId, String feedId,
			boolean autoFeedId, String name, String description, String type,
			String structureId, String templateId, String rendererTemplateId,
			int delta, String orderByCol, String orderByType,
			String targetLayoutFriendlyUrl, String targetPortletId,
			String contentField, String feedType, double feedVersion,
			Boolean addCommunityPermissions, Boolean addGuestPermissions,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		// Feed

		User user = userPersistence.findByPrimaryKey(userId);
		Date now = new Date();

		validate(
			groupId, feedId, autoFeedId, name, description, structureId,
			targetLayoutFriendlyUrl, contentField);

		long id = counterLocalService.increment();

		JournalFeed feed = journalFeedPersistence.create(id);

		feed.setUuid(uuid);
		feed.setGroupId(groupId);
		feed.setCompanyId(user.getCompanyId());
		feed.setUserId(user.getUserId());
		feed.setUserName(user.getFullName());
		feed.setCreateDate(now);
		feed.setModifiedDate(now);
		feed.setFeedId(feedId);
		feed.setName(name);
		feed.setDescription(description);
		feed.setType(type);
		feed.setStructureId(structureId);
		feed.setTemplateId(templateId);
		feed.setRendererTemplateId(rendererTemplateId);
		feed.setDelta(delta);
		feed.setOrderByCol(orderByCol);
		feed.setOrderByType(orderByType);
		feed.setTargetLayoutFriendlyUrl(targetLayoutFriendlyUrl);
		feed.setTargetPortletId(targetPortletId);
		feed.setContentField(contentField);

		if (Validator.isNull(feedType)) {
			feed.setFeedType(RSSUtil.DEFAULT_TYPE);
			feed.setFeedVersion(RSSUtil.DEFAULT_VERSION);
		}
		else {
			feed.setFeedType(feedType);
			feed.setFeedVersion(feedVersion);
		}

		journalFeedPersistence.update(feed);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addFeedResources(
				feed, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addFeedResources(feed, communityPermissions, guestPermissions);
		}

		return feed;
	}

	public void addFeedResources(
			long feedId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		JournalFeed feed = journalFeedPersistence.findByPrimaryKey(feedId);

		addFeedResources(feed, addCommunityPermissions, addGuestPermissions);
	}

	public void addFeedResources(
			JournalFeed feed, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			feed.getCompanyId(), feed.getGroupId(), feed.getUserId(),
			JournalFeed.class.getName(), feed.getId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addFeedResources(
			long feedId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		JournalFeed feed = journalFeedPersistence.findByPrimaryKey(feedId);

		addFeedResources(feed, communityPermissions, guestPermissions);
	}

	public void addFeedResources(
			JournalFeed feed, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			feed.getCompanyId(), feed.getGroupId(), feed.getUserId(),
			JournalFeed.class.getName(), feed.getId(), communityPermissions,
			guestPermissions);
	}

	public void deleteFeed(long feedId)
		throws PortalException, SystemException {

		JournalFeed feed = journalFeedPersistence.findByPrimaryKey(feedId);

		deleteFeed(feed);
	}

	public void deleteFeed(long groupId, String feedId)
		throws PortalException, SystemException {

		JournalFeed feed = journalFeedPersistence.findByG_F(groupId, feedId);

		deleteFeed(feed);
	}

	public void deleteFeed(JournalFeed feed)
		throws PortalException, SystemException {

		// Resources

		resourceLocalService.deleteResource(
			feed.getCompanyId(), JournalFeed.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, feed.getId());

		// Feed

		journalFeedPersistence.remove(feed.getPrimaryKey());
	}

	public JournalFeed getFeed(long feedId)
		throws PortalException, SystemException {

		return journalFeedPersistence.findByPrimaryKey(feedId);
	}

	public JournalFeed getFeed(long groupId, String feedId)
		throws PortalException, SystemException {

		return journalFeedPersistence.findByG_F(groupId, feedId);
	}

	public List getFeeds() throws SystemException {
		return journalFeedPersistence.findAll();
	}

	public List getFeeds(long groupId) throws SystemException {
		return journalFeedPersistence.findByGroupId(groupId);
	}

	public List getFeeds(long groupId, int begin, int end)
		throws SystemException {

		return journalFeedPersistence.findByGroupId(groupId, begin, end);
	}

	public int getFeedsCount(long groupId) throws SystemException {
		return journalFeedPersistence.countByGroupId(groupId);
	}

	public List search(
			long companyId, long groupId, String keywords, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		return journalFeedFinder.findByKeywords(
			companyId, groupId, keywords, begin, end, obc);
	}

	public List search(
			long companyId, long groupId, String feedId, String name,
			String description, boolean andOperator, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		return journalFeedFinder.findByC_G_F_N_D(
			companyId, groupId, feedId, name, description, andOperator, begin,
			end, obc);
	}

	public int searchCount(long companyId, long groupId, String keywords)
		throws SystemException {

		return journalFeedFinder.countByKeywords(
			companyId, groupId, keywords);
	}

	public int searchCount(
			long companyId, long groupId, String feedId, String name,
			String description, boolean andOperator)
		throws SystemException {

		return journalFeedFinder.countByC_G_F_N_D(
			companyId, groupId, feedId, name, description, andOperator);
	}

	public JournalFeed updateFeed(
			long groupId, String feedId, String name, String description,
			String type, String structureId, String templateId,
			String rendererTemplateId, int delta, String orderByCol,
			String orderByType, String targetLayoutFriendlyUrl,
			String targetPortletId, String contentField, String feedType,
			double feedVersion)
		throws PortalException, SystemException{

		// Feed

		validate(
			groupId, name, description, structureId, targetLayoutFriendlyUrl,
			contentField);

		JournalFeed feed = journalFeedPersistence.findByG_F(groupId, feedId);

		feed.setModifiedDate(new Date());
		feed.setName(name);
		feed.setDescription(description);
		feed.setType(type);
		feed.setStructureId(structureId);
		feed.setTemplateId(templateId);
		feed.setRendererTemplateId(rendererTemplateId);
		feed.setDelta(delta);
		feed.setOrderByCol(orderByCol);
		feed.setOrderByType(orderByType);
		feed.setTargetLayoutFriendlyUrl(targetLayoutFriendlyUrl);
		feed.setTargetPortletId(targetPortletId);
		feed.setContentField(contentField);

		if (Validator.isNull(feedType)) {
			feed.setFeedType(RSSUtil.DEFAULT_TYPE);
			feed.setFeedVersion(RSSUtil.DEFAULT_VERSION);
		}
		else {
			feed.setFeedType(feedType);
			feed.setFeedVersion(feedVersion);
		}

		journalFeedPersistence.update(feed);

		return feed;
	}

	protected boolean isValidStructureField(
		long groupId, String structureId, String contentField) {

		if (contentField.equals(JournalFeedImpl.ARTICLE_DESCRIPTION) ||
			contentField.equals(JournalFeedImpl.RENDERED_ARTICLE)) {

			return true;
		}
		else {
			try {
				JournalStructure structure =
					journalStructurePersistence.findByG_S(groupId, structureId);

				Document doc = PortalUtil.readDocumentFromXML(
					structure.getXsd());

				XPath xpathSelector = DocumentHelper.createXPath(
					"//dynamic-element[@name='"+ contentField + "']");

				Element el = (Element)xpathSelector.selectSingleNode(doc);

		    	if (el != null) {
		    		return true;
		    	}
			}
			catch (Exception e) {
			}
		}

		return false;
	}

	protected void validate(
			long groupId, String feedId, boolean autoFeedId, String name,
			String description, String structureId,
			String targetLayoutFriendlyUrl, String contentField)
		throws PortalException, SystemException {

		if (!autoFeedId) {
			if ((Validator.isNull(feedId)) || (Validator.isNumber(feedId)) ||
				(feedId.indexOf(StringPool.SPACE) != -1)) {

				throw new FeedIdException();
			}

			try {
				journalFeedPersistence.findByG_F(groupId, feedId);

				throw new DuplicateFeedIdException();
			}
			catch (NoSuchFeedException nsfe) {
			}
		}

		validate(
			groupId, name, description, structureId, targetLayoutFriendlyUrl,
			contentField);
	}

	protected void validate(
			long groupId, String name, String description, String structureId,
			String targetLayoutFriendlyUrl, String contentField)
		throws PortalException {

		if (Validator.isNull(name)) {
			throw new FeedNameException();
		}

		if (Validator.isNull(description)) {
			throw new FeedDescriptionException();
		}

		if (Validator.isNull(targetLayoutFriendlyUrl)) {
			throw new FeedTargetLayoutFriendlyUrlException();
		}

		if (!isValidStructureField(groupId, structureId, contentField)) {
			throw new FeedContentFieldException();
		}
	}

}