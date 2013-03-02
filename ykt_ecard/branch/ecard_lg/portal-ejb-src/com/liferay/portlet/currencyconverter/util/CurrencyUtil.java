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

import com.liferay.portal.language.LanguageException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.util.WebCachePool;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.currencyconverter.model.Currency;
import com.liferay.util.CollectionFactory;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringPool;

import java.util.Iterator;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.struts.Globals;

/**
 * <a href="CurrencyUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.20 $
 *
 */
public class CurrencyUtil {

	public static Map getAllSymbols(PageContext pageContext)
		throws LanguageException {

		HttpSession ses = pageContext.getSession();

		Locale locale = (Locale)ses.getAttribute(Globals.LOCALE_KEY);

		String scpId =
			CurrencyUtil.class.getName() + ".symbols." + locale.toString();

		Map symbols = (Map)SimpleCachePool.get(scpId);

		if (symbols != null) {
			return symbols;
		}

		symbols = new TreeMap();

		Iterator itr = _instance._currencyIds.iterator();

		while (itr.hasNext()) {
			String symbol = (String)itr.next();

			symbols.put(LanguageUtil.get(pageContext, symbol), symbol);
		}

		SimpleCachePool.put(scpId, symbols);

		return symbols;
	}

	public static Currency getCurrency(String symbol) {
		WebCacheable wc = new CurrencyConverter(symbol);

		return (Currency)WebCachePool.get(
			CurrencyUtil.class.getName() + StringPool.PERIOD + symbol, wc);
	}

	public static boolean isCurrency(String symbol) {
		return _instance._currencyIds.contains(symbol);
	}

	private CurrencyUtil() {
		_currencyIds = CollectionFactory.getHashSet();
		_currencyIds.add("AFA");
		_currencyIds.add("ALL");
		_currencyIds.add("DZD");
		_currencyIds.add("ARS");
		_currencyIds.add("AWG");
		_currencyIds.add("AUD");
		_currencyIds.add("BSD");
		_currencyIds.add("BHD");
		_currencyIds.add("BDT");
		_currencyIds.add("BBD");
		_currencyIds.add("BYR");
		_currencyIds.add("BZD");
		_currencyIds.add("BMD");
		_currencyIds.add("BTN");
		_currencyIds.add("BOB");
		_currencyIds.add("BWP");
		_currencyIds.add("BRL");
		_currencyIds.add("GBP");
		_currencyIds.add("BND");
		_currencyIds.add("BGN");
		_currencyIds.add("BIF");
		_currencyIds.add("KHR");
		_currencyIds.add("CAD");
		_currencyIds.add("CVE");
		_currencyIds.add("KYD");
		_currencyIds.add("CLP");
		_currencyIds.add("CNY");
		_currencyIds.add("COP");
		_currencyIds.add("KMF");
		_currencyIds.add("CRC");
		_currencyIds.add("HRK");
		_currencyIds.add("CUP");
		_currencyIds.add("CYP");
		_currencyIds.add("CZK");
		_currencyIds.add("DKK");
		_currencyIds.add("DJF");
		_currencyIds.add("DOP");
		_currencyIds.add("XCD");
		_currencyIds.add("ECS");
		_currencyIds.add("EGP");
		_currencyIds.add("SVC");
		_currencyIds.add("ERN");
		_currencyIds.add("EEK");
		_currencyIds.add("ETB");
		_currencyIds.add("EUR");
		_currencyIds.add("FKP");
		_currencyIds.add("FJD");
		_currencyIds.add("GMD");
		_currencyIds.add("GHC");
		_currencyIds.add("GIP");
		_currencyIds.add("XAU");
		_currencyIds.add("GTQ");
		_currencyIds.add("GNF");
		_currencyIds.add("GYD");
		_currencyIds.add("HTG");
		_currencyIds.add("HNL");
		_currencyIds.add("HKD");
		_currencyIds.add("HUF");
		_currencyIds.add("ISK");
		_currencyIds.add("INR");
		_currencyIds.add("IDR");
		_currencyIds.add("IRR");
		_currencyIds.add("IQD");
		_currencyIds.add("ILS");
		_currencyIds.add("JMD");
		_currencyIds.add("JPY");
		_currencyIds.add("JOD");
		_currencyIds.add("KZT");
		_currencyIds.add("KES");
		_currencyIds.add("KRW");
		_currencyIds.add("KWD");
		_currencyIds.add("LAK");
		_currencyIds.add("LVL");
		_currencyIds.add("LBP");
		_currencyIds.add("LSL");
		_currencyIds.add("LRD");
		_currencyIds.add("LYD");
		_currencyIds.add("LTL");
		_currencyIds.add("MOP");
		_currencyIds.add("MKD");
		_currencyIds.add("MGF");
		_currencyIds.add("MWK");
		_currencyIds.add("MYR");
		_currencyIds.add("MVR");
		_currencyIds.add("MTL");
		_currencyIds.add("MRO");
		_currencyIds.add("MUR");
		_currencyIds.add("MXN");
		_currencyIds.add("MDL");
		_currencyIds.add("MNT");
		_currencyIds.add("MAD");
		_currencyIds.add("MZM");
		_currencyIds.add("MMK");
		_currencyIds.add("NAD");
		_currencyIds.add("NPR");
		_currencyIds.add("ANG");
		_currencyIds.add("NZD");
		_currencyIds.add("NIO");
		_currencyIds.add("NGN");
		_currencyIds.add("KPW");
		_currencyIds.add("NOK");
		_currencyIds.add("OMR");
		_currencyIds.add("XPF");
		_currencyIds.add("PKR");
		_currencyIds.add("XPD");
		_currencyIds.add("PAB");
		_currencyIds.add("PGK");
		_currencyIds.add("PYG");
		_currencyIds.add("PEN");
		_currencyIds.add("PHP");
		_currencyIds.add("XPT");
		_currencyIds.add("PLN");
		_currencyIds.add("QAR");
		_currencyIds.add("SDP");
		_currencyIds.add("ROL");
		_currencyIds.add("RUB");
		_currencyIds.add("RWF");
		_currencyIds.add("WST");
		_currencyIds.add("STD");
		_currencyIds.add("SAR");
		_currencyIds.add("SCR");
		_currencyIds.add("SLL");
		_currencyIds.add("XAG");
		_currencyIds.add("SGD");
		_currencyIds.add("SKK");
		_currencyIds.add("SIT");
		_currencyIds.add("SBD");
		_currencyIds.add("SOS");
		_currencyIds.add("ZAR");
		_currencyIds.add("LKR");
		_currencyIds.add("SHP");
		_currencyIds.add("SDD");
		_currencyIds.add("SRG");
		_currencyIds.add("SZL");
		_currencyIds.add("SEK");
		_currencyIds.add("CHF");
		_currencyIds.add("SYP");
		_currencyIds.add("TWD");
		_currencyIds.add("TZS");
		_currencyIds.add("THB");
		_currencyIds.add("TOP");
		_currencyIds.add("TTD");
		_currencyIds.add("TND");
		_currencyIds.add("TRL");
		_currencyIds.add("USD");
		_currencyIds.add("AED");
		_currencyIds.add("UGX");
		_currencyIds.add("UAH");
		_currencyIds.add("UYU");
		_currencyIds.add("VUV");
		_currencyIds.add("VEB");
		_currencyIds.add("VND");
		_currencyIds.add("YER");
		_currencyIds.add("YUM");
		_currencyIds.add("ZMK");
		_currencyIds.add("ZWD");
	}

	private static CurrencyUtil _instance = new CurrencyUtil();

	private Set _currencyIds;

}