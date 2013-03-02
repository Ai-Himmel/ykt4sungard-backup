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

package com.liferay.theme.taglib;

import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.ThemeDisplay;

import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import javax.servlet.jsp.tagext.TagData;
import javax.servlet.jsp.tagext.TagExtraInfo;
import javax.servlet.jsp.tagext.VariableInfo;

/**
 * <a href="DefineObjectsTei.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class DefineObjectsTei extends TagExtraInfo {

	public VariableInfo[] getVariableInfo(TagData data) {
		return new VariableInfo[] {
			new VariableInfo(
				"themeDisplay", ThemeDisplay.class.getName(), true,
				VariableInfo.AT_END),
			new VariableInfo(
				"company", Company.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"user", User.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"layout", Layout.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"layouts", List.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"layoutId", String.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"layoutTypePortlet", LayoutTypePortlet.class.getName(), true,
				VariableInfo.AT_END),
			new VariableInfo(
				"portletGroupId", String.class.getName(), true,
				VariableInfo.AT_END),
			new VariableInfo(
				"locale", Locale.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"timeZone", TimeZone.class.getName(), true,
				VariableInfo.AT_END),
			new VariableInfo(
				"theme", Theme.class.getName(), true, VariableInfo.AT_END),
			new VariableInfo(
				"colorScheme", ColorScheme.class.getName(), true,
				VariableInfo.AT_END),
			new VariableInfo(
				"portletDisplay", PortletDisplay.class.getName(), true,
				VariableInfo.AT_END)
		};
	}

}