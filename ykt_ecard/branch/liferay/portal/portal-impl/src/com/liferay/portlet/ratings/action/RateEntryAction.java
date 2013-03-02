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

package com.liferay.portlet.ratings.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.JSONAction;
import com.liferay.portlet.ratings.model.RatingsStats;
import com.liferay.portlet.ratings.service.RatingsEntryServiceUtil;
import com.liferay.portlet.ratings.service.RatingsStatsLocalServiceUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.json.JSONObject;

/**
 * <a href="RateEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RateEntryAction extends JSONAction {

	public String getJSON(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		String className = getClassName(req);
		long classPK = getClassPK(req);
		double score = ParamUtil.getDouble(req, "score");

		RatingsEntryServiceUtil.updateEntry(className, classPK, score);

		RatingsStats stats = RatingsStatsLocalServiceUtil.getStats(
			className, classPK);

		JSONObject jsonObj = new JSONObject();

		jsonObj.put("totalEntries", stats.getTotalEntries());
		jsonObj.put("totalScore", stats.getTotalScore());
		jsonObj.put("averageScore", stats.getAverageScore());

		return jsonObj.toString();
	}

	protected String getClassName(HttpServletRequest req) {
		return ParamUtil.getString(req, "className");
	}

	protected long getClassPK(HttpServletRequest req) {
		return ParamUtil.getLong(req, "classPK");
	}

}