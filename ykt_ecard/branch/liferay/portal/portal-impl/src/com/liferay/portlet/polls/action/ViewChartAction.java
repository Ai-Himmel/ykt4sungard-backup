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

package com.liferay.portlet.polls.action;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.polls.util.PollsUtil;

import java.io.OutputStream;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.general.DatasetUtilities;
import org.jfree.data.general.PieDataset;

/**
 * <a href="ViewChartAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ViewChartAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			long questionId = ParamUtil.getLong(req, "questionId");

			String chartType = ParamUtil.getString(req, "chartType", "pie");

			CategoryDataset dataset = PollsUtil.getVotesDataset(questionId);

			String chartName = LanguageUtil.get(
				themeDisplay.getCompanyId(), themeDisplay.getLocale(),
				"vote-results");
			String xName = LanguageUtil.get(
				themeDisplay.getCompanyId(), themeDisplay.getLocale(),
				"choice");
			String yName = LanguageUtil.get(
				themeDisplay.getCompanyId(), themeDisplay.getLocale(), "votes");

			JFreeChart chart = null;

			if (chartType.equals("area")) {
				chart = ChartFactory.createAreaChart(
					chartName, xName, yName, dataset,
					PlotOrientation.VERTICAL, true, false, false);
			}
			else if (chartType.equals("horizontal_bar")) {
				chart = ChartFactory.createBarChart(
					chartName, xName, yName, dataset,
					PlotOrientation.HORIZONTAL, true, false, false);
			}
			else if (chartType.equals("line")) {
				chart = ChartFactory.createLineChart(
					chartName, xName, yName, dataset,
					PlotOrientation.VERTICAL, true, false, false);
			}
			else if (chartType.equals("vertical_bar")) {
				chart = ChartFactory.createBarChart(
					chartName, xName, yName, dataset,
					PlotOrientation.VERTICAL, true, false, false);
			}
			else {
				PieDataset pieData =
					DatasetUtilities.createPieDatasetForRow(dataset, 0);

				chart = ChartFactory.createPieChart(
					chartName, pieData, true, false, false);
			}

			res.setContentType("image/jpeg");

			OutputStream out = res.getOutputStream();

			ChartUtilities.writeChartAsJPEG(out, chart, 400, 400);

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

}