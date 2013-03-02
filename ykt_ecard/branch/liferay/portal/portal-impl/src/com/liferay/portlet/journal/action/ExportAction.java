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

package com.liferay.portlet.journal.action;

import com.liferay.counter.service.CounterLocalServiceUtil;
import com.liferay.portal.NoSuchPortletPreferencesException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.zip.ZipWriter;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.service.ImageLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.upgrade.util.IdReplacer;
import com.liferay.portal.upgrade.util.MemoryValueMapper;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portal.util.comparator.LayoutComparator;
import com.liferay.portlet.PortletPreferencesImpl;
import com.liferay.portlet.PortletPreferencesSerializer;
import com.liferay.portlet.imagegallery.NoSuchImageException;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.IGFolderLocalServiceUtil;
import com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil;
import com.liferay.portlet.journal.NoSuchArticleImageException;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalArticleImage;
import com.liferay.portlet.journal.model.JournalArticleResource;
import com.liferay.portlet.journal.model.JournalContentSearch;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.model.impl.JournalArticleImpl;
import com.liferay.portlet.journal.service.JournalArticleImageLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalStructureLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.journal.service.persistence.JournalContentSearchUtil;
import com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;
import com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalServiceUtil;
import com.liferay.util.Time;
import com.liferay.util.servlet.ServletResponseUtil;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Properties;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ExportAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ExportAction extends Action {

	public static final String COMPANY_ID = "liferay.com";

	public static final long DEFAULT_GROUP_ID = 14;

	public static final long DEFAULT_USER_ID = 2;

	public static final String DEFAULT_USER_NAME = "Joe Bloggs";

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			PermissionChecker permissionChecker =
				themeDisplay.getPermissionChecker();

			if (permissionChecker.isOmniadmin()) {
				long groupId = ParamUtil.getLong(
					req, "groupId", DEFAULT_GROUP_ID);

				_primaryKeys.clear();
				_primaryKeyCount = 1500;

				ZipWriter zipWriter = new ZipWriter();

				List journalContentSearches = new ArrayList();

				insertDataImage(groupId, zipWriter);
				insertDataCMSLayout(groupId, zipWriter, journalContentSearches);
				insertDataCMSContent(
					groupId, zipWriter, journalContentSearches);

				String fileName = "journal.zip";

				ServletResponseUtil.sendFile(res, fileName, zipWriter.finish());
			}

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

	protected void addColumn(StringMaker sm, boolean value) {
		//sm.append("'");

		if (value) {
			sm.append("TRUE");
		}
		else {
			sm.append("FALSE");
		}

		//sm.append("', ");
		sm.append(", ");
	}

	protected void addColumn(StringMaker sm, double value) {
		sm.append(value);
		sm.append(", ");
	}

	protected void addColumn(StringMaker sm, float value) {
		sm.append(value);
		sm.append(", ");
	}

	protected void addColumn(StringMaker sm, int value) {
		sm.append(value);
		sm.append(", ");
	}

	protected void addColumn(StringMaker sm, long value) {
		sm.append(value);
		sm.append(", ");
	}

	protected void addColumn(StringMaker sm, short value) {
		sm.append(value);
		sm.append(", ");
	}

	protected void addColumn(StringMaker sm, Date value) {
		addColumn(sm, value, true);
	}

	protected void addColumn(StringMaker sm, Date value, boolean current) {
		if (current) {
			sm.append("CURRENT_TIMESTAMP, ");
		}
		else {
			sm.append("SPECIFIC_TIMESTAMP_");
			sm.append(Time.getSimpleDate(value, "yyyyMMddHHmmss"));
			sm.append(", ");
		}
	}

	protected void addColumn(StringMaker sm, String value) {
		addColumn(sm, value, true);
	}

	protected void addColumn(StringMaker sm, String value, boolean format) {
		if (format) {
			value = StringUtil.replace(
				value,
				new String[] {"\\", "'", "\"", "\n", "\r"},
				new String[] {"\\\\", "\\'", "\\\"", "\\n", "\\r"});
		}

		value = GetterUtil.getString(value);

		sm.append("'");
		sm.append(value);
		sm.append("', ");
	}

	protected void addPKColumn(StringMaker sm, long value) {
		sm.append(getNewPrimaryKey(value));
		sm.append(", ");
	}

	protected void addPKColumn(StringMaker sm, String value) {
		sm.append("'");
		sm.append(getNewPrimaryKey(value));
		sm.append("', ");
	}

	protected String getNewPrimaryKey(String pk) {
		if (Validator.isNumber(pk)) {
			long pkLong = GetterUtil.getLong(pk);

			return String.valueOf(getNewPrimaryKey(pkLong));
		}
		else {
			return pk;
		}
	}

	protected long getNewPrimaryKey(long pk) {
		Long pkObj = new Long(pk);

		Long newPkObj = (Long)_primaryKeys.get(pkObj);

		if (newPkObj == null) {
			newPkObj = new Long(_primaryKeyCount);

			_primaryKeyCount++;

			_primaryKeys.put(pkObj, newPkObj);
		}

		return newPkObj.longValue();
	}

	protected void insertDataCMSContent(
			long groupId, ZipWriter zipWriter, List journalContentSearches)
		throws Exception {

		StringMaker sm = new StringMaker();

		List igImages = new ArrayList();

		Iterator itr = IGFolderLocalServiceUtil.getFolders(groupId).iterator();

		while (itr.hasNext()) {
			IGFolder folder = (IGFolder)itr.next();

			sm.append("insert into IGFolder (");
			sm.append("folderId, groupId, companyId, userId, createDate, ");
			sm.append("modifiedDate, parentFolderId, name");
			sm.append(") values (");
			addPKColumn(sm, folder.getFolderId());
			addColumn(sm, folder.getGroupId());
			addColumn(sm, folder.getCompanyId());
			//addColumn(sm, folder.getUserId());
			addColumn(sm, DEFAULT_USER_ID);
			addColumn(sm, folder.getCreateDate());
			addColumn(sm, folder.getModifiedDate());
			addColumn(sm, folder.getParentFolderId());
			addColumn(sm, folder.getName());
			removeTrailingComma(sm);
			sm.append(");\n");

			igImages.addAll(
				IGImageLocalServiceUtil.getImages(folder.getFolderId()));
		}

		sm.append("\n");

		Collections.sort(igImages);

		itr = igImages.iterator();

		while (itr.hasNext()) {
			IGImage image = (IGImage)itr.next();

			sm.append("insert into IGImage (");
			sm.append("imageId, companyId, userId, createDate, modifiedDate, ");
			sm.append("folderId, description, smallImageId, largeImageId");
			sm.append(") values (");
			addPKColumn(sm, image.getImageId());
			addColumn(sm, image.getCompanyId());
			//addColumn(sm, image.getUserId());
			addColumn(sm, DEFAULT_USER_ID);
			addColumn(sm, image.getCreateDate());
			addColumn(sm, image.getModifiedDate());
			addPKColumn(sm, image.getFolderId());
			addColumn(sm, image.getDescription());
			addPKColumn(sm, image.getSmallImageId());
			addPKColumn(sm, image.getLargeImageId());
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		sm.append("\n");

		itr = JournalArticleLocalServiceUtil.getArticles(groupId).iterator();

		while (itr.hasNext()) {
			JournalArticle article = (JournalArticle)itr.next();

			if (article.isApproved() &&
				JournalArticleLocalServiceUtil.isLatestVersion(
					article.getGroupId(), article.getArticleId(),
					article.getVersion())) {

				sm.append("insert into JournalArticle (");
				sm.append("id_, resourcePrimKey, groupId, companyId, userId, ");
				sm.append("userName, createDate, modifiedDate, articleId, ");
				sm.append("version, title, description, content, type_, ");
				sm.append("structureId, templateId, displayDate, approved, ");
				sm.append("approvedByUserId, approvedByUserName, expired, ");
				sm.append("indexable");
				sm.append(") values (");
				addPKColumn(sm, article.getId());
				addPKColumn(sm, article.getResourcePrimKey());
				addColumn(sm, article.getGroupId());
				addColumn(sm, article.getCompanyId());
				//addColumn(sm, article.getUserId());
				//addColumn(sm, article.getUserName());
				addColumn(sm, DEFAULT_USER_ID);
				addColumn(sm, DEFAULT_USER_NAME);
				addColumn(sm, article.getCreateDate());
				addColumn(sm, article.getModifiedDate());
				addPKColumn(sm, article.getArticleId());
				addColumn(sm, JournalArticleImpl.DEFAULT_VERSION);
				addColumn(sm, article.getTitle());
				addColumn(sm, article.getDescription());
				addColumn(sm, replaceIds(article.getContent()));
				addColumn(sm, article.getType());
				addPKColumn(sm, article.getStructureId());
				addPKColumn(sm, article.getTemplateId());
				addColumn(sm, article.getDisplayDate(), false);
				addColumn(sm, article.getApproved());
				//addColumn(sm, article.getApprovedByUserId());
				//addColumn(sm, article.getApprovedByUserName());
				addColumn(sm, DEFAULT_USER_ID);
				addColumn(sm, DEFAULT_USER_NAME);
				//addColumn(sm, article.getApprovedDate(), false);
				addColumn(sm, article.getExpired());
				//addColumn(sm, article.getExpirationDate(), false);
				//addColumn(sm, article.getReviewDate(), false);
				addColumn(sm, article.getIndexable());
				removeTrailingComma(sm);
				sm.append(");\n");
			}
		}

		sm.append("\n");

		itr = JournalArticleImageLocalServiceUtil.getArticleImages(
			groupId).iterator();

		while (itr.hasNext()) {
			JournalArticleImage articleImage = (JournalArticleImage)itr.next();

			sm.append("insert into JournalArticleImage (");
			sm.append("articleImageId, groupId, articleId, version, elName, ");
			sm.append("languageId, tempImage");
			sm.append(") values (");
			addPKColumn(sm, articleImage.getArticleImageId());
			addColumn(sm, articleImage.getGroupId());
			addPKColumn(sm, articleImage.getArticleId());
			addColumn(sm, articleImage.getVersion());
			addColumn(sm, articleImage.getElName());
			addColumn(sm, articleImage.getLanguageId());
			addColumn(sm, articleImage.getTempImage());
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		sm.append("\n");

		itr = JournalArticleResourceLocalServiceUtil.getArticleResources(
			groupId).iterator();

		while (itr.hasNext()) {
			JournalArticleResource articleResource =
				(JournalArticleResource)itr.next();

			sm.append("insert into JournalArticleResource (");
			sm.append("resourcePrimKey, groupId, articleId");
			sm.append(") values (");
			addPKColumn(sm, articleResource.getResourcePrimKey());
			addColumn(sm, articleResource.getGroupId());
			addPKColumn(sm, articleResource.getArticleId());
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		sm.append("\n");

		itr = journalContentSearches.iterator();

		while (itr.hasNext()) {
			JournalContentSearch contentSearch =
				(JournalContentSearch)itr.next();

			sm.append("insert into JournalContentSearch (");
			sm.append("contentSearchId, groupId, companyId, privateLayout, ");
			sm.append("layoutId, portletId, articleId");
			sm.append(") values (");
			addPKColumn(sm, contentSearch.getContentSearchId());
			addColumn(sm, contentSearch.getGroupId());
			addColumn(sm, contentSearch.getCompanyId());
			addColumn(sm, contentSearch.isPrivateLayout());
			addColumn(sm, contentSearch.getLayoutId());
			addColumn(sm, contentSearch.getPortletId());
			addPKColumn(sm, contentSearch.getArticleId());
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		sm.append("\n");

		itr = JournalStructureLocalServiceUtil.getStructures(
			groupId).iterator();

		while (itr.hasNext()) {
			JournalStructure structure = (JournalStructure)itr.next();

			sm.append("insert into JournalStructure (");
			sm.append("id_, groupId, companyId, userId, userName, ");
			sm.append("createDate, modifiedDate, structureId, name, ");
			sm.append("description, xsd");
			sm.append(") values (");
			addPKColumn(sm, structure.getId());
			addColumn(sm, structure.getGroupId());
			addColumn(sm, structure.getCompanyId());
			//addColumn(sm, structure.getUserId());
			//addColumn(sm, structure.getUserName());
			addColumn(sm, DEFAULT_USER_ID);
			addColumn(sm, DEFAULT_USER_NAME);
			addColumn(sm, structure.getCreateDate());
			addColumn(sm, structure.getModifiedDate());
			addPKColumn(sm, structure.getStructureId());
			addColumn(sm, structure.getName());
			addColumn(sm, structure.getDescription());
			addColumn(sm, replaceIds(structure.getXsd()));
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		sm.append("\n");

		itr = JournalTemplateLocalServiceUtil.getTemplates(groupId).iterator();

		while (itr.hasNext()) {
			JournalTemplate template = (JournalTemplate)itr.next();

			sm.append("insert into JournalTemplate (");
			sm.append("id_, groupId, companyId, userId, userName, ");
			sm.append("createDate, modifiedDate, templateId, structureId, ");
			sm.append("name, description, xsl, langType, smallImage, ");
			sm.append("smallImageId, smallImageURL");
			sm.append(") values (");
			addPKColumn(sm, template.getId());
			addColumn(sm, template.getGroupId());
			addColumn(sm, template.getCompanyId());
			//addColumn(sm, template.getUserId());
			//addColumn(sm, template.getUserName());
			addColumn(sm, DEFAULT_USER_ID);
			addColumn(sm, DEFAULT_USER_NAME);
			addColumn(sm, template.getCreateDate());
			addColumn(sm, template.getModifiedDate());
			addPKColumn(sm, template.getTemplateId());
			addPKColumn(sm, template.getStructureId());
			addColumn(sm, template.getName());
			addColumn(sm, template.getDescription());
			addColumn(sm, replaceIds(template.getXsl()));
			addColumn(sm, template.getLangType());
			addColumn(sm, template.getSmallImage());
			addPKColumn(sm, template.getSmallImageId());
			addColumn(sm, template.getSmallImageURL());
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		removeTrailingNewLine(sm);

		zipWriter.addEntry("portal-data-cms-content.sql", sm);
	}

	protected void insertDataCMSLayout(
			long groupId, ZipWriter zipWriter, List journalContentSearches)
		throws Exception {

		StringMaker sm = new StringMaker();

		List layouts = LayoutLocalServiceUtil.getLayouts(groupId, false);

		sm.append("update LayoutSet ");
		sm.append("set themeId = 'liferayjedi_WAR_liferayjeditheme', ");
		sm.append("pageCount = ");
		sm.append(layouts.size());
		sm.append(" where groupId = ");
		sm.append(groupId);
		sm.append(" and privateLayout = FALSE;\n\n");

		Collections.sort(layouts, new LayoutComparator(true));

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			getNewPrimaryKey(layout.getPlid());
		}

		itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			Properties props = layout.getTypeSettingsProperties();

			long linkToPlid = GetterUtil.getLong(
				props.getProperty("linkToPlid"));

			if (linkToPlid > 0) {
				long newLinkToPlid = getNewPrimaryKey(linkToPlid);

				props.setProperty("linkToPlid", String.valueOf(newLinkToPlid));
			}

			sm.append("insert into Layout (");
			sm.append("plid, groupId, companyId, privateLayout, layoutId, ");
			sm.append("parentLayoutId, name, title, type_, typeSettings, ");
			sm.append("hidden_, friendlyURL, iconImage, iconImageId, ");
			//sm.append("themeId, colorSchemeId, wapThemeId, wapColorSchemeId, ");
			sm.append("css, priority");
			sm.append(") values (");
			addPKColumn(sm, layout.getPlid());
			addColumn(sm, layout.getGroupId());
			addColumn(sm, layout.getCompanyId());
			addColumn(sm, layout.isPrivateLayout());
			addColumn(sm, layout.getLayoutId());
			addColumn(sm, layout.getParentLayoutId());
			addColumn(sm, layout.getName());
			addColumn(sm, layout.getTitle());
			addColumn(sm, layout.getType());
			addColumn(sm, layout.getTypeSettings());
			addColumn(sm, layout.isHidden());
			addColumn(sm, layout.getFriendlyURL());
			addColumn(sm, layout.isIconImage());
			addColumn(sm, layout.getIconImageId());
			//addColumn(sm, layout.getThemeId());
			//addColumn(sm, layout.getColorSchemeId());
			//addColumn(sm, layout.getWapThemeId());
			//addColumn(sm, layout.getWapColorSchemeId());
			addColumn(sm, layout.getCss());
			addColumn(sm, layout.getPriority());
			removeTrailingComma(sm);
			sm.append(");\n");
		}

		sm.append("\n");

		itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			LayoutTypePortlet layoutType =
				(LayoutTypePortlet)layout.getLayoutType();

			List portletIds = layoutType.getPortletIds();

			Collections.sort(portletIds);

			for (int i = 0; i < portletIds.size(); i++) {
				String portletId = (String)portletIds.get(i);

				try {
					PortletPreferences portletPreferences =
						PortletPreferencesLocalServiceUtil.
							getPortletPreferences(
								PortletKeys.PREFS_OWNER_ID_DEFAULT,
								PortletKeys.PREFS_OWNER_TYPE_LAYOUT,
								layout.getPlid(), portletId);

					String prefsXml = portletPreferences.getPreferences();

					PortletPreferencesImpl prefs = (PortletPreferencesImpl)
						PortletPreferencesSerializer.fromDefaultXML(
							portletPreferences.getPreferences());

					String articleId =
						prefs.getValue("article-id", StringPool.BLANK);

					articleId = articleId.toUpperCase();

					if (Validator.isNotNull(articleId)) {
						if (!JournalArticleLocalServiceUtil.hasArticle(
								layout.getGroupId(), articleId)) {

							continue;
						}

						// Make sure article id is upper case in the preferences
						// XML

						prefs.setValue(
							"article-id", getNewPrimaryKey(articleId));

						prefsXml = PortletPreferencesSerializer.toXML(prefs);

						// Add to the journal content search list

						long contentSearchId =
							CounterLocalServiceUtil.increment();

						JournalContentSearch journalContentSearch =
							JournalContentSearchUtil.create(contentSearchId);

						journalContentSearch.setContentSearchId(
							contentSearchId);
						journalContentSearch.setCompanyId(
							layout.getCompanyId());
						journalContentSearch.setGroupId(layout.getGroupId());
						journalContentSearch.setPrivateLayout(
							layout.isPrivateLayout());
						journalContentSearch.setPortletId(portletId);
						journalContentSearch.setLayoutId(layout.getLayoutId());
						journalContentSearch.setPortletId(portletId);
						journalContentSearch.setArticleId(
							getNewPrimaryKey(articleId));

						journalContentSearches.add(journalContentSearch);
					}

					sm.append("insert into PortletPreferences (");
					sm.append("portletPreferencesId, ownerId, ownerType, ");
					sm.append("plid, portletId, preferences");
					sm.append(") values (");
					addPKColumn(
						sm, portletPreferences.getPortletPreferencesId());
					addColumn(sm, portletPreferences.getOwnerId());
					addColumn(sm, portletPreferences.getOwnerType());
					addPKColumn(sm, portletPreferences.getPlid());
					addColumn(sm, portletId);
					addColumn(sm, prefsXml);
					removeTrailingComma(sm);
					sm.append(");\n");
				}
				catch (NoSuchPortletPreferencesException nsppe) {
					_log.warn(nsppe.getMessage());
				}
			}

			sm.append("\n");
		}

		removeTrailingNewLine(sm);
		removeTrailingNewLine(sm);

		zipWriter.addEntry("portal-data-cms-layout.sql", sm);
	}

	protected void insertDataImage(long groupId, ZipWriter zipWriter)
		throws Exception {

		StringMaker sm1 = new StringMaker();
		StringMaker sm2 = new StringMaker();

		Iterator itr = ImageLocalServiceUtil.getImagesBySize(70000).iterator();

		while (itr.hasNext()) {
			Image image = (Image)itr.next();

			long imageId = image.getImageId();

			try {
				UserLocalServiceUtil.getUserByPortraitId(imageId);

				continue;
			}
			catch (NoSuchUserException nsue) {
			}

			try {
				IGImage igImage =
					IGImageLocalServiceUtil.getImageBySmallImageId(imageId);

				IGFolder igFolder = igImage.getFolder();

				if (igFolder.getGroupId() != groupId) {
					continue;
				}
			}
			catch (NoSuchImageException nsie) {
			}

			try {
				IGImage igImage =
					IGImageLocalServiceUtil.getImageByLargeImageId(imageId);

				IGFolder igFolder = igImage.getFolder();

				if (igFolder.getGroupId() != groupId) {
					continue;
				}
			}
			catch (NoSuchImageException nsie) {
			}

			try {
				JournalArticleImage journalArticleImage =
					JournalArticleImageLocalServiceUtil.getArticleImage(
						imageId);

				if (journalArticleImage.getGroupId() != groupId) {
					continue;
				}
			}
			catch (NoSuchArticleImageException nsaie) {
			}

			try {
				SCProductScreenshotLocalServiceUtil.
					getProductScreenshotByFullImageId(imageId);

				continue;
			}
			catch (NoSuchProductScreenshotException nspse) {
			}

			try {
				SCProductScreenshotLocalServiceUtil.
					getProductScreenshotByThumbnailId(imageId);

				continue;
			}
			catch (NoSuchProductScreenshotException nspse) {
			}

			sm1.append("insert into Image (");
			sm1.append("imageId, modifiedDate, text_, type_, height, width, ");
			sm1.append("size_");
			sm1.append(") values (");
			addPKColumn(sm1, imageId);
			addColumn(sm1, image.getModifiedDate());
			addColumn(sm1, image.getText(), false);
			addColumn(sm1, image.getType());
			addColumn(sm1, image.getHeight());
			addColumn(sm1, image.getWidth());
			addColumn(sm1, image.getSize());
			removeTrailingComma(sm1);
			sm1.append(");\n");

			sm2.append("<img src=\"http://localhost:8080/image?img_id=");
			sm2.append(imageId);
			sm2.append("\" /><br />\n");
		}

		removeTrailingNewLine(sm1);

		zipWriter.addEntry("portal-data-image.sql", sm1);
		zipWriter.addEntry("portal-data-image.html", sm2);
	}

	protected void removeTrailingComma(StringMaker sm) {
		sm.delete(sm.length() - 2, sm.length());
	}

	protected void removeTrailingNewLine(StringMaker sm) {
		if (sm.length() > 0) {
			sm.delete(sm.length() - 1, sm.length());
		}
	}

	protected String replaceIds(String content) throws Exception {
		content = IdReplacer.replaceLongIds(content, "?img_id=", _valueMapper);

		return content;
	}

	private static Log _log = LogFactory.getLog(ExportAction.class);

	private MemoryValueMapper _valueMapper = new MemoryValueMapper();
	private Map _primaryKeys = _valueMapper.getMap();
	private int _primaryKeyCount;

}