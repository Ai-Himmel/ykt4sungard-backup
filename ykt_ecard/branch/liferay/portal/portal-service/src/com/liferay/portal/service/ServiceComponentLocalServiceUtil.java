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
 * <a href="ServiceComponentLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ServiceComponentLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ServiceComponentLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ServiceComponentLocalService
 * @see com.liferay.portal.service.ServiceComponentLocalServiceFactory
 *
 */
public class ServiceComponentLocalServiceUtil {
	public static com.liferay.portal.model.ServiceComponent addServiceComponent(
		com.liferay.portal.model.ServiceComponent model)
		throws com.liferay.portal.SystemException {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.addServiceComponent(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.ServiceComponent updateServiceComponent(
		com.liferay.portal.model.ServiceComponent model)
		throws com.liferay.portal.SystemException {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.updateServiceComponent(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		serviceComponentLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.ServiceComponent updateServiceComponent(
		javax.servlet.ServletContext ctx,
		java.lang.ClassLoader portletClassLoader,
		java.lang.String buildNamespace, long buildNumber, long buildDate)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ServiceComponentLocalService serviceComponentLocalService = ServiceComponentLocalServiceFactory.getService();

		return serviceComponentLocalService.updateServiceComponent(ctx,
			portletClassLoader, buildNamespace, buildNumber, buildDate);
	}
}