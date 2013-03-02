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
 * <a href="PasswordPolicyRelLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PasswordPolicyRelLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PasswordPolicyRelLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PasswordPolicyRelLocalService
 * @see com.liferay.portal.service.PasswordPolicyRelLocalServiceFactory
 *
 */
public class PasswordPolicyRelLocalServiceUtil {
	public static com.liferay.portal.model.PasswordPolicyRel addPasswordPolicyRel(
		com.liferay.portal.model.PasswordPolicyRel model)
		throws com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.addPasswordPolicyRel(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portal.model.PasswordPolicyRel updatePasswordPolicyRel(
		com.liferay.portal.model.PasswordPolicyRel model)
		throws com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.updatePasswordPolicyRel(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.afterPropertiesSet();
	}

	public static com.liferay.portal.model.PasswordPolicyRel addPasswordPolicyRel(
		long passwordPolicyId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.addPasswordPolicyRel(passwordPolicyId,
			className, classPK);
	}

	public static void addPasswordPolicyRels(long passwordPolicyId,
		java.lang.String className, long[] classPKs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.addPasswordPolicyRels(passwordPolicyId,
			className, classPKs);
	}

	public static void deletePasswordPolicyRel(java.lang.String className,
		long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.deletePasswordPolicyRel(className, classPK);
	}

	public static void deletePasswordPolicyRel(long passwordPolicyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.deletePasswordPolicyRel(passwordPolicyId,
			className, classPK);
	}

	public static void deletePasswordPolicyRels(long passwordPolicyId,
		java.lang.String className, long[] classPKs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		passwordPolicyRelLocalService.deletePasswordPolicyRels(passwordPolicyId,
			className, classPKs);
	}

	public static com.liferay.portal.model.PasswordPolicyRel getPasswordPolicyRel(
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPasswordPolicyRel(className,
			classPK);
	}

	public static com.liferay.portal.model.PasswordPolicyRel getPasswordPolicyRel(
		long passwordPolicyId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.getPasswordPolicyRel(passwordPolicyId,
			className, classPK);
	}

	public static boolean hasPasswordPolicyRel(long passwordPolicyId,
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		PasswordPolicyRelLocalService passwordPolicyRelLocalService = PasswordPolicyRelLocalServiceFactory.getService();

		return passwordPolicyRelLocalService.hasPasswordPolicyRel(passwordPolicyId,
			className, classPK);
	}
}