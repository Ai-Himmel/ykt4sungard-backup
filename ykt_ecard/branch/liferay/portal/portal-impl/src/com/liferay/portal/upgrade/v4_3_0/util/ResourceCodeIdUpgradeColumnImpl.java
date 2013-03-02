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

import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.service.ResourceCodeLocalServiceUtil;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;

/**
 * <a href="ResourceCodeIdUpgradeColumnImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Alexander Chow
 * @author Brian Wing Shun Chan
 *
 */
public class ResourceCodeIdUpgradeColumnImpl extends BaseUpgradeColumnImpl {

	public ResourceCodeIdUpgradeColumnImpl(
		UpgradeColumn companyIdColumn, UpgradeColumn nameColumn,
		UpgradeColumn scopeColumn) {

		super("codeId");

		_companyIdColumn = companyIdColumn;
		_nameColumn = nameColumn;
		_scopeColumn = scopeColumn;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		_scope = 0;

		Long companyId = (Long)_companyIdColumn.getOldValue();
		String name = (String)_nameColumn.getOldValue();
		String scope = (String)_scopeColumn.getOldValue();

		if (scope.equals("company")) {
			_scope = ResourceImpl.SCOPE_COMPANY;
		}
		else if (scope.equals("group")) {
			_scope = ResourceImpl.SCOPE_GROUP;
		}
		else if (scope.equals("groupTemplate")) {
			_scope = ResourceImpl.SCOPE_GROUP_TEMPLATE;
		}
		else if (scope.equals("individual")) {
			_scope = ResourceImpl.SCOPE_INDIVIDUAL;
		}
		else {
			throw new UpgradeException("Scope " + _scope + " is invalid");
		}

		ResourceCode resourceCode =
			ResourceCodeLocalServiceUtil.getResourceCode(
				companyId.longValue(), name, _scope);

		return new Long(resourceCode.getCodeId());
	}

	public int getScope() {
		return _scope;
	}

	private UpgradeColumn _companyIdColumn;
	private UpgradeColumn _nameColumn;
	private UpgradeColumn _scopeColumn;
	private int _scope;

}