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

import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.upgrade.StagnantRowException;
import com.liferay.portal.upgrade.util.PKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.util.ValueMapperFactory;

/**
 * <a href="LayoutPlidUpgradeColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutPlidUpgradeColumnImpl extends PKUpgradeColumnImpl {

	public LayoutPlidUpgradeColumnImpl(
		UpgradeColumn upgradeLayoutOwnerIdColumn,
		LayoutOwnerIdUpgradeColumnImpl groupIdColumn,
		LayoutOwnerIdUpgradeColumnImpl privateLayoutColumn,
		UpgradeColumn layoutIdColumn) {

		super("plid", false);

		_upgradeLayoutOwnerIdColumn = upgradeLayoutOwnerIdColumn;
		_groupIdColumn = groupIdColumn;
		_privateLayoutColumn = privateLayoutColumn;
		_layoutIdColumn = layoutIdColumn;
		_layoutPlidMapper = ValueMapperFactory.getValueMapper();
	}

	public Object getNewValue(Object oldValue) throws Exception {
		Object newValue = super.getNewValue(oldValue);

		Long groupId = _groupIdColumn.getGroupId();
		Boolean privateLayout = _privateLayoutColumn.isPrivateLayout();
		Long layoutId = (Long)_layoutIdColumn.getOldValue();

		if ((groupId == null) || (privateLayout == null) ||
			(Validator.isNull(layoutId))) {

			throw new StagnantRowException(
				"{groupId=" + groupId + ",privateLayout=" + privateLayout +
					",layoutId=" + layoutId + "}");
		}

		String oldOwnerId = (String)_upgradeLayoutOwnerIdColumn.getOldValue();

		String oldPlidValue =
			"{layoutId=" + layoutId + ", ownerId=" + oldOwnerId + "}";

		_layoutPlidMapper.mapValue(oldPlidValue, newValue);

		return newValue;
	}

	public ValueMapper getValueMapper() {
		return _layoutPlidMapper;
	}

	private UpgradeColumn _upgradeLayoutOwnerIdColumn;
	private LayoutOwnerIdUpgradeColumnImpl _groupIdColumn;
	private LayoutOwnerIdUpgradeColumnImpl _privateLayoutColumn;
	private UpgradeColumn _layoutIdColumn;
	private ValueMapper _layoutPlidMapper;

}