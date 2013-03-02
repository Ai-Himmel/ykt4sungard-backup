<%
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
%>

<%@ include file="/html/extportlet/init.jsp" %>

<%@ page import="com.liferay.portal.AccountNameException" %>
<%@ page import="com.liferay.portal.AddressCityException" %>
<%@ page import="com.liferay.portal.AddressStreetException" %>
<%@ page import="com.liferay.portal.AddressZipException" %>
<%@ page import="com.liferay.portal.CompanyMxException" %>
<%@ page import="com.liferay.portal.CompanyVirtualHostException" %>
<%@ page import="com.liferay.portal.ContactFirstNameException" %>
<%@ page import="com.liferay.portal.ContactLastNameException" %>
<%@ page import="com.liferay.portal.DuplicateOrganizationException" %>
<%@ page import="com.liferay.portal.DuplicateRoleException" %>
<%@ page import="com.liferay.portal.DuplicateUserEmailAddressException" %>
<%@ page import="com.liferay.portal.DuplicateUserGroupException" %>
<%@ page import="com.liferay.portal.DuplicateUserIdException" %>
<%@ page import="com.liferay.portal.DuplicateUserScreenNameException" %>
<%@ page import="com.liferay.portal.EmailAddressException" %>
<%@ page import="com.liferay.portal.NoSuchListTypeException" %>
<%@ page import="com.liferay.portal.NoSuchCountryException" %>
<%@ page import="com.liferay.portal.NoSuchOrganizationException" %>
<%@ page import="com.liferay.portal.NoSuchRegionException" %>
<%@ page import="com.liferay.portal.NoSuchRoleException" %>
<%@ page import="com.liferay.portal.NoSuchUserGroupException" %>
<%@ page import="com.liferay.portal.NoSuchUserException" %>
<%@ page import="com.liferay.portal.OrganizationNameException" %>
<%@ page import="com.liferay.portal.OrganizationParentException" %>
<%@ page import="com.liferay.portal.PasswordPolicyNameException" %>
<%@ page import="com.liferay.portal.PhoneNumberException" %>
<%@ page import="com.liferay.portal.RequiredOrganizationException" %>
<%@ page import="com.liferay.portal.RequiredRoleException" %>
<%@ page import="com.liferay.portal.RequiredUserException" %>
<%@ page import="com.liferay.portal.RequiredUserGroupException" %>
<%@ page import="com.liferay.portal.ReservedUserIdException" %>
<%@ page import="com.liferay.portal.ReservedUserEmailAddressException" %>
<%@ page import="com.liferay.portal.ReservedUserScreenNameException" %>
<%@ page import="com.liferay.portal.RoleNameException" %>
<%@ page import="com.liferay.portal.UserEmailAddressException" %>
<%@ page import="com.liferay.portal.UserGroupNameException" %>
<%@ page import="com.liferay.portal.UserIdException" %>
<%@ page import="com.liferay.portal.UserPasswordException" %>
<%@ page import="com.liferay.portal.UserPortraitException" %>
<%@ page import="com.liferay.portal.UserScreenNameException" %>
<%@ page import="com.liferay.portal.UserSmsException" %>
<%@ page import="com.liferay.portal.WebsiteURLException" %>
<%@ page import="com.liferay.portal.kernel.plugin.PluginPackage" %>
<%@ page import="com.liferay.portal.security.ldap.PortalLDAPUtil" %>
<%@ page import="com.liferay.portal.security.permission.ResourceActionsUtil" %>
<%@ page import="com.liferay.portal.security.permission.comparator.ActionComparator" %>
<%@ page import="com.liferay.portal.security.permission.comparator.ModelResourceComparator" %>
<%@ page import="com.liferay.portal.service.impl.ThemeLocalUtil" %>
<%@ page import="com.liferay.portal.service.permission.OrganizationPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.PasswordPolicyPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.PortalPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.RolePermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.UserGroupPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.UserPermissionUtil" %>
<%@ page import="com.liferay.portal.servlet.PortalSessionContext" %>
<%@ page import="com.liferay.portal.util.LiveUsers" %>
<%@ page import="com.liferay.portal.util.comparator.UserTrackerModifiedDateComparator" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupDisplayTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupPermissionChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupRoleChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupSearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupSearchTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.OrganizationDisplayTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.OrganizationPasswordPolicyChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.OrganizationRoleChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.OrganizationSearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.OrganizationSearchTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.PasswordPolicyDisplayTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.PasswordPolicySearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.PasswordPolicySearchTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.RoleDisplayTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.RoleSearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.RoleSearchTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.RoleUserChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserDisplayTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserGroupDisplayTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserGroupRoleChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserGroupSearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserGroupSearchTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserOrganizationChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserPasswordPolicyChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserRoleChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserSearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserSearchTerms" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.UserUserGroupChecker" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.util.EnterpriseAdminUtil" %>
<%@ page import="com.liferay.util.ldap.LDAPUtil" %>

<%@ page import="javax.naming.NamingEnumeration" %>
<%@ page import="javax.naming.directory.Attribute" %>
<%@ page import="javax.naming.directory.Attributes" %>
<%@ page import="javax.naming.directory.SearchResult" %>
<%@ page import="javax.naming.ldap.LdapContext" %>
<%@ taglib uri="/WEB-INF/tld/extremecomponents.tld" prefix="ec"%>
<%@ taglib uri="/WEB-INF/tld/cewolf-1.1.tld" prefix="cewolf"%>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>

<%@page import="com.kingstargroup.ecard.hibernate.shop.TShop"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@page import="com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil"%>
        
<script type="text/javascript" src="/html/extjs/My97DatePicker/WdatePicker.js"></script>
<link href="/html/extcommon/styles/extremecomponents.css" rel="stylesheet" type="text/css" />
<link href="/html/extcommon/styles/displaytag/alternative.css" rel="stylesheet" type="text/css" />