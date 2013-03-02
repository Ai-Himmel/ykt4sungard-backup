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

package com.liferay.portlet.enterpriseadmin.action;

import com.liferay.portal.AddressCityException;
import com.liferay.portal.AddressStreetException;
import com.liferay.portal.AddressZipException;
import com.liferay.portal.NoSuchAddressException;
import com.liferay.portal.NoSuchCountryException;
import com.liferay.portal.NoSuchListTypeException;
import com.liferay.portal.NoSuchRegionException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.AddressServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditAddressAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditAddressAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateAddress(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteAddress(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchAddressException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof AddressCityException  ||
					 e instanceof AddressStreetException  ||
					 e instanceof AddressZipException ||
					 e instanceof NoSuchCountryException  ||
					 e instanceof NoSuchListTypeException ||
					 e instanceof NoSuchRegionException) {

				SessionErrors.add(req, e.getClass().getName());
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			ActionUtil.getAddress(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchAddressException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_address"));
	}

	protected void deleteAddress(ActionRequest req) throws Exception {
		long addressId = ParamUtil.getLong(req, "addressId");

		AddressServiceUtil.deleteAddress(addressId);
	}

	protected void updateAddress(ActionRequest req) throws Exception {
		long addressId = ParamUtil.getLong(req, "addressId");

		String className = ParamUtil.getString(req, "className");
		long classPK = ParamUtil.getLong(req, "classPK");

		String street1 = ParamUtil.getString(req, "street1");
		String street2 = ParamUtil.getString(req, "street2");
		String street3 = ParamUtil.getString(req, "street3");
		String city = ParamUtil.getString(req, "city");
		String zip = ParamUtil.getString(req, "zip");
		long regionId = ParamUtil.getLong(req, "regionId");
		long countryId = ParamUtil.getLong(req, "countryId");
		int typeId = ParamUtil.getInteger(req, "typeId");
		boolean mailing = ParamUtil.getBoolean(req, "mailing");
		boolean primary = ParamUtil.getBoolean(req, "primary");

		if (addressId <= 0) {

			// Add address

			AddressServiceUtil.addAddress(
				className, classPK, street1, street2, street3, city, zip,
				regionId, countryId, typeId, mailing, primary);
		}
		else {

			// Update address

			AddressServiceUtil.updateAddress(
				addressId, street1, street2, street3, city, zip, regionId,
				countryId, typeId, mailing, primary);
		}
	}

}