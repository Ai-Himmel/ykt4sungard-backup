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
 * <a href="LayoutSetLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.LayoutSetLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.LayoutSetLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.LayoutSetLocalService
 * @see com.liferay.portal.service.LayoutSetLocalServiceFactory
 *
 */
public class LayoutSetLocalServiceUtil {
	public static com.liferay.portal.model.LayoutSet addLayoutSet(
		com.liferay.portal.model.LayoutSet model)
		throws com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.addLayoutSet(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.LayoutSet updateLayoutSet(
		com.liferay.portal.model.LayoutSet model)
		throws com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.updateLayoutSet(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.LayoutSet addLayoutSet(
		long groupId, boolean privateLayout)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.addLayoutSet(groupId, privateLayout);
	}

	public static void deleteLayoutSet(long groupId, boolean privateLayout)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.deleteLayoutSet(groupId, privateLayout);
	}

	public static com.liferay.portal.model.LayoutSet getLayoutSet(
		long groupId, boolean privateLayout)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getLayoutSet(groupId, privateLayout);
	}

	public static com.liferay.portal.model.LayoutSet getLayoutSet(
		java.lang.String virtualHost)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.getLayoutSet(virtualHost);
	}

	public static void updateLogo(long groupId, boolean privateLayout,
		boolean logo, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		layoutSetLocalService.updateLogo(groupId, privateLayout, logo, file);
	}

	public static com.liferay.portal.model.LayoutSet updateLookAndFeel(
		long groupId, boolean privateLayout, java.lang.String themeId,
		java.lang.String colorSchemeId, java.lang.String css, boolean wapTheme)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.updateLookAndFeel(groupId, privateLayout,
			themeId, colorSchemeId, css, wapTheme);
	}

	public static com.liferay.portal.model.LayoutSet updatePageCount(
		long groupId, boolean privateLayout)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.updatePageCount(groupId, privateLayout);
	}

	public static com.liferay.portal.model.LayoutSet updateVirtualHost(
		long groupId, boolean privateLayout, java.lang.String virtualHost)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutSetLocalService layoutSetLocalService = LayoutSetLocalServiceFactory.getService();

		return layoutSetLocalService.updateVirtualHost(groupId, privateLayout,
			virtualHost);
	}
}