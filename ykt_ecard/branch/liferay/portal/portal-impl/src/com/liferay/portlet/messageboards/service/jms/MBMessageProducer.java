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

import com.liferay.portal.SystemException;
import com.liferay.util.JMSUtil;

import java.io.Serializable;

import javax.jms.JMSException;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueSender;
import javax.jms.QueueSession;

/**
 * <a href="MBMessageProducer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageProducer {

	static {
		MBMessageConsumer consumer = new MBMessageConsumer();

		consumer.consume();
	}

	public static void produce(Serializable obj) throws SystemException {
		QueueConnection con = null;
		QueueSession session = null;
		QueueSender sender = null;

		try {
			QueueConnectionFactory qcf = MBMessageQCFUtil.getQCF();
			Queue queue = MBMessageQueueUtil.getQueue();

			con = qcf.createQueueConnection();
			session = con.createQueueSession(
				false, QueueSession.AUTO_ACKNOWLEDGE);
			sender = session.createSender(queue);

			ObjectMessage objMsg = session.createObjectMessage();

			objMsg.setObject(obj);

			sender.send(objMsg);
		}
		catch (JMSException jmse) {
			throw new SystemException(jmse);
		}
		finally {
			JMSUtil.cleanUp(con, session, sender);
		}
	}

}