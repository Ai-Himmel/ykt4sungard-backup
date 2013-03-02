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

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.model.WebDAVProps;
import com.liferay.portal.model.impl.WebDAVPropsImpl;
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
import com.liferay.portal.service.GroupServiceFactory;
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
import com.liferay.portal.service.WebsiteLocalService;
import com.liferay.portal.service.WebsiteLocalServiceFactory;
import com.liferay.portal.service.WebsiteService;
import com.liferay.portal.service.WebsiteServiceFactory;
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

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="WebDAVPropsLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class WebDAVPropsLocalServiceBaseImpl
	implements WebDAVPropsLocalService, InitializingBean {
	public WebDAVProps addWebDAVProps(WebDAVProps model)
		throws SystemException {
		WebDAVProps webDAVProps = new WebDAVPropsImpl();

		webDAVProps.setNew(true);

		webDAVProps.setWebDavPropsId(model.getWebDavPropsId());
		webDAVProps.setCompanyId(model.getCompanyId());
		webDAVProps.setCreateDate(model.getCreateDate());
		webDAVProps.setModifiedDate(model.getModifiedDate());
		webDAVProps.setClassNameId(model.getClassNameId());
		webDAVProps.setClassPK(model.getClassPK());
		webDAVProps.setProps(model.getProps());

		return webDAVPropsPersistence.update(webDAVProps);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return webDAVPropsPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return webDAVPropsPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public WebDAVProps updateWebDAVProps(WebDAVProps model)
		throws SystemException {
		WebDAVProps webDAVProps = new WebDAVPropsImpl();

		webDAVProps.setNew(false);

		webDAVProps.setWebDavPropsId(model.getWebDavPropsId());
		webDAVProps.setCompanyId(model.getCompanyId());
		webDAVProps.setCreateDate(model.getCreateDate());
		webDAVProps.setModifiedDate(model.getModifiedDate());
		webDAVProps.setClassNameId(model.getClassNameId());
		webDAVProps.setClassPK(model.getClassPK());
		webDAVProps.setProps(model.getProps());

		return webDAVPropsPersistence.update(webDAVProps);
	}

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

	public GroupService getGroupService() {
		return groupService;
	}

	public void setGroupService(GroupService groupService) {
		this.groupService = groupService;
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

		if (groupService == null) {
			groupService = GroupServiceFactory.getImpl();
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
	protected GroupService groupService;
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
	protected WebDAVPropsPersistence webDAVPropsPersistence;
	protected WebsiteLocalService websiteLocalService;
	protected WebsiteService websiteService;
	protected WebsitePersistence websitePersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
}