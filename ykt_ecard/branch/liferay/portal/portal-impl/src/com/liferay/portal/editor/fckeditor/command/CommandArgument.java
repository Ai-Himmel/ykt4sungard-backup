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

package com.liferay.portal.editor.fckeditor.command;

import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;

import java.util.StringTokenizer;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="CommandArgument.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public class CommandArgument {

	public CommandArgument(
		String command, String type, String currentFolder, String newFolder,
		ThemeDisplay themeDisplay, HttpServletRequest req) {

		_command = command;
		_type = type;
		_currentFolder = currentFolder;
		_newFolder = newFolder;
		_themeDisplay = themeDisplay;
		_req = req;
	}

	public String getCommand() {
		return _command;
	}

	public String getType() {
		return _type;
	}

	public String getCurrentFolder() {
		return _currentFolder;
	}

	public String getNewFolder() {
		return _newFolder;
	}

	public ThemeDisplay getThemeDisplay() {
		return _themeDisplay;
	}

	public HttpServletRequest getHttpServletRequest() {
		return _req;
	}

	public long getCompanyId() {
		return _themeDisplay.getCompanyId();
	}

	public Group getCurrentGroup() throws Exception {
		String currentGroupName = getCurrentGroupName();

		int pos = currentGroupName.indexOf(" - ");

		if (pos > 0) {
			long groupId = GetterUtil.getLong(
				currentGroupName.substring(0, pos));

			Group group = GroupLocalServiceUtil.getGroup(groupId);

			if (group.getCompanyId() == getCompanyId()) {
				return group;
			}
		}

		throw new NoSuchGroupException();
	}

	public String getCurrentGroupName() {
		if (_currentFolder.equals("/")) {
			return StringPool.BLANK;
		}
		else {
			StringTokenizer st = new StringTokenizer(_currentFolder, "/");

			return st.nextToken();
		}
	}

	public long getUserId() {
		return _themeDisplay.getUserId();
	}

	public long getPlid() throws Exception {
		long plid = _themeDisplay.getPlid();

		Layout layout = LayoutLocalServiceUtil.getLayout(plid);

		Group group = getCurrentGroup();

		if (layout.getGroupId() != group.getGroupId()) {
			plid = LayoutLocalServiceUtil.getDefaultPlid(group.getGroupId());
		}

		return plid;
	}

	private String _command;
	private String _type;
	private String _currentFolder;
	private String _newFolder;
	private ThemeDisplay _themeDisplay;
	private HttpServletRequest _req;

}