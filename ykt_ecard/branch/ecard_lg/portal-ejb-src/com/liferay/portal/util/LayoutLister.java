/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="LayoutLister.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class LayoutLister {

	public LayoutView getLayoutView(String userId)
		throws PortalException, SystemException {

		_userId = userId;
		_nodeId = 1;

		_layoutList = new ArrayList();
		_layoutList.add("1|0|0|-1|Root|0");

		_createLayoutList(Layout.DEFAULT_PARENT_LAYOUT_ID, 1, 0);

		return new LayoutView(_layoutList, _depth);
	}

	private void _createLayoutList(
			String parentLayoutId, int parentId, int depth)
		throws PortalException, SystemException {

		List layouts = UserLocalServiceUtil.getLayouts(_userId, parentLayoutId);

		for (int i = 0; i < layouts.size(); i++) {
			Layout layout = (Layout)layouts.get(i);

			if (i == 0) {
				depth++;

				if (depth > _depth) {
					_depth = depth;
				}
			}

			FastStringBuffer sb = new FastStringBuffer();

			sb.append(++_nodeId).append("|");
			sb.append(parentId).append("|");

			if ((i + 1) == layouts.size()) {
				sb.append("1");
			}
			else {
				sb.append("0");
			}

			sb.append("|");
			sb.append(layout.getLayoutId()).append("|");
			sb.append(layout.getName()).append("|");

			if (layout.getType().equals(Layout.TYPE_PORTLET)) {
				//sb.append("9");
				sb.append("11");

				_layoutList.add(sb.toString());

				_createLayoutList(layout.getLayoutId(), _nodeId, depth);
			}
			else {
				sb.append("11");

				_layoutList.add(sb.toString());
			}
		}
	}

	private String _userId;
	private int _nodeId;
	private List _layoutList;
	private int _depth;

}