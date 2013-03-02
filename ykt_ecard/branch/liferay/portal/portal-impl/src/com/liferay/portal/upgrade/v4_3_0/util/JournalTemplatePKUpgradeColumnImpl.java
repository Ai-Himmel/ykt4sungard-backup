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

import com.liferay.portal.upgrade.util.PKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.util.ValueMapperFactory;

import java.sql.Types;

/**
 * <a href="JournalTemplatePKUpgradeColumnImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalTemplatePKUpgradeColumnImpl extends PKUpgradeColumnImpl {

	public JournalTemplatePKUpgradeColumnImpl(
		UpgradeColumn companyIdColumn, UpgradeColumn groupIdColumn) {

		super("id_", new Integer(Types.VARCHAR), false);

		_companyIdColumn = companyIdColumn;
		_groupIdColumn = groupIdColumn;
		_journalTemplateIdMapper = ValueMapperFactory.getValueMapper();
	}

	public Object getNewValue(Object oldValue) throws Exception {
		Object newValue = super.getNewValue(oldValue);

		String companyId = (String)_companyIdColumn.getOldValue();
		Long groupId = (Long)_groupIdColumn.getOldValue();
		String templateId = (String)oldValue;

		String oldIdValue =
			"{companyId=" + companyId + ", groupId=" + groupId +
				", templateId=" + templateId + "}";

		_journalTemplateIdMapper.mapValue(oldIdValue, newValue);

		return newValue;
	}

	public ValueMapper getValueMapper() {
		return _journalTemplateIdMapper;
	}

	private UpgradeColumn _companyIdColumn;
	private UpgradeColumn _groupIdColumn;
	private ValueMapper _journalTemplateIdMapper;

}