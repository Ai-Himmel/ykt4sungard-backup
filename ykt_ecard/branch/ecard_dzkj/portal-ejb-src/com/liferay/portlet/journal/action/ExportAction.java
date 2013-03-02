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

package com.liferay.portlet.journal.action;

import com.liferay.portal.NoSuchPortletPreferencesException;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.service.persistence.PortletPreferencesPK;
import com.liferay.portal.service.spring.ImageServiceUtil;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.service.spring.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.LayoutComparator;
import com.liferay.portal.util.OmniadminUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.spring.IGFolderServiceUtil;
import com.liferay.portlet.imagegallery.service.spring.IGImageServiceUtil;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.spring.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalStructureLocalServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.spring.ShoppingCategoryServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemServiceUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.servlet.ServletResponseUtil;
import com.liferay.util.zip.ZipCollection;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

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
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.19 $
 *
 */
public class ExportAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			if (OmniadminUtil.isOmniadmin(req.getRemoteUser())) {
				String fileName = "journal.zip";

				ZipCollection zipCol = new ZipCollection();

				_insertDataCMSContent(zipCol);
				_insertDataCMSLayout(zipCol);
				_insertDataImage(zipCol);
				_insertDataShopping(zipCol);

				ServletResponseUtil.sendFile(res, fileName, zipCol.finish());
			}

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

	private void _addColumn(FastStringBuffer sb, boolean value) {
		sb.append("'");

		if (value) {
			sb.append("TRUE");
		}
		else {
			sb.append("FALSE");
		}

		sb.append("', ");
	}

	private void _addColumn(FastStringBuffer sb, double value) {
		sb.append(value);
		sb.append(", ");
	}

	private void _addColumn(FastStringBuffer sb, Date value) {
		sb.append("CURRENT_TIMESTAMP, ");
	}

	private void _addColumn(FastStringBuffer sb, String value) {
		_addColumn(sb, value, true);
	}

	private void _addColumn(FastStringBuffer sb, String value, boolean format) {
		if (format) {
			value = StringUtil.replace(
				value,
				new String[] {"\\", "'", "\"", "\n", "\r"},
				new String[] {"\\\\", "\\'", "\\\"", "\\n", "\\r"});
		}

		value = GetterUtil.getString(value);

		sb.append("'");
		sb.append(value);
		sb.append("', ");
	}

	private void _insertDataCMSContent(ZipCollection zipCol) throws Exception {
		FastStringBuffer sb = new FastStringBuffer();

		List igImages = new ArrayList();

		Iterator itr = IGFolderServiceUtil.getFolders(
			_CMS_GROUP_ID, _COMPANY_ID).iterator();

		while (itr.hasNext()) {
			IGFolder folder = (IGFolder)itr.next();

			sb.append("insert into IGFolder (");
			sb.append("folderId, groupId, companyId, userId, createDate, ");
			sb.append("modifiedDate, parentFolderId, name");
			sb.append(") values (");
			_addColumn(sb, folder.getFolderId());
			_addColumn(sb, folder.getGroupId());
			_addColumn(sb, folder.getCompanyId());
			_addColumn(sb, folder.getUserId());
			_addColumn(sb, folder.getCreateDate());
			_addColumn(sb, folder.getModifiedDate());
			_addColumn(sb, folder.getParentFolderId());
			_addColumn(sb, folder.getName());
			_removeTrailingComma(sb);
			sb.append(");\n");

			igImages.addAll(IGImageServiceUtil.getImages(folder));
		}

		sb.append("\n");

		Collections.sort(igImages);

		itr = igImages.iterator();

		while (itr.hasNext()) {
			IGImage image = (IGImage)itr.next();

			sb.append("insert into IGImage (");
			sb.append("imageId, companyId, userId, createDate, modifiedDate, ");
			sb.append("folderId, description, height, width, size_");
			sb.append(") values (");
			_addColumn(sb, image.getImageId());
			_addColumn(sb, image.getCompanyId());
			_addColumn(sb, image.getUserId());
			_addColumn(sb, image.getCreateDate());
			_addColumn(sb, image.getModifiedDate());
			_addColumn(sb, image.getFolderId());
			_addColumn(sb, image.getDescription());
			_addColumn(sb, image.getHeight());
			_addColumn(sb, image.getWidth());
			_addColumn(sb, image.getSize());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		sb.append("\n");

		itr = JournalArticleLocalServiceUtil.getArticles(
			PortletKeys.JOURNAL, _CMS_GROUP_ID, _COMPANY_ID).iterator();

		while (itr.hasNext()) {
			JournalArticle article = (JournalArticle)itr.next();

			sb.append("insert into JournalArticle (");
			sb.append("articleId, version, portletId, groupId, companyId, ");
			sb.append("userId, userName, createDate, modifiedDate, title, ");
			sb.append("content, type_, structureId, templateId, displayDate, ");
			sb.append("approved, approvedByUserId, approvedByUserName");
			sb.append(") values (");
			_addColumn(sb, article.getArticleId());
			_addColumn(sb, article.getVersion());
			_addColumn(sb, article.getPortletId());
			_addColumn(sb, article.getGroupId());
			_addColumn(sb, article.getCompanyId());
			_addColumn(sb, article.getUserId());
			_addColumn(sb, article.getUserName());
			_addColumn(sb, article.getCreateDate());
			_addColumn(sb, article.getModifiedDate());
			_addColumn(sb, article.getTitle());
			_addColumn(sb, article.getContent());
			_addColumn(sb, article.getType());
			_addColumn(sb, article.getStructureId());
			_addColumn(sb, article.getTemplateId());
			_addColumn(sb, article.getDisplayDate());
			_addColumn(sb, article.getApproved());
			_addColumn(sb, article.getApprovedByUserId());
			_addColumn(sb, article.getApprovedByUserName());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		sb.append("\n");

		itr = JournalStructureLocalServiceUtil.getStructures(
			PortletKeys.JOURNAL, _CMS_GROUP_ID, _COMPANY_ID).iterator();

		while (itr.hasNext()) {
			JournalStructure structure = (JournalStructure)itr.next();

			sb.append("insert into JournalStructure (");
			sb.append("structureId, portletId, groupId, companyId, userId, ");
			sb.append("userName, createDate, modifiedDate, name, ");
			sb.append("description, xsd");
			sb.append(") values (");
			_addColumn(sb, structure.getStructureId());
			_addColumn(sb, structure.getPortletId());
			_addColumn(sb, structure.getGroupId());
			_addColumn(sb, structure.getCompanyId());
			_addColumn(sb, structure.getUserId());
			_addColumn(sb, structure.getUserName());
			_addColumn(sb, structure.getCreateDate());
			_addColumn(sb, structure.getModifiedDate());
			_addColumn(sb, structure.getName());
			_addColumn(sb, structure.getDescription());
			_addColumn(sb, structure.getXsd());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		sb.append("\n");

		itr = JournalTemplateLocalServiceUtil.getTemplates(
			PortletKeys.JOURNAL, _CMS_GROUP_ID, _COMPANY_ID).iterator();

		while (itr.hasNext()) {
			JournalTemplate template = (JournalTemplate)itr.next();

			sb.append("insert into JournalTemplate (");
			sb.append("templateId, portletId, groupId, companyId, userId, ");
			sb.append("userName, createDate, modifiedDate, structureId, ");
			sb.append("name, description, xsl, smallImage, smallImageURL");
			sb.append(") values (");
			_addColumn(sb, template.getTemplateId());
			_addColumn(sb, template.getPortletId());
			_addColumn(sb, template.getGroupId());
			_addColumn(sb, template.getCompanyId());
			_addColumn(sb, template.getUserId());
			_addColumn(sb, template.getUserName());
			_addColumn(sb, template.getCreateDate());
			_addColumn(sb, template.getModifiedDate());
			_addColumn(sb, template.getStructureId());
			_addColumn(sb, template.getName());
			_addColumn(sb, template.getDescription());
			_addColumn(sb, template.getXsl());
			_addColumn(sb, template.getSmallImage());
			_addColumn(sb, template.getSmallImageURL());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		_removeTrailingNewLine(sb);

		zipCol.addEntry("portal-data-cms-content.sql", sb);
	}

	private void _insertDataCMSLayout(ZipCollection zipCol) throws Exception {
		FastStringBuffer sb = new FastStringBuffer();

		List layouts = LayoutLocalServiceUtil.getLayouts(
			Layout.GROUP + _GENERAL_GUEST_GROUP_ID);

		Collections.sort(layouts, new LayoutComparator(true));

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			sb.append("insert into Layout (");
			sb.append("layoutId, userId, companyId, parentLayoutId, name, ");
			sb.append("type_, typeSettings, friendlyURL, priority");
			sb.append(") values (");
			_addColumn(sb, layout.getLayoutId());
			_addColumn(sb, layout.getUserId());
			_addColumn(sb, layout.getCompanyId());
			_addColumn(sb, layout.getParentLayoutId());
			_addColumn(sb, layout.getName());
			_addColumn(sb, layout.getType());
			_addColumn(sb, layout.getTypeSettings());
			_addColumn(sb, layout.getFriendlyURL());
			_addColumn(sb, layout.getPriority());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		sb.append("\n");

		itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			LayoutTypePortlet layoutType =
				(LayoutTypePortlet)layout.getLayoutType();

			String[] portletIds = layoutType.getPortletIds();

			Arrays.sort(portletIds);

			for (int i = 0; i < portletIds.length; i++) {
				PortletPreferencesPK pk = new PortletPreferencesPK(
					portletIds[i], layout.getLayoutId(), layout.getUserId());

				try {
					PortletPreferences portletPreferences =
						PortletPreferencesLocalServiceUtil.
							getPortletPreferences(pk);

					sb.append("insert into PortletPreferences (");
					sb.append("portletId, userId, layoutId, preferences");
					sb.append(") values (");
					_addColumn(sb, portletPreferences.getPortletId());
					_addColumn(sb, portletPreferences.getUserId());
					_addColumn(sb, portletPreferences.getLayoutId());
					_addColumn(sb, portletPreferences.getPreferences());
					_removeTrailingComma(sb);
					sb.append(");\n");
				}
				catch (NoSuchPortletPreferencesException nsppe) {
					_log.warn(nsppe.getMessage());
				}
			}

			sb.append("\n");
		}

		_removeTrailingNewLine(sb);
		_removeTrailingNewLine(sb);

		zipCol.addEntry("portal-data-cms-layout.sql", sb);
	}

	private void _insertDataImage(ZipCollection zipCol) throws Exception {
		FastStringBuffer sb = new FastStringBuffer();

		Iterator itr = ImageServiceUtil.getImageById(
			_COMPANY_ID + "%").iterator();

		while (itr.hasNext()) {
			Image image = (Image)itr.next();

			String imageId = image.getImageId();

			boolean insert = true;

			if ((imageId.indexOf(".shopping.item.") != -1) &&
					imageId.endsWith(".large")) {

				insert = false;
			}

			if (insert) {
				sb.append("insert into Image (");
				sb.append("imageId, modifiedDate, text_");
				sb.append(") values (");
				_addColumn(sb, image.getImageId());
				_addColumn(sb, image.getModifiedDate());
				_addColumn(sb, image.getText(), false);
				_removeTrailingComma(sb);
				sb.append(");\n");
			}
		}

		_removeTrailingNewLine(sb);

		zipCol.addEntry("portal-data-image.sql", sb);
	}

	private void _insertDataShopping(ZipCollection zipCol) throws Exception {
		FastStringBuffer sb = new FastStringBuffer();

		Iterator itr = ShoppingCategoryServiceUtil.getCategories(
			_COMPANY_ID).iterator();

		while (itr.hasNext()) {
			ShoppingCategory category = (ShoppingCategory)itr.next();

			sb.append("insert into ShoppingCategory (");
			sb.append("categoryId, companyId, createDate, modifiedDate, ");
			sb.append("parentCategoryId, name");
			sb.append(") values (");
			_addColumn(sb, category.getCategoryId());
			_addColumn(sb, category.getCompanyId());
			_addColumn(sb, category.getCreateDate());
			_addColumn(sb, category.getModifiedDate());
			_addColumn(sb, category.getParentCategoryId());
			_addColumn(sb, category.getName());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		sb.append("\n");

		itr = ShoppingItemServiceUtil.getItems(_COMPANY_ID).iterator();

		while (itr.hasNext()) {
			ShoppingItem item = (ShoppingItem)itr.next();

			sb.append("insert into ShoppingItem (");
			sb.append("itemId, companyId, createDate, modifiedDate, ");
			sb.append("categoryId, sku, name, description, properties, ");
			sb.append("supplierUserId, fields_, fieldsQuantities, ");
			sb.append("minQuantity, maxQuantity, price, discount, taxable, ");
			sb.append("shipping, useShippingFormula, requiresShipping, ");
			sb.append("stockQuantity, featured_, sale_, smallImage, ");
			sb.append("smallImageURL, mediumImage, mediumImageURL, ");
			sb.append("largeImage, largeImageURL");
			sb.append(") values (");
			_addColumn(sb, item.getItemId());
			_addColumn(sb, item.getCompanyId());
			_addColumn(sb, item.getCreateDate());
			_addColumn(sb, item.getModifiedDate());
			_addColumn(sb, item.getCategoryId());
			_addColumn(sb, item.getSku());
			_addColumn(sb, item.getName());
			_addColumn(sb, item.getDescription());
			_addColumn(sb, item.getProperties());
			_addColumn(sb, item.getSupplierUserId());
			_addColumn(sb, item.getFields());
			_addColumn(sb, item.getFieldsQuantities());
			_addColumn(sb, item.getMinQuantity());
			_addColumn(sb, item.getMaxQuantity());
			_addColumn(sb, item.getPrice());
			_addColumn(sb, item.getDiscount());
			_addColumn(sb, item.getTaxable());
			_addColumn(sb, item.getShipping());
			_addColumn(sb, item.getUseShippingFormula());
			_addColumn(sb, item.getRequiresShipping());
			_addColumn(sb, item.getStockQuantity());
			_addColumn(sb, item.getFeatured());
			_addColumn(sb, item.getSale());
			_addColumn(sb, item.getSmallImage());
			_addColumn(sb, item.getSmallImageURL());
			_addColumn(sb, item.getMediumImage());
			_addColumn(sb, item.getMediumImageURL());
			//_addColumn(sb, item.getLargeImage());
			_addColumn(sb, false);
			_addColumn(sb, item.getLargeImageURL());
			_removeTrailingComma(sb);
			sb.append(");\n");
		}

		_removeTrailingNewLine(sb);

		zipCol.addEntry("portal-data-shopping.sql", sb);
	}

	public void _removeTrailingComma(FastStringBuffer sb) {
		sb.delete(sb.length() - 2, sb.length());
	}

	public void _removeTrailingNewLine(FastStringBuffer sb) {
		if (sb.length() > 0) {
			sb.delete(sb.length() - 1, sb.length());
		}
	}

	private static final Log _log = LogFactory.getLog(ExportAction.class);

	private static final String _COMPANY_ID = "liferay.com";
	private static final String _GENERAL_GUEST_GROUP_ID = "1";
	private static final String _CMS_GROUP_ID = "3";

}