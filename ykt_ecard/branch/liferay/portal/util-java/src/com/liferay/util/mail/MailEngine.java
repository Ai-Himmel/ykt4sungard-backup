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

package com.liferay.util.mail;

import com.liferay.portal.kernel.jndi.PortalJNDIUtil;
import com.liferay.portal.kernel.mail.MailMessage;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;

import java.io.ByteArrayInputStream;
import java.io.File;

import java.net.SocketException;

import java.util.Date;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Part;
import javax.mail.SendFailedException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import javax.naming.NamingException;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailEngine.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 * @author Jorge Ferrer
 * @author Neil Griffin
 *
 */
public class MailEngine {

	public static Session getSession() throws NamingException {
		return getSession(false);
	}

	public static Session getSession(boolean cache) throws NamingException {
		Session session = PortalJNDIUtil.getMailSession();

		session.setDebug(_log.isDebugEnabled());

		if (_log.isDebugEnabled()) {
			session.getProperties().list(System.out);
		}

		return session;
	}

	public static void send(MailMessage mailMessage)
		throws MailEngineException {

		send(
			mailMessage.getFrom(), mailMessage.getTo(), mailMessage.getCC(),
			mailMessage.getBCC(), mailMessage.getSubject(),
			mailMessage.getBody(), mailMessage.isHTMLFormat(),
			mailMessage.getReplyTo(), mailMessage.getMessageId(),
			mailMessage.getInReplyTo(), mailMessage.getAttachments());
	}

	public static void send(String from, String to, String subject, String body)
		throws MailEngineException {

		try {
			send(
				new InternetAddress(from), new InternetAddress(to), subject,
				body);
		}
		catch (AddressException ae) {
			throw new MailEngineException(ae);
		}
	}

