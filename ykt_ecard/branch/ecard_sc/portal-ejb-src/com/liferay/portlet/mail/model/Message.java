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

package com.liferay.portlet.mail.model;

import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.util.BrowserSniffer;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="Message.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class Message {

	public Message(HttpServletRequest req, PortletPreferences prefs) {
		setHTMLFormat(req, prefs);
	}

	public Message(ActionRequest req, PortletPreferences prefs) {
		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		setHTMLFormat(reqImpl.getHttpServletRequest(), prefs);
	}

	public Message(RenderRequest req, PortletPreferences prefs) {
		RenderRequestImpl reqImpl = (RenderRequestImpl)req;

		setHTMLFormat(reqImpl.getHttpServletRequest(), prefs);
	}

	public javax.mail.Message getMessage() {
		return _msg;
	}

	public void setMessage(javax.mail.Message msg) {
		_msg = msg;
	}

	public String getMessageType() {
		return _messageType;
	}

	public void setMessageType(String messageType) {
		_messageType = messageType;
	}

	public String getParentFolder() {
		return _parentFolder;
	}

	public void setParentFolder(String parentFolder) {
		_parentFolder = parentFolder;
	}

	public String getParentNumber() {
		return _parentNumber;
	}

	public void setParentNumber(String parentNumber) {
		_parentNumber = parentNumber;
	}

	public String getTo() {
		return _to;
	}

	public void setTo(String to) {
		_to = to;
	}

	public String getCc() {
		return _cc;
	}

	public void setCc(String cc) {
		_cc = cc;
	}

	public String getBcc() {
		return _bcc;
	}

	public void setBcc(String bcc) {
		_bcc = bcc;
	}

	public String getSubject() {
		return _subject;
	}

	public void setSubject(String subject) {
		_subject = subject;
	}

	public String getBody() {
		return _body;
	}

	public void setBody(String body) {
		_body = body;
	}

	public boolean isReturnReceipt() {
		return _returnReceipt;
	}

	public void setReturnReceipt(boolean returnReceipt) {
		_returnReceipt = returnReceipt;
	}

	public boolean isHTMLFormat() {
		return _htmlFormat;
	}

	public void setHTMLFormat(boolean htmlFormat) {
		_htmlFormat = htmlFormat;
	}

	public void setHTMLFormat(
		HttpServletRequest req, PortletPreferences prefs) {

		// If the browser capable of using RTF

		if (BrowserSniffer.is_rtf(req)) {

			// If the user last chose to use RTF

			_htmlFormat = GetterUtil.getBoolean(prefs.getValue(
				"html-format", StringPool.BLANK));
		}
	}

	public boolean isDraft() {
		return _draft;
	}

	public void setDraft(boolean draft) {
		_draft = draft;
	}

	private javax.mail.Message _msg = null;
	private String _parentFolder = StringPool.BLANK;
	private String _parentNumber = StringPool.BLANK;
	private String _messageType = StringPool.BLANK;
	private String _to = StringPool.BLANK;
	private String _cc = StringPool.BLANK;
	private String _bcc = StringPool.BLANK;
	private String _subject = StringPool.BLANK;
	private String _body = StringPool.BLANK;
	private boolean _returnReceipt = false;
	private boolean _htmlFormat = false;
	private boolean _draft = false;

}