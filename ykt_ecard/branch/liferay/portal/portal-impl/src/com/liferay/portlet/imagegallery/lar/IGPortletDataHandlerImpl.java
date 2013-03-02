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

package com.liferay.portlet.imagegallery.lar;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Image;
import com.liferay.portal.service.persistence.ImageUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.imagegallery.NoSuchFolderException;
import com.liferay.portlet.imagegallery.NoSuchImageException;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.model.impl.IGFolderImpl;
import com.liferay.portlet.imagegallery.service.IGFolderLocalServiceUtil;
import com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderUtil;
import com.liferay.portlet.imagegallery.service.persistence.IGImageFinderUtil;
import com.liferay.portlet.imagegallery.service.persistence.IGImageUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;
import com.liferay.util.MapUtil;

import com.thoughtworks.xstream.XStream;

import java.io.File;

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
 * <a href="IGPortletDataHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class IGPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Folders

			if (!context.addPrimaryKey(
					IGPortletDataHandlerImpl.class, "deleteData")) {

				IGFolderLocalServiceUtil.deleteFolders(context.getGroupId());
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

			Element root = doc.addElement("image-gallery");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Folders

			List folders = IGFolderUtil.findByGroupId(context.getGroupId());

			List igImages = new ArrayList();

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				IGFolder folder = (IGFolder)itr.next();

				if (context.addPrimaryKey(
						IGFolder.class, folder.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					folder.setUserUuid(folder.getUserUuid());

					List folderIGImages = IGImageUtil.findByFolderId(
						folder.getFolderId());

					igImages.addAll(folderIGImages);
				}
			}

			String xml = xStream.toXML(folders);

			Element el = root.addElement("ig-folders");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// IGImages

			itr = igImages.iterator();

			while (itr.hasNext()) {
				IGImage igImage = (IGImage)itr.next();

				if (context.addPrimaryKey(
						IGImage.class, igImage.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					igImage.setUserUuid(igImage.getUserUuid());

					if (context.getBooleanParameter(_NAMESPACE, "tags")) {
						context.addTagsEntries(
							IGImage.class, igImage.getPrimaryKeyObj());
					}

					try {
						Image largeImage = ImageUtil.findByPrimaryKey(
							igImage.getLargeImageId());

						igImage.setImageType(largeImage.getType());

						context.getZipWriter().addEntry(
							getIGImageDir(igImage), largeImage.getTextObj());
					}
					catch (com.liferay.portal.NoSuchImageException nsie) {
					}
				}
			}

			xml = xStream.toXML(igImages);

			el = root.addElement("ig-images");

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

		return new PortletDataHandlerControl[] {_foldersAndImages, _tags};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_foldersAndImages, _tags};
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

			Element el = root.element("ig-folders").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map folderPKs = CollectionFactory.getHashMap();

			List folders = (List)xStream.fromXML(tempDoc.asXML());

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				IGFolder folder = (IGFolder)itr.next();

				importFolder(context, folderPKs, folder);
			}

			// IGImages

			el = root.element("ig-images").element("list");

			tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			List igImages = (List)xStream.fromXML(tempDoc.asXML());

			itr = igImages.iterator();

			while (itr.hasNext()) {
				IGImage igImage = (IGImage)itr.next();

				importIGImage(context, folderPKs, igImage);
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected String getIGImageDir(IGImage igImage)
		throws PortalException, SystemException {

		return _IMAGE_GALLERY_FOLDER + igImage.getPrimaryKey() + "." +
			igImage.getImageType();
	}

	protected void importFolder(
			PortletDataContext context, Map folderPKs, IGFolder folder)
		throws Exception {

		long userId = context.getUserId(folder.getUserUuid());
		long plid = context.getPlid();
		long parentFolderId = MapUtil.getLong(
			folderPKs, folder.getParentFolderId(), folder.getParentFolderId());

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		IGFolder existingFolder = null;

		try {
			if (parentFolderId != IGFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
				IGFolderUtil.findByPrimaryKey(parentFolderId);
			}

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				existingFolder = IGFolderUtil.fetchByUUID_G(
					folder.getUuid(), context.getGroupId());

				if (existingFolder == null) {
					existingFolder = IGFolderLocalServiceUtil.addFolder(
						folder.getUuid(), userId, plid, parentFolderId,
						folder.getName(), folder.getDescription(),
						addCommunityPermissions, addGuestPermissions);
				}
				else {
					existingFolder = IGFolderLocalServiceUtil.updateFolder(
						existingFolder.getFolderId(), parentFolderId,
						folder.getName(), folder.getDescription(), false);
				}
			}
			else {
				existingFolder = IGFolderLocalServiceUtil.addFolder(
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

	protected void importIGImage(
			PortletDataContext context, Map folderPKs, IGImage igImage)
		throws Exception {

		long userId = context.getUserId(igImage.getUserUuid());
		long folderId = MapUtil.getLong(
			folderPKs, igImage.getFolderId(), igImage.getFolderId());

		File imageFile = null;

		byte[] byteArray = context.getZipReader().getEntryAsByteArray(
			getIGImageDir(igImage));

		if (byteArray == null) {
			_log.error(
				"Could not find image for IG image " + igImage.getImageId());

			return;
		}
		else {
			imageFile = File.createTempFile(
				String.valueOf(igImage.getPrimaryKey()),
				StringPool.PERIOD + igImage.getImageType());

			FileUtil.write(imageFile, byteArray);
		}

		String[] tagsEntries = null;

		if (context.getBooleanParameter(_NAMESPACE, "tags")) {
			tagsEntries = context.getTagsEntries(
				IGImage.class, igImage.getPrimaryKeyObj());
		}

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		IGImage existingImage = null;

		try {
			IGFolderUtil.findByPrimaryKey(folderId);

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				try {
					existingImage = IGImageFinderUtil.findByUuid_G(
						igImage.getUuid(), context.getGroupId());

					IGImageLocalServiceUtil.updateImage(
						userId, existingImage.getImageId(), folderId,
						igImage.getDescription(), imageFile,
						igImage.getImageType(), tagsEntries);
				}
				catch (NoSuchImageException nsie) {
					IGImageLocalServiceUtil.addImage(
						igImage.getUuid(), userId, folderId,
						igImage.getDescription(), imageFile,
						igImage.getImageType(), tagsEntries,
						addCommunityPermissions, addGuestPermissions);
				}
			}
			else {
				IGImageLocalServiceUtil.addImage(
					userId, folderId, igImage.getDescription(), imageFile,
					igImage.getImageType(), tagsEntries,
					addCommunityPermissions, addGuestPermissions);
			}
		}
		catch (NoSuchFolderException nsfe) {
			_log.error(
				"Could not find the parent folder for IG image " +
					igImage.getImageId());
		}
	}

	private static final String _NAMESPACE = "image_gallery";

	private static final String _IMAGE_GALLERY_FOLDER = "image-gallery/";

	private static final PortletDataHandlerBoolean _foldersAndImages =
		new PortletDataHandlerBoolean(
			_NAMESPACE, "folders-and-images", true, true);

	private static final PortletDataHandlerBoolean _tags =
		new PortletDataHandlerBoolean(_NAMESPACE, "tags");

	private static Log _log = LogFactory.getLog(IGPortletDataHandlerImpl.class);

}