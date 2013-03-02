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

import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.webdav.BaseResourceImpl;
import com.liferay.portal.webdav.BaseWebDAVStorageImpl;
import com.liferay.portal.webdav.Resource;
import com.liferay.portal.webdav.Status;
import com.liferay.portal.webdav.WebDAVException;
import com.liferay.portal.webdav.WebDAVRequest;
import com.liferay.portal.webdav.WebDAVUtil;
import com.liferay.portlet.documentlibrary.DuplicateFolderNameException;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFileEntryServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderServiceUtil;
import com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission;
import com.liferay.portlet.documentlibrary.service.permission.DLFolderPermission;
import com.liferay.util.FileUtil;
import com.liferay.util.PwdGenerator;
import com.liferay.util.SystemProperties;
import com.liferay.util.Time;

import java.io.File;
import java.io.InputStream;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="DLWebDAVStorageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class DLWebDAVStorageImpl extends BaseWebDAVStorageImpl {

	public Status addCollection(WebDAVRequest webDavReq)
		throws WebDAVException {

		try {
			HttpServletRequest req = webDavReq.getHttpServletRequest();

			if (req.getContentLength() > 0) {
				return new Status(
					HttpServletResponse.SC_UNSUPPORTED_MEDIA_TYPE);
			}

			String[] pathArray = webDavReq.getPathArray();
			long parentFolderId = getParentFolderId(pathArray);
			String name = WebDAVUtil.getEntryName(pathArray);

			try {
				DLFileEntryLocalServiceUtil.getFileEntryByTitle(
					parentFolderId, name);

				return new Status(HttpServletResponse.SC_CONFLICT);
			}
			catch (Exception e) {
			}

			long plid = getPlid(webDavReq.getGroupId());
			String description = StringPool.BLANK;
			boolean addCommunityPermissions = true;
			boolean addGuestPermissions = true;

			DLFolderServiceUtil.addFolder(
				plid, parentFolderId, name, description,
				addCommunityPermissions, addGuestPermissions);

			String location = StringUtil.merge(pathArray, StringPool.SLASH);

			return new Status(location, HttpServletResponse.SC_CREATED);
		}
		catch (DuplicateFolderNameException dfne) {
			return new Status(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
		}
		catch (NoSuchFolderException nsfe) {
			return new Status(HttpServletResponse.SC_CONFLICT);
		}
		catch (PrincipalException pe) {
			return new Status(HttpServletResponse.SC_FORBIDDEN);
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public int copyCollectionResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite, long depth)
		throws WebDAVException {

		try {
			String[] destinationArray = WebDAVUtil.getPathArray(
				destination, true);

			long parentFolderId = DLFolderImpl.DEFAULT_PARENT_FOLDER_ID;

			try {
				parentFolderId = getParentFolderId(destinationArray);
			}
			catch (NoSuchFolderException nsfe) {
				return HttpServletResponse.SC_CONFLICT;
			}

			DLFolder folder = (DLFolder)resource.getModel();

			long groupId = WebDAVUtil.getGroupId(destination);
			long plid = getPlid(groupId);
			String name = WebDAVUtil.getEntryName(destinationArray);
			String description = folder.getDescription();
			boolean addCommunityPermissions = true;
			boolean addGuestPermissions = true;

			int status = HttpServletResponse.SC_CREATED;

			if (overwrite) {
				try {
					DLFolder destFolder = DLFolderServiceUtil.getFolder(
						groupId, parentFolderId, name);

					DLFolderServiceUtil.deleteFolder(destFolder.getFolderId());

					status = HttpServletResponse.SC_NO_CONTENT;
				}
				catch (NoSuchFolderException nsfe) {
					try {
						DLFileEntryServiceUtil.deleteFileEntryByTitle(
							parentFolderId, name);

						status = HttpServletResponse.SC_NO_CONTENT;
					}
					catch (NoSuchFileEntryException nsfee) {
					}
				}
			}

			if (depth == 0) {
				DLFolderServiceUtil.addFolder(
					plid, parentFolderId, name, description,
					addCommunityPermissions, addGuestPermissions);
			}
			else {
				DLFolderServiceUtil.copyFolder(
					plid, folder.getFolderId(), parentFolderId, name,
					description, addCommunityPermissions, addGuestPermissions);
			}

			return status;
		}
		catch (DuplicateFolderNameException dfne) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (PrincipalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public int copySimpleResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException {

		File file = null;

		try {
			String[] destinationArray = WebDAVUtil.getPathArray(
				destination, true);

			long parentFolderId;

			try {
				parentFolderId = getParentFolderId(destinationArray);
			}
			catch (NoSuchFolderException nsfe) {
				return HttpServletResponse.SC_CONFLICT;
			}

			DLFileEntry fileEntry = (DLFileEntry)resource.getModel();

			DLFileEntryPermission.check(
				webDavReq.getPermissionChecker(), fileEntry,
				ActionKeys.VIEW);

			long userId = webDavReq.getUserId();
			String name = StringPool.BLANK;
			String sourceName = fileEntry.getName();
			String title = WebDAVUtil.getEntryName(destinationArray);
			String description = fileEntry.getDescription();
			String[] tagsEntries = new String[0];
			String extraSettings = fileEntry.getExtraSettings();
			boolean addCommunityPermissions = true;
			boolean addGuestPermissions = true;

			String fileName =
				SystemProperties.get(SystemProperties.TMP_DIR) +
					StringPool.SLASH + Time.getTimestamp() +
						PwdGenerator.getPassword(PwdGenerator.KEY2, 8);

			file = new File(fileName);

			InputStream is = DLFileEntryLocalServiceUtil.getFileAsStream(
				fileEntry.getCompanyId(), userId, fileEntry.getFolderId(),
				fileEntry.getName());

			FileUtil.write(file, is);

			if (_log.isDebugEnabled()) {
				_log.debug("Writing request to file " + fileName);
			}

			DLFolderPermission.check(
				webDavReq.getPermissionChecker(), parentFolderId,
				ActionKeys.ADD_DOCUMENT);

			int status = HttpServletResponse.SC_CREATED;

			if (overwrite) {
				try {
					long groupId = webDavReq.getGroupId();

					DLFolderServiceUtil.deleteFolder(
						groupId, parentFolderId, title);

					DLFileEntryLocalServiceUtil.addFileEntry(
						userId, parentFolderId, name, title,
						description, tagsEntries, extraSettings, file,
						addCommunityPermissions, addGuestPermissions);

					status = HttpServletResponse.SC_NO_CONTENT;
				}
				catch (NoSuchFolderException nsfe) {
					DLFileEntry destFile =
						DLFileEntryLocalServiceUtil.addOrOverwriteFileEntry(
							userId, parentFolderId, name, sourceName, title,
							description, tagsEntries, extraSettings, file,
							addCommunityPermissions, addGuestPermissions);

					if (destFile.getVersion() > 1.0) {
						status = HttpServletResponse.SC_NO_CONTENT;
					}
					else {
						status = HttpServletResponse.SC_CREATED;
					}
				}
			}
			else {
				DLFileEntryLocalServiceUtil.addFileEntry(
					userId, parentFolderId, name, title,
					description, tagsEntries, extraSettings, file,
					addCommunityPermissions, addGuestPermissions);

				status = HttpServletResponse.SC_CREATED;
			}

			return status;
		}
		catch (DuplicateFolderNameException dfne) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (DuplicateFileException dfe) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (PrincipalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
		finally {
			if (file != null) {
				file.delete();
			}
		}
	}

	public int deleteResource(WebDAVRequest webDavReq) throws WebDAVException {
		try {
			Resource resource = getResource(webDavReq);

			if (resource == null) {
				return HttpServletResponse.SC_NOT_FOUND;
			}

			Object model = resource.getModel();

			if (model instanceof DLFolder) {
				DLFolder folder = (DLFolder)model;

				DLFolderServiceUtil.deleteFolder(folder.getFolderId());
			}
			else {
				DLFileEntry fileEntry = (DLFileEntry)model;

				DLFileEntryServiceUtil.deleteFileEntry(
					fileEntry.getFolderId(), fileEntry.getName());
			}

			return HttpServletResponse.SC_NO_CONTENT;
		}
		catch (PrincipalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public Resource getResource(WebDAVRequest webDavReq)
		throws WebDAVException {

		try {
			String[] pathArray = webDavReq.getPathArray();

			long parentFolderId = getParentFolderId(pathArray);
			String name = WebDAVUtil.getEntryName(pathArray);

			try {
				DLFolder folder = DLFolderServiceUtil.getFolder(
					webDavReq.getGroupId(), parentFolderId, name);

				if ((folder.getParentFolderId() != parentFolderId) ||
					(webDavReq.getGroupId() != folder.getGroupId())) {

					throw new NoSuchFolderException();
				}

				return toResource(webDavReq, folder, false);
			}
			catch (NoSuchFolderException nsfe) {
				try {
					String titleWithExtension = name;

					DLFileEntry fileEntry =
						DLFileEntryLocalServiceUtil.getFileEntryByTitle(
							parentFolderId, titleWithExtension);

					DLFileEntryPermission.check(
						webDavReq.getPermissionChecker(), fileEntry,
						ActionKeys.VIEW);

					return toResource(webDavReq, fileEntry, false);
				}
				catch (NoSuchFileEntryException nsfee) {
					return null;
				}
			}
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public List getResources(WebDAVRequest webDavReq)
		throws WebDAVException {

		try {
			long folderId = getFolderId(webDavReq.getPathArray());

			List folders = getFolders(webDavReq, folderId);
			List fileEntries = getFileEntries(webDavReq, folderId);

			List resources = new ArrayList(folders.size() + fileEntries.size());

			resources.addAll(folders);
			resources.addAll(fileEntries);

			return resources;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public int moveCollectionResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException {

		try {
			String[] destinationArray = WebDAVUtil.getPathArray(
				destination, true);

			DLFolder folder = (DLFolder)resource.getModel();

			long groupId = webDavReq.getGroupId();
			long folderId = folder.getFolderId();
			long parentFolderId = getParentFolderId(destinationArray);
			String name = WebDAVUtil.getEntryName(destinationArray);
			String description = folder.getDescription();

			if (parentFolderId != folder.getParentFolderId()) {
				name = folder.getName();
			}

			int status = HttpServletResponse.SC_CREATED;

			if (overwrite) {
				try {
					DLFolder destFolder = DLFolderServiceUtil.getFolder(
						groupId, parentFolderId, name);

					DLFolderServiceUtil.deleteFolder(
						destFolder.getFolderId());

					status = HttpServletResponse.SC_NO_CONTENT;
				}
				catch (NoSuchFolderException nsfe) {
					try {
						DLFileEntryServiceUtil.deleteFileEntryByTitle(
							parentFolderId, name);

						status = HttpServletResponse.SC_NO_CONTENT;
					}
					catch (NoSuchFileEntryException nsfee) {
					}
				}
			}

			DLFolderServiceUtil.updateFolder(
				folderId, parentFolderId, name, description);

			return status;
		}
		catch (PrincipalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (DuplicateFileException dfe) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (DuplicateFolderNameException dfne) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public int moveSimpleResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException {

		try {
			String[] destinationArray = WebDAVUtil.getPathArray(
				destination, true);

			DLFileEntry fileEntry = (DLFileEntry)resource.getModel();

			long folderId = fileEntry.getFolderId();
			long newFolderId = getParentFolderId(destinationArray);
			String name = fileEntry.getName();
			String sourceFileName = null;
			String title = WebDAVUtil.getEntryName(destinationArray);
			String description = fileEntry.getDescription();
			String[] tagsEntries = new String[0];
			String extraSettings = fileEntry.getExtraSettings();
			byte[] byteArray = null;

			if (newFolderId != folderId) {
				title = fileEntry.getTitle();
			}

			int status = HttpServletResponse.SC_CREATED;

			if (overwrite) {
				try {
					DLFileEntry destFile =
						DLFileEntryServiceUtil.getFileEntryByTitle(
							folderId, title);

					DLFileEntryServiceUtil.deleteFileEntry(
						destFile.getFolderId(), destFile.getName());

					status = HttpServletResponse.SC_NO_CONTENT;
				}
				catch (NoSuchFileEntryException nsfee) {
					try {
						long groupId = webDavReq.getGroupId();

						DLFolderServiceUtil.deleteFolder(
							groupId, folderId, title);

						status = HttpServletResponse.SC_NO_CONTENT;
					}
					catch (NoSuchFolderException nsfe) {
					}
				}
			}

			DLFileEntryServiceUtil.updateFileEntry(
				folderId, newFolderId, name, sourceFileName, title,
				description, tagsEntries, extraSettings, byteArray);

			return status;
		}
		catch (PrincipalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (DuplicateFileException dfe) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (DuplicateFolderNameException dfne) {
			return HttpServletResponse.SC_PRECONDITION_FAILED;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public int putResource(WebDAVRequest webDavReq) throws WebDAVException {
		File file = null;

		try {
			HttpServletRequest req = webDavReq.getHttpServletRequest();
			String[] pathArray = webDavReq.getPathArray();
			long userId = webDavReq.getUserId();

			long parentFolderId = getParentFolderId(pathArray);
			String name = WebDAVUtil.getEntryName(pathArray);
			String title = WebDAVUtil.getEntryName(pathArray);
			String description = StringPool.BLANK;
			String[] tagsEntries = new String[0];
			String extraSettings = StringPool.BLANK;
			boolean addCommunityPermissions = true;
			boolean addGuestPermissions = true;

			String fileName =
				SystemProperties.get(SystemProperties.TMP_DIR) +
					StringPool.SLASH + Time.getTimestamp() +
						PwdGenerator.getPassword(PwdGenerator.KEY2, 8);

			file = new File(fileName);

			FileUtil.write(file, req.getInputStream());

			if (_log.isDebugEnabled()) {
				_log.debug("Writing request to file " + fileName);
			}

			DLFolderPermission.check(
				webDavReq.getPermissionChecker(), parentFolderId,
				ActionKeys.ADD_DOCUMENT);

			DLFileEntryLocalServiceUtil.addFileEntry(
				userId, parentFolderId, name, title, description, tagsEntries,
				extraSettings, file, addCommunityPermissions,
				addGuestPermissions);

			return HttpServletResponse.SC_CREATED;
		}
		catch (PrincipalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (PortalException pe) {
			if (_log.isWarnEnabled()) {
				_log.warn(pe, pe);
			}

			return HttpServletResponse.SC_CONFLICT;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
		finally {
			if (file != null) {
				file.delete();
			}
		}
	}

	protected List getFileEntries(WebDAVRequest webDavReq, long parentFolderId)
		throws Exception {

		List fileEntries = new ArrayList();

		long plid = getPlid(webDavReq.getGroupId());

		DLFolderPermission.check(
			webDavReq.getPermissionChecker(), plid, parentFolderId,
			ActionKeys.VIEW);

		Iterator itr = DLFileEntryLocalServiceUtil.getFileEntries(
			parentFolderId).iterator();

		while (itr.hasNext()) {
			DLFileEntry fileEntry = (DLFileEntry)itr.next();

			if (DLFileEntryPermission.contains(
					webDavReq.getPermissionChecker(), fileEntry,
					ActionKeys.VIEW)) {

				Resource resource = toResource(webDavReq, fileEntry, true);

				fileEntries.add(resource);
			}
		}

		return fileEntries;
	}

	protected long getFolderId(String[] pathArray) throws Exception {
		return getFolderId(pathArray, false);
	}

	protected long getFolderId(String[] pathArray, boolean parent)
		throws Exception {

		long folderId = DLFolderImpl.DEFAULT_PARENT_FOLDER_ID;

		if (pathArray.length <= 2) {
			return folderId;
		}
		else {
			long groupId = WebDAVUtil.getGroupId(pathArray);

			int x = pathArray.length;

			if (parent) {
				x--;
			}

			for (int i = 2; i < x; i++) {
				String name = pathArray[i];

				DLFolder folder = DLFolderServiceUtil.getFolder(
					groupId, folderId, name);

				if (groupId == folder.getGroupId()) {
					folderId = folder.getFolderId();
				}
			}
		}

		return folderId;
	}

	protected List getFolders(WebDAVRequest webDavReq, long parentFolderId)
		throws Exception {

		List folders = new ArrayList();

		long plid = getPlid(webDavReq.getGroupId());
		long groupId = webDavReq.getGroupId();

		DLFolderPermission.check(
			webDavReq.getPermissionChecker(), plid, parentFolderId,
			ActionKeys.VIEW);

		Iterator itr = DLFolderLocalServiceUtil.getFolders(
			groupId, parentFolderId).iterator();

		while (itr.hasNext()) {
			DLFolder folder = (DLFolder)itr.next();

			if (DLFolderPermission.contains(
					webDavReq.getPermissionChecker(), folder,
					ActionKeys.VIEW)) {

				Resource resource = toResource(webDavReq, folder, true);

				folders.add(resource);
			}
		}

		return folders;
	}

	protected long getParentFolderId(String[] pathArray) throws Exception {
		return getFolderId(pathArray, true);
	}

	protected long getPlid(long groupId) throws SystemException {
		return LayoutLocalServiceUtil.getDefaultPlid(groupId);
	}

	protected Resource toResource(
		WebDAVRequest webDavReq, DLFileEntry fileEntry, boolean appendPath) {

		String parentPath = getRootPath() + webDavReq.getPath();
		String name = StringPool.BLANK;

		if (appendPath) {
			name = fileEntry.getTitleWithExtension();
		}

		return new DLFileEntryResourceImpl(
			webDavReq, fileEntry, parentPath, name);
	}

	protected Resource toResource(
		WebDAVRequest webDavReq, DLFolder folder, boolean appendPath) {

		String parentPath = getRootPath() + webDavReq.getPath();
		String name = StringPool.BLANK;

		if (appendPath) {
			name = folder.getName();
		}

		Resource resource = new BaseResourceImpl(
			parentPath, name, folder.getName(), folder.getCreateDate(),
			folder.getModifiedDate());

		resource.setModel(folder);
		resource.setClassName(DLFolder.class.getName());
		resource.setPrimaryKey(folder.getPrimaryKey());

		return resource;
	}

	private static Log _log = LogFactory.getLog(DLWebDAVStorageImpl.class);

}