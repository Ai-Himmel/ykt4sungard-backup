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
 * <a href="UserGroupLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.UserGroupLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.UserGroupLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.UserGroupLocalService
 * @see com.liferay.portal.service.UserGroupLocalServiceFactory
 *
 */
public class UserGroupLocalServiceUtil {
	public static com.liferay.portal.model.UserGroup addUserGroup(
		com.liferay.portal.model.UserGroup model)
		throws com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.addUserGroup(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.UserGroup updateUserGroup(
		com.liferay.portal.model.UserGroup model)
		throws com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.updateUserGroup(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.afterPropertiesSet();
	}

	public static void addGroupUserGroups(long groupId, long[] userGroupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.addGroupUserGroups(groupId, userGroupIds);
	}

	public static com.liferay.portal.model.UserGroup addUserGroup(long userId,
		long companyId, java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.addUserGroup(userId, companyId, name,
			description);
	}

	public static void clearUserUserGroups(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.clearUserUserGroups(userId);
	}

	public static void deleteUserGroup(long userGroupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.deleteUserGroup(userGroupId);
	}

	public static com.liferay.portal.model.UserGroup getUserGroup(
		long userGroupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserGroup(userGroupId);
	}

	public static com.liferay.portal.model.UserGroup getUserGroup(
		long companyId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserGroup(companyId, name);
	}

	public static java.util.List getUserGroups(long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserGroups(companyId);
	}

	public static java.util.List getUserUserGroups(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.getUserUserGroups(userId);
	}

	public static boolean hasGroupUserGroup(long groupId, long userGroupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.hasGroupUserGroup(groupId, userGroupId);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String description, java.util.LinkedHashMap params,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.search(companyId, name, description,
			params, begin, end, obc);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.util.LinkedHashMap params)
		throws com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.searchCount(companyId, name, description,
			params);
	}

	public static void unsetGroupUserGroups(long groupId, long[] userGroupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		userGroupLocalService.unsetGroupUserGroups(groupId, userGroupIds);
	}

	public static com.liferay.portal.model.UserGroup updateUserGroup(
		long companyId, long userGroupId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserGroupLocalService userGroupLocalService = UserGroupLocalServiceFactory.getService();

		return userGroupLocalService.updateUserGroup(companyId, userGroupId,
			name, description);
	}
}