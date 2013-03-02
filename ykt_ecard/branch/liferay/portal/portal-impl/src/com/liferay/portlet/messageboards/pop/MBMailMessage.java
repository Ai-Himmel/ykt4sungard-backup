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

package com.liferay.portlet.messageboards.pop;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ObjectValuePair;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.Html;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="MBMailMessage.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class MBMailMessage {

	public void addFile(String fileName, byte[] data) {
		_files.add(new ObjectValuePair(fileName, data));
	}

	public List getFiles() {
		return _files;
	}

	public String getHtmlBody() {
		return _htmlBody;
	}

	public void setHtmlBody(String htmlBody) {
		_htmlBody = htmlBody;
	}

	public String getPlainBody() {
		return _plainBody;
	}

	public void setPlainBody(String plainBody) {
		_plainBody = plainBody;
	}

	public String getBody() {
		if (Validator.isNotNull(_plainBody)) {
			return GetterUtil.getString(_plainBody);
		}
		else if (Validator.isNotNull(_htmlBody)) {
			return Html.stripHtml(_htmlBody);
		}
		else {
			return "-";
		}
	}

	private String _htmlBody;
	private String _plainBody;
	private List _files = new ArrayList();

}