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

import com.liferay.portal.model.Contact;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="ContactJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.ContactServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.ContactServiceJSON
 *
 */
public class ContactJSONSerializer {
	public static JSONObject toJSONObject(Contact model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "contactId", model.getContactId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "userId", model.getUserId());
		JSONUtil.put(jsonObj, "userName", model.getUserName());
		JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
		JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
		JSONUtil.put(jsonObj, "accountId", model.getAccountId());
		JSONUtil.put(jsonObj, "parentContactId", model.getParentContactId());
		JSONUtil.put(jsonObj, "firstName", model.getFirstName());
		JSONUtil.put(jsonObj, "middleName", model.getMiddleName());
		JSONUtil.put(jsonObj, "lastName", model.getLastName());
		JSONUtil.put(jsonObj, "prefixId", model.getPrefixId());
		JSONUtil.put(jsonObj, "suffixId", model.getSuffixId());
		JSONUtil.put(jsonObj, "male", model.getMale());
		JSONUtil.put(jsonObj, "birthday", model.getBirthday());
		JSONUtil.put(jsonObj, "smsSn", model.getSmsSn());
		JSONUtil.put(jsonObj, "aimSn", model.getAimSn());
		JSONUtil.put(jsonObj, "icqSn", model.getIcqSn());
		JSONUtil.put(jsonObj, "jabberSn", model.getJabberSn());
		JSONUtil.put(jsonObj, "msnSn", model.getMsnSn());
		JSONUtil.put(jsonObj, "skypeSn", model.getSkypeSn());
		JSONUtil.put(jsonObj, "ymSn", model.getYmSn());
		JSONUtil.put(jsonObj, "employeeStatusId", model.getEmployeeStatusId());
		JSONUtil.put(jsonObj, "employeeNumber", model.getEmployeeNumber());
		JSONUtil.put(jsonObj, "jobTitle", model.getJobTitle());
		JSONUtil.put(jsonObj, "jobClass", model.getJobClass());
		JSONUtil.put(jsonObj, "hoursOfOperation", model.getHoursOfOperation());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			Contact model = (Contact)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}