	public static void send(
			InternetAddress from, InternetAddress to,
			String subject, String body)
		throws MailEngineException {

		send(
			from, new InternetAddress[] {to}, null, null, subject, body, false,
			null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress to, String subject,
			String body, boolean htmlFormat)
		throws MailEngineException {

		send(
			from, new InternetAddress[] {to}, null, null, subject, body,
			htmlFormat, null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, String subject,
			String body)
		throws MailEngineException {

		send(from, to, null, null, subject, body, false, null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, String subject,
			String body, boolean htmlFormat)
		throws MailEngineException {

		send(from, to, null, null, subject, body, htmlFormat, null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, InternetAddress[] cc,
			String subject, String body)
		throws MailEngineException {

		send(from, to, cc, null, subject, body, false, null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, InternetAddress[] cc,
			String subject, String body, boolean htmlFormat)
		throws MailEngineException {

		send(from, to, cc, null, subject, body, htmlFormat, null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, InternetAddress[] cc,
			InternetAddress[] bcc, String subject, String body)
		throws MailEngineException {

		send(from, to, cc, bcc, subject, body, false, null, null, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, InternetAddress[] cc,
			InternetAddress[] bcc, String subject, String body,
			boolean htmlFormat, InternetAddress[] replyTo, String messageId,
			String inReplyTo)
		throws MailEngineException {

		send(
			from, to, cc, bcc, subject, body, htmlFormat, replyTo, messageId,
			inReplyTo, null);
	}

	public static void send(
			InternetAddress from, InternetAddress[] to, InternetAddress[] cc,
			InternetAddress[] bcc, String subject, String body,
			boolean htmlFormat, InternetAddress[] replyTo, String messageId,
			String inReplyTo, File[] attachments)
		throws MailEngineException {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();

			_log.debug("From: " + from);
			_log.debug("To: " + to);
			_log.debug("CC: " + cc);
			_log.debug("BCC: " + bcc);
			_log.debug("Subject: " + subject);
			_log.debug("Body: " + body);
			_log.debug("HTML Format: " + htmlFormat);
			_log.debug("Reply to: " + replyTo);
			_log.debug("Message ID: " + messageId);
			_log.debug("In Reply To: " + inReplyTo);

			if (attachments != null) {
				for (int i = 0; i < attachments.length; i++) {
					File attachment = attachments[i];

					if (attachment != null) {
						String path = attachment.getAbsolutePath();

						_log.debug("Attachment #" + (i + 1) + ": " + path);
					}
				}
			}
		}

		try {
			Session session = getSession();

			Message msg = new LiferayMimeMessage(session);

			msg.setFrom(from);
			msg.setRecipients(Message.RecipientType.TO, to);

			if (cc != null) {
				msg.setRecipients(Message.RecipientType.CC, cc);
			}

			if (bcc != null) {
				msg.setRecipients(Message.RecipientType.BCC, bcc);
			}

			msg.setSubject(subject);

			if ((attachments != null) && (attachments.length > 0)) {
				MimeMultipart rootMultipart = new MimeMultipart(
					_MULTIPART_TYPE_MIXED);

				MimeMultipart messageMultipart = new MimeMultipart(
					_MULTIPART_TYPE_ALTERNATIVE);

				MimeBodyPart messageBodyPart = new MimeBodyPart();

				messageBodyPart.setContent(messageMultipart);

				rootMultipart.addBodyPart(messageBodyPart);

				if (htmlFormat) {
					MimeBodyPart bodyPart = new MimeBodyPart();

					bodyPart.setContent(body, _TEXT_HTML);

					messageMultipart.addBodyPart(bodyPart);
				}
				else {
					MimeBodyPart bodyPart = new MimeBodyPart();

					bodyPart.setText(body);

					messageMultipart.addBodyPart(bodyPart);
				}

				for (int i = 0; i < attachments.length; i++) {
					File attachment = attachments[i];

					if (attachment != null) {
						MimeBodyPart bodyPart = new MimeBodyPart();

						DataSource source = new FileDataSource(attachment);

						bodyPart.setDisposition(Part.ATTACHMENT);
						bodyPart.setDataHandler(new DataHandler(source));
						bodyPart.setFileName(attachment.getName());

						rootMultipart.addBodyPart(bodyPart);
					}
				}

				msg.setContent(rootMultipart);

				msg.saveChanges();
			}
			else {
				if (htmlFormat) {
					msg.setContent(body, _TEXT_HTML);
				}
				else {
					msg.setContent(body, _TEXT_PLAIN);
				}
			}

			msg.setSentDate(new Date());

			if (replyTo != null) {
				msg.setReplyTo(replyTo);
			}

			if (messageId != null) {
				msg.setHeader("Message-ID", messageId);
			}

			if (inReplyTo!= null) {
				msg.setHeader("In-Reply-To", inReplyTo);
				msg.setHeader("References", inReplyTo);
			}

			_send(session, msg);
		}
		catch (SendFailedException sfe) {
			_log.error(sfe);
		}
		catch (Exception e) {
			throw new MailEngineException(e);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Sending mail takes " + stopWatch.getTime() + " ms");
		}
	}

	public static void send(byte[] msgByteArray) throws MailEngineException {
		try {
			Session session = getSession();

			Message msg = new MimeMessage(
				session, new ByteArrayInputStream(msgByteArray));

			_send(session, msg);
		}
		catch (Exception e) {
			throw new MailEngineException(e);
		}
	}

	private static void _send(Session session, Message msg)
		throws MessagingException {

		try {
			boolean smtpAuth = GetterUtil.getBoolean(
				session.getProperty("mail.smtp.auth"), false);
			String smtpHost = session.getProperty("mail.smtp.host");
			String user = session.getProperty("mail.smtp.user");
			String password = session.getProperty("mail.smtp.password");

			if (smtpAuth && Validator.isNotNull(user) &&
				Validator.isNotNull(password)) {

				Transport transport = session.getTransport("smtp");

				transport.connect(smtpHost, user, password);

				transport.sendMessage(msg, msg.getAllRecipients());

				transport.close();
			}
			else {
				Transport.send(msg);
			}
		}
		catch (MessagingException me) {
			if (me.getNextException() instanceof SocketException) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Failed to connect to a valid mail server. Please " +
							"make sure one is properly configured. " +
								me.getMessage());
				}
			}
		}
	}

	private static final String _MULTIPART_TYPE_ALTERNATIVE = "alternative";

	private static final String _MULTIPART_TYPE_MIXED = "mixed";

	private static final String _TEXT_HTML = "text/html;charset=\"UTF-8\"";

	private static final String _TEXT_PLAIN = "text/plain;charset=\"UTF-8\"";

	private static Log _log = LogFactory.getLog(MailEngine.class);

}