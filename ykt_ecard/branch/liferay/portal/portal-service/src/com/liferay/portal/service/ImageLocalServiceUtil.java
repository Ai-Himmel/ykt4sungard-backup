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
 * <a href="ImageLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.ImageLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.ImageLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.ImageLocalService
 * @see com.liferay.portal.service.ImageLocalServiceFactory
 *
 */
public class ImageLocalServiceUtil {
	public static com.liferay.portal.model.Image addImage(
		com.liferay.portal.model.Image model)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.addImage(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portal.model.Image updateImage(
		com.liferay.portal.model.Image model)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.updateImage(model);
	}

	public static com.liferay.portal.service.persistence.AccountPersistence getAccountPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getAccountPersistence();
	}

	public static void setAccountPersistence(
		com.liferay.portal.service.persistence.AccountPersistence accountPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setAccountPersistence(accountPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.AddressPersistence getAddressPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getAddressPersistence();
	}

	public static void setAddressPersistence(
		com.liferay.portal.service.persistence.AddressPersistence addressPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setAddressPersistence(addressPersistence);
	}

	public static com.liferay.portal.service.persistence.ClassNamePersistence getClassNamePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getClassNamePersistence();
	}

	public static void setClassNamePersistence(
		com.liferay.portal.service.persistence.ClassNamePersistence classNamePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setClassNamePersistence(classNamePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.ContactPersistence getContactPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getContactPersistence();
	}

	public static void setContactPersistence(
		com.liferay.portal.service.persistence.ContactPersistence contactPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setContactPersistence(contactPersistence);
	}

	public static com.liferay.portal.service.persistence.CountryPersistence getCountryPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getCountryPersistence();
	}

	public static void setCountryPersistence(
		com.liferay.portal.service.persistence.CountryPersistence countryPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setCountryPersistence(countryPersistence);
	}

	public static com.liferay.portal.service.persistence.EmailAddressPersistence getEmailAddressPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getEmailAddressPersistence();
	}

	public static void setEmailAddressPersistence(
		com.liferay.portal.service.persistence.EmailAddressPersistence emailAddressPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setEmailAddressPersistence(emailAddressPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.ImagePersistence getImagePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getImagePersistence();
	}

	public static void setImagePersistence(
		com.liferay.portal.service.persistence.ImagePersistence imagePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setImagePersistence(imagePersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutSetPersistence getLayoutSetPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getLayoutSetPersistence();
	}

	public static void setLayoutSetPersistence(
		com.liferay.portal.service.persistence.LayoutSetPersistence layoutSetPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setLayoutSetPersistence(layoutSetPersistence);
	}

	public static com.liferay.portal.service.persistence.ListTypePersistence getListTypePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getListTypePersistence();
	}

	public static void setListTypePersistence(
		com.liferay.portal.service.persistence.ListTypePersistence listTypePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setListTypePersistence(listTypePersistence);
	}

	public static com.liferay.portal.service.persistence.MembershipRequestPersistence getMembershipRequestPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getMembershipRequestPersistence();
	}

	public static void setMembershipRequestPersistence(
		com.liferay.portal.service.persistence.MembershipRequestPersistence membershipRequestPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setMembershipRequestPersistence(membershipRequestPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionPersistence getOrgGroupPermissionPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getOrgGroupPermissionPersistence();
	}

	public static void setOrgGroupPermissionPersistence(
		com.liferay.portal.service.persistence.OrgGroupPermissionPersistence orgGroupPermissionPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setOrgGroupPermissionPersistence(orgGroupPermissionPersistence);
	}

	public static com.liferay.portal.service.persistence.OrgGroupPermissionFinder getOrgGroupPermissionFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getOrgGroupPermissionFinder();
	}

	public static void setOrgGroupPermissionFinder(
		com.liferay.portal.service.persistence.OrgGroupPermissionFinder orgGroupPermissionFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setOrgGroupPermissionFinder(orgGroupPermissionFinder);
	}

	public static com.liferay.portal.service.persistence.OrgGroupRolePersistence getOrgGroupRolePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getOrgGroupRolePersistence();
	}

	public static void setOrgGroupRolePersistence(
		com.liferay.portal.service.persistence.OrgGroupRolePersistence orgGroupRolePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setOrgGroupRolePersistence(orgGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.OrgLaborPersistence getOrgLaborPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getOrgLaborPersistence();
	}

	public static void setOrgLaborPersistence(
		com.liferay.portal.service.persistence.OrgLaborPersistence orgLaborPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setOrgLaborPersistence(orgLaborPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyPersistence getPasswordPolicyPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPasswordPolicyPersistence();
	}

	public static void setPasswordPolicyPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyPersistence passwordPolicyPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPasswordPolicyPersistence(passwordPolicyPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyFinder getPasswordPolicyFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPasswordPolicyFinder();
	}

	public static void setPasswordPolicyFinder(
		com.liferay.portal.service.persistence.PasswordPolicyFinder passwordPolicyFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPasswordPolicyFinder(passwordPolicyFinder);
	}

	public static com.liferay.portal.service.persistence.PasswordPolicyRelPersistence getPasswordPolicyRelPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPasswordPolicyRelPersistence();
	}

	public static void setPasswordPolicyRelPersistence(
		com.liferay.portal.service.persistence.PasswordPolicyRelPersistence passwordPolicyRelPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPasswordPolicyRelPersistence(passwordPolicyRelPersistence);
	}

	public static com.liferay.portal.service.persistence.PasswordTrackerPersistence getPasswordTrackerPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPasswordTrackerPersistence();
	}

	public static void setPasswordTrackerPersistence(
		com.liferay.portal.service.persistence.PasswordTrackerPersistence passwordTrackerPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPasswordTrackerPersistence(passwordTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionPersistence getPermissionPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPermissionPersistence();
	}

	public static void setPermissionPersistence(
		com.liferay.portal.service.persistence.PermissionPersistence permissionPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPermissionPersistence(permissionPersistence);
	}

	public static com.liferay.portal.service.persistence.PermissionFinder getPermissionFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPermissionFinder();
	}

	public static void setPermissionFinder(
		com.liferay.portal.service.persistence.PermissionFinder permissionFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPermissionFinder(permissionFinder);
	}

	public static com.liferay.portal.service.persistence.PermissionUserFinder getPermissionUserFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPermissionUserFinder();
	}

	public static void setPermissionUserFinder(
		com.liferay.portal.service.persistence.PermissionUserFinder permissionUserFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPermissionUserFinder(permissionUserFinder);
	}

	public static com.liferay.portal.service.persistence.PhonePersistence getPhonePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPhonePersistence();
	}

	public static void setPhonePersistence(
		com.liferay.portal.service.persistence.PhonePersistence phonePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPhonePersistence(phonePersistence);
	}

	public static com.liferay.portal.service.persistence.PluginSettingPersistence getPluginSettingPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPluginSettingPersistence();
	}

	public static void setPluginSettingPersistence(
		com.liferay.portal.service.persistence.PluginSettingPersistence pluginSettingPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPluginSettingPersistence(pluginSettingPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPersistence getPortletPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPortletPersistence();
	}

	public static void setPortletPersistence(
		com.liferay.portal.service.persistence.PortletPersistence portletPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPortletPersistence(portletPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.RegionPersistence getRegionPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getRegionPersistence();
	}

	public static void setRegionPersistence(
		com.liferay.portal.service.persistence.RegionPersistence regionPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setRegionPersistence(regionPersistence);
	}

	public static com.liferay.portal.service.persistence.ReleasePersistence getReleasePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getReleasePersistence();
	}

	public static void setReleasePersistence(
		com.liferay.portal.service.persistence.ReleasePersistence releasePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setReleasePersistence(releasePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.ResourceCodePersistence getResourceCodePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getResourceCodePersistence();
	}

	public static void setResourceCodePersistence(
		com.liferay.portal.service.persistence.ResourceCodePersistence resourceCodePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setResourceCodePersistence(resourceCodePersistence);
	}

	public static com.liferay.portal.service.persistence.RolePersistence getRolePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getRolePersistence();
	}

	public static void setRolePersistence(
		com.liferay.portal.service.persistence.RolePersistence rolePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setRolePersistence(rolePersistence);
	}

	public static com.liferay.portal.service.persistence.RoleFinder getRoleFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getRoleFinder();
	}

	public static void setRoleFinder(
		com.liferay.portal.service.persistence.RoleFinder roleFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setRoleFinder(roleFinder);
	}

	public static com.liferay.portal.service.persistence.ServiceComponentPersistence getServiceComponentPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getServiceComponentPersistence();
	}

	public static void setServiceComponentPersistence(
		com.liferay.portal.service.persistence.ServiceComponentPersistence serviceComponentPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setServiceComponentPersistence(serviceComponentPersistence);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupPersistence getUserGroupPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserGroupPersistence();
	}

	public static void setUserGroupPersistence(
		com.liferay.portal.service.persistence.UserGroupPersistence userGroupPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserGroupPersistence(userGroupPersistence);
	}

	public static com.liferay.portal.service.persistence.UserGroupFinder getUserGroupFinder() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserGroupFinder();
	}

	public static void setUserGroupFinder(
		com.liferay.portal.service.persistence.UserGroupFinder userGroupFinder) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserGroupFinder(userGroupFinder);
	}

	public static com.liferay.portal.service.persistence.UserGroupRolePersistence getUserGroupRolePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserGroupRolePersistence();
	}

	public static void setUserGroupRolePersistence(
		com.liferay.portal.service.persistence.UserGroupRolePersistence userGroupRolePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserGroupRolePersistence(userGroupRolePersistence);
	}

	public static com.liferay.portal.service.persistence.UserIdMapperPersistence getUserIdMapperPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserIdMapperPersistence();
	}

	public static void setUserIdMapperPersistence(
		com.liferay.portal.service.persistence.UserIdMapperPersistence userIdMapperPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserIdMapperPersistence(userIdMapperPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPersistence getUserTrackerPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserTrackerPersistence();
	}

	public static void setUserTrackerPersistence(
		com.liferay.portal.service.persistence.UserTrackerPersistence userTrackerPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserTrackerPersistence(userTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.UserTrackerPathPersistence getUserTrackerPathPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getUserTrackerPathPersistence();
	}

	public static void setUserTrackerPathPersistence(
		com.liferay.portal.service.persistence.UserTrackerPathPersistence userTrackerPathPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setUserTrackerPathPersistence(userTrackerPathPersistence);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portal.service.persistence.WebsitePersistence getWebsitePersistence() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getWebsitePersistence();
	}

	public static void setWebsitePersistence(
		com.liferay.portal.service.persistence.WebsitePersistence websitePersistence) {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.setWebsitePersistence(websitePersistence);
	}

	public static void afterPropertiesSet() {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.afterPropertiesSet();
	}

	public static void deleteImage(long imageId)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		imageLocalService.deleteImage(imageId);
	}

	public static com.liferay.portal.model.Image getImage(long imageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getImage(imageId);
	}

	public static java.util.List getImages()
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getImages();
	}

	public static java.util.List getImages(int begin, int end)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getImages(begin, end);
	}

	public static java.util.List getImagesBySize(int size)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.getImagesBySize(size);
	}

	public static com.liferay.portal.model.Image updateImage(long imageId,
		byte[] bytes, java.lang.String type, int height, int width, int size)
		throws com.liferay.portal.SystemException {
		ImageLocalService imageLocalService = ImageLocalServiceFactory.getService();

		return imageLocalService.updateImage(imageId, bytes, type, height,
			width, size);
	}
}