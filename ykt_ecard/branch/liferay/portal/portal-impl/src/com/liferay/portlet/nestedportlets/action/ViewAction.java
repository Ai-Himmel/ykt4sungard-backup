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

package com.liferay.portlet.nestedportlets.action;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.LayoutTemplate;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.Theme;
import com.liferay.portal.service.impl.LayoutTemplateLocalUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletPreferencesFactoryUtil;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ViewAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Berentey Zsolt
 * @author Jorge Ferrer
 *
 */
public class ViewAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		Portlet portlet = (Portlet)req.getAttribute(WebKeys.RENDER_PORTLET);

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portlet.getPortletId(), true, true);

		String layoutTemplateId = prefs.getValue(
			"layout-template-id",
			PropsValues.NESTED_PORTLETS_LAYOUT_TEMPLATE_DEFAULT);

		String content = StringPool.BLANK;

		if (Validator.isNotNull(layoutTemplateId)) {
			Theme theme = themeDisplay.getTheme();

			LayoutTemplate layoutTemplate =
				LayoutTemplateLocalUtil.getLayoutTemplate(
					layoutTemplateId, false, theme.getThemeId());

			content = renameTemplateColumnsAndIds(
				layoutTemplate.getContent(), portlet);
		}

		req.setAttribute(WebKeys.LAYOUT_TEMPLATE_CONTENT, content);

		return mapping.findForward("portlet.nested_portlets.view");
	}

	protected String renameTemplateColumnsAndIds(
		String content, Portlet portlet) {

		Matcher m = _searchColumnsAndIdsPattern.matcher(content);

		Set columnIds = new HashSet();

		while (m.find()) {
			if (Validator.isNotNull(m.group(1))) {
				columnIds.add(m.group(1));
			}

			if (Validator.isNotNull(m.group(2))) {
				columnIds.add(m.group(2));
			}
		}

		Iterator itr = columnIds.iterator();

		while (itr.hasNext()) {
			String columnId = (String)itr.next();

			if (columnId.indexOf(portlet.getPortletId()) == -1) {
				content = content.replaceAll(
					columnId, portlet.getPortletId() + "_" + columnId);
			}
		}

		return content;
	}

	private static final Pattern _searchColumnsAndIdsPattern = Pattern.compile(
		"processColumn[(]\"(.*?)\"[)]|[<].*?id=[\"']([^ ]*?)[\"'].*?[>]",
		Pattern.DOTALL);

}