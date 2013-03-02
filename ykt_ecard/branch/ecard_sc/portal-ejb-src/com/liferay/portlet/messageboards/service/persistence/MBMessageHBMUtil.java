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

package com.liferay.portlet.messageboards.service.persistence;

/**
 * <a href="MBMessageHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessageHBMUtil {
	public static com.liferay.portlet.messageboards.model.MBMessage model(
		MBMessageHBM mbMessageHBM) {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = MBMessagePool.get(mbMessageHBM.getPrimaryKey());

		if (mbMessage == null) {
			mbMessage = new com.liferay.portlet.messageboards.model.MBMessage(mbMessageHBM.getMessageId(),
					mbMessageHBM.getTopicId(), mbMessageHBM.getCompanyId(),
					mbMessageHBM.getUserId(), mbMessageHBM.getUserName(),
					mbMessageHBM.getCreateDate(),
					mbMessageHBM.getModifiedDate(), mbMessageHBM.getThreadId(),
					mbMessageHBM.getParentMessageId(),
					mbMessageHBM.getSubject(), mbMessageHBM.getBody(),
					mbMessageHBM.getAttachments(), mbMessageHBM.getAnonymous());
			MBMessagePool.put(mbMessage.getPrimaryKey(), mbMessage);
		}

		return mbMessage;
	}
}