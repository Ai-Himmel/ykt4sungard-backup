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

package com.liferay.portlet.documentlibrary.lar;

import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.NoSuchFileShortcutException;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFileRank;
import com.liferay.portlet.documentlibrary.model.DLFileShortcut;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFileRankLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFileShortcutLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinderUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileRankUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinderUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFolderUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;
import com.liferay.util.MapUtil;

import com.thoughtworks.xstream.XStream;

import java.io.InputStream;

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
 * <a href="DLPortletDataHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class DLPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Folders

			if (!context.addPrimaryKey(
					DLPortletDataHandlerImpl.class, "deleteData")) {

				DLFolderLocalServiceUtil.deleteFolders(context.getGroupId());
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

			Element root = doc.addElement("documentlibrary-data");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Folders

			List folders = DLFolderUtil.findByGroupId(
				context.getGroupId());

			List entries = new ArrayList();

			List shortcuts = new ArrayList();

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				DLFolder folder = (DLFolder)itr.next();

				if (context.addPrimaryKey(
						DLFolder.class, folder.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					folder.setUserUuid(folder.getUserUuid());

					List folderEntries = DLFileEntryUtil.findByFolderId(
						folder.getFolderId());

					entries.addAll(folderEntries);

					if (context.getBooleanParameter(_NAMESPACE, "shortcuts")) {
						List folderShortcuts =
							DLFileShortcutUtil.findByFolderId(
								folder.getFolderId());

						shortcuts.addAll(folderShortcuts);
					}
				}
			}

			String xml = xStream.toXML(folders);

			Element el = root.addElement("documentlibrary-folders");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Entries

			List ranks = new ArrayList();

			itr = entries.iterator();

			while (itr.hasNext()) {
				DLFileEntry entry = (DLFileEntry)itr.next();

				if (context.addPrimaryKey(
						DLFileEntry.class, entry.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					entry.setUserUuid(entry.getUserUuid());

					if (context.getBooleanParameter(_NAMESPACE, "comments")) {
						context.addComments(
							DLFileEntry.class, entry.getPrimaryKeyObj());
					}

					if (context.getBooleanParameter(_NAMESPACE, "ratings")) {
						context.addRatingsEntries(
							DLFileEntry.class, entry.getPrimaryKeyObj());
					}

					if (context.getBooleanParameter(_NAMESPACE, "tags")) {
						context.addTagsEntries(
							DLFileEntry.class, entry.getPrimaryKeyObj());
					}

					InputStream in =
						DLFileEntryLocalServiceUtil.getFileAsStream(
							entry.getCompanyId(), entry.getUserId(),
							entry.getFolderId(), entry.getName());

					context.getZipWriter().addEntry(
						_ZIP_FOLDER + entry.getName(), FileUtil.getBytes(in));

					if (context.getBooleanParameter(_NAMESPACE, "ranks")) {
						List entryRanks = DLFileRankUtil.findByF_N(
							entry.getFolderId(), entry.getName());

						ranks.addAll(entryRanks);
					}
				}
			}

			xml = xStream.toXML(entries);

			el = root.addElement("documentlibrary-entries");

			tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Shortcuts

			itr = shortcuts.iterator();

			while (itr.hasNext()) {
				DLFileShortcut shortcut = (DLFileShortcut)itr.next();

				if (context.addPrimaryKey(
						DLFileShortcut.class, shortcut.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					shortcut.setUserUuid(shortcut.getUserUuid());
				}
			}

			xml = xStream.toXML(shortcuts);

			el = root.addElement("documentlibrary-shortcuts");

			tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Ranks

			itr = ranks.iterator();

			while (itr.hasNext()) {
				DLFileRank rank = (DLFileRank)itr.next();

				if (context.addPrimaryKey(
						DLFileRank.class, rank.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					rank.setUserUuid(rank.getUserUuid());
				}
			}

			xml = xStream.toXML(ranks);

			el = root.addElement("documentlibrary-ranks");

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

		return new PortletDataHandlerControl[] {
			_foldersAndDocuments, _shortcuts, _ranks, _comments, _ratings, _tags
		};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {
			_foldersAndDocuments, _shortcuts, _ranks, _comments, _ratings, _tags
		};
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

			Element el = root.element(
				"documentlibrary-folders").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map folderPKs = CollectionFactory.getHashMap();

			List folders = (List)xStream.fromXML(tempDoc.asXML());

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				DLFolder folder = (DLFolder)itr.next();

				importFolder(context, folderPKs, folder);
			}

			// Entries

			el = root.element("documentlibrary-entries").element("list");

			tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map entryNames = CollectionFactory.getHashMap();

			List entries = (List)xStream.fromXML(tempDoc.asXML());

			itr = entries.iterator();

			while (itr.hasNext()) {
				DLFileEntry entry = (DLFileEntry)itr.next();

				importEntry(context, folderPKs, entryNames, entry);
			}

			// Shortcuts

			if (context.getBooleanParameter(_NAMESPACE, "shortcuts")) {
				el = root.element("documentlibrary-shortcuts").element("list");

				tempDoc = DocumentHelper.createDocument();

				tempDoc.content().add(el.createCopy());

				List shortcuts = (List)xStream.fromXML(tempDoc.asXML());

				itr = shortcuts.iterator();

				while (itr.hasNext()) {
					DLFileShortcut shortcut = (DLFileShortcut)itr.next();

					importShortcut(context, folderPKs, entryNames, shortcut);
				}
			}

			// Ranks

			if (context.getBooleanParameter(_NAMESPACE, "ranks")) {
				el = root.element("documentlibrary-ranks").element("list");

				tempDoc = DocumentHelper.createDocument();

				tempDoc.content().add(el.createCopy());

				List ranks = (List)xStream.fromXML(tempDoc.asXML());

				itr = ranks.iterator();

				while (itr.hasNext()) {
					DLFileRank rank = (DLFileRank)itr.next();

					importRank(context, folderPKs, entryNames, rank);
				}
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected void importEntry(
			PortletDataContext context, Map folderPKs, Map entryNames,
			DLFileEntry entry)
		throws Exception {

		long userId = context.getUserId(entry.getUserUuid());
		long folderId = MapUtil.getLong(
			folderPKs, entry.getFolderId(), entry.getFolderId());

		String[] tagsEntries = null;

		if (context.getBooleanParameter(_NAMESPACE, "tags")) {
			tagsEntries = context.getTagsEntries(
				DLFileEntry.class, entry.getPrimaryKeyObj());
		}

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		byte[] byteArray = context.getZipReader().getEntryAsByteArray(
			_ZIP_FOLDER + entry.getName());

		DLFileEntry existingEntry = null;

		try {
			DLFolderUtil.findByPrimaryKey(folderId);

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				try {
					existingEntry = DLFileEntryFinderUtil.findByUuid_G(
						entry.getUuid(), context.getGroupId());

					existingEntry = DLFileEntryLocalServiceUtil.updateFileEntry(
						userId, existingEntry.getFolderId(), folderId,
						existingEntry.getName(), entry.getName(),
						entry.getTitle(), entry.getDescription(), tagsEntries,
						entry.getExtraSettings(), byteArray);
				}
				catch (NoSuchFileEntryException nsfee) {
					existingEntry = DLFileEntryLocalServiceUtil.addFileEntry(
						entry.getUuid(), userId, folderId, entry.getName(),
						entry.getTitle(), entry.getDescription(),
						tagsEntries, entry.getExtraSettings(), byteArray,
						addCommunityPermissions, addGuestPermissions);
				}
			}
			else {
				existingEntry = DLFileEntryLocalServiceUtil.addFileEntry(
					userId, folderId, entry.getName(), entry.getTitle(),
					entry.getDescription(), tagsEntries,
					entry.getExtraSettings(), byteArray,
					addCommunityPermissions, addGuestPermissions);
			}

			entryNames.put(entry.getName(), existingEntry.getName());

			if (context.getBooleanParameter(_NAMESPACE, "comments")) {
				context.importComments(
					DLFileEntry.class, entry.getPrimaryKeyObj(),
					existingEntry.getPrimaryKeyObj(), context.getGroupId());
			}

			if (context.getBooleanParameter(_NAMESPACE, "ratings")) {
				context.importRatingsEntries(
					DLFileEntry.class, entry.getPrimaryKeyObj(),
					existingEntry.getPrimaryKeyObj());
			}
		}
		catch (NoSuchFolderException nsfe) {
			_log.error(
				"Could not find the parent folder for entry " +
					entry.getFileEntryId());
		}
	}

	protected void importFolder(
			PortletDataContext context, Map folderPKs, DLFolder folder)
		throws Exception {

		long userId = context.getUserId(folder.getUserUuid());
		long plid = context.getPlid();
		long parentFolderId = MapUtil.getLong(
			folderPKs, folder.getParentFolderId(), folder.getParentFolderId());

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		DLFolder existingFolder = null;

		try {
			if (parentFolderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
				DLFolderUtil.findByPrimaryKey(parentFolderId);
			}

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				existingFolder = DLFolderUtil.fetchByUUID_G(
					folder.getUuid(), context.getGroupId());

				if (existingFolder == null) {
					existingFolder = DLFolderLocalServiceUtil.addFolder(
						folder.getUuid(), userId, plid, parentFolderId,
						folder.getName(), folder.getDescription(),
						addCommunityPermissions, addGuestPermissions);
				}
				else {
					existingFolder = DLFolderLocalServiceUtil.updateFolder(
						existingFolder.getFolderId(), parentFolderId,
						folder.getName(), folder.getDescription());
				}
			}
			else {
				existingFolder = DLFolderLocalServiceUtil.addFolder(
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

	protected void importRank(
			PortletDataContext context, Map folderPKs, Map entryNames,
			DLFileRank rank)
		throws Exception {

		long userId = context.getUserId(rank.getUserUuid());
		long folderId = MapUtil.getLong(
			folderPKs, rank.getFolderId(), rank.getFolderId());

		String name = (String)folderPKs.get(rank.getName());

		if (name == null) {
			name = rank.getName();
		}

		try {
			DLFolderUtil.findByPrimaryKey(folderId);

			DLFileRankLocalServiceUtil.updateFileRank(
				context.getGroupId(), context.getCompanyId(), userId, folderId,
				name);
		}
		catch (NoSuchFolderException nsfe) {
			_log.error(
				"Could not find the folder for rank " + rank.getFileRankId());
		}
	}

	protected void importShortcut(
			PortletDataContext context, Map folderPKs, Map entryNames,
			DLFileShortcut shortcut)
		throws Exception {

		long userId = context.getUserId(shortcut.getUserUuid());
		long folderId = MapUtil.getLong(
			folderPKs, shortcut.getFolderId(), shortcut.getFolderId());
		long toFolderId = MapUtil.getLong(
			folderPKs, shortcut.getToFolderId(), shortcut.getToFolderId());
		String toName = MapUtil.getString(
			entryNames, shortcut.getToName(), shortcut.getToName());

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		try {
			DLFolderUtil.findByPrimaryKey(folderId);
			DLFolderUtil.findByPrimaryKey(toFolderId);

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				try {
					DLFileShortcut existingShortcut =
						DLFileShortcutFinderUtil.findByUuid_G(
							shortcut.getUuid(), context.getGroupId());

					DLFileShortcutLocalServiceUtil.updateFileShortcut(
						userId, existingShortcut.getFileShortcutId(), folderId,
						toFolderId, toName);
				}
				catch (NoSuchFileShortcutException nsfse) {
					DLFileShortcutLocalServiceUtil.addFileShortcut(
						shortcut.getUuid(), userId, folderId, toFolderId,
						toName, addCommunityPermissions, addGuestPermissions);
				}
			}
			else {
				DLFileShortcutLocalServiceUtil.addFileShortcut(
					userId, folderId, toFolderId, toName,
					addCommunityPermissions, addGuestPermissions);
			}
		}
		catch (NoSuchFolderException nsfe) {
			_log.error(
				"Could not find the folder for shortcut " +
					shortcut.getFileShortcutId());
		}
	}

	private static final String _NAMESPACE = "document_library";

	private static final String _ZIP_FOLDER = "document-library/";

	private static final PortletDataHandlerBoolean _foldersAndDocuments =
		new PortletDataHandlerBoolean(
			_NAMESPACE, "folders-and-documents", true, true);

	private static final PortletDataHandlerBoolean _ranks =
		new PortletDataHandlerBoolean(_NAMESPACE, "ranks");

	private static final PortletDataHandlerBoolean _shortcuts=
		new PortletDataHandlerBoolean(_NAMESPACE, "shortcuts");

	private static final PortletDataHandlerBoolean _comments =
		new PortletDataHandlerBoolean(_NAMESPACE, "comments");

	private static final PortletDataHandlerBoolean _ratings =
		new PortletDataHandlerBoolean(_NAMESPACE, "ratings");

	private static final PortletDataHandlerBoolean _tags =
		new PortletDataHandlerBoolean(_NAMESPACE, "tags");

	private static Log _log =
		LogFactory.getLog(DLPortletDataHandlerImpl.class);

}