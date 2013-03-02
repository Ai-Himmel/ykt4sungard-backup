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
 * <a href="PermissionLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PermissionLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PermissionLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PermissionLocalService
 * @see com.liferay.portal.service.PermissionLocalServiceFactory
 *
 */
public class PermissionLocalServiceUtil {
	public static com.liferay.portal.model.Permission addPermission(
		com.liferay.portal.model.Permission model)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.addPermission(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Permission updatePermission(
		com.liferay.portal.model.Permission model)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.updatePermission(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Permission addPermission(
		long companyId, java.lang.String actionId, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.addPermission(companyId, actionId,
			resourceId);
	}

	public static java.util.List addPermissions(long companyId,
		java.lang.String name, long resourceId, boolean portletActions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.addPermissions(companyId, name,
			resourceId, portletActions);
	}

	public static void addUserPermissions(long userId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.addUserPermissions(userId, actionIds, resourceId);
	}

	public static java.util.List getActions(java.util.List permissions)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getActions(permissions);
	}

	public static java.util.List getGroupPermissions(long groupId,
		long resourceId) throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getGroupPermissions(groupId, resourceId);
	}

	public static java.util.List getGroupPermissions(long groupId,
		long companyId, java.lang.String name, int scope,
		java.lang.String primKey) throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getGroupPermissions(groupId, companyId,
			name, scope, primKey);
	}

	public static java.util.List getOrgGroupPermissions(long organizationId,
		long groupId, long resourceId)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getOrgGroupPermissions(organizationId,
			groupId, resourceId);
	}

	public static long getLatestPermissionId()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getLatestPermissionId();
	}

	public static java.util.List getPermissions(long companyId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getPermissions(companyId, actionIds,
			resourceId);
	}

	public static java.util.List getRolePermissions(long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getRolePermissions(roleId);
	}

	public static java.util.List getRolePermissions(long roleId, long resourceId)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getRolePermissions(roleId, resourceId);
	}

	public static java.util.List getUserPermissions(long userId, long resourceId)
		throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserPermissions(userId, resourceId);
	}

	public static java.util.List getUserPermissions(long userId,
		long companyId, java.lang.String name, int scope,
		java.lang.String primKey) throws com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.getUserPermissions(userId, companyId,
			name, scope, primKey);
	}

	public static boolean hasGroupPermission(long groupId,
		java.lang.String actionId, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.hasGroupPermission(groupId, actionId,
			resourceId);
	}

	public static boolean hasRolePermission(long roleId, long companyId,
		java.lang.String name, int scope, java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.hasRolePermission(roleId, companyId,
			name, scope, actionId);
	}

	public static boolean hasRolePermission(long roleId, long companyId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.hasRolePermission(roleId, companyId,
			name, scope, primKey, actionId);
	}

	public static boolean hasUserPermission(long userId,
		java.lang.String actionId, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.hasUserPermission(userId, actionId,
			resourceId);
	}

	public static boolean hasUserPermissions(long userId, long groupId,
		java.lang.String actionId, long[] resourceIds,
		com.liferay.portal.kernel.security.permission.PermissionCheckerBag permissionCheckerBag)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		return permissionLocalService.hasUserPermissions(userId, groupId,
			actionId, resourceIds, permissionCheckerBag);
	}

	public static void setGroupPermissions(long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setGroupPermissions(groupId, actionIds,
			resourceId);
	}

	public static void setGroupPermissions(java.lang.String className,
		java.lang.String classPK, long groupId, java.lang.String[] actionIds,
		long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setGroupPermissions(className, classPK, groupId,
			actionIds, resourceId);
	}

	public static void setOrgGroupPermissions(long organizationId,
		long groupId, java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setOrgGroupPermissions(organizationId, groupId,
			actionIds, resourceId);
	}

	public static void setRolePermission(long roleId, long companyId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setRolePermission(roleId, companyId, name,
			scope, primKey, actionId);
	}

	public static void setRolePermissions(long roleId, long companyId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String[] actionIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setRolePermissions(roleId, companyId, name,
			scope, primKey, actionIds);
	}

	public static void setRolePermissions(long roleId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setRolePermissions(roleId, actionIds, resourceId);
	}

	public static void setUserPermissions(long userId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.setUserPermissions(userId, actionIds, resourceId);
	}

	public static void unsetRolePermission(long roleId, long permissionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.unsetRolePermission(roleId, permissionId);
	}

	public static void unsetRolePermission(long roleId, long companyId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.unsetRolePermission(roleId, companyId, name,
			scope, primKey, actionId);
	}

	public static void unsetRolePermissions(long roleId, long companyId,
		java.lang.String name, int scope, java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.unsetRolePermissions(roleId, companyId, name,
			scope, actionId);
	}

	public static void unsetUserPermissions(long userId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PermissionLocalService permissionLocalService = PermissionLocalServiceFactory.getService();

		permissionLocalService.unsetUserPermissions(userId, actionIds,
			resourceId);
	}
}