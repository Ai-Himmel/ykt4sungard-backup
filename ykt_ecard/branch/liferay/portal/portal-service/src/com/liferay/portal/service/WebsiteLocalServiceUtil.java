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
 * <a href="WebsiteLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.WebsiteLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.WebsiteLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.WebsiteLocalService
 * @see com.liferay.portal.service.WebsiteLocalServiceFactory
 *
 */
public class WebsiteLocalServiceUtil {
	public static com.liferay.portal.model.Website addWebsite(
		com.liferay.portal.model.Website model)
		throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.addWebsite(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Website updateWebsite(
		com.liferay.portal.model.Website model)
		throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.updateWebsite(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Website addWebsite(long userId,
		java.lang.String className, long classPK, java.lang.String url,
		int typeId, boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.addWebsite(userId, className, classPK, url,
			typeId, primary);
	}

	public static void deleteWebsite(long websiteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.deleteWebsite(websiteId);
	}

	public static void deleteWebsites(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		websiteLocalService.deleteWebsites(companyId, className, classPK);
	}

	public static com.liferay.portal.model.Website getWebsite(long websiteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getWebsite(websiteId);
	}

	public static java.util.List getWebsites()
		throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getWebsites();
	}

	public static java.util.List getWebsites(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.getWebsites(companyId, className, classPK);
	}

	public static com.liferay.portal.model.Website updateWebsite(
		long websiteId, java.lang.String url, int typeId, boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebsiteLocalService websiteLocalService = WebsiteLocalServiceFactory.getService();

		return websiteLocalService.updateWebsite(websiteId, url, typeId, primary);
	}
}