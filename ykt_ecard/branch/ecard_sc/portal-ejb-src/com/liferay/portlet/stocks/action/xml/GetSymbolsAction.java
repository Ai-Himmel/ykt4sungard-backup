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

package com.liferay.portlet.stocks.action.xml;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.stocks.model.Stocks;
import com.liferay.portlet.stocks.util.StocksUtil;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.servlet.ServletResponseUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.PortletPreferences;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="GetSymbolsAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class GetSymbolsAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String fileName = null;
			byte[] byteArray = _getSymbols(req);

			ServletResponseUtil.sendFile(
				res, fileName, byteArray, Constants.TEXT_XML);

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (PrincipalException pe) {
			SessionErrors.add(req, pe.getClass().getName());

			return mapping.findForward(Constants.PORTAL_ERROR);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

	private byte[] _getSymbols(HttpServletRequest req) throws Exception {
		FastStringBuffer sb = new FastStringBuffer();

		sb.append("<stocks>\n");

		PortletPreferences prefs = StocksUtil.getPreferences(req);

		String[] symbols = prefs.getValues("symbols", new String[0]);

		for (int i = 0; i < symbols.length; i++) {
			Stocks stocks = StocksUtil.getStocks(symbols[i]);

			sb.append("\t<stock ");

			sb.append("symbol=\"");
			sb.append(stocks.getSymbol());
			sb.append("\" ");

			sb.append("last-trade=\"");
			sb.append(stocks.getLastTrade());
			sb.append("\" ");

			sb.append("last-trade-available=\"");
			sb.append(stocks.isLastTradeAvailable());
			sb.append("\" ");

			sb.append("change=\"");
			sb.append(stocks.getChange());
			sb.append("\" ");

			sb.append("change-available=\"");
			sb.append(stocks.isChangeAvailable());
			sb.append("\" ");

			sb.append("open=\"");
			sb.append(stocks.getOpen());
			sb.append("\" ");

			sb.append("open-available=\"");
			sb.append(stocks.isOpenAvailable());
			sb.append("\" ");

			sb.append("day-high=\"");
			sb.append(stocks.getDayHigh());
			sb.append("\" ");

			sb.append("day-high-available=\"");
			sb.append(stocks.isDayHighAvailable());
			sb.append("\" ");

			sb.append("day-low=\"");
			sb.append(stocks.getDayLow());
			sb.append("\" ");

			sb.append("day-low-available=\"");
			sb.append(stocks.isDayLowAvailable());
			sb.append("\" ");

			sb.append("volume=\"");
			sb.append(stocks.getVolume());
			sb.append("\" ");

			sb.append("volume-available=\"");
			sb.append(stocks.isVolumeAvailable());
			sb.append("\" ");

			sb.append("/>\n");
		}

		sb.append("</stocks>");

		return sb.toString().getBytes();
	}

}