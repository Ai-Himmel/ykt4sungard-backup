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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.shopping.NoSuchOrderException;
import com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil;
import com.liferay.portlet.shopping.util.ShoppingUtil;
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
 * <a href="EditOrderAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditOrderAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateOrder(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteOrders(req);
			}
			else if (cmd.equals("sendEmail")) {
				sendEmail(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchOrderException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.shopping.error");
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
			ActionUtil.getOrder(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchOrderException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.shopping.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.shopping.edit_order"));
	}

	protected void deleteOrders(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long[] deleteOrderIds = StringUtil.split(
			ParamUtil.getString(req, "deleteOrderIds"), 0L);

		for (int i = 0; i < deleteOrderIds.length; i++) {
			ShoppingOrderServiceUtil.deleteOrder(
				layout.getPlid(), deleteOrderIds[i]);
		}
	}

	protected void sendEmail(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long orderId = ParamUtil.getLong(req, "orderId");

		String emailType = ParamUtil.getString(req, "emailType");

		ShoppingOrderServiceUtil.sendEmail(
			layout.getPlid(), orderId, emailType);
	}

	protected void updateOrder(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		String number = ParamUtil.getString(req, "number");
		String ppTxnId = ParamUtil.getString(req, "ppTxnId");
		String ppPaymentStatus = ShoppingUtil.getPpPaymentStatus(
			ParamUtil.getString(req, "ppPaymentStatus"));
		double ppPaymentGross = ParamUtil.getDouble(req, "ppPaymentGross");
		String ppReceiverEmail = ParamUtil.getString(req, "ppReceiverEmail");
		String ppPayerEmail = ParamUtil.getString(req, "ppPayerEmail");

		ShoppingOrderServiceUtil.completeOrder(
			layout.getPlid(), number, ppTxnId, ppPaymentStatus, ppPaymentGross,
			ppReceiverEmail, ppPayerEmail);
	}

}