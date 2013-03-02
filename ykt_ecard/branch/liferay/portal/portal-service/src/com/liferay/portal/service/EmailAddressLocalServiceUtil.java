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
 * <a href="EmailAddressLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.EmailAddressLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.EmailAddressLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.EmailAddressLocalService
 * @see com.liferay.portal.service.EmailAddressLocalServiceFactory
 *
 */
public class EmailAddressLocalServiceUtil {
	public static com.liferay.portal.model.EmailAddress addEmailAddress(
		com.liferay.portal.model.EmailAddress model)
		throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.addEmailAddress(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.EmailAddress updateEmailAddress(
		com.liferay.portal.model.EmailAddress model)
		throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.updateEmailAddress(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.EmailAddress addEmailAddress(
		long userId, java.lang.String className, long classPK,
		java.lang.String address, int typeId, boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.addEmailAddress(userId, className,
			classPK, address, typeId, primary);
	}

	public static void deleteEmailAddress(long emailAddressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.deleteEmailAddress(emailAddressId);
	}

	public static void deleteEmailAddresses(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		emailAddressLocalService.deleteEmailAddresses(companyId, className,
			classPK);
	}

	public static com.liferay.portal.model.EmailAddress getEmailAddress(
		long emailAddressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getEmailAddress(emailAddressId);
	}

	public static java.util.List getEmailAddresses()
		throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getEmailAddresses();
	}

	public static java.util.List getEmailAddresses(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.getEmailAddresses(companyId, className,
			classPK);
	}

	public static com.liferay.portal.model.EmailAddress updateEmailAddress(
		long emailAddressId, java.lang.String address, int typeId,
		boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		EmailAddressLocalService emailAddressLocalService = EmailAddressLocalServiceFactory.getService();

		return emailAddressLocalService.updateEmailAddress(emailAddressId,
			address, typeId, primary);
	}
}