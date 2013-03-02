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

package com.liferay.portlet.messageboards.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.messageboards.service.persistence.MBThreadUtil;
import com.liferay.portlet.messageboards.service.spring.MBThreadService;
import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;

import java.util.List;

/**
 * <a href="MBThreadServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MBThreadServiceImpl
	extends PrincipalBean implements MBThreadService {

	// Business methods

	public boolean hasReadThread(String threadId)
		throws PortalException,  SystemException {

		try {
			String userId = getUserId();

			int total = MBMessageUtil.countByThreadId(threadId);
			int read = MBMessageFlagFinder.countByT_U(threadId, userId);

			if (total != read) {
				return false;
			}
			else {
				return true;
			}
		}
		catch (PrincipalException pe) {

			// Unauthenticated users do not have a record of read messages

			return true;
		}
	}

	public List getThreads(String topicId, int begin, int end)
		throws PortalException, SystemException {

		if (!MBTopicServiceUtil.hasRead(topicId)) {
			throw new PrincipalException();
		}

		return MBThreadUtil.findByTopicId(topicId, begin, end);
	}

	public int getThreadsSize(String topicId) throws SystemException {
		return MBThreadUtil.countByTopicId(topicId);
	}

}