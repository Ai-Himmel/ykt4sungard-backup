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

package com.liferay.portlet.addressbook.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.addressbook.ContactEmailAddressException;
import com.liferay.portlet.addressbook.ContactFirstNameException;
import com.liferay.portlet.addressbook.ContactLastNameException;
import com.liferay.portlet.addressbook.DuplicateContactException;
import com.liferay.portlet.addressbook.service.spring.ABContactServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditContactAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class EditContactAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_updateContact(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof ContactEmailAddressException ||
					e instanceof ContactFirstNameException ||
					e instanceof ContactLastNameException ||
					e instanceof DuplicateContactException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.address_book.edit_contact");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals(Constants.DELETE))) {
			try {
				_deleteContact(req, res);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else {
			setForward(req, "portlet.address_book.edit_contact");
		}
	}

	private void _deleteContact(ActionRequest req, ActionResponse res)
		throws Exception {

		String contactId = req.getParameter("contact_id");

		ABContactServiceUtil.deleteContact(contactId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateContact(ActionRequest req, ActionResponse res)
		throws Exception {

		String contactId = ParamUtil.getString(req, "contact_id");

		String firstName = ParamUtil.getString(req, "contact_first_name");
		String middleName = ParamUtil.getString(req, "contact_middle_name");
		String lastName = ParamUtil.getString(req, "contact_last_name");
		String nickName = ParamUtil.getString(req, "contact_nick_name");
		String emailAddress = ParamUtil.getString(req, "contact_email_address");

		String hStreet = ParamUtil.getString(req, "contact_home_street");
		String hCity = ParamUtil.getString(req, "contact_home_city");
		String hState = ParamUtil.getString(req, "contact_home_state");
		String hZip = ParamUtil.getString(req, "contact_home_zip");
		String hCountry = ParamUtil.getString(req, "contact_home_country");
		String hPhone = ParamUtil.getString(req, "contact_home_phone");
		String hFax = ParamUtil.getString(req, "contact_home_fax");
		String hCell = ParamUtil.getString(req, "contact_home_cell");
		String hPager = ParamUtil.getString(req, "contact_home_pager");
		String hTollFree = ParamUtil.getString(req, "contact_home_toll_free");
		String hEmailAddress = ParamUtil.getString(
			req, "contact_home_email_address");

		String bCompany = ParamUtil.getString(req, "contact_biz_company");
		String bStreet = ParamUtil.getString(req, "contact_biz_street");
		String bCity = ParamUtil.getString(req, "contact_biz_city");
		String bState = ParamUtil.getString(req, "contact_biz_state");
		String bZip = ParamUtil.getString(req, "contact_biz_zip");
		String bCountry = ParamUtil.getString(req, "contact_biz_country");
		String bPhone = ParamUtil.getString(req, "contact_biz_phone");
		String bFax = ParamUtil.getString(req, "contact_biz_fax");
		String bCell = ParamUtil.getString(req, "contact_biz_cell");
		String bPager = ParamUtil.getString(req, "contact_biz_pager");
		String bTollFree = ParamUtil.getString(req, "contact_biz_toll_free");
		String bEmailAddress = ParamUtil.getString(
			req, "contact_biz_email_address");

		String employeeNumber = ParamUtil.getString(
			req, "contact_employee_number");
		String jobTitle = ParamUtil.getString(req, "contact_job_title");
		String jobClass = ParamUtil.getString(req, "contact_job_class");

		String hoursOfOperation = ParamUtil.getString(req, "contact_hop");

		String bdMonth = req.getParameter("contact_birthday_month");
		String bdDay = req.getParameter("contact_birthday_day");
		String bdYear = req.getParameter("contact_birthday_year");

		Date bdDate = null;

		if ((Validator.isNumber(bdMonth)) &&
			(Validator.isNumber(bdDay)) &&
			(Validator.isNumber(bdYear))) {

			Calendar birthday = new GregorianCalendar();
			birthday.set(Calendar.MONTH, Integer.parseInt(bdMonth));
			birthday.set(Calendar.DATE, Integer.parseInt(bdDay));
			birthday.set(Calendar.YEAR, Integer.parseInt(bdYear));

			bdDate = birthday.getTime();
		}

		String timeZoneId = ParamUtil.getString(req, "contact_time_zone_id");
		String instantMessenger = ParamUtil.getString(req, "contact_im");
		String website = ParamUtil.getString(req, "contact_website");
		String comments = ParamUtil.getString(req, "contact_comments");

		if (Validator.isNull(contactId)) {

			// Add contact

			ABContactServiceUtil.addContact(
				firstName, middleName, lastName, nickName, emailAddress,
				hStreet, hCity, hState, hZip, hCountry, hPhone, hFax, hCell,
				hPager, hTollFree, hEmailAddress, bCompany, bStreet, bCity,
				bState, bZip, bCountry, bPhone, bFax, bCell,  bPager, bTollFree,
				bEmailAddress, employeeNumber, jobTitle, jobClass,
				hoursOfOperation, bdDate, timeZoneId, instantMessenger, website,
				comments);
		}
		else {

			// Update contact

			ABContactServiceUtil.updateContact(
				contactId, firstName, middleName, lastName, nickName,
				emailAddress, hStreet, hCity, hState, hZip, hCountry, hPhone,
				hFax, hCell, hPager, hTollFree, hEmailAddress, bCompany,
				bStreet, bCity, bState, bZip, bCountry, bPhone, bFax, bCell,
				bPager, bTollFree, bEmailAddress, employeeNumber, jobTitle,
				jobClass, hoursOfOperation, bdDate, timeZoneId,
				instantMessenger, website, comments);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}