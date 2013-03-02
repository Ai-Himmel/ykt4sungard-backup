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

package com.liferay.portal.upgrade.v4_3_0.util;

import com.liferay.documentlibrary.service.DLLocalServiceUtil;
import com.liferay.documentlibrary.service.DLServiceUtil;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBMessageAttachmentsUpgradeColumnImpl.java.html"><b><i>View Source
 * </i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageAttachmentsUpgradeColumnImpl
	extends BaseUpgradeColumnImpl {

	public MBMessageAttachmentsUpgradeColumnImpl(
		UpgradeColumn messageIdColumn, UpgradeColumn companyIdColumn,
		UpgradeColumn threadIdColumn) {

		super("attachments");

		_messageIdColumn = messageIdColumn;
		_companyIdColumn = companyIdColumn;
		_threadIdColumn = threadIdColumn;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		Boolean attachments = (Boolean)oldValue;

		if (attachments.booleanValue()) {
			Long oldMessageId = (Long)_messageIdColumn.getOldValue();
			String oldCompanyId = (String)_companyIdColumn.getOldValue();
			Long oldThreadId = (Long)_threadIdColumn.getOldValue();

			Long newMessageId = (Long)_messageIdColumn.getNewValue();
			Long newCompanyId = (Long)_companyIdColumn.getNewValue();
			Long newThreadId = (Long)_threadIdColumn.getNewValue();

			try {
				DLServiceUtil.addDirectory(
					newCompanyId.longValue(), CompanyImpl.SYSTEM,
					"messageboards/" + newThreadId);

				DLLocalServiceUtil.move(
					"/" + oldCompanyId +
						"/documentlibrary/system/messageboards/" + oldThreadId +
							"/" + oldMessageId,
					"/" + newCompanyId + "/documentlibrary/0/messageboards/" +
						newThreadId + "/" + newMessageId);
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		return attachments;
	}

	private static Log _log =
		LogFactory.getLog(MBMessageAttachmentsUpgradeColumnImpl.class);

	private UpgradeColumn _messageIdColumn;
	private UpgradeColumn _companyIdColumn;
	private UpgradeColumn _threadIdColumn;

}