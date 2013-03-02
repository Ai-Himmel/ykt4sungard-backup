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

import com.liferay.util.JMSUtil;

import java.io.Serializable;

import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueSender;
import javax.jms.QueueSession;

import org.codehaus.activemq.broker.BrokerContainer;
import org.codehaus.activemq.broker.BrokerContext;
import org.codehaus.activemq.spring.SpringBrokerContainerFactory;

import org.springframework.core.io.ClassPathResource;

/**
 * <a href="MailProducer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MailProducer {

	static {
		try {
			SpringBrokerContainerFactory factory =
				new SpringBrokerContainerFactory();
			factory.setResource(new ClassPathResource("META-INF/activemq.xml"));

			BrokerContainer container = factory.createBrokerContainer(
				"DefaultBroker", BrokerContext.getInstance());
			container.start();

			MailConsumer consumer = new MailConsumer();
			consumer.consume();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void produce(Serializable obj) {
		QueueConnection con = null;
		QueueSession session = null;
		QueueSender sender = null;

		try {
			QueueConnectionFactory qcf = MailQCFUtil.getQCF();
			Queue queue = MailQueueUtil.getQueue();

			con = qcf.createQueueConnection();
			session = con.createQueueSession(
				false, QueueSession.AUTO_ACKNOWLEDGE);
			sender = session.createSender(queue);

			ObjectMessage objMsg = session.createObjectMessage();
			objMsg.setObject(obj);

			sender.send(objMsg);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			JMSUtil.cleanUp(con, session, sender);
		}
	}

}