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
 * <a href="PortletPreferencesLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PortletPreferencesLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PortletPreferencesLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PortletPreferencesLocalService
 * @see com.liferay.portal.service.PortletPreferencesLocalServiceFactory
 *
 */
public class PortletPreferencesLocalServiceUtil {
	public static com.liferay.portal.model.PortletPreferences addPortletPreferences(
		com.liferay.portal.model.PortletPreferences model)
		throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.addPortletPreferences(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.PortletPreferences updatePortletPreferences(
		com.liferay.portal.model.PortletPreferences model)
		throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.updatePortletPreferences(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.afterPropertiesSet();
	}

	public static void deletePortletPreferences(long portletPreferencesId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.deletePortletPreferences(portletPreferencesId);
	}

	public static void deletePortletPreferences(long ownerId, int ownerType,
		long plid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.deletePortletPreferences(ownerId,
			ownerType, plid);
	}

	public static void deletePortletPreferences(long ownerId, int ownerType,
		long plid, java.lang.String portletId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		portletPreferencesLocalService.deletePortletPreferences(ownerId,
			ownerType, plid, portletId);
	}

	public static javax.portlet.PortletPreferences getDefaultPreferences(
		long companyId, java.lang.String portletId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getDefaultPreferences(companyId,
			portletId);
	}

	public static java.util.List getPortletPreferences()
		throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferences();
	}

	public static java.util.List getPortletPreferences(long plid)
		throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferences(plid);
	}

	public static java.util.List getPortletPreferences(long plid,
		java.lang.String portletId) throws com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferences(plid,
			portletId);
	}

	public static java.util.List getPortletPreferences(long ownerId,
		int ownerType, long plid)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferences(ownerId,
			ownerType, plid);
	}

	public static com.liferay.portal.model.PortletPreferences getPortletPreferences(
		long ownerId, int ownerType, long plid, java.lang.String portletId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPortletPreferences(ownerId,
			ownerType, plid, portletId);
	}

	public static javax.portlet.PortletPreferences getPreferences(
		com.liferay.portal.model.PortletPreferencesIds portletPreferencesIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPreferences(portletPreferencesIds);
	}

	public static javax.portlet.PortletPreferences getPreferences(
		long companyId, long ownerId, int ownerType, long plid,
		java.lang.String portletId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPreferences(companyId,
			ownerId, ownerType, plid, portletId);
	}

	public static javax.portlet.PortletPreferences getPreferences(
		long companyId, long ownerId, int ownerType, long plid,
		java.lang.String portletId, java.lang.String defaultPreferences)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.getPreferences(companyId,
			ownerId, ownerType, plid, portletId, defaultPreferences);
	}

	public static com.liferay.portal.model.PortletPreferences updatePreferences(
		long ownerId, int ownerType, long plid, java.lang.String portletId,
		javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PortletPreferencesLocalService portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getService();

		return portletPreferencesLocalService.updatePreferences(ownerId,
			ownerType, plid, portletId, prefs);
	}
}