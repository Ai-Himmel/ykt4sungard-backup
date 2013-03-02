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

package com.liferay.portal.im;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import rath.msnm.MSNMessenger;
import rath.msnm.SwitchboardSession;
import rath.msnm.entity.MsnFriend;
import rath.msnm.event.MsnAdapter;
import rath.msnm.msg.MimeMessage;

/**
 * <a href="MSNMessageAdapter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MSNMessageAdapter extends MsnAdapter {

	public MSNMessageAdapter(MSNMessenger msn, String to, String msg) {
		_msn = msn;
		_to = to;
		_msg = msg;
	}

	public void whoJoinSession(SwitchboardSession ss, MsnFriend join) {
		try {
			if (_to.equals(join.getLoginName())) {
				ss.sendInstantMessage(new MimeMessage(_msg));
				ss.cleanUp();
			}
		}
		catch (Exception e) {
			_log.warn(e);
		}

		_msn.removeMsnListener(this);
	}

	private static Log _log = LogFactory.getLog(MSNConnector.class);

	private MSNMessenger _msn;
	private String _to;
	private String _msg;

}