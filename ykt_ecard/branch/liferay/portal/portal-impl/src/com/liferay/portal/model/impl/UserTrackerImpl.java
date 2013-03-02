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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.model.UserTrackerPath;
import com.liferay.portal.service.UserLocalServiceUtil;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UserTrackerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserTrackerImpl
	extends UserTrackerModelImpl implements UserTracker {

	public UserTrackerImpl() {
	}

	public HttpSession getHttpSession() {
		return _ses;
	}

	public void setHttpSession(HttpSession ses) {
		_ses = ses;

		setSessionId(_ses.getId());
	}

	public String getFullName() {
		if (_fullName == null) {
			try {
				if (_user == null) {
					_user = UserLocalServiceUtil.getUserById(getUserId());
				}

				_fullName = _user.getFullName();
			}
			catch (Exception e) {
			}
		}

		if (_fullName == null) {
			_fullName = StringPool.BLANK;
		}

		return _fullName;
	}

	public String getEmailAddress() {
		if (_emailAddress == null) {
			try {
				if (_user == null) {
					_user = UserLocalServiceUtil.getUserById(getUserId());
				}

				_emailAddress = _user.getEmailAddress();
			}
			catch (Exception e) {
			}
		}

		if (_emailAddress == null) {
			_emailAddress = StringPool.BLANK;
		}

		return _emailAddress;
	}

	public List getPaths() {
		return _paths;
	}

	public void addPath(UserTrackerPath path) {
		try {
			_paths.add(path);
		}
		catch (ArrayIndexOutOfBoundsException aioobe) {
			if (_log.isWarnEnabled()) {
				_log.warn(aioobe);
			}
		}

		setModifiedDate(path.getPathDate());
	}

	public int getHits() {
		return _paths.size();
	}

	public int compareTo(Object obj) {
		UserTracker userTracker = (UserTracker)obj;

		String userName1 = getFullName().toLowerCase();
		String userName2 = userTracker.getFullName().toLowerCase();

		int value = userName1.compareTo(userName2);

		if (value == 0) {
			value = getModifiedDate().compareTo(userTracker.getModifiedDate());
		}

		return value;
	}

	private static Log _log = LogFactory.getLog(UserTrackerImpl.class);

	private HttpSession _ses;
	private User _user;
	private String _fullName;
	private String _emailAddress;
	private List _paths = new ArrayList();

}