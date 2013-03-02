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

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import java.util.Locale;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.json.JSONObject;

/**
 * <a href="PortletSetupUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletSetupUtil {

	public static final JSONObject cssToJSON(
			PortletPreferences portletSetup, String css)
		throws Exception {

		return _toJSONObject(portletSetup, css);
	}

	public static final String cssToString(PortletPreferences portletSetup) {
		String css = portletSetup.getValue(
			"portlet-setup-css", StringPool.BLANK);

		try {
			if (Validator.isNotNull(css)) {
				return _toJSONObject(portletSetup, css).toString();
			}
		}
		catch (Exception e) {
			css = null;

			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}

		return css;
	}

	private static final JSONObject _toJSONObject(
			PortletPreferences portletSetup, String css)
		throws Exception {

		if (_log.isDebugEnabled()) {
			_log.debug("Transform CSS to JSON " + css);
		}

		JSONObject jsonObj = new JSONObject(css);

		JSONObject portletData = new JSONObject();

		jsonObj.put("portletData", portletData);

		JSONObject titles = new JSONObject();

		portletData.put("titles", titles);

		Locale[] locales = LanguageUtil.getAvailableLocales();

		for (int i = 0; i < locales.length; i++) {
			String languageId = LocaleUtil.toLanguageId(locales[i]);

			String title = portletSetup.getValue(
				"portlet-setup-title-" + languageId, null);

			if (Validator.isNotNull(languageId)) {
				titles.put(languageId, title);
			}
		}

		boolean useCustomTitle = GetterUtil.getBoolean(
			portletSetup.getValue("portlet-setup-use-custom-title", null));
		boolean showBorders = GetterUtil.getBoolean(
			portletSetup.getValue("portlet-setup-show-borders", null), true);
		long linkToPlid = GetterUtil.getLong(
			portletSetup.getValue("portlet-setup-link-to-plid", null));

		portletData.put("useCustomTitle", useCustomTitle);
		portletData.put("showBorders", showBorders);
		portletData.put("portletLinksTarget", linkToPlid);

		// The JSONObject class does not properly detect boolean attributes
		// without going through serialization

		jsonObj = new JSONObject(jsonObj.toString());

		return jsonObj;
	}

	private static Log _log = LogFactory.getLog(PortletSetupUtil.class);

}