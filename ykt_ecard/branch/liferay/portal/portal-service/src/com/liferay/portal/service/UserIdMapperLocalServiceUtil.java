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
 * <a href="UserIdMapperLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.UserIdMapperLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.UserIdMapperLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.UserIdMapperLocalService
 * @see com.liferay.portal.service.UserIdMapperLocalServiceFactory
 *
 */
public class UserIdMapperLocalServiceUtil {
	public static com.liferay.portal.model.UserIdMapper addUserIdMapper(
		com.liferay.portal.model.UserIdMapper model)
		throws com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.addUserIdMapper(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.UserIdMapper updateUserIdMapper(
		com.liferay.portal.model.UserIdMapper model)
		throws com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.updateUserIdMapper(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.afterPropertiesSet();
	}

	public static void deleteUserIdMappers(long userId)
		throws com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		userIdMapperLocalService.deleteUserIdMappers(userId);
	}

	public static com.liferay.portal.model.UserIdMapper getUserIdMapper(
		long userId, java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserIdMapper(userId, type);
	}

	public static com.liferay.portal.model.UserIdMapper getUserIdMapperByExternalUserId(
		java.lang.String type, java.lang.String externalUserId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserIdMapperByExternalUserId(type,
			externalUserId);
	}

	public static java.util.List getUserIdMappers(long userId)
		throws com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.getUserIdMappers(userId);
	}

	public static com.liferay.portal.model.UserIdMapper updateUserIdMapper(
		long userId, java.lang.String type, java.lang.String description,
		java.lang.String externalUserId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		UserIdMapperLocalService userIdMapperLocalService = UserIdMapperLocalServiceFactory.getService();

		return userIdMapperLocalService.updateUserIdMapper(userId, type,
			description, externalUserId);
	}
}