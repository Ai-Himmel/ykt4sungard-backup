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

package com.liferay.portal.theme;

import com.liferay.portal.kernel.util.MethodCache;
import com.liferay.portal.kernel.util.WebKeys;
import com.liferay.portal.model.Layout;

import java.io.Serializable;

import java.lang.reflect.Method;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="NavItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class NavItem implements Serializable {

	public static NavItem fromLayout(RequestVars vars, Layout layout) {
		return new NavItem(vars, layout);
	}

	public static List fromLayouts(RequestVars vars, List layouts) {
		if (layouts == null) {
			return null;
		}

		List navItems = new ArrayList(layouts.size());

		for (int i = 0; i < layouts.size(); i++) {
			Layout layout = (Layout)layouts.get(i);

			navItems.add(fromLayout(vars, layout));
		}

		return navItems;
	}

	public NavItem(RequestVars vars, Layout layout) {
		_vars = vars;
		_layout = layout;
	}

	public Layout getLayout() {
		return _layout;
	}

	public boolean isSelected() {
		ThemeDisplay themeDisplay = _vars.getThemeDisplay();

		return _layout.isSelected(
			themeDisplay.isTilesSelectable(), themeDisplay.getLayout(),
			_vars.getAncestorPlid());
	}

	public String getName() {
		return _layout.getName(_vars.getThemeDisplay().getLocale());
	}

	public String getTarget() {
		return _layout.getTarget();
	}

	public String getTitle() {
		return _layout.getTitle(_vars.getThemeDisplay().getLocale());
	}

	public String getURL() throws Exception {
		return getRegularURL();
	}

	public String getRegularURL() throws Exception {
		return _layout.getRegularURL(_vars.getRequest());
	}

	public String getResetMaxStateURL() throws Exception {
		return _layout.getResetMaxStateURL(_vars.getRequest());
	}

	public String getResetLayoutURL() throws Exception {
		return _layout.getResetLayoutURL(_vars.getRequest());
	}

	public List getChildren() throws Exception {
		if (_children == null) {
			ThemeDisplay themeDisplay = _vars.getThemeDisplay();

			List layouts = _layout.getChildren(
				themeDisplay.getPermissionChecker());

			_children = fromLayouts(_vars, layouts);
		}

		return _children;
	}

	public boolean hasChildren() throws Exception {
		if (getChildren().size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public String icon() throws Exception {
		HttpServletRequest req = _vars.getRequest();

		Object velocityTaglib = req.getAttribute(WebKeys.VELOCITY_TAGLIB);

		Method method = MethodCache.get(
			_VELOCITY_TAGLIB_CLASS, _VELOCITY_TAGLIB_LAYOUT_ICON_METHOD,
			_VELOCITY_TAGLIB_LAYOUT_ICON_PARAMS);

		return (String)method.invoke(velocityTaglib, new Layout[] {_layout});
	}

	private static final String _VELOCITY_TAGLIB_CLASS =
		"com.liferay.taglib.util.VelocityTaglib";

	private static final String _VELOCITY_TAGLIB_LAYOUT_ICON_METHOD =
		"layoutIcon";

	private static final Class[] _VELOCITY_TAGLIB_LAYOUT_ICON_PARAMS =
		new Class[] {Layout.class};

	private RequestVars _vars;
	private Layout _layout;
	private List _children;

}