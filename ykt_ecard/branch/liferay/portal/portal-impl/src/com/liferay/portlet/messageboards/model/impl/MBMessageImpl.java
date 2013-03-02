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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.service.MBCategoryLocalServiceUtil;
import com.liferay.portlet.messageboards.service.MBThreadLocalServiceUtil;
import com.liferay.portlet.messageboards.util.BBCodeUtil;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBMessageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageImpl extends MBMessageModelImpl implements MBMessage {

	public static final long DEFAULT_PARENT_MESSAGE_ID = 0;

	public MBMessageImpl() {
	}

	public String getUserUuid() throws SystemException {
		return PortalUtil.getUserValue(getUserId(), "uuid", _userUuid);
	}

	public void setUserUuid(String userUuid) {
		_userUuid = userUuid;
	}

	public MBCategory getCategory() {
		MBCategory category = null;

		try {
			if (getCategoryId() == CompanyImpl.SYSTEM) {
				category = MBCategoryLocalServiceUtil.getSystemCategory();
			}
			else {
				category = MBCategoryLocalServiceUtil.getCategory(
					getCategoryId());
			}
		}
		catch (Exception e) {
			category = new MBCategoryImpl();

			_log.error(e);
		}

		return category;
	}

	public boolean isRoot() {
		if (getParentMessageId() == DEFAULT_PARENT_MESSAGE_ID) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isReply() {
		return !isRoot();
	}

	public boolean isDiscussion() {
		if (getCategoryId() == CompanyImpl.SYSTEM) {
			return true;
		}
		else {
			return false;
		}
	}

	public double getPriority() throws PortalException, SystemException {
		if (_priority == -1) {
			_priority = MBThreadLocalServiceUtil.getThread(getThreadId()).
				getPriority();
		}
		return _priority;
	}

	public void setPriority(double priority) {
		_priority = priority;
	}

	public String getThreadAttachmentsDir() {
		return "messageboards/" + getThreadId();
	}

	public String getAttachmentsDir() {
		if (_attachmentDirs == null) {
			_attachmentDirs = getThreadAttachmentsDir() + "/" + getMessageId();
		}
		return _attachmentDirs;
	}

	public void setAttachmentsDir(String attachmentsDir) {
		_attachmentDirs = attachmentsDir;
	}

	public String getBody(boolean translated) {
		if (translated) {
			return BBCodeUtil.getHTML(getBody());
		}
		else {
			return getBody();
		}
	}

	public String[] getTagsEntries() throws PortalException, SystemException {
		return TagsEntryLocalServiceUtil.getEntryNames(
			MBMessage.class.getName(), getMessageId());
	}

	private static Log _log = LogFactory.getLog(MBMessageImpl.class);

	private String _userUuid;
	private double _priority = -1;
	private String _attachmentDirs;

}