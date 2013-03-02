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
 * <a href="PhoneLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PhoneLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PhoneLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PhoneLocalService
 * @see com.liferay.portal.service.PhoneLocalServiceFactory
 *
 */
public class PhoneLocalServiceUtil {
	public static com.liferay.portal.model.Phone addPhone(
		com.liferay.portal.model.Phone model)
		throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.addPhone(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Phone updatePhone(
		com.liferay.portal.model.Phone model)
		throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.updatePhone(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Phone addPhone(long userId,
		java.lang.String className, long classPK, java.lang.String number,
		java.lang.String extension, int typeId, boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.addPhone(userId, className, classPK, number,
			extension, typeId, primary);
	}

	public static void deletePhone(long phoneId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.deletePhone(phoneId);
	}

	public static void deletePhones(long companyId, java.lang.String className,
		long classPK) throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		phoneLocalService.deletePhones(companyId, className, classPK);
	}

	public static com.liferay.portal.model.Phone getPhone(long phoneId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPhone(phoneId);
	}

	public static java.util.List getPhones()
		throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPhones();
	}

	public static java.util.List getPhones(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.getPhones(companyId, className, classPK);
	}

	public static com.liferay.portal.model.Phone updatePhone(long phoneId,
		java.lang.String number, java.lang.String extension, int typeId,
		boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PhoneLocalService phoneLocalService = PhoneLocalServiceFactory.getService();

		return phoneLocalService.updatePhone(phoneId, number, extension,
			typeId, primary);
	}
}