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
 * <a href="RoleLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.RoleLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.RoleLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.RoleLocalService
 * @see com.liferay.portal.service.RoleLocalServiceFactory
 *
 */
public class RoleLocalServiceUtil {
	public static com.liferay.portal.model.Role addRole(
		com.liferay.portal.model.Role model)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.addRole(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Role updateRole(
		com.liferay.portal.model.Role model)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.updateRole(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Role addRole(long userId,
		long companyId, java.lang.String name, java.lang.String description,
		int type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.addRole(userId, companyId, name, description,
			type);
	}

	public static com.liferay.portal.model.Role addRole(long userId,
		long companyId, java.lang.String name, java.lang.String description,
		int type, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.addRole(userId, companyId, name, description,
			type, className, classPK);
	}

	public static void addUserRoles(long userId, long[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.addUserRoles(userId, roleIds);
	}

	public static void checkSystemRoles(long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.checkSystemRoles(companyId);
	}

	public static void deleteRole(long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.deleteRole(roleId);
	}

	public static com.liferay.portal.model.Role getGroupRole(long companyId,
		long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getGroupRole(companyId, groupId);
	}

	public static java.util.List getGroupRoles(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getGroupRoles(groupId);
	}

	public static java.util.Map getResourceRoles(long companyId,
		java.lang.String name, int scope, java.lang.String primKey)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getResourceRoles(companyId, name, scope, primKey);
	}

	public static com.liferay.portal.model.Role getRole(long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getRole(roleId);
	}

	public static com.liferay.portal.model.Role getRole(long companyId,
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getRole(companyId, name);
	}

	public static java.util.List getUserGroupRoles(long userId, long groupId)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserGroupRoles(userId, groupId);
	}

	public static java.util.List getUserRelatedRoles(long userId, long groupId)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserRelatedRoles(userId, groupId);
	}

	public static java.util.List getUserRelatedRoles(long userId,
		long[] groupIds) throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserRelatedRoles(userId, groupIds);
	}

	public static java.util.List getUserRelatedRoles(long userId,
		java.util.List groups) throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserRelatedRoles(userId, groups);
	}

	public static java.util.List getUserRoles(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.getUserRoles(userId);
	}

	public static boolean hasUserRole(long userId, long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.hasUserRole(userId, roleId);
	}

	public static boolean hasUserRole(long userId, long companyId,
		java.lang.String name, boolean inherited)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.hasUserRole(userId, companyId, name, inherited);
	}

	public static boolean hasUserRoles(long userId, long companyId,
		java.lang.String[] names, boolean inherited)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.hasUserRoles(userId, companyId, names, inherited);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String description, java.lang.Integer type, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.search(companyId, name, description, type,
			begin, end, obc);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String description, java.lang.Integer type,
		java.util.LinkedHashMap params, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.search(companyId, name, description, type,
			params, begin, end, obc);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.lang.Integer type)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.searchCount(companyId, name, description, type);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.lang.Integer type,
		java.util.LinkedHashMap params)
		throws com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.searchCount(companyId, name, description, type,
			params);
	}

	public static void setUserRoles(long userId, long[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.setUserRoles(userId, roleIds);
	}

	public static void unsetUserRoles(long userId, long[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		roleLocalService.unsetUserRoles(userId, roleIds);
	}

	public static com.liferay.portal.model.Role updateRole(long roleId,
		java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RoleLocalService roleLocalService = RoleLocalServiceFactory.getService();

		return roleLocalService.updateRole(roleId, name, description);
	}
}