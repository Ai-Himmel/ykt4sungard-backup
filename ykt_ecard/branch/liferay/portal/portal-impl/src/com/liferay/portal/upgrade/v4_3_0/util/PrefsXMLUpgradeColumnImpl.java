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

package com.liferay.portal.upgrade.v4_3_0.util;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portlet.PortletPreferencesImpl;
import com.liferay.portlet.PortletPreferencesSerializer;

import javax.portlet.PortletPreferences;

/**
 * <a href="PrefsXMLUpgradeColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PrefsXMLUpgradeColumnImpl extends BaseUpgradeColumnImpl {

	public PrefsXMLUpgradeColumnImpl(
		UpgradeColumn upgradePortletIdColumn, ValueMapper groupIdMapper,
		ValueMapper pollsQuestionIdMapper, ValueMapper wikiNodeIdMapper) {

		super("preferences");

		_upgradePortletIdColumn = upgradePortletIdColumn;
		_groupIdMapper = groupIdMapper;
		_pollsQuestionIdMapper = pollsQuestionIdMapper;
		_wikiNodeIdMapper = wikiNodeIdMapper;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		String xml = (String)oldValue;

		String portletId = (String)_upgradePortletIdColumn.getOldValue();

		PortletPreferences prefs =
			PortletPreferencesSerializer.fromDefaultXML(xml);

		processPrefs(portletId, prefs);

		return PortletPreferencesSerializer.toXML(
			(PortletPreferencesImpl)prefs);
	}

	protected void processPrefs(String portletId, PortletPreferences prefs)
		throws Exception {

		// Portlet Setup

		String portletCSS = prefs.getValue("portlet-setup-css", null);

		if (Validator.isNotNull(portletCSS)) {
			prefs.reset("portlet-setup-css");
		}

		// Journal Articles and Journal Content

		if (portletId.startsWith("62_INSTANCE_") ||
			portletId.startsWith("56_INSTANCE_")) {

			String groupId = prefs.getValue("group-id", null);

			if (Validator.isNotNull(groupId)) {
				groupId = String.valueOf(_groupIdMapper.getNewValue(
					new Long(GetterUtil.getLong(groupId))));

				prefs.setValue("group-id", groupId);
			}
		}

		// Polls Display

		else if (portletId.startsWith("59_INSTANCE_")) {
			String questionId = prefs.getValue("question-id", null);

			if (Validator.isNotNull(questionId)) {
				questionId = String.valueOf(_pollsQuestionIdMapper.getNewValue(
					new Long(GetterUtil.getLong(questionId))));

				prefs.setValue("question-id", questionId);
			}
		}

		// Wiki Display

		else if (portletId.startsWith("54_INSTANCE_")) {
			String nodeId = prefs.getValue("node-id", null);

			if (Validator.isNotNull(nodeId)) {
				nodeId = String.valueOf(_wikiNodeIdMapper.getNewValue(
					new Long(GetterUtil.getLong(nodeId))));

				prefs.setValue("node-id", nodeId);
			}
		}
	}

	private UpgradeColumn _upgradePortletIdColumn;
	private ValueMapper _groupIdMapper;
	private ValueMapper _pollsQuestionIdMapper;
	private ValueMapper _wikiNodeIdMapper;

}