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
 * <a href="CompanyLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.CompanyLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.CompanyLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.CompanyLocalService
 * @see com.liferay.portal.service.CompanyLocalServiceFactory
 *
 */
public class CompanyLocalServiceUtil {
	public static com.liferay.portal.model.Company addCompany(
		com.liferay.portal.model.Company model)
		throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.addCompany(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Company updateCompany(
		com.liferay.portal.model.Company model)
		throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.updateCompany(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Company addCompany(
		java.lang.String webId, java.lang.String virtualHost,
		java.lang.String mx)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.addCompany(webId, virtualHost, mx);
	}

	public static com.liferay.portal.model.Company checkCompany(
		java.lang.String webId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.checkCompany(webId);
	}

	public static com.liferay.portal.model.Company checkCompany(
		java.lang.String webId, java.lang.String mx)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.checkCompany(webId, mx);
	}

	public static void checkCompanyKey(long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.checkCompanyKey(companyId);
	}

	public static java.util.List getCompanies()
		throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanies();
	}

	public static com.liferay.portal.model.Company getCompanyById(
		long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanyById(companyId);
	}

	public static com.liferay.portal.model.Company getCompanyByLogoId(
		long logoId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanyByLogoId(logoId);
	}

	public static com.liferay.portal.model.Company getCompanyByMx(
		java.lang.String mx)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanyByMx(mx);
	}

	public static com.liferay.portal.model.Company getCompanyByVirtualHost(
		java.lang.String virtualHost)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanyByVirtualHost(virtualHost);
	}

	public static com.liferay.portal.model.Company getCompanyByWebId(
		java.lang.String webId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.getCompanyByWebId(webId);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.search(companyId, keywords);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		java.lang.String portletId, long groupId, java.lang.String type,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.search(companyId, portletId, groupId, type,
			keywords);
	}

	public static com.liferay.portal.model.Company updateCompany(
		long companyId, java.lang.String virtualHost, java.lang.String mx)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.updateCompany(companyId, virtualHost, mx);
	}

	public static com.liferay.portal.model.Company updateCompany(
		long companyId, java.lang.String virtualHost, java.lang.String mx,
		java.lang.String name, java.lang.String legalName,
		java.lang.String legalId, java.lang.String legalType,
		java.lang.String sicCode, java.lang.String tickerSymbol,
		java.lang.String industry, java.lang.String type, java.lang.String size)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		return companyLocalService.updateCompany(companyId, virtualHost, mx,
			name, legalName, legalId, legalType, sicCode, tickerSymbol,
			industry, type, size);
	}

	public static void updateDisplay(long companyId,
		java.lang.String languageId, java.lang.String timeZoneId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.updateDisplay(companyId, languageId, timeZoneId);
	}

	public static void updateLogo(long companyId, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.updateLogo(companyId, file);
	}

	public static void updateSecurity(long companyId,
		java.lang.String authType, boolean autoLogin, boolean sendPassword,
		boolean strangers, boolean strangersWithMx, boolean strangersVerify,
		boolean communityLogo)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CompanyLocalService companyLocalService = CompanyLocalServiceFactory.getService();

		companyLocalService.updateSecurity(companyId, authType, autoLogin,
			sendPassword, strangers, strangersWithMx, strangersVerify,
			communityLogo);
	}
}