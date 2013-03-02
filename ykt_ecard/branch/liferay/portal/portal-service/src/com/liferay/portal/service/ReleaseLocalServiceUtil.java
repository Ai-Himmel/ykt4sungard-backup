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
 * <a href="ReleaseLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ReleaseLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ReleaseLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ReleaseLocalService
 * @see com.liferay.portal.service.ReleaseLocalServiceFactory
 *
 */
public class ReleaseLocalServiceUtil {
	public static com.liferay.portal.model.Release addRelease(
		com.liferay.portal.model.Release model)
		throws com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.addRelease(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Release updateRelease(
		com.liferay.portal.model.Release model)
		throws com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.updateRelease(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		releaseLocalService.afterPropertiesSet();
	}

	public static int getBuildNumberOrCreate()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getBuildNumberOrCreate();
	}

	public static com.liferay.portal.model.Release getRelease()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.getRelease();
	}

	public static com.liferay.portal.model.Release updateRelease(
		boolean verified)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ReleaseLocalService releaseLocalService = ReleaseLocalServiceFactory.getService();

		return releaseLocalService.updateRelease(verified);
	}
}