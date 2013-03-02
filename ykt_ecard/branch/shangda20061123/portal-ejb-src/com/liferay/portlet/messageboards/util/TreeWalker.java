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

package com.liferay.portlet.messageboards.util;

import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.service.spring.MBMessageServiceUtil;
import com.liferay.util.CollectionFactory;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * <a href="TreeWalker.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class TreeWalker implements Serializable {

	public TreeWalker() {
	}

	public TreeWalker(MBMessage message) {
		_messageIdsMap = CollectionFactory.getHashMap();

		try {
			_messages = (MBMessage[])MBMessageServiceUtil.getMessagesByThread(
				message.getThreadId()).toArray(new MBMessage[0]);

			for (int i = 0; i < _messages.length; i++) {
				String parentMessageId = _messages[i].getParentMessageId();

				if (((parentMessageId != null) &&
						(!parentMessageId.equals(
							MBMessage.DEFAULT_PARENT_MESSAGE_ID))) &&
					(!_messageIdsMap.containsKey(parentMessageId))) {

					_messageIdsMap.put(parentMessageId, new Integer(i));
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public MBMessage getRoot() {
		return _messages[0];
	}

	public MBMessage[] getChildren(MBMessage message) {
		List messages = new ArrayList();

		int[] range = getChildrenRange(message);

		for (int i = range[0]; i < range[1]; i++) {
			messages.add(_messages[i]);
		}

		return (MBMessage[])messages.toArray(new MBMessage[0]);
	}

	public int[] getChildrenRange(MBMessage message) {
		String messageId = message.getMessageId();

		Integer pos = (Integer)_messageIdsMap.get(messageId);

		if (pos == null) {
			return new int[] {0, 0};
		}

		int[] range = new int[2];
		range[0] = pos.intValue();

		for (int i = range[0]; i < _messages.length; i++) {
			if (_messages[i].getParentMessageId().equals(messageId)) {
				range[1] = i + 1;
			}
			else {
				break;
			}
		}

		return range;
	}

	public MBMessage[] getMessages() {
		return _messages;
	}

	public boolean isOdd() {
		_odd = !_odd;

		return _odd;
	}

	public boolean isLeaf(MBMessage message) {
		if (_messageIdsMap.get(message.getMessageId()) == null) {
			return true;
		}
		else {
			return false;
		}
	}

	private MBMessage[] _messages;
	private Map _messageIdsMap;
	private boolean _odd;

}