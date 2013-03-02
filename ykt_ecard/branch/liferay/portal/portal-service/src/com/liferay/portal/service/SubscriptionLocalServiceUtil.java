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
 * <a href="SubscriptionLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.SubscriptionLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.SubscriptionLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.SubscriptionLocalService
 * @see com.liferay.portal.service.SubscriptionLocalServiceFactory
 *
 */
public class SubscriptionLocalServiceUtil {
	public static com.liferay.portal.model.Subscription addSubscription(
		com.liferay.portal.model.Subscription model)
		throws com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.addSubscription(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.Subscription updateSubscription(
		com.liferay.portal.model.Subscription model)
		throws com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.updateSubscription(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Subscription addSubscription(
		long userId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.addSubscription(userId, className,
			classPK);
	}

	public static com.liferay.portal.model.Subscription addSubscription(
		long userId, java.lang.String className, long classPK,
		java.lang.String frequency)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.addSubscription(userId, className,
			classPK, frequency);
	}

	public static void deleteSubscription(long subscriptionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.deleteSubscription(subscriptionId);
	}

	public static void deleteSubscription(long userId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.deleteSubscription(userId, className, classPK);
	}

	public static void deleteSubscriptions(long userId)
		throws com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.deleteSubscriptions(userId);
	}

	public static void deleteSubscriptions(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		subscriptionLocalService.deleteSubscriptions(companyId, className,
			classPK);
	}

	public static com.liferay.portal.model.Subscription getSubscription(
		long companyId, long userId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getSubscription(companyId, userId,
			className, classPK);
	}

	public static java.util.List getSubscriptions(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.getSubscriptions(companyId, className,
			classPK);
	}

	public static boolean isSubscribed(long companyId, long userId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SubscriptionLocalService subscriptionLocalService = SubscriptionLocalServiceFactory.getService();

		return subscriptionLocalService.isSubscribed(companyId, userId,
			className, classPK);
	}
}