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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.util.Constants;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderLocalServiceUtil;
import com.liferay.util.Http;
import com.liferay.util.ParamUtil;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import java.net.URL;
import java.net.URLConnection;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="PayPalNotificationAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class PayPalNotificationAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			_log.debug("Receiving notification from PayPal");

			String query = "cmd=_notify-validate";

			Enumeration enu = req.getParameterNames();

			while (enu.hasMoreElements()){
				String name = (String)enu.nextElement();
				String value = req.getParameter(name);

				query = query + "&" + name + "=" + Http.encodeURL(value);
			}

			_log.debug("Sending response to PayPal: " + query);

			URL url = new URL("http://www.paypal.com/cgi-bin/webscr");

			URLConnection urlc = url.openConnection();
			urlc.setDoOutput(true);
			urlc.setRequestProperty(
				"Content-Type","application/x-www-form-urlencoded");

			PrintWriter pw = new PrintWriter(urlc.getOutputStream());
			pw.println(query);
			pw.close();

			BufferedReader br = new BufferedReader(
				new InputStreamReader(urlc.getInputStream()));
			String payPalStatus = br.readLine();
			br.close();

			_log.debug("Receiving response from PayPal: " + payPalStatus);

			String itemName = ParamUtil.getString(req, "item_name");
			String itemNumber = ParamUtil.getString(req, "item_number");
			String invoice = ParamUtil.getString(req, "invoice");
			String txnId = ParamUtil.getString(req, "txn_id");
			String paymentStatus = ParamUtil.getString(req, "payment_status");
			double paymentGross = ParamUtil.get(req, "payment_gross", 0.0);
			String receiverEmail = ParamUtil.getString(req, "receiver_email");
			String payerEmail = ParamUtil.getString(req, "payer_email");

			if (payPalStatus.equals("VERIFIED")) {
				ShoppingOrderLocalServiceUtil.completeOrder(
					invoice, txnId, paymentStatus, paymentGross, receiverEmail,
					payerEmail, true);
			}
			else if (payPalStatus.equals("INVALID")) {
			}

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

	private static final Log _log =
		LogFactory.getLog(PayPalNotificationAction.class);

}