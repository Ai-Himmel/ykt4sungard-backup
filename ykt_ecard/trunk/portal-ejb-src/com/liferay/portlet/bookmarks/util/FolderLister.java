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

package com.liferay.portlet.bookmarks.util;

import com.liferay.portal.SystemException;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderLocalServiceUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="FolderLister.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class FolderLister {

	public FolderView getFolderView(String groupId, String userId)
		throws SystemException {

		_groupId = groupId;
		_userId = userId;
		_nodeId = 1;

		_entryList = new ArrayList();
		_entryList.add("1|0|0||Root|0");

		_createEntryList(BookmarksFolder.DEFAULT_PARENT_FOLDER_ID, 1);

		return new FolderView(_entryList);
	}

	private void _createEntryList(String parentFolderId, int parentId)
		throws SystemException {

		List folders = BookmarksFolderLocalServiceUtil.getFolders(
			_groupId, _userId, parentFolderId);

		List entries = BookmarksEntryLocalServiceUtil.getEntries(
			_groupId, _userId, parentFolderId);

		Iterator itr = folders.iterator();

		while (itr.hasNext()) {
			BookmarksFolder folder = (BookmarksFolder)itr.next();

			FastStringBuffer sb = new FastStringBuffer();

			sb.append(++_nodeId).append("|");
			sb.append(parentId).append("|");

			if (entries.size() == 0 && !itr.hasNext()) {
				sb.append("1");
			}
			else {
				sb.append("0");
			}

			sb.append("|");
			sb.append(folder.getFolderId()).append("|");
			sb.append(folder.getName()).append("|");
			sb.append("9");

			_entryList.add(sb.toString());

			_createEntryList(folder.getFolderId(), _nodeId);
		}

		itr = entries.iterator();

		while (itr.hasNext()) {
			BookmarksEntry entry = (BookmarksEntry)itr.next();

			FastStringBuffer sb = new FastStringBuffer();

			sb.append(++_nodeId).append("|");
			sb.append(parentId).append("|");

			if (!itr.hasNext()) {
				sb.append("1");
			}
			else {
				sb.append("0");
			}

			sb.append("|");
			sb.append(entry.getEntryId()).append("|");
			sb.append(entry.getName()).append("|");
			sb.append("11");

			_entryList.add(sb.toString());
		}
	}

	private String _groupId;
	private String _userId;
	private int _nodeId;
	private List _entryList;

}