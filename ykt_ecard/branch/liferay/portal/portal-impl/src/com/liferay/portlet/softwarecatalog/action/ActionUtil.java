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

package com.liferay.portlet.softwarecatalog.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion;
import com.liferay.portlet.softwarecatalog.model.SCLicense;
import com.liferay.portlet.softwarecatalog.model.SCProductEntry;
import com.liferay.portlet.softwarecatalog.model.SCProductVersion;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionServiceUtil;
import com.liferay.portlet.softwarecatalog.service.SCLicenseServiceUtil;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryServiceUtil;
import com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceUtil;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class ActionUtil {

	public static void getFrameworkVersion(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFrameworkVersion(httpReq);
	}

	public static void getFrameworkVersion(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFrameworkVersion(httpReq);
	}

	public static void getFrameworkVersion(HttpServletRequest req)
		throws Exception {

		long frameworkVersionId = ParamUtil.getLong(req, "frameworkVersionId");

		SCFrameworkVersion frameworkVersion = null;

		if (frameworkVersionId > 0) {
			frameworkVersion =
				SCFrameworkVersionServiceUtil.getFrameworkVersion(
					frameworkVersionId);
		}

		req.setAttribute(
			WebKeys.SOFTWARE_CATALOG_FRAMEWORK_VERSION, frameworkVersion);
	}

	public static void getLicense(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getLicense(httpReq);
	}

	public static void getLicense(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getLicense(httpReq);
	}

	public static void getLicense(HttpServletRequest req) throws Exception {
		long licenseId = ParamUtil.getLong(req, "licenseId");

		SCLicense license = null;

		if (licenseId > 0) {
			license = SCLicenseServiceUtil.getLicense(licenseId);
		}

		req.setAttribute(WebKeys.SOFTWARE_CATALOG_LICENSE, license);
	}

	public static void getProductEntry(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getProductEntry(httpReq);
	}

	public static void getProductEntry(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getProductEntry(httpReq);
	}

	public static void getProductEntry(HttpServletRequest req)
		throws Exception {

		long productEntryId = ParamUtil.getLong(req, "productEntryId");

		SCProductEntry productEntry = null;

		if (productEntryId > 0) {
			productEntry = SCProductEntryServiceUtil.getProductEntry(
				productEntryId);
		}

		req.setAttribute(
			WebKeys.SOFTWARE_CATALOG_PRODUCT_ENTRY, productEntry);
	}

	public static void getProductVersion(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getProductVersion(httpReq);
	}

	public static void getProductVersion(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getProductVersion(httpReq);
	}

	public static void getProductVersion(HttpServletRequest req)
		throws Exception {

		long productVersionId = ParamUtil.getLong(req, "productVersionId");
		long copyProductVersionId = ParamUtil.getLong(
			req, "copyProductVersionId");

		SCProductVersion productVersion = null;
		SCProductEntry productEntry = null;

		if (productVersionId > 0) {
			productVersion = SCProductVersionServiceUtil.getProductVersion(
				productVersionId);

			productEntry = SCProductEntryServiceUtil.getProductEntry(
				productVersion.getProductEntryId());

			req.setAttribute(
				WebKeys.SOFTWARE_CATALOG_PRODUCT_VERSION, productVersion);

			req.setAttribute(
				WebKeys.SOFTWARE_CATALOG_PRODUCT_ENTRY, productEntry);
		}
		else if (copyProductVersionId > 0) {
			productVersion = SCProductVersionServiceUtil.getProductVersion(
				copyProductVersionId);

			productEntry = SCProductEntryServiceUtil.getProductEntry(
				productVersion.getProductEntryId());

			req.setAttribute(
				WebKeys.SOFTWARE_CATALOG_PRODUCT_VERSION, productVersion);

			req.setAttribute(
				WebKeys.SOFTWARE_CATALOG_PRODUCT_ENTRY, productEntry);
		}
		else {
			getProductEntry(req);
		}
	}

}