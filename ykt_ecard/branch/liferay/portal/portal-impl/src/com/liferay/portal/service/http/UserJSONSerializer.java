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

package com.liferay.portal.service.http;

import com.liferay.portal.model.User;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="UserJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.UserServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.UserServiceJSON
 *
 */
public class UserJSONSerializer {
	public static JSONObject toJSONObject(User model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "uuid", model.getUuid());
		JSONUtil.put(jsonObj, "userId", model.getUserId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
		JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
		JSONUtil.put(jsonObj, "defaultUser", model.getDefaultUser());
		JSONUtil.put(jsonObj, "contactId", model.getContactId());
		JSONUtil.put(jsonObj, "password", model.getPassword());
		JSONUtil.put(jsonObj, "passwordEncrypted", model.getPasswordEncrypted());
		JSONUtil.put(jsonObj, "passwordReset", model.getPasswordReset());
		JSONUtil.put(jsonObj, "passwordModifiedDate",
			model.getPasswordModifiedDate());
		JSONUtil.put(jsonObj, "graceLoginCount", model.getGraceLoginCount());
		JSONUtil.put(jsonObj, "screenName", model.getScreenName());
		JSONUtil.put(jsonObj, "emailAddress", model.getEmailAddress());
		JSONUtil.put(jsonObj, "portraitId", model.getPortraitId());
		JSONUtil.put(jsonObj, "languageId", model.getLanguageId());
		JSONUtil.put(jsonObj, "timeZoneId", model.getTimeZoneId());
		JSONUtil.put(jsonObj, "greeting", model.getGreeting());
		JSONUtil.put(jsonObj, "comments", model.getComments());
		JSONUtil.put(jsonObj, "loginDate", model.getLoginDate());
		JSONUtil.put(jsonObj, "loginIP", model.getLoginIP());
		JSONUtil.put(jsonObj, "lastLoginDate", model.getLastLoginDate());
		JSONUtil.put(jsonObj, "lastLoginIP", model.getLastLoginIP());
		JSONUtil.put(jsonObj, "lastFailedLoginDate",
			model.getLastFailedLoginDate());
		JSONUtil.put(jsonObj, "failedLoginAttempts",
			model.getFailedLoginAttempts());
		JSONUtil.put(jsonObj, "lockout", model.getLockout());
		JSONUtil.put(jsonObj, "lockoutDate", model.getLockoutDate());
		JSONUtil.put(jsonObj, "agreedToTermsOfUse",
			model.getAgreedToTermsOfUse());
		JSONUtil.put(jsonObj, "active", model.getActive());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			User model = (User)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}