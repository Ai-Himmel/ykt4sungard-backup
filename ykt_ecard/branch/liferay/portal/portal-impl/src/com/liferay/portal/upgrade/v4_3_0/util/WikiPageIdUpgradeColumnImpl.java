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
import com.liferay.portlet.wiki.service.WikiPageResourceLocalServiceUtil;

/**
 * <a href="WikiPageIdUpgradeColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageIdUpgradeColumnImpl extends PKUpgradeColumnImpl {

	public WikiPageIdUpgradeColumnImpl(
		UpgradeColumn nodeIdColumn, UpgradeColumn titleColumn) {

		super("pageId", false);

		_nodeIdColumn = nodeIdColumn;
		_titleColumn = titleColumn;
		_wikiPageIdMapper = ValueMapperFactory.getValueMapper();
	}

	public Object getNewValue(Object oldValue) throws Exception {
		_resourcePrimKey = null;

		Object newValue = super.getNewValue(oldValue);

		Long oldNodeId = (Long)_nodeIdColumn.getOldValue();
		Long newNodeId = (Long)_nodeIdColumn.getNewValue();
		String title = (String)_titleColumn.getOldValue();

		String oldPageIdValue =
			"{nodeId=" + oldNodeId + ", title=" + title + ", version=1.0}";

		_resourcePrimKey = new Long(WikiPageResourceLocalServiceUtil.
			getPageResourcePrimKey(newNodeId.longValue(), title));

		_wikiPageIdMapper.mapValue(oldPageIdValue, _resourcePrimKey);

		return newValue;
	}

	public ValueMapper getValueMapper() {
		return _wikiPageIdMapper;
	}

	public Long getResourcePrimKey() {
		return _resourcePrimKey;
	}

	private UpgradeColumn _nodeIdColumn;
	private UpgradeColumn _titleColumn;
	private ValueMapper _wikiPageIdMapper;
	private Long _resourcePrimKey;

}