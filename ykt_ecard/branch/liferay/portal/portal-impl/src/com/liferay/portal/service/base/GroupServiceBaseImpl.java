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

package com.liferay.portal.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.service.AccountLocalService;
import com.liferay.portal.service.AccountLocalServiceFactory;
import com.liferay.portal.service.AccountService;
import com.liferay.portal.service.AccountServiceFactory;
import com.liferay.portal.service.ActivityTrackerLocalService;
import com.liferay.portal.service.ActivityTrackerLocalServiceFactory;
import com.liferay.portal.service.AddressLocalService;
import com.liferay.portal.service.AddressLocalServiceFactory;
import com.liferay.portal.service.AddressService;
import com.liferay.portal.service.AddressServiceFactory;
import com.liferay.portal.service.ClassNameLocalService;
import com.liferay.portal.service.ClassNameLocalServiceFactory;
import com.liferay.portal.service.ClassNameService;
import com.liferay.portal.service.ClassNameServiceFactory;
import com.liferay.portal.service.CompanyLocalService;
import com.liferay.portal.service.CompanyLocalServiceFactory;
import com.liferay.portal.service.CompanyService;
import com.liferay.portal.service.CompanyServiceFactory;
import com.liferay.portal.service.ContactLocalService;
import com.liferay.portal.service.ContactLocalServiceFactory;
import com.liferay.portal.service.ContactService;
import com.liferay.portal.service.ContactServiceFactory;
import com.liferay.portal.service.CountryService;
import com.liferay.portal.service.CountryServiceFactory;
import com.liferay.portal.service.EmailAddressLocalService;
import com.liferay.portal.service.EmailAddressLocalServiceFactory;
import com.liferay.portal.service.EmailAddressService;
import com.liferay.portal.service.EmailAddressServiceFactory;
import com.liferay.portal.service.GroupLocalService;
import com.liferay.portal.service.GroupLocalServiceFactory;
import com.liferay.portal.service.GroupService;
import com.liferay.portal.service.ImageLocalService;
import com.liferay.portal.service.ImageLocalServiceFactory;
import com.liferay.portal.service.LayoutLocalService;
import com.liferay.portal.service.LayoutLocalServiceFactory;
import com.liferay.portal.service.LayoutService;
import com.liferay.portal.service.LayoutServiceFactory;
import com.liferay.portal.service.LayoutSetLocalService;
import com.liferay.portal.service.LayoutSetLocalServiceFactory;
import com.liferay.portal.service.LayoutSetService;
import com.liferay.portal.service.LayoutSetServiceFactory;
import com.liferay.portal.service.ListTypeService;
import com.liferay.portal.service.ListTypeServiceFactory;
import com.liferay.portal.service.MembershipRequestLocalService;
import com.liferay.portal.service.MembershipRequestLocalServiceFactory;
import com.liferay.portal.service.MembershipRequestService;
import com.liferay.portal.service.MembershipRequestServiceFactory;
import com.liferay.portal.service.OrgLaborLocalService;
import com.liferay.portal.service.OrgLaborLocalServiceFactory;
import com.liferay.portal.service.OrgLaborService;
import com.liferay.portal.service.OrgLaborServiceFactory;
import com.liferay.portal.service.OrganizationLocalService;
import com.liferay.portal.service.OrganizationLocalServiceFactory;
import com.liferay.portal.service.OrganizationService;
import com.liferay.portal.service.OrganizationServiceFactory;
import com.liferay.portal.service.PasswordPolicyLocalService;
import com.liferay.portal.service.PasswordPolicyLocalServiceFactory;
import com.liferay.portal.service.PasswordPolicyRelLocalService;
import com.liferay.portal.service.PasswordPolicyRelLocalServiceFactory;
import com.liferay.portal.service.PasswordPolicyService;
import com.liferay.portal.service.PasswordPolicyServiceFactory;
import com.liferay.portal.service.PasswordTrackerLocalService;
import com.liferay.portal.service.PasswordTrackerLocalServiceFactory;
import com.liferay.portal.service.PermissionLocalService;
import com.liferay.portal.service.PermissionLocalServiceFactory;
import com.liferay.portal.service.PermissionService;
import com.liferay.portal.service.PermissionServiceFactory;
import com.liferay.portal.service.PhoneLocalService;
import com.liferay.portal.service.PhoneLocalServiceFactory;
import com.liferay.portal.service.PhoneService;
import com.liferay.portal.service.PhoneServiceFactory;
import com.liferay.portal.service.PluginSettingLocalService;
import com.liferay.portal.service.PluginSettingLocalServiceFactory;
import com.liferay.portal.service.PluginSettingService;
import com.liferay.portal.service.PluginSettingServiceFactory;
import com.liferay.portal.service.PortalService;
import com.liferay.portal.service.PortalServiceFactory;
import com.liferay.portal.service.PortletLocalService;
import com.liferay.portal.service.PortletLocalServiceFactory;
import com.liferay.portal.service.PortletPreferencesLocalService;
import com.liferay.portal.service.PortletPreferencesLocalServiceFactory;
import com.liferay.portal.service.PortletService;
import com.liferay.portal.service.PortletServiceFactory;
import com.liferay.portal.service.RegionService;
import com.liferay.portal.service.RegionServiceFactory;
import com.liferay.portal.service.ReleaseLocalService;
import com.liferay.portal.service.ReleaseLocalServiceFactory;
import com.liferay.portal.service.ResourceCodeLocalService;
import com.liferay.portal.service.ResourceCodeLocalServiceFactory;
import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.RoleLocalService;
import com.liferay.portal.service.RoleLocalServiceFactory;
import com.liferay.portal.service.RoleService;
import com.liferay.portal.service.RoleServiceFactory;
import com.liferay.portal.service.ServiceComponentLocalService;
import com.liferay.portal.service.ServiceComponentLocalServiceFactory;
import com.liferay.portal.service.SubscriptionLocalService;
import com.liferay.portal.service.SubscriptionLocalServiceFactory;
import com.liferay.portal.service.UserGroupLocalService;
import com.liferay.portal.service.UserGroupLocalServiceFactory;
import com.liferay.portal.service.UserGroupRoleLocalService;
import com.liferay.portal.service.UserGroupRoleLocalServiceFactory;
import com.liferay.portal.service.UserGroupRoleService;
import com.liferay.portal.service.UserGroupRoleServiceFactory;
import com.liferay.portal.service.UserGroupService;
import com.liferay.portal.service.UserGroupServiceFactory;
import com.liferay.portal.service.UserIdMapperLocalService;
import com.liferay.portal.service.UserIdMapperLocalServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.UserTrackerLocalService;
import com.liferay.portal.service.UserTrackerLocalServiceFactory;
import com.liferay.portal.service.UserTrackerPathLocalService;
import com.liferay.portal.service.UserTrackerPathLocalServiceFactory;
import com.liferay.portal.service.WebDAVPropsLocalService;
import com.liferay.portal.service.WebDAVPropsLocalServiceFactory;
import com.liferay.portal.service.WebsiteLocalService;
import com.liferay.portal.service.WebsiteLocalServiceFactory;
import com.liferay.portal.service.WebsiteService;
import com.liferay.portal.service.WebsiteServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.persistence.AccountPersistence;
import com.liferay.portal.service.persistence.AccountUtil;
import com.liferay.portal.service.persistence.ActivityTrackerFinder;
import com.liferay.portal.service.persistence.ActivityTrackerFinderUtil;
import com.liferay.portal.service.persistence.ActivityTrackerPersistence;
import com.liferay.portal.service.persistence.ActivityTrackerUtil;
import com.liferay.portal.service.persistence.AddressPersistence;
import com.liferay.portal.service.persistence.AddressUtil;
import com.liferay.portal.service.persistence.ClassNamePersistence;
import com.liferay.portal.service.persistence.ClassNameUtil;
import com.liferay.portal.service.persistence.CompanyPersistence;
import com.liferay.portal.service.persistence.CompanyUtil;
import com.liferay.portal.service.persistence.ContactPersistence;
import com.liferay.portal.service.persistence.ContactUtil;
import com.liferay.portal.service.persistence.CountryPersistence;
import com.liferay.portal.service.persistence.CountryUtil;
import com.liferay.portal.service.persistence.EmailAddressPersistence;
import com.liferay.portal.service.persistence.EmailAddressUtil;
import com.liferay.portal.service.persistence.GroupFinder;
import com.liferay.portal.service.persistence.GroupFinderUtil;
import com.liferay.portal.service.persistence.GroupPersistence;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.ImagePersistence;
import com.liferay.portal.service.persistence.ImageUtil;
import com.liferay.portal.service.persistence.LayoutFinder;
import com.liferay.portal.service.persistence.LayoutFinderUtil;
import com.liferay.portal.service.persistence.LayoutPersistence;
import com.liferay.portal.service.persistence.LayoutSetPersistence;
import com.liferay.portal.service.persistence.LayoutSetUtil;
import com.liferay.portal.service.persistence.LayoutUtil;
import com.liferay.portal.service.persistence.ListTypePersistence;
import com.liferay.portal.service.persistence.ListTypeUtil;
import com.liferay.portal.service.persistence.MembershipRequestPersistence;
import com.liferay.portal.service.persistence.MembershipRequestUtil;
import com.liferay.portal.service.persistence.OrgGroupPermissionFinder;
import com.liferay.portal.service.persistence.OrgGroupPermissionFinderUtil;
import com.liferay.portal.service.persistence.OrgGroupPermissionPersistence;
import com.liferay.portal.service.persistence.OrgGroupPermissionUtil;
import com.liferay.portal.service.persistence.OrgGroupRolePersistence;
import com.liferay.portal.service.persistence.OrgGroupRoleUtil;
import com.liferay.portal.service.persistence.OrgLaborPersistence;
import com.liferay.portal.service.persistence.OrgLaborUtil;
import com.liferay.portal.service.persistence.OrganizationFinder;
import com.liferay.portal.service.persistence.OrganizationFinderUtil;
import com.liferay.portal.service.persistence.OrganizationPersistence;
import com.liferay.portal.service.persistence.OrganizationUtil;
import com.liferay.portal.service.persistence.PasswordPolicyFinder;
import com.liferay.portal.service.persistence.PasswordPolicyFinderUtil;
import com.liferay.portal.service.persistence.PasswordPolicyPersistence;
import com.liferay.portal.service.persistence.PasswordPolicyRelPersistence;
import com.liferay.portal.service.persistence.PasswordPolicyRelUtil;
import com.liferay.portal.service.persistence.PasswordPolicyUtil;
import com.liferay.portal.service.persistence.PasswordTrackerPersistence;
import com.liferay.portal.service.persistence.PasswordTrackerUtil;
import com.liferay.portal.service.persistence.PermissionFinder;
import com.liferay.portal.service.persistence.PermissionFinderUtil;
import com.liferay.portal.service.persistence.PermissionPersistence;
import com.liferay.portal.service.persistence.PermissionUserFinder;
import com.liferay.portal.service.persistence.PermissionUserFinderUtil;
import com.liferay.portal.service.persistence.PermissionUtil;
import com.liferay.portal.service.persistence.PhonePersistence;
import com.liferay.portal.service.persistence.PhoneUtil;
import com.liferay.portal.service.persistence.PluginSettingPersistence;
import com.liferay.portal.service.persistence.PluginSettingUtil;
import com.liferay.portal.service.persistence.PortletPersistence;
import com.liferay.portal.service.persistence.PortletPreferencesFinder;
import com.liferay.portal.service.persistence.PortletPreferencesFinderUtil;
import com.liferay.portal.service.persistence.PortletPreferencesPersistence;
import com.liferay.portal.service.persistence.PortletPreferencesUtil;
import com.liferay.portal.service.persistence.PortletUtil;
import com.liferay.portal.service.persistence.RegionPersistence;
import com.liferay.portal.service.persistence.RegionUtil;
import com.liferay.portal.service.persistence.ReleasePersistence;
import com.liferay.portal.service.persistence.ReleaseUtil;
import com.liferay.portal.service.persistence.ResourceCodePersistence;
import com.liferay.portal.service.persistence.ResourceCodeUtil;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.RoleFinder;
import com.liferay.portal.service.persistence.RoleFinderUtil;
import com.liferay.portal.service.persistence.RolePersistence;
import com.liferay.portal.service.persistence.RoleUtil;
import com.liferay.portal.service.persistence.ServiceComponentPersistence;
import com.liferay.portal.service.persistence.ServiceComponentUtil;
import com.liferay.portal.service.persistence.SubscriptionPersistence;
import com.liferay.portal.service.persistence.SubscriptionUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserGroupFinder;
import com.liferay.portal.service.persistence.UserGroupFinderUtil;
import com.liferay.portal.service.persistence.UserGroupPersistence;
import com.liferay.portal.service.persistence.UserGroupRolePersistence;
import com.liferay.portal.service.persistence.UserGroupRoleUtil;
import com.liferay.portal.service.persistence.UserGroupUtil;
import com.liferay.portal.service.persistence.UserIdMapperPersistence;
import com.liferay.portal.service.persistence.UserIdMapperUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserTrackerPathPersistence;
import com.liferay.portal.service.persistence.UserTrackerPathUtil;
import com.liferay.portal.service.persistence.UserTrackerPersistence;
import com.liferay.portal.service.persistence.UserTrackerUtil;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.persistence.WebDAVPropsPersistence;
import com.liferay.portal.service.persistence.WebDAVPropsUtil;
import com.liferay.portal.service.persistence.WebsitePersistence;
import com.liferay.portal.service.persistence.WebsiteUtil;

