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
 * <a href="ResourceCodeLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ResourceCodeLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ResourceCodeLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ResourceCodeLocalService
 * @see com.liferay.portal.service.ResourceCodeLocalServiceFactory
 *
 */
public class ResourceCodeLocalServiceUtil {
	public static com.liferay.portal.model.ResourceCode addResourceCode(
		com.liferay.portal.model.ResourceCode model)
		throws com.liferay.portal.SystemException {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.addResourceCode(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.ResourceCode updateResourceCode(
		com.liferay.portal.model.ResourceCode model)
		throws com.liferay.portal.SystemException {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.updateResourceCode(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		resourceCodeLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.ResourceCode getResourceCode(
		long codeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getResourceCode(codeId);
	}

	public static com.liferay.portal.model.ResourceCode getResourceCode(
		long companyId, java.lang.String name, int scope)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ResourceCodeLocalService resourceCodeLocalService = ResourceCodeLocalServiceFactory.getService();

		return resourceCodeLocalService.getResourceCode(companyId, name, scope);
	}
}