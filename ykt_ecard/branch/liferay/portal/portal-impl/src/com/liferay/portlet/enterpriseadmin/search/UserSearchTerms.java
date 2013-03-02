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

package com.liferay.portlet.enterpriseadmin.search;

import com.liferay.portal.kernel.dao.DAOParamUtil;
import com.liferay.portal.kernel.util.ParamUtil;

import javax.portlet.RenderRequest;

/**
 * <a href="UserSearchTerms.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserSearchTerms extends UserDisplayTerms {

	public UserSearchTerms(RenderRequest req) {
		super(req);

		firstName = DAOParamUtil.getLike(req, FIRST_NAME);
		middleName = DAOParamUtil.getLike(req, MIDDLE_NAME);
		lastName = DAOParamUtil.getLike(req, LAST_NAME);
		screenName = DAOParamUtil.getLike(req, SCREEN_NAME);
		emailAddress = DAOParamUtil.getLike(req, EMAIL_ADDRESS);
		active = ParamUtil.getBoolean(req, ACTIVE, true);
		organizationId = ParamUtil.getLong(req, ORGANIZATION_ID);
		roleId = ParamUtil.getLong(req, ROLE_ID);
		userGroupId = ParamUtil.getLong(req, USER_GROUP_ID);
	}

	public Boolean getActiveObj() {
		return Boolean.valueOf(active);
	}

}