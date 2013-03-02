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

package com.liferay.portlet.documentlibrary.action;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.JSONAction;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.http.DLFolderJSONSerializer;
import com.liferay.util.JSONUtil;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="GetFoldersAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Edward Shin
 *
 */
public class GetFoldersAction extends JSONAction {

	public String getJSON(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		long groupId = ParamUtil.getLong(req, "groupId");
		long parentFolderId = ParamUtil.getLong(req, "folderId");

		List folders = DLFolderLocalServiceUtil.getFolders(
			groupId, parentFolderId);

		JSONArray jsonArray = toJSONArray(folders);

		return jsonArray.toString();
	}

	protected JSONArray toJSONArray(List folders)
		throws PortalException, SystemException {

		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < folders.size(); i++) {
			DLFolder folder = (DLFolder)folders.get(i);

			jsonArray.put(toJSONObject(folder));
		}

		return jsonArray;
	}

	protected JSONObject toJSONObject(DLFolder folder)
		throws PortalException, SystemException {

		JSONObject jsonObj = DLFolderJSONSerializer.toJSONObject(folder);

		List subfolderIds = new ArrayList();

		subfolderIds.add(new Long(folder.getFolderId()));

		DLFolderLocalServiceUtil.getSubfolderIds(
			subfolderIds, folder.getGroupId(), folder.getFolderId());

		int subFoldersCount = subfolderIds.size() - 1;
		int fileEntriesCount =
			DLFileEntryLocalServiceUtil.getFileEntriesAndShortcutsCount(
				subfolderIds);

		JSONUtil.put(jsonObj, "subFoldersCount", subFoldersCount);
		JSONUtil.put(jsonObj, "fileEntriesCount", fileEntriesCount);

		return jsonObj;
	}

}