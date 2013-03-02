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

package com.liferay.portal.language;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.util.CookieKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebAppPool;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.util.CollectionFactory;
import com.liferay.util.CookieUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.LocaleUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Time;
import com.liferay.util.Validator;

import java.text.MessageFormat;

import java.util.Locale;
import java.util.Map;

import javax.portlet.ActionRequest;
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
 * <a href="LanguageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.17 $
 *
 */
public class LanguageUtil {

	public static final String DEFAULT_ENCODING = "UTF-8";

	public static String format(
			PageContext pageContext, String pattern, Object argument)
		throws LanguageException {

		return format(pageContext, pattern, new Object[] {argument}, true);
	}

	public static String format(
			PageContext pageContext, String pattern, Object argument,
			boolean translateArguments)
		throws LanguageException {

		return format(
			pageContext, pattern, new Object[] {argument}, translateArguments);
	}

	public static String format(
			PageContext pageContext, String pattern, Object[] arguments)
		throws LanguageException {

		return format(pageContext, pattern, arguments, true);
	}

	public static String format(
			PageContext pageContext, String pattern, Object[] arguments,
			boolean translateArguments)
		throws LanguageException {

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
			throw new LanguageException(e);
		}

		return value;
	}

	public static String format(
			PageContext pageContext, String pattern, LanguageWrapper argument)
		throws LanguageException {

		return format(
			pageContext, pattern, new LanguageWrapper[] {argument}, true);
	}

	public static String format(
			PageContext pageContext, String pattern, LanguageWrapper argument,
			boolean translateArguments)
		throws LanguageException {

		return format(
			pageContext, pattern, new LanguageWrapper[] {argument},
			translateArguments);
	}

	public static String format(
			PageContext pageContext, String pattern,
			LanguageWrapper[] arguments)
		throws LanguageException {

		return format(pageContext, pattern, arguments, true);
	}

	public static String format(
			PageContext pageContext, String pattern,
			LanguageWrapper[] arguments, boolean translateArguments)
		throws LanguageException {

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
			throw new LanguageException(e);
		}

		return value;
	}

	public static String get(User user, String key) throws LanguageException {
		return get(user.getCompanyId(), user.getLocale(), key);
	}

	public static String get(String companyId, Locale locale, String key)
		throws LanguageException {

		String value = null;

		try {
			MessageResources resources = (MessageResources)WebAppPool.get(
				companyId, Globals.MESSAGES_KEY);

			value = resources.getMessage(locale, key);
		}
		catch (Exception e) {
			throw new LanguageException(e);
		}

		if (value == null) {
			value = key;
		}

		return value;
	}

	public static String get(PageContext pageContext, String key)
		throws LanguageException {

		return get(pageContext, key, key);
	}

	public static String get(
			PageContext pageContext, String key, String defaultValue)
		throws LanguageException {

		String value = null;

		try {
			value = TagUtils.getInstance().message(
				pageContext, null, null, key);
		}
		catch (Exception e) {
			_log.error(e.getMessage());

			throw new LanguageException(key, e);
		}

		if (value == null) {
			value = defaultValue;
		}

		return value;
	}

	public static Locale[] getAvailableLocales() {
		return _instance._locales;
	}

    public static String getCharset(Locale locale) {
		return _instance._getCharset(locale);
	}

	public static String getLanguageId(ActionRequest req)
		throws PortalException, SystemException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		return getLanguageId(reqImpl.getHttpServletRequest());
	}

	public static String getLanguageId(RenderRequest req)
		throws PortalException, SystemException {

		RenderRequestImpl reqImpl = (RenderRequestImpl)req;

		return getLanguageId(reqImpl.getHttpServletRequest());
	}

	public static String getLanguageId(HttpServletRequest req) {
	    String languageId = ParamUtil.getString(req, "language_id");

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

		return LocaleUtil.toLanguageId(locale);
	}

	public static Locale getLocale(String languageCode) {
		return _instance._getLocale(languageCode);
	}

	public static String getTimeDescription(
			PageContext pageContext, Long milliseconds)
		throws LanguageException {

		return getTimeDescription(pageContext, milliseconds.longValue());
	}

	public static String getTimeDescription(
			PageContext pageContext, long milliseconds)
		throws LanguageException {

		String desc = Time.getDescription(milliseconds);

		String value = null;

		try {
			int pos = desc.indexOf(" ");

			int x = GetterUtil.get(desc.substring(0, pos), 0);

			value =
				x + " " +
				get(
					pageContext,
					desc.substring(pos + 1, desc.length()).toLowerCase());
		}
		catch (Exception e) {
			throw new LanguageException(e);
		}

		return value;
	}

	public static void updateCookie(HttpServletResponse res, Locale locale) {
		String languageId = LocaleUtil.toLanguageId(locale);

		Cookie languageIdCookie = new Cookie(
			CookieKeys.GUEST_LANGUAGE_ID, languageId);
		languageIdCookie.setPath("/");
		languageIdCookie.setMaxAge(CookieKeys.MAX_AGE);

		res.addCookie(languageIdCookie);
	}

	private LanguageUtil() {
		String[] array = StringUtil.split(
			PropsUtil.get(PropsUtil.LOCALES), StringPool.COMMA);

		_locales = new Locale[array.length];
		_localesByLanguageCode = CollectionFactory.getHashMap();
		_charEncodings = CollectionFactory.getHashMap();

		for (int i = 0; i < array.length; i++) {
			int x = array[i].indexOf(StringPool.UNDERLINE);

			String language = array[i].substring(0, x);
			String country = array[i].substring(x + 1, array[i].length());

			Locale locale = new Locale(language, country);
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

	private static final Log _log = LogFactory.getLog(LanguageUtil.class);

	private static LanguageUtil _instance = new LanguageUtil();

	private Locale[] _locales;
	private Map _localesByLanguageCode;
	private Map _charEncodings;

}