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

package com.liferay.util;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.xml.XMLFormatter;

import java.io.StringReader;

import java.util.Iterator;

import javax.portlet.PortletPreferences;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="LocalizationUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class LocalizationUtil {

	public static String[] getAvailableLocales(String xml) {
		String[] availableLocales = new String[0];

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			availableLocales = StringUtil.split(
				root.attributeValue("available-locales"));
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return availableLocales;
	}

	public static String getDefaultLocale(String xml) {
		String defaultLanguageId = LocaleUtil.toLanguageId(
			LocaleUtil.getDefault());

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			return root.attributeValue("default-locale", defaultLanguageId);
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return defaultLanguageId;
	}

	public static String getLocalization(
		String xml, String requestedLanguageId) {

		return getLocalization(xml, requestedLanguageId, true);
	}

	public static String getLocalization(
		String xml, String requestedLanguageId, boolean useDefault) {

		String defaultLanguageId = LocaleUtil.toLanguageId(
			LocaleUtil.getDefault());

		String value = StringPool.BLANK;

		String defaultValue = StringPool.BLANK;

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			Iterator itr = root.elements().iterator();

			while (itr.hasNext()) {
				Element el = (Element)itr.next();

				String languageId =
					el.attributeValue("language-id", defaultLanguageId);

				if (languageId.equals(defaultLanguageId)) {
					defaultValue = el.getText();
				}

				if (languageId.equals(requestedLanguageId)) {
					value = el.getText();
				}
			}

			if (useDefault && Validator.isNull(value)) {
				value = defaultValue;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return value;
	}

	public static String getPrefsValue(
		PortletPreferences prefs, String key, String languageId) {

		return getPrefsValue(prefs, key, languageId, true);
	}

	public static String getPrefsValue(
		PortletPreferences prefs, String key, String languageId,
		boolean useDefault) {

		String localizedKey = _getPrefsKey(key, languageId);

		String value = prefs.getValue(localizedKey, StringPool.BLANK);

		if (useDefault && Validator.isNull(value)) {
			value = prefs.getValue(key, StringPool.BLANK);
		}

		return value;
	}

	public static String[] getPrefsValues(
		PortletPreferences prefs, String key, String languageId) {

		return getPrefsValues(prefs, key, languageId, true);
	}

	public static String[] getPrefsValues(
		PortletPreferences prefs, String key, String languageId,
		boolean useDefault) {

		String localizedKey = _getPrefsKey(key, languageId);

		String[] values = prefs.getValues(localizedKey, new String[0]);

		if (useDefault && Validator.isNull(values)) {
			values = prefs.getValues(key, new String[0]);
		}

		return values;
	}

	public static String removeLocalization(
		String xml, String key, String requestedLanguageId) {

		if (Validator.isNull(xml) || (xml.indexOf("<root") == -1)) {
			xml = "<root />";
		}

		String defaultLanguageId =
			LocaleUtil.toLanguageId(LocaleUtil.getDefault());

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			String availableLocales = root.attributeValue("available-locales");

			defaultLanguageId =
				root.attributeValue("default-locale", defaultLanguageId);

			if (availableLocales.indexOf(requestedLanguageId) != -1) {
				Iterator itr = root.elements().iterator();

				while (itr.hasNext()) {
					Element el = (Element) itr.next();

					String languageId =
						el.attributeValue("language-id", defaultLanguageId);

					if (languageId.equals(requestedLanguageId)) {
						root.remove(el);

						break;
					}
				}

				availableLocales = StringUtil.remove(
					availableLocales, requestedLanguageId, StringPool.COMMA);

				root.addAttribute("available-locales", availableLocales);
			}

			xml = XMLFormatter.toString(doc, "  ");
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return xml;
	}

	public static void setPrefsValue(
			PortletPreferences prefs, String key, String languageId,
			String value)
		throws Exception {

		prefs.setValue(_getPrefsKey(key, languageId), value);
	}

	public static void setPrefsValues(
			PortletPreferences prefs, String key, String languageId,
			String[] values)
		throws Exception {

		prefs.setValues(_getPrefsKey(key, languageId), values);
	}

	public static String updateLocalization(
		String xml, String key, String value) {

		String defaultLanguageId = LocaleUtil.toLanguageId(
			LocaleUtil.getDefault());

		return updateLocalization(
			xml, key, value, defaultLanguageId, defaultLanguageId);
	}

	public static String updateLocalization(
		String xml, String key, String value, String requestedLanguageId) {

		String defaultLanguageId = LocaleUtil.toLanguageId(
			LocaleUtil.getDefault());

		return updateLocalization(
			xml, key, value, requestedLanguageId, defaultLanguageId);
	}

	public static String updateLocalization(
		String xml, String key, String value, String requestedLanguageId,
		String defaultLanguageId) {

		return updateLocalization(
			xml, key, value, requestedLanguageId, defaultLanguageId, false);
	}

	public static String updateLocalization(
		String xml, String key, String value, String requestedLanguageId,
		String defaultLanguageId, boolean cdata) {

		if (Validator.isNull(xml) || (xml.indexOf("<root") == -1)) {
			xml = "<root />";
		}

		String updatedXml = xml;

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			String availableLocales = root.attributeValue("available-locales");

			Element localeEl = null;

			Iterator itr = root.elements().iterator();

			while (itr.hasNext()) {
				Element el = (Element) itr.next();

				String languageId =
					el.attributeValue("language-id", defaultLanguageId);

				if (languageId.equals(requestedLanguageId)) {
					localeEl = el;

					break;
				}
			}

			if (localeEl != null) {
				localeEl.addAttribute("language-id", requestedLanguageId);

				if (cdata) {
					localeEl.clearContent();
					localeEl.addCDATA(value);
				}
				else {
					localeEl.setText(value);
				}
			}
			else {
				localeEl = root.addElement(key);

				localeEl.addAttribute("language-id", requestedLanguageId);

				if (cdata) {
					localeEl.addCDATA(value);
				}
				else {
					localeEl.setText(value);
				}

				if (availableLocales == null) {
					availableLocales = defaultLanguageId;
				}

				if (!requestedLanguageId.equals(defaultLanguageId)) {
					availableLocales += StringPool.COMMA + requestedLanguageId;
				}

				root.addAttribute("available-locales", availableLocales);
			}

			root.addAttribute("default-locale", defaultLanguageId);

			updatedXml = XMLFormatter.toString(doc, "  ");
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return updatedXml;
	}

	private static String _getPrefsKey(String key, String languageId) {
		String defaultLanguageId = LocaleUtil.toLanguageId(
			LocaleUtil.getDefault());

		if (!languageId.equals(defaultLanguageId)) {
			key += "_" + languageId;
		}

		return key;
	}

	private static Log _log = LogFactoryUtil.getLog(LocalizationUtil.class);

}