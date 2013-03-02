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
 * <a href="ResourceLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ResourceLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ResourceLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ResourceLocalService
 * @see com.liferay.portal.service.ResourceLocalServiceFactory
 *
 */
public class ResourceLocalServiceUtil {
	public static com.liferay.portal.model.Resource addResource(
		com.liferay.portal.model.Resource model)
		throws com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.addResource(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Resource updateResource(
		com.liferay.portal.model.Resource model)
		throws com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.updateResource(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.afterPropertiesSet();
	}

	public static void addModelResources(long companyId, long groupId,
		long userId, java.lang.String name, long primKey,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.addModelResources(companyId, groupId, userId,
			name, primKey, communityPermissions, guestPermissions);
	}

	public static void addModelResources(long companyId, long groupId,
		long userId, java.lang.String name, java.lang.String primKey,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.addModelResources(companyId, groupId, userId,
			name, primKey, communityPermissions, guestPermissions);
	}

	public static com.liferay.portal.model.Resource addResource(
		long companyId, java.lang.String name, int scope,
		java.lang.String primKey)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.addResource(companyId, name, scope, primKey);
	}

	public static void addResources(long companyId, long groupId,
		java.lang.String name, boolean portletActions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.addResources(companyId, groupId, name,
			portletActions);
	}

	public static void addResources(long companyId, long groupId, long userId,
		java.lang.String name, long primKey, boolean portletActions,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.addResources(companyId, groupId, userId, name,
			primKey, portletActions, addCommunityPermissions,
			addGuestPermissions);
	}

	public static void addResources(long companyId, long groupId, long userId,
		java.lang.String name, java.lang.String primKey,
		boolean portletActions, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.addResources(companyId, groupId, userId, name,
			primKey, portletActions, addCommunityPermissions,
			addGuestPermissions);
	}

	public static void deleteResource(long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.deleteResource(resourceId);
	}

	public static void deleteResource(
		com.liferay.portal.model.Resource resource)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.deleteResource(resource);
	}

	public static void deleteResource(long companyId, java.lang.String name,
		int scope, long primKey)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.deleteResource(companyId, name, scope, primKey);
	}

	public static void deleteResource(long companyId, java.lang.String name,
		int scope, java.lang.String primKey)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.deleteResource(companyId, name, scope, primKey);
	}

	public static void deleteResources(java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		resourceLocalService.deleteResources(name);
	}

	public static long getLatestResourceId()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getLatestResourceId();
	}

	public static com.liferay.portal.model.Resource getResource(long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getResource(resourceId);
	}

	public static java.util.List getResources()
		throws com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getResources();
	}

	public static com.liferay.portal.model.Resource getResource(
		long companyId, java.lang.String name, int scope,
		java.lang.String primKey)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceLocalService resourceLocalService = ResourceLocalServiceFactory.getService();

		return resourceLocalService.getResource(companyId, name, scope, primKey);
	}
}