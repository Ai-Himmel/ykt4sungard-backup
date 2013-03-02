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
 * <a href="UserTrackerLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.UserTrackerLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.UserTrackerLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.UserTrackerLocalService
 * @see com.liferay.portal.service.UserTrackerLocalServiceFactory
 *
 */
public class UserTrackerLocalServiceUtil {
	public static com.liferay.portal.model.UserTracker addUserTracker(
		com.liferay.portal.model.UserTracker model)
		throws com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.addUserTracker(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.UserTracker updateUserTracker(
		com.liferay.portal.model.UserTracker model)
		throws com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.updateUserTracker(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.UserTracker addUserTracker(
		long companyId, long userId, java.util.Date modifiedDate,
		java.lang.String sessionId, java.lang.String remoteAddr,
		java.lang.String remoteHost, java.lang.String userAgent,
		java.util.List userTrackerPaths)
		throws com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.addUserTracker(companyId, userId,
			modifiedDate, sessionId, remoteAddr, remoteHost, userAgent,
			userTrackerPaths);
	}

	public static void deleteUserTracker(long userTrackerId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		userTrackerLocalService.deleteUserTracker(userTrackerId);
	}

	public static java.util.List getUserTrackers(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		UserTrackerLocalService userTrackerLocalService = UserTrackerLocalServiceFactory.getService();

		return userTrackerLocalService.getUserTrackers(companyId, begin, end);
	}
}