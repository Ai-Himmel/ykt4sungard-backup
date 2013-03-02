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

package com.liferay.portal.util;

import java.util.Properties;

import com.germinus.easyconf.ComponentProperties;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.util.ExtPropertiesLoader;

/**
 * <a href="PropsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PropsUtil {

	static {
		InitUtil.init();
	}

	// Portal Context

	public static final String PORTAL_CTX = "portal.ctx";

	// TCK

	public static final String TCK_URL = "tck.url";

	// Schema

	public static final String SCHEMA_RUN_ENABLED = "schema.run.enabled";

	public static final String SCHEMA_RUN_MINIMAL = "schema.run.minimal";

	// Upgrade

	public static final String UPGRADE_PROCESSES = "upgrade.processes";

	// Verify

	public static final String VERIFY_PROCESSES = "verify.processes";

	public static final String VERIFY_FREQUENCY = "verify.frequency";

	// Auto Deploy

	public static final String AUTO_DEPLOY_LISTENERS = "auto.deploy.listeners";

	public static final String AUTO_DEPLOY_ENABLED = "auto.deploy.enabled";

	public static final String AUTO_DEPLOY_DEPLOY_DIR = "auto.deploy.deploy.dir";

	public static final String AUTO_DEPLOY_DEST_DIR = "auto.deploy.dest.dir";

	public static final String AUTO_DEPLOY_DEFAULT_DEST_DIR = "auto.deploy.default.dest.dir";

	public static final String AUTO_DEPLOY_INTERVAL = "auto.deploy.interval";

	public static final String AUTO_DEPLOY_BLACKLIST_THRESHOLD = "auto.deploy.blacklist.threshold";

	public static final String AUTO_DEPLOY_UNPACK_WAR = "auto.deploy.unpack.war";

	public static final String AUTO_DEPLOY_CUSTOM_PORTLET_XML = "auto.deploy.custom.portlet.xml";

	public static final String AUTO_DEPLOY_JBOSS_PREFIX = "auto.deploy.jboss.prefix";

	public static final String AUTO_DEPLOY_TOMCAT_CONF_DIR = "auto.deploy.tomcat.conf.dir";

	public static final String AUTO_DEPLOY_TOMCAT_DEST_DIR = "auto.deploy.tomcat.dest.dir";

	public static final String AUTO_DEPLOY_TOMCAT_LIB_DIR = "auto.deploy.tomcat.lib.dir";

	public static final String LIBRARY_DOWNLOAD_URL = "library.download.url.";

	// Hot Deploy

	public static final String HOT_DEPLOY_LISTENERS = "hot.deploy.listeners";

	// Plugin

	public static final String PLUGIN_TYPES = "plugin.types";

	public static final String PLUGIN_REPOSITORIES_TRUSTED = "plugin.repositories.trusted";

	public static final String PLUGIN_REPOSITORIES_UNTRUSTED = "plugin.repositories.untrusted";

	public static final String PLUGIN_NOTIFICATIONS_ENABLED = "plugin.notifications.enabled";

	public static final String PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED = "plugin.notifications.packages.ignored";

	// Portlet

	public static final String PORTLET_VIRTUAL_PATH = "portlet.virtual.path";

	// Theme

	public static final String THEME_CSS_FAST_LOAD = "theme.css.fast.load";

	public static final String THEME_VIRTUAL_PATH = "theme.virtual.path";

	public static final String THEME_LOADER_STORAGE_PATH = "theme.loader.storage.path";

	public static final String THEME_LOADER_NEW_THEME_ID_ON_IMPORT = "theme.loader.new.theme.id.on.import";

	// Resource Actions

	public static final String RESOURCE_ACTIONS_CONFIGS = "resource.actions.configs";

	// Model Hints

	public static final String MODEL_HINTS_CONFIGS = "model.hints.configs";

	// Spring

	public static final String SPRING_CONFIGS = "spring.configs";

	public static final String SPRING_HIBERNATE_DATA_SOURCE = "spring.hibernate.data.source";

	public static final String SPRING_HIBERNATE_SESSION_FACTORY = "spring.hibernate.session.factory";

	// Hibernate

	public static final String HIBERNATE_CONFIGS = "hibernate.configs";

	public static final String HIBERNATE_DIALECT = "hibernate.dialect.";

	// Custom SQL

	public static final String CUSTOM_SQL_CONFIGS = "custom.sql.configs";

	public static final String CUSTOM_SQL_FUNCTION_ISNULL = "custom.sql.function.isnull";

	public static final String CUSTOM_SQL_FUNCTION_ISNOTNULL = "custom.sql.function.isnotnull";

	// Ehcache

	public static final String EHCACHE_SINGLE_VM_CONFIG_LOCATION = "ehcache.single.vm.config.location";

	public static final String EHCACHE_MULTI_VM_CONFIG_LOCATION = "ehcache.multi.vm.config.location";

	// Commons Pool

	public static final String COMMONS_POOL_ENABLED = "commons.pool.enabled";

	// JavaScript

	public static final String JAVASCRIPT_FILES = "javascript.files";

	public static final String JAVASCRIPT_FAST_LOAD = "javascript.fast.load";

	public static final String JAVASCRIPT_LOG_ENABLED = "javascript.log.enabled";

	// SQL Data

    public static final String SQL_DATA_COM_LIFERAY_PORTAL_MODEL_COUNTRY_COUNTRY_ID = "sql.data.com.liferay.portal.model.Country.country.id";

	public static final String SQL_DATA_COM_LIFERAY_PORTAL_MODEL_REGION_REGION_ID = "sql.data.com.liferay.portal.model.Region.region.id";

	public static final String SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_ACCOUNT_ADDRESS = "sql.data.com.liferay.portal.model.ListType.account.address";

	public static final String SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_ACCOUNT_EMAIL_ADDRESS = "sql.data.com.liferay.portal.model.ListType.account.email.address";

	public static final String SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_CONTACT_EMAIL_ADDRESS = "sql.data.com.liferay.portal.model.ListType.contact.email.address";

	public static final String SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_ORGANIZATION_STATUS = "sql.data.com.liferay.portal.model.ListType.organization.status";

	// Company

	public static final String COMPANY_DEFAULT_WEB_ID = "company.default.web.id";

	public static final String COMPANY_SECURITY_AUTH_TYPE = "company.security.auth.type";

	public static final String COMPANY_SECURITY_AUTH_REQUIRES_HTTPS = "company.security.auth.requires.https";

	public static final String COMPANY_SECURITY_AUTO_LOGIN = "company.security.auto.login";

	public static final String COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE = "company.security.auto.login.max.age";

	public static final String COMPANY_SECURITY_SEND_PASSWORD = "company.security.send.password";

	public static final String COMPANY_SECURITY_STRANGERS = "company.security.strangers";

	public static final String COMPANY_SECURITY_STRANGERS_WITH_MX = "company.security.strangers.with.mx";

	public static final String COMPANY_SECURITY_STRANGERS_VERIFY = "company.security.strangers.verify";

	public static final String COMPANY_SECURITY_COMMUNITY_LOGO = "company.security.community.logo";

	// Users

	public static final String USERS_DELETE = "users.delete";

	public static final String USERS_SCREEN_NAME_ALWAYS_AUTOGENERATE = "users.screen.name.always.autogenerate";

	public static final String USERS_SCREEN_NAME_GENERATOR = "users.screen.name.generator";

	public static final String USERS_SCREEN_NAME_VALIDATOR = "users.screen.name.validator";

	public static final String USERS_IMAGE_MAX_SIZE = "users.image.max.size";

	// Groups and Roles

	public static final String SYSTEM_GROUPS = "system.groups";

	public static final String SYSTEM_ROLES = "system.roles";

	public static final String SYSTEM_COMMUNITY_ROLES = "system.community.roles";

	public static final String SYSTEM_ORGANIZATION_ROLES = "system.organization.roles";

	public static final String OMNIADMIN_USERS = "omniadmin.users";

	public static final String TERMS_OF_USE_REQUIRED = "terms.of.use.required";

	// Languages and Time Zones

	public static final String LOCALES = "locales";

	public static final String LOCALE_DEFAULT_REQUEST = "locale.default.request";

	public static final String TIME_ZONES = "time.zones";

	// Organizations

	public static final String ORGANIZATIONS_COUNTRY_REQUIRED = "organizations.country.required";

	// Look and Feel

	public static final String LOOK_AND_FEEL_MODIFIABLE = "look.and.feel.modifiable";

	public static final String DEFAULT_THEME_ID = "default.theme.id";

	public static final String DEFAULT_COLOR_SCHEME_ID = "default.color.scheme.id";

	public static final String DEFAULT_REGULAR_THEME_ID = "default.regular.theme.id";

	public static final String DEFAULT_REGULAR_COLOR_SCHEME_ID = "default.regular.color.scheme.id";

	public static final String DEFAULT_WAP_THEME_ID = "default.wap.theme.id";

	public static final String DEFAULT_WAP_COLOR_SCHEME_ID = "default.wap.color.scheme.id";

	public static final String THEME_SYNC_ON_GROUP = "theme.sync.on.group";

	// Request

	public static final String REQUEST_SHARED_ATTRIBUTES = "request.shared.attributes";

	// Session

	public static final String SESSION_TIMEOUT = "session.timeout";

	public static final String SESSION_TIMEOUT_WARNING = "session.timeout.warning";

	public static final String SESSION_TIMEOUT_AUTO_EXTEND = "session.timeout.auto.extend";

	public static final String SESSION_SHARED_ATTRIBUTES = "session.shared.attributes";

	public static final String SESSION_ENABLE_PERSISTENT_COOKIES = "session.enable.persistent.cookies";

	public static final String SESSION_COOKIE_DOMAIN = "session.cookie.domain";

	public static final String SESSION_ENABLE_PHISHING_PROTECTION = "session.enable.phishing.protection";

	public static final String SESSION_TEST_COOKIE_SUPPORT = "session.test.cookie.support";

	public static final String SESSION_DISABLED = "session.disabled";

	public static final String SERVLET_SESSION_CREATE_EVENTS = "servlet.session.create.events";

	public static final String SERVLET_SESSION_DESTROY_EVENTS = "servlet.session.destroy.events";

	public static final String SESSION_TRACKER_MEMORY_ENABLED = "session.tracker.memory.enabled";

	public static final String SESSION_TRACKER_PERSISTENCE_ENABLED = "session.tracker.persistence.enabled";

	public static final String SESSION_TRACKER_FRIENDLY_PATHS_ENABLED = "session.tracker.friendly.paths.enabled";

	public static final String SESSION_TRACKER_IGNORE_PATHS = "session.tracker.ignore.paths";

	// JAAS

	public static final String PORTAL_CONFIGURATION = "portal.configuration";

	public static final String PORTAL_JAAS_ENABLE = "portal.jaas.enable";

	public static final String PORTAL_JAAS_IMPL = "portal.jaas.impl";

	public static final String PORTAL_JAAS_STRICT_PASSWORD = "portal.jaas.strict.password";

	public static final String PORTAL_IMPERSONATION_ENABLE = "portal.impersonation.enable";

	// LDAP

	public static final String LDAP_FACTORY_INITIAL = "ldap.factory.initial";

	public static final String LDAP_BASE_PROVIDER_URL = "ldap.base.provider.url";

	public static final String LDAP_BASE_DN = "ldap.base.dn";

	public static final String LDAP_SECURITY_PRINCIPAL = "ldap.security.principal";

	public static final String LDAP_SECURITY_CREDENTIALS = "ldap.security.credentials";

	public static final String LDAP_AUTH_ENABLED = "ldap.auth.enabled";

	public static final String LDAP_AUTH_REQUIRED = "ldap.auth.required";

	public static final String LDAP_AUTH_METHOD = "ldap.auth.method";

	public static final String LDAP_AUTH_PASSWORD_ENCRYPTION_ALGORITHM = "ldap.auth.password.encryption.algorithm";

	public static final String LDAP_AUTH_PASSWORD_ENCRYPTION_ALGORITHM_TYPES = "ldap.auth.password.encryption.algorithm.types";

	public static final String LDAP_AUTH_SEARCH_FILTER = "ldap.auth.search.filter";

	public static final String LDAP_ATTRS_TRANSFORMER_IMPL = "ldap.attrs.transformer.impl";

	public static final String LDAP_USER_IMPL = "ldap.user.impl";

	public static final String LDAP_USER_DEFAULT_OBJECT_CLASSES = "ldap.user.default.object.classes";

	public static final String LDAP_USER_MAPPINGS = "ldap.user.mappings";

	public static final String LDAP_GROUP_MAPPINGS = "ldap.group.mappings";

	public static final String LDAP_IMPORT_ENABLED = "ldap.import.enabled";

	public static final String LDAP_IMPORT_ON_STARTUP = "ldap.import.on.startup";

	public static final String LDAP_IMPORT_INTERVAL = "ldap.import.interval";

	public static final String LDAP_IMPORT_USER_SEARCH_FILTER = "ldap.import.user.search.filter";

	public static final String LDAP_IMPORT_GROUP_SEARCH_FILTER = "ldap.import.group.search.filter";

	public static final String LDAP_IMPORT_METHOD = "ldap.import.method";

	public static final String LDAP_EXPORT_ENABLED = "ldap.export.enabled";

	public static final String LDAP_USERS_DN = "ldap.users.dn";

	public static final String LDAP_GROUPS_DN = "ldap.groups.dn";

	public static final String LDAP_PASSWORD_POLICY_ENABLED = "ldap.password.policy.enabled";

	public static final String LDAP_ERROR_PASSWORD_AGE = "ldap.error.password.age";

	public static final String LDAP_ERROR_PASSWORD_EXPIRED = "ldap.error.password.expired";

	public static final String LDAP_ERROR_PASSWORD_HISTORY = "ldap.error.password.history";

	public static final String LDAP_ERROR_PASSWORD_NOT_CHANGEABLE = "ldap.error.password.not.changeable";

	public static final String LDAP_ERROR_PASSWORD_SYNTAX = "ldap.error.password.syntax";

	public static final String LDAP_ERROR_PASSWORD_TRIVIAL = "ldap.error.password.trivial";

	public static final String LDAP_ERROR_USER_LOCKOUT = "ldap.error.user.lockout";

	// CAS

	public static final String CAS_AUTH_ENABLED = "cas.auth.enabled";

	public static final String CAS_IMPORT_FROM_LDAP = "cas.import.from.ldap";

    public static final String CAS_LOGIN_URL = "cas.login.url";

	public static final String CAS_LOGOUT_URL = "cas.logout.url";

	public static final String CAS_SERVER_NAME = "cas.server.name";

	public static final String CAS_SERVICE_URL = "cas.service.url";

	public static final String CAS_VALIDATE_URL = "cas.validate.url";

	// NTLM

	public static final String NTLM_AUTH_ENABLED = "ntlm.auth.enabled";

	public static final String NTLM_DOMAIN_CONTROLLER = "ntlm.auth.domain.controller";

	public static final String NTLM_DOMAIN = "ntlm.auth.domain";

	// OpenID

	public static final String OPEN_ID_AUTH_ENABLED = "open.id.auth.enabled";

	// OpenSSO

	public static final String OPEN_SSO_AUTH_ENABLED = "open.sso.auth.enabled";

	public static final String OPEN_SSO_LOGIN_URL = "open.sso.login.url";

	public static final String OPEN_SSO_LOGOUT_URL = "open.sso.logout.url";

	public static final String OPEN_SSO_SERVICE_URL = "open.sso.service.url";

	public static final String OPEN_SSO_SUBJECT_COOKIE_NAME = "open.sso.subject.cookie.name";

	// Authentication Pipeline

	public static final String AUTH_PIPELINE_PRE = "auth.pipeline.pre";

	public static final String AUTH_PIPELINE_POST = "auth.pipeline.post";

	public static final String AUTH_PIPELINE_ENABLE_LIFERAY_CHECK = "auth.pipeline.enable.liferay.check";

	public static final String AUTH_FAILURE = "auth.failure";

	public static final String AUTH_MAX_FAILURES = "auth.max.failures";

	public static final String AUTH_SIMULTANEOUS_LOGINS = "auth.simultaneous.logins";

	public static final String AUTH_FORWARD_BY_LAST_PATH = "auth.forward.by.last.path";

	public static final String AUTH_FORWARD_BY_REDIRECT = "auth.forward.by.redirect";

	public static final String AUTH_FORWARD_LAST_PATHS = "auth.forward.last.paths";

	public static final String AUTH_PUBLIC_PATHS = "auth.public.paths";

	// Auto Login

	public static final String AUTO_LOGIN_HOOKS = "auto.login.hooks";

	// SSO with MAC

	public static final String AUTH_MAC_ALLOW = "auth.mac.allow";

	public static final String AUTH_MAC_ALGORITHM = "auth.mac.algorithm";

	public static final String AUTH_MAC_SHARED_KEY = "auth.mac.shared.key";

	// Passwords

	public static final String PASSWORDS_ENCRYPTION_ALGORITHM = "passwords.encryption.algorithm";

	public static final String PASSWORDS_DIGEST_ENCODING = "passwords.digest.encoding";

	public static final String PASSWORDS_TOOLKIT = "passwords.toolkit";

	public static final String PASSWORDS_PASSWORDPOLICYTOOLKIT_GENERATOR = "passwords.passwordpolicytoolkit.generator";

	public static final String PASSWORDS_PASSWORDPOLICYTOOLKIT_STATIC = "passwords.passwordpolicytoolkit.static";

	public static final String PASSWORDS_REGEXPTOOLKIT_PATTERN = "passwords.regexptoolkit.pattern";

	public static final String PASSWORDS_REGEXPTOOLKIT_CHARSET = "passwords.regexptoolkit.charset";

	public static final String PASSWORDS_REGEXPTOOLKIT_LENGTH = "passwords.regexptoolkit.length";

	public static final String PASSWORDS_DEFAULT_POLICY_NAME = "passwords.default.policy.name";

	// Permissions

	public static final String PERMISSIONS_CHECKER = "permissions.checker";

	public static final String PERMISSIONS_USER_CHECK_ALGORITHM = "permissions.user.check.algorithm";

	public static final String PERMISSIONS_LIST_FILTER = "permissions.list.filter";

	// Captcha

	public static final String CAPTCHA_MAX_CHALLENGES = "captcha.max.challenges";

	// Startup Events

	public static final String GLOBAL_STARTUP_EVENTS = "global.startup.events";

	public static final String APPLICATION_STARTUP_EVENTS = "application.startup.events";

	public static final String SHUTDOWN_PROGRAMMATICALLY_EXIT = "shutdown.programmatically.exit";

	// Shutdown Events

	public static final String GLOBAL_SHUTDOWN_EVENTS = "global.shutdown.events";

	public static final String APPLICATION_SHUTDOWN_EVENTS = "application.shutdown.events";

	// Portal Events

	public static final String SERVLET_SERVICE_EVENTS_PRE = "servlet.service.events.pre";

	public static final String SERVLET_SERVICE_EVENTS_PRE_ERROR_PAGE = "servlet.service.events.pre.error.page";

	public static final String SERVLET_SERVICE_EVENTS_POST = "servlet.service.events.post";

	public static final String LOGIN_EVENTS_PRE = "login.events.pre";

	public static final String LOGIN_EVENTS_POST = "login.events.post";

	public static final String LOGOUT_EVENTS_PRE = "logout.events.pre";

	public static final String LOGOUT_EVENTS_POST = "logout.events.post";

	// Default Landing Page

	public static final String DEFAULT_LANDING_PAGE_PATH = "default.landing.page.path";

	// Default Guest

	public static final String DEFAULT_GUEST_LAYOUT_NAME = "default.guest.layout.name";

	public static final String DEFAULT_GUEST_LAYOUT_TEMPLATE_ID = "default.guest.layout.template.id";

	public static final String DEFAULT_GUEST_LAYOUT_COLUMN = "default.guest.layout.column-";

	public static final String DEFAULT_GUEST_FRIENDLY_URL = "default.guest.friendly.url";

	// Default User

	public static final String DEFAULT_USER_LAYOUT_NAME = "default.user.layout.name";

	public static final String DEFAULT_USER_LAYOUT_TEMPLATE_ID = "default.user.layout.template.id";

	public static final String DEFAULT_USER_LAYOUT_COLUMN = "default.user.layout.column-";

	public static final String DEFAULT_USER_PRIVATE_LAYOUT_LAR = "default.user.private.layout.lar";

	public static final String DEFAULT_USER_PUBLIC_LAYOUT_LAR = "default.user.public.layout.lar";
	
	//default user's pbulic layout
	
	public static final String DEFAULT_USER_PUBLIC_HOME_LAYOUT_NAME = "default.user.public.home.layout.name";

	public static final String DEFAULT_USER_PUBLIC_HOME_LAYOUT_TEMPLATE_ID = "default.user.public.home.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_HOME_LAYOUT_COLUMN = "default.user.public.home.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_HOME_LAYOUT_PARENT = "default.user.public.home.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_CARDABOUT_LAYOUT_NAME = "default.user.public.ecardabout.layout.name";

	public static final String DEFAULT_USER_PUBLIC_CARDABOUT_LAYOUT_TEMPLATE_ID = "default.user.public.ecardabout.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_CARDABOUT_LAYOUT_COLUMN = "default.user.public.ecardabout.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_CARDABOUT_LAYOUT_PARENT = "default.user.public.ecardabout.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_SERVICEPLACE_LAYOUT_NAME = "default.user.public.serviceplace.layout.name";

	public static final String DEFAULT_USER_PUBLIC_SERVICEPLACE_LAYOUT_TEMPLATE_ID = "default.user.public.serviceplace.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_SERVICEPLACE_LAYOUT_COLUMN = "default.user.public.serviceplace.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_SERVICEPLACE_LAYOUT_PARENT = "default.user.public.serviceplace.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_ECARDRULES_LAYOUT_NAME = "default.user.public.ecardrules.layout.name";

	public static final String DEFAULT_USER_PUBLIC_ECARDRULES_LAYOUT_TEMPLATE_ID = "default.user.public.ecardrules.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_ECARDRULES_LAYOUT_COLUMN = "default.user.public.ecardrules.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_ECARDRULES_LAYOUT_PARENT = "default.user.public.ecardrules.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_ECARDTURTORIAL_LAYOUT_NAME = "default.user.public.ecardturtorial.layout.name";

	public static final String DEFAULT_USER_PUBLIC_ECARDTURTORIAL_LAYOUT_TEMPLATE_ID = "default.user.public.ecardturtorial.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_ECARDTURTORIAL_LAYOUT_COLUMN = "default.user.public.ecardturtorial.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_ECARDTURTORIAL_LAYOUT_PARENT = "default.user.public.ecardturtorial.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_DOBUSINESS_LAYOUT_NAME = "default.user.public.dobusiness.layout.name";

	public static final String DEFAULT_USER_PUBLIC_DOBUSINESS_LAYOUT_TEMPLATE_ID = "default.user.public.dobusiness.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_DOBUSINESS_LAYOUT_COLUMN = "default.user.public.dobusiness.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_DOBUSINESS_LAYOUT_PARENT = "default.user.public.dobusiness.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_ECARDCARDPROCESS_LAYOUT_NAME = "default.user.public.ecardcardprocess.layout.name";

	public static final String DEFAULT_USER_PUBLIC_ECARDCARDPROCESS_LAYOUT_TEMPLATE_ID = "default.user.public.ecardcardprocess.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_ECARDCARDPROCESS_LAYOUT_COLUMN = "default.user.public.ecardcardprocess.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_ECARDCARDPROCESS_LAYOUT_PARENT = "default.user.public.ecardcardprocess.layout.parent";
	
	
	public static final String DEFAULT_USER_PUBLIC_ECARDDOC_LAYOUT_NAME = "default.user.public.ecarddoc.layout.name";

	public static final String DEFAULT_USER_PUBLIC_ECARDDOC_LAYOUT_TEMPLATE_ID = "default.user.public.ecarddoc.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_ECARDDOC_LAYOUT_COLUMN = "default.user.public.ecarddoc.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_ECARDDOC_LAYOUT_PARENT = "default.user.public.ecarddoc.layout.parent";	
	
	
	public static final String DEFAULT_USER_PUBLIC_ECARDSERVICE_LAYOUT_NAME = "default.user.public.ecardservice.layout.name";

	public static final String DEFAULT_USER_PUBLIC_ECARDSERVICE_LAYOUT_TEMPLATE_ID = "default.user.public.ecardservice.layout.template.id";

	public static final String DEFAULT_USER_PUBLIC_ECARDSERVICE_LAYOUT_COLUMN = "default.user.public.ecardservice.layout.column-";
	
	public static final String DEFAULT_USER_PUBLIC_ECARDSERVICE_LAYOUT_PARENT = "default.user.public.ecardservice.layout.parent";
	

	public static final String DEFAULT_USER_SUBPAGE_BANKBIND_LAYOUT_NAME = "default.user.subpage.bankbind.layout.name";

	public static final String DEFAULT_USER_SUBPAGE_BANKBIND_LAYOUT_TEMPLATE_ID = "default.user.subpage.bankbind.layout.template.id";

	public static final String DEFAULT_USER_SUBPAGE_BANKBIND_LAYOUT_COLUMN = "default.user.subpage.bankbind.layout.column-";
	
	public static final String DEFAULT_USER_SUBPAGE_BANKBIND_LAYOUT_PARENT = "default.user.subpage.bankbind.layout.parent";
	
	
	public static final String DEFAULT_USER_SUBPAGE_CARDLOST_LAYOUT_NAME = "default.user.subpage.cardlost.layout.name";

	public static final String DEFAULT_USER_SUBPAGE_CARDLOST_LAYOUT_TEMPLATE_ID = "default.user.subpage.cardlost.layout.template.id";

	public static final String DEFAULT_USER_SUBPAGE_CARDLOST_LAYOUT_COLUMN = "default.user.subpage.cardlost.layout.column-";
	
	public static final String DEFAULT_USER_SUBPAGE_CARDLOST_LAYOUT_PARENT = "default.user.subpage.cardlost.layout.parent";
	
	
	public static final String DEFAULT_USER_SUBPAGE_QUERYDETAIL_LAYOUT_NAME = "default.user.subpage.querydetail.layout.name";

	public static final String DEFAULT_USER_SUBPAGE_QUERYDETAIL_LAYOUT_TEMPLATE_ID = "default.user.subpage.querydetail.layout.template.id";

	public static final String DEFAULT_USER_SUBPAGE_QUERYDETAIL_LAYOUT_COLUMN = "default.user.subpage.querydetail.layout.column-";
	
	public static final String DEFAULT_USER_SUBPAGE_QUERYDETAIL_LAYOUT_PARENT = "default.user.subpage.querydetail.layout.parent";
	

	
	
	// Default Admin

	public static final String DEFAULT_ADMIN_PASSWORD = "default.admin.password";

	public static final String DEFAULT_ADMIN_SCREEN_NAME = "default.admin.screen.name";

	public static final String DEFAULT_ADMIN_EMAIL_ADDRESS_PREFIX = "default.admin.email.address.prefix";

	public static final String DEFAULT_ADMIN_FIRST_NAME = "default.admin.first.name";

	public static final String DEFAULT_ADMIN_MIDDLE_NAME = "default.admin.middle.name";

	public static final String DEFAULT_ADMIN_LAST_NAME = "default.admin.last.name";

	// Layouts

	public static final String LAYOUT_TYPES = "layout.types";

	public static final String LAYOUT_CONFIGURATION_ACTION_UPDATE = "layout.configuration.action.update";

	public static final String LAYOUT_CONFIGURATION_ACTION_DELETE = "layout.configuration.action.delete";

	public static final String LAYOUT_EDIT_PAGE = "layout.edit.page";

	public static final String LAYOUT_VIEW_PAGE = "layout.view.page";

	public static final String LAYOUT_URL = "layout.url";

	public static final String LAYOUT_URL_FRIENDLIABLE = "layout.url.friendliable";

	public static final String LAYOUT_PARENTABLE = "layout.parentable";

	public static final String LAYOUT_SITEMAPABLE = "layout.sitemapable";

	public static final String LAYOUT_STATIC_PORTLETS_START = "layout.static.portlets.start.";

	public static final String LAYOUT_STATIC_PORTLETS_END = "layout.static.portlets.end.";

	public static final String LAYOUT_FRIENDLY_URL_PRIVATE_GROUP_SERVLET_MAPPING = "layout.friendly.url.private.group.servlet.mapping";

	public static final String LAYOUT_FRIENDLY_URL_PRIVATE_USER_SERVLET_MAPPING = "layout.friendly.url.private.user.servlet.mapping";

	public static final String LAYOUT_FRIENDLY_URL_PUBLIC_SERVLET_MAPPING = "layout.friendly.url.public.servlet.mapping";

	public static final String LAYOUT_FRIENDLY_URL_PAGE_NOT_FOUND = "layout.friendly.url.page.not.found";

	public static final String LAYOUT_FRIENDLY_URL_KEYWORDS = "layout.friendly.url.keywords";

	public static final String LAYOUT_ADD_PORTLETS = "layout.add.portlets";

	public static final String LAYOUT_NAME_MAX_LENGTH = "layout.name.max.length";

	public static final String LAYOUT_TABS_PER_ROW = "layout.tabs.per.row";

	public static final String LAYOUT_REMEMBER_SESSION_WINDOW_STATE_MAXIMIZED = "layout.remember.session.window.state.maximized";

	public static final String LAYOUT_REMEMBER_REQUEST_WINDOW_STATE_MAXIMIZED = "layout.remember.request.window.state.maximized";

	public static final String LAYOUT_GUEST_SHOW_MAX_ICON = "layout.guest.show.max.icon";

	public static final String LAYOUT_GUEST_SHOW_MIN_ICON = "layout.guest.show.min.icon";

	public static final String LAYOUT_SHOW_PORTLET_ACCESS_DENIED = "layout.show.portlet.access.denied";

	public static final String LAYOUT_SHOW_PORTLET_INACTIVE = "layout.show.portlet.inactive";

	public static final String LAYOUT_SHOW_HTTP_STATUS = "layout.show.http.status";

	public static final String LAYOUT_DEFAULT_TEMPLATE_ID = "layout.default.template.id";

	public static final String LAYOUT_PARALLEL_RENDER_ENABLE = "layout.parallel.render.enable";

	public static final String LAYOUT_CLONE_IMPL = "layout.clone.impl";

	public static final String LAYOUT_TEMPLATE_CACHE_ENABLED = "layout.template.cache.enabled";

	public static final String LAYOUT_DEFAULT_P_L_RESET = "layout.default.p_l_reset";

	// Portlet URL

	public static final String PORTLET_URL_APPEND_PARAMETERS = "portlet.url.append.parameters";

	public static final String PORTLET_URL_ANCHOR_ENABLE = "portlet.url.anchor.enable";

	// Preferences

	public static final String PREFERENCE_VALIDATE_ON_STARTUP = "preference.validate.on.startup";

	// Struts

	public static final String STRUTS_PORTLET_REQUEST_PROCESSOR = "struts.portlet.request.processor";

	// Images

	public static final String IMAGE_DEFAULT_SPACER = "image.default.spacer";

	public static final String IMAGE_DEFAULT_COMPANY_LOGO = "image.default.company.logo";

	public static final String IMAGE_DEFAULT_USER_PORTRAIT = "image.default.user.portrait";

	// Editors

	public static final String EDITOR_WYSIWYG_DEFAULT = "editor.wysiwyg.default";

	// Fields

	public static final String FIELD_ENABLE_COM_LIFERAY_PORTAL_MODEL_CONTACT_MALE = "field.enable.com.liferay.portal.model.Contact.male";

	public static final String FIELD_ENABLE_COM_LIFERAY_PORTAL_MODEL_CONTACT_BIRTHDAY = "field.enable.com.liferay.portal.model.Contact.birthday";

	public static final String FIELD_ENABLE_COM_LIFERAY_PORTAL_MODEL_ORGANIZATION_STATUS = "field.enable.com.liferay.portal.model.Organization.status";

	// Mime Types

	public static final String MIME_TYPES = "mime.types";

	// Amazon License Keys

	public static final String AMAZON_LICENSE = "amazon.license.";

	// Instant Messenger

	public static final String AIM_LOGIN = "aim.login";

	public static final String AIM_PASSWORD = "aim.password";

	public static final String ICQ_JAR = "icq.jar";

	public static final String ICQ_LOGIN = "icq.login";

	public static final String ICQ_PASSWORD = "icq.password";

	public static final String MSN_LOGIN = "msn.login";

	public static final String MSN_PASSWORD = "msn.password";

	public static final String YM_LOGIN = "ym.login";

	public static final String YM_PASSWORD = "ym.password";

	// Lucene Search

	public static final String INDEX_READ_ONLY = "index.read.only";

	public static final String INDEX_ON_STARTUP = "index.on.startup";

	public static final String INDEX_WITH_THREAD = "index.with.thread";

	public static final String LUCENE_STORE_TYPE = "lucene.store.type";

	public static final String LUCENE_STORE_JDBC_AUTO_CLEAN_UP = "lucene.store.jdbc.auto.clean.up";

	public static final String LUCENE_STORE_JDBC_DIALECT = "lucene.store.jdbc.dialect.";

	public static final String LUCENE_DIR = "lucene.dir";

	public static final String LUCENE_FILE_EXTRACTOR = "lucene.file.extractor";

	public static final String LUCENE_FILE_EXTRACTOR_REGEXP_STRIP = "lucene.file.extractor.regexp.strip";

	public static final String LUCENE_ANALYZER = "lucene.analyzer";

	public static final String LUCENE_MERGE_FACTOR = "lucene.merge.factor";

	public static final String LUCENE_OPTIMIZE_INTERVAL = "lucene.optimize.interval";

	// SourceForge

	public static final String SOURCE_FORGE_MIRRORS = "source.forge.mirrors";

	// Value Object

	public static final String VALUE_OBJECT_FINDER_CACHE_ENABLED = "value.object.finder.cache.enabled";

	// Last Modified

	public static final String LAST_MODIFIED_CHECK = "last.modified.check";

	public static final String LAST_MODIFIED_PATHS = "last.modified.paths";

	// Communication Link

	public static final String COMM_LINK_PROPERTIES = "comm.link.properties";

	// Content Delivery Network

	public static final String CDN_HOST = "cdn.host";

	// Counter

	public static final String COUNTER_INCREMENT = "counter.increment";

	// Jabber

	public static final String JABBER_XMPP_SERVER_ENABLED = "jabber.xmpp.server.enabled";

	public static final String JABBER_XMPP_SERVER_ADDRESS = "jabber.xmpp.server.address";

	public static final String JABBER_XMPP_SERVER_NAME = "jabber.xmpp.server.name";

	public static final String JABBER_XMPP_SERVER_PORT = "jabber.xmpp.server.port";

	public static final String JABBER_XMPP_USER_PASSWORD = "jabber.xmpp.user.password";

	// JBI

	public static final String JBI_WORKFLOW_URL = "jbi.workflow.url";

	// JCR

	public static final String JCR_INITIALIZE_ON_STARTUP = "jcr.initialize.on.startup";

	public static final String JCR_WORKSPACE_NAME = "jcr.workspace.name";

	public static final String JCR_NODE_DOCUMENTLIBRARY = "jcr.node.documentlibrary";

	public static final String JCR_JACKRABBIT_REPOSITORY_ROOT = "jcr.jackrabbit.repository.root";

	public static final String JCR_JACKRABBIT_CONFIG_FILE_PATH = "jcr.jackrabbit.config.file.path";

	public static final String JCR_JACKRABBIT_REPOSITORY_HOME = "jcr.jackrabbit.repository.home";

	public static final String JCR_JACKRABBIT_CREDENTIALS_USERNAME = "jcr.jackrabbit.credentials.username";

	public static final String JCR_JACKRABBIT_CREDENTIALS_PASSWORD = "jcr.jackrabbit.credentials.password";

	// OpenOffice

	public static final String OPENOFFICE_SERVER_ENABLED = "openoffice.server.enabled";

	public static final String OPENOFFICE_SERVER_HOST = "openoffice.server.host";

	public static final String OPENOFFICE_SERVER_PORT = "openoffice.server.port";

	// POP

	public static final String POP_SERVER_NOTIFICATIONS_ENABLED = "pop.server.notifications.enabled";

	public static final String POP_SERVER_NOTIFICATIONS_INTERVAL = "pop.server.notifications.interval";

	public static final String POP_SERVER_SUBDOMAIN = "pop.server.subdomain";

	// Reverse AJAX

	public static final String REVERSE_AJAX_ENABLED = "reverse.ajax.enabled";

	public static final String REVERSE_AJAX_HEARTBEAT = "reverse.ajax.heartbeat";

	// Scheduler

	public static final String SCHEDULER_ENABLED = "scheduler.enabled";

	// Social Bookmarking

	public static final String SOCIAL_BOOKMARK_TYPES = "social.bookmark.types";

	public static final String SOCIAL_BOOKMARK_POST_URL = "social.bookmark.post.url";

	// Velocity Engine

	public static final String VELOCITY_ENGINE_RESOURCE_LISTENERS = "velocity.engine.resource.listeners";

	public static final String VELOCITY_ENGINE_RESOURCE_MANAGER = "velocity.engine.resource.manager";

	public static final String VELOCITY_ENGINE_RESOURCE_MANAGER_CACHE = "velocity.engine.resource.manager.cache";

	public static final String VELOCITY_ENGINE_RESOURCE_MANAGER_CACHE_ENABLED = "velocity.engine.resource.manager.cache.enabled";

	public static final String VELOCITY_ENGINE_RESOURCE_MANAGER_MODIFICATION_CHECK_INTERVAL = "velocity.engine.resource.manager.modification.check.interval";

	public static final String VELOCITY_ENGINE_VELOCIMACRO_LIBRARY = "velocity.engine.velocimacro.library";

	public static final String VELOCITY_ENGINE_LOGGER = "velocity.engine.logger";

	public static final String VELOCITY_ENGINE_LOGGER_CATEGORY = "velocity.engine.logger.category";

	// Virtual Hosts

	public static final String VIRTUAL_HOSTS_IGNORE_HOSTS = "virtual.hosts.ignore.hosts";

	public static final String VIRTUAL_HOSTS_IGNORE_PATHS = "virtual.hosts.ignore.paths";

	// Web Server

	public static final String WEB_SERVER_HTTP_PORT = "web.server.http.port";

	public static final String WEB_SERVER_HTTPS_PORT = "web.server.https.port";

	public static final String WEB_SERVER_HOST = "web.server.host";

	public static final String WEB_SERVER_PROTOCOL = "web.server.protocol";

	public static final String WEB_SERVER_DISPLAY_NODE = "web.server.display.node";

	// WebDAV

	public static final String WEBDAV_LITMUS = "webdav.litmus";

	// Admin Portlet

	public static final String ADMIN_DEFAULT_GROUP_NAMES = "admin.default.group.names";

	public static final String ADMIN_DEFAULT_ROLE_NAMES = "admin.default.role.names";

	public static final String ADMIN_DEFAULT_USER_GROUP_NAMES = "admin.default.user.group.names";

	public static final String ADMIN_MAIL_HOST_NAMES = "admin.mail.host.names";

	public static final String ADMIN_RESERVED_SCREEN_NAMES = "admin.reserved.screen.names";

	public static final String ADMIN_RESERVED_EMAIL_ADDRESSES = "admin.reserved.email.addresses";

	public static final String ADMIN_EMAIL_FROM_NAME = "admin.email.from.name";

	public static final String ADMIN_EMAIL_FROM_ADDRESS = "admin.email.from.address";

	public static final String ADMIN_EMAIL_USER_ADDED_ENABLED = "admin.email.user.added.enabled";

	public static final String ADMIN_EMAIL_USER_ADDED_SUBJECT = "admin.email.user.added.subject";

	public static final String ADMIN_EMAIL_USER_ADDED_BODY = "admin.email.user.added.body";

	public static final String ADMIN_EMAIL_PASSWORD_SENT_ENABLED = "admin.email.password.sent.enabled";

	public static final String ADMIN_EMAIL_PASSWORD_SENT_SUBJECT = "admin.email.password.sent.subject";

	public static final String ADMIN_EMAIL_PASSWORD_SENT_BODY = "admin.email.password.sent.body";

	// Blogs Portlet

	public static final String BLOGS_EMAIL_COMMENTS_ADDED_ENABLED = "blogs.email.comments.added.enabled";

	public static final String BLOGS_EMAIL_COMMENTS_ADDED_SUBJECT = "blogs.email.comments.added.subject";

	public static final String BLOGS_EMAIL_COMMENTS_ADDED_BODY = "blogs.email.comments.added.body";

	public static final String BLOGS_PAGE_ABSTRACT_LENGTH = "blogs.page.abstract.length";

	public static final String BLOGS_RSS_ABSTRACT_LENGTH = "blogs.rss.abstract.length";

	// Calendar Portlet

	public static final String CALENDAR_EVENT_TYPES = "calendar.event.types";

	public static final String CALENDAR_EMAIL_FROM_NAME = "calendar.email.from.name";

	public static final String CALENDAR_EMAIL_FROM_ADDRESS = "calendar.email.from.address";

	public static final String CALENDAR_EMAIL_EVENT_REMINDER_ENABLED = "calendar.email.event.reminder.enabled";

	public static final String CALENDAR_EMAIL_EVENT_REMINDER_SUBJECT = "calendar.email.event.reminder.subject";

	public static final String CALENDAR_EMAIL_EVENT_REMINDER_BODY = "calendar.email.event.reminder.body";

	// Communities Portlet

	public static final String COMMUNITIES_EMAIL_FROM_NAME = "communities.email.from.name";

	public static final String COMMUNITIES_EMAIL_FROM_ADDRESS = "communities.email.from.address";

	public static final String COMMUNITIES_EMAIL_MEMBERSHIP_REPLY_SUBJECT = "communities.email.membership.reply.subject";

	public static final String COMMUNITIES_EMAIL_MEMBERSHIP_REPLY_BODY = "communities.email.membership.reply.body";

	public static final String COMMUNITIES_EMAIL_MEMBERSHIP_REQUEST_SUBJECT = "communities.email.membership.request.subject";

	public static final String COMMUNITIES_EMAIL_MEMBERSHIP_REQUEST_BODY = "communities.email.membership.request.body";

	// Document Library Portlet

	public static final String DL_HOOK_IMPL = "dl.hook.impl";

	public static final String DL_HOOK_FILE_SYSTEM_ROOT_DIR = "dl.hook.file.system.root.dir";

    public static final String DL_HOOK_S3_ACCESS_KEY = "dl.hook.s3.access.key";

	public static final String DL_HOOK_S3_SECRET_KEY = "dl.hook.s3.secret.key";

	public static final String DL_HOOK_S3_BUCKET_NAME = "dl.hook.s3.bucket.name";

	public static final String DL_FILE_MAX_SIZE = "dl.file.max.size";

	public static final String DL_FILE_EXTENSIONS = "dl.file.extensions";

	public static final String DL_LAYOUTS_SYNC_ENABLED = "dl.layouts.sync.enabled";

	public static final String DL_LAYOUTS_SYNC_PRIVATE_FOLDER = "dl.layouts.sync.private.folder";

	public static final String DL_LAYOUTS_SYNC_PUBLIC_FOLDER = "dl.layouts.sync.public.folder";

	// Image Gallery Portlet

	public static final String IG_IMAGE_MAX_SIZE = "ig.image.max.size";

	public static final String IG_IMAGE_EXTENSIONS = "ig.image.extensions";

	public static final String IG_IMAGE_THUMBNAIL_MAX_HEIGHT = "ig.image.thumbnail.max.height";

	public static final String IG_IMAGE_THUMBNAIL_MAX_WIDTH = "ig.image.thumbnail.max.width";

	// Invitation Portlet

	public static final String INVITATION_EMAIL_MAX_RECIPIENTS = "invitation.email.max.recipients";

	public static final String INVITATION_EMAIL_MESSAGE_BODY = "invitation.email.message.body";

	public static final String INVITATION_EMAIL_MESSAGE_SUBJECT = "invitation.email.message.subject";

	// Journal Portlet

	public static final String JOURNAL_ARTICLE_FORCE_AUTOGENERATE_ID = "journal.article.force.autogenerate.id";

	public static final String JOURNAL_ARTICLE_FORCE_INCREMENT_VERSION = "journal.article.force.increment.version";

	public static final String JOURNAL_ARTICLE_TYPES = "journal.article.types";

	public static final String JOURNAL_ARTICLE_TOKEN_PAGE_BREAK = "journal.article.token.page.break";

	public static final String JOURNAL_ARTICLE_CHECK_INTERVAL = "journal.article.check.interval";

	public static final String JOURNAL_FEED_FORCE_AUTOGENERATE_ID = "journal.feed.force.autogenerate.id";

	public static final String JOURNAL_STRUCTURE_FORCE_AUTOGENERATE_ID = "journal.structure.force.autogenerate.id";

	public static final String JOURNAL_TEMPLATE_FORCE_AUTOGENERATE_ID = "journal.template.force.autogenerate.id";

	public static final String JOURNAL_TEMPLATE_VELOCITY_RESTRICTED_VARIABLES = "journal.template.velocity.restricted.variables";

	public static final String JOURNAL_IMAGE_SMALL_MAX_SIZE = "journal.image.small.max.size";

	public static final String JOURNAL_IMAGE_EXTENSIONS = "journal.image.extensions";

	public static final String JOURNAL_TRANSFORMER_LISTENER = "journal.transformer.listener";

	public static final String JOURNAL_SYNC_CONTENT_SEARCH_ON_STARTUP = "journal.sync.content.search.on.startup";

	public static final String JOURNAL_EMAIL_FROM_NAME = "journal.email.from.name";

	public static final String JOURNAL_EMAIL_FROM_ADDRESS = "journal.email.from.address";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_DENIED_ENABLED = "journal.email.article.approval.denied.enabled";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_DENIED_SUBJECT = "journal.email.article.approval.denied.subject";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_DENIED_BODY = "journal.email.article.approval.denied.body";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_GRANTED_ENABLED = "journal.email.article.approval.granted.enabled";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_GRANTED_SUBJECT = "journal.email.article.approval.granted.subject";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_GRANTED_BODY = "journal.email.article.approval.granted.body";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_REQUESTED_ENABLED = "journal.email.article.approval.requested.enabled";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_REQUESTED_SUBJECT = "journal.email.article.approval.requested.subject";

	public static final String JOURNAL_EMAIL_ARTICLE_APPROVAL_REQUESTED_BODY = "journal.email.article.approval.requested.body";

	public static final String JOURNAL_EMAIL_ARTICLE_REVIEW_ENABLED = "journal.email.article.review.enabled";

	public static final String JOURNAL_EMAIL_ARTICLE_REVIEW_SUBJECT = "journal.email.article.review.subject";

	public static final String JOURNAL_EMAIL_ARTICLE_REVIEW_BODY = "journal.email.article.review.body";

	// Journal Articles Portlet

	public static final String JOURNAL_ARTICLES_PAGE_DELTA_VALUES = "journal.articles.page.delta.values";

	// Mail Portlet

	public static final String MAIL_MX_UPDATE = "mail.mx.update";

	public static final String MAIL_HOOK_IMPL = "mail.hook.impl";

	public static final String MAIL_HOOK_CYRUS_ADD_USER = "mail.hook.cyrus.add.user";

	public static final String MAIL_HOOK_CYRUS_DELETE_USER = "mail.hook.cyrus.delete.user";

	public static final String MAIL_HOOK_CYRUS_HOME = "mail.hook.cyrus.home";

	public static final String MAIL_HOOK_FUSEMAIL_URL = "mail.hook.fusemail.url";

	public static final String MAIL_HOOK_FUSEMAIL_USERNAME = "mail.hook.fusemail.username";

	public static final String MAIL_HOOK_FUSEMAIL_PASSWORD = "mail.hook.fusemail.password";

	public static final String MAIL_HOOK_FUSEMAIL_ACCOUNT_TYPE = "mail.hook.fusemail.account.type";

	public static final String MAIL_HOOK_FUSEMAIL_GROUP_PARENT = "mail.hook.fusemail.group.parent";

	public static final String MAIL_HOOK_SENDMAIL_ADD_USER = "mail.hook.sendmail.add.user";

	public static final String MAIL_HOOK_SENDMAIL_CHANGE_PASSWORD = "mail.hook.sendmail.change.password";

	public static final String MAIL_HOOK_SENDMAIL_DELETE_USER = "mail.hook.sendmail.delete.user";

	public static final String MAIL_HOOK_SENDMAIL_HOME = "mail.hook.sendmail.home";

	public static final String MAIL_HOOK_SENDMAIL_VIRTUSERTABLE = "mail.hook.sendmail.virtusertable";

	public static final String MAIL_HOOK_SENDMAIL_VIRTUSERTABLE_REFRESH = "mail.hook.sendmail.virtusertable.refresh";

	public static final String MAIL_HOOK_SHELL_SCRIPT = "mail.hook.shell.script";

	public static final String MAIL_BOX_STYLE = "mail.box.style";

	public static final String MAIL_INBOX_NAME = "mail.inbox.name";

	public static final String MAIL_SPAM_NAME = "mail.spam.name";

	public static final String MAIL_SENT_NAME = "mail.sent.name";

	public static final String MAIL_DRAFTS_NAME = "mail.drafts.name";

	public static final String MAIL_TRASH_NAME = "mail.trash.name";

	public static final String MAIL_JUNK_MAIL_WARNING_SIZE = "mail.junk-mail.warning.size";

	public static final String MAIL_TRASH_WARNING_SIZE = "mail.trash.warning.size";

	public static final String MAIL_SMTP_DEBUG = "mail.smtp.debug";

	public static final String MAIL_AUDIT_TRAIL = "mail.audit.trail";

	public static final String MAIL_ATTACHMENTS_MAX_SIZE = "mail.attachments.max.size";

	public static final String MAIL_ACCOUNT_FINDER = "mail.account.finder";

	public static final String MAIL_ACCOUNT_FINDER_PASSWORD = "mail.account.finder.password";

	public static final String MAIL_RECIPIENT_FINDER = "mail.recipient.finder";

	// Message Boards Portlet

	public static final String MESSAGE_BOARDS_EMAIL_FROM_NAME = "message.boards.email.from.name";

	public static final String MESSAGE_BOARDS_EMAIL_FROM_ADDRESS = "message.boards.email.from.address";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_ENABLED = "message.boards.email.message.added.enabled";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_SUBJECT_PREFIX = "message.boards.email.message.added.subject.prefix";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_BODY = "message.boards.email.message.added.body";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_SIGNATURE = "message.boards.email.message.added.signature";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_ENABLED = "message.boards.email.message.updated.enabled";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_SUBJECT_PREFIX = "message.boards.email.message.updated.subject.prefix";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_BODY = "message.boards.email.message.updated.body";

	public static final String MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_SIGNATURE = "message.boards.email.message.updated.signature";

	public static final String MESSAGE_BOARDS_ALLOW_ANONYMOUS_POSTING = "message.boards.anonymous.posting.enabled";

	public static final String MESSAGE_BOARDS_ANONYMOUS_POSTING_ENABLED = "message.boards.expire.ban.job.interval";

	public static final String MESSAGE_BOARDS_EXPIRE_BAN_JOB_INTERVAL = "message.boards.expire.ban.job.interval";

	public static final String MESSAGE_BOARDS_EXPIRE_BAN_INTERVAL = "message.boards.expire.ban.interval";

	public static final String MESSAGE_BOARDS_RSS_ABSTRACT_LENGTH = "message.boards.rss.abstract.length";

	// My Places Portlet

    public static final String MY_PLACES_SHOW_USER_PUBLIC_SITES_WITH_NO_LAYOUTS = "my.places.show.user.public.sites.with.no.layouts";

	public static final String MY_PLACES_SHOW_USER_PRIVATE_SITES_WITH_NO_LAYOUTS = "my.places.show.user.private.sites.with.no.layouts";

    public static final String MY_PLACES_SHOW_ORGANIZATION_PUBLIC_SITES_WITH_NO_LAYOUTS = "my.places.show.organization.public.sites.with.no.layouts";

    public static final String MY_PLACES_SHOW_ORGANIZATION_PRIVATE_SITES_WITH_NO_LAYOUTS = "my.places.show.organization.private.sites.with.no.layouts";

    public static final String MY_PLACES_SHOW_COMMUNITY_PUBLIC_SITES_WITH_NO_LAYOUTS = "my.places.show.community.public.sites.with.no.layouts";

    public static final String MY_PLACES_SHOW_COMMUNITY_PRIVATE_SITES_WITH_NO_LAYOUTS = "my.places.show.community.private.sites.with.no.layouts";

	// Nested Portlet Portlet

	public static final String NESTED_PORTLETS_LAYOUT_TEMPLATE_DEFAULT = "nested.portlets.layout.template.default";

	public static final String NESTED_PORTLETS_LAYOUT_TEMPLATE_UNSUPPORTED = "nested.portlets.layout.template.unsupported";

	// Portlet CSS Portlet

	public static final String PORTLET_CSS_ENABLED = "portlet.css.enabled";

	// Shopping Portlet

	public static final String SHOPPING_CART_MIN_QTY_MULTIPLE = "shopping.cart.min.qty.multiple";

	public static final String SHOPPING_CATEGORY_FORWARD_TO_CART = "shopping.category.forward.to.cart";

	public static final String SHOPPING_CATEGORY_SHOW_SPECIAL_ITEMS = "shopping.category.show.special.items";

	public static final String SHOPPING_ITEM_SHOW_AVAILABILITY = "shopping.item.show.availability";

	public static final String SHOPPING_IMAGE_SMALL_MAX_SIZE = "shopping.image.small.max.size";

	public static final String SHOPPING_IMAGE_MEDIUM_MAX_SIZE = "shopping.image.medium.max.size";

	public static final String SHOPPING_IMAGE_LARGE_MAX_SIZE = "shopping.image.large.max.size";

	public static final String SHOPPING_IMAGE_EXTENSIONS = "shopping.image.extensions";

	public static final String SHOPPING_EMAIL_FROM_NAME = "shopping.email.from.name";

	public static final String SHOPPING_EMAIL_FROM_ADDRESS = "shopping.email.from.address";

	public static final String SHOPPING_EMAIL_ORDER_CONFIRMATION_ENABLED = "shopping.email.order.confirmation.enabled";

	public static final String SHOPPING_EMAIL_ORDER_CONFIRMATION_SUBJECT = "shopping.email.order.confirmation.subject";

	public static final String SHOPPING_EMAIL_ORDER_CONFIRMATION_BODY = "shopping.email.order.confirmation.body";

	public static final String SHOPPING_EMAIL_ORDER_SHIPPING_ENABLED = "shopping.email.order.shipping.enabled";

	public static final String SHOPPING_EMAIL_ORDER_SHIPPING_SUBJECT = "shopping.email.order.shipping.subject";

	public static final String SHOPPING_EMAIL_ORDER_SHIPPING_BODY = "shopping.email.order.shipping.body";

	// Software Catalog Portlet

	public static final String SC_IMAGE_MAX_SIZE = "sc.image.max.size";

	public static final String SC_IMAGE_THUMBNAIL_MAX_HEIGHT = "sc.image.thumbnail.max.height";

	public static final String SC_IMAGE_THUMBNAIL_MAX_WIDTH = "sc.image.thumbnail.max.width";

	// Tags Compiler Portlet

	public static final String TAGS_COMPILER_ENABLED = "tags.compiler.enabled";

	// Tags Portlet

	public static final String TAGS_ASSET_VALIDATOR = "tags.asset.validator";

	// Translator Portlet

	public static final String TRANSLATOR_DEFAULT_LANGUAGES = "translator.default.languages";

	// Web Form Portlet

	public static final String WEB_FORM_PORTLET_MAX_FIELDS = "web.form.portlet.max.fields";

	// Wiki Portlet

	public static final String WIKI_CLASSIC_SYNTAX_HELP_URL = "wiki.classic.syntax.help.url";

	public static final String WIKI_FRONT_PAGE_NAME = "wiki.front.page.name";

	public static final String WIKI_INITIAL_NODE_NAME = "wiki.initial.node.name";

	public static boolean containsKey(String key) {
		return _getInstance().containsKey(key);
	}

	public static String get(String key) {
		return _getInstance().get(key);
	}

	public static String get(long companyId, String key) {
		return _getInstance(companyId).get(key);
	}

	public static void set(String key, String value) {
		_getInstance().set(key, value);
	}

	public static void set(long companyId, String key, String value) {
		_getInstance(companyId).set(key, value);
	}

	public static String[] getArray(String key) {
		return _getInstance().getArray(key);
	}

	public static Properties getProperties() {
		return _getInstance().getProperties();
	}

	public static ComponentProperties getComponentProperties() {
		return _getInstance().getComponentProperties();
	}

	private static ExtPropertiesLoader _getInstance() {
		long companyId = CompanyThreadLocal.getCompanyId();

		return _getInstance(companyId);
	}

	private static ExtPropertiesLoader _getInstance(long companyId) {
		if (companyId > CompanyImpl.SYSTEM) {
			return ExtPropertiesLoader
					.getInstance(PropsFiles.PORTAL, companyId);
		}
		else {
			return ExtPropertiesLoader.getInstance(PropsFiles.PORTAL);
		}
	}

}