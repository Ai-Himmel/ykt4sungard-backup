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

import com.liferay.portal.model.PasswordPolicy;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="PasswordPolicyJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.PasswordPolicyServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.PasswordPolicyServiceJSON
 *
 */
public class PasswordPolicyJSONSerializer {
	public static JSONObject toJSONObject(PasswordPolicy model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "passwordPolicyId", model.getPasswordPolicyId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "userId", model.getUserId());
		JSONUtil.put(jsonObj, "userName", model.getUserName());
		JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
		JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
		JSONUtil.put(jsonObj, "defaultPolicy", model.getDefaultPolicy());
		JSONUtil.put(jsonObj, "name", model.getName());
		JSONUtil.put(jsonObj, "description", model.getDescription());
		JSONUtil.put(jsonObj, "changeable", model.getChangeable());
		JSONUtil.put(jsonObj, "changeRequired", model.getChangeRequired());
		JSONUtil.put(jsonObj, "minAge", model.getMinAge());
		JSONUtil.put(jsonObj, "checkSyntax", model.getCheckSyntax());
		JSONUtil.put(jsonObj, "allowDictionaryWords",
			model.getAllowDictionaryWords());
		JSONUtil.put(jsonObj, "minLength", model.getMinLength());
		JSONUtil.put(jsonObj, "history", model.getHistory());
		JSONUtil.put(jsonObj, "historyCount", model.getHistoryCount());
		JSONUtil.put(jsonObj, "expireable", model.getExpireable());
		JSONUtil.put(jsonObj, "maxAge", model.getMaxAge());
		JSONUtil.put(jsonObj, "warningTime", model.getWarningTime());
		JSONUtil.put(jsonObj, "graceLimit", model.getGraceLimit());
		JSONUtil.put(jsonObj, "lockout", model.getLockout());
		JSONUtil.put(jsonObj, "maxFailure", model.getMaxFailure());
		JSONUtil.put(jsonObj, "lockoutDuration", model.getLockoutDuration());
		JSONUtil.put(jsonObj, "requireUnlock", model.getRequireUnlock());
		JSONUtil.put(jsonObj, "resetFailureCount", model.getResetFailureCount());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			PasswordPolicy model = (PasswordPolicy)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}