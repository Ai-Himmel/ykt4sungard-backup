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

package com.liferay.portal.pop;

import com.liferay.portal.job.IntervalJob;
import com.liferay.portal.kernel.pop.MessageListener;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.Time;
import com.liferay.util.mail.MailEngine;

import java.util.Iterator;
import java.util.List;

import javax.mail.Address;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message.RecipientType;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.internet.InternetAddress;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * <a href="POPNotificationsJob.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class POPNotificationsJob implements IntervalJob {

	public static final long INTERVAL = GetterUtil.getLong(PropsUtil.get(
		PropsUtil.POP_SERVER_NOTIFICATIONS_INTERVAL)) * Time.MINUTE;

	public long getInterval() {
		return INTERVAL;
	}

	public void execute(JobExecutionContext context)
		throws JobExecutionException {

		if (!_executing) {
			try {
				_executing = true;

				if (_log.isDebugEnabled()) {
					_log.debug("Executing");

					pollPopServer();
				}
			}
			catch (Exception e) {
				_log.error(e, e);
			}
			finally {
				_executing = false;
			}
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug("Not executing");
			}
		}
	}

	protected String getEmailAddress(Address[] addresses) {
		if ((addresses == null) || (addresses.length == 0)) {
			return StringPool.BLANK;
		}

		InternetAddress internetAddress = (InternetAddress)addresses[0];

		return internetAddress.getAddress();
	}

	protected void initInboxFolder() throws Exception {
		if ((_inboxFolder == null) || !_inboxFolder.isOpen()) {
			initStore();

			Folder defaultFolder = _store.getDefaultFolder();

			Folder[] folders = defaultFolder.list();

			if (folders.length == 0) {
				throw new MessagingException("Inbox not found");
			}
			else {
				_inboxFolder = folders[0];

				_inboxFolder.open(Folder.READ_WRITE);
			}
		}
	}

	protected void initStore() throws Exception {
		if ((_store == null) || !_store.isConnected()) {
			Session session = MailEngine.getSession();

			_store = session.getStore("pop3");

			String popHost = session.getProperty("mail.pop3.host");
			String smtpUser = session.getProperty("mail.smtp.user");
			String smtpPassword = session.getProperty("mail.smtp.password");

			_store.connect(popHost, smtpUser, smtpPassword);
		}
	}

	protected void nostifyListeners(List listeners, Message message)
		throws Exception {

		String from = getEmailAddress(message.getFrom());
		String recipient = getEmailAddress(
			message.getRecipients(RecipientType.TO));

		if (_log.isDebugEnabled()) {
			_log.debug("From " + from);
			_log.debug("Recipient " + recipient);
		}

		Iterator itr = listeners.iterator();

		while (itr.hasNext()) {
			MessageListener messageListener = (MessageListener)itr.next();

			try {
				if (messageListener.accept(from, recipient)) {
					messageListener.deliver(from, recipient, message);
				}
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}
	}

	protected void nostifyListeners(Message[] messages) throws Exception {
		if (_log.isDebugEnabled()) {
			_log.debug("Messages " + messages.length);
		}

		List listeners = POPServerUtil.getListeners();

		for (int i = 0; i < messages.length; i++) {
			Message message = messages[i];

			if (_log.isDebugEnabled()) {
				_log.debug("Message " + message);
			}

			nostifyListeners(listeners, message);
		}
	}

	protected void pollPopServer() throws Exception {
		initInboxFolder();

		Message[] messages = _inboxFolder.getMessages();

		try {
			nostifyListeners(messages);
		}
		finally {
			if (_log.isDebugEnabled()) {
				_log.debug("Deleting messages");
			}

			_inboxFolder.setFlags(
				messages, new Flags(Flags.Flag.DELETED), true);

			_inboxFolder.close(true);
		}
	}

	private static Log _log = LogFactory.getLog(POPNotificationsJob.class);

	private boolean _executing;
	private Store _store;
	private Folder _inboxFolder;

}