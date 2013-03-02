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

package com.liferay.portlet.mail.action;

import com.liferay.mail.model.Filter;
import com.liferay.mail.service.MailServiceUtil;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.mail.util.recipient.RecipientFinder;
import com.liferay.portlet.mail.util.recipient.RecipientFinderLocator;
import com.liferay.util.servlet.SessionMessages;

import java.rmi.RemoteException;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletException;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.commons.collections.map.MultiValueMap;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPreferencesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditPreferencesAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		long userId = PortalUtil.getUserId(req);

		PortletPreferences prefs = req.getPreferences();

		String tabs1 = ParamUtil.getString(req, "tabs1");

		if (tabs1.equals("recipients")) {
			List recipientFinders = RecipientFinderLocator.getInstances();

			for (int i = 0; i < recipientFinders.size(); i++) {
				RecipientFinder recipientFinder =
					(RecipientFinder)recipientFinders.get(i);

				String rfName = recipientFinder.getClass().getName();

				boolean enabled = ParamUtil.getBoolean(req, rfName, true);

				prefs.setValue(rfName, String.valueOf(enabled));

				MultiValueMap options = recipientFinder.getOptions(userId);

				Iterator itr = options.keySet().iterator();

				while (itr.hasNext()) {
					String key =
						rfName + StringPool.PERIOD + (String)itr.next();

					String value = ParamUtil.getString(req, key);

					if (Validator.isNotNull(key)) {
						prefs.setValue(key, value);
					}
				}
			}
		}
		else if (tabs1.equals("filters")) {
			List filters = new ArrayList();
			List filterObjects = new ArrayList();

			for (int i = 0; i < 10; i++) {
				String emailAddress = ParamUtil.getString(
					req, "filterEmailAddress" + i);
				String folder = ParamUtil.getString(req, "filterFolder" + i);

				if (Validator.isNotNull(emailAddress) &&
					Validator.isNotNull(folder)) {

					filters.add(emailAddress + "[$FILTER_SEPARATOR$]" + folder);
					filterObjects.add(new Filter(emailAddress, folder));
				}
			}

			prefs.setValues(
				"filters", (String[])filters.toArray(new String[0]));

			String forwardAddress = GetterUtil.getString(
				prefs.getValue("forward-address", StringPool.BLANK));

			List emailAddresses = getEmailAddresses(
				forwardAddress, StringPool.SPACE);

			boolean leaveCopy = GetterUtil.getBoolean(
				prefs.getValue("leave-copy", StringPool.BLANK));

			try {
				MailServiceUtil.addForward(
					userId, filterObjects, emailAddresses, leaveCopy);
			}
			catch (SystemException se) {
				throw new PortletException(se);
			}
		}
		else if (tabs1.equals("forward-address")) {
			String forwardAddress = ParamUtil.getString(req, "forwardAddress");

			List emailAddresses = getEmailAddresses(forwardAddress, "\n");

			if (emailAddresses.size() > 0) {
				forwardAddress = StringUtil.merge(
					emailAddresses, StringPool.SPACE);
			}
			else {
				forwardAddress = StringPool.BLANK;
			}

			boolean leaveCopy = ParamUtil.getBoolean(req, "leaveCopy");

			prefs.setValue("forward-address", forwardAddress);
			prefs.setValue("leave-copy", String.valueOf(leaveCopy));

			List filterObjects = new ArrayList();

			String[] filters = prefs.getValues("filters", new String[0]);

			for (int i = 0; i < filters.length; i++) {
				String[] kvp = StringUtil.split(
					filters[i], "[$FILTER_SEPARATOR$]");

				if (kvp.length == 2) {
					String emailAddress = kvp[0];
					String folder = kvp[1];

					if (Validator.isNotNull(emailAddress) &&
						Validator.isNotNull(folder)) {

						filterObjects.add(new Filter(emailAddress, folder));
					}
				}
			}

			try {
				MailServiceUtil.addForward(
					userId, filterObjects, emailAddresses, leaveCopy);
			}
			catch (SystemException se) {
				throw new PortletException(se);
			}

			res.setRenderParameter("forwardAddress", forwardAddress);
		}
		else if (tabs1.equals("signature")) {
			String signature = ParamUtil.getString(req, "signature");

			prefs.setValue("signature", signature);
		}
		else if (tabs1.equals("vacation-message")) {
			String vacationMessage = ParamUtil.getString(
				req, "vacationMessage");

			prefs.setValue("vacation-message", vacationMessage);

			try {
				User user = PortalUtil.getUser(req);

				MailServiceUtil.addVacationMessage(
					user.getUserId(), user.getEmailAddress(), vacationMessage);
			}
			catch (RemoteException re) {
				throw new SystemException(re);
			}
			catch (SystemException se) {
				throw new PortletException(se);
			}
		}

		prefs.store();

		SessionMessages.add(req, config.getPortletName() + ".doEdit");
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward("portlet.mail.edit");
	}

	protected List getEmailAddresses(String forwardAddress, String delimiter) {
		String[] forwardAddressArray = StringUtil.split(
			forwardAddress, delimiter);

		List emailAddresses = new ArrayList();

		for (int i = 0; i < forwardAddressArray.length; i++) {
			if (Validator.isEmailAddress(forwardAddressArray[i])) {
				emailAddresses.add(forwardAddressArray[i]);
			}
		}

		return emailAddresses;
	}

}