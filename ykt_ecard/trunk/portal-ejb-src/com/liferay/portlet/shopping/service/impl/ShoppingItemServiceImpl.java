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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.amazonrankings.model.AmazonRankings;
import com.liferay.portlet.amazonrankings.util.AmazonRankingsUtil;
import com.liferay.portlet.shopping.DuplicateItemSKUException;
import com.liferay.portlet.shopping.ItemLargeImageNameException;
import com.liferay.portlet.shopping.ItemLargeImageSizeException;
import com.liferay.portlet.shopping.ItemMediumImageNameException;
import com.liferay.portlet.shopping.ItemMediumImageSizeException;
import com.liferay.portlet.shopping.ItemNameException;
import com.liferay.portlet.shopping.ItemSKUException;
import com.liferay.portlet.shopping.ItemSmallImageNameException;
import com.liferay.portlet.shopping.ItemSmallImageSizeException;
import com.liferay.portlet.shopping.NoSuchCategoryException;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemField;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCategoryServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemService;
import com.liferay.portlet.shopping.util.ItemMinQuantityComparator;
import com.liferay.portlet.shopping.util.ItemNameComparator;
import com.liferay.portlet.shopping.util.ItemPriceComparator;
import com.liferay.portlet.shopping.util.ItemSKUComparator;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.PwdGenerator;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;
import com.liferay.util.dao.hibernate.OrderByComparator;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.portlet.PortletPreferences;

