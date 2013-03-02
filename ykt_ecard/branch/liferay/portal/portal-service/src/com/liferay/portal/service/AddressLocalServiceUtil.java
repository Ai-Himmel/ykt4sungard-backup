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
 * <a href="AddressLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.AddressLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.AddressLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.AddressLocalService
 * @see com.liferay.portal.service.AddressLocalServiceFactory
 *
 */
public class AddressLocalServiceUtil {
	public static com.liferay.portal.model.Address addAddress(
		com.liferay.portal.model.Address model)
		throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.addAddress(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Address updateAddress(
		com.liferay.portal.model.Address model)
		throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.updateAddress(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.Address addAddress(long userId,
		java.lang.String className, long classPK, java.lang.String street1,
		java.lang.String street2, java.lang.String street3,
		java.lang.String city, java.lang.String zip, long regionId,
		long countryId, int typeId, boolean mailing, boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.addAddress(userId, className, classPK,
			street1, street2, street3, city, zip, regionId, countryId, typeId,
			mailing, primary);
	}

	public static void deleteAddress(long addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.deleteAddress(addressId);
	}

	public static void deleteAddresses(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		addressLocalService.deleteAddresses(companyId, className, classPK);
	}

	public static com.liferay.portal.model.Address getAddress(long addressId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getAddress(addressId);
	}

	public static java.util.List getAddresses()
		throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getAddresses();
	}

	public static java.util.List getAddresses(long companyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.getAddresses(companyId, className, classPK);
	}

	public static com.liferay.portal.model.Address updateAddress(
		long addressId, java.lang.String street1, java.lang.String street2,
		java.lang.String street3, java.lang.String city, java.lang.String zip,
		long regionId, long countryId, int typeId, boolean mailing,
		boolean primary)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		AddressLocalService addressLocalService = AddressLocalServiceFactory.getService();

		return addressLocalService.updateAddress(addressId, street1, street2,
			street3, city, zip, regionId, countryId, typeId, mailing, primary);
	}
}