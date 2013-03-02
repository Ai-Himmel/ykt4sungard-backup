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

package com.liferay.portlet.messageboards.model.impl;

import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBTreeWalker;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceUtil;
import com.liferay.util.CollectionFactory;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBTreeWalkerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBTreeWalkerImpl implements MBTreeWalker {

	public MBTreeWalkerImpl(MBMessage message) {
		_messageIdsMap = CollectionFactory.getHashMap();

		try {
			_messages = MBMessageLocalServiceUtil.getThreadMessages(
				message.getThreadId());

			for (int i = 0; i < _messages.size(); i++) {
				MBMessage curMessage = (MBMessage)_messages.get(i);

				Long parentMessageIdObj = new Long(
					curMessage.getParentMessageId());

				if (!curMessage.isRoot() &&
					!_messageIdsMap.containsKey(parentMessageIdObj)) {

					_messageIdsMap.put(parentMessageIdObj, new Integer(i));
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	public MBMessage getRoot() {
		return (MBMessage)_messages.get(0);
	}

	public List getChildren(MBMessage message) {
		List children = new ArrayList();

		int[] range = getChildrenRange(message);

		for (int i = range[0]; i < range[1]; i++) {
			children.add(_messages.get(i));
		}

		return children;
	}

	public int[] getChildrenRange(MBMessage message) {
		Long messageIdObj = new Long(message.getMessageId());

		Integer pos = (Integer)_messageIdsMap.get(messageIdObj);

		if (pos == null) {
			return new int[] {0, 0};
		}

		int[] range = new int[2];
		range[0] = pos.intValue();

		for (int i = range[0]; i < _messages.size(); i++) {
			MBMessage curMessage = (MBMessage)_messages.get(i);

			if (curMessage.getParentMessageId() == messageIdObj.longValue()) {
				range[1] = i + 1;
			}
			else {
				break;
			}
		}

		return range;
	}

	public List getMessages() {
		return _messages;
	}

	public boolean isOdd() {
		_odd = !_odd;

		return _odd;
	}

	public boolean isLeaf(MBMessage message) {
		Long messageIdObj = new Long(message.getMessageId());

		if (_messageIdsMap.containsKey(messageIdObj)) {
			return false;
		}
		else {
			return true;
		}
	}

	private static Log _log = LogFactory.getLog(MBTreeWalkerImpl.class);

	private List _messages;
	private Map _messageIdsMap;
	private boolean _odd;

}