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

package com.liferay.mail.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;

import java.util.List;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.NameValuePair;
import org.apache.commons.httpclient.methods.PostMethod;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="FuseMailHook.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class FuseMailHook implements Hook {

	public FuseMailHook() {
		_client = new HttpClient();
	}

	public void addForward(
		long userId, List filters, List emailAddresses, boolean leaveCopy) {
	}

	public void addUser(
		long userId, String password, String firstName, String middleName,
		String lastName, String emailAddress) {

		try {
			String mailUserId = getMailUserId(userId);

			PostMethod method = getPostMethod();

			method.addParameter("request", "order");
			method.addParameter("user", mailUserId);
			method.addParameter("password", password);
			method.addParameter("first_name", firstName);
			method.addParameter("last_name", lastName);
			method.addParameter("account_type", _ACCOUNT_TYPE);
			method.addParameter("group_parent", _GROUP_PARENT);
			method.addParameter("alias[0]", emailAddress);

			executeMethod(method);
        }
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public void addVacationMessage(
		long userId, String emailAddress, String vacationMessage) {
	}

	public void deleteEmailAddress(long userId) {
		try {
			User user = UserLocalServiceUtil.getUserById(userId);

			String mailUserId = getMailUserId(userId);

			PostMethod method = getPostMethod();

			method.addParameter("request", "removealias");
			method.addParameter("user", mailUserId);
			method.addParameter("alias", user.getEmailAddress());

			executeMethod(method);
        }
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public void deleteUser(long userId) {
		try {
			String mailUserId = getMailUserId(userId);

			PostMethod method = getPostMethod();

			method.addParameter("request", "terminate");
			method.addParameter("user", mailUserId);

			executeMethod(method);
        }
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public void updateBlocked(long userId, List blocked) {
	}

	public void updateEmailAddress(long userId, String emailAddress) {
		try {
			deleteEmailAddress(userId);

			String mailUserId = getMailUserId(userId);

			PostMethod method = getPostMethod();

			method.addParameter("request", "modify");
			method.addParameter("user", mailUserId);
			method.addParameter("alias[0]", emailAddress);

			executeMethod(method);
        }
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public void updatePassword(long userId, String password) {
		try {
			String mailUserId = getMailUserId(userId);

			PostMethod method = getPostMethod();

			method.addParameter("request", "modify");
			method.addParameter("user", mailUserId);
			method.addParameter("password", password);

			executeMethod(method);
        }
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	protected int executeMethod(PostMethod method) throws Exception {
		HttpClient client = getHttpClient();

		int status = client.executeMethod(method);

		if (_log.isDebugEnabled()) {
			_log.debug("Posting to URI: " + method.getURI());

			NameValuePair[] pairs = method.getParameters();

			if (pairs.length > 0) {
				StringMaker sm = new StringMaker();

				sm.append("With parameters:\n");

				for (int i = 0; i < pairs.length; i++) {
					sm.append("\t");
					sm.append(pairs[i]);
					sm.append("\n");
				}

				_log.debug(sm.toString());
			}

			_log.debug("Status: " + status);
			_log.debug("Response body: " + method.getResponseBodyAsString());
		}

		return status;
	}

	protected String getMailUserId(long userId) throws Exception {
		User user = UserLocalServiceUtil.getUserById(userId);

		StringMaker sm = new StringMaker();

		sm.append(user.getCompanyMx());
		sm.append(StringPool.PERIOD);
		sm.append(user.getUserId());

		String mailUserId = sm.toString();

		if (_log.isDebugEnabled()) {
			_log.debug("Mail user id " + mailUserId + " for user id " + userId);
		}

		return mailUserId;
	}

	protected HttpClient getHttpClient() {
		return _client;
	}

	protected PostMethod getPostMethod() {
		PostMethod post = new PostMethod(_URL);

		post.addParameter("PlatformUser", _USERNAME);
		post.addParameter("PlatformPassword", _PASSWORD);

		return post;
	}

	private static final String _URL = PropsUtil.get(
		PropsUtil.MAIL_HOOK_FUSEMAIL_URL);

	private static final String _USERNAME = PropsUtil.get(
		PropsUtil.MAIL_HOOK_FUSEMAIL_USERNAME);

	private static final String _PASSWORD = PropsUtil.get(
		PropsUtil.MAIL_HOOK_FUSEMAIL_PASSWORD);

	private static final String _ACCOUNT_TYPE = PropsUtil.get(
		PropsUtil.MAIL_HOOK_FUSEMAIL_ACCOUNT_TYPE);

	private static final String _GROUP_PARENT = PropsUtil.get(
		PropsUtil.MAIL_HOOK_FUSEMAIL_GROUP_PARENT);

	private static Log _log = LogFactory.getLog(FuseMailHook.class);

	private HttpClient _client;

}