/**
 * <a href="ShoppingItemServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class ShoppingItemServiceImpl
	extends PrincipalBean implements ShoppingItemService {

	// Business methods

	public void addBookItems(String categoryId, String[] isbnArray)
		throws PortalException, SystemException {

		String tmpDir = SystemProperties.get("java.io.tmpdir");

		try {
			for (int i = 0; i < isbnArray.length && i < 50; i++) {
				String isbn = isbnArray[i];

				AmazonRankings amazonRankings =
					AmazonRankingsUtil.getAmazonRankings(isbn);

				String name = amazonRankings.getProductName();
				String description = StringPool.BLANK;
				String properties = _getBookProperties(amazonRankings);
				String supplierUserId = null;

				int minQuantity = 0;
				int maxQuantity = 0;
				double price = amazonRankings.getListPrice();
				double discount = 1 - amazonRankings.getOurPrice() / price;
				boolean suggestedPrice = false;
				boolean taxable = true;
				double shipping = 0.0;
				boolean useShippingFormula = true;

				ShoppingItemPrice itemPrice = new ShoppingItemPrice(
					null, null, minQuantity, maxQuantity, price, discount,
					taxable, shipping, useShippingFormula,
					ShoppingItemPrice.STATUS_ACTIVE_DEFAULT);

				boolean requiresShipping = true;
				int stockQuantity = 0;
				boolean featured = false;
				Boolean sale = null;

				boolean smallImage = true;
				String smallImageURL = StringPool.BLANK;
				File smallFile = new File(
					tmpDir + File.separatorChar +
					PwdGenerator.getPassword(
						PwdGenerator.KEY1 + PwdGenerator.KEY2, 12) + ".jpg");
				byte[] smallBytes = Http.URLtoByteArray(
					amazonRankings.getSmallImageURL());
				if (smallBytes.length < 1024) {
					smallImage = false;
				}
				else {
					OutputStream out = new FileOutputStream(smallFile);
					out.write(smallBytes);
					out.close();
				}

				boolean mediumImage = true;
				String mediumImageURL = StringPool.BLANK;
				File mediumFile = new File(
					tmpDir + File.separatorChar +
					PwdGenerator.getPassword(
						PwdGenerator.KEY1 + PwdGenerator.KEY2, 12) + ".jpg");
				byte[] mediumBytes = Http.URLtoByteArray(
					amazonRankings.getMediumImageURL());
				if (mediumBytes.length < 1024) {
					mediumImage = false;
				}
				else {
					OutputStream out = new FileOutputStream(mediumFile);
					out.write(mediumBytes);
					out.close();
				}

				boolean largeImage = true;
				String largeImageURL = StringPool.BLANK;
				File largeFile = new File(
					tmpDir + File.separatorChar +
					PwdGenerator.getPassword(
						PwdGenerator.KEY1 + PwdGenerator.KEY2, 12) + ".jpg");
				byte[] largeBytes = Http.URLtoByteArray(
					amazonRankings.getLargeImageURL());
				if (largeBytes.length < 1024) {
					largeImage = false;
				}
				else {
					OutputStream out = new FileOutputStream(largeFile);
					out.write(largeBytes);
					out.close();
				}

				List itemFields = new ArrayList();

				List itemPrices = new ArrayList();
				itemPrices.add(itemPrice);

				addItem(
					categoryId, isbn, name, description, properties,
					supplierUserId, StringPool.BLANK, requiresShipping,
					stockQuantity, featured, sale, smallImage, smallImageURL,
					smallFile, mediumImage, mediumImageURL, mediumFile,
					largeImage, largeImageURL, largeFile, itemFields,
					itemPrices);

				smallFile.delete();
				mediumFile.delete();
				largeFile.delete();
			}
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	public ShoppingItem addItem(
			String categoryId, String sku, String name, String description,
			String properties, String supplierUserId, String fieldsQuantities,
			boolean requiresShipping, int stockQuantity, boolean featured,
			Boolean sale, boolean smallImage, String smallImageURL,
			File smallFile, boolean mediumImage, String mediumImageURL,
			File mediumFile, boolean largeImage, String largeImageURL,
			File largeFile, List itemFields, List itemPrices)
		throws PortalException, SystemException {

		User user = getUser();

		categoryId = _getCategoryId(categoryId);
		sku = sku.trim().toUpperCase();

		byte[] smallBytes = null;
		byte[] mediumBytes = null;
		byte[] largeBytes = null;
		try {
			smallBytes = FileUtil.getBytes(smallFile);
			mediumBytes = FileUtil.getBytes(mediumFile);
			largeBytes = FileUtil.getBytes(largeFile);
		}
		catch (IOException ioe) {
		}

		_validate(
			user.getCompanyId(), null, categoryId, sku, name, smallImage,
			smallImageURL, smallFile, smallBytes, mediumImage, mediumImageURL,
			mediumFile, mediumBytes, largeImage, largeImageURL, largeFile,
			largeBytes);

		if (!ShoppingCategoryServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		String itemId = Long.toString(CounterServiceUtil.increment(
			ShoppingItem.class.getName()));

		ShoppingItem item = ShoppingItemUtil.create(itemId);

		Date now = new Date();

		item.setCompanyId(user.getCompanyId());
		item.setCreateDate(now);
		item.setModifiedDate(now);
		item.setCategoryId(categoryId);
		item.setSku(sku);
		item.setName(name);
		item.setDescription(description);
		item.setProperties(properties);
		item.setSupplierUserId(supplierUserId);
		item.setFields(itemFields.size() > 0);
		item.setFieldsQuantities(fieldsQuantities);

		for (int i = 0; i < itemPrices.size(); i++) {
			ShoppingItemPrice itemPrice = (ShoppingItemPrice)itemPrices.get(i);

			if (itemPrice.getStatus() ==
					ShoppingItemPrice.STATUS_ACTIVE_DEFAULT) {

				item.setMinQuantity(itemPrice.getMinQuantity());
				item.setMaxQuantity(itemPrice.getMaxQuantity());
				item.setPrice(itemPrice.getPrice());
				item.setDiscount(itemPrice.getDiscount());
				item.setTaxable(itemPrice.getTaxable());
				item.setShipping(itemPrice.getShipping());
				item.setUseShippingFormula(
					itemPrice.getUseShippingFormula());
			}

			if ((sale == null) && (itemPrice.getDiscount() > 0) &&
				((itemPrice.getStatus() ==
					ShoppingItemPrice.STATUS_ACTIVE_DEFAULT) ||
				(itemPrice.getStatus() == ShoppingItemPrice.STATUS_ACTIVE))) {

				sale = Boolean.TRUE;
			}
		}

		item.setRequiresShipping(requiresShipping);
		item.setStockQuantity(stockQuantity);
		item.setFeatured(featured);
		item.setSale((sale != null) ? sale.booleanValue() : false);
		item.setSmallImage(smallImage);
		item.setSmallImageURL(smallImageURL);
		item.setMediumImage(mediumImage);
		item.setMediumImageURL(mediumImageURL);
		item.setLargeImage(largeImage);
		item.setLargeImageURL(largeImageURL);

		ShoppingItemUtil.update(item);

		// Save fields

		for (int i = 0; i < itemFields.size() && itemFields.size() > 0; i++) {
			ShoppingItemField itemField = (ShoppingItemField)itemFields.get(i);

			String itemFieldId = Long.toString(CounterServiceUtil.increment(
				ShoppingItemField.class.getName()));

			itemField.setItemFieldId(itemFieldId);
			itemField.setItemId(itemId);
			itemField.setName(_checkItemField(itemField.getName()));
			itemField.setValues(_checkItemField(itemField.getValues()));

			ShoppingItemFieldUtil.update(itemField);
		}

		// Save prices

		for (int i = 0; i < itemPrices.size() && itemPrices.size() > 1; i++) {
			ShoppingItemPrice itemPrice = (ShoppingItemPrice)itemPrices.get(i);

			String itemPriceId = Long.toString(CounterServiceUtil.increment(
				ShoppingItemPrice.class.getName()));

			itemPrice.setItemPriceId(itemPriceId);
			itemPrice.setItemId(itemId);

			ShoppingItemPriceUtil.update(itemPrice);
		}

		// Save images

		_saveImages(
			smallImage, item.getSmallImageId(), smallFile, smallBytes,
			mediumImage, item.getMediumImageId(), mediumFile, mediumBytes,
			largeImage, item.getLargeImageId(), largeFile, largeBytes);

		return item;
	}

	public void deleteItem(String itemId)
		throws PortalException, SystemException {

		ShoppingItem item = ShoppingItemUtil.findByPrimaryKey(itemId);

		deleteItem(item);
	}

	public void deleteItem(ShoppingItem item)
		throws PortalException, SystemException {

		String itemId = item.getPrimaryKey();

		if (!hasAdmin(itemId)) {
			throw new PrincipalException();
		}

		ShoppingItemUtil.remove(itemId);

		// Remove prices

		ShoppingItemPriceUtil.removeByItemId(itemId);

		// Remove images

		ImageLocalUtil.remove(item.getSmallImageId());
		ImageLocalUtil.remove(item.getMediumImageId());
		ImageLocalUtil.remove(item.getLargeImageId());
	}

	public List getFeaturedItems(
			String companyId, String categoryId, int numOfItems)
		throws SystemException {

		List featuredItems = ShoppingItemFinder.findByFeatured(
			companyId, new String[] {categoryId}, numOfItems);

		if (featuredItems.size() == 0) {
			List childCategories =
				ShoppingCategoryUtil.findByC_P(companyId, categoryId);

			if (childCategories.size() > 0) {
				String[] categoryIds = new String[childCategories.size()];

				for (int i = 0; i < childCategories.size(); i++) {
					ShoppingCategory childCategory =
						(ShoppingCategory)childCategories.get(i);

					categoryIds[i] = childCategory.getCategoryId();
				}

				featuredItems = ShoppingItemFinder.findByFeatured(
					companyId, categoryIds, numOfItems);
			}
		}

		return featuredItems;
	}

	public ShoppingItem getItemById(String itemId)
		throws PortalException, SystemException {

		return ShoppingItemUtil.findByPrimaryKey(itemId);
	}

	public ShoppingItem getItemBySKU(String companyId, String sku)
		throws PortalException, SystemException {

		return ShoppingItemUtil.findByC_S(companyId, sku);
	}

	public List getItems(String companyId) throws SystemException {
		return ShoppingItemUtil.findByCompanyId(companyId);
	}

	public List getItems(String companyId, String categoryId)
		throws SystemException {

		return ShoppingItemUtil.findByC_C(companyId, categoryId);
	}

	public List getItems(
			String companyId, String categoryId, int begin, int end,
			PortletPreferences prefs)
		throws SystemException {

		return ShoppingItemUtil.findByC_C(
			companyId, categoryId, begin, end, _getOrderByComparator(prefs));
	}

	public ShoppingItem[] getItemsPrevAndNext(
			String itemId, PortletPreferences prefs)
		throws PortalException, SystemException {

		ShoppingItem item = ShoppingItemUtil.findByPrimaryKey(itemId);

		return ShoppingItemUtil.findByC_C_PrevAndNext(
			item.getItemId(), item.getCompanyId(), item.getCategoryId(),
			_getOrderByComparator(prefs));
	}

	public int getItemsSize(String companyId) throws SystemException {
		return ShoppingItemUtil.countByCompanyId(companyId);
	}

	public int getItemsSize(String companyId, String categoryId)
		throws SystemException {

		return ShoppingItemUtil.countByC_C(companyId, categoryId);
	}

	public List getSaleItems(
			String companyId, String categoryId, int numOfItems)
		throws SystemException {

		List saleItems = ShoppingItemFinder.findBySale(
			companyId, new String[] {categoryId}, numOfItems);

		if (saleItems.size() == 0) {
			List childCategories =
				ShoppingCategoryUtil.findByC_P(companyId, categoryId);

			if (childCategories.size() > 0) {
				String[] categoryIds = new String[childCategories.size()];

				for (int i = 0; i < childCategories.size(); i++) {
					ShoppingCategory childCategory =
						(ShoppingCategory)childCategories.get(i);

					categoryIds[i] = childCategory.getCategoryId();
				}

				saleItems = ShoppingItemFinder.findBySale(
					companyId, categoryIds, numOfItems);
			}
		}

		return saleItems;
	}

	public List search(
			String companyId, String[] categoryIds, String keywords, int begin,
			int end)
		throws SystemException {

		List recursiveCategoryIds = new ArrayList();

		_getRecursiveCategoryIds(recursiveCategoryIds, companyId, categoryIds);

		return ShoppingItemFinder.findByKeywords(
			companyId, (String[])recursiveCategoryIds.toArray(new String[0]),
			keywords, begin, end);
	}

	public int searchSize(
			String companyId, String[] categoryIds, String keywords)
		throws SystemException {

		List recursiveCategoryIds = new ArrayList();

		_getRecursiveCategoryIds(recursiveCategoryIds, companyId, categoryIds);

		return ShoppingItemFinder.countByKeywords(
			companyId, (String[])recursiveCategoryIds.toArray(new String[0]),
			keywords);
	}

	public ShoppingItem updateItem(
			String itemId, String categoryId, String sku, String name,
			String description, String properties, String supplierUserId,
			String fieldsQuantities, boolean requiresShipping,
			int stockQuantity, boolean featured, Boolean sale,
			boolean smallImage, String smallImageURL, File smallFile,
			boolean mediumImage, String mediumImageURL, File mediumFile,
			boolean largeImage, String largeImageURL, File largeFile,
			List itemFields, List itemPrices)
		throws PortalException, SystemException {

		User user = getUser();

		categoryId = _getCategoryId(categoryId);
		sku = sku.trim().toUpperCase();

		byte[] smallBytes = null;
		byte[] mediumBytes = null;
		byte[] largeBytes = null;
		try {
			smallBytes = FileUtil.getBytes(smallFile);
			mediumBytes = FileUtil.getBytes(mediumFile);
			largeBytes = FileUtil.getBytes(largeFile);
		}
		catch (IOException ioe) {
		}

		_validate(
			user.getCompanyId(), itemId, categoryId, sku, name, smallImage,
			smallImageURL, smallFile, smallBytes, mediumImage, mediumImageURL,
			mediumFile, mediumBytes, largeImage, largeImageURL, largeFile,
			largeBytes);

		if (!hasAdmin(itemId)) {
			throw new PrincipalException();
		}

		ShoppingItem item = ShoppingItemUtil.findByPrimaryKey(itemId);

		item.setModifiedDate(new Date());
		item.setCategoryId(categoryId);
		item.setSku(sku);
		item.setName(name);
		item.setDescription(description);
		item.setProperties(properties);
		item.setSupplierUserId(supplierUserId);
		item.setFields(itemFields.size() > 0);
		item.setFieldsQuantities(fieldsQuantities);

		for (int i = 0; i < itemPrices.size(); i++) {
			ShoppingItemPrice itemPrice = (ShoppingItemPrice)itemPrices.get(i);

			if (itemPrice.getStatus() ==
					ShoppingItemPrice.STATUS_ACTIVE_DEFAULT) {

				item.setMinQuantity(itemPrice.getMinQuantity());
				item.setMaxQuantity(itemPrice.getMaxQuantity());
				item.setPrice(itemPrice.getPrice());
				item.setDiscount(itemPrice.getDiscount());
				item.setTaxable(itemPrice.getTaxable());
				item.setShipping(itemPrice.getShipping());
				item.setUseShippingFormula(
					itemPrice.getUseShippingFormula());
			}

			if ((sale == null) && (itemPrice.getDiscount() > 0) &&
				((itemPrice.getStatus() ==
					ShoppingItemPrice.STATUS_ACTIVE_DEFAULT) ||
				(itemPrice.getStatus() == ShoppingItemPrice.STATUS_ACTIVE))) {

				sale = Boolean.TRUE;
			}
		}

		item.setRequiresShipping(requiresShipping);
		item.setStockQuantity(stockQuantity);
		item.setFeatured(featured);
		item.setSale((sale != null) ? sale.booleanValue() : false);
		item.setSmallImage(smallImage);
		item.setSmallImageURL(smallImageURL);
		item.setMediumImage(mediumImage);
		item.setMediumImageURL(mediumImageURL);
		item.setLargeImage(largeImage);
		item.setLargeImageURL(largeImageURL);

		ShoppingItemUtil.update(item);

		// Save fields

		ShoppingItemFieldUtil.removeByItemId(itemId);

		for (int i = 0; i < itemFields.size() && itemFields.size() > 0; i++) {
			ShoppingItemField itemField = (ShoppingItemField)itemFields.get(i);

			String itemFieldId = Long.toString(CounterServiceUtil.increment(
				ShoppingItemField.class.getName()));

			itemField.setItemFieldId(itemFieldId);
			itemField.setItemId(itemId);
			itemField.setName(_checkItemField(itemField.getName()));
			itemField.setValues(_checkItemField(itemField.getValues()));

			ShoppingItemFieldUtil.update(itemField);
		}

		// Save prices

		ShoppingItemPriceUtil.removeByItemId(itemId);

		for (int i = 0; i < itemPrices.size() && itemPrices.size() > 1; i++) {
			ShoppingItemPrice itemPrice = (ShoppingItemPrice)itemPrices.get(i);

			String itemPriceId = Long.toString(CounterServiceUtil.increment(
				ShoppingItemPrice.class.getName()));

			itemPrice.setItemPriceId(itemPriceId);
			itemPrice.setItemId(itemId);

			ShoppingItemPriceUtil.update(itemPrice);
		}

		// Save images

		_saveImages(
			smallImage, item.getSmallImageId(), smallFile, smallBytes,
			mediumImage, item.getMediumImageId(), mediumFile, mediumBytes,
			largeImage, item.getLargeImageId(), largeFile, largeBytes);

		return item;
	}

	// Permission methods

	public boolean hasAdmin(String itemId)
		throws PortalException, SystemException {

		ShoppingItem item = ShoppingItemUtil.findByPrimaryKey(itemId);

		if (getUser().getCompanyId().equals(item.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.SHOPPING_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private String _checkItemField(String value) {
		return StringUtil.replace(
			value,
			new String[] {
				"\"", "&", "'", ".", "=", "|"
			},
			new String[] {
				StringPool.BLANK,
				StringPool.BLANK,
				StringPool.BLANK,
				StringPool.BLANK,
				StringPool.BLANK,
				StringPool.BLANK
			}
		);
	}

	private String _getBookProperties(AmazonRankings amazonRankings) {
		String isbn = amazonRankings.getISBN();

		String authors = StringUtil.merge(amazonRankings.getAuthors(), ", ");

		String publisher =
			amazonRankings.getManufacturer() + "; (" +
			amazonRankings.getReleaseDateAsString() + ")";

		String properties =
			"ISBN=" + isbn + "\nAuthor=" + authors + "\nPublisher=" + publisher;

		return properties;
	}

	private String _getCategoryId(String categoryId)
		throws PortalException, SystemException {

		if (!categoryId.equals(ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID)) {

			// Ensure category exists and belongs to the proper company

			try {
				ShoppingCategory category =
					ShoppingCategoryUtil.findByPrimaryKey(categoryId);

				if (!category.getCompanyId().equals(getUser().getCompanyId())) {
					categoryId =
						ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID;
				}
			}
			catch (NoSuchCategoryException nsce) {
				categoryId = ShoppingCategory.DEFAULT_PARENT_CATEGORY_ID;
			}
		}

		return categoryId;
	}

	private OrderByComparator _getOrderByComparator(PortletPreferences prefs) {
		String orderByCol = prefs.getValue("order-by-col", StringPool.BLANK);
		String orderByType = prefs.getValue("order-by-type", StringPool.BLANK);

		if (orderByCol.equals("s")) {
			if (orderByType.equals("asc")) {
				return new ItemSKUComparator(true);
			}
			else {
				return new ItemSKUComparator(false);
			}
		}
		else if (orderByCol.equals("n")) {
			if (orderByType.equals("desc")) {
				return new ItemNameComparator(false);
			}
		}
		else if (orderByCol.equals("min")) {
			if (orderByType.equals("asc")) {
				return new ItemMinQuantityComparator(true);
			}
			else {
				return new ItemMinQuantityComparator(false);
			}
		}
		else if (orderByCol.equals("p")) {
			if (orderByType.equals("asc")) {
				return new ItemPriceComparator(true);
			}
			else {
				return new ItemPriceComparator(false);
			}
		}

		return new ItemNameComparator(true);
	}

	private void _getRecursiveCategoryIds(
			List recursiveCategoryIds, String companyId, String[] categoryIds)
		throws SystemException {

		for (int i = 0; i < categoryIds.length; i++) {
			recursiveCategoryIds.add(categoryIds[i]);

			List childCategories =
				ShoppingCategoryUtil.findByC_P(companyId, categoryIds[i]);

			String[] childCategoryIds = new String[childCategories.size()];

			for (int j = 0; j < childCategories.size(); j++) {
				ShoppingCategory childCategory =
					(ShoppingCategory)childCategories.get(j);

				childCategoryIds[j] = childCategory.getCategoryId();
			}

			_getRecursiveCategoryIds(
				recursiveCategoryIds, companyId, childCategoryIds);
		}
	}

	private void _saveImages(
		boolean smallImage, String smallImageKey, File smallFile,
		byte[] smallBytes, boolean mediumImage, String mediumImageKey,
		File mediumFile, byte[] mediumBytes, boolean largeImage,
		String largeImageKey, File largeFile, byte[] largeBytes) {

		// Save small image

		if (smallImage) {
			if (smallFile != null && smallBytes != null) {
				ImageLocalUtil.put(smallImageKey, smallBytes);
			}
		}
		else {
			ImageLocalUtil.remove(smallImageKey);
		}

		// Save medium image

		if (mediumImage) {
			if (mediumFile != null && mediumBytes != null) {
				ImageLocalUtil.put(mediumImageKey, mediumBytes);
			}
		}
		else {
			ImageLocalUtil.remove(mediumImageKey);
		}

		// Save large image

		if (largeImage) {
			if (largeFile != null && largeBytes != null) {
				ImageLocalUtil.put(largeImageKey, largeBytes);
			}
		}
		else {
			ImageLocalUtil.remove(largeImageKey);
		}
	}

	private void _validate(
			String companyId, String itemId, String categoryId, String sku,
			String name, boolean smallImage, String smallImageURL,
			File smallFile, byte[] smallBytes, boolean mediumImage,
			String mediumImageURL, File mediumFile, byte[] mediumBytes,
			boolean largeImage, String largeImageURL, File largeFile,
			byte[] largeBytes)
		throws PortalException, SystemException {

		if (Validator.isNull(sku)) {
			throw new ItemSKUException();
		}

		try {
			ShoppingItem item = ShoppingItemUtil.findByC_S(companyId, sku);

			if (itemId != null) {
				if (!item.getItemId().equals(itemId)) {
					throw new DuplicateItemSKUException();
				}
			}
			else {
				throw new DuplicateItemSKUException();
			}
		}
		catch (NoSuchItemException nsie) {
		}

		ShoppingCategory category =
			ShoppingCategoryUtil.findByPrimaryKey(categoryId);

		if (Validator.isNull(name)) {
			throw new ItemNameException();
		}

		String[] imageExtensions =
			PropsUtil.getArray(PropsUtil.SHOPPING_IMAGE_EXTENSIONS);

		// Small image

		if (smallImage && Validator.isNull(smallImageURL) &&
			smallFile != null && smallBytes != null) {

			String smallImageName = smallFile.getName();

			if (smallImageName != null) {
				boolean validSmallImageExtension = false;

				for (int i = 0; i < imageExtensions.length; i++) {
					if (StringPool.STAR.equals(imageExtensions[i]) ||
						StringUtil.endsWith(
							smallImageName, imageExtensions[i])) {

						validSmallImageExtension = true;

						break;
					}
				}

				if (!validSmallImageExtension) {
					throw new ItemSmallImageNameException(smallImageName);
				}
			}

			long smallImageMaxSize = GetterUtil.getLong(
				PropsUtil.get(PropsUtil.SHOPPING_IMAGE_SMALL_MAX_SIZE));

			if ((smallImageMaxSize > 0) &&
				((smallBytes == null) ||
					(smallBytes.length > smallImageMaxSize))) {

				throw new ItemSmallImageSizeException();
			}
		}

		// Medium image

		if (mediumImage && Validator.isNull(mediumImageURL) &&
			mediumFile != null && mediumBytes != null) {

			String mediumImageName = mediumFile.getName();

			if (mediumImageName != null) {
				boolean validMediumImageExtension = false;

				for (int i = 0; i < imageExtensions.length; i++) {
					if (StringPool.STAR.equals(imageExtensions[i]) ||
						StringUtil.endsWith(
							mediumImageName, imageExtensions[i])) {

						validMediumImageExtension = true;

						break;
					}
				}

				if (!validMediumImageExtension) {
					throw new ItemMediumImageNameException(mediumImageName);
				}
			}

			long mediumImageMaxSize = GetterUtil.getLong(
				PropsUtil.get(PropsUtil.SHOPPING_IMAGE_MEDIUM_MAX_SIZE));

			if ((mediumImageMaxSize > 0) &&
				((mediumBytes == null) ||
					(mediumBytes.length > mediumImageMaxSize))) {

				throw new ItemMediumImageSizeException();
			}
		}

		// Large image

		if (largeImage && Validator.isNull(largeImageURL) &&
			largeFile != null && largeBytes != null) {

			String largeImageName = largeFile.getName();

			if (largeImageName != null) {
				boolean validLargeImageExtension = false;

				for (int i = 0; i < imageExtensions.length; i++) {
					if (StringPool.STAR.equals(imageExtensions[i]) ||
						StringUtil.endsWith(
							largeImageName, imageExtensions[i])) {

						validLargeImageExtension = true;

						break;
					}
				}

				if (!validLargeImageExtension) {
					throw new ItemLargeImageNameException(largeImageName);
				}
			}

			long largeImageMaxSize = GetterUtil.getLong(
				PropsUtil.get(PropsUtil.SHOPPING_IMAGE_LARGE_MAX_SIZE));

			if ((largeImageMaxSize > 0) &&
				((largeBytes == null) ||
					(largeBytes.length > largeImageMaxSize))) {

				throw new ItemLargeImageSizeException();
			}
		}
	}

}