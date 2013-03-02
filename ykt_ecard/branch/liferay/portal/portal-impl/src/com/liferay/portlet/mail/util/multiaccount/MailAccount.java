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

package com.liferay.portlet.mail.util.multiaccount;

import com.liferay.portal.kernel.util.StringPool;

import java.io.Serializable;

import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Store;

import org.apache.commons.lang.builder.ToStringBuilder;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailAccount.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * MailAccount represents a mail account. It contains all the necessary
 * information to connect to the IMAP server with its credentials.
 * </p>
 *
 * @author Jorge Ferrer
 *
 */
public class MailAccount implements Serializable {

	public MailAccount(String accountName, long userId, String password,
					   String emailAddress) {

		this(accountName, String.valueOf(userId), password, emailAddress);
	}

	public MailAccount(String accountName, String userId, String password,
					   String emailAddress) {

		_name = accountName;
		_userId = userId;
		_password = password;
		_emailAddress = emailAddress;
	}

	public String getName() {
		return _name;
	}

	public String getUserId() {
		return _userId;
	}

	public String getPassword() {
		return _password;
	}

	public String getEmailAddress() {
		return _emailAddress;
	}

	public String getRole() {
		return _role;
	}

	public void setRole(String role) {
		_role = role;
	}

	public Store getStore() {
		return _store;
	}

	public void setStore(Store store) {
		_store = store;
		_size = calculateStoreSize(store);
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		_active = active;
	}

	public long getQuota() {
		return _quota;
	}

	public void setQuota(long quota) {
		_quota = quota;
	}

	public long getQuotaInMb() {
		return Math.round((float)getQuota() / _MB);
	}

	public long getSize() {
		return _size;
	}

	public long getSizeInMb() {
		return _size / _MB;
	}

	public long getFreeSpace() {
		return Math.max(0, getQuota() - getSize());
	}

	public long getFreeSpaceInMb() {
		return Math.round((float)getFreeSpace() / _MB);
	}

	public long getFreeSpaceInPercentage() {
		return Math.round(((float)getSize() / getQuota()) * 100);
	}

	private static long calculateStoreSize(Store store) {
		return 1;

		/*try {
			return calculateFolderSize(store.getDefaultFolder());
		}
		catch (MessagingException me) {
			_log.warn("Error calculating store size", me);
		}*/
	}

	private static long calculateFolderSize(Folder folder)
		throws MessagingException {

		long size = 0;

		if ((folder.getType() & Folder.HOLDS_MESSAGES) != 0) {
			folder.open(Folder.READ_ONLY);

			try {
				Message[] folderMsgs = folder.getMessages();

				for (int i = 0; i < folderMsgs.length; i++) {
					int msgSize = folderMsgs[i].getSize();

					if (msgSize != -1) {
						size += msgSize;
					}
					else {
						if (_log.isWarnEnabled()) {
							_log.warn(
								"Could not determine the size of message " +
									folderMsgs[i].getSubject());
						}
					}
				}
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Error calculating the size of the folder " +
							folder.getName(),
						e);
				}
			}
			finally {
				folder.close(false);
			}
		}

		if ((folder.getType() & Folder.HOLDS_FOLDERS) != 0) {
			Folder[] folderChildren = folder.list();

			for (int i = 0; i < folderChildren.length; i++) {
				size += calculateFolderSize(folderChildren[i]);
			}
		}

		return size;
	}

	public String toString() {
		return ToStringBuilder.reflectionToString(this);
	}

	public static final long _MB = 1024 * 1024;

	private static Log _log = LogFactory.getLog(MailAccount.class);

	private String _name;
	private String _userId;
	private String _password;
	private String _emailAddress;
	private String _role = StringPool.BLANK;
	private Store _store;
	private boolean _active = true;
	private long _quota = 0;
	private long _size = 0;

}