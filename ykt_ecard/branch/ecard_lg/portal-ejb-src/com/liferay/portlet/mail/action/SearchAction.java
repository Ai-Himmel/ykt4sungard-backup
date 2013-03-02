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

package com.liferay.portlet.mail.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.model.SearchResult;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.List;

import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.internet.InternetAddress;
import javax.mail.search.AndTerm;
import javax.mail.search.BodyTerm;
import javax.mail.search.DateTerm;
import javax.mail.search.FromTerm;
import javax.mail.search.OrTerm;
import javax.mail.search.ReceivedDateTerm;
import javax.mail.search.RecipientTerm;
import javax.mail.search.SearchTerm;
import javax.mail.search.SentDateTerm;
import javax.mail.search.SubjectTerm;

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
 * @version $Revision: 1.3 $
 *
 */
public class SearchAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			_search(req);

			return mapping.findForward("portlet.mail.search_results");
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

	private void _search(RenderRequest req) throws Exception {
		String query = ParamUtil.getString(req, "search_query");
		if (Validator.isNull(query)) {
			return;
		}

		String[] folderNames = req.getParameterValues("search_folder_names");
		String[] areas = req.getParameterValues("search_area");
		String method = req.getParameter("search_method");

		List folders = new ArrayList();

		if ((folderNames != null) && (folderNames.length > 0)) {
			for (int i = 0; i < folderNames.length; i++) {
				Folder folder = MailUtil.getFolder(req, folderNames[i]);

				if (folder != null) {
					folders.add(folder);
				}
			}
		}

		if (folders.size() == 0) {
			return;
		}

		List terms = new ArrayList();

		if ((areas != null) && (areas.length > 0)) {
			for (int i = 0; i < areas.length; i++) {
				if (areas[i].equals("from")) {
					terms.add(new FromTerm(
						InternetAddress.parse(query, false)[0]));
				}
				else if (areas[i].equals("to")) {
					terms.add(new RecipientTerm(
						Message.RecipientType.TO,
						InternetAddress.parse(query, false)[0]));
				}
				else if (areas[i].equals("cc")) {
					terms.add(new RecipientTerm(
						Message.RecipientType.CC,
						InternetAddress.parse(query, false)[0]));
				}
				else if (areas[i].equals("bcc")) {
					terms.add(new RecipientTerm(
						Message.RecipientType.BCC,
						InternetAddress.parse(query, false)[0]));
				}
				else if (areas[i].equals("subject")) {
					terms.add(new SubjectTerm(query));
				}
				else if (areas[i].equals("body")) {
					terms.add(new BodyTerm(query));
				}
			}
		}

		if (terms.size() == 0) {
			terms.add(new FromTerm(InternetAddress.parse(query, false)[0]));
			terms.add(new SubjectTerm(query));
			terms.add(new BodyTerm(query));
		}

		SearchTerm searchTerm = null;

		if (Validator.isNull(method) || method.equals("and")) {
			if (terms.size() > 1) {
				searchTerm = new AndTerm(
					(SearchTerm[])terms.toArray(new SearchTerm[0]));
			}
			else {
				searchTerm = (SearchTerm)terms.get(0);
			}
		}
		else {
			if (terms.size() > 1) {
				searchTerm = new OrTerm(
					(SearchTerm[])terms.toArray(new SearchTerm[0]));
			}
			else {
				searchTerm = (SearchTerm)terms.get(0);
			}
		}

		List dateTerms = new ArrayList();

		String dateSearchMethod =
			ParamUtil.getString(req, "search_date_method", "tf");

		if (dateSearchMethod.equals("tf")) {
			int timeFrame = ParamUtil.get(req, "search_date_tf", 0);

			Calendar timeFrameCal = new GregorianCalendar();

			if (timeFrame == 1) {
				timeFrameCal.add(Calendar.DATE, -1);
			}
			else if (timeFrame == 2) {
				timeFrameCal.add(Calendar.WEEK_OF_YEAR, -1);
			}
			else if (timeFrame == 3) {
				timeFrameCal.add(Calendar.WEEK_OF_YEAR, -2);
			}
			else if (timeFrame == 4) {
				timeFrameCal.add(Calendar.MONTH, -1);
			}
			else if (timeFrame == 5) {
				timeFrameCal.add(Calendar.MONTH, -3);
			}
			else if (timeFrame == 6) {
				timeFrameCal.add(Calendar.MONTH, -6);
			}
			else if (timeFrame == 7) {
				timeFrameCal.add(Calendar.YEAR, -1);
			}

			if (timeFrame > 0 && timeFrame <= 7) {
				Date timeFrameDate = timeFrameCal.getTime();

				dateTerms.add(new OrTerm(
					new ReceivedDateTerm(DateTerm.GE, timeFrameDate),
					new SentDateTerm(DateTerm.GE, timeFrameDate)));
			}
		}
		else {
			DateFormat df = new SimpleDateFormat("mm/dd/yyyy");

			Date dateRangeFrom = ParamUtil.get(
				req, "search_date_dr_from", df, null);
			if (dateRangeFrom != null) {
				dateTerms.add(new OrTerm(
					new ReceivedDateTerm(DateTerm.GE, dateRangeFrom),
					new SentDateTerm(DateTerm.GE, dateRangeFrom)));
			}

			Date dateRangeTo = ParamUtil.get(
				req, "search_date_dr_to", df, null);
			if (dateRangeTo != null) {
				dateTerms.add(new OrTerm(
					new ReceivedDateTerm(DateTerm.LE, dateRangeTo),
					new SentDateTerm(DateTerm.LE, dateRangeTo)));
			}
		}

		SearchTerm fullSearchTerm = null;

		if (dateTerms.size() > 0) {
			fullSearchTerm = new AndTerm(
				searchTerm,
				new AndTerm(
					(SearchTerm[])dateTerms.toArray(new SearchTerm[0])));
		}
		else {
			fullSearchTerm = searchTerm;
		}

		List results = new ArrayList();

		for (int i = 0; i < folders.size(); i++) {
			Folder folder = (Folder)folders.get(i);
			Message[] messages = folder.search(fullSearchTerm);
			results.add(new SearchResult(folder.getName(), messages));
		}

		req.setAttribute(WebKeys.MAIL_SEARCH_RESULTS, results);
	}

}