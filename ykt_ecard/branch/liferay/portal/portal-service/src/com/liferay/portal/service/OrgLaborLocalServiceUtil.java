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
 * <a href="OrgLaborLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.OrgLaborLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.OrgLaborLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.OrgLaborLocalService
 * @see com.liferay.portal.service.OrgLaborLocalServiceFactory
 *
 */
public class OrgLaborLocalServiceUtil {
	public static com.liferay.portal.model.OrgLabor addOrgLabor(
		com.liferay.portal.model.OrgLabor model)
		throws com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.addOrgLabor(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.OrgLabor updateOrgLabor(
		com.liferay.portal.model.OrgLabor model)
		throws com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.updateOrgLabor(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.OrgLabor addOrgLabor(
		long organizationId, int typeId, int sunOpen, int sunClose,
		int monOpen, int monClose, int tueOpen, int tueClose, int wedOpen,
		int wedClose, int thuOpen, int thuClose, int friOpen, int friClose,
		int satOpen, int satClose)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.addOrgLabor(organizationId, typeId,
			sunOpen, sunClose, monOpen, monClose, tueOpen, tueClose, wedOpen,
			wedClose, thuOpen, thuClose, friOpen, friClose, satOpen, satClose);
	}

	public static void deleteOrgLabor(long orgLaborId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		orgLaborLocalService.deleteOrgLabor(orgLaborId);
	}

	public static com.liferay.portal.model.OrgLabor getOrgLabor(long orgLaborId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrgLabor(orgLaborId);
	}

	public static java.util.List getOrgLabors(long organizationId)
		throws com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.getOrgLabors(organizationId);
	}

	public static com.liferay.portal.model.OrgLabor updateOrgLabor(
		long orgLaborId, int sunOpen, int sunClose, int monOpen, int monClose,
		int tueOpen, int tueClose, int wedOpen, int wedClose, int thuOpen,
		int thuClose, int friOpen, int friClose, int satOpen, int satClose)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		OrgLaborLocalService orgLaborLocalService = OrgLaborLocalServiceFactory.getService();

		return orgLaborLocalService.updateOrgLabor(orgLaborId, sunOpen,
			sunClose, monOpen, monClose, tueOpen, tueClose, wedOpen, wedClose,
			thuOpen, thuClose, friOpen, friClose, satOpen, satClose);
	}
}