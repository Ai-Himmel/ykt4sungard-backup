/*
 * Copyright 2000-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.wsrp4j.util;

import java.util.Locale;
import java.util.ArrayList;

public class LocaleHelper {
	private final static String LOCALE_SEPARATOR = "-";

	/**
	 * Gets the language code from a locales string representation, assuming
	 * that the provided locale has a format like [2 char language code]"-"[2 char country code].
	 * 
	 * @param locale The locale as <code>String</code>.
	 * @return The language code.
	 **/
	public static String getLanguageCode(String locale) {

		String code = "";

		int pos = locale.indexOf(LOCALE_SEPARATOR);

		if (pos != -1) {
			code = locale.substring(0, pos);

		}
		else if (locale.length() == 2) {
			//see if locale is language only
			code = locale;

		}
		else if ((pos = locale.indexOf("_")) != -1) {

			// see if separator is "_" instead of "-"
			code = locale.substring(0, pos);

		}

		return code;
	}

	/**
	 * Gets the country code from a locales string representation, assuming
	 * that the provided locale has a format like [2 char language code]"-"[2 char country code].
	 * 
	 * @param locale The locale as <code>String</code>.
	 * @return The country code.
	 **/
	public static String getCountryCode(String locale) {

		String code = "";

		int pos = locale.indexOf(LOCALE_SEPARATOR);

		if (pos != -1) {
			code = locale.substring(pos + 1, locale.length());

		}
		else if ((pos = locale.indexOf("_")) != -1) {

			// see if separator is "_" instead of "-"
			code = locale.substring(0, pos);
		}

		return code;
	}

	/**
	 * Convinence method to create a <code>Locale</code> object from a locales
	 * string representation, assuming that the provided locale has a format like 
	 * [2 char language code]"-"[2 char country code].
	 *
	 * @param locale The locale as <code>String</code>.
	 * @return The corresponding <code>Locale</code> object.
	 **/
	public static Locale getLocale(String locale) {
		return new Locale(getLanguageCode(locale), getCountryCode(locale));
	}

	/**
	 * The method takes a given <code>Locale</code> and returns a string
	 * representation which is conform to the WSRP standard.
	 * 
	 * @param locale The <code>Locale</code> to be formatted.
	 * @return A string representation of the given locale which is conform to the 
	 *          WSRP standard.    
	 **/
	public static String getWsrpLocale(Locale locale) {
		if (locale == null)
			return null;

		String lang = locale.getLanguage();
		String country = locale.getCountry();

		return lang
				+ ((country != null && !country.equals("")) ? "-" + country
						: "");
	}

	/**
	 * Convinence method to create a <code>Locale</code> object array from a locales
	 * string array representation, assuming that the provided locale has a format like 
	 * [2 char language code]"-"[2 char country code].
	 *
	 * @param locales The locale as <code>String</code>.
	 * @return The corresponding <code>Locale</code> object.
	 **/
	public static Locale[] getLocales(String[] locales) {

		ArrayList list = new ArrayList();

		for (int i = 0; i < locales.length; i++) {
			list.add(getLocale(locales[i]));
		}

		Locale[] typedArray = new Locale[locales.length];

		return (Locale[]) list.toArray(typedArray);
	}
}