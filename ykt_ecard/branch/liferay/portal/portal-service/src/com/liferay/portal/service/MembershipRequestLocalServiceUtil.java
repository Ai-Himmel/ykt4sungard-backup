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
 * <a href="MembershipRequestLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.MembershipRequestLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.MembershipRequestLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.MembershipRequestLocalService
 * @see com.liferay.portal.service.MembershipRequestLocalServiceFactory
 *
 */
public class MembershipRequestLocalServiceUtil {
	public static com.liferay.portal.model.MembershipRequest addMembershipRequest(
		com.liferay.portal.model.MembershipRequest model)
		throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.addMembershipRequest(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.MembershipRequest updateMembershipRequest(
		com.liferay.portal.model.MembershipRequest model)
		throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.updateMembershipRequest(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.MembershipRequest addMembershipRequest(
		long userId, long groupId, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.addMembershipRequest(userId,
			groupId, comments);
	}

	public static com.liferay.portal.model.MembershipRequest getMembershipRequest(
		long membershipRequestId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.getMembershipRequest(membershipRequestId);
	}

	public static void deleteMembershipRequests(long groupId)
		throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.deleteMembershipRequests(groupId);
	}

	public static void deleteMembershipRequests(long groupId, int statusId)
		throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.deleteMembershipRequests(groupId, statusId);
	}

	public static java.util.List search(long groupId, int status, int begin,
		int end) throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.search(groupId, status, begin, end);
	}

	public static int searchCount(long groupId, int status)
		throws com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		return membershipRequestLocalService.searchCount(groupId, status);
	}

	public static void updateStatus(long replierUserId,
		long membershipRequestId, java.lang.String replyComments, int statusId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MembershipRequestLocalService membershipRequestLocalService = MembershipRequestLocalServiceFactory.getService();

		membershipRequestLocalService.updateStatus(replierUserId,
			membershipRequestId, replyComments, statusId);
	}
}