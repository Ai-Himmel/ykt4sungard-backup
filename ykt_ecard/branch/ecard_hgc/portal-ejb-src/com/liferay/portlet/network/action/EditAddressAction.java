/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.network.action;

import com.liferay.portal.struts.ActionException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.network.AddressNameException;
import com.liferay.portlet.network.AddressURLException;
import com.liferay.portlet.network.NoSuchAddressException;
import com.liferay.portlet.network.model.NetworkAddress;
import com.liferay.portlet.network.service.spring.NetworkAddressServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditAddressAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class EditAddressAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editAddress(req);

				_updateAddress(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof AddressNameException ||
					e instanceof AddressURLException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.network.edit_address");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteAddress(req, res);
			}
			catch (ActionException ae) {
				req.setAttribute(PageContext.EXCEPTION, ae.getCause());

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				_editAddress(req);

				setForward(req, "portlet.network.edit_address");
			}
			catch (ActionException ae) {
				req.setAttribute(PageContext.EXCEPTION, ae.getCause());

				setForward(req, Constants.COMMON_ERROR);
			}
		}

		setForward(req, "portlet.network.edit_address");
	}

	private void _deleteAddress(ActionRequest req, ActionResponse res)
		throws Exception {

		String addressId = ParamUtil.getString(req, "address_id");

		NetworkAddressServiceUtil.deleteAddress(addressId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editAddress(ActionRequest req) throws Exception {
		String addressId = req.getParameter("address_id");

		// Find address

		NetworkAddress address = null;

		if (Validator.isNotNull(addressId)) {
			try {
				address = NetworkAddressServiceUtil.getAddress(addressId);
			}
			catch (NoSuchAddressException nsae) {
			}
		}

		req.setAttribute(WebKeys.NETWORK_ADDRESS, address);
	}

	private void _updateAddress(ActionRequest req, ActionResponse res)
		throws Exception {

		String addressId = ParamUtil.getString(req, "address_id");

		String name = ParamUtil.getString(req, "address_name");
		String url = ParamUtil.getString(req, "address_url");
		String comments = ParamUtil.getString(req, "address_comments");
		String notifyBy = ParamUtil.get(
			req, "address_notify_by", NetworkAddress.NOTIFY_BY_NONE);
		long interval = ParamUtil.get(req, "address_interval", 0);
		boolean active = ParamUtil.get(req, "address_active", false);

		if (Validator.isNull(addressId)) {
			NetworkAddressServiceUtil.addAddress(
				name, url, comments, notifyBy, interval, active);
		}
		else {
			NetworkAddressServiceUtil.updateAddress(
				addressId, name, url, comments, notifyBy, interval, active);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}