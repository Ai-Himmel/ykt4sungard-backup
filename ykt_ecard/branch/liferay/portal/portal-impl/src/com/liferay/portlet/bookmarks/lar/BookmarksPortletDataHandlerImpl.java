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

package com.liferay.portlet.bookmarks.lar;

import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.bookmarks.NoSuchEntryException;
import com.liferay.portlet.bookmarks.NoSuchFolderException;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.model.impl.BookmarksFolderImpl;
import com.liferay.portlet.bookmarks.service.BookmarksEntryLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinderUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.MapUtil;

import com.thoughtworks.xstream.XStream;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="BookmarksPortletDataHandlerImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 * @author Bruno Farache
 *
 */
public class BookmarksPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Folders

			if (!context.addPrimaryKey(
					BookmarksPortletDataHandlerImpl.class, "deleteData")) {

				BookmarksFolderLocalServiceUtil.deleteFolders(
					context.getGroupId());
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public String exportData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = DocumentHelper.createDocument();

			Element root = doc.addElement("bookmarks-data");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Folders

			List folders = BookmarksFolderUtil.findByGroupId(
				context.getGroupId());

			List entries = new ArrayList();

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				BookmarksFolder folder = (BookmarksFolder)itr.next();

				if (context.addPrimaryKey(
						BookmarksFolder.class, folder.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					folder.setUserUuid(folder.getUserUuid());

					List folderEntries = BookmarksEntryUtil.findByFolderId(
						folder.getFolderId());

					entries.addAll(folderEntries);
				}
			}

			String xml = xStream.toXML(folders);

			Element el = root.addElement("bookmark-folders");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Entries

			itr = entries.iterator();

			while (itr.hasNext()) {
				BookmarksEntry entry = (BookmarksEntry)itr.next();

				if (context.addPrimaryKey(
						BookmarksEntry.class, entry.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					entry.setUserUuid(entry.getUserUuid());

					if (context.getBooleanParameter(_NAMESPACE, "tags")) {
						context.addTagsEntries(
							BookmarksEntry.class, entry.getPrimaryKeyObj());
					}
				}
			}

			xml = xStream.toXML(entries);

			el = root.addElement("bookmark-entries");

			tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			return doc.asXML();
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public PortletDataHandlerControl[] getExportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_foldersAndEntries, _tags};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_foldersAndEntries, _tags};
	}

	public PortletPreferences importData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs, String data)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = PortalUtil.readDocumentFromXML(data);

			Element root = doc.getRootElement();

			// Folders

			Element el = root.element("bookmark-folders").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map folderPKs = CollectionFactory.getHashMap();

			List folders = (List)xStream.fromXML(tempDoc.asXML());

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				BookmarksFolder folder = (BookmarksFolder)itr.next();

				importFolder(context, folderPKs, folder);
			}

			// Entries

			el = root.element("bookmark-entries").element("list");

			tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			List entries = (List)xStream.fromXML(tempDoc.asXML());

			itr = entries.iterator();

			while (itr.hasNext()) {
				BookmarksEntry entry = (BookmarksEntry)itr.next();

				importEntry(context, folderPKs, entry);
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected void importEntry(
			PortletDataContext context, Map folderPKs, BookmarksEntry entry)
		throws Exception {

		long userId = context.getUserId(entry.getUserUuid());
		long folderId = MapUtil.getLong(
			folderPKs, entry.getFolderId(), entry.getFolderId());

		String[] tagsEntries = null;

		if (context.getBooleanParameter(_NAMESPACE, "tags")) {
			tagsEntries = context.getTagsEntries(
				BookmarksEntry.class, entry.getPrimaryKeyObj());
		}

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		BookmarksEntry existingEntry = null;

		try {
			BookmarksFolderUtil.findByPrimaryKey(folderId);

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				try {
					existingEntry = BookmarksEntryFinderUtil.findByUuid_G(
						entry.getUuid(), context.getGroupId());

					BookmarksEntryLocalServiceUtil.updateEntry(
						userId, existingEntry.getEntryId(), folderId,
						entry.getName(), entry.getUrl(), entry.getComments(),
						tagsEntries);
				}
				catch (NoSuchEntryException nsee) {
					BookmarksEntryLocalServiceUtil.addEntry(
						entry.getUuid(), userId, folderId, entry.getName(),
						entry.getUrl(), entry.getComments(), tagsEntries,
						addCommunityPermissions, addGuestPermissions);
				}
			}
			else {
				BookmarksEntryLocalServiceUtil.addEntry(
					userId, folderId, entry.getName(), entry.getUrl(),
					entry.getComments(), tagsEntries, addCommunityPermissions,
					addGuestPermissions);
			}
		}
		catch (NoSuchFolderException nsfe) {
			_log.error(
				"Could not find the parent folder for entry " +
					entry.getEntryId());
		}
	}

	protected void importFolder(
			PortletDataContext context, Map folderPKs, BookmarksFolder folder)
		throws Exception {

		long userId = context.getUserId(folder.getUserUuid());
		long plid = context.getPlid();
		long parentFolderId = MapUtil.getLong(
			folderPKs, folder.getParentFolderId(), folder.getParentFolderId());

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		BookmarksFolder existingFolder = null;

		try {
			if (parentFolderId !=
					BookmarksFolderImpl.DEFAULT_PARENT_FOLDER_ID) {

				BookmarksFolderUtil.findByPrimaryKey(parentFolderId);
			}

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {
				existingFolder = BookmarksFolderUtil.fetchByUUID_G(
					folder.getUuid(), context.getGroupId());

				if (existingFolder == null) {
					existingFolder = BookmarksFolderLocalServiceUtil.addFolder(
						folder.getUuid(), userId, plid, parentFolderId,
						folder.getName(), folder.getDescription(),
						addCommunityPermissions, addGuestPermissions);
				}
				else {
					existingFolder =
						BookmarksFolderLocalServiceUtil.updateFolder(
							existingFolder.getFolderId(), parentFolderId,
							folder.getName(), folder.getDescription(), false);
				}
			}
			else {
				existingFolder = BookmarksFolderLocalServiceUtil.addFolder(
					userId, plid, parentFolderId, folder.getName(),
					folder.getDescription(), addCommunityPermissions,
					addGuestPermissions);
			}

			folderPKs.put(
				folder.getPrimaryKeyObj(), existingFolder.getPrimaryKeyObj());
		}
		catch (NoSuchFolderException nsfe) {
			_log.error(
				"Could not find the parent folder for folder " +
					folder.getFolderId());
		}
	}

	private static final String _NAMESPACE = "bookmarks";

	private static final PortletDataHandlerBoolean _foldersAndEntries =
		new PortletDataHandlerBoolean(
			_NAMESPACE, "folders-and-entries", true, true);

	private static final PortletDataHandlerBoolean _tags =
		new PortletDataHandlerBoolean(_NAMESPACE, "tags");

	private static Log _log =
		LogFactory.getLog(BookmarksPortletDataHandlerImpl.class);

}