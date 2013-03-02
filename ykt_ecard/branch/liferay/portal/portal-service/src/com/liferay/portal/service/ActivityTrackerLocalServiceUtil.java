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
 * <a href="ActivityTrackerLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ActivityTrackerLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ActivityTrackerLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ActivityTrackerLocalService
 * @see com.liferay.portal.service.ActivityTrackerLocalServiceFactory
 *
 */
public class ActivityTrackerLocalServiceUtil {
	public static com.liferay.portal.model.ActivityTracker addActivityTracker(
		com.liferay.portal.model.ActivityTracker model)
		throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.addActivityTracker(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.ActivityTracker updateActivityTracker(
		com.liferay.portal.model.ActivityTracker model)
		throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.updateActivityTracker(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.ActivityTracker addActivityTracker(
		long userId, long groupId, java.lang.String className, long classPK,
		java.lang.String activity, java.lang.String extraData,
		long receiverUserId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.addActivityTracker(userId, groupId,
			className, classPK, activity, extraData, receiverUserId);
	}

	public static void deleteActivityTrackers(java.lang.String className,
		long classPK) throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		activityTrackerLocalService.deleteActivityTrackers(className, classPK);
	}

	public static java.util.List getCompanyActivityTrackers(long companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getCompanyActivityTrackers(companyId,
			begin, end);
	}

	public static int getCompanyActivityTrackersCount(long companyId)
		throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getCompanyActivityTrackersCount(companyId);
	}

	public static java.util.List getGroupActivityTrackers(long groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getGroupActivityTrackers(groupId,
			begin, end);
	}

	public static int getGroupActivityTrackersCount(long groupId)
		throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getGroupActivityTrackersCount(groupId);
	}

	public static java.util.List getUserActivityTrackers(long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserActivityTrackers(userId,
			begin, end);
	}

	public static int getUserActivityTrackersCount(long userId)
		throws com.liferay.portal.SystemException {
		ActivityTrackerLocalService activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getService();

		return activityTrackerLocalService.getUserActivityTrackersCount(userId);
	}
}