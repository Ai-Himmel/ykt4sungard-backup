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

package com.liferay.portal.kernel.util;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

/**
 * <a href="LocaleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LocaleUtil {

	public static Locale fromLanguageId(String languageId) {
		return _instance._fromLanguageId(languageId);
	}

	public static Locale[] fromLanguageIds(String[] languageIds) {
		return _instance._fromLanguageIds(languageIds);
	}

	public static Locale getDefault() {
		return _instance._getDefault();
	}

	public static void setDefault(
		String userLanguage, String userCountry, String userVariant) {

		_instance._setDefault(userLanguage, userCountry, userVariant);
	}

	public static String toLanguageId(Locale locale) {
		return _instance._toLanguageId(locale);
	}

	public static String[] toLanguageIds(Locale[] locales) {
		return _instance._toLanguageIds(locales);
	}

	private LocaleUtil() {
		_locale = new Locale("en", "US");
	}

	private Locale _fromLanguageId(String languageId) {
		Locale locale = null;

		try {
			locale = (Locale)_locales.get(languageId);

			if (locale == null) {
				int pos = languageId.indexOf(StringPool.UNDERLINE);

				if (pos == -1) {
					locale = new Locale(languageId);
				}
				else {
					String languageCode = languageId.substring(0, pos);
					String countryCode = languageId.substring(
						pos + 1, languageId.length());

					locale = new Locale(languageCode, countryCode);
				}

				_locales.put(languageId, locale);
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(languageId + " is not a valid language id");
			}
		}

		if (locale == null) {
			locale = _locale;
		}

		return locale;
	}

	private Locale[] _fromLanguageIds(String[] languageIds) {
		Locale[] locales = new Locale[languageIds.length];

		for (int i = 0; i < languageIds.length; i++) {
			locales[i] = _fromLanguageId(languageIds[i]);
		}

		return locales;
	}

	private Locale _getDefault() {
		return _locale;
	}

	public void _setDefault(
		String userLanguage, String userCountry, String userVariant) {

		if (Validator.isNotNull(userLanguage) &&
			Validator.isNull(userCountry) && Validator.isNull(userVariant)) {

			_locale = new Locale(userLanguage);
		}
		else if (Validator.isNotNull(userLanguage) &&
				 Validator.isNotNull(userCountry) &&
				 Validator.isNull(userVariant)) {

			_locale = new Locale(userLanguage, userCountry);
		}
		else if (Validator.isNotNull(userLanguage) &&
				 Validator.isNotNull(userCountry) &&
				 Validator.isNotNull(userVariant)) {

			_locale = new Locale(userLanguage, userCountry, userVariant);
		}
	}

	private String _toLanguageId(Locale locale) {
		if (locale == null) {
			locale = _locale;
		}

		StringMaker sm = new StringMaker();

		sm.append(locale.getLanguage());

		if (Validator.isNotNull(locale.getCountry())) {
			sm.append(StringPool.UNDERLINE);
			sm.append(locale.getCountry());
		}

		return sm.toString();
	}

	private String[] _toLanguageIds(Locale[] locales) {
		String[] languageIds = new String[locales.length];

		for (int i = 0; i < locales.length; i++) {
			languageIds[i] = _toLanguageId(locales[i]);
		}

		return languageIds;
	}

	private static Log _log = LogFactoryUtil.getLog(LocaleUtil.class);

	private static LocaleUtil _instance = new LocaleUtil();

	private Locale _locale;
	private Map _locales = new HashMap();

}