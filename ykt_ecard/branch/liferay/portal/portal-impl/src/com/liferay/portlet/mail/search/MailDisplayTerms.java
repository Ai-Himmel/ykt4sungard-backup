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

package com.liferay.portlet.mail.search;

import com.liferay.portal.PortalException;
import com.liferay.portal.kernel.dao.search.DisplayTerms;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;

import java.util.Calendar;
import java.util.Date;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="MailDisplayTerms.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class MailDisplayTerms extends DisplayTerms {

	public static String[] DATE_RANGE_OPTIONS = new String[] {
		"any-day", "1-day", "3-days", "1-week", "2-weeks", "1-month",
		"2-months", "6-months", "1-year"
	};

	public static String FOLDER_NAME =
		MailDisplayTerms.class.getName() + "folderName";

	public static String FROM = MailDisplayTerms.class.getName() + "from";

	public static String TO = MailDisplayTerms.class.getName() + "to";

	public static String SUBJECT = MailDisplayTerms.class.getName() + "subject";

	public static String ENTIRE_MESSAGE =
		MailDisplayTerms.class.getName() + "entireMessage";

	public MailDisplayTerms(HttpServletRequest req) {
		super(req);

		folderName = ParamUtil.getString(req, FOLDER_NAME);
		from = ParamUtil.getString(req, FROM);
		to = ParamUtil.getString(req, TO);
		subject = ParamUtil.getString(req, SUBJECT);
		entireMessage = ParamUtil.getString(req, ENTIRE_MESSAGE);

		try {
			String range = ParamUtil.getString(req, "dateRange");

			if (Validator.isNotNull(range) &&
				!DATE_RANGE_OPTIONS[0].equals(range)) {

				ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
					WebKeys.THEME_DISPLAY);

				int dateMonth = ParamUtil.getInteger(req, "dateMonth");
				int dateDay = ParamUtil.getInteger(req, "dateDay");
				int dateYear = ParamUtil.getInteger(req, "dateYear");

				Date date =
					PortalUtil.getDate(
						dateMonth, dateDay, dateYear,
						themeDisplay.getTimeZone(), null);

				Calendar startCal =
					Calendar.getInstance(
						themeDisplay.getTimeZone(), themeDisplay.getLocale());

				startCal.setTime(date);

				Calendar endCal = (Calendar)startCal.clone();

				int ordinal = GetterUtil.getInteger(range.substring(0, 1));

				if (ordinal > 0) {
					if (range.indexOf("day") != -1) {
						startCal.add(Calendar.DATE, -ordinal);
						endCal.add(Calendar.DATE, ordinal);
					}
					else if (range.indexOf("week") != -1) {
						startCal.add(Calendar.WEEK_OF_YEAR, -ordinal);
						endCal.add(Calendar.WEEK_OF_YEAR, ordinal);
					}
					else if (range.indexOf("month") != -1) {
						startCal.add(Calendar.MONTH, -ordinal);
						endCal.add(Calendar.MONTH, ordinal);
					}
					else if (range.indexOf("year") != -1) {
						startCal.add(Calendar.YEAR, -ordinal);
						endCal.add(Calendar.YEAR, ordinal);
					}

					startDate = startCal.getTime();
					endDate = endCal.getTime();
				}
			}
		}
		catch (PortalException pe) {
		}
	}

	public String getFolderName() {
		return folderName;
	}

	public void setFolderName(String folderName) {
		this.folderName = folderName;
	}

	public String getFrom() {
		return from;
	}

	public String getTo() {
		return to;
	}

	public String getSubject() {
		return subject;
	}

	public String getEntireMessage() {
		return entireMessage;
	}

	public boolean hasDate() {
		if (startDate != null) {
			return true;
		}
		else {
			return false;
		}
	}

	public Date getStartDate() {
		return startDate;
	}

	public Date getEndDate() {
		return endDate;
	}

	protected String folderName;
	protected String from;
	protected String to;
	protected String subject;
	protected String entireMessage;
	protected Date startDate;
	protected Date endDate;

}