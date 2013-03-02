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

package com.liferay.portlet.stocks.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.stocks.model.Stocks;
import com.liferay.util.ConverterException;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.Time;

import java.util.StringTokenizer;

/**
 * <a href="StocksConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class StocksConverter implements WebCacheable {

	public StocksConverter(String symbol) {
		_symbol = symbol;
	}

	public Object convert(String id) throws ConverterException {
		String symbol = _symbol;
		double lastTrade = 0.0;
		double change = 0.0;
		double open = 0.0;
		double dayHigh = 0.0;
		double dayLow = 0.0;
		long volume = 0;

		Stocks stocks = new Stocks(
			symbol, lastTrade, change, open, dayHigh, dayLow, volume);

		try {
			String text = Http.URLtoString(
				"http://finance.yahoo.com/d/quotes.csv?s=" +
				symbol + "&f=sl1d1t1c1ohgv&e=.csv");

			StringTokenizer st = new StringTokenizer(text, StringPool.COMMA);

			// Skip symbol

			st.nextToken();

			try {
				lastTrade = Double.parseDouble(
					st.nextToken().replace('"', ' ').trim());

				stocks.setLastTrade(lastTrade);
			}
			catch (NumberFormatException nfe) {
				stocks.setLastTradeAvailable(false);
			}

			// Skip date and time

			st.nextToken();
			st.nextToken();

			try {
				change = Double.parseDouble(
					st.nextToken().replace('"', ' ').trim());

				stocks.setChange(change);
			}
			catch (NumberFormatException nfe) {
				stocks.setChangeAvailable(false);
			}

			try {
				open = Double.parseDouble(
					st.nextToken().replace('"', ' ').trim());

				stocks.setOpen(open);
			}
			catch (NumberFormatException nfe) {
				stocks.setOpenAvailable(false);
			}

			try {
				dayHigh = Double.parseDouble(
					st.nextToken().replace('"', ' ').trim());

				stocks.setDayHigh(dayHigh);
			}
			catch (NumberFormatException nfe) {
				stocks.setDayHighAvailable(false);
			}

			try {
				dayLow = Double.parseDouble(
					st.nextToken().replace('"', ' ').trim());

				stocks.setDayLow(dayLow);
			}
			catch (NumberFormatException nfe) {
				stocks.setDayLowAvailable(false);
			}

			try {
				volume = Long.parseLong(
					st.nextToken().replace('"', ' ').trim());

				stocks.setVolume(volume);
			}
			catch (NumberFormatException nfe) {
				stocks.setVolumeAvailable(false);
			}

			if (!stocks.isValid()) {
				throw new ConverterException(symbol);
			}
		}
		catch (Exception e) {
			throw new ConverterException(symbol + " " + e.toString());
		}

		return stocks;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

	private String _symbol;

}