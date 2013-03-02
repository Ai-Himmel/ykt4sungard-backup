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

import com.liferay.portal.kernel.dao.search.RowChecker;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.service.PermissionLocalServiceUtil;

import javax.portlet.RenderResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="GroupPermissionChecker.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupPermissionChecker extends RowChecker {

	public GroupPermissionChecker(RenderResponse res, Role role,
								  String resourceName, String actionId) {

		super(res);

		_role = role;
		_resourceName = resourceName;
		_actionId = actionId;
	}

	public boolean isChecked(Object obj) {
		Group group = (Group)obj;

		try {
			return PermissionLocalServiceUtil.hasRolePermission(
				_role.getRoleId(), group.getCompanyId(), _resourceName,
				ResourceImpl.SCOPE_GROUP, String.valueOf(group.getGroupId()),
				_actionId);
		}
		catch (Exception e){
			_log.error(e);

			return false;
		}
	}

	private static Log _log = LogFactory.getLog(GroupPermissionChecker.class);

	private Role _role;
	private String _resourceName;
	private String _actionId;

}