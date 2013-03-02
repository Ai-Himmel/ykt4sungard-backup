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
 * <a href="UserTrackerPathLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.UserTrackerPathLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.UserTrackerPathLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.UserTrackerPathLocalService
 * @see com.liferay.portal.service.UserTrackerPathLocalServiceFactory
 *
 */
public class UserTrackerPathLocalServiceUtil {
	public static com.liferay.portal.model.UserTrackerPath addUserTrackerPath(
		com.liferay.portal.model.UserTrackerPath model)
		throws com.liferay.portal.SystemException {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.addUserTrackerPath(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.UserTrackerPath updateUserTrackerPath(
		com.liferay.portal.model.UserTrackerPath model)
		throws com.liferay.portal.SystemException {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.updateUserTrackerPath(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		userTrackerPathLocalService.afterPropertiesSet();
	}

	public static java.util.List getUserTrackerPaths(long userTrackerId,
		int begin, int end) throws com.liferay.portal.SystemException {
		UserTrackerPathLocalService userTrackerPathLocalService = UserTrackerPathLocalServiceFactory.getService();

		return userTrackerPathLocalService.getUserTrackerPaths(userTrackerId,
			begin, end);
	}
}