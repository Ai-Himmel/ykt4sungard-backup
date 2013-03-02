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

package com.liferay.portlet.currencyconverter.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.currencyconverter.model.Currency;
import com.liferay.util.ConverterException;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.Time;

import java.util.StringTokenizer;

/**
 * <a href="CurrencyConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class CurrencyConverter implements WebCacheable {

	public CurrencyConverter(String symbol) {
		_symbol = symbol;
	}

	public Object convert(String id) throws ConverterException {
		String symbol = _symbol;
		double rate = 0.0;

		try {
			if (symbol.length() == 6) {
				String fromSymbol = symbol.substring(0, 3);
				String toSymbol = symbol.substring(3, 6);

				if (!CurrencyUtil.isCurrency(fromSymbol) ||
					!CurrencyUtil.isCurrency(toSymbol)) {

					throw new ConverterException(symbol);
				}
			}
			else if (symbol.length() == 3) {
				if (!CurrencyUtil.isCurrency(symbol)) {
					throw new ConverterException(symbol);
				}
			}
			else {
				throw new ConverterException(symbol);
			}

			String text = Http.URLtoString(
				"http://finance.yahoo.com/d/quotes.csv?s=" +
				symbol + "=X&f=sl1d1t1c1ohgv&e=.csv");

			StringTokenizer st = new StringTokenizer(text, StringPool.COMMA);

			// Skip symbol

			st.nextToken();

			rate = Double.parseDouble(st.nextToken().replace('"', ' ').trim());
		}
		catch (Exception e) {
			throw new ConverterException(e);
		}

		return new Currency(symbol, rate);
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

	private String _symbol;

}