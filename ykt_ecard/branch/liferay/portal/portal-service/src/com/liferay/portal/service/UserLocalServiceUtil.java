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
 * <a href="UserLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 * 
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 * 
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.UserLocalService</code> bean. The static
 * methods of this class calls the same methods of the bean instance. It's
 * convenient to be able to just write one line to call a method on a bean
 * instead of writing a lookup call and a method call.
 * </p>
 * 
 * <p>
 * <code>com.liferay.portal.service.UserLocalServiceFactory</code> is
 * responsible for the lookup of the bean.
 * </p>
 * 
 * @author Brian Wing Shun Chan
 * 
 * @see com.liferay.portal.service.UserLocalService
 * @see com.liferay.portal.service.UserLocalServiceFactory
 * 
 */
public class UserLocalServiceUtil {
	public static com.liferay.portal.model.User addUser(
			com.liferay.portal.model.User model)
			throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.addUser(model);
	}

	public static java.util.List dynamicQuery(
			com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
			throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
			com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
			int begin, int end) throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.User updateUser(
			com.liferay.portal.model.User model)
			throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateUser(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
			com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
			com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
			com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
			com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
			com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
			com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
			com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
			com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
			com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
			com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
			com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
			com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
			com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
			com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
			com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
			com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
			com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
			com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
			com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
			com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
			com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
			com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
			com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
			com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
			com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
			com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
			com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
			com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
			com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
			com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
			com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
			com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
			com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
			com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
			com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
			com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
			com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
			com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
			com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
			com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
			com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
			com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
			com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
			com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
			com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserFinder();
	}

	public static void setUserFinder(
			com.liferay.portal.service.persistence.UserFinder userFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
			com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
			com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
			com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
			com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
			com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
			com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
			com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
			com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setWebsitePersistence(websitePersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getBlogsStatsUserPersistence();
	}

	public static void setBlogsStatsUserPersistence(
			com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence blogsStatsUserPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService
				.setBlogsStatsUserPersistence(blogsStatsUserPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder getBlogsStatsUserFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getBlogsStatsUserFinder();
	}

	public static void setBlogsStatsUserFinder(
			com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder blogsStatsUserFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setBlogsStatsUserFinder(blogsStatsUserFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence getDLFileRankPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getDLFileRankPersistence();
	}

	public static void setDLFileRankPersistence(
			com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence dlFileRankPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setDLFileRankPersistence(dlFileRankPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder getDLFileRankFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getDLFileRankFinder();
	}

	public static void setDLFileRankFinder(
			com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder dlFileRankFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setDLFileRankFinder(dlFileRankFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBBanPersistence getMBBanPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getMBBanPersistence();
	}

	public static void setMBBanPersistence(
			com.liferay.portlet.messageboards.service.persistence.MBBanPersistence mbBanPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setMBBanPersistence(mbBanPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence getMBMessageFlagPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getMBMessageFlagPersistence();
	}

	public static void setMBMessageFlagPersistence(
			com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence mbMessageFlagPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setMBMessageFlagPersistence(mbMessageFlagPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder getMBMessageFlagFinder() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getMBMessageFlagFinder();
	}

	public static void setMBMessageFlagFinder(
			com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder mbMessageFlagFinder) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setMBMessageFlagFinder(mbMessageFlagFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence getMBStatsUserPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getMBStatsUserPersistence();
	}

	public static void setMBStatsUserPersistence(
			com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence mbStatsUserPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setMBStatsUserPersistence(mbStatsUserPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
			com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static void afterPropertiesSet() {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.afterPropertiesSet();
	}

	public static void addGroupUsers(long groupId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.addGroupUsers(groupId, userIds);
	}

	public static void addOrganizationUsers(long organizationId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.addOrganizationUsers(organizationId, userIds);
	}

	public static void addPasswordPolicyUsers(long passwordPolicyId,
			long[] userIds) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.addPasswordPolicyUsers(passwordPolicyId, userIds);
	}

	public static void addRoleUsers(long roleId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.addRoleUsers(roleId, userIds);
	}

	public static void addUserGroupUsers(long userGroupId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.addUserGroupUsers(userGroupId, userIds);
	}

	public static com.liferay.portal.model.User addUser(long creatorUserId,
			long companyId, boolean autoPassword, java.lang.String password1,
			java.lang.String password2, boolean autoScreenName,
			java.lang.String screenName, java.lang.String emailAddress,
			java.util.Locale locale, java.lang.String firstName,
			java.lang.String middleName, java.lang.String lastName,
			int prefixId, int suffixId, boolean male, int birthdayMonth,
			int birthdayDay, int birthdayYear, java.lang.String jobTitle,
			long[] organizationIds, boolean sendEmail)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.addUser(creatorUserId, companyId, autoPassword,
				password1, password2, autoScreenName, screenName, emailAddress,
				locale, firstName, middleName, lastName, prefixId, suffixId,
				male, birthdayMonth, birthdayDay, birthdayYear, jobTitle,
				organizationIds, sendEmail);
	}

	public static int authenticateByEmailAddress(long companyId,
			java.lang.String emailAddress, java.lang.String password,
			java.util.Map headerMap, java.util.Map parameterMap)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateByEmailAddress(companyId,
				emailAddress, password, headerMap, parameterMap);
	}

	public static int authenticateByScreenName(long companyId,
			java.lang.String screenName, java.lang.String password,
			java.util.Map headerMap, java.util.Map parameterMap)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateByScreenName(companyId, screenName,
				password, headerMap, parameterMap);
	}

	public static int authenticateByUserId(long companyId, long userId,
			java.lang.String password, java.util.Map headerMap,
			java.util.Map parameterMap)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateByUserId(companyId, userId,
				password, headerMap, parameterMap);
	}

	public static int authenticateByEmailAddress(long companyId,
			java.lang.String emailAddress)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateByEmailAddress(companyId,
				emailAddress);
	}

	public static int authenticateByScreenName(long companyId,
			java.lang.String screenName)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateByScreenName(companyId, screenName);
	}

	public static int authenticateByUserId(long companyId, long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateByUserId(companyId, userId);
	}

	public static boolean authenticateForJAAS(long userId,
			java.lang.String encPwd) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.authenticateForJAAS(userId, encPwd);
	}

	public static void checkLockout(com.liferay.portal.model.User user)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.checkLockout(user);
	}

	public static void checkLoginFailure(com.liferay.portal.model.User user)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.checkLoginFailure(user);
	}

	public static void checkLoginFailureByEmailAddress(long companyId,
			java.lang.String emailAddress)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.checkLoginFailureByEmailAddress(companyId,
				emailAddress);
	}

	public static void checkLoginFailureById(long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.checkLoginFailureById(userId);
	}

	public static void checkLoginFailureByScreenName(long companyId,
			java.lang.String screenName)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.checkLoginFailureByScreenName(companyId, screenName);
	}

	public static void checkPasswordExpired(com.liferay.portal.model.User user)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.checkPasswordExpired(user);
	}

	public static void clearOrganizationUsers(long organizationId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.clearOrganizationUsers(organizationId);
	}

	public static void clearUserGroupUsers(long userGroupId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.clearUserGroupUsers(userGroupId);
	}

	public static com.liferay.portal.kernel.util.KeyValuePair decryptUserId(
			long companyId, java.lang.String name, java.lang.String password)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.decryptUserId(companyId, name, password);
	}

	public static void deletePasswordPolicyUser(long passwordPolicyId,
			long userId) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.deletePasswordPolicyUser(passwordPolicyId, userId);
	}

	public static void deleteRoleUser(long roleId, long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.deleteRoleUser(roleId, userId);
	}

	public static void deleteUser(long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.deleteUser(userId);
	}

	public static java.lang.String encryptUserId(java.lang.String name)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.encryptUserId(name);
	}

	public static com.liferay.portal.model.User getDefaultUser(long companyId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getDefaultUser(companyId);
	}

	public static long getDefaultUserId(long companyId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getDefaultUserId(companyId);
	}

	public static java.util.List getGroupUsers(long groupId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getGroupUsers(groupId);
	}

	public static java.util.List getOrganizationUsers(long organizationId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getOrganizationUsers(organizationId);
	}

	public static java.util.List getPermissionUsers(long companyId,
			long groupId, java.lang.String name, java.lang.String primKey,
			java.lang.String actionId, java.lang.String firstName,
			java.lang.String middleName, java.lang.String lastName,
			java.lang.String emailAddress, boolean andOperator, int begin,
			int end) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPermissionUsers(companyId, groupId, name,
				primKey, actionId, firstName, middleName, lastName,
				emailAddress, andOperator, begin, end);
	}

	public static int getPermissionUsersCount(long companyId, long groupId,
			java.lang.String name, java.lang.String primKey,
			java.lang.String actionId, java.lang.String firstName,
			java.lang.String middleName, java.lang.String lastName,
			java.lang.String emailAddress, boolean andOperator)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getPermissionUsersCount(companyId, groupId,
				name, primKey, actionId, firstName, middleName, lastName,
				emailAddress, andOperator);
	}

	public static java.util.List getRoleUsers(long roleId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getRoleUsers(roleId);
	}

	public static java.util.List getUserGroupUsers(long userGroupId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserGroupUsers(userGroupId);
	}

	public static com.liferay.portal.model.User getUserByContactId(
			long contactId) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserByContactId(contactId);
	}

	public static com.liferay.portal.model.User getUserByEmailAddress(
			long companyId, java.lang.String emailAddress)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserByEmailAddress(companyId, emailAddress);
	}

	public static com.liferay.portal.model.User getUserById(long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserById(userId);
	}

	public static com.liferay.portal.model.User getUserById(long companyId,
			long userId) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserById(companyId, userId);
	}

	public static com.liferay.portal.model.User getUserByPortraitId(
			long portraitId) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserByPortraitId(portraitId);
	}

	public static com.liferay.portal.model.User getUserByScreenName(
			long companyId, java.lang.String screenName)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserByScreenName(companyId, screenName);
	}

	public static long getUserIdByEmailAddress(long companyId,
			java.lang.String emailAddress)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService
				.getUserIdByEmailAddress(companyId, emailAddress);
	}

	public static long getUserIdByScreenName(long companyId,
			java.lang.String screenName)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.getUserIdByScreenName(companyId, screenName);
	}

	public static boolean hasGroupUser(long groupId, long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.hasGroupUser(groupId, userId);
	}

	public static boolean hasOrganizationUser(long organizationId, long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.hasOrganizationUser(organizationId, userId);
	}

	public static boolean hasPasswordPolicyUser(long passwordPolicyId,
			long userId) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.hasPasswordPolicyUser(passwordPolicyId, userId);
	}

	public static boolean hasRoleUser(long roleId, long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.hasRoleUser(roleId, userId);
	}

	public static boolean hasUserGroupUser(long userGroupId, long userId)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.hasUserGroupUser(userGroupId, userId);
	}

	public static boolean isPasswordExpired(com.liferay.portal.model.User user)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.isPasswordExpired(user);
	}

	public static boolean isPasswordExpiringSoon(
			com.liferay.portal.model.User user)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.isPasswordExpiringSoon(user);
	}

	public static java.util.List search(long companyId,
			java.lang.String keywords, java.lang.Boolean active,
			java.util.LinkedHashMap params, int begin, int end,
			com.liferay.portal.kernel.util.OrderByComparator obc)
			throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.search(companyId, keywords, active, params,
				begin, end, obc);
	}

	public static java.util.List search(long companyId,
			java.lang.String firstName, java.lang.String middleName,
			java.lang.String lastName, java.lang.String screenName,
			java.lang.String emailAddress, java.lang.Boolean active,
			java.util.LinkedHashMap params, boolean andSearch, int begin,
			int end, com.liferay.portal.kernel.util.OrderByComparator obc)
			throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.search(companyId, firstName, middleName,
				lastName, screenName, emailAddress, active, params, andSearch,
				begin, end, obc);
	}

	public static int searchCount(long companyId, java.lang.String keywords,
			java.lang.Boolean active, java.util.LinkedHashMap params)
			throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService
				.searchCount(companyId, keywords, active, params);
	}

	public static int searchCount(long companyId, java.lang.String firstName,
			java.lang.String middleName, java.lang.String lastName,
			java.lang.String screenName, java.lang.String emailAddress,
			java.lang.Boolean active, java.util.LinkedHashMap params,
			boolean andSearch) throws com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.searchCount(companyId, firstName, middleName,
				lastName, screenName, emailAddress, active, params, andSearch);
	}

	public static void sendPassword(long companyId,
			java.lang.String emailAddress, java.lang.String remoteAddr,
			java.lang.String remoteHost, java.lang.String userAgent)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.sendPassword(companyId, emailAddress, remoteAddr,
				remoteHost, userAgent);
	}

	public static void setRoleUsers(long roleId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setRoleUsers(roleId, userIds);
	}

	public static void setUserGroupUsers(long userGroupId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.setUserGroupUsers(userGroupId, userIds);
	}

	public static void unsetGroupUsers(long groupId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.unsetGroupUsers(groupId, userIds);
	}

	public static void unsetOrganizationUsers(long organizationId,
			long[] userIds) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.unsetOrganizationUsers(organizationId, userIds);
	}

	public static void unsetPasswordPolicyUsers(long passwordPolicyId,
			long[] userIds) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.unsetPasswordPolicyUsers(passwordPolicyId, userIds);
	}

	public static void unsetRoleUsers(long roleId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.unsetRoleUsers(roleId, userIds);
	}

	public static void unsetUserGroupUsers(long userGroupId, long[] userIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.unsetUserGroupUsers(userGroupId, userIds);
	}

	public static com.liferay.portal.model.User updateActive(long userId,
			boolean active) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateActive(userId, active);
	}

	public static com.liferay.portal.model.User updateAgreedToTermsOfUse(
			long userId, boolean agreedToTermsOfUse)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateAgreedToTermsOfUse(userId,
				agreedToTermsOfUse);
	}

	public static com.liferay.portal.model.User updateCreateDate(long userId,
			java.util.Date createDate)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateCreateDate(userId, createDate);
	}

	public static com.liferay.portal.model.User updateLastLogin(long userId,
			java.lang.String loginIP)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateLastLogin(userId, loginIP);
	}

	public static com.liferay.portal.model.User updateLockout(
			com.liferay.portal.model.User user, boolean lockout)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateLockout(user, lockout);
	}

	public static com.liferay.portal.model.User updateLockoutByEmailAddress(
			long companyId, java.lang.String emailAddress, boolean lockout)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateLockoutByEmailAddress(companyId,
				emailAddress, lockout);
	}

	public static com.liferay.portal.model.User updateLockoutById(long userId,
			boolean lockout) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateLockoutById(userId, lockout);
	}

	public static com.liferay.portal.model.User updateLockoutByScreenName(
			long companyId, java.lang.String screenName, boolean lockout)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateLockoutByScreenName(companyId,
				screenName, lockout);
	}

	public static com.liferay.portal.model.User updateModifiedDate(long userId,
			java.util.Date modifiedDate)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateModifiedDate(userId, modifiedDate);
	}

	public static void updateOrganizations(long userId,
			long[] newOrganizationIds)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.updateOrganizations(userId, newOrganizationIds);
	}

	public static com.liferay.portal.model.User updatePassword(long userId,
			java.lang.String password1, java.lang.String password2,
			boolean passwordReset) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updatePassword(userId, password1, password2,
				passwordReset);
	}

	public static com.liferay.portal.model.User updatePassword(long userId,
			java.lang.String password1, java.lang.String password2,
			boolean passwordReset, boolean silentUpdate)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updatePassword(userId, password1, password2,
				passwordReset, silentUpdate);
	}

	public static com.liferay.portal.model.User updatePasswordManually(
			long userId, java.lang.String password, boolean passwordEncrypted,
			boolean passwordReset, java.util.Date passwordModifiedDate)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updatePasswordManually(userId, password,
				passwordEncrypted, passwordReset, passwordModifiedDate);
	}

	public static void updatePasswordReset(long userId, boolean passwordReset)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.updatePasswordReset(userId, passwordReset);
	}

	public static void updatePortrait(long userId, byte[] bytes)
			throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		userLocalService.updatePortrait(userId, bytes);
	}

	public static com.liferay.portal.model.User updateUser(long userId,
			java.lang.String oldPassword, boolean passwordReset,
			java.lang.String screenName, java.lang.String emailAddress,
			java.lang.String languageId, java.lang.String timeZoneId,
			java.lang.String greeting, java.lang.String comments,
			java.lang.String firstName, java.lang.String middleName,
			java.lang.String lastName, int prefixId, int suffixId,
			boolean male, int birthdayMonth, int birthdayDay, int birthdayYear,
			java.lang.String smsSn, java.lang.String aimSn,
			java.lang.String icqSn, java.lang.String jabberSn,
			java.lang.String msnSn, java.lang.String skypeSn,
			java.lang.String ymSn, java.lang.String jobTitle,
			long[] organizationIds) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateUser(userId, oldPassword, passwordReset,
				screenName, emailAddress, languageId, timeZoneId, greeting,
				comments, firstName, middleName, lastName, prefixId, suffixId,
				male, birthdayMonth, birthdayDay, birthdayYear, smsSn, aimSn,
				icqSn, jabberSn, msnSn, skypeSn, ymSn, jobTitle,
				organizationIds);
	}

	public static com.liferay.portal.model.User updateUser(long userId,
			java.lang.String oldPassword, java.lang.String newPassword1,
			java.lang.String newPassword2, boolean passwordReset,
			java.lang.String screenName, java.lang.String emailAddress,
			java.lang.String languageId, java.lang.String timeZoneId,
			java.lang.String greeting, java.lang.String comments,
			java.lang.String firstName, java.lang.String middleName,
			java.lang.String lastName, int prefixId, int suffixId,
			boolean male, int birthdayMonth, int birthdayDay, int birthdayYear,
			java.lang.String smsSn, java.lang.String aimSn,
			java.lang.String icqSn, java.lang.String jabberSn,
			java.lang.String msnSn, java.lang.String skypeSn,
			java.lang.String ymSn, java.lang.String jobTitle,
			long[] organizationIds) throws com.liferay.portal.PortalException,
			com.liferay.portal.SystemException {
		UserLocalService userLocalService = UserLocalServiceFactory
				.getService();

		return userLocalService.updateUser(userId, oldPassword, newPassword1,
				newPassword2, passwordReset, screenName, emailAddress,
				languageId, timeZoneId, greeting, comments, firstName,
				middleName, lastName, prefixId, suffixId, male, birthdayMonth,
				birthdayDay, birthdayYear, smsSn, aimSn, icqSn, jabberSn,
				msnSn, skypeSn, ymSn, jobTitle, organizationIds);
	}
}