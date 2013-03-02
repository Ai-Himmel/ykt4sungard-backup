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

package com.liferay.mail.service.jms;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.lang.MethodInvoker;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.mail.MailEngine;
import com.liferay.util.mail.MailMessage;

import javax.jms.JMSException;
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

/**
 * <a href="MailConsumer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MailConsumer implements MessageListener {

	public void consume() throws JMSException {
		QueueConnectionFactory qcf = MailQCFUtil.getQCF();
		QueueConnection con = qcf.createQueueConnection();

		QueueSession session = con.createQueueSession(
			false, Session.AUTO_ACKNOWLEDGE);
		Queue queue = (Queue)MailQueueUtil.getQueue();

		QueueReceiver subscriber = session.createReceiver(queue);
		subscriber.setMessageListener(this);

		con.start();
	}

	public void onMessage(Message msg) {
		try {
			ObjectMessage objMsg = (ObjectMessage)msg;

			Object obj = objMsg.getObject();

			if (obj instanceof MailMessage) {
				MailMessage mailMessage = (MailMessage)obj;

				InternetAddress[] auditTrail = InternetAddress.parse(
					PropsUtil.get(PropsUtil.MAIL_AUDIT_TRAIL));

				if (auditTrail.length > 0) {
					InternetAddress[] bcc = mailMessage.getBCC();

					if (bcc != null) {
						InternetAddress[] allBCC = new InternetAddress[
							bcc.length + auditTrail.length];

						System.arraycopy(
							bcc, 0, allBCC, 0, bcc.length);

						System.arraycopy(
							auditTrail, 0, allBCC, bcc.length,
							auditTrail.length);

						mailMessage.setBCC(allBCC);
					}
					else {
						mailMessage.setBCC(auditTrail);
					}
				}

				MailEngine.send(mailMessage);
			}
			else if (obj instanceof MethodWrapper) {
				MethodWrapper methodWrapper = (MethodWrapper)obj;

				MethodInvoker.invoke(methodWrapper);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}