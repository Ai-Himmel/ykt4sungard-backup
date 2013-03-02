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

package com.liferay.portlet;

import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.util.CollectionFactory;

import java.io.ByteArrayInputStream;
import java.io.IOException;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Locale;
import java.util.Map;
import java.util.MissingResourceException;
import java.util.PropertyResourceBundle;
import java.util.ResourceBundle;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.util.RequestUtils;

/**
 * <a href="PortletResourceBundles.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletResourceBundles {

	public static String getString(PageContext pageContext, String key) {
		return _instance._getString(pageContext, key);
	}

	public static String getString(Locale locale, String key) {
		return _instance._getString(locale, key);
	}

	public static String getString(String languageId, String key) {
		return _instance._getString(languageId, key);
	}

	public static String getString(
		String servletContextName, String languageId, String key) {

		return _instance._getString(servletContextName, languageId, key);
	}

	public static void put(
		String servletContextName, String languageId, ResourceBundle bundle) {

		_instance._put(servletContextName, languageId, bundle);
	}

	public static void remove(String servletContextName) {
		_instance._remove(servletContextName);
	}

	private PortletResourceBundles() {
		_contexts = CollectionFactory.getSyncHashMap(new LinkedHashMap());
	}

	private ResourceBundle _getBundle(
		String servletContextName, String languageId) {

		Map bundles = _getBundles(servletContextName);

		return _getBundle(bundles, languageId);
	}

	private ResourceBundle _getBundle(Map bundles, String languageId) {
		ResourceBundle bundle = (ResourceBundle)bundles.get(languageId);

		if (bundle == null) {
			try {
				bundle = new PropertyResourceBundle(
					new ByteArrayInputStream(new byte[0]));

				bundles.put(languageId, bundle);
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}

		return bundle;
	}

	private Map _getBundles(String servletContextName) {
		Map bundles = (Map)_contexts.get(servletContextName);

		if (bundles == null) {
			bundles = CollectionFactory.getHashMap();

			_contexts.put(servletContextName, bundles);
		}

		return bundles;
	}

	private String _getString(PageContext pageContext, String key) {
		Locale locale = RequestUtils.getUserLocale(
			(HttpServletRequest)pageContext.getRequest(), null);

		return _getString(locale, key);
	}

	private String _getString(Locale locale, String key) {
		return _getString(LocaleUtil.toLanguageId(locale), key);
	}

	private String _getString(String languageId, String key) {
		return _getString(null, languageId, key);
	}

	private String _getString(
		String servletContextName, String languageId, String key) {

		if (servletContextName != null) {
			ResourceBundle bundle = _getBundle(servletContextName, languageId);

			return bundle.getString(key);
		}

		Iterator itr = _contexts.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			Map bundles = (Map)entry.getValue();

			ResourceBundle bundle = _getBundle(bundles, languageId);

			try {
				return bundle.getString(key);
			}
			catch (MissingResourceException mre) {
			}
		}

		return null;
	}

	private void _put(
		String servletContextName, String languageId, ResourceBundle bundle) {

		Map bundles = _getBundles(servletContextName);

		bundles.put(languageId, bundle);
	}

	private void _remove(String servletContextName) {
		_contexts.remove(servletContextName);
	}

	private static Log _log = LogFactory.getLog(PortletResourceBundles.class);

	private static PortletResourceBundles _instance =
		new PortletResourceBundles();

	private Map _contexts;

}