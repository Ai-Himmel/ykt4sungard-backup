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

import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="GroupSearch.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupSearch extends SearchContainer {

	static List headerNames = new ArrayList();
	static Map orderableHeaders = CollectionFactory.getHashMap();

	static {
		headerNames.add("name");
		headerNames.add("type");

		orderableHeaders.put("name", "name");
		orderableHeaders.put("type", "type");
	}

	public static final String EMPTY_RESULTS_MESSAGE =
		"no-communities-were-found";

	public GroupSearch(RenderRequest req, PortletURL iteratorURL) {
		super(req, new GroupDisplayTerms(req), new GroupSearchTerms(req),
			  DEFAULT_CUR_PARAM, DEFAULT_DELTA, iteratorURL, headerNames,
			  EMPTY_RESULTS_MESSAGE);

		GroupDisplayTerms displayTerms = (GroupDisplayTerms)getDisplayTerms();

		iteratorURL.setParameter(
			GroupDisplayTerms.NAME, displayTerms.getName());
		iteratorURL.setParameter(
			GroupDisplayTerms.DESCRIPTION, displayTerms.getDescription());

		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String orderByCol = ParamUtil.getString(req, "orderByCol");
			String orderByType = ParamUtil.getString(req, "orderByType");

			if (Validator.isNotNull(orderByCol) &&
				Validator.isNotNull(orderByType)) {

				prefs.setValue(
					PortletKeys.ENTERPRISE_ADMIN, "groups-order-by-col",
					orderByCol);
				prefs.setValue(
					PortletKeys.ENTERPRISE_ADMIN, "groups-order-by-type",
					orderByType);
			}
			else {
				orderByCol = prefs.getValue(
					PortletKeys.ENTERPRISE_ADMIN, "groups-order-by-col",
					"name");
				orderByType = prefs.getValue(
					PortletKeys.ENTERPRISE_ADMIN, "groups-order-by-type",
					"asc");
			}

			OrderByComparator orderByComparator =
				EnterpriseAdminUtil.getGroupOrderByComparator(
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

	private static Log _log = LogFactory.getLog(GroupSearch.class);

}