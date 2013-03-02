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
 * <a href="ClassNameLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ClassNameLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ClassNameLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ClassNameLocalService
 * @see com.liferay.portal.service.ClassNameLocalServiceFactory
 *
 */
public class ClassNameLocalServiceUtil {
	public static com.liferay.portal.model.ClassName addClassName(
		com.liferay.portal.model.ClassName model)
		throws com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.addClassName(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.ClassName updateClassName(
		com.liferay.portal.model.ClassName model)
		throws com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.updateClassName(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.afterPropertiesSet();
	}

	public static void checkClassNames()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		classNameLocalService.checkClassNames();
	}

	public static com.liferay.portal.model.ClassName getClassName(
		long classNameId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getClassName(classNameId);
	}

	public static com.liferay.portal.model.ClassName getClassName(
		java.lang.String value)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ClassNameLocalService classNameLocalService = ClassNameLocalServiceFactory.getService();

		return classNameLocalService.getClassName(value);
	}
}