import com.liferay.portlet.blogs.service.BlogsEntryLocalService;
import com.liferay.portlet.blogs.service.BlogsEntryLocalServiceFactory;
import com.liferay.portlet.blogs.service.BlogsEntryService;
import com.liferay.portlet.blogs.service.BlogsEntryServiceFactory;
import com.liferay.portlet.blogs.service.BlogsStatsUserLocalService;
import com.liferay.portlet.blogs.service.BlogsStatsUserLocalServiceFactory;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinderUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinderUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserUtil;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalService;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceFactory;
import com.liferay.portlet.bookmarks.service.BookmarksFolderService;
import com.liferay.portlet.bookmarks.service.BookmarksFolderServiceFactory;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderUtil;
import com.liferay.portlet.calendar.service.CalEventLocalService;
import com.liferay.portlet.calendar.service.CalEventLocalServiceFactory;
import com.liferay.portlet.calendar.service.CalEventService;
import com.liferay.portlet.calendar.service.CalEventServiceFactory;
import com.liferay.portlet.calendar.service.persistence.CalEventFinder;
import com.liferay.portlet.calendar.service.persistence.CalEventFinderUtil;
import com.liferay.portlet.calendar.service.persistence.CalEventPersistence;
import com.liferay.portlet.calendar.service.persistence.CalEventUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalService;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceFactory;
import com.liferay.portlet.documentlibrary.service.DLFolderService;
import com.liferay.portlet.documentlibrary.service.DLFolderServiceFactory;
import com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence;
import com.liferay.portlet.documentlibrary.service.persistence.DLFolderUtil;
import com.liferay.portlet.imagegallery.service.IGFolderLocalService;
import com.liferay.portlet.imagegallery.service.IGFolderLocalServiceFactory;
import com.liferay.portlet.imagegallery.service.IGFolderService;
import com.liferay.portlet.imagegallery.service.IGFolderServiceFactory;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistence;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderUtil;
import com.liferay.portlet.journal.service.JournalArticleLocalService;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleService;
import com.liferay.portlet.journal.service.JournalArticleServiceFactory;
import com.liferay.portlet.journal.service.JournalStructureLocalService;
import com.liferay.portlet.journal.service.JournalStructureLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalStructureService;
import com.liferay.portlet.journal.service.JournalStructureServiceFactory;
import com.liferay.portlet.journal.service.JournalTemplateLocalService;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalTemplateService;
import com.liferay.portlet.journal.service.JournalTemplateServiceFactory;
import com.liferay.portlet.journal.service.persistence.JournalArticleFinder;
import com.liferay.portlet.journal.service.persistence.JournalArticleFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticlePersistence;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.journal.service.persistence.JournalStructureFinder;
import com.liferay.portlet.journal.service.persistence.JournalStructureFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalStructurePersistence;
import com.liferay.portlet.journal.service.persistence.JournalStructureUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplateFinder;
import com.liferay.portlet.journal.service.persistence.JournalTemplateFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence;
import com.liferay.portlet.journal.service.persistence.JournalTemplateUtil;
import com.liferay.portlet.messageboards.service.MBBanLocalService;
import com.liferay.portlet.messageboards.service.MBBanLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBBanService;
import com.liferay.portlet.messageboards.service.MBBanServiceFactory;
import com.liferay.portlet.messageboards.service.MBCategoryLocalService;
import com.liferay.portlet.messageboards.service.MBCategoryLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBCategoryService;
import com.liferay.portlet.messageboards.service.MBCategoryServiceFactory;
import com.liferay.portlet.messageboards.service.MBStatsUserLocalService;
import com.liferay.portlet.messageboards.service.MBStatsUserLocalServiceFactory;
import com.liferay.portlet.messageboards.service.persistence.MBBanPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBBanUtil;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryUtil;
import com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBStatsUserUtil;
import com.liferay.portlet.polls.service.PollsQuestionLocalService;
import com.liferay.portlet.polls.service.PollsQuestionLocalServiceFactory;
import com.liferay.portlet.polls.service.PollsQuestionService;
import com.liferay.portlet.polls.service.PollsQuestionServiceFactory;
import com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence;
import com.liferay.portlet.polls.service.persistence.PollsQuestionUtil;
import com.liferay.portlet.shopping.service.ShoppingCartLocalService;
import com.liferay.portlet.shopping.service.ShoppingCartLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalService;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCategoryService;
import com.liferay.portlet.shopping.service.ShoppingCategoryServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCouponLocalService;
import com.liferay.portlet.shopping.service.ShoppingCouponLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCouponService;
import com.liferay.portlet.shopping.service.ShoppingCouponServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingOrderLocalService;
import com.liferay.portlet.shopping.service.ShoppingOrderLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingOrderService;
import com.liferay.portlet.shopping.service.ShoppingOrderServiceFactory;
import com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingCartUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinderUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinderUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderUtil;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalService;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionService;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalService;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryService;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryServiceFactory;
import com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionUtil;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryUtil;
import com.liferay.portlet.wiki.service.WikiNodeLocalService;
import com.liferay.portlet.wiki.service.WikiNodeLocalServiceFactory;
import com.liferay.portlet.wiki.service.WikiNodeService;
import com.liferay.portlet.wiki.service.WikiNodeServiceFactory;
import com.liferay.portlet.wiki.service.persistence.WikiNodePersistence;
import com.liferay.portlet.wiki.service.persistence.WikiNodeUtil;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="GroupServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class GroupServiceBaseImpl extends PrincipalBean
	implements GroupService, InitializingBean {
	public AccountLocalService getAccountLocalService() {
		return accountLocalService;
	}

	public void setAccountLocalService(AccountLocalService accountLocalService) {
		this.accountLocalService = accountLocalService;
	}

	public AccountService getAccountService() {
		return accountService;
	}

	public void setAccountService(AccountService accountService) {
		this.accountService = accountService;
	}

	public AccountPersistence getAccountPersistence() {
		return accountPersistence;
	}

	public void setAccountPersistence(AccountPersistence accountPersistence) {
		this.accountPersistence = accountPersistence;
	}

	public ActivityTrackerLocalService getActivityTrackerLocalService() {
		return activityTrackerLocalService;
	}

	public void setActivityTrackerLocalService(
		ActivityTrackerLocalService activityTrackerLocalService) {
		this.activityTrackerLocalService = activityTrackerLocalService;
	}

	public ActivityTrackerPersistence getActivityTrackerPersistence() {
		return activityTrackerPersistence;
	}

	public void setActivityTrackerPersistence(
		ActivityTrackerPersistence activityTrackerPersistence) {
		this.activityTrackerPersistence = activityTrackerPersistence;
	}

	public ActivityTrackerFinder getActivityTrackerFinder() {
		return activityTrackerFinder;
	}

	public void setActivityTrackerFinder(
		ActivityTrackerFinder activityTrackerFinder) {
		this.activityTrackerFinder = activityTrackerFinder;
	}

	public AddressLocalService getAddressLocalService() {
		return addressLocalService;
	}

	public void setAddressLocalService(AddressLocalService addressLocalService) {
		this.addressLocalService = addressLocalService;
	}

	public AddressService getAddressService() {
		return addressService;
	}

	public void setAddressService(AddressService addressService) {
		this.addressService = addressService;
	}

	public AddressPersistence getAddressPersistence() {
		return addressPersistence;
	}

	public void setAddressPersistence(AddressPersistence addressPersistence) {
		this.addressPersistence = addressPersistence;
	}

	public ClassNameLocalService getClassNameLocalService() {
		return classNameLocalService;
	}

	public void setClassNameLocalService(
		ClassNameLocalService classNameLocalService) {
		this.classNameLocalService = classNameLocalService;
	}

	public ClassNameService getClassNameService() {
		return classNameService;
	}

	public void setClassNameService(ClassNameService classNameService) {
		this.classNameService = classNameService;
	}

	public ClassNamePersistence getClassNamePersistence() {
		return classNamePersistence;
	}

	public void setClassNamePersistence(
		ClassNamePersistence classNamePersistence) {
		this.classNamePersistence = classNamePersistence;
	}

	public CompanyLocalService getCompanyLocalService() {
		return companyLocalService;
	}

	public void setCompanyLocalService(CompanyLocalService companyLocalService) {
		this.companyLocalService = companyLocalService;
	}

	public CompanyService getCompanyService() {
		return companyService;
	}

	public void setCompanyService(CompanyService companyService) {
		this.companyService = companyService;
	}

	public CompanyPersistence getCompanyPersistence() {
		return companyPersistence;
	}

	public void setCompanyPersistence(CompanyPersistence companyPersistence) {
		this.companyPersistence = companyPersistence;
	}

	public ContactLocalService getContactLocalService() {
		return contactLocalService;
	}

	public void setContactLocalService(ContactLocalService contactLocalService) {
		this.contactLocalService = contactLocalService;
	}

	public ContactService getContactService() {
		return contactService;
	}

	public void setContactService(ContactService contactService) {
		this.contactService = contactService;
	}

	public ContactPersistence getContactPersistence() {
		return contactPersistence;
	}

	public void setContactPersistence(ContactPersistence contactPersistence) {
		this.contactPersistence = contactPersistence;
	}

	public CountryService getCountryService() {
		return countryService;
	}

	public void setCountryService(CountryService countryService) {
		this.countryService = countryService;
	}

	public CountryPersistence getCountryPersistence() {
		return countryPersistence;
	}

	public void setCountryPersistence(CountryPersistence countryPersistence) {
		this.countryPersistence = countryPersistence;
	}

	public EmailAddressLocalService getEmailAddressLocalService() {
		return emailAddressLocalService;
	}

	public void setEmailAddressLocalService(
		EmailAddressLocalService emailAddressLocalService) {
		this.emailAddressLocalService = emailAddressLocalService;
	}

	public EmailAddressService getEmailAddressService() {
		return emailAddressService;
	}

	public void setEmailAddressService(EmailAddressService emailAddressService) {
		this.emailAddressService = emailAddressService;
	}

	public EmailAddressPersistence getEmailAddressPersistence() {
		return emailAddressPersistence;
	}

	public void setEmailAddressPersistence(
		EmailAddressPersistence emailAddressPersistence) {
		this.emailAddressPersistence = emailAddressPersistence;
	}

	public GroupLocalService getGroupLocalService() {
		return groupLocalService;
	}

	public void setGroupLocalService(GroupLocalService groupLocalService) {
		this.groupLocalService = groupLocalService;
	}

	public GroupPersistence getGroupPersistence() {
		return groupPersistence;
	}

	public void setGroupPersistence(GroupPersistence groupPersistence) {
		this.groupPersistence = groupPersistence;
	}

	public GroupFinder getGroupFinder() {
		return groupFinder;
	}

	public void setGroupFinder(GroupFinder groupFinder) {
		this.groupFinder = groupFinder;
	}

	public ImageLocalService getImageLocalService() {
		return imageLocalService;
	}

	public void setImageLocalService(ImageLocalService imageLocalService) {
		this.imageLocalService = imageLocalService;
	}

	public ImagePersistence getImagePersistence() {
		return imagePersistence;
	}

	public void setImagePersistence(ImagePersistence imagePersistence) {
		this.imagePersistence = imagePersistence;
	}

	public LayoutLocalService getLayoutLocalService() {
		return layoutLocalService;
	}

	public void setLayoutLocalService(LayoutLocalService layoutLocalService) {
		this.layoutLocalService = layoutLocalService;
	}

	public LayoutService getLayoutService() {
		return layoutService;
	}

	public void setLayoutService(LayoutService layoutService) {
		this.layoutService = layoutService;
	}

	public LayoutPersistence getLayoutPersistence() {
		return layoutPersistence;
	}

	public void setLayoutPersistence(LayoutPersistence layoutPersistence) {
		this.layoutPersistence = layoutPersistence;
	}

	public LayoutFinder getLayoutFinder() {
		return layoutFinder;
	}

	public void setLayoutFinder(LayoutFinder layoutFinder) {
		this.layoutFinder = layoutFinder;
	}

	public LayoutSetLocalService getLayoutSetLocalService() {
		return layoutSetLocalService;
	}

	public void setLayoutSetLocalService(
		LayoutSetLocalService layoutSetLocalService) {
		this.layoutSetLocalService = layoutSetLocalService;
	}

	public LayoutSetService getLayoutSetService() {
		return layoutSetService;
	}

	public void setLayoutSetService(LayoutSetService layoutSetService) {
		this.layoutSetService = layoutSetService;
	}

	public LayoutSetPersistence getLayoutSetPersistence() {
		return layoutSetPersistence;
	}

	public void setLayoutSetPersistence(
		LayoutSetPersistence layoutSetPersistence) {
		this.layoutSetPersistence = layoutSetPersistence;
	}

	public ListTypeService getListTypeService() {
		return listTypeService;
	}

	public void setListTypeService(ListTypeService listTypeService) {
		this.listTypeService = listTypeService;
	}

	public ListTypePersistence getListTypePersistence() {
		return listTypePersistence;
	}

	public void setListTypePersistence(ListTypePersistence listTypePersistence) {
		this.listTypePersistence = listTypePersistence;
	}

	public MembershipRequestLocalService getMembershipRequestLocalService() {
		return membershipRequestLocalService;
	}

	public void setMembershipRequestLocalService(
		MembershipRequestLocalService membershipRequestLocalService) {
		this.membershipRequestLocalService = membershipRequestLocalService;
	}

	public MembershipRequestService getMembershipRequestService() {
		return membershipRequestService;
	}

	public void setMembershipRequestService(
		MembershipRequestService membershipRequestService) {
		this.membershipRequestService = membershipRequestService;
	}

	public MembershipRequestPersistence getMembershipRequestPersistence() {
		return membershipRequestPersistence;
	}

	public void setMembershipRequestPersistence(
		MembershipRequestPersistence membershipRequestPersistence) {
		this.membershipRequestPersistence = membershipRequestPersistence;
	}

	public OrganizationLocalService getOrganizationLocalService() {
		return organizationLocalService;
	}

	public void setOrganizationLocalService(
		OrganizationLocalService organizationLocalService) {
		this.organizationLocalService = organizationLocalService;
	}

	public OrganizationService getOrganizationService() {
		return organizationService;
	}

	public void setOrganizationService(OrganizationService organizationService) {
		this.organizationService = organizationService;
	}

	public OrganizationPersistence getOrganizationPersistence() {
		return organizationPersistence;
	}

	public void setOrganizationPersistence(
		OrganizationPersistence organizationPersistence) {
		this.organizationPersistence = organizationPersistence;
	}

	public OrganizationFinder getOrganizationFinder() {
		return organizationFinder;
	}

	public void setOrganizationFinder(OrganizationFinder organizationFinder) {
		this.organizationFinder = organizationFinder;
	}

	public OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		return orgGroupPermissionPersistence;
	}

	public void setOrgGroupPermissionPersistence(
		OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		this.orgGroupPermissionPersistence = orgGroupPermissionPersistence;
	}

	public OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		return orgGroupPermissionFinder;
	}

	public void setOrgGroupPermissionFinder(
		OrgGroupPermissionFinder orgGroupPermissionFinder) {
		this.orgGroupPermissionFinder = orgGroupPermissionFinder;
	}

	public OrgGroupRolePersistence getOrgGroupRolePersistence() {
		return orgGroupRolePersistence;
	}

	public void setOrgGroupRolePersistence(
		OrgGroupRolePersistence orgGroupRolePersistence) {
		this.orgGroupRolePersistence = orgGroupRolePersistence;
	}

	public OrgLaborLocalService getOrgLaborLocalService() {
		return orgLaborLocalService;
	}

	public void setOrgLaborLocalService(
		OrgLaborLocalService orgLaborLocalService) {
		this.orgLaborLocalService = orgLaborLocalService;
	}

	public OrgLaborService getOrgLaborService() {
		return orgLaborService;
	}

	public void setOrgLaborService(OrgLaborService orgLaborService) {
		this.orgLaborService = orgLaborService;
	}

	public OrgLaborPersistence getOrgLaborPersistence() {
		return orgLaborPersistence;
	}

	public void setOrgLaborPersistence(OrgLaborPersistence orgLaborPersistence) {
		this.orgLaborPersistence = orgLaborPersistence;
	}

	public PasswordPolicyLocalService getPasswordPolicyLocalService() {
		return passwordPolicyLocalService;
	}

	public void setPasswordPolicyLocalService(
		PasswordPolicyLocalService passwordPolicyLocalService) {
		this.passwordPolicyLocalService = passwordPolicyLocalService;
	}

	public PasswordPolicyService getPasswordPolicyService() {
		return passwordPolicyService;
	}

	public void setPasswordPolicyService(
		PasswordPolicyService passwordPolicyService) {
		this.passwordPolicyService = passwordPolicyService;
	}

	public PasswordPolicyPersistence getPasswordPolicyPersistence() {
		return passwordPolicyPersistence;
	}

	public void setPasswordPolicyPersistence(
		PasswordPolicyPersistence passwordPolicyPersistence) {
		this.passwordPolicyPersistence = passwordPolicyPersistence;
	}

	public PasswordPolicyFinder getPasswordPolicyFinder() {
		return passwordPolicyFinder;
	}

	public void setPasswordPolicyFinder(
		PasswordPolicyFinder passwordPolicyFinder) {
		this.passwordPolicyFinder = passwordPolicyFinder;
	}

	public PasswordPolicyRelLocalService getPasswordPolicyRelLocalService() {
		return passwordPolicyRelLocalService;
	}

	public void setPasswordPolicyRelLocalService(
		PasswordPolicyRelLocalService passwordPolicyRelLocalService) {
		this.passwordPolicyRelLocalService = passwordPolicyRelLocalService;
	}

	public PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		return passwordPolicyRelPersistence;
	}

	public void setPasswordPolicyRelPersistence(
		PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		this.passwordPolicyRelPersistence = passwordPolicyRelPersistence;
	}

	public PasswordTrackerLocalService getPasswordTrackerLocalService() {
		return passwordTrackerLocalService;
	}

	public void setPasswordTrackerLocalService(
		PasswordTrackerLocalService passwordTrackerLocalService) {
		this.passwordTrackerLocalService = passwordTrackerLocalService;
	}

	public PasswordTrackerPersistence getPasswordTrackerPersistence() {
		return passwordTrackerPersistence;
	}

	public void setPasswordTrackerPersistence(
		PasswordTrackerPersistence passwordTrackerPersistence) {
		this.passwordTrackerPersistence = passwordTrackerPersistence;
	}

	public PermissionLocalService getPermissionLocalService() {
		return permissionLocalService;
	}

	public void setPermissionLocalService(
		PermissionLocalService permissionLocalService) {
		this.permissionLocalService = permissionLocalService;
	}

	public PermissionService getPermissionService() {
		return permissionService;
	}

	public void setPermissionService(PermissionService permissionService) {
		this.permissionService = permissionService;
	}

	public PermissionPersistence getPermissionPersistence() {
		return permissionPersistence;
	}

	public void setPermissionPersistence(
		PermissionPersistence permissionPersistence) {
		this.permissionPersistence = permissionPersistence;
	}

	public PermissionFinder getPermissionFinder() {
		return permissionFinder;
	}

	public void setPermissionFinder(PermissionFinder permissionFinder) {
		this.permissionFinder = permissionFinder;
	}

	public PermissionUserFinder getPermissionUserFinder() {
		return permissionUserFinder;
	}

	public void setPermissionUserFinder(
		PermissionUserFinder permissionUserFinder) {
		this.permissionUserFinder = permissionUserFinder;
	}

	public PhoneLocalService getPhoneLocalService() {
		return phoneLocalService;
	}

	public void setPhoneLocalService(PhoneLocalService phoneLocalService) {
		this.phoneLocalService = phoneLocalService;
	}

	public PhoneService getPhoneService() {
		return phoneService;
	}

	public void setPhoneService(PhoneService phoneService) {
		this.phoneService = phoneService;
	}

	public PhonePersistence getPhonePersistence() {
		return phonePersistence;
	}

	public void setPhonePersistence(PhonePersistence phonePersistence) {
		this.phonePersistence = phonePersistence;
	}

	public PortalService getPortalService() {
		return portalService;
	}

	public void setPortalService(PortalService portalService) {
		this.portalService = portalService;
	}

	public PluginSettingLocalService getPluginSettingLocalService() {
		return pluginSettingLocalService;
	}

	public void setPluginSettingLocalService(
		PluginSettingLocalService pluginSettingLocalService) {
		this.pluginSettingLocalService = pluginSettingLocalService;
	}

	public PluginSettingService getPluginSettingService() {
		return pluginSettingService;
	}

	public void setPluginSettingService(
		PluginSettingService pluginSettingService) {
		this.pluginSettingService = pluginSettingService;
	}

	public PluginSettingPersistence getPluginSettingPersistence() {
		return pluginSettingPersistence;
	}

	public void setPluginSettingPersistence(
		PluginSettingPersistence pluginSettingPersistence) {
		this.pluginSettingPersistence = pluginSettingPersistence;
	}

	public PortletLocalService getPortletLocalService() {
		return portletLocalService;
	}

	public void setPortletLocalService(PortletLocalService portletLocalService) {
		this.portletLocalService = portletLocalService;
	}

	public PortletService getPortletService() {
		return portletService;
	}

	public void setPortletService(PortletService portletService) {
		this.portletService = portletService;
	}

	public PortletPersistence getPortletPersistence() {
		return portletPersistence;
	}

	public void setPortletPersistence(PortletPersistence portletPersistence) {
		this.portletPersistence = portletPersistence;
	}

	public PortletPreferencesLocalService getPortletPreferencesLocalService() {
		return portletPreferencesLocalService;
	}

	public void setPortletPreferencesLocalService(
		PortletPreferencesLocalService portletPreferencesLocalService) {
		this.portletPreferencesLocalService = portletPreferencesLocalService;
	}

	public PortletPreferencesPersistence getPortletPreferencesPersistence() {
		return portletPreferencesPersistence;
	}

	public void setPortletPreferencesPersistence(
		PortletPreferencesPersistence portletPreferencesPersistence) {
		this.portletPreferencesPersistence = portletPreferencesPersistence;
	}

	public PortletPreferencesFinder getPortletPreferencesFinder() {
		return portletPreferencesFinder;
	}

	public void setPortletPreferencesFinder(
		PortletPreferencesFinder portletPreferencesFinder) {
		this.portletPreferencesFinder = portletPreferencesFinder;
	}

	public RegionService getRegionService() {
		return regionService;
	}

	public void setRegionService(RegionService regionService) {
		this.regionService = regionService;
	}

	public RegionPersistence getRegionPersistence() {
		return regionPersistence;
	}

	public void setRegionPersistence(RegionPersistence regionPersistence) {
		this.regionPersistence = regionPersistence;
	}

	public ReleaseLocalService getReleaseLocalService() {
		return releaseLocalService;
	}

	public void setReleaseLocalService(ReleaseLocalService releaseLocalService) {
		this.releaseLocalService = releaseLocalService;
	}

	public ReleasePersistence getReleasePersistence() {
		return releasePersistence;
	}

	public void setReleasePersistence(ReleasePersistence releasePersistence) {
		this.releasePersistence = releasePersistence;
	}

	public ResourceLocalService getResourceLocalService() {
		return resourceLocalService;
	}

	public void setResourceLocalService(
		ResourceLocalService resourceLocalService) {
		this.resourceLocalService = resourceLocalService;
	}

	public ResourceService getResourceService() {
		return resourceService;
	}

	public void setResourceService(ResourceService resourceService) {
		this.resourceService = resourceService;
	}

	public ResourcePersistence getResourcePersistence() {
		return resourcePersistence;
	}

	public void setResourcePersistence(ResourcePersistence resourcePersistence) {
		this.resourcePersistence = resourcePersistence;
	}

	public ResourceFinder getResourceFinder() {
		return resourceFinder;
	}

	public void setResourceFinder(ResourceFinder resourceFinder) {
		this.resourceFinder = resourceFinder;
	}

	public ResourceCodeLocalService getResourceCodeLocalService() {
		return resourceCodeLocalService;
	}

	public void setResourceCodeLocalService(
		ResourceCodeLocalService resourceCodeLocalService) {
		this.resourceCodeLocalService = resourceCodeLocalService;
	}

	public ResourceCodePersistence getResourceCodePersistence() {
		return resourceCodePersistence;
	}

	public void setResourceCodePersistence(
		ResourceCodePersistence resourceCodePersistence) {
		this.resourceCodePersistence = resourceCodePersistence;
	}

	public RoleLocalService getRoleLocalService() {
		return roleLocalService;
	}

	public void setRoleLocalService(RoleLocalService roleLocalService) {
		this.roleLocalService = roleLocalService;
	}

	public RoleService getRoleService() {
		return roleService;
	}

	public void setRoleService(RoleService roleService) {
		this.roleService = roleService;
	}

	public RolePersistence getRolePersistence() {
		return rolePersistence;
	}

	public void setRolePersistence(RolePersistence rolePersistence) {
		this.rolePersistence = rolePersistence;
	}

	public RoleFinder getRoleFinder() {
		return roleFinder;
	}

	public void setRoleFinder(RoleFinder roleFinder) {
		this.roleFinder = roleFinder;
	}

	public ServiceComponentLocalService getServiceComponentLocalService() {
		return serviceComponentLocalService;
	}

	public void setServiceComponentLocalService(
		ServiceComponentLocalService serviceComponentLocalService) {
		this.serviceComponentLocalService = serviceComponentLocalService;
	}

	public ServiceComponentPersistence getServiceComponentPersistence() {
		return serviceComponentPersistence;
	}

	public void setServiceComponentPersistence(
		ServiceComponentPersistence serviceComponentPersistence) {
		this.serviceComponentPersistence = serviceComponentPersistence;
	}

	public SubscriptionLocalService getSubscriptionLocalService() {
		return subscriptionLocalService;
	}

	public void setSubscriptionLocalService(
		SubscriptionLocalService subscriptionLocalService) {
		this.subscriptionLocalService = subscriptionLocalService;
	}

	public SubscriptionPersistence getSubscriptionPersistence() {
		return subscriptionPersistence;
	}

	public void setSubscriptionPersistence(
		SubscriptionPersistence subscriptionPersistence) {
		this.subscriptionPersistence = subscriptionPersistence;
	}

	public UserLocalService getUserLocalService() {
		return userLocalService;
	}

	public void setUserLocalService(UserLocalService userLocalService) {
		this.userLocalService = userLocalService;
	}

	public UserService getUserService() {
		return userService;
	}

	public void setUserService(UserService userService) {
		this.userService = userService;
	}

	public UserPersistence getUserPersistence() {
		return userPersistence;
	}

	public void setUserPersistence(UserPersistence userPersistence) {
		this.userPersistence = userPersistence;
	}

	public UserFinder getUserFinder() {
		return userFinder;
	}

	public void setUserFinder(UserFinder userFinder) {
		this.userFinder = userFinder;
	}

	public UserGroupLocalService getUserGroupLocalService() {
		return userGroupLocalService;
	}

	public void setUserGroupLocalService(
		UserGroupLocalService userGroupLocalService) {
		this.userGroupLocalService = userGroupLocalService;
	}

	public UserGroupService getUserGroupService() {
		return userGroupService;
	}

	public void setUserGroupService(UserGroupService userGroupService) {
		this.userGroupService = userGroupService;
	}

	public UserGroupPersistence getUserGroupPersistence() {
		return userGroupPersistence;
	}

	public void setUserGroupPersistence(
		UserGroupPersistence userGroupPersistence) {
		this.userGroupPersistence = userGroupPersistence;
	}

	public UserGroupFinder getUserGroupFinder() {
		return userGroupFinder;
	}

	public void setUserGroupFinder(UserGroupFinder userGroupFinder) {
		this.userGroupFinder = userGroupFinder;
	}

	public UserGroupRoleLocalService getUserGroupRoleLocalService() {
		return userGroupRoleLocalService;
	}

	public void setUserGroupRoleLocalService(
		UserGroupRoleLocalService userGroupRoleLocalService) {
		this.userGroupRoleLocalService = userGroupRoleLocalService;
	}

	public UserGroupRoleService getUserGroupRoleService() {
		return userGroupRoleService;
	}

	public void setUserGroupRoleService(
		UserGroupRoleService userGroupRoleService) {
		this.userGroupRoleService = userGroupRoleService;
	}

	public UserGroupRolePersistence getUserGroupRolePersistence() {
		return userGroupRolePersistence;
	}

	public void setUserGroupRolePersistence(
		UserGroupRolePersistence userGroupRolePersistence) {
		this.userGroupRolePersistence = userGroupRolePersistence;
	}

	public UserIdMapperLocalService getUserIdMapperLocalService() {
		return userIdMapperLocalService;
	}

	public void setUserIdMapperLocalService(
		UserIdMapperLocalService userIdMapperLocalService) {
		this.userIdMapperLocalService = userIdMapperLocalService;
	}

	public UserIdMapperPersistence getUserIdMapperPersistence() {
		return userIdMapperPersistence;
	}

	public void setUserIdMapperPersistence(
		UserIdMapperPersistence userIdMapperPersistence) {
		this.userIdMapperPersistence = userIdMapperPersistence;
	}

	public UserTrackerLocalService getUserTrackerLocalService() {
		return userTrackerLocalService;
	}

	public void setUserTrackerLocalService(
		UserTrackerLocalService userTrackerLocalService) {
		this.userTrackerLocalService = userTrackerLocalService;
	}

	public UserTrackerPersistence getUserTrackerPersistence() {
		return userTrackerPersistence;
	}

	public void setUserTrackerPersistence(
		UserTrackerPersistence userTrackerPersistence) {
		this.userTrackerPersistence = userTrackerPersistence;
	}

	public UserTrackerPathLocalService getUserTrackerPathLocalService() {
		return userTrackerPathLocalService;
	}

	public void setUserTrackerPathLocalService(
		UserTrackerPathLocalService userTrackerPathLocalService) {
		this.userTrackerPathLocalService = userTrackerPathLocalService;
	}

	public UserTrackerPathPersistence getUserTrackerPathPersistence() {
		return userTrackerPathPersistence;
	}

	public void setUserTrackerPathPersistence(
		UserTrackerPathPersistence userTrackerPathPersistence) {
		this.userTrackerPathPersistence = userTrackerPathPersistence;
	}

	public WebDAVPropsLocalService getWebDAVPropsLocalService() {
		return webDAVPropsLocalService;
	}

	public void setWebDAVPropsLocalService(
		WebDAVPropsLocalService webDAVPropsLocalService) {
		this.webDAVPropsLocalService = webDAVPropsLocalService;
	}

	public WebDAVPropsPersistence getWebDAVPropsPersistence() {
		return webDAVPropsPersistence;
	}

	public void setWebDAVPropsPersistence(
		WebDAVPropsPersistence webDAVPropsPersistence) {
		this.webDAVPropsPersistence = webDAVPropsPersistence;
	}

	public WebsiteLocalService getWebsiteLocalService() {
		return websiteLocalService;
	}

	public void setWebsiteLocalService(WebsiteLocalService websiteLocalService) {
		this.websiteLocalService = websiteLocalService;
	}

	public WebsiteService getWebsiteService() {
		return websiteService;
	}

	public void setWebsiteService(WebsiteService websiteService) {
		this.websiteService = websiteService;
	}

	public WebsitePersistence getWebsitePersistence() {
		return websitePersistence;
	}

	public void setWebsitePersistence(WebsitePersistence websitePersistence) {
		this.websitePersistence = websitePersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public BlogsEntryLocalService getBlogsEntryLocalService() {
		return blogsEntryLocalService;
	}

	public void setBlogsEntryLocalService(
		BlogsEntryLocalService blogsEntryLocalService) {
		this.blogsEntryLocalService = blogsEntryLocalService;
	}

	public BlogsEntryService getBlogsEntryService() {
		return blogsEntryService;
	}

	public void setBlogsEntryService(BlogsEntryService blogsEntryService) {
		this.blogsEntryService = blogsEntryService;
	}

	public BlogsEntryPersistence getBlogsEntryPersistence() {
		return blogsEntryPersistence;
	}

	public void setBlogsEntryPersistence(
		BlogsEntryPersistence blogsEntryPersistence) {
		this.blogsEntryPersistence = blogsEntryPersistence;
	}

	public BlogsEntryFinder getBlogsEntryFinder() {
		return blogsEntryFinder;
	}

	public void setBlogsEntryFinder(BlogsEntryFinder blogsEntryFinder) {
		this.blogsEntryFinder = blogsEntryFinder;
	}

	public BlogsStatsUserLocalService getBlogsStatsUserLocalService() {
		return blogsStatsUserLocalService;
	}

	public void setBlogsStatsUserLocalService(
		BlogsStatsUserLocalService blogsStatsUserLocalService) {
		this.blogsStatsUserLocalService = blogsStatsUserLocalService;
	}

	public BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		return blogsStatsUserPersistence;
	}

	public void setBlogsStatsUserPersistence(
		BlogsStatsUserPersistence blogsStatsUserPersistence) {
		this.blogsStatsUserPersistence = blogsStatsUserPersistence;
	}

	public BlogsStatsUserFinder getBlogsStatsUserFinder() {
		return blogsStatsUserFinder;
	}

	public void setBlogsStatsUserFinder(
		BlogsStatsUserFinder blogsStatsUserFinder) {
		this.blogsStatsUserFinder = blogsStatsUserFinder;
	}

	public BookmarksFolderLocalService getBookmarksFolderLocalService() {
		return bookmarksFolderLocalService;
	}

	public void setBookmarksFolderLocalService(
		BookmarksFolderLocalService bookmarksFolderLocalService) {
		this.bookmarksFolderLocalService = bookmarksFolderLocalService;
	}

	public BookmarksFolderService getBookmarksFolderService() {
		return bookmarksFolderService;
	}

	public void setBookmarksFolderService(
		BookmarksFolderService bookmarksFolderService) {
		this.bookmarksFolderService = bookmarksFolderService;
	}

	public BookmarksFolderPersistence getBookmarksFolderPersistence() {
		return bookmarksFolderPersistence;
	}

	public void setBookmarksFolderPersistence(
		BookmarksFolderPersistence bookmarksFolderPersistence) {
		this.bookmarksFolderPersistence = bookmarksFolderPersistence;
	}

	public CalEventLocalService getCalEventLocalService() {
		return calEventLocalService;
	}

	public void setCalEventLocalService(
		CalEventLocalService calEventLocalService) {
		this.calEventLocalService = calEventLocalService;
	}

	public CalEventService getCalEventService() {
		return calEventService;
	}

	public void setCalEventService(CalEventService calEventService) {
		this.calEventService = calEventService;
	}

	public CalEventPersistence getCalEventPersistence() {
		return calEventPersistence;
	}

	public void setCalEventPersistence(CalEventPersistence calEventPersistence) {
		this.calEventPersistence = calEventPersistence;
	}

	public CalEventFinder getCalEventFinder() {
		return calEventFinder;
	}

	public void setCalEventFinder(CalEventFinder calEventFinder) {
		this.calEventFinder = calEventFinder;
	}

	public DLFolderLocalService getDLFolderLocalService() {
		return dlFolderLocalService;
	}

	public void setDLFolderLocalService(
		DLFolderLocalService dlFolderLocalService) {
		this.dlFolderLocalService = dlFolderLocalService;
	}

	public DLFolderService getDLFolderService() {
		return dlFolderService;
	}

	public void setDLFolderService(DLFolderService dlFolderService) {
		this.dlFolderService = dlFolderService;
	}

	public DLFolderPersistence getDLFolderPersistence() {
		return dlFolderPersistence;
	}

	public void setDLFolderPersistence(DLFolderPersistence dlFolderPersistence) {
		this.dlFolderPersistence = dlFolderPersistence;
	}

	public IGFolderLocalService getIGFolderLocalService() {
		return igFolderLocalService;
	}

	public void setIGFolderLocalService(
		IGFolderLocalService igFolderLocalService) {
		this.igFolderLocalService = igFolderLocalService;
	}

	public IGFolderService getIGFolderService() {
		return igFolderService;
	}

	public void setIGFolderService(IGFolderService igFolderService) {
		this.igFolderService = igFolderService;
	}

	public IGFolderPersistence getIGFolderPersistence() {
		return igFolderPersistence;
	}

	public void setIGFolderPersistence(IGFolderPersistence igFolderPersistence) {
		this.igFolderPersistence = igFolderPersistence;
	}

	public JournalArticleLocalService getJournalArticleLocalService() {
		return journalArticleLocalService;
	}

	public void setJournalArticleLocalService(
		JournalArticleLocalService journalArticleLocalService) {
		this.journalArticleLocalService = journalArticleLocalService;
	}

	public JournalArticleService getJournalArticleService() {
		return journalArticleService;
	}

	public void setJournalArticleService(
		JournalArticleService journalArticleService) {
		this.journalArticleService = journalArticleService;
	}

	public JournalArticlePersistence getJournalArticlePersistence() {
		return journalArticlePersistence;
	}

	public void setJournalArticlePersistence(
		JournalArticlePersistence journalArticlePersistence) {
		this.journalArticlePersistence = journalArticlePersistence;
	}

	public JournalArticleFinder getJournalArticleFinder() {
		return journalArticleFinder;
	}

	public void setJournalArticleFinder(
		JournalArticleFinder journalArticleFinder) {
		this.journalArticleFinder = journalArticleFinder;
	}

	public JournalStructureLocalService getJournalStructureLocalService() {
		return journalStructureLocalService;
	}

	public void setJournalStructureLocalService(
		JournalStructureLocalService journalStructureLocalService) {
		this.journalStructureLocalService = journalStructureLocalService;
	}

	public JournalStructureService getJournalStructureService() {
		return journalStructureService;
	}

	public void setJournalStructureService(
		JournalStructureService journalStructureService) {
		this.journalStructureService = journalStructureService;
	}

	public JournalStructurePersistence getJournalStructurePersistence() {
		return journalStructurePersistence;
	}

	public void setJournalStructurePersistence(
		JournalStructurePersistence journalStructurePersistence) {
		this.journalStructurePersistence = journalStructurePersistence;
	}

	public JournalStructureFinder getJournalStructureFinder() {
		return journalStructureFinder;
	}

	public void setJournalStructureFinder(
		JournalStructureFinder journalStructureFinder) {
		this.journalStructureFinder = journalStructureFinder;
	}

	public JournalTemplateLocalService getJournalTemplateLocalService() {
		return journalTemplateLocalService;
	}

	public void setJournalTemplateLocalService(
		JournalTemplateLocalService journalTemplateLocalService) {
		this.journalTemplateLocalService = journalTemplateLocalService;
	}

	public JournalTemplateService getJournalTemplateService() {
		return journalTemplateService;
	}

	public void setJournalTemplateService(
		JournalTemplateService journalTemplateService) {
		this.journalTemplateService = journalTemplateService;
	}

	public JournalTemplatePersistence getJournalTemplatePersistence() {
		return journalTemplatePersistence;
	}

	public void setJournalTemplatePersistence(
		JournalTemplatePersistence journalTemplatePersistence) {
		this.journalTemplatePersistence = journalTemplatePersistence;
	}

	public JournalTemplateFinder getJournalTemplateFinder() {
		return journalTemplateFinder;
	}

	public void setJournalTemplateFinder(
		JournalTemplateFinder journalTemplateFinder) {
		this.journalTemplateFinder = journalTemplateFinder;
	}

	public MBBanLocalService getMBBanLocalService() {
		return mbBanLocalService;
	}

	public void setMBBanLocalService(MBBanLocalService mbBanLocalService) {
		this.mbBanLocalService = mbBanLocalService;
	}

	public MBBanService getMBBanService() {
		return mbBanService;
	}

	public void setMBBanService(MBBanService mbBanService) {
		this.mbBanService = mbBanService;
	}

	public MBBanPersistence getMBBanPersistence() {
		return mbBanPersistence;
	}

	public void setMBBanPersistence(MBBanPersistence mbBanPersistence) {
		this.mbBanPersistence = mbBanPersistence;
	}

	public MBCategoryLocalService getMBCategoryLocalService() {
		return mbCategoryLocalService;
	}

	public void setMBCategoryLocalService(
		MBCategoryLocalService mbCategoryLocalService) {
		this.mbCategoryLocalService = mbCategoryLocalService;
	}

	public MBCategoryService getMBCategoryService() {
		return mbCategoryService;
	}

	public void setMBCategoryService(MBCategoryService mbCategoryService) {
		this.mbCategoryService = mbCategoryService;
	}

	public MBCategoryPersistence getMBCategoryPersistence() {
		return mbCategoryPersistence;
	}

	public void setMBCategoryPersistence(
		MBCategoryPersistence mbCategoryPersistence) {
		this.mbCategoryPersistence = mbCategoryPersistence;
	}

	public MBCategoryFinder getMBCategoryFinder() {
		return mbCategoryFinder;
	}

	public void setMBCategoryFinder(MBCategoryFinder mbCategoryFinder) {
		this.mbCategoryFinder = mbCategoryFinder;
	}

	public MBStatsUserLocalService getMBStatsUserLocalService() {
		return mbStatsUserLocalService;
	}

	public void setMBStatsUserLocalService(
		MBStatsUserLocalService mbStatsUserLocalService) {
		this.mbStatsUserLocalService = mbStatsUserLocalService;
	}

	public MBStatsUserPersistence getMBStatsUserPersistence() {
		return mbStatsUserPersistence;
	}

	public void setMBStatsUserPersistence(
		MBStatsUserPersistence mbStatsUserPersistence) {
		this.mbStatsUserPersistence = mbStatsUserPersistence;
	}

	public PollsQuestionLocalService getPollsQuestionLocalService() {
		return pollsQuestionLocalService;
	}

	public void setPollsQuestionLocalService(
		PollsQuestionLocalService pollsQuestionLocalService) {
		this.pollsQuestionLocalService = pollsQuestionLocalService;
	}

	public PollsQuestionService getPollsQuestionService() {
		return pollsQuestionService;
	}

	public void setPollsQuestionService(
		PollsQuestionService pollsQuestionService) {
		this.pollsQuestionService = pollsQuestionService;
	}

	public PollsQuestionPersistence getPollsQuestionPersistence() {
		return pollsQuestionPersistence;
	}

	public void setPollsQuestionPersistence(
		PollsQuestionPersistence pollsQuestionPersistence) {
		this.pollsQuestionPersistence = pollsQuestionPersistence;
	}

	public ShoppingCartLocalService getShoppingCartLocalService() {
		return shoppingCartLocalService;
	}

	public void setShoppingCartLocalService(
		ShoppingCartLocalService shoppingCartLocalService) {
		this.shoppingCartLocalService = shoppingCartLocalService;
	}

	public ShoppingCartPersistence getShoppingCartPersistence() {
		return shoppingCartPersistence;
	}

	public void setShoppingCartPersistence(
		ShoppingCartPersistence shoppingCartPersistence) {
		this.shoppingCartPersistence = shoppingCartPersistence;
	}

	public ShoppingCategoryLocalService getShoppingCategoryLocalService() {
		return shoppingCategoryLocalService;
	}

	public void setShoppingCategoryLocalService(
		ShoppingCategoryLocalService shoppingCategoryLocalService) {
		this.shoppingCategoryLocalService = shoppingCategoryLocalService;
	}

	public ShoppingCategoryService getShoppingCategoryService() {
		return shoppingCategoryService;
	}

	public void setShoppingCategoryService(
		ShoppingCategoryService shoppingCategoryService) {
		this.shoppingCategoryService = shoppingCategoryService;
	}

	public ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		return shoppingCategoryPersistence;
	}

	public void setShoppingCategoryPersistence(
		ShoppingCategoryPersistence shoppingCategoryPersistence) {
		this.shoppingCategoryPersistence = shoppingCategoryPersistence;
	}

	public ShoppingCouponLocalService getShoppingCouponLocalService() {
		return shoppingCouponLocalService;
	}

	public void setShoppingCouponLocalService(
		ShoppingCouponLocalService shoppingCouponLocalService) {
		this.shoppingCouponLocalService = shoppingCouponLocalService;
	}

	public ShoppingCouponService getShoppingCouponService() {
		return shoppingCouponService;
	}

	public void setShoppingCouponService(
		ShoppingCouponService shoppingCouponService) {
		this.shoppingCouponService = shoppingCouponService;
	}

	public ShoppingCouponPersistence getShoppingCouponPersistence() {
		return shoppingCouponPersistence;
	}

	public void setShoppingCouponPersistence(
		ShoppingCouponPersistence shoppingCouponPersistence) {
		this.shoppingCouponPersistence = shoppingCouponPersistence;
	}

	public ShoppingCouponFinder getShoppingCouponFinder() {
		return shoppingCouponFinder;
	}

	public void setShoppingCouponFinder(
		ShoppingCouponFinder shoppingCouponFinder) {
		this.shoppingCouponFinder = shoppingCouponFinder;
	}

	public ShoppingOrderLocalService getShoppingOrderLocalService() {
		return shoppingOrderLocalService;
	}

	public void setShoppingOrderLocalService(
		ShoppingOrderLocalService shoppingOrderLocalService) {
		this.shoppingOrderLocalService = shoppingOrderLocalService;
	}

	public ShoppingOrderService getShoppingOrderService() {
		return shoppingOrderService;
	}

	public void setShoppingOrderService(
		ShoppingOrderService shoppingOrderService) {
		this.shoppingOrderService = shoppingOrderService;
	}

	public ShoppingOrderPersistence getShoppingOrderPersistence() {
		return shoppingOrderPersistence;
	}

	public void setShoppingOrderPersistence(
		ShoppingOrderPersistence shoppingOrderPersistence) {
		this.shoppingOrderPersistence = shoppingOrderPersistence;
	}

	public ShoppingOrderFinder getShoppingOrderFinder() {
		return shoppingOrderFinder;
	}

	public void setShoppingOrderFinder(ShoppingOrderFinder shoppingOrderFinder) {
		this.shoppingOrderFinder = shoppingOrderFinder;
	}

	public SCFrameworkVersionLocalService getSCFrameworkVersionLocalService() {
		return scFrameworkVersionLocalService;
	}

	public void setSCFrameworkVersionLocalService(
		SCFrameworkVersionLocalService scFrameworkVersionLocalService) {
		this.scFrameworkVersionLocalService = scFrameworkVersionLocalService;
	}

	public SCFrameworkVersionService getSCFrameworkVersionService() {
		return scFrameworkVersionService;
	}

	public void setSCFrameworkVersionService(
		SCFrameworkVersionService scFrameworkVersionService) {
		this.scFrameworkVersionService = scFrameworkVersionService;
	}

	public SCFrameworkVersionPersistence getSCFrameworkVersionPersistence() {
		return scFrameworkVersionPersistence;
	}

	public void setSCFrameworkVersionPersistence(
		SCFrameworkVersionPersistence scFrameworkVersionPersistence) {
		this.scFrameworkVersionPersistence = scFrameworkVersionPersistence;
	}

	public SCProductEntryLocalService getSCProductEntryLocalService() {
		return scProductEntryLocalService;
	}

	public void setSCProductEntryLocalService(
		SCProductEntryLocalService scProductEntryLocalService) {
		this.scProductEntryLocalService = scProductEntryLocalService;
	}

	public SCProductEntryService getSCProductEntryService() {
		return scProductEntryService;
	}

	public void setSCProductEntryService(
		SCProductEntryService scProductEntryService) {
		this.scProductEntryService = scProductEntryService;
	}

	public SCProductEntryPersistence getSCProductEntryPersistence() {
		return scProductEntryPersistence;
	}

	public void setSCProductEntryPersistence(
		SCProductEntryPersistence scProductEntryPersistence) {
		this.scProductEntryPersistence = scProductEntryPersistence;
	}

	public WikiNodeLocalService getWikiNodeLocalService() {
		return wikiNodeLocalService;
	}

	public void setWikiNodeLocalService(
		WikiNodeLocalService wikiNodeLocalService) {
		this.wikiNodeLocalService = wikiNodeLocalService;
	}

	public WikiNodeService getWikiNodeService() {
		return wikiNodeService;
	}

	public void setWikiNodeService(WikiNodeService wikiNodeService) {
		this.wikiNodeService = wikiNodeService;
	}

	public WikiNodePersistence getWikiNodePersistence() {
		return wikiNodePersistence;
	}

	public void setWikiNodePersistence(WikiNodePersistence wikiNodePersistence) {
		this.wikiNodePersistence = wikiNodePersistence;
	}

	public void afterPropertiesSet() {
		if (accountLocalService == null) {
			accountLocalService = AccountLocalServiceFactory.getImpl();
		}

		if (accountService == null) {
			accountService = AccountServiceFactory.getImpl();
		}

		if (accountPersistence == null) {
			accountPersistence = AccountUtil.getPersistence();
		}

		if (activityTrackerLocalService == null) {
			activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getImpl();
		}

		if (activityTrackerPersistence == null) {
			activityTrackerPersistence = ActivityTrackerUtil.getPersistence();
		}

		if (activityTrackerFinder == null) {
			activityTrackerFinder = ActivityTrackerFinderUtil.getFinder();
		}

		if (addressLocalService == null) {
			addressLocalService = AddressLocalServiceFactory.getImpl();
		}

		if (addressService == null) {
			addressService = AddressServiceFactory.getImpl();
		}

		if (addressPersistence == null) {
			addressPersistence = AddressUtil.getPersistence();
		}

		if (classNameLocalService == null) {
			classNameLocalService = ClassNameLocalServiceFactory.getImpl();
		}

		if (classNameService == null) {
			classNameService = ClassNameServiceFactory.getImpl();
		}

		if (classNamePersistence == null) {
			classNamePersistence = ClassNameUtil.getPersistence();
		}

		if (companyLocalService == null) {
			companyLocalService = CompanyLocalServiceFactory.getImpl();
		}

		if (companyService == null) {
			companyService = CompanyServiceFactory.getImpl();
		}

		if (companyPersistence == null) {
			companyPersistence = CompanyUtil.getPersistence();
		}

		if (contactLocalService == null) {
			contactLocalService = ContactLocalServiceFactory.getImpl();
		}

		if (contactService == null) {
			contactService = ContactServiceFactory.getImpl();
		}

		if (contactPersistence == null) {
			contactPersistence = ContactUtil.getPersistence();
		}

		if (countryService == null) {
			countryService = CountryServiceFactory.getImpl();
		}

		if (countryPersistence == null) {
			countryPersistence = CountryUtil.getPersistence();
		}

		if (emailAddressLocalService == null) {
			emailAddressLocalService = EmailAddressLocalServiceFactory.getImpl();
		}

		if (emailAddressService == null) {
			emailAddressService = EmailAddressServiceFactory.getImpl();
		}

		if (emailAddressPersistence == null) {
			emailAddressPersistence = EmailAddressUtil.getPersistence();
		}

		if (groupLocalService == null) {
			groupLocalService = GroupLocalServiceFactory.getImpl();
		}

		if (groupPersistence == null) {
			groupPersistence = GroupUtil.getPersistence();
		}

		if (groupFinder == null) {
			groupFinder = GroupFinderUtil.getFinder();
		}

		if (imageLocalService == null) {
			imageLocalService = ImageLocalServiceFactory.getImpl();
		}

		if (imagePersistence == null) {
			imagePersistence = ImageUtil.getPersistence();
		}

		if (layoutLocalService == null) {
			layoutLocalService = LayoutLocalServiceFactory.getImpl();
		}

		if (layoutService == null) {
			layoutService = LayoutServiceFactory.getImpl();
		}

		if (layoutPersistence == null) {
			layoutPersistence = LayoutUtil.getPersistence();
		}

		if (layoutFinder == null) {
			layoutFinder = LayoutFinderUtil.getFinder();
		}

		if (layoutSetLocalService == null) {
			layoutSetLocalService = LayoutSetLocalServiceFactory.getImpl();
		}

		if (layoutSetService == null) {
			layoutSetService = LayoutSetServiceFactory.getImpl();
		}

		if (layoutSetPersistence == null) {
			layoutSetPersistence = LayoutSetUtil.getPersistence();
		}

		if (listTypeService == null) {
			listTypeService = ListTypeServiceFactory.getImpl();
		}

		if (listTypePersistence == null) {
			listTypePersistence = ListTypeUtil.getPersistence();
		}

		if (membershipRequestLocalService == null) {
			membershipRequestLocalService = MembershipRequestLocalServiceFactory.getImpl();
		}

		if (membershipRequestService == null) {
			membershipRequestService = MembershipRequestServiceFactory.getImpl();
		}

		if (membershipRequestPersistence == null) {
			membershipRequestPersistence = MembershipRequestUtil.getPersistence();
		}

		if (organizationLocalService == null) {
			organizationLocalService = OrganizationLocalServiceFactory.getImpl();
		}

		if (organizationService == null) {
			organizationService = OrganizationServiceFactory.getImpl();
		}

		if (organizationPersistence == null) {
			organizationPersistence = OrganizationUtil.getPersistence();
		}

		if (organizationFinder == null) {
			organizationFinder = OrganizationFinderUtil.getFinder();
		}

		if (orgGroupPermissionPersistence == null) {
			orgGroupPermissionPersistence = OrgGroupPermissionUtil.getPersistence();
		}

		if (orgGroupPermissionFinder == null) {
			orgGroupPermissionFinder = OrgGroupPermissionFinderUtil.getFinder();
		}

		if (orgGroupRolePersistence == null) {
			orgGroupRolePersistence = OrgGroupRoleUtil.getPersistence();
		}

		if (orgLaborLocalService == null) {
			orgLaborLocalService = OrgLaborLocalServiceFactory.getImpl();
		}

		if (orgLaborService == null) {
			orgLaborService = OrgLaborServiceFactory.getImpl();
		}

		if (orgLaborPersistence == null) {
			orgLaborPersistence = OrgLaborUtil.getPersistence();
		}

		if (passwordPolicyLocalService == null) {
			passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getImpl();
		}

		if (passwordPolicyService == null) {
			passwordPolicyService = PasswordPolicyServiceFactory.getImpl();
		}

		if (passwordPolicyPersistence == null) {
			passwordPolicyPersistence = PasswordPolicyUtil.getPersistence();
		}

		if (passwordPolicyFinder == null) {
			passwordPolicyFinder = PasswordPolicyFinderUtil.getFinder();
		}

		if (passwordPolicyRelLocalService == null) {
			passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getImpl();
		}

		if (passwordPolicyRelPersistence == null) {
			passwordPolicyRelPersistence = PasswordPolicyRelUtil.getPersistence();
		}

		if (passwordTrackerLocalService == null) {
			passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getImpl();
		}

		if (passwordTrackerPersistence == null) {
			passwordTrackerPersistence = PasswordTrackerUtil.getPersistence();
		}

		if (permissionLocalService == null) {
			permissionLocalService = PermissionLocalServiceFactory.getImpl();
		}

		if (permissionService == null) {
			permissionService = PermissionServiceFactory.getImpl();
		}

		if (permissionPersistence == null) {
			permissionPersistence = PermissionUtil.getPersistence();
		}

		if (permissionFinder == null) {
			permissionFinder = PermissionFinderUtil.getFinder();
		}

		if (permissionUserFinder == null) {
			permissionUserFinder = PermissionUserFinderUtil.getFinder();
		}

		if (phoneLocalService == null) {
			phoneLocalService = PhoneLocalServiceFactory.getImpl();
		}

		if (phoneService == null) {
			phoneService = PhoneServiceFactory.getImpl();
		}

		if (phonePersistence == null) {
			phonePersistence = PhoneUtil.getPersistence();
		}

		if (portalService == null) {
			portalService = PortalServiceFactory.getImpl();
		}

		if (pluginSettingLocalService == null) {
			pluginSettingLocalService = PluginSettingLocalServiceFactory.getImpl();
		}

		if (pluginSettingService == null) {
			pluginSettingService = PluginSettingServiceFactory.getImpl();
		}

		if (pluginSettingPersistence == null) {
			pluginSettingPersistence = PluginSettingUtil.getPersistence();
		}

		if (portletLocalService == null) {
			portletLocalService = PortletLocalServiceFactory.getImpl();
		}

		if (portletService == null) {
			portletService = PortletServiceFactory.getImpl();
		}

		if (portletPersistence == null) {
			portletPersistence = PortletUtil.getPersistence();
		}

		if (portletPreferencesLocalService == null) {
			portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getImpl();
		}

		if (portletPreferencesPersistence == null) {
			portletPreferencesPersistence = PortletPreferencesUtil.getPersistence();
		}

		if (portletPreferencesFinder == null) {
			portletPreferencesFinder = PortletPreferencesFinderUtil.getFinder();
		}

		if (regionService == null) {
			regionService = RegionServiceFactory.getImpl();
		}

		if (regionPersistence == null) {
			regionPersistence = RegionUtil.getPersistence();
		}

		if (releaseLocalService == null) {
			releaseLocalService = ReleaseLocalServiceFactory.getImpl();
		}

		if (releasePersistence == null) {
			releasePersistence = ReleaseUtil.getPersistence();
		}

		if (resourceLocalService == null) {
			resourceLocalService = ResourceLocalServiceFactory.getImpl();
		}

		if (resourceService == null) {
			resourceService = ResourceServiceFactory.getImpl();
		}

		if (resourcePersistence == null) {
			resourcePersistence = ResourceUtil.getPersistence();
		}

		if (resourceFinder == null) {
			resourceFinder = ResourceFinderUtil.getFinder();
		}

		if (resourceCodeLocalService == null) {
			resourceCodeLocalService = ResourceCodeLocalServiceFactory.getImpl();
		}

		if (resourceCodePersistence == null) {
			resourceCodePersistence = ResourceCodeUtil.getPersistence();
		}

		if (roleLocalService == null) {
			roleLocalService = RoleLocalServiceFactory.getImpl();
		}

		if (roleService == null) {
			roleService = RoleServiceFactory.getImpl();
		}

		if (rolePersistence == null) {
			rolePersistence = RoleUtil.getPersistence();
		}

		if (roleFinder == null) {
			roleFinder = RoleFinderUtil.getFinder();
		}

		if (serviceComponentLocalService == null) {
			serviceComponentLocalService = ServiceComponentLocalServiceFactory.getImpl();
		}

		if (serviceComponentPersistence == null) {
			serviceComponentPersistence = ServiceComponentUtil.getPersistence();
		}

		if (subscriptionLocalService == null) {
			subscriptionLocalService = SubscriptionLocalServiceFactory.getImpl();
		}

		if (subscriptionPersistence == null) {
			subscriptionPersistence = SubscriptionUtil.getPersistence();
		}

		if (userLocalService == null) {
			userLocalService = UserLocalServiceFactory.getImpl();
		}

		if (userService == null) {
			userService = UserServiceFactory.getImpl();
		}

		if (userPersistence == null) {
			userPersistence = UserUtil.getPersistence();
		}

		if (userFinder == null) {
			userFinder = UserFinderUtil.getFinder();
		}

		if (userGroupLocalService == null) {
			userGroupLocalService = UserGroupLocalServiceFactory.getImpl();
		}

		if (userGroupService == null) {
			userGroupService = UserGroupServiceFactory.getImpl();
		}

		if (userGroupPersistence == null) {
			userGroupPersistence = UserGroupUtil.getPersistence();
		}

		if (userGroupFinder == null) {
			userGroupFinder = UserGroupFinderUtil.getFinder();
		}

		if (userGroupRoleLocalService == null) {
			userGroupRoleLocalService = UserGroupRoleLocalServiceFactory.getImpl();
		}

		if (userGroupRoleService == null) {
			userGroupRoleService = UserGroupRoleServiceFactory.getImpl();
		}

		if (userGroupRolePersistence == null) {
			userGroupRolePersistence = UserGroupRoleUtil.getPersistence();
		}

		if (userIdMapperLocalService == null) {
			userIdMapperLocalService = UserIdMapperLocalServiceFactory.getImpl();
		}

		if (userIdMapperPersistence == null) {
			userIdMapperPersistence = UserIdMapperUtil.getPersistence();
		}

		if (userTrackerLocalService == null) {
			userTrackerLocalService = UserTrackerLocalServiceFactory.getImpl();
		}

		if (userTrackerPersistence == null) {
			userTrackerPersistence = UserTrackerUtil.getPersistence();
		}

		if (userTrackerPathLocalService == null) {
			userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getImpl();
		}

		if (userTrackerPathPersistence == null) {
			userTrackerPathPersistence = UserTrackerPathUtil.getPersistence();
		}

		if (webDAVPropsLocalService == null) {
			webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getImpl();
		}

		if (webDAVPropsPersistence == null) {
			webDAVPropsPersistence = WebDAVPropsUtil.getPersistence();
		}

		if (websiteLocalService == null) {
			websiteLocalService = WebsiteLocalServiceFactory.getImpl();
		}

		if (websiteService == null) {
			websiteService = WebsiteServiceFactory.getImpl();
		}

		if (websitePersistence == null) {
			websitePersistence = WebsiteUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (blogsEntryLocalService == null) {
			blogsEntryLocalService = BlogsEntryLocalServiceFactory.getImpl();
		}

		if (blogsEntryService == null) {
			blogsEntryService = BlogsEntryServiceFactory.getImpl();
		}

		if (blogsEntryPersistence == null) {
			blogsEntryPersistence = BlogsEntryUtil.getPersistence();
		}

		if (blogsEntryFinder == null) {
			blogsEntryFinder = BlogsEntryFinderUtil.getFinder();
		}

		if (blogsStatsUserLocalService == null) {
			blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getImpl();
		}

		if (blogsStatsUserPersistence == null) {
			blogsStatsUserPersistence = BlogsStatsUserUtil.getPersistence();
		}

		if (blogsStatsUserFinder == null) {
			blogsStatsUserFinder = BlogsStatsUserFinderUtil.getFinder();
		}

		if (bookmarksFolderLocalService == null) {
			bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getImpl();
		}

		if (bookmarksFolderService == null) {
			bookmarksFolderService = BookmarksFolderServiceFactory.getImpl();
		}

		if (bookmarksFolderPersistence == null) {
			bookmarksFolderPersistence = BookmarksFolderUtil.getPersistence();
		}

		if (calEventLocalService == null) {
			calEventLocalService = CalEventLocalServiceFactory.getImpl();
		}

		if (calEventService == null) {
			calEventService = CalEventServiceFactory.getImpl();
		}

		if (calEventPersistence == null) {
			calEventPersistence = CalEventUtil.getPersistence();
		}

		if (calEventFinder == null) {
			calEventFinder = CalEventFinderUtil.getFinder();
		}

		if (dlFolderLocalService == null) {
			dlFolderLocalService = DLFolderLocalServiceFactory.getImpl();
		}

		if (dlFolderService == null) {
			dlFolderService = DLFolderServiceFactory.getImpl();
		}

		if (dlFolderPersistence == null) {
			dlFolderPersistence = DLFolderUtil.getPersistence();
		}

		if (igFolderLocalService == null) {
			igFolderLocalService = IGFolderLocalServiceFactory.getImpl();
		}

		if (igFolderService == null) {
			igFolderService = IGFolderServiceFactory.getImpl();
		}

		if (igFolderPersistence == null) {
			igFolderPersistence = IGFolderUtil.getPersistence();
		}

		if (journalArticleLocalService == null) {
			journalArticleLocalService = JournalArticleLocalServiceFactory.getImpl();
		}

		if (journalArticleService == null) {
			journalArticleService = JournalArticleServiceFactory.getImpl();
		}

		if (journalArticlePersistence == null) {
			journalArticlePersistence = JournalArticleUtil.getPersistence();
		}

		if (journalArticleFinder == null) {
			journalArticleFinder = JournalArticleFinderUtil.getFinder();
		}

		if (journalStructureLocalService == null) {
			journalStructureLocalService = JournalStructureLocalServiceFactory.getImpl();
		}

		if (journalStructureService == null) {
			journalStructureService = JournalStructureServiceFactory.getImpl();
		}

		if (journalStructurePersistence == null) {
			journalStructurePersistence = JournalStructureUtil.getPersistence();
		}

		if (journalStructureFinder == null) {
			journalStructureFinder = JournalStructureFinderUtil.getFinder();
		}

		if (journalTemplateLocalService == null) {
			journalTemplateLocalService = JournalTemplateLocalServiceFactory.getImpl();
		}

		if (journalTemplateService == null) {
			journalTemplateService = JournalTemplateServiceFactory.getImpl();
		}

		if (journalTemplatePersistence == null) {
			journalTemplatePersistence = JournalTemplateUtil.getPersistence();
		}

		if (journalTemplateFinder == null) {
			journalTemplateFinder = JournalTemplateFinderUtil.getFinder();
		}

		if (mbBanLocalService == null) {
			mbBanLocalService = MBBanLocalServiceFactory.getImpl();
		}

		if (mbBanService == null) {
			mbBanService = MBBanServiceFactory.getImpl();
		}

		if (mbBanPersistence == null) {
			mbBanPersistence = MBBanUtil.getPersistence();
		}

		if (mbCategoryLocalService == null) {
			mbCategoryLocalService = MBCategoryLocalServiceFactory.getImpl();
		}

		if (mbCategoryService == null) {
			mbCategoryService = MBCategoryServiceFactory.getImpl();
		}

		if (mbCategoryPersistence == null) {
			mbCategoryPersistence = MBCategoryUtil.getPersistence();
		}

		if (mbCategoryFinder == null) {
			mbCategoryFinder = MBCategoryFinderUtil.getFinder();
		}

		if (mbStatsUserLocalService == null) {
			mbStatsUserLocalService = MBStatsUserLocalServiceFactory.getImpl();
		}

		if (mbStatsUserPersistence == null) {
			mbStatsUserPersistence = MBStatsUserUtil.getPersistence();
		}

		if (pollsQuestionLocalService == null) {
			pollsQuestionLocalService = PollsQuestionLocalServiceFactory.getImpl();
		}

		if (pollsQuestionService == null) {
			pollsQuestionService = PollsQuestionServiceFactory.getImpl();
		}

		if (pollsQuestionPersistence == null) {
			pollsQuestionPersistence = PollsQuestionUtil.getPersistence();
		}

		if (shoppingCartLocalService == null) {
			shoppingCartLocalService = ShoppingCartLocalServiceFactory.getImpl();
		}

		if (shoppingCartPersistence == null) {
			shoppingCartPersistence = ShoppingCartUtil.getPersistence();
		}

		if (shoppingCategoryLocalService == null) {
			shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getImpl();
		}

		if (shoppingCategoryService == null) {
			shoppingCategoryService = ShoppingCategoryServiceFactory.getImpl();
		}

		if (shoppingCategoryPersistence == null) {
			shoppingCategoryPersistence = ShoppingCategoryUtil.getPersistence();
		}

		if (shoppingCouponLocalService == null) {
			shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getImpl();
		}

		if (shoppingCouponService == null) {
			shoppingCouponService = ShoppingCouponServiceFactory.getImpl();
		}

		if (shoppingCouponPersistence == null) {
			shoppingCouponPersistence = ShoppingCouponUtil.getPersistence();
		}

		if (shoppingCouponFinder == null) {
			shoppingCouponFinder = ShoppingCouponFinderUtil.getFinder();
		}

		if (shoppingOrderLocalService == null) {
			shoppingOrderLocalService = ShoppingOrderLocalServiceFactory.getImpl();
		}

		if (shoppingOrderService == null) {
			shoppingOrderService = ShoppingOrderServiceFactory.getImpl();
		}

		if (shoppingOrderPersistence == null) {
			shoppingOrderPersistence = ShoppingOrderUtil.getPersistence();
		}

		if (shoppingOrderFinder == null) {
			shoppingOrderFinder = ShoppingOrderFinderUtil.getFinder();
		}

		if (scFrameworkVersionLocalService == null) {
			scFrameworkVersionLocalService = SCFrameworkVersionLocalServiceFactory.getImpl();
		}

		if (scFrameworkVersionService == null) {
			scFrameworkVersionService = SCFrameworkVersionServiceFactory.getImpl();
		}

		if (scFrameworkVersionPersistence == null) {
			scFrameworkVersionPersistence = SCFrameworkVersionUtil.getPersistence();
		}

		if (scProductEntryLocalService == null) {
			scProductEntryLocalService = SCProductEntryLocalServiceFactory.getImpl();
		}

		if (scProductEntryService == null) {
			scProductEntryService = SCProductEntryServiceFactory.getImpl();
		}

		if (scProductEntryPersistence == null) {
			scProductEntryPersistence = SCProductEntryUtil.getPersistence();
		}

		if (wikiNodeLocalService == null) {
			wikiNodeLocalService = WikiNodeLocalServiceFactory.getImpl();
		}

		if (wikiNodeService == null) {
			wikiNodeService = WikiNodeServiceFactory.getImpl();
		}

		if (wikiNodePersistence == null) {
			wikiNodePersistence = WikiNodeUtil.getPersistence();
		}
	}

	protected AccountLocalService accountLocalService;
	protected AccountService accountService;
	protected AccountPersistence accountPersistence;
	protected ActivityTrackerLocalService activityTrackerLocalService;
	protected ActivityTrackerPersistence activityTrackerPersistence;
	protected ActivityTrackerFinder activityTrackerFinder;
	protected AddressLocalService addressLocalService;
	protected AddressService addressService;
	protected AddressPersistence addressPersistence;
	protected ClassNameLocalService classNameLocalService;
	protected ClassNameService classNameService;
	protected ClassNamePersistence classNamePersistence;
	protected CompanyLocalService companyLocalService;
	protected CompanyService companyService;
	protected CompanyPersistence companyPersistence;
	protected ContactLocalService contactLocalService;
	protected ContactService contactService;
	protected ContactPersistence contactPersistence;
	protected CountryService countryService;
	protected CountryPersistence countryPersistence;
	protected EmailAddressLocalService emailAddressLocalService;
	protected EmailAddressService emailAddressService;
	protected EmailAddressPersistence emailAddressPersistence;
	protected GroupLocalService groupLocalService;
	protected GroupPersistence groupPersistence;
	protected GroupFinder groupFinder;
	protected ImageLocalService imageLocalService;
	protected ImagePersistence imagePersistence;
	protected LayoutLocalService layoutLocalService;
	protected LayoutService layoutService;
	protected LayoutPersistence layoutPersistence;
	protected LayoutFinder layoutFinder;
	protected LayoutSetLocalService layoutSetLocalService;
	protected LayoutSetService layoutSetService;
	protected LayoutSetPersistence layoutSetPersistence;
	protected ListTypeService listTypeService;
	protected ListTypePersistence listTypePersistence;
	protected MembershipRequestLocalService membershipRequestLocalService;
	protected MembershipRequestService membershipRequestService;
	protected MembershipRequestPersistence membershipRequestPersistence;
	protected OrganizationLocalService organizationLocalService;
	protected OrganizationService organizationService;
	protected OrganizationPersistence organizationPersistence;
	protected OrganizationFinder organizationFinder;
	protected OrgGroupPermissionPersistence orgGroupPermissionPersistence;
	protected OrgGroupPermissionFinder orgGroupPermissionFinder;
	protected OrgGroupRolePersistence orgGroupRolePersistence;
	protected OrgLaborLocalService orgLaborLocalService;
	protected OrgLaborService orgLaborService;
	protected OrgLaborPersistence orgLaborPersistence;
	protected PasswordPolicyLocalService passwordPolicyLocalService;
	protected PasswordPolicyService passwordPolicyService;
	protected PasswordPolicyPersistence passwordPolicyPersistence;
	protected PasswordPolicyFinder passwordPolicyFinder;
	protected PasswordPolicyRelLocalService passwordPolicyRelLocalService;
	protected PasswordPolicyRelPersistence passwordPolicyRelPersistence;
	protected PasswordTrackerLocalService passwordTrackerLocalService;
	protected PasswordTrackerPersistence passwordTrackerPersistence;
	protected PermissionLocalService permissionLocalService;
	protected PermissionService permissionService;
	protected PermissionPersistence permissionPersistence;
	protected PermissionFinder permissionFinder;
	protected PermissionUserFinder permissionUserFinder;
	protected PhoneLocalService phoneLocalService;
	protected PhoneService phoneService;
	protected PhonePersistence phonePersistence;
	protected PortalService portalService;
	protected PluginSettingLocalService pluginSettingLocalService;
	protected PluginSettingService pluginSettingService;
	protected PluginSettingPersistence pluginSettingPersistence;
	protected PortletLocalService portletLocalService;
	protected PortletService portletService;
	protected PortletPersistence portletPersistence;
	protected PortletPreferencesLocalService portletPreferencesLocalService;
	protected PortletPreferencesPersistence portletPreferencesPersistence;
	protected PortletPreferencesFinder portletPreferencesFinder;
	protected RegionService regionService;
	protected RegionPersistence regionPersistence;
	protected ReleaseLocalService releaseLocalService;
	protected ReleasePersistence releasePersistence;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected ResourceCodeLocalService resourceCodeLocalService;
	protected ResourceCodePersistence resourceCodePersistence;
	protected RoleLocalService roleLocalService;
	protected RoleService roleService;
	protected RolePersistence rolePersistence;
	protected RoleFinder roleFinder;
	protected ServiceComponentLocalService serviceComponentLocalService;
	protected ServiceComponentPersistence serviceComponentPersistence;
	protected SubscriptionLocalService subscriptionLocalService;
	protected SubscriptionPersistence subscriptionPersistence;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
	protected UserGroupLocalService userGroupLocalService;
	protected UserGroupService userGroupService;
	protected UserGroupPersistence userGroupPersistence;
	protected UserGroupFinder userGroupFinder;
	protected UserGroupRoleLocalService userGroupRoleLocalService;
	protected UserGroupRoleService userGroupRoleService;
	protected UserGroupRolePersistence userGroupRolePersistence;
	protected UserIdMapperLocalService userIdMapperLocalService;
	protected UserIdMapperPersistence userIdMapperPersistence;
	protected UserTrackerLocalService userTrackerLocalService;
	protected UserTrackerPersistence userTrackerPersistence;
	protected UserTrackerPathLocalService userTrackerPathLocalService;
	protected UserTrackerPathPersistence userTrackerPathPersistence;
	protected WebDAVPropsLocalService webDAVPropsLocalService;
	protected WebDAVPropsPersistence webDAVPropsPersistence;
	protected WebsiteLocalService websiteLocalService;
	protected WebsiteService websiteService;
	protected WebsitePersistence websitePersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected BlogsEntryLocalService blogsEntryLocalService;
	protected BlogsEntryService blogsEntryService;
	protected BlogsEntryPersistence blogsEntryPersistence;
	protected BlogsEntryFinder blogsEntryFinder;
	protected BlogsStatsUserLocalService blogsStatsUserLocalService;
	protected BlogsStatsUserPersistence blogsStatsUserPersistence;
	protected BlogsStatsUserFinder blogsStatsUserFinder;
	protected BookmarksFolderLocalService bookmarksFolderLocalService;
	protected BookmarksFolderService bookmarksFolderService;
	protected BookmarksFolderPersistence bookmarksFolderPersistence;
	protected CalEventLocalService calEventLocalService;
	protected CalEventService calEventService;
	protected CalEventPersistence calEventPersistence;
	protected CalEventFinder calEventFinder;
	protected DLFolderLocalService dlFolderLocalService;
	protected DLFolderService dlFolderService;
	protected DLFolderPersistence dlFolderPersistence;
	protected IGFolderLocalService igFolderLocalService;
	protected IGFolderService igFolderService;
	protected IGFolderPersistence igFolderPersistence;
	protected JournalArticleLocalService journalArticleLocalService;
	protected JournalArticleService journalArticleService;
	protected JournalArticlePersistence journalArticlePersistence;
	protected JournalArticleFinder journalArticleFinder;
	protected JournalStructureLocalService journalStructureLocalService;
	protected JournalStructureService journalStructureService;
	protected JournalStructurePersistence journalStructurePersistence;
	protected JournalStructureFinder journalStructureFinder;
	protected JournalTemplateLocalService journalTemplateLocalService;
	protected JournalTemplateService journalTemplateService;
	protected JournalTemplatePersistence journalTemplatePersistence;
	protected JournalTemplateFinder journalTemplateFinder;
	protected MBBanLocalService mbBanLocalService;
	protected MBBanService mbBanService;
	protected MBBanPersistence mbBanPersistence;
	protected MBCategoryLocalService mbCategoryLocalService;
	protected MBCategoryService mbCategoryService;
	protected MBCategoryPersistence mbCategoryPersistence;
	protected MBCategoryFinder mbCategoryFinder;
	protected MBStatsUserLocalService mbStatsUserLocalService;
	protected MBStatsUserPersistence mbStatsUserPersistence;
	protected PollsQuestionLocalService pollsQuestionLocalService;
	protected PollsQuestionService pollsQuestionService;
	protected PollsQuestionPersistence pollsQuestionPersistence;
	protected ShoppingCartLocalService shoppingCartLocalService;
	protected ShoppingCartPersistence shoppingCartPersistence;
	protected ShoppingCategoryLocalService shoppingCategoryLocalService;
	protected ShoppingCategoryService shoppingCategoryService;
	protected ShoppingCategoryPersistence shoppingCategoryPersistence;
	protected ShoppingCouponLocalService shoppingCouponLocalService;
	protected ShoppingCouponService shoppingCouponService;
	protected ShoppingCouponPersistence shoppingCouponPersistence;
	protected ShoppingCouponFinder shoppingCouponFinder;
	protected ShoppingOrderLocalService shoppingOrderLocalService;
	protected ShoppingOrderService shoppingOrderService;
	protected ShoppingOrderPersistence shoppingOrderPersistence;
	protected ShoppingOrderFinder shoppingOrderFinder;
	protected SCFrameworkVersionLocalService scFrameworkVersionLocalService;
	protected SCFrameworkVersionService scFrameworkVersionService;
	protected SCFrameworkVersionPersistence scFrameworkVersionPersistence;
	protected SCProductEntryLocalService scProductEntryLocalService;
	protected SCProductEntryService scProductEntryService;
	protected SCProductEntryPersistence scProductEntryPersistence;
	protected WikiNodeLocalService wikiNodeLocalService;
	protected WikiNodeService wikiNodeService;
	protected WikiNodePersistence wikiNodePersistence;
}