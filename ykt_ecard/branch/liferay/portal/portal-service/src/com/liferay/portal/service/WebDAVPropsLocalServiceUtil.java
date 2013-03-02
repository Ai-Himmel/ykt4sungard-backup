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
 * <a href="WebDAVPropsLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.WebDAVPropsLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.WebDAVPropsLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.WebDAVPropsLocalService
 * @see com.liferay.portal.service.WebDAVPropsLocalServiceFactory
 *
 */
public class WebDAVPropsLocalServiceUtil {
	public static com.liferay.portal.model.WebDAVProps addWebDAVProps(
		com.liferay.portal.model.WebDAVProps model)
		throws com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.addWebDAVProps(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.WebDAVProps updateWebDAVProps(
		com.liferay.portal.model.WebDAVProps model)
		throws com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.updateWebDAVProps(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.afterPropertiesSet();
	}

	public static void deleteWebDAVProps(java.lang.String className,
		long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.deleteWebDAVProps(className, classPK);
	}

	public static com.liferay.portal.model.WebDAVProps getWebDAVProps(
		long companyId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		return webDAVPropsLocalService.getWebDAVProps(companyId, className,
			classPK);
	}

	public static void storeWebDAVProps(
		com.liferay.portal.model.WebDAVProps webDavProps)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WebDAVPropsLocalService webDAVPropsLocalService = WebDAVPropsLocalServiceFactory.getService();

		webDAVPropsLocalService.storeWebDAVProps(webDavProps);
	}
}