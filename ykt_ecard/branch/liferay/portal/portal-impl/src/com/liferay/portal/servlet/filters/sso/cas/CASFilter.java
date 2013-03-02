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

package com.liferay.portal.servlet.filters.sso.cas;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.CollectionFactory;
import com.liferay.util.servlet.filters.DynamicFilterConfig;

import java.io.IOException;

import java.util.Map;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * <a href="CASFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class CASFilter extends BaseFilter {

	public static void reload(long companyId) {
		_casFilters.remove(new Long(companyId));
	}

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		try {
			HttpServletRequest httpReq = (HttpServletRequest)req;

			long companyId = PortalUtil.getCompanyId(httpReq);

			if (PrefsPropsUtil.getBoolean(
					companyId, PropsUtil.CAS_AUTH_ENABLED,
					PropsValues.CAS_AUTH_ENABLED)) {

				String pathInfo = httpReq.getPathInfo();

				if (pathInfo.indexOf("/portal/logout") != -1) {
					HttpServletResponse httpRes = (HttpServletResponse)res;
					HttpSession httpSes = httpReq.getSession();

					httpSes.invalidate();

					String logoutUrl = PrefsPropsUtil.getString(
						companyId, PropsUtil.CAS_LOGOUT_URL);

					httpRes.sendRedirect(logoutUrl);
				}
				else {
					Filter casFilter = getCASFilter(companyId);

					casFilter.doFilter(req, res, chain);
				}
			}
			else {
				doFilter(CASFilter.class, req, res, chain);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	protected Filter getCASFilter(long companyId) throws Exception {
		Long companyIdObj = new Long(companyId);

		edu.yale.its.tp.cas.client.filter.CASFilter casFilter =
			(edu.yale.its.tp.cas.client.filter.CASFilter)_casFilters.get(
				companyIdObj);

		if (casFilter == null) {
			casFilter = new edu.yale.its.tp.cas.client.filter.CASFilter();

			DynamicFilterConfig config = new DynamicFilterConfig(
				_filterName, _ctx);

			String serverName = PrefsPropsUtil.getString(
				companyId, PropsUtil.CAS_SERVER_NAME);
			String serviceUrl = PrefsPropsUtil.getString(
				companyId, PropsUtil.CAS_SERVICE_URL);

			config.addInitParameter(
				edu.yale.its.tp.cas.client.filter.CASFilter.LOGIN_INIT_PARAM,
				PrefsPropsUtil.getString(companyId, PropsUtil.CAS_LOGIN_URL));

			if (Validator.isNotNull(serviceUrl)) {
				config.addInitParameter(
					edu.yale.its.tp.cas.client.filter.CASFilter.
						SERVICE_INIT_PARAM,
					serviceUrl);
			}
			else {
				config.addInitParameter(
					edu.yale.its.tp.cas.client.filter.CASFilter.
						SERVERNAME_INIT_PARAM,
					serverName);
			}

			config.addInitParameter(
				edu.yale.its.tp.cas.client.filter.CASFilter.VALIDATE_INIT_PARAM,
				PrefsPropsUtil.getString(
					companyId, PropsUtil.CAS_VALIDATE_URL));

			casFilter.init(config);

			_casFilters.put(companyIdObj, casFilter);
		}

		return casFilter;
	}

	private static Log _log = LogFactoryUtil.getLog(CASFilter.class);

	private static Map _casFilters = CollectionFactory.getSyncHashMap();

	private String _filterName;
	private ServletContext _ctx;

}