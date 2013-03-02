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

package com.liferay.portal.service;


/**
 * <a href="AccountLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.AccountLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.AccountLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.AccountLocalService
 * @see com.liferay.portal.service.AccountLocalServiceFactory
 *
 */
public class AccountLocalServiceUtil {
	public static com.liferay.portal.model.Account addAccount(
		com.liferay.portal.model.Account model)
		throws com.liferay.portal.SystemException {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.addAccount(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Account updateAccount(
		com.liferay.portal.model.Account model)
		throws com.liferay.portal.SystemException {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.updateAccount(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		accountLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Account getAccount(long accountId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		AccountLocalService accountLocalService = AccountLocalServiceFactory.getService();

		return accountLocalService.getAccount(accountId);
	}
}