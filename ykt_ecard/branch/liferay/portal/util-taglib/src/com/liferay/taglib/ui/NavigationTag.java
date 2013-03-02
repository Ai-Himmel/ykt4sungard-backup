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

package com.liferay.taglib.ui;

import com.liferay.taglib.util.IncludeTag;

import javax.servlet.ServletRequest;

/**
 * <a href="NavigationTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class NavigationTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:navigation:bulletStyle", _bulletStyle);
		req.setAttribute("liferay-ui:navigation:displayStyle", _displayStyle);
		req.setAttribute("liferay-ui:navigation:headerType", _headerType);
		req.setAttribute(
			"liferay-ui:navigation:rootLayoutType", _rootLayoutType);
		req.setAttribute(
			"liferay-ui:navigation:rootLayoutLevel",
			String.valueOf(_rootLayoutLevel));
		req.setAttribute(
			"liferay-ui:navigation:includedLayouts", _includedLayouts);

		return EVAL_BODY_BUFFERED;
	}

	public void setBulletStyle(String bulletStyle) {
		_bulletStyle = bulletStyle;
	}

	public void setDisplayStyle(String displayStyle) {
		_displayStyle = displayStyle;
	}

	public void setHeaderType(String headerType) {
		_headerType = headerType;
	}

	public void setRootLayoutType(String rootLayoutType) {
		_rootLayoutType = rootLayoutType;
	}

	public void setRootLayoutLevel(int rootLayoutLevel) {
		_rootLayoutLevel = rootLayoutLevel;
	}

	public void setIncludedLayouts(String includedLayouts) {
		_includedLayouts = includedLayouts;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/navigation/page.jsp";

	private String _bulletStyle = "1";
	private String _displayStyle = "1";
	private String _headerType = "none";
	private String _rootLayoutType = "absolute";
	private int _rootLayoutLevel = 1;
	private String _includedLayouts = "auto";

}