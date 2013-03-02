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

package com.liferay.portlet.softwarecatalog.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.servlet.ImageServletTokenUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.plugin.ModuleId;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.softwarecatalog.DuplicateProductEntryModuleIdException;
import com.liferay.portlet.softwarecatalog.NoSuchProductEntryException;
import com.liferay.portlet.softwarecatalog.ProductEntryAuthorException;
import com.liferay.portlet.softwarecatalog.ProductEntryLicenseException;
import com.liferay.portlet.softwarecatalog.ProductEntryNameException;
import com.liferay.portlet.softwarecatalog.ProductEntryPageURLException;
import com.liferay.portlet.softwarecatalog.ProductEntryScreenshotsException;
import com.liferay.portlet.softwarecatalog.ProductEntryShortDescriptionException;
import com.liferay.portlet.softwarecatalog.ProductEntryTypeException;
import com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion;
import com.liferay.portlet.softwarecatalog.model.SCLicense;
import com.liferay.portlet.softwarecatalog.model.SCProductEntry;
import com.liferay.portlet.softwarecatalog.model.SCProductScreenshot;
import com.liferay.portlet.softwarecatalog.model.SCProductVersion;
import com.liferay.portlet.softwarecatalog.service.base.SCProductEntryLocalServiceBaseImpl;
import com.liferay.portlet.softwarecatalog.util.Indexer;
import com.liferay.util.Time;
import com.liferay.util.Version;
import com.liferay.util.lucene.HitsImpl;
import com.liferay.util.xml.DocUtil;

