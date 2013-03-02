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
 * <a href="PluginSettingLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PluginSettingLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PluginSettingLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PluginSettingLocalService
 * @see com.liferay.portal.service.PluginSettingLocalServiceFactory
 *
 */
public class PluginSettingLocalServiceUtil {
	public static com.liferay.portal.model.PluginSetting addPluginSetting(
		com.liferay.portal.model.PluginSetting model)
		throws com.liferay.portal.SystemException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.addPluginSetting(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portal.model.PluginSetting updatePluginSetting(
		com.liferay.portal.model.PluginSetting model)
		throws com.liferay.portal.SystemException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.updatePluginSetting(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.afterPropertiesSet();
	}

	public static void checkPermission(long userId, java.lang.String pluginId,
		java.lang.String pluginType) throws com.liferay.portal.PortalException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		pluginSettingLocalService.checkPermission(userId, pluginId, pluginType);
	}

	public static com.liferay.portal.model.PluginSetting getDefaultPluginSetting() {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getDefaultPluginSetting();
	}

	public static com.liferay.portal.model.PluginSetting getPluginSetting(
		long companyId, java.lang.String pluginId, java.lang.String pluginType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.getPluginSetting(companyId, pluginId,
			pluginType);
	}

	public static boolean hasPermission(long userId, java.lang.String pluginId,
		java.lang.String pluginType) {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.hasPermission(userId, pluginId,
			pluginType);
	}

	public static com.liferay.portal.model.PluginSetting updatePluginSetting(
		long companyId, java.lang.String pluginId, java.lang.String pluginType,
		java.lang.String roles, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PluginSettingLocalService pluginSettingLocalService = PluginSettingLocalServiceFactory.getService();

		return pluginSettingLocalService.updatePluginSetting(companyId,
			pluginId, pluginType, roles, active);
	}
}