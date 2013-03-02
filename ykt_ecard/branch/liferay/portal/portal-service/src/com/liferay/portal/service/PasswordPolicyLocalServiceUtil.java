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
 * <a href="PasswordPolicyLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PasswordPolicyLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PasswordPolicyLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PasswordPolicyLocalService
 * @see com.liferay.portal.service.PasswordPolicyLocalServiceFactory
 *
 */
public class PasswordPolicyLocalServiceUtil {
	public static com.liferay.portal.model.PasswordPolicy addPasswordPolicy(
		com.liferay.portal.model.PasswordPolicy model)
		throws com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.addPasswordPolicy(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.PasswordPolicy updatePasswordPolicy(
		com.liferay.portal.model.PasswordPolicy model)
		throws com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.updatePasswordPolicy(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.PasswordPolicy addPasswordPolicy(
		long userId, boolean defaultPolicy, java.lang.String name,
		java.lang.String description, boolean changeable,
		boolean changeRequired, long minAge, boolean checkSyntax,
		boolean allowDictionaryWords, int minLength, boolean history,
		int historyCount, boolean expireable, long maxAge, long warningTime,
		int graceLimit, boolean lockout, int maxFailure, long lockoutDuration,
		long resetFailureCount)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.addPasswordPolicy(userId,
			defaultPolicy, name, description, changeable, changeRequired,
			minAge, checkSyntax, allowDictionaryWords, minLength, history,
			historyCount, expireable, maxAge, warningTime, graceLimit, lockout,
			maxFailure, lockoutDuration, resetFailureCount);
	}

	public static void checkDefaultPasswordPolicy(long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.checkDefaultPasswordPolicy(companyId);
	}

	public static void deletePasswordPolicy(long passwordPolicyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		passwordPolicyLocalService.deletePasswordPolicy(passwordPolicyId);
	}

	public static com.liferay.portal.model.PasswordPolicy getDefaultPasswordPolicy(
		long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getDefaultPasswordPolicy(companyId);
	}

	public static com.liferay.portal.model.PasswordPolicy getPasswordPolicy(
		long passwordPolicyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicy(passwordPolicyId);
	}

	public static com.liferay.portal.model.PasswordPolicy getPasswordPolicy(
		long companyId, long organizationId, long locationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicy(companyId,
			organizationId, locationId);
	}

	public static com.liferay.portal.model.PasswordPolicy getPasswordPolicy(
		long companyId, long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicy(companyId,
			organizationIds);
	}

	public static com.liferay.portal.model.PasswordPolicy getPasswordPolicyByUserId(
		long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.getPasswordPolicyByUserId(userId);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.search(companyId, name, begin, end,
			obc);
	}

	public static int searchCount(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.searchCount(companyId, name);
	}

	public static com.liferay.portal.model.PasswordPolicy updatePasswordPolicy(
		long passwordPolicyId, java.lang.String name,
		java.lang.String description, boolean changeable,
		boolean changeRequired, long minAge, boolean checkSyntax,
		boolean allowDictionaryWords, int minLength, boolean history,
		int historyCount, boolean expireable, long maxAge, long warningTime,
		int graceLimit, boolean lockout, int maxFailure, long lockoutDuration,
		long resetFailureCount)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyLocalService passwordPolicyLocalService = PasswordPolicyLocalServiceFactory.getService();

		return passwordPolicyLocalService.updatePasswordPolicy(passwordPolicyId,
			name, description, changeable, changeRequired, minAge, checkSyntax,
			allowDictionaryWords, minLength, history, historyCount, expireable,
			maxAge, warningTime, graceLimit, lockout, maxFailure,
			lockoutDuration, resetFailureCount);
	}
}