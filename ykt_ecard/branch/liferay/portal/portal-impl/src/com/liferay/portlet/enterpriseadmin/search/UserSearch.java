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

package com.liferay.portlet.enterpriseadmin.search;

import com.liferay.portal.kernel.dao.search.SearchContainer;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.PortalPreferences;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.enterpriseadmin.util.EnterpriseAdminUtil;
import com.liferay.util.CollectionFactory;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UserSearch.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserSearch extends SearchContainer {

	static List headerNames = new ArrayList();
	static Map orderableHeaders = CollectionFactory.getHashMap();

	static {
		headerNames.add("first-name");
//		headerNames.add("last-name");
		headerNames.add("screen-name");
		//headerNames.add("email-address");
		headerNames.add("job-title");
		headerNames.add("organizations");

		orderableHeaders.put("first-name", "first-name");
//		orderableHeaders.put("last-name", "last-name");
		orderableHeaders.put("screen-name", "screen-name");
		//orderableHeaders.put("email-address", "email-address");
		orderableHeaders.put("job-title", "job-title");
	}

	public static final String EMPTY_RESULTS_MESSAGE = "no-users-were-found";

	public UserSearch(RenderRequest req, PortletURL iteratorURL) {
		super(req, new UserDisplayTerms(req), new UserSearchTerms(req),
			  DEFAULT_CUR_PARAM, DEFAULT_DELTA, iteratorURL, headerNames,
			  EMPTY_RESULTS_MESSAGE);

		PortletConfig portletConfig = (PortletConfig)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		UserDisplayTerms displayTerms = (UserDisplayTerms)getDisplayTerms();
		UserSearchTerms searchTerms = (UserSearchTerms)getSearchTerms();

		String portletName = portletConfig.getPortletName();

		if (!portletName.equals(PortletKeys.ENTERPRISE_ADMIN) &&
			!portletName.equals(PortletKeys.ORGANIZATION_ADMIN)) {

			displayTerms.setActive(true);
			searchTerms.setActive(true);
		}

		iteratorURL.setParameter(
			UserDisplayTerms.FIRST_NAME, displayTerms.getFirstName());
		iteratorURL.setParameter(
			UserDisplayTerms.MIDDLE_NAME, displayTerms.getMiddleName());
		iteratorURL.setParameter(
			UserDisplayTerms.LAST_NAME, displayTerms.getLastName());
		iteratorURL.setParameter(
			UserDisplayTerms.SCREEN_NAME, displayTerms.getScreenName());
		iteratorURL.setParameter(
			UserDisplayTerms.EMAIL_ADDRESS, displayTerms.getEmailAddress());
		iteratorURL.setParameter(
			UserDisplayTerms.ACTIVE, String.valueOf(displayTerms.isActive()));
		iteratorURL.setParameter(
			UserDisplayTerms.ORGANIZATION_ID,
			String.valueOf(displayTerms.getOrganizationId()));
		iteratorURL.setParameter(
			UserDisplayTerms.ROLE_ID, String.valueOf(displayTerms.getRoleId()));
		iteratorURL.setParameter(
			UserDisplayTerms.USER_GROUP_ID,
			String.valueOf(displayTerms.getUserGroupId()));

		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String orderByCol = ParamUtil.getString(req, "orderByCol");
			String orderByType = ParamUtil.getString(req, "orderByType");

			if (Validator.isNotNull(orderByCol) &&
				Validator.isNotNull(orderByType)) {

				prefs.setValue(
					PortletKeys.ENTERPRISE_ADMIN, "users-order-by-col",
					orderByCol);
				prefs.setValue(
					PortletKeys.ENTERPRISE_ADMIN, "users-order-by-type",
					orderByType);
			}
			else {
				orderByCol = prefs.getValue(
					PortletKeys.ENTERPRISE_ADMIN, "users-order-by-col",
					"last-name");
				orderByType = prefs.getValue(
					PortletKeys.ENTERPRISE_ADMIN, "users-order-by-type", "asc");
			}

			OrderByComparator orderByComparator =
				EnterpriseAdminUtil.getUserOrderByComparator(
					orderByCol, orderByType);

			setOrderableHeaders(orderableHeaders);
			setOrderByCol(orderByCol);
			setOrderByType(orderByType);
			setOrderByComparator(orderByComparator);
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	private static Log _log = LogFactory.getLog(UserSearch.class);

}