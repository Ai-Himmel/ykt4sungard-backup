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

package com.liferay.portlet.globalprayerdigest;

import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.IFramePortlet;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.TimeZone;

import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="GlobalPrayerDigestPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class GlobalPrayerDigestPortlet extends IFramePortlet {

	protected String getSrc(RenderRequest req, RenderResponse res) {
		PortletPreferences prefs = req.getPreferences();

		String src = prefs.getValue("src", DEFAULT_SRC);

		TimeZone timeZone = TimeZone.getDefault();
		try {
			User user = PortalUtil.getUser(req);

			timeZone = user.getTimeZone();
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		Calendar cal = new GregorianCalendar(timeZone);

		src = src +
			  "?which=chosenday&whichyear=" + cal.get(Calendar.YEAR) +
			  "&whichmonth=" + (cal.get(Calendar.MONTH) + 1) +
			  "&whichday=" + cal.get(Calendar.DATE);

		return src;
	}

}