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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.upgrade.StagnantRowException;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.ValueMapper;

/**
 * <a href="LayoutOwnerIdUpgradeColumnImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutOwnerIdUpgradeColumnImpl extends BaseUpgradeColumnImpl {

	public LayoutOwnerIdUpgradeColumnImpl(
		String name, UpgradeColumn upgradeColumn, ValueMapper groupIdMapper) {

		super(name);

		_name = name;
		_upgradeColumn = upgradeColumn;
		_groupIdMapper = groupIdMapper;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		_groupId = null;
		_privateLayout = null;

		String ownerId = (String)_upgradeColumn.getOldValue();

		if (_name.equals("groupId")) {
			if (ownerId.startsWith("PUB.") || ownerId.startsWith("PRI.")) {
				Long groupId = new Long(GetterUtil.getLong(
					ownerId.substring(4, ownerId.length())));

				_groupId = (Long)_groupIdMapper.getNewValue(groupId);

				return _groupId;
			}
			else {
				throw new StagnantRowException(ownerId);
			}
		}
		else {
			if (ownerId.startsWith("PUB.")) {
				_privateLayout = Boolean.FALSE;

				return _privateLayout;
			}
			else if (ownerId.startsWith("PRI.")) {
				_privateLayout = Boolean.TRUE;

				return _privateLayout;
			}
			else {
				throw new StagnantRowException(ownerId);
			}
		}
	}

	public Long getGroupId() {
		return _groupId;
	}

	public Boolean isPrivateLayout() {
		return _privateLayout;
	}

	private String _name;
	private UpgradeColumn _upgradeColumn;
	private ValueMapper _groupIdMapper;
	private Long _groupId;
	private Boolean _privateLayout;

}