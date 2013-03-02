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

import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBMessageDisplay;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.portlet.messageboards.model.MBTreeWalker;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="MBMessageDisplayImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageDisplayImpl implements MBMessageDisplay {

	public MBMessageDisplayImpl(MBMessage message, MBMessage parentMessage,
								MBCategory category, MBThread thread,
								MBTreeWalker treeWalker,
								MBThread previousThread, MBThread nextThread,
								MBThread firstThread, MBThread lastThread) {

		_message = message;
		_parentMessage = parentMessage;
		_category = category;
		_thread = thread;
		_treeWalker = new MBTreeWalkerImpl(message);
		_previousThread = previousThread;
		_nextThread = nextThread;
		_firstThread = firstThread;
		_lastThread = lastThread;

		List orderedMessages = new ArrayList();

		_orderMessages(_treeWalker, treeWalker.getRoot(), orderedMessages);

		for (int i = 0; i < orderedMessages.size(); i++) {
			MBMessage curMessage = (MBMessage)orderedMessages.get(i);

			if (i == 0) {
				_firstMessage = curMessage;
			}

			if (curMessage.equals(message)) {
				if ((i - 1) >= 0) {
					_previousMessage = (MBMessage)orderedMessages.get(i - 1);
				}

				if ((i + 1) < orderedMessages.size()) {
					_nextMessage = (MBMessage)orderedMessages.get(i + 1);
				}
			}

			if ((i + 1) == orderedMessages.size()) {
				_lastMessage = curMessage;
			}
		}
	}

	public MBMessage getMessage() {
		return _message;
	}

	public MBMessage getParentMessage() {
		return _parentMessage;
	}

	public MBCategory getCategory() {
		return _category;
	}

	public MBThread getThread() {
		return _thread;
	}

	public MBTreeWalker getTreeWalker() {
		return _treeWalker;
	}

	public MBThread getPreviousThread() {
		return _previousThread;
	}

	public MBThread getNextThread() {
		return _nextThread;
	}

	public MBThread getFirstThread() {
		return _firstThread;
	}

	public MBThread getLastThread() {
		return _lastThread;
	}

	public boolean isFirstThread() {
		if (_firstThread == null) {
			return false;
		}
		else if (_firstThread.equals(_thread)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isLastThread() {
		if (_lastThread == null) {
			return false;
		}
		else if (_lastThread.equals(_thread)) {
			return true;
		}
		else {
			return false;
		}
	}

	public MBMessage getPreviousMessage() {
		return _previousMessage;
	}

	public MBMessage getNextMessage() {
		return _nextMessage;
	}

	public MBMessage getFirstMessage() {
		return _firstMessage;
	}

	public MBMessage getLastMessage() {
		return _lastMessage;
	}

	public boolean isFirstMessage() {
		if (_firstMessage == null) {
			return false;
		}
		else if (_firstMessage.equals(_message)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isLastMessage() {
		if (_lastMessage == null) {
			return false;
		}
		else if (_lastMessage.equals(_message)) {
			return true;
		}
		else {
			return false;
		}
	}

	private void _orderMessages(
		MBTreeWalker treeWalker, MBMessage message, List orderedMessages) {

		orderedMessages.add(message);

		List messages = treeWalker.getMessages();
		int[] range = treeWalker.getChildrenRange(message);

		for (int i = range[0]; i < range[1]; i++) {
			MBMessage curMessage = (MBMessage)messages.get(i);

			_orderMessages(treeWalker, curMessage, orderedMessages);
		}
	}

	private MBMessage _message;
	private MBMessage _parentMessage;
	private MBCategory _category;
	private MBThread _thread;
	private MBTreeWalker _treeWalker;
	private MBThread _previousThread;
	private MBThread _nextThread;
	private MBThread _firstThread;
	private MBThread _lastThread;
	private MBMessage _previousMessage;
	private MBMessage _nextMessage;
	private MBMessage _firstMessage;
	private MBMessage _lastMessage;

}