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

package com.liferay.portlet.directory.action;

import com.liferay.portal.service.spring.CompanyServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;

import java.util.Calendar;
import java.util.Collection;
import java.util.Date;
import java.util.GregorianCalendar;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="SearchAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class SearchAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if (Validator.isNotNull(cmd)) {
			try {
				_search(req);

				return mapping.findForward("portlet.directory.search_results");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else {
			return mapping.findForward("portlet.directory.search");
		}
	}

	private void _search(RenderRequest req) throws Exception {
		String cmd = ParamUtil.get(req, Constants.CMD, Constants.SEARCH);

		String firstName = req.getParameter("first_name");
		if (firstName != null) {
			firstName = firstName.toLowerCase().trim();
		}

		if (Validator.isNull(firstName)) {
			firstName = null;
		}
		else {
			firstName = "%" + firstName + "%";
		}

		String middleName = req.getParameter("middle_name");
		if (middleName != null) {
			middleName = middleName.toLowerCase().trim();
		}

		if (Validator.isNull(middleName)) {
			middleName = null;
		}
		else {
			middleName = "%" + middleName + "%";
		}

		String lastName = req.getParameter("last_name");
		if (lastName != null) {
			lastName = lastName.toLowerCase().trim();
		}

		if (Validator.isNull(lastName)) {
			lastName = null;
		}
		else {
			lastName = "%" + lastName + "%";
		}

		Boolean male = null;

		String sex = req.getParameter("sex");
		if (Validator.isNotNull(sex) && (sex.equals("male"))) {
			male = Boolean.TRUE;
		}
		else if (Validator.isNotNull(sex) && (sex.equals("female"))) {
			male = Boolean.FALSE;
		}

		Date age1 = null;
		Date age2 = null;

		String age = req.getParameter("age");

		if (Validator.isNotNull(age)) {
			int max = 200;
			int min = 65;

			if (!age.endsWith("+")) {
				int pos = age.indexOf('-');

				try {
					max = Integer.parseInt(
						age.substring(pos + 1, age.length()));

					min = Integer.parseInt(age.substring(0, pos));
				}
				catch (Exception e) {
				}
			}

			Calendar cal = new GregorianCalendar();
			cal.add(Calendar.YEAR, -max);
			cal.add(Calendar.DAY_OF_YEAR, -364);
			age1 = new Date(cal.getTime().getTime());

			cal.add(Calendar.YEAR, -min + max);
			cal.add(Calendar.DAY_OF_YEAR, 365);
			age2 = new Date(cal.getTime().getTime());
		}

		String emailAddress = req.getParameter("email_address");
		if (emailAddress != null) {
			emailAddress = emailAddress.toLowerCase().trim();
		}

		if (Validator.isNull(emailAddress)) {
			emailAddress = null;
		}
		else {
			emailAddress = "%" + emailAddress + "%";
		}

		String im = req.getParameter("im");
		if (im != null) {
			im = im.toLowerCase().trim();
		}

		if (Validator.isNull(im)) {
			im = null;
		}
		else {
			im = "%" + im + "%";
		}

		String street1 = req.getParameter("street_1");
		if (street1 != null) {
			street1 = street1.toLowerCase().trim();
		}

		if (Validator.isNull(street1)) {
			street1 = null;
		}
		else {
			street1 = "%" + street1 + "%";
		}

		String street2 = req.getParameter("street_2");
		if (street2 != null) {
			street2 = street2.toLowerCase().trim();
		}

		if (Validator.isNull(street2)) {
			street2 = null;
		}
		else {
			street2 = "%" + street2 + "%";
		}

		String city = req.getParameter("city");
		if (city != null) {
			city = city.toLowerCase().trim();
		}

		if (Validator.isNull(city)) {
			city = null;
		}
		else {
			city = "%" + city + "%";
		}

		String state = req.getParameter("state");
		if (state != null) {
			state = state.toLowerCase().trim();
		}

		if (Validator.isNull(state)) {
			state = null;
		}
		else {
			state = "%" + state + "%";
		}

		String zip = req.getParameter("zip");
		if (zip != null) {
			zip = zip.toLowerCase().trim();
		}

		if (Validator.isNull(zip)) {
			zip = null;
		}
		else {
			zip = "%" + zip + "%";
		}

		String phone = req.getParameter("phone");
		if (phone != null) {
			phone = phone.toLowerCase().trim();
		}

		if (Validator.isNull(phone)) {
			phone = null;
		}
		else {
			phone = "%" + phone + "%";
		}

		String fax = req.getParameter("fax");
		if (fax != null) {
			fax = fax.toLowerCase().trim();
		}

		if (Validator.isNull(fax)) {
			fax = null;
		}
		else {
			fax = "%" + fax + "%";
		}

		String cell = req.getParameter("cell");
		if (cell != null) {
			cell = cell.toLowerCase().trim();
		}

		if (Validator.isNull(cell)) {
			cell = null;
		}
		else {
			cell = "%" + cell + "%";
		}

		boolean andSearch = false;

		String searchType = req.getParameter("search_type");
		if ((searchType != null) && (searchType.equals("and"))) {
			andSearch = true;
		}

		Collection users = null;

		if ((Validator.isNull(firstName) &&
			 Validator.isNull(middleName) &&
			 Validator.isNull(lastName) &&
			 Validator.isNull(sex) &&
			 Validator.isNull(age) &&
			 Validator.isNull(emailAddress) &&
			 Validator.isNull(im) &&
			 Validator.isNull(street1) &&
			 Validator.isNull(street2) &&
			 Validator.isNull(city) &&
			 Validator.isNull(state) &&
			 Validator.isNull(zip) &&
			 Validator.isNull(phone) &&
			 Validator.isNull(fax) &&
			 Validator.isNull(cell)) ||
			 !cmd.equals(Constants.SEARCH)) {

			users = CompanyServiceUtil.getUsers();
		}
		else {
			if (andSearch) {
				users = UserServiceUtil.findByAnd_C_FN_MN_LN_EA_M_BD_IM_A(
					firstName, middleName, lastName, emailAddress, male, age1,
					age2, im, street1, street2, city, state, zip, phone, fax,
					cell);
			}
			else {
				users = UserServiceUtil.findByOr_C_FN_MN_LN_EA_M_BD_IM_A(
					firstName, middleName, lastName, emailAddress, male, age1,
					age2, im, street1, street2, city, state, zip, phone, fax,
					cell);
			}
		}

		req.setAttribute(WebKeys.DIRECTORY_SEARCH_RESULTS, users);
	}

}