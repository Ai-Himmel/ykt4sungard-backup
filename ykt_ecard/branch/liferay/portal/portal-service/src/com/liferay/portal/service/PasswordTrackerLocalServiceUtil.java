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
 * <a href="PasswordTrackerLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PasswordTrackerLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PasswordTrackerLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PasswordTrackerLocalService
 * @see com.liferay.portal.service.PasswordTrackerLocalServiceFactory
 *
 */
public class PasswordTrackerLocalServiceUtil {
	public static com.liferay.portal.model.PasswordTracker addPasswordTracker(
		com.liferay.portal.model.PasswordTracker model)
		throws com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.addPasswordTracker(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.PasswordTracker updatePasswordTracker(
		com.liferay.portal.model.PasswordTracker model)
		throws com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.updatePasswordTracker(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.afterPropertiesSet();
	}

	public static void deletePasswordTrackers(long userId)
		throws com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.deletePasswordTrackers(userId);
	}

	public static boolean isSameAsCurrentPassword(long userId,
		java.lang.String newClearTextPwd)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.isSameAsCurrentPassword(userId,
			newClearTextPwd);
	}

	public static boolean isValidPassword(long userId,
		java.lang.String newClearTextPwd)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		return passwordTrackerLocalService.isValidPassword(userId,
			newClearTextPwd);
	}

	public static void trackPassword(long userId, java.lang.String encPwd)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordTrackerLocalService passwordTrackerLocalService = PasswordTrackerLocalServiceFactory.getService();

		passwordTrackerLocalService.trackPassword(userId, encPwd);
	}
}