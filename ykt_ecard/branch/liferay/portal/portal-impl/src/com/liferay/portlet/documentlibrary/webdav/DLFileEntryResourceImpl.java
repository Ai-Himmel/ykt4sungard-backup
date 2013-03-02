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

package com.liferay.portlet.documentlibrary.webdav;

import com.liferay.portal.util.ContentTypeUtil;
import com.liferay.portal.webdav.BaseResourceImpl;
import com.liferay.portal.webdav.WebDAVException;
import com.liferay.portal.webdav.WebDAVRequest;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;

import java.io.InputStream;

/**
 * <a href="DLFileEntryResourceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileEntryResourceImpl extends BaseResourceImpl {

	public DLFileEntryResourceImpl(
		WebDAVRequest webDavReq, DLFileEntry fileEntry, String parentPath,
		String name) {

		super(
			parentPath, name, fileEntry.getTitleWithExtension(),
			fileEntry.getCreateDate(), fileEntry.getModifiedDate(),
			fileEntry.getSize());

		setModel(fileEntry);
		setClassName(DLFileEntry.class.getName());
		setPrimaryKey(fileEntry.getPrimaryKey());

		_webDavReq = webDavReq;
		_fileEntry = fileEntry;
	}

	public boolean isCollection() {
		return false;
	}

	public String getContentType() {
		return ContentTypeUtil.getContentType(_fileEntry.getName());
	}

	public InputStream getContentAsStream() throws WebDAVException {
		try {
			return DLFileEntryLocalServiceUtil.getFileAsStream(
				_webDavReq.getCompanyId(), _webDavReq.getUserId(),
				_fileEntry.getFolderId(), _fileEntry.getName());
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	private WebDAVRequest _webDavReq;
	private DLFileEntry _fileEntry;

}