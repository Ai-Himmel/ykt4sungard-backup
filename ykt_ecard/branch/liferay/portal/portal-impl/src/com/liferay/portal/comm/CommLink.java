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

package com.liferay.portal.comm;

import com.liferay.portal.kernel.util.MethodInvoker;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PropsUtil;

import java.io.Serializable;

import java.util.LinkedList;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.jgroups.Channel;
import org.jgroups.JChannel;
import org.jgroups.Message;
import org.jgroups.MessageListener;
import org.jgroups.blocks.PullPushAdapter;
import org.jgroups.util.Util;

/**
 * <a href="CommLink.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CommLink implements MessageListener {

	public static CommLink getInstance() {
		return _instance;
	}

	public byte[] getState() {
		try {
			return Util.objectToByteBuffer(_history);
		}
		catch(Exception e) {
			return null;
		}
	}

	public void setState(byte[] state) {
		try {
			_history = (List)Util.objectFromByteBuffer(state);
		}
		catch(Exception e) {
			_log.error("Error setting state", e);
		}
	}

	public void receive(Message msg) {
		try {
			Object obj = msg.getObject();

			if (_log.isDebugEnabled()) {
				_log.debug("Receiving message " + obj);
			}

			if (obj instanceof MethodWrapper) {
				MethodWrapper methodWrapper = (MethodWrapper)obj;

				MethodInvoker.invoke(methodWrapper);
			}

			_history.add(obj);
		}
		catch(Exception e) {
			_log.error("Error receiving message", e);
		}
	}

	public void send(Serializable obj) {
		try {
			if (_channel == null) {
				return;
			}

			Message msg = new Message(null, null, obj);

			_channel.send(msg);
		}
		catch(Exception e) {
			_log.error("Error sending message", e);
		}
	}

	private CommLink() {
		try {
			String properties = PropsUtil.get(PropsUtil.COMM_LINK_PROPERTIES);

			if (Validator.isNotNull(properties)) {
				_channel = new JChannel(properties);

				_channel.connect("PortalMessageListener");

				new PullPushAdapter(_channel, this);
			}
		}
		catch (Exception e) {
			_log.error("Error initializing", e);
		}
	}

	private static Log _log = LogFactory.getLog(CommLink.class);

	private static CommLink _instance = new CommLink();

	private Channel _channel;
	private List _history = new LinkedList();

}