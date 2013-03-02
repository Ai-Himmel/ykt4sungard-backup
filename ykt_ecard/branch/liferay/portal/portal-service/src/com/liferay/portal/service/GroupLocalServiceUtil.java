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
 * <a href="GroupLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.GroupLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.GroupLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.GroupLocalService
 * @see com.liferay.portal.service.GroupLocalServiceFactory
 *
 */
public class GroupLocalServiceUtil {
	public static com.liferay.portal.model.Group addGroup(
		com.liferay.portal.model.Group model)
		throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.addGroup(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Group updateGroup(
		com.liferay.portal.model.Group model)
		throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.updateGroup(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setWebsitePersistence(websitePersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getBlogsEntryPersistence();
	}

	public static void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setBlogsEntryPersistence(blogsEntryPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getBlogsEntryFinder();
	}

	public static void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setBlogsEntryFinder(blogsEntryFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getBlogsStatsUserPersistence();
	}

	public static void setBlogsStatsUserPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence blogsStatsUserPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setBlogsStatsUserPersistence(blogsStatsUserPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder getBlogsStatsUserFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getBlogsStatsUserFinder();
	}

	public static void setBlogsStatsUserFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder blogsStatsUserFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setBlogsStatsUserFinder(blogsStatsUserFinder);
	}

	public static com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence getBookmarksFolderPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getBookmarksFolderPersistence();
	}

	public static void setBookmarksFolderPersistence(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence bookmarksFolderPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setBookmarksFolderPersistence(bookmarksFolderPersistence);
	}

	public static com.liferay.portlet.calendar.service.persistence.CalEventPersistence getCalEventPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getCalEventPersistence();
	}

	public static void setCalEventPersistence(
		com.liferay.portlet.calendar.service.persistence.CalEventPersistence calEventPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setCalEventPersistence(calEventPersistence);
	}

	public static com.liferay.portlet.calendar.service.persistence.CalEventFinder getCalEventFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getCalEventFinder();
	}

	public static void setCalEventFinder(
		com.liferay.portlet.calendar.service.persistence.CalEventFinder calEventFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setCalEventFinder(calEventFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getDLFolderPersistence();
	}

	public static void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setDLFolderPersistence(dlFolderPersistence);
	}

	public static com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistence getIGFolderPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getIGFolderPersistence();
	}

	public static void setIGFolderPersistence(
		com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistence igFolderPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setIGFolderPersistence(igFolderPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBBanPersistence getMBBanPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getMBBanPersistence();
	}

	public static void setMBBanPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBBanPersistence mbBanPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setMBBanPersistence(mbBanPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence getMBCategoryPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getMBCategoryPersistence();
	}

	public static void setMBCategoryPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence mbCategoryPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setMBCategoryPersistence(mbCategoryPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder getMBCategoryFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getMBCategoryFinder();
	}

	public static void setMBCategoryFinder(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder mbCategoryFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setMBCategoryFinder(mbCategoryFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence getMBStatsUserPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getMBStatsUserPersistence();
	}

	public static void setMBStatsUserPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence mbStatsUserPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setMBStatsUserPersistence(mbStatsUserPersistence);
	}

	public static com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence getPollsQuestionPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getPollsQuestionPersistence();
	}

	public static void setPollsQuestionPersistence(
		com.liferay.portlet.polls.service.persistence.PollsQuestionPersistence pollsQuestionPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setPollsQuestionPersistence(pollsQuestionPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence getSCFrameworkVersionPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getSCFrameworkVersionPersistence();
	}

	public static void setSCFrameworkVersionPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence scFrameworkVersionPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setSCFrameworkVersionPersistence(scFrameworkVersionPersistence);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence getSCProductEntryPersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getSCProductEntryPersistence();
	}

	public static void setSCProductEntryPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence scProductEntryPersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setSCProductEntryPersistence(scProductEntryPersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiNodePersistence getWikiNodePersistence() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getWikiNodePersistence();
	}

	public static void setWikiNodePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiNodePersistence wikiNodePersistence) {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setWikiNodePersistence(wikiNodePersistence);
	}

	public static void afterPropertiesSet() {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Group addGroup(long userId,
		java.lang.String className, long classPK, java.lang.String name,
		java.lang.String description, int type, java.lang.String friendlyURL,
		boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.addGroup(userId, className, classPK, name,
			description, type, friendlyURL, active);
	}

	public static com.liferay.portal.model.Group addGroup(long userId,
		java.lang.String className, long classPK, long liveGroupId,
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.addGroup(userId, className, classPK,
			liveGroupId, name, description, type, friendlyURL, active);
	}

	public static void addRoleGroups(long roleId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.addRoleGroups(roleId, groupIds);
	}

	public static void addUserGroups(long userId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.addUserGroups(userId, groupIds);
	}

	public static void checkSystemGroups(long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.checkSystemGroups(companyId);
	}

	public static void deleteGroup(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.deleteGroup(groupId);
	}

	public static com.liferay.portal.model.Group getFriendlyURLGroup(
		long companyId, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getFriendlyURLGroup(companyId, friendlyURL);
	}

	public static com.liferay.portal.model.Group getGroup(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getGroup(groupId);
	}

	public static com.liferay.portal.model.Group getGroup(long companyId,
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getGroup(companyId, name);
	}

	public static com.liferay.portal.model.Group getOrganizationGroup(
		long companyId, long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrganizationGroup(companyId, organizationId);
	}

	public static java.util.List getOrganizationsGroups(
		java.util.List organizations)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getOrganizationsGroups(organizations);
	}

	public static java.util.List getRoleGroups(long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getRoleGroups(roleId);
	}

	public static com.liferay.portal.model.Group getStagingGroup(
		long liveGroupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getStagingGroup(liveGroupId);
	}

	public static com.liferay.portal.model.Group getUserGroup(long companyId,
		long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroup(companyId, userId);
	}

	public static com.liferay.portal.model.Group getUserGroupGroup(
		long companyId, long userGroupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroupGroup(companyId, userGroupId);
	}

	public static java.util.List getUserGroups(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroups(userId);
	}

	public static java.util.List getUserGroupsGroups(java.util.List userGroups)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.getUserGroupsGroups(userGroups);
	}

	public static boolean hasRoleGroup(long roleId, long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.hasRoleGroup(roleId, groupId);
	}

	public static boolean hasUserGroup(long userId, long groupId)
		throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.hasUserGroup(userId, groupId);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String description, java.util.LinkedHashMap params,
		int begin, int end) throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.search(companyId, name, description, params,
			begin, end);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String description, java.util.LinkedHashMap params,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.search(companyId, name, description, params,
			begin, end, obc);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.util.LinkedHashMap params)
		throws com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.searchCount(companyId, name, description,
			params);
	}

	public static void setRoleGroups(long roleId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.setRoleGroups(roleId, groupIds);
	}

	public static void unsetRoleGroups(long roleId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.unsetRoleGroups(roleId, groupIds);
	}

	public static void unsetUserGroups(long userId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		groupLocalService.unsetUserGroups(userId, groupIds);
	}

	public static com.liferay.portal.model.Group updateGroup(long groupId,
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.updateGroup(groupId, name, description, type,
			friendlyURL, active);
	}

	public static com.liferay.portal.model.Group updateGroup(long groupId,
		java.lang.String typeSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

		return groupLocalService.updateGroup(groupId, typeSettings);
	}
}