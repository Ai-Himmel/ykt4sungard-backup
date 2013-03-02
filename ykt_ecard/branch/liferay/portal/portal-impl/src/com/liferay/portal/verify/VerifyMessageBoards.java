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

package com.liferay.portal.verify;

import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceUtil;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="VerifyMessageBoards.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class VerifyMessageBoards extends VerifyProcess {

	public void verify() throws VerifyException {
		_log.info("Verifying integrity");

		try {
			verifyMessageBoards();
		}
		catch (Exception e) {
			throw new VerifyException(e);
		}
	}

	protected void verifyMessageBoards() throws Exception {
		List messages = MBMessageLocalServiceUtil.getNoAssetMessages();

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Processing " + messages.size() +
					" messages with no tags assets");
		}

		for (int i = 0; i < messages.size(); i++) {
			MBMessage message = (MBMessage)messages.get(i);

			try {
				MBMessageLocalServiceUtil.updateTagsAsset(
					message.getUserId(), message, new String[0]);
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Unable to update tags asset for message " +
							message.getMessageId() + ": " + e.getMessage());
				}
			}
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Tags assets verified for messages");
		}
	}

	private static Log _log = LogFactory.getLog(VerifyMessageBoards.class);

}