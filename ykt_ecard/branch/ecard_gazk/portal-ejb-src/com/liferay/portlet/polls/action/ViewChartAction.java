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

package com.liferay.portlet.polls.action;

import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.polls.util.PollsUtil;
import com.liferay.util.ParamUtil;

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
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class ViewChartAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String questionId = ParamUtil.getString(req, "question_id");
			String chartType = ParamUtil.get(req, "question_chart", "pie");

			CategoryDataset dataset = PollsUtil.getVotesDataset(questionId);

			User user = PortalUtil.getUser(req);

			String chartName = LanguageUtil.get(user, "vote-results");
			String xName = LanguageUtil.get(user, "choice");
			String yName = LanguageUtil.get(user, "votes");

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

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}