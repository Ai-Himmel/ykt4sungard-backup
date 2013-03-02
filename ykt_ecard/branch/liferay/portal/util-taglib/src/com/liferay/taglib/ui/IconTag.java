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
 * <a href="IconTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IconTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:icon:image", _image);
		req.setAttribute("liferay-ui:icon:message", _message);
		req.setAttribute("liferay-ui:icon:src", _src);
		req.setAttribute("liferay-ui:icon:url", _url);
		req.setAttribute("liferay-ui:icon:target", _target);
		req.setAttribute("liferay-ui:icon:label", String.valueOf(_label));
		req.setAttribute("liferay-ui:icon:toolTip", String.valueOf(_toolTip));

		return EVAL_BODY_BUFFERED;
	}

	public void setImage(String image) {
		_image = image;
	}

	public void setMessage(String message) {
		_message = message;
	}

	public void setSrc(String src) {
		_src = src;
	}

	public void setUrl(String url) {
		_url = url;
	}

	public void setTarget(String target) {
		_target = target;
	}

	public void setLabel(boolean label) {
		_label = label;
	}

	public void setToolTip(boolean toolTip) {
		_toolTip = toolTip;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/icon/page.jsp";

	private String _image;
	private String _message;
	private String _src;
	private String _url;
	private String _target = "_self";
	private boolean _label;
	private boolean _toolTip = true;

}