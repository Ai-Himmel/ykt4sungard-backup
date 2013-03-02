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

package com.liferay.portal.language;

import com.liferay.portal.kernel.language.Language;
import com.liferay.portal.kernel.language.LanguageWrapper;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.util.CookieKeys;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebAppPool;
import com.liferay.util.CollectionFactory;
import com.liferay.util.CookieUtil;
import com.liferay.util.Time;

import java.text.MessageFormat;

import java.util.Locale;
import java.util.Map;
import java.util.MissingResourceException;
import java.util.ResourceBundle;

import javax.portlet.ActionRequest;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;
import org.apache.struts.taglib.TagUtils;
import org.apache.struts.util.MessageResources;

/**
 * <a href="LanguageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Andrius Vitkauskas
 *
 */
public class LanguageImpl implements Language {

	public static final String DEFAULT_ENCODING = "UTF-8";

	public String format(Locale locale, String pattern, Object argument) {
		long companyId = CompanyThreadLocal.getCompanyId();

		return format(companyId, locale, pattern, new Object[] {argument});
	}

	public String format(Locale locale, String pattern, Object[] arguments) {
		long companyId = CompanyThreadLocal.getCompanyId();

		return format(companyId, locale, pattern, arguments);
	}

	public String format(
		long companyId, Locale locale, String pattern, Object argument) {

		return format(companyId, locale, pattern, new Object[] {argument});
	}

	public String format(
		long companyId, Locale locale, String pattern, Object[] arguments) {

		String value = null;

		try {
			pattern = get(companyId, locale, pattern);

			if (arguments != null) {
				Object[] formattedArguments = new Object[arguments.length];

				for (int i = 0; i < arguments.length; i++) {
					formattedArguments[i] = get(
						companyId, locale, arguments[i].toString());
				}

				value = MessageFormat.format(pattern, formattedArguments);
			}
			else {
				value = pattern;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}
		}

		return value;
	}

	public String format(
		PageContext pageContext, String pattern, Object argument) {

		return format(pageContext, pattern, new Object[] {argument}, true);
	}

	public String format(
		PageContext pageContext, String pattern, Object argument,
		boolean translateArguments) {

		return format(
			pageContext, pattern, new Object[] {argument}, translateArguments);
	}

	public String format(
		PageContext pageContext, String pattern, Object[] arguments) {

		return format(pageContext, pattern, arguments, true);
	}

	public String format(
		PageContext pageContext, String pattern, Object[] arguments,
		boolean translateArguments) {

		String value = null;

		try {
			pattern = get(pageContext, pattern);

			if (arguments != null) {
				Object[] formattedArguments = new Object[arguments.length];

				for (int i = 0; i < arguments.length; i++) {
					if (translateArguments) {
						formattedArguments[i] =
							get(pageContext, arguments[i].toString());
					}
					else {
						formattedArguments[i] = arguments[i];
					}
				}

				value = MessageFormat.format(pattern, formattedArguments);
			}
			else {
				value = pattern;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}
		}

		return value;
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper argument) {

		return format(
			pageContext, pattern, new LanguageWrapper[] {argument}, true);
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper argument,
		boolean translateArguments) {

		return format(
			pageContext, pattern, new LanguageWrapper[] {argument},
			translateArguments);
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments) {

		return format(pageContext, pattern, arguments, true);
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments,
		boolean translateArguments) {

		String value = null;

		try {
			pattern = get(pageContext, pattern);

			if (arguments != null) {
				Object[] formattedArguments = new Object[arguments.length];

				for (int i = 0; i < arguments.length; i++) {
					if (translateArguments) {
						formattedArguments[i] =
							arguments[i].getBefore() +
							get(pageContext, arguments[i].getText()) +
							arguments[i].getAfter();
					}
					else {
						formattedArguments[i] =
							arguments[i].getBefore() +
							arguments[i].getText() +
							arguments[i].getAfter();
					}
				}

				value = MessageFormat.format(pattern, formattedArguments);
			}
			else {
				value = pattern;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}
		}

		return value;
	}

	public String get(Locale locale, String key) {
		long companyId = CompanyThreadLocal.getCompanyId();

		return get(companyId, locale, key, key);
	}

	public String get(long companyId, Locale locale, String key) {
		return get(companyId, locale, key, key);
	}

	public String get(
		long companyId, Locale locale, String key, String defaultValue) {

		if (key == null) {
			return null;
		}

		String value = null;

		try {
			MessageResources resources = (MessageResources)WebAppPool.get(
				String.valueOf(companyId), Globals.MESSAGES_KEY);

			if (resources == null) {

				// LEP-4505

				ResourceBundle bundle = ResourceBundle.getBundle(
					"content/Language", locale);

				value = bundle.getString(key);
			}
			else {
				value = resources.getMessage(locale, key);
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}
		}

		if (value == null) {
			value = defaultValue;
		}

		return value;
	}

	public String get(PageContext pageContext, String key) {
		return get(pageContext, key, key);
	}

	public String get(
		PageContext pageContext, String key, String defaultValue) {

		if (key == null) {
			return null;
		}

		String value = null;

		try {
			value = TagUtils.getInstance().message(
				pageContext, null, null, key);
		}
		catch (Exception e) {
			_log.error(e);
		}

		if (value == null) {

			// LEP-2849

			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			PortletConfig portletConfig = (PortletConfig)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_CONFIG);

			if (portletConfig != null) {
				Locale locale = req.getLocale();

				ResourceBundle bundle = portletConfig.getResourceBundle(locale);

				try {
					value = bundle.getString(key);
				}
				catch (MissingResourceException mre) {
				}
			}
		}

		if (value == null) {
			value = defaultValue;
		}

		return value;
	}

	public Locale[] getAvailableLocales() {
		return _getInstance()._locales;
	}

	public String getCharset(Locale locale) {
		return _getInstance()._getCharset(locale);
	}

	public String getLanguageId(ActionRequest req) {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getLanguageId(httpReq);
	}

	public String getLanguageId(RenderRequest req) {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getLanguageId(httpReq);
	}

	public String getLanguageId(HttpServletRequest req) {
		String languageId = ParamUtil.getString(req, "languageId");

		if (Validator.isNotNull(languageId)) {
			return languageId;
		}

		Locale locale =
			(Locale)req.getSession().getAttribute(Globals.LOCALE_KEY);

		if (locale == null) {
			languageId = CookieUtil.get(
				req.getCookies(), CookieKeys.GUEST_LANGUAGE_ID);

			if (Validator.isNotNull(languageId)) {
				locale = LocaleUtil.fromLanguageId(languageId);
			}
		}

		return getLanguageId(locale);
	}

	public String getLanguageId(Locale locale) {
		return LocaleUtil.toLanguageId(locale);
	}

	public Locale getLocale(String languageCode) {
		return _getInstance()._getLocale(languageCode);
	}

	public String getTimeDescription(
		PageContext pageContext, Long milliseconds) {

		return getTimeDescription(pageContext, milliseconds.longValue());
	}

	public String getTimeDescription(
		PageContext pageContext, long milliseconds) {

		String desc = Time.getDescription(milliseconds);

		String value = null;

		try {
			int pos = desc.indexOf(StringPool.SPACE);

			int x = GetterUtil.getInteger(desc.substring(0, pos));

			value =
				x + " " +
				get(
					pageContext,
					desc.substring(pos + 1, desc.length()).toLowerCase());
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}
		}

		return value;
	}

	public void updateCookie(HttpServletResponse res, Locale locale) {
		String languageId = LocaleUtil.toLanguageId(locale);

		Cookie languageIdCookie = new Cookie(
			CookieKeys.GUEST_LANGUAGE_ID, languageId);

		languageIdCookie.setPath(StringPool.SLASH);
		languageIdCookie.setMaxAge(CookieKeys.MAX_AGE);

		CookieKeys.addCookie(res, languageIdCookie);
	}

	private static LanguageImpl _getInstance() {
		Long companyIdObj = new Long(CompanyThreadLocal.getCompanyId());

		LanguageImpl instance = (LanguageImpl)_instances.get(companyIdObj);

		if (instance == null) {
			instance = new LanguageImpl();

			_instances.put(companyIdObj, instance);
		}

		return instance;
	}

	private LanguageImpl() {
		String[] localesArray = PropsValues.LOCALES;

		_locales = new Locale[localesArray.length];
		_localesByLanguageCode = CollectionFactory.getHashMap();
		_charEncodings = CollectionFactory.getHashMap();

		for (int i = 0; i < localesArray.length; i++) {
			String languageId = localesArray[i];

			int x = languageId.indexOf(StringPool.UNDERLINE);

			String language = languageId.substring(0, x);
			//String country = languageId.substring(x + 1, languageId.length());

			Locale locale = LocaleUtil.fromLanguageId(languageId);

			_locales[i] = locale;
			_localesByLanguageCode.put(language, locale);
			_charEncodings.put(locale.toString(), DEFAULT_ENCODING);
		}
	}

	private String _getCharset(Locale locale) {
		return DEFAULT_ENCODING;
	}

	private Locale _getLocale(String languageCode) {
		return (Locale)_localesByLanguageCode.get(languageCode);
	}

	private static Log _log = LogFactory.getLog(LanguageImpl.class);

	private static Map _instances = CollectionFactory.getSyncHashMap();

	private Locale[] _locales;
	private Map _localesByLanguageCode;
	private Map _charEncodings;

}