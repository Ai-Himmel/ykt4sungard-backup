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

package com.liferay.portlet.mail.model;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.Html;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="MailContent.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class MailContent {

	public MailContent() {
	}

	public MailContent(String body) {
		setHtmlBody(body);
	}

	public String getPlainBody() {
		return GetterUtil.getString(_plainBody);
	}

	public void setPlainBody(String plainBody) {
		_plainBody = plainBody;
	}

	public void appendPlainBody(String plainBody) {
		if (Validator.isNull(_plainBody)) {
			_plainBody = plainBody;
		}
		else {
			_plainBody += StringPool.NEW_LINE + StringPool.NEW_LINE + plainBody;
		}
	}

	public String getHtmlBody() {
		if (Validator.isNotNull(_htmlBody)) {
			return _htmlBody;
		}
		else {
			String body = GetterUtil.getString(_plainBody);

			if (Validator.isNotNull(body)) {
				body = Html.escape(body);
				body = StringUtil.replace(body, "\t", "    ");
				body = StringUtil.replace(body, "  ", " &nbsp;");
				body = StringUtil.replace(body, "\n", "<BR />");
				body =
					"<div style=\"font-family: courier, monospace; " +
						"font-size: 12\">" + body + "</div>";
			}

			return body;
		}
	}

	public void setHtmlBody(String htmlBody) {
		_htmlBody = htmlBody;
	}

	public void appendHtmlBody(String htmlBody) {
		if (Validator.isNull(_htmlBody)) {
			_htmlBody = htmlBody;
		}
		else {
			_htmlBody += "<HR/>" + htmlBody;
		}
	}

	public List getSubContent() {
		return _subContent;
	}

	public void appendSubContent(MailContent mc) {
		_subContent.add(mc);
	}

	public String toString() {
		StringMaker sm = new StringMaker();

		sm.append(getHtmlBody());

		for (int i = 0; i < _subContent.size(); i++) {
			sm.append("<HR/>" + _subContent.get(i).toString());
		}

		return sm.toString();
	}

	private String _plainBody;
	private String _htmlBody;
	private List _subContent = new ArrayList();

}