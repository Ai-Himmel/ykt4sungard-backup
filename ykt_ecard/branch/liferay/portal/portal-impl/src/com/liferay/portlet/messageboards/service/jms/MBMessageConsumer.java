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

package com.liferay.portlet.messageboards.service.jms;

import com.liferay.mail.service.MailServiceUtil;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.kernel.mail.MailMessage;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Subscription;
import com.liferay.portal.model.User;
import com.liferay.portal.service.SubscriptionLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.util.CollectionFactory;

import java.util.List;
import java.util.Set;

import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueReceiver;
import javax.jms.QueueSession;
import javax.jms.Session;

import javax.mail.internet.InternetAddress;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBMessageConsumer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageConsumer implements MessageListener {

	public void consume() {
		try {
			QueueConnectionFactory qcf = MBMessageQCFUtil.getQCF();
			QueueConnection con = qcf.createQueueConnection();

			QueueSession session = con.createQueueSession(
				false, Session.AUTO_ACKNOWLEDGE);
			Queue queue = (Queue)MBMessageQueueUtil.getQueue();

			QueueReceiver subscriber = session.createReceiver(queue);

			subscriber.setMessageListener(this);

			con.start();
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	public void onMessage(Message msg) {
		try {
			ObjectMessage objMsg = (ObjectMessage)msg;

			String[] array = (String[])objMsg.getObject();

			_onMessage(array);
		}
		catch (Exception e) {
			_log.error("Error sending message board notifications", e);
		}
	}

	private void _onMessage(String[] array) throws Exception {
		long companyId = GetterUtil.getLong(array[0]);
		long userId = GetterUtil.getLong(array[1]);
		String[] categoryIds = StringUtil.split(array[2]);
		String threadId = array[3];
		String fromName = array[4];
		String fromAddress = array[5];
		String subject = array[6];
		String body = array[7];
		String replyToAddress = array[8];
		String messageId = array[9];
		String inReplyTo = array[10];

		Set sent = CollectionFactory.getHashSet();

		if (_log.isInfoEnabled()) {
			_log.info(
				"Sending notifications for {messageId=" + messageId +
					", threadId=" + threadId + ", categoryIds=" + array[2] +
						"}");
		}

		// Threads

		List subscriptions = SubscriptionLocalServiceUtil.getSubscriptions(
			companyId, MBThread.class.getName(), GetterUtil.getLong(threadId));

		_sendEmail(
			userId, fromName, fromAddress, subject, body, subscriptions, sent,
			replyToAddress, messageId, inReplyTo);

		// Categories

		for (int i = 0; i < categoryIds.length; i++) {
			subscriptions = SubscriptionLocalServiceUtil.getSubscriptions(
				companyId, MBCategory.class.getName(),
				GetterUtil.getLong(categoryIds[i]));

			_sendEmail(
				userId, fromName, fromAddress, subject, body, subscriptions,
				sent, replyToAddress, messageId, inReplyTo);
		}

		if (_log.isInfoEnabled()) {
			_log.info("Finished sending notifications");
		}
	}

	private void _sendEmail(
			long userId, String fromName, String fromAddress, String subject,
			String body, List subscriptions, Set sent, String replyToAddress,
			String messageId, String inReplyTo)
		throws Exception {

		for (int i = 0; i < subscriptions.size(); i++) {
			Subscription subscription = (Subscription)subscriptions.get(i);

			Long subscribedUserId = new Long(subscription.getUserId());

			if (sent.contains(subscribedUserId)) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Do not send a duplicate email to user " +
							subscribedUserId);
				}

				continue;
			}
			else {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Add user " + subscribedUserId +
							" to the list of users who have received an email");
				}

				sent.add(subscribedUserId);
			}

			User user = null;

			try {
				user = UserLocalServiceUtil.getUserById(
					subscription.getUserId());
			}
			catch (NoSuchUserException nsue) {
				if (_log.isInfoEnabled()) {
					_log.info(
						"Subscription " + subscription.getSubscriptionId() +
							" is stale and will be deleted");
				}

				SubscriptionLocalServiceUtil.deleteSubscription(
					subscription.getSubscriptionId());

				continue;
			}

			try {
				InternetAddress from = new InternetAddress(
					fromAddress, fromName);

				InternetAddress to = new InternetAddress(
					user.getEmailAddress(), user.getFullName());

				String curSubject = StringUtil.replace(
					subject,
					new String[] {
						"[$TO_ADDRESS$]",
						"[$TO_NAME$]"
					},
					new String[] {
						user.getFullName(),
						user.getEmailAddress()
					});

				String curBody = StringUtil.replace(
					body,
					new String[] {
						"[$TO_ADDRESS$]",
						"[$TO_NAME$]"
					},
					new String[] {
						user.getFullName(),
						user.getEmailAddress()
					});

				InternetAddress replyTo = new InternetAddress(
					replyToAddress, replyToAddress);

				MailMessage message = new MailMessage(
					from, to, curSubject, curBody, false);

				message.setReplyTo(new InternetAddress[] {replyTo});
				message.setMessageId(messageId);
				message.setInReplyTo(inReplyTo);

				MailServiceUtil.sendEmail(message);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
	}

	private static Log _log = LogFactory.getLog(MBMessageConsumer.class);

}