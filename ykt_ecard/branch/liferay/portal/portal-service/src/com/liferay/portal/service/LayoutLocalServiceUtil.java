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
 * <a href="LayoutLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.LayoutLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.LayoutLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.LayoutLocalService
 * @see com.liferay.portal.service.LayoutLocalServiceFactory
 *
 */
public class LayoutLocalServiceUtil {
	public static com.liferay.portal.model.Layout addLayout(
		com.liferay.portal.model.Layout model)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.addLayout(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Layout updateLayout(
		com.liferay.portal.model.Layout model)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateLayout(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setWebsitePersistence(websitePersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getDLFolderPersistence();
	}

	public static void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setDLFolderPersistence(dlFolderPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static void afterPropertiesSet() {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Layout addLayout(long userId,
		long groupId, boolean privateLayout, long parentLayoutId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.addLayout(userId, groupId, privateLayout,
			parentLayoutId, name, title, description, type, hidden, friendlyURL);
	}

	public static com.liferay.portal.model.Layout addLayout(long userId,
		long groupId, boolean privateLayout, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.addLayout(userId, groupId, privateLayout,
			parentLayoutId, localeNamesMap, localeTitlesMap, description, type,
			hidden, friendlyURL);
	}

	public static com.liferay.portal.model.Layout addLayout(long userId,
		long groupId, boolean privateLayout, long parentLayoutId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL, long dlFolderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.addLayout(userId, groupId, privateLayout,
			parentLayoutId, name, title, description, type, hidden,
			friendlyURL, dlFolderId);
	}

	public static com.liferay.portal.model.Layout addLayout(long userId,
		long groupId, boolean privateLayout, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL, long dlFolderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.addLayout(userId, groupId, privateLayout,
			parentLayoutId, localeNamesMap, localeTitlesMap, description, type,
			hidden, friendlyURL, dlFolderId);
	}

	public static void deleteLayout(long plid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.deleteLayout(plid);
	}

	public static void deleteLayout(long groupId, boolean privateLayout,
		long layoutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.deleteLayout(groupId, privateLayout, layoutId);
	}

	public static void deleteLayout(com.liferay.portal.model.Layout layout,
		boolean updateLayoutSet)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.deleteLayout(layout, updateLayoutSet);
	}

	public static void deleteLayouts(long groupId, boolean privateLayout)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.deleteLayouts(groupId, privateLayout);
	}

	public static byte[] exportLayouts(long groupId, boolean privateLayout,
		java.util.Map parameterMap)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.exportLayouts(groupId, privateLayout,
			parameterMap);
	}

	public static byte[] exportLayouts(long groupId, boolean privateLayout,
		long[] layoutIds, java.util.Map parameterMap)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.exportLayouts(groupId, privateLayout,
			layoutIds, parameterMap);
	}

	public static byte[] exportPortletInfo(long plid,
		java.lang.String portletId, java.util.Map parameterMap)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.exportPortletInfo(plid, portletId,
			parameterMap);
	}

	public static long getDefaultPlid(long groupId)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getDefaultPlid(groupId);
	}

	public static long getDefaultPlid(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getDefaultPlid(groupId, privateLayout);
	}

	public static com.liferay.portal.model.Layout getDLFolderLayout(
		long dlFolderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getDLFolderLayout(dlFolderId);
	}

	public static com.liferay.portal.model.Layout getFriendlyURLLayout(
		long groupId, boolean privateLayout, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getFriendlyURLLayout(groupId, privateLayout,
			friendlyURL);
	}

	public static com.liferay.portal.model.Layout getLayout(long plid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayout(plid);
	}

	public static com.liferay.portal.model.Layout getLayout(long groupId,
		boolean privateLayout, long layoutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayout(groupId, privateLayout, layoutId);
	}

	public static com.liferay.portal.model.Layout getLayoutByIconImageId(
		long iconImageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayoutByIconImageId(iconImageId);
	}

	public static java.util.List getLayouts(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayouts(groupId, privateLayout);
	}

	public static java.util.List getLayouts(long groupId,
		boolean privateLayout, long parentLayoutId)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayouts(groupId, privateLayout,
			parentLayoutId);
	}

	public static java.util.List getLayouts(long groupId,
		boolean privateLayout, long parentLayoutId, int begin, int end)
		throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayouts(groupId, privateLayout,
			parentLayoutId, begin, end);
	}

	public static java.util.List getLayouts(long groupId,
		boolean privateLayout, long[] layoutIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayouts(groupId, privateLayout, layoutIds);
	}

	public static com.liferay.portal.model.LayoutReference[] getLayouts(
		long companyId, java.lang.String portletId, java.lang.String prefsKey,
		java.lang.String prefsValue) throws com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.getLayouts(companyId, portletId, prefsKey,
			prefsValue);
	}

	public static void importLayouts(long userId, long groupId,
		boolean privateLayout, java.util.Map parameterMap, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.importLayouts(userId, groupId, privateLayout,
			parameterMap, file);
	}

	public static void importLayouts(long userId, long groupId,
		boolean privateLayout, java.util.Map parameterMap,
		java.io.InputStream is)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.importLayouts(userId, groupId, privateLayout,
			parameterMap, is);
	}

	public static void importPortletInfo(long userId, long plid,
		java.lang.String portletId, java.util.Map parameterMap,
		java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.importPortletInfo(userId, plid, portletId,
			parameterMap, file);
	}

	public static void importPortletInfo(long userId, long plid,
		java.lang.String portletId, java.util.Map parameterMap,
		java.io.InputStream is)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.importPortletInfo(userId, plid, portletId,
			parameterMap, is);
	}

	public static void setLayouts(long groupId, boolean privateLayout,
		long parentLayoutId, long[] layoutIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		layoutLocalService.setLayouts(groupId, privateLayout, parentLayoutId,
			layoutIds);
	}

	public static com.liferay.portal.model.Layout updateLayout(long groupId,
		boolean privateLayout, long layoutId, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateLayout(groupId, privateLayout,
			layoutId, parentLayoutId, localeNamesMap, localeTitlesMap,
			description, type, hidden, friendlyURL);
	}

	public static com.liferay.portal.model.Layout updateLayout(long groupId,
		boolean privateLayout, long layoutId, long parentLayoutId,
		java.util.Map localeNamesMap, java.util.Map localeTitlesMap,
		java.lang.String description, java.lang.String type, boolean hidden,
		java.lang.String friendlyURL, java.lang.Boolean iconImage,
		byte[] iconBytes)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateLayout(groupId, privateLayout,
			layoutId, parentLayoutId, localeNamesMap, localeTitlesMap,
			description, type, hidden, friendlyURL, iconImage, iconBytes);
	}

	public static com.liferay.portal.model.Layout updateLayout(long groupId,
		boolean privateLayout, long layoutId, java.lang.String typeSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateLayout(groupId, privateLayout,
			layoutId, typeSettings);
	}

	public static com.liferay.portal.model.Layout updateLookAndFeel(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String themeId, java.lang.String colorSchemeId,
		java.lang.String css, boolean wapTheme)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateLookAndFeel(groupId, privateLayout,
			layoutId, themeId, colorSchemeId, css, wapTheme);
	}

	public static com.liferay.portal.model.Layout updateName(long plid,
		java.lang.String name, java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateName(plid, name, languageId);
	}

	public static com.liferay.portal.model.Layout updateName(long groupId,
		boolean privateLayout, long layoutId, java.lang.String name,
		java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateName(groupId, privateLayout, layoutId,
			name, languageId);
	}

	public static com.liferay.portal.model.Layout updateName(
		com.liferay.portal.model.Layout layout, java.lang.String name,
		java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateName(layout, name, languageId);
	}

	public static com.liferay.portal.model.Layout updateParentLayoutId(
		long plid, long parentPlid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateParentLayoutId(plid, parentPlid);
	}

	public static com.liferay.portal.model.Layout updateParentLayoutId(
		long groupId, boolean privateLayout, long layoutId, long parentLayoutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updateParentLayoutId(groupId, privateLayout,
			layoutId, parentLayoutId);
	}

	public static com.liferay.portal.model.Layout updatePriority(long plid,
		int priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updatePriority(plid, priority);
	}

	public static com.liferay.portal.model.Layout updatePriority(long groupId,
		boolean privateLayout, long layoutId, int priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updatePriority(groupId, privateLayout,
			layoutId, priority);
	}

	public static com.liferay.portal.model.Layout updatePriority(
		com.liferay.portal.model.Layout layout, int priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		LayoutLocalService layoutLocalService = LayoutLocalServiceFactory.getService();

		return layoutLocalService.updatePriority(layout, priority);
	}
}