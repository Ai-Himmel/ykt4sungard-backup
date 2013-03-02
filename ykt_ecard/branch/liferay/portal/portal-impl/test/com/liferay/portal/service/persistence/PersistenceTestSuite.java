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

package com.liferay.portal.service.persistence;

import com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistenceTest;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistenceTest;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistenceTest;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistenceTest;
import com.liferay.portlet.calendar.service.persistence.CalEventPersistenceTest;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistenceTest;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistenceTest;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistenceTest;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistenceTest;
import com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistenceTest;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistenceTest;
import com.liferay.portlet.imagegallery.service.persistence.IGImagePersistenceTest;
import com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistenceTest;
import com.liferay.portlet.journal.service.persistence.JournalArticlePersistenceTest;
import com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistenceTest;
import com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistenceTest;
import com.liferay.portlet.journal.service.persistence.JournalStructurePersistenceTest;
import com.liferay.portlet.journal.service.persistence.JournalTemplatePersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBBanPersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistenceTest;
import com.liferay.portlet.messageboards.service.persistence.MBThreadPersistenceTest;
import com.liferay.portlet.polls.service.persistence.PollsChoicePersistenceTest;
import com.liferay.portlet.polls.service.persistence.PollsQuestionPersistenceTest;
import com.liferay.portlet.polls.service.persistence.PollsVotePersistenceTest;
import com.liferay.portlet.ratings.service.persistence.RatingsEntryPersistenceTest;
import com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistenceTest;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistenceTest;
import com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistenceTest;
import com.liferay.portlet.softwarecatalog.service.persistence.SCLicensePersistenceTest;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistenceTest;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotPersistenceTest;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionPersistenceTest;
import com.liferay.portlet.tags.service.persistence.TagsAssetPersistenceTest;
import com.liferay.portlet.tags.service.persistence.TagsEntryPersistenceTest;
import com.liferay.portlet.tags.service.persistence.TagsPropertyPersistenceTest;
import com.liferay.portlet.tags.service.persistence.TagsSourcePersistenceTest;
import com.liferay.portlet.wiki.service.persistence.WikiNodePersistenceTest;
import com.liferay.portlet.wiki.service.persistence.WikiPagePersistenceTest;
import com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistenceTest;

import junit.framework.TestSuite;

/**
 * <a href="PersistenceTestSuite.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PersistenceTestSuite extends TestSuite {

	public PersistenceTestSuite() {
		addTestSuite(AccountPersistenceTest.class);
		addTestSuite(ActivityTrackerPersistenceTest.class);
		addTestSuite(AddressPersistenceTest.class);
		addTestSuite(ClassNamePersistenceTest.class);
		addTestSuite(CompanyPersistenceTest.class);
		addTestSuite(ContactPersistenceTest.class);
		addTestSuite(CountryPersistenceTest.class);
		addTestSuite(EmailAddressPersistenceTest.class);
		addTestSuite(GroupPersistenceTest.class);
		addTestSuite(ImagePersistenceTest.class);
		addTestSuite(LayoutPersistenceTest.class);
		addTestSuite(LayoutSetPersistenceTest.class);
		addTestSuite(ListTypePersistenceTest.class);
		addTestSuite(MembershipRequestPersistenceTest.class);
		addTestSuite(OrganizationPersistenceTest.class);
		addTestSuite(OrgGroupPermissionPersistenceTest.class);
		addTestSuite(OrgGroupRolePersistenceTest.class);
		addTestSuite(OrgLaborPersistenceTest.class);
		addTestSuite(PasswordPolicyPersistenceTest.class);
		addTestSuite(PasswordPolicyRelPersistenceTest.class);
		addTestSuite(PasswordTrackerPersistenceTest.class);
		addTestSuite(PermissionPersistenceTest.class);
		addTestSuite(PhonePersistenceTest.class);
		addTestSuite(PluginSettingPersistenceTest.class);
		addTestSuite(PortletPersistenceTest.class);
		addTestSuite(PortletPreferencesPersistenceTest.class);
		addTestSuite(RegionPersistenceTest.class);
		addTestSuite(ReleasePersistenceTest.class);
		addTestSuite(ResourceCodePersistenceTest.class);
		addTestSuite(ResourcePersistenceTest.class);
		addTestSuite(RolePersistenceTest.class);
		addTestSuite(ServiceComponentPersistenceTest.class);
		addTestSuite(SubscriptionPersistenceTest.class);
		addTestSuite(UserGroupPersistenceTest.class);
		addTestSuite(UserGroupRolePersistenceTest.class);
		addTestSuite(UserIdMapperPersistenceTest.class);
		addTestSuite(UserPersistenceTest.class);
		addTestSuite(UserTrackerPathPersistenceTest.class);
		addTestSuite(UserTrackerPersistenceTest.class);
		addTestSuite(WebsitePersistenceTest.class);

		addTestSuite(BlogsEntryPersistenceTest.class);
		addTestSuite(BlogsStatsUserPersistenceTest.class);

		addTestSuite(BookmarksEntryPersistenceTest.class);
		addTestSuite(BookmarksFolderPersistenceTest.class);

		addTestSuite(CalEventPersistenceTest.class);

		addTestSuite(DLFileEntryPersistenceTest.class);
		addTestSuite(DLFileRankPersistenceTest.class);
		addTestSuite(DLFileShortcutPersistenceTest.class);
		addTestSuite(DLFileVersionPersistenceTest.class);
		addTestSuite(DLFolderPersistenceTest.class);

		addTestSuite(IGFolderPersistenceTest.class);
		addTestSuite(IGImagePersistenceTest.class);

		addTestSuite(JournalArticleImagePersistenceTest.class);
		addTestSuite(JournalArticlePersistenceTest.class);
		addTestSuite(JournalArticleResourcePersistenceTest.class);
		addTestSuite(JournalContentSearchPersistenceTest.class);
		addTestSuite(JournalStructurePersistenceTest.class);
		addTestSuite(JournalTemplatePersistenceTest.class);

		addTestSuite(MBBanPersistenceTest.class);
		addTestSuite(MBCategoryPersistenceTest.class);
		addTestSuite(MBDiscussionPersistenceTest.class);
		addTestSuite(MBMessageFlagPersistenceTest.class);
		addTestSuite(MBMessagePersistenceTest.class);
		addTestSuite(MBStatsUserPersistenceTest.class);
		addTestSuite(MBThreadPersistenceTest.class);

		addTestSuite(PollsChoicePersistenceTest.class);
		addTestSuite(PollsQuestionPersistenceTest.class);
		addTestSuite(PollsVotePersistenceTest.class);

		addTestSuite(RatingsEntryPersistenceTest.class);
		addTestSuite(RatingsStatsPersistenceTest.class);

		addTestSuite(ShoppingCartPersistenceTest.class);
		addTestSuite(ShoppingCategoryPersistenceTest.class);
		addTestSuite(ShoppingCouponPersistenceTest.class);
		addTestSuite(ShoppingItemFieldPersistenceTest.class);
		addTestSuite(ShoppingItemPersistenceTest.class);
		addTestSuite(ShoppingItemPricePersistenceTest.class);
		addTestSuite(ShoppingOrderItemPersistenceTest.class);
		addTestSuite(ShoppingOrderPersistenceTest.class);

		addTestSuite(SCFrameworkVersionPersistenceTest.class);
		addTestSuite(SCLicensePersistenceTest.class);
		addTestSuite(SCProductEntryPersistenceTest.class);
		addTestSuite(SCProductScreenshotPersistenceTest.class);
		addTestSuite(SCProductVersionPersistenceTest.class);

		addTestSuite(TagsAssetPersistenceTest.class);
		addTestSuite(TagsEntryPersistenceTest.class);
		addTestSuite(TagsPropertyPersistenceTest.class);
		addTestSuite(TagsSourcePersistenceTest.class);

		addTestSuite(WikiNodePersistenceTest.class);
		addTestSuite(WikiPagePersistenceTest.class);
		addTestSuite(WikiPageResourcePersistenceTest.class);
	}

	public void test() {
	}

}