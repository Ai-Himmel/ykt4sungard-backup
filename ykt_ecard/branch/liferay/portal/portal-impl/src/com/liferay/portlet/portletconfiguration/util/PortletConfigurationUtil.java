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

package com.liferay.portlet.portletconfiguration.util;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletConfigurationUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletConfigurationUtil {

	public static String getPortletTitle(
		PortletPreferences portletSetup, String languageId) {

		String useCustomTitle = GetterUtil.getString(portletSetup.getValue(
			"portlet-setup-use-custom-title", StringPool.BLANK));

		if (useCustomTitle.equals("false")) {
			return StringPool.BLANK;
		}

		String defaultLanguageId = LocaleUtil.toLanguageId(
			LocaleUtil.getDefault());

		String defaultPortletTitle = portletSetup.getValue(
			"portlet-setup-title-" + defaultLanguageId, StringPool.BLANK);

		String portletTitle = portletSetup.getValue(
			"portlet-setup-title-" + languageId, defaultPortletTitle);

		if (Validator.isNull(portletTitle)) {

			// For backwards compatibility

			String oldPortletTitle = portletSetup.getValue(
				"portlet-setup-title", null);

			if (Validator.isNull(useCustomTitle) &&
				Validator.isNotNull(oldPortletTitle)) {

				portletTitle = oldPortletTitle;

				try {
					portletSetup.setValue(
						"portlet-setup-title-" + defaultLanguageId,
						portletTitle);
					portletSetup.setValue(
						"portlet-setup-use-custom-title", "true");

					portletSetup.store();
				}
				catch (Exception e) {
					_log.error(e);
				}
			}
		}

		return portletTitle;
	}

	private static Log _log = LogFactory.getLog(PortletConfigurationUtil.class);

}