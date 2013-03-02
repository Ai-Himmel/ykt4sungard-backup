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

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.regex.Pattern;

import javax.mail.Address;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;

/**
 * <a href="MailMessage.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class MailMessage {

	public long getMessageId() {
		return _messageId;
	}

	public void setMessageId(long messageId) {
		_messageId = messageId;
	}

	public Address getFrom() {
		return _from;
	}

	public void setFrom(Address from) {
		_from = from;
	}

	public Address[] getTo() {
		return _to;
	}

	public void setTo(String to) throws AddressException {
		_to = InternetAddress.parse(to);
	}

	public void setTo(Address[] to) {
		_to = to;
	}

	public Address[] getCc() {
		return _cc;
	}

	public void setCc(Address[] cc) {
		_cc = cc;
	}

	public void setCc(String ccs) throws AddressException {
		_cc = InternetAddress.parse(ccs);
	}

	public Address[] getBcc() {
		return _bcc;
	}

	public void setBcc(Address[] bcc) {
		_bcc = bcc;
	}

	public void setBcc(String bccs) throws AddressException {
		_bcc = InternetAddress.parse(bccs);
	}

	public String getInReplyTo() {
		return _inReplyTo;
	}

	public void setInReplyTo(String inReplyTo) {
		_inReplyTo = inReplyTo;
	}

	public Address[] getReplyTo() {
		return _replyTo;
	}

	public void setReplyTo(String replyTos) throws AddressException {
		_replyTo = InternetAddress.parse(replyTos);
	}

	public void setReplyTo(Address[] replyTo) {
		_replyTo = replyTo;
	}

	public String getReferences() {
		return _references;
	}

	public void setReferences(String references) {
		_references = references;
	}

	public String getSubject() {
		return GetterUtil.getString(_subject);
	}

	public void setSubject(String subject) {
		_subject = subject;
	}

	public Date getSentDate() {
		return _sentDate;
	}

	public void setSentDate(Date sentDate) {
		_sentDate = sentDate;
	}

	public String getBody() {
		return getBody(false, false);
	}

	public String getBody(boolean replaceLinks, boolean popup) {
		String body = _content.toString();

		if (replaceLinks) {
			for (int i = 0; i < _LINK_REGEXP.length; i++) {
				body = Pattern.compile(
					_LINK_REGEXP[i], Pattern.CASE_INSENSITIVE).
						matcher(body).replaceAll(_LINK_REPLACEMENT[i]);
			}

			String mailtoReplacement = "<a href=\"javascript: ";

			if (popup) {
				mailtoReplacement += "opener.compose('$2')";
			}
			else {
				mailtoReplacement += "parent.compose('$2')";
			}

			body = Pattern.compile(
				_MAILTO_REGEXP, Pattern.CASE_INSENSITIVE).
					matcher(body).replaceAll(mailtoReplacement);
		}

		return body;
	}

	public void setBody(String body) {
		MailContent content = new MailContent(body);

		_content = content;
	}

	public MailContent getMailContent() {
		return _content;
	}

	public void setMailContent(MailContent mc) {
		_content = mc;
	}

	public List getAttachments() {
		return _attachments;
	}

	public void appendAttachment(MailAttachment ma) {
		_attachments.add(ma);
	}

	public List getRemoteAttachments() {
		return _remoteAttachments;
	}

	public void setRemoteAttachments(List remoteAttachments) {
		_remoteAttachments = remoteAttachments;
	}

	public void appendRemoteAttachment(RemoteMailAttachment rma) {
		_remoteAttachments.add(rma);
	}

	public void purgeDirtyRemoteAttachments() {
		for (int i = 0; i < _remoteAttachments.size(); i++) {
			RemoteMailAttachment rma =
				(RemoteMailAttachment)_remoteAttachments.get(i);

			if (rma.isDirty()) {
				_remoteAttachments.remove(i);

				i--;
			}
		}
	}

	private static final String[] _LINK_REGEXP = {
		"([^]_a-z0-9-=\"'/])" +
			"((https?|ftp|gopher|news|telnet)://|www\\.)" +
			"([^\\s\\(\\)\\*\\^\\$!`\"'\\|\\[\\]\\{\\};<>\\.]*)" +
			"((\\.[^\\s\\(\\)\\*\\^\\$!`\"'\\|\\[\\]\\{\\};<>\\.]+)*)",
		"<a\\s+href=\"www\\."
	};

	private static String[] _LINK_REPLACEMENT = {
		"$1<a href=\"$2$4$5\" target=\"_blank\">$2$4$5</a>",
		"<a href=\"http://www."
	};

	private static String _MAILTO_REGEXP =
		"(<a\\s+href=\"mailto:\\s*)([\\w.-_]*@[\\w.-_]*)";

	private long _messageId;
	private Address _from;
	private Address[] _to;
	private Address[] _cc;
	private Address[] _bcc;
	private String _inReplyTo;
	private Address[] _replyTo;
	private String _references;
	private String _subject;
	private Date _sentDate;
	private MailContent _content;
	private List _attachments = new ArrayList();
	private List _remoteAttachments = new ArrayList();

}