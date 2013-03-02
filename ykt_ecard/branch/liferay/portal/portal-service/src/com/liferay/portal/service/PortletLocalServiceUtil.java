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
 * <a href="PortletLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PortletLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PortletLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PortletLocalService
 * @see com.liferay.portal.service.PortletLocalServiceFactory
 *
 */
public class PortletLocalServiceUtil {
	public static com.liferay.portal.model.Portlet addPortlet(
		com.liferay.portal.model.Portlet model)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.addPortlet(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Portlet updatePortlet(
		com.liferay.portal.model.Portlet model)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.updatePortlet(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.afterPropertiesSet();
	}

	public static void destroyPortlet(com.liferay.portal.model.Portlet portlet) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.destroyPortlet(portlet);
	}

	public static com.liferay.portal.model.PortletCategory getEARDisplay(
		java.lang.String xml) throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getEARDisplay(xml);
	}

	public static com.liferay.portal.model.PortletCategory getWARDisplay(
		java.lang.String servletContextName, java.lang.String xml)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getWARDisplay(servletContextName, xml);
	}

	public static java.util.List getFriendlyURLMappers() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getFriendlyURLMappers();
	}

	public static com.liferay.portal.model.Portlet getPortletById(
		long companyId, java.lang.String portletId)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortletById(companyId, portletId);
	}

	public static com.liferay.portal.model.Portlet getPortletByStrutsPath(
		long companyId, java.lang.String strutsPath)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortletByStrutsPath(companyId, strutsPath);
	}

	public static java.util.List getPortlets() {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortlets();
	}

	public static java.util.List getPortlets(long companyId)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortlets(companyId);
	}

	public static java.util.List getPortlets(long companyId,
		boolean showSystem, boolean showPortal)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.getPortlets(companyId, showSystem, showPortal);
	}

	public static boolean hasPortlet(long companyId, java.lang.String portletId)
		throws com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.hasPortlet(companyId, portletId);
	}

	public static void initEAR(java.lang.String[] xmls,
		com.liferay.portal.kernel.plugin.PluginPackage pluginPackage) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		portletLocalService.initEAR(xmls, pluginPackage);
	}

	public static java.util.List initWAR(java.lang.String servletContextName,
		java.lang.String[] xmls,
		com.liferay.portal.kernel.plugin.PluginPackage pluginPackage) {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.initWAR(servletContextName, xmls,
			pluginPackage);
	}

	public static com.liferay.portal.model.Portlet updatePortlet(
		long companyId, java.lang.String portletId, java.lang.String roles,
		boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletLocalService portletLocalService = PortletLocalServiceFactory.getService();

		return portletLocalService.updatePortlet(companyId, portletId, roles,
			active);
	}
}