import java.io.IOException;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="SCProductEntryLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductEntryLocalServiceImpl
	extends SCProductEntryLocalServiceBaseImpl {

	public SCProductEntry addProductEntry(
			long userId, long plid, String name, String type, String tags,
			String shortDescription, String longDescription, String pageURL,
			String author, String repoGroupId, String repoArtifactId,
			long[] licenseIds, List thumbnails, List fullImages,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addProductEntry(
			userId, plid, name, type, tags, shortDescription, longDescription,
			pageURL, author, repoGroupId, repoArtifactId, licenseIds,
			thumbnails, fullImages, Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public SCProductEntry addProductEntry(
			long userId, long plid, String name, String type, String tags,
			String shortDescription, String longDescription, String pageURL,
			String author, String repoGroupId, String repoArtifactId,
			long[] licenseIds, List thumbnails, List fullImages,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		return addProductEntry(
			userId, plid, name, type, tags, shortDescription, longDescription,
			pageURL, author, repoGroupId, repoArtifactId, licenseIds,
			thumbnails, fullImages, null, null, communityPermissions,
			guestPermissions);
	}

	public SCProductEntry addProductEntry(
			long userId, long plid, String name, String type, String tags,
			String shortDescription, String longDescription, String pageURL,
			String author, String repoGroupId, String repoArtifactId,
			long[] licenseIds, List thumbnails, List fullImages,
			Boolean addCommunityPermissions, Boolean addGuestPermissions,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		// Product entry

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);
		tags = getTags(tags);
		repoGroupId = repoGroupId.trim().toLowerCase();
		repoArtifactId = repoArtifactId.trim().toLowerCase();
		Date now = new Date();

		validate(
			0, name, type, shortDescription, pageURL, author, repoGroupId,
			repoArtifactId, licenseIds, thumbnails, fullImages);

		long productEntryId = counterLocalService.increment();

		SCProductEntry productEntry = scProductEntryPersistence.create(
			productEntryId);

		productEntry.setGroupId(groupId);
		productEntry.setCompanyId(user.getCompanyId());
		productEntry.setUserId(user.getUserId());
		productEntry.setUserName(user.getFullName());
		productEntry.setCreateDate(now);
		productEntry.setModifiedDate(now);
		productEntry.setName(name);
		productEntry.setType(type);
		productEntry.setTags(tags);
		productEntry.setShortDescription(shortDescription);
		productEntry.setLongDescription(longDescription);
		productEntry.setPageURL(pageURL);
		productEntry.setAuthor(author);
		productEntry.setRepoGroupId(repoGroupId);
		productEntry.setRepoArtifactId(repoArtifactId);

		scProductEntryPersistence.update(productEntry);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addProductEntryResources(
				productEntry, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addProductEntryResources(
				productEntry, communityPermissions, guestPermissions);
		}

		// Licenses

		scProductEntryPersistence.setSCLicenses(productEntryId, licenseIds);

		// Product screenshots

		saveProductScreenshots(productEntry, thumbnails, fullImages);

		// Lucene

		try {
			Indexer.addProductEntry(
				productEntry.getCompanyId(), groupId, userId,
				user.getFullName(), productEntryId, name, now, StringPool.BLANK,
				type, shortDescription, longDescription, pageURL, repoGroupId,
				repoArtifactId);
		}
		catch (IOException ioe) {
			_log.error("Indexing " + productEntryId, ioe);
		}

		return productEntry;
	}

	public void addProductEntryResources(
			long productEntryId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		SCProductEntry productEntry =
			scProductEntryPersistence.findByPrimaryKey(productEntryId);

		addProductEntryResources(
			productEntry, addCommunityPermissions, addGuestPermissions);
	}

	public void addProductEntryResources(
			SCProductEntry productEntry, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			productEntry.getCompanyId(), productEntry.getGroupId(),
			productEntry.getUserId(), SCProductEntry.class.getName(),
			productEntry.getProductEntryId(), false, addCommunityPermissions,
			addGuestPermissions);
	}

	public void addProductEntryResources(
			long productEntryId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		SCProductEntry productEntry =
			scProductEntryPersistence.findByPrimaryKey(productEntryId);

		addProductEntryResources(
			productEntry, communityPermissions, guestPermissions);
	}

	public void addProductEntryResources(
			SCProductEntry productEntry, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			productEntry.getCompanyId(), productEntry.getGroupId(),
			productEntry.getUserId(), SCProductEntry.class.getName(),
			productEntry.getProductEntryId(), communityPermissions,
			guestPermissions);
	}

	public void deleteProductEntries(long groupId)
		throws PortalException, SystemException {

		Iterator itr = scProductEntryPersistence.findByGroupId(
			groupId).iterator();

		while (itr.hasNext()) {
			SCProductEntry productEntry = (SCProductEntry)itr.next();

			deleteProductEntry(productEntry);
		}
	}

	public void deleteProductEntry(long productEntryId)
		throws PortalException, SystemException {

		SCProductEntry productEntry =
			scProductEntryPersistence.findByPrimaryKey(productEntryId);

		deleteProductEntry(productEntry);
	}

	public void deleteProductEntry(SCProductEntry productEntry)
		throws PortalException, SystemException {

		// Lucene

		try {
			Indexer.deleteProductEntry(
				productEntry.getCompanyId(), productEntry.getProductEntryId());
		}
		catch (IOException ioe) {
			_log.error(
				"Deleting index " + productEntry.getProductEntryId(), ioe);
		}

		// Product screenshots

		scProductScreenshotLocalService.deleteProductScreenshots(
			productEntry.getProductEntryId());

		// Product versions

		scProductVersionLocalService.deleteProductVersions(
			productEntry.getProductEntryId());

		// Ratings

		ratingsStatsLocalService.deleteStats(
			SCProductEntry.class.getName(), productEntry.getProductEntryId());

		// Message boards

		mbMessageLocalService.deleteDiscussionMessages(
			SCProductEntry.class.getName(), productEntry.getProductEntryId());

		// Resources

		resourceLocalService.deleteResource(
			productEntry.getCompanyId(), SCProductEntry.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, productEntry.getProductEntryId());

		// Product entry

		scProductEntryPersistence.remove(productEntry);
	}

	public SCProductEntry getProductEntry(long productEntryId)
		throws PortalException, SystemException {

		return scProductEntryPersistence.findByPrimaryKey(productEntryId);
	}

	public List getProductEntries(long groupId, int begin, int end)
		throws SystemException {

		return scProductEntryPersistence.findByGroupId(groupId, begin, end);
	}

	public List getProductEntries(
			long groupId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return scProductEntryPersistence.findByGroupId(
			groupId, begin, end, obc);
	}

	public List getProductEntries(long groupId, long userId, int begin, int end)
		throws SystemException {

		return scProductEntryPersistence.findByG_U(groupId, userId, begin, end);
	}

	public List getProductEntries(
			long groupId, long userId, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		return scProductEntryPersistence.findByG_U(
			groupId, userId, begin, end, obc);
	}

	public int getProductEntriesCount(long groupId)
		throws SystemException {

		return scProductEntryPersistence.countByGroupId(groupId);
	}

	public int getProductEntriesCount(long groupId, long userId)
		throws SystemException {

		return scProductEntryPersistence.countByG_U(groupId, userId);
	}

	public String getRepositoryXML(
			long groupId, String baseImageURL, Date oldestDate,
			int maxNumOfVersions, Properties repoSettings)
		throws PortalException, SystemException {

		return getRepositoryXML(
			groupId, null, baseImageURL, oldestDate, maxNumOfVersions,
			repoSettings);
	}

	public String getRepositoryXML(
			long groupId, String version, String baseImageURL, Date oldestDate,
			int maxNumOfVersions, Properties repoSettings)
		throws PortalException, SystemException {

		Document doc = DocumentHelper.createDocument();

		doc.setXMLEncoding("UTF-8");

		Element root = doc.addElement("plugin-repository");

		Element settingsEl = root.addElement("settings");

		populateSettingsElement(settingsEl, repoSettings);

		List productEntries = scProductEntryPersistence.findByGroupId(groupId);

		Iterator itr = productEntries.iterator();

		while (itr.hasNext()) {
			SCProductEntry productEntry = (SCProductEntry)itr.next();

			if (Validator.isNull(productEntry.getRepoGroupId()) ||
				Validator.isNull(productEntry.getRepoArtifactId())) {

				continue;
			}

			List productVersions =
				scProductVersionPersistence.findByProductEntryId(
					productEntry.getProductEntryId());

			Iterator itr2 = productVersions.iterator();

			for (int i = 1; itr2.hasNext(); i++) {
				SCProductVersion productVersion = (SCProductVersion)itr2.next();

				if ((maxNumOfVersions > 0) && (maxNumOfVersions < i)) {
					break;
				}

				if (!productVersion.isRepoStoreArtifact()) {
					continue;
				}

				if ((oldestDate != null) &&
					(oldestDate.after(productVersion.getModifiedDate()))) {

					continue;
				}

				if (Validator.isNotNull(version) &&
					!isVersionSupported(
						version, productVersion.getFrameworkVersions())) {

					continue;
				}

				Element el = root.addElement("plugin-package");

				populatePluginPackageElement(
					el, productEntry, productVersion, baseImageURL);
			}
		}

		return doc.asXML();
	}

	public void reIndex(String[] ids) throws SystemException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		long companyId = GetterUtil.getLong(ids[0]);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			Iterator itr = scProductEntryPersistence.findByCompanyId(
				companyId).iterator();

			while (itr.hasNext()) {
				SCProductEntry productEntry = (SCProductEntry)itr.next();

				long productEntryId = productEntry.getProductEntryId();

				String version = StringPool.BLANK;

				SCProductVersion latestProductVersion =
					productEntry.getLatestVersion();

				if (latestProductVersion != null) {
					version = latestProductVersion.getVersion();
				}

				try {
					org.apache.lucene.document.Document doc =
						Indexer.getAddProductEntryDocument(
							companyId, productEntry.getGroupId(),
							productEntry.getUserId(),
							productEntry.getUserName(),
							productEntryId, productEntry.getName(),
							productEntry.getModifiedDate(), version,
							productEntry.getType(),
							productEntry.getShortDescription(),
							productEntry.getLongDescription(),
							productEntry.getPageURL(),
							productEntry.getRepoGroupId(),
							productEntry.getRepoArtifactId());

					writer.addDocument(doc);
				}
				catch (Exception e1) {
					_log.error("Reindexing " + productEntryId, e1);
				}
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e2) {
			throw new SystemException(e2);
		}
		finally {
			try {
				if (writer != null) {
					LuceneUtil.write(companyId);
				}
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
	}

	public Hits search(
			long companyId, long groupId, String keywords, String type)
		throws SystemException {

		Searcher searcher = null;

		try {
			HitsImpl hits = new HitsImpl();

			BooleanQuery contextQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				contextQuery, LuceneFields.PORTLET_ID, Indexer.PORTLET_ID);
			LuceneUtil.addRequiredTerm(
				contextQuery, LuceneFields.GROUP_ID, groupId);

			BooleanQuery fullQuery = new BooleanQuery();

			fullQuery.add(contextQuery, BooleanClause.Occur.MUST);

			if (Validator.isNotNull(keywords)) {
				BooleanQuery searchQuery = new BooleanQuery();

				LuceneUtil.addTerm(searchQuery, LuceneFields.TITLE, keywords);
				LuceneUtil.addTerm(searchQuery, LuceneFields.CONTENT, keywords);

				fullQuery.add(searchQuery, BooleanClause.Occur.MUST);
			}

			if (Validator.isNotNull(type)) {
				BooleanQuery searchQuery = new BooleanQuery();

				LuceneUtil.addRequiredTerm(searchQuery, "type", type);

				fullQuery.add(searchQuery, BooleanClause.Occur.MUST);
			}

			searcher = LuceneUtil.getSearcher(companyId);

			hits.recordHits(searcher.search(fullQuery), searcher);

			return hits;
		}
		catch (Exception e) {
			return LuceneUtil.closeSearcher(searcher, keywords, e);
		}
	}

	public SCProductEntry updateProductEntry(
			long productEntryId, String name, String type, String tags,
			String shortDescription, String longDescription, String pageURL,
			String author, String repoGroupId, String repoArtifactId,
			long[] licenseIds, List thumbnails, List fullImages)
		throws PortalException, SystemException {

		// Product entry

		tags = getTags(tags);
		repoGroupId = repoGroupId.trim().toLowerCase();
		repoArtifactId = repoArtifactId.trim().toLowerCase();
		Date now = new Date();

		validate(
			productEntryId, name, type, shortDescription, pageURL, author,
			repoGroupId, repoArtifactId, licenseIds, thumbnails, fullImages);

		SCProductEntry productEntry =
			scProductEntryPersistence.findByPrimaryKey(productEntryId);

		productEntry.setModifiedDate(now);
		productEntry.setName(name);
		productEntry.setType(type);
		productEntry.setTags(tags);
		productEntry.setShortDescription(shortDescription);
		productEntry.setLongDescription(longDescription);
		productEntry.setPageURL(pageURL);
		productEntry.setAuthor(author);
		productEntry.setRepoGroupId(repoGroupId);
		productEntry.setRepoArtifactId(repoArtifactId);

		scProductEntryPersistence.update(productEntry);

		// Licenses

		scProductEntryPersistence.setSCLicenses(productEntryId, licenseIds);

		// Product screenshots

		if (thumbnails.size() == 0) {
			scProductScreenshotLocalService.deleteProductScreenshots(
				productEntryId);
		}
		else {
			saveProductScreenshots(productEntry, thumbnails, fullImages);
		}

		// Latest product version

		String version = StringPool.BLANK;

		List productVersions = scProductVersionPersistence.findByProductEntryId(
			productEntryId, 0, 1);

		if (productVersions.size() > 0) {
			SCProductVersion productVersion =
				(SCProductVersion)productVersions.get(0);

			productVersion.setModifiedDate(now);

			scProductVersionPersistence.update(productVersion);

			version = productVersion.getVersion();
		}

		// Lucene

		try {
			Indexer.updateProductEntry(
				productEntry.getCompanyId(), productEntry.getGroupId(),
				productEntry.getUserId(), productEntry.getUserName(),
				productEntryId, name, now, version, type, shortDescription,
				longDescription, pageURL, repoGroupId, repoArtifactId);
		}
		catch (IOException ioe) {
			_log.error("Indexing " + productEntryId, ioe);
		}

		return productEntry;
	}

	protected String getTags(String tags) {
		tags = tags.trim().toLowerCase();

		return StringUtil.merge(StringUtil.split(tags), ", ");
	}

	protected boolean isVersionSupported(
		String version, List supportedVersions) {

		Version currentVersion = Version.getInstance(version);

		Iterator iterator = supportedVersions.iterator();

		while (iterator.hasNext()) {
			SCFrameworkVersion frameworkVersion =
				(SCFrameworkVersion)iterator.next();

			Version supportedVersion = Version.getInstance(
				frameworkVersion.getName());

			if (supportedVersion.includes(currentVersion)) {
				return true;
			}
		}

		return false;
	}

	protected void populatePluginPackageElement(
			Element el, SCProductEntry productEntry,
			SCProductVersion productVersion, String baseImageURL)
		throws PortalException, SystemException {

		DocUtil.add(el, "name", productEntry.getName());

		String moduleId = ModuleId.toString(
			productEntry.getRepoGroupId(), productEntry.getRepoArtifactId(),
			productVersion.getVersion(), "war");

		DocUtil.add(el, "module-id", moduleId);

		DocUtil.add(
			el, "modified-date",
			Time.getRFC822(productVersion.getModifiedDate()));

		Element typesEl = el.addElement("types");

		DocUtil.add(typesEl, "type", productEntry.getType());

		Element tagsEl = el.addElement("tags");

		String[] tags = StringUtil.split(productEntry.getTags());

		for (int i = 0; i < tags.length; i++) {
			DocUtil.add(tagsEl, "tag", tags[i]);
		}

		DocUtil.add(
			el, "short-description", productEntry.getShortDescription());

		if (Validator.isNotNull(productEntry.getLongDescription())) {
			DocUtil.add(
				el, "long-description", productEntry.getLongDescription());
		}

		if (Validator.isNotNull(productVersion.getChangeLog())) {
			DocUtil.add(el, "change-log", productVersion.getChangeLog());
		}

		if (Validator.isNotNull(productVersion.getDirectDownloadURL())) {
			DocUtil.add(
				el, "download-url", productVersion.getDirectDownloadURL());
		}

		DocUtil.add(el, "author", productEntry.getAuthor());

		Element screenshotsEl = el.addElement("screenshots");

		Iterator itr = productEntry.getScreenshots().iterator();

		while (itr.hasNext()) {
			SCProductScreenshot screenshot = (SCProductScreenshot)itr.next();

			long thumbnailId = screenshot.getThumbnailId();
			long fullImageId = screenshot.getFullImageId();

			Element screenshotEl = screenshotsEl.addElement("screenshot");

			DocUtil.add(
				screenshotEl, "thumbnail-url",
				baseImageURL + "?img_id=" + thumbnailId + "&t=" +
					ImageServletTokenUtil.getToken(thumbnailId));
			DocUtil.add(
				screenshotEl, "large-image-url",
				baseImageURL + "?img_id=" + fullImageId + "&t=" +
					ImageServletTokenUtil.getToken(fullImageId));
		}

		Element licensesEl = el.addElement("licenses");

		itr = productEntry.getLicenses().iterator();

		while (itr.hasNext()) {
			SCLicense license = (SCLicense)itr.next();

			Element licenseEl = licensesEl.addElement("license");

			licenseEl.addText(license.getName());
			licenseEl.addAttribute(
				"osi-approved", String.valueOf(license.isOpenSource()));
		}

		Element liferayVersionsEl = el.addElement("liferay-versions");

		itr = productVersion.getFrameworkVersions().iterator();

		while (itr.hasNext()) {
			SCFrameworkVersion frameworkVersion =
				(SCFrameworkVersion)itr.next();

			DocUtil.add(
				liferayVersionsEl, "liferay-version",
				frameworkVersion.getName());
		}
	}

	protected void populateSettingsElement(
		Element el, Properties repoSettings) {

		if (repoSettings == null) {
			return;
		}

		Iterator itr = repoSettings.keySet().iterator();

		while (itr.hasNext()) {
			String key = (String) itr.next();

			Element settingEl = el.addElement("setting");

			settingEl.addAttribute("name", key);
			settingEl.addAttribute("value", repoSettings.getProperty(key));
		}
	}

	protected void saveProductScreenshots(
			SCProductEntry productEntry, List thumbnails, List fullImages)
		throws SystemException {

		long productEntryId = productEntry.getProductEntryId();

		List productScreenshots =
			scProductScreenshotPersistence.findByProductEntryId(productEntryId);

		if (thumbnails.size() < productScreenshots.size()) {
			for (int i = thumbnails.size(); i < productScreenshots.size();
					i++) {

				SCProductScreenshot productScreenshot =
					(SCProductScreenshot)productScreenshots.get(i);

				scProductScreenshotLocalService.deleteProductScreenshot(
					productScreenshot);
			}
		}

		for (int i = 0; i < thumbnails.size(); i++) {
			int priority = i;

			byte[] thumbnail = (byte[])thumbnails.get(i);
			byte[] fullImage = (byte[])fullImages.get(i);

			SCProductScreenshot productScreenshot =
				scProductScreenshotPersistence.fetchByP_P(
					productEntryId, priority);

			if (productScreenshot == null) {
				long productScreenshotId = counterLocalService.increment();

				long thumbnailId = counterLocalService.increment();
				long fullImageId = counterLocalService.increment();

				productScreenshot = scProductScreenshotPersistence.create(
					productScreenshotId);

				productScreenshot.setCompanyId(productEntry.getCompanyId());
				productScreenshot.setGroupId(productEntry.getGroupId());
				productScreenshot.setProductEntryId(productEntryId);
				productScreenshot.setThumbnailId(thumbnailId);
				productScreenshot.setFullImageId(fullImageId);
				productScreenshot.setPriority(priority);

				scProductScreenshotPersistence.update(productScreenshot);
			}

			ImageLocalUtil.updateImage(
				productScreenshot.getThumbnailId(), thumbnail);
			ImageLocalUtil.updateImage(
				productScreenshot.getFullImageId(), fullImage);
		}
	}

	protected void validate(
			long productEntryId, String name, String type,
			String shortDescription, String pageURL, String author,
			String repoGroupId, String repoArtifactId, long[] licenseIds,
			List thumbnails, List fullImages)
		throws PortalException, SystemException {

		if (Validator.isNull(name)) {
			throw new ProductEntryNameException();
		}

		if (Validator.isNull(type)) {
			throw new ProductEntryTypeException();
		}

		if (Validator.isNull(shortDescription)) {
			throw new ProductEntryShortDescriptionException();
		}

		if (Validator.isNull(pageURL)) {
			throw new ProductEntryPageURLException();
		}
		else {
			try {
				new URL(pageURL);
			}
			catch (MalformedURLException murle) {
				throw new ProductEntryPageURLException();
			}
		}

		if (Validator.isNull(author)) {
			throw new ProductEntryAuthorException();
		}

		try {
			SCProductEntry productEntry = scProductEntryPersistence.findByRG_RA(
				repoGroupId, repoArtifactId);

			if (productEntry.getProductEntryId() != productEntryId) {
				throw new DuplicateProductEntryModuleIdException();
			}
		}
		catch (NoSuchProductEntryException nspee) {
		}

		if (licenseIds.length == 0) {
			throw new ProductEntryLicenseException();
		}

		if (thumbnails.size() != fullImages.size()) {
			throw new ProductEntryScreenshotsException();
		}
		else {
			Iterator itr = thumbnails.iterator();

			while (itr.hasNext()) {
				if (itr.next() == null) {
					throw new ProductEntryScreenshotsException();
				}
			}

			itr = fullImages.iterator();

			while (itr.hasNext()) {
				if (itr.next() == null) {
					throw new ProductEntryScreenshotsException();
				}
			}
		}
	}

	private static Log _log =
		LogFactory.getLog(SCProductEntryLocalServiceImpl.class);

}