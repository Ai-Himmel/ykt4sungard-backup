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

import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.model.PortletCategory;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.service.LayoutSetLocalServiceUtil;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.struts.MultiMessageResources;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceUtil;
import com.liferay.util.CookieUtil;
import com.liferay.util.Http;
import com.liferay.util.SetUtil;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;

/**
 * <a href="PortalInstances.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jose Oliver
 * @author Atul Patel
 * @author Mika Koivisto
 *
 */
public class PortalInstances {

	public static final String DEFAULT_VIRTUAL_HOST = "localhost";

	public static void addCompanyId(long companyId) {
		_instance._addCompanyId(companyId);
	}

	public static long getCompanyId(HttpServletRequest req) {
		return _instance._getCompanyId(req);
	}

	public static long[] getCompanyIds() {
		return _instance._getCompanyIds();
	}

	public static long getDefaultCompanyId() {
		return _instance._getDefaultCompanyId();
	}

	public static String[] getWebIds() {
		return _instance._getWebIds();
	}

	public static long initCompany(ServletContext ctx, String webId) {
		return _instance._initCompany(ctx, webId);
	}

	public static boolean isIgnoreHost(String host) {
		return _instance._isIgnoreHost(host);
	}

	public static boolean isIgnorePath(String path) {
		return _instance._isIgnorePath(path);
	}

	private PortalInstances() {
		_companyIds = new long[0];
		_ignoreHosts = SetUtil.fromArray(PropsUtil.getArray(
			PropsUtil.VIRTUAL_HOSTS_IGNORE_HOSTS));
		_ignorePaths = SetUtil.fromArray(PropsUtil.getArray(
			PropsUtil.VIRTUAL_HOSTS_IGNORE_PATHS));
	}

	private void _addCompanyId(long companyId) {
		long[] companyIds = new long[_companyIds.length + 1];

		System.arraycopy(
			_companyIds, 0, companyIds, 0, _companyIds.length);

		companyIds[_companyIds.length] = companyId;

		_companyIds = companyIds;
	}

	private long _getCompanyId(HttpServletRequest req) {
		if (_log.isDebugEnabled()) {
			_log.debug("Get company id");
		}

		Long companyIdObj = (Long)req.getAttribute(WebKeys.COMPANY_ID);

		if (_log.isDebugEnabled()) {
			_log.debug("Company id from request " + companyIdObj);
		}

		if (companyIdObj != null) {
			return companyIdObj.longValue();
		}

		String host = PortalUtil.getHost(req);

		if (_log.isDebugEnabled()) {
			_log.debug("Host " + host);
		}

		long companyId = _getCompanyIdByVirtualHost(host);

		if (_log.isDebugEnabled()) {
			_log.debug("Company id from host " + companyId);
		}

		if (companyId <= 0) {
			LayoutSet layoutSet = _getLayoutSetByVirtualHost(host);

			if (layoutSet != null) {
				companyId = layoutSet.getCompanyId();

				if (_log.isDebugEnabled()) {
					_log.debug(
						"Company id " + companyId + " is associated with " +
							"layout set " + layoutSet.getLayoutSetId());
				}

				req.setAttribute(WebKeys.VIRTUAL_HOST_LAYOUT_SET, layoutSet);
			}
		}

		if (companyId <= 0) {
			companyId = GetterUtil.getLong(
				CookieUtil.get(req.getCookies(), CookieKeys.COMPANY_ID));

			if (_log.isDebugEnabled()) {
				_log.debug("Company id from cookie " + companyId);
			}
		}

		if (companyId <= 0) {
			companyId = _getDefaultCompanyId();

			if (_log.isDebugEnabled()) {
				_log.debug("Default company id " + companyId);
			}
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Set company id " + companyId);
		}

		req.setAttribute(WebKeys.COMPANY_ID, new Long(companyId));

		CompanyThreadLocal.setCompanyId(companyId);

		return companyId;
	}

	private long _getCompanyIdByVirtualHost(String host) {
		if (Validator.isNull(host)) {
			return 0;
		}

		try {
			Iterator itr = CompanyLocalServiceUtil.getCompanies().iterator();

			while (itr.hasNext()) {
				Company company = (Company)itr.next();

				if (company.getVirtualHost().equals(host)) {
					return company.getCompanyId();
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		return 0;
	}

	private long[] _getCompanyIds() {
		return _companyIds;
	}

	private long _getDefaultCompanyId() {
		return _companyIds[0];
	}

	private LayoutSet _getLayoutSetByVirtualHost(String host) {
		if (Validator.isNull(host)) {
			return null;
		}

		if (_isIgnoreHost(host)) {
			return null;
		}

		try {
			return LayoutSetLocalServiceUtil.getLayoutSet(host);
		}
		catch (Exception e) {
			return null;
		}
	}

	private String[] _getWebIds() {
		if (_webIds != null) {
			return _webIds;
		}

		if (Validator.isNull(CompanyImpl.DEFAULT_WEB_ID)) {
			throw new RuntimeException("Default web id must not be null");
		}

		try {
			List companies = CompanyLocalServiceUtil.getCompanies();

			List webIdsList = new ArrayList(companies.size());

			Iterator itr = companies.iterator();

			while (itr.hasNext()) {
				Company company = (Company)itr.next();

				webIdsList.add(company.getWebId());
			}

			_webIds = (String[])webIdsList.toArray(new String[0]);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		if ((_webIds == null) || (_webIds.length == 0)) {
			_webIds = new String[] {CompanyImpl.DEFAULT_WEB_ID};
		}

		return _webIds;
	}

	private long _initCompany(ServletContext ctx, String webId) {

		// Begin initializing company

		if (_log.isDebugEnabled()) {
			_log.debug("Begin initializing company with web id " + webId);
		}

		long companyId = 0;

		try {
			Company company = CompanyLocalServiceUtil.checkCompany(webId);

			companyId = company.getCompanyId();
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		CompanyThreadLocal.setCompanyId(companyId);

		// Initialize display

		if (_log.isDebugEnabled()) {
			_log.debug("Initialize display");
		}

		try {
			String xml = Http.URLtoString(ctx.getResource(
				"/WEB-INF/liferay-display.xml"));

			PortletCategory portletCategory =
				(PortletCategory)WebAppPool.get(
					String.valueOf(companyId), WebKeys.PORTLET_CATEGORY);

			if (portletCategory == null) {
				portletCategory = new PortletCategory();
			}

			PortletCategory newPortletCategory =
				PortletLocalServiceUtil.getEARDisplay(xml);

			portletCategory.merge(newPortletCategory);

			WebAppPool.put(
				String.valueOf(companyId), WebKeys.PORTLET_CATEGORY,
				portletCategory);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Check journal content search

		if (_log.isDebugEnabled()) {
			_log.debug("Check journal content search");
		}

		if (GetterUtil.getBoolean(PropsUtil.get(
				CompanyImpl.SYSTEM,
				PropsUtil.JOURNAL_SYNC_CONTENT_SEARCH_ON_STARTUP)) ||
			GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.JOURNAL_SYNC_CONTENT_SEARCH_ON_STARTUP))) {

			try {
				JournalContentSearchLocalServiceUtil.checkContentSearches(
					companyId);
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}

		// LDAP Import

		try {
			if (PortalLDAPUtil.isImportOnStartup(companyId)) {
				PortalLDAPUtil.importFromLDAP(companyId);
			}
		}
		catch (Exception e){
			_log.error(e, e);
		}

		// Message resources

		if (_log.isDebugEnabled()) {
			_log.debug("Message resources");
		}

		MultiMessageResources messageResources =
			(MultiMessageResources)ctx.getAttribute(Globals.MESSAGES_KEY);

		messageResources.setServletContext(ctx);

		WebAppPool.put(
			String.valueOf(companyId), Globals.MESSAGES_KEY, messageResources);

		// Process application startup events

		if (_log.isDebugEnabled()) {
			_log.debug("Process application startup events");
		}

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.APPLICATION_STARTUP_EVENTS),
				new String[] {String.valueOf(companyId)});
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// End initializing company

		if (_log.isDebugEnabled()) {
			_log.debug(
				"End initializing company with web id " + webId +
					" and company id " + companyId);
		}

		addCompanyId(companyId);

		return companyId;
	}

	private boolean _isIgnoreHost(String host) {
		return _ignoreHosts.contains(host);
	}

	private boolean _isIgnorePath(String path) {
		return _ignorePaths.contains(path);
	}

	private static Log _log = LogFactory.getLog(PortalInstances.class);

	private static PortalInstances _instance = new PortalInstances();

	private long[] _companyIds;
	private String[] _webIds;
	private Set _ignoreHosts;
	private Set _ignorePaths;

}