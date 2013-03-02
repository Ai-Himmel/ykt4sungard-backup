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
 * <a href="OrganizationLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.OrganizationLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.OrganizationLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.OrganizationLocalService
 * @see com.liferay.portal.service.OrganizationLocalServiceFactory
 *
 */
public class OrganizationLocalServiceUtil {
	public static com.liferay.portal.model.Organization addOrganization(
		com.liferay.portal.model.Organization model)
		throws com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.addOrganization(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.Organization updateOrganization(
		com.liferay.portal.model.Organization model)
		throws com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.updateOrganization(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.afterPropertiesSet();
	}

	public static void addGroupOrganizations(long groupId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.addGroupOrganizations(groupId, organizationIds);
	}

	public static com.liferay.portal.model.Organization addOrganization(
		long userId, long parentOrganizationId, java.lang.String name,
		int type, boolean recursable, long regionId, long countryId,
		int statusId, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.addOrganization(userId,
			parentOrganizationId, name, type, recursable, regionId, countryId,
			statusId, comments);
	}

	public static void addOrganizationResources(long userId,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.addOrganizationResources(userId, organization);
	}

	public static void addPasswordPolicyOrganizations(long passwordPolicyId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.addPasswordPolicyOrganizations(passwordPolicyId,
			organizationIds);
	}

	public static void deleteOrganization(long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.deleteOrganization(organizationId);
	}

	public static void deleteOrganization(
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.deleteOrganization(organization);
	}

	public static java.util.List getGroupOrganizations(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getGroupOrganizations(groupId);
	}

	public static java.util.List getManageableOrganizations(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getManageableOrganizations(userId);
	}

	public static com.liferay.portal.model.Organization getOrganization(
		long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrganization(organizationId);
	}

	public static com.liferay.portal.model.Organization getOrganization(
		long companyId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrganization(companyId, name);
	}

	public static long getOrganizationId(long companyId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrganizationId(companyId, name);
	}

	public static java.util.List getOrganizations(long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getOrganizations(organizationIds);
	}

	public static java.util.List getParentOrganizations(long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getParentOrganizations(organizationId);
	}

	public static java.util.List getSuborganizations(
		java.util.List organizations) throws com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getSuborganizations(organizations);
	}

	public static java.util.List getSubsetOrganizations(
		java.util.List allOrganizations, java.util.List availableOrganizations)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getSubsetOrganizations(allOrganizations,
			availableOrganizations);
	}

	public static java.util.List getUserOrganizations(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserOrganizations(userId);
	}

	public static int getUserOrganizationsCount(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.getUserOrganizationsCount(userId);
	}

	public static boolean hasGroupOrganization(long groupId, long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.hasGroupOrganization(groupId,
			organizationId);
	}

	public static boolean hasUserOrganization(long userId, long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.hasUserOrganization(userId,
			organizationId);
	}

	public static boolean hasPasswordPolicyOrganization(long passwordPolicyId,
		long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.hasPasswordPolicyOrganization(passwordPolicyId,
			organizationId);
	}

	public static java.util.List search(long companyId,
		long parentOrganizationId, java.lang.String keywords, int type,
		java.lang.Long regionId, java.lang.Long countryId,
		java.util.LinkedHashMap params, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.search(companyId, parentOrganizationId,
			keywords, type, regionId, countryId, params, begin, end);
	}

	public static java.util.List search(long companyId,
		long parentOrganizationId, java.lang.String keywords, int type,
		java.lang.Long regionId, java.lang.Long countryId,
		java.util.LinkedHashMap params, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.search(companyId, parentOrganizationId,
			keywords, type, regionId, countryId, params, begin, end, obc);
	}

	public static java.util.List search(long companyId,
		long parentOrganizationId, java.lang.String name, int type,
		java.lang.String street, java.lang.String city, java.lang.String zip,
		java.lang.Long regionId, java.lang.Long countryId,
		java.util.LinkedHashMap params, boolean andOperator, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.search(companyId, parentOrganizationId,
			name, type, street, city, zip, regionId, countryId, params,
			andOperator, begin, end);
	}

	public static java.util.List search(long companyId,
		long parentOrganizationId, java.lang.String name, int type,
		java.lang.String street, java.lang.String city, java.lang.String zip,
		java.lang.Long regionId, java.lang.Long countryId,
		java.util.LinkedHashMap params, boolean andOperator, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.search(companyId, parentOrganizationId,
			name, type, street, city, zip, regionId, countryId, params,
			andOperator, begin, end, obc);
	}

	public static int searchCount(long companyId, long parentOrganizationId,
		java.lang.String keywords, int type, java.lang.Long regionId,
		java.lang.Long countryId, java.util.LinkedHashMap params)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.searchCount(companyId,
			parentOrganizationId, keywords, type, regionId, countryId, params);
	}

	public static int searchCount(long companyId, long parentOrganizationId,
		java.lang.String name, int type, java.lang.String street,
		java.lang.String city, java.lang.String zip, java.lang.Long regionId,
		java.lang.Long countryId, java.util.LinkedHashMap params,
		boolean andOperator)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.searchCount(companyId,
			parentOrganizationId, name, type, street, city, zip, regionId,
			countryId, params, andOperator);
	}

	public static void setGroupOrganizations(long groupId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.setGroupOrganizations(groupId, organizationIds);
	}

	public static void unsetGroupOrganizations(long groupId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.unsetGroupOrganizations(groupId,
			organizationIds);
	}

	public static void unsetPasswordPolicyOrganizations(long passwordPolicyId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		organizationLocalService.unsetPasswordPolicyOrganizations(passwordPolicyId,
			organizationIds);
	}

	public static com.liferay.portal.model.Organization updateOrganization(
		long companyId, long organizationId, long parentOrganizationId,
		java.lang.String name, int type, boolean recursable, long regionId,
		long countryId, int statusId, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrganizationLocalService organizationLocalService = OrganizationLocalServiceFactory.getService();

		return organizationLocalService.updateOrganization(companyId,
			organizationId, parentOrganizationId, name, type, recursable,
			regionId, countryId, statusId, comments);
	}
}