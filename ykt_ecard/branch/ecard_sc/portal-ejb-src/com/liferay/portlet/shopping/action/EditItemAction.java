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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.ActionResponseImpl;
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
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemField;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.service.spring.ShoppingItemServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.util.ArrayList;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletURL;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditItemAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class EditItemAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				ActionUtil.getItem(req);

				_updateItem(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof DuplicateItemSKUException ||
					e instanceof ItemLargeImageNameException ||
					e instanceof ItemLargeImageSizeException ||
					e instanceof ItemMediumImageNameException ||
					e instanceof ItemMediumImageSizeException ||
					e instanceof ItemNameException ||
					e instanceof ItemSKUException ||
					e instanceof ItemSmallImageNameException ||
					e instanceof ItemSmallImageSizeException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.edit_item");
				}
				else if (e != null &&
						 e instanceof NoSuchCategoryException ||
						 e instanceof NoSuchItemException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteItem(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchItemException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				ActionUtil.getItem(req);

				setForward(req, "portlet.shopping.edit_item");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchItemException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.shopping.edit_item");
		}
	}

	private void _deleteItem(ActionRequest req, ActionResponse res)
		throws Exception {

		String itemId = ParamUtil.getString(req, "item_id");

		ShoppingItemServiceUtil.deleteItem(itemId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateItem(ActionRequest req, ActionResponse res)
		throws Exception {

		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		String itemId = ParamUtil.getString(uploadReq, "item_id");

		String categoryId = ParamUtil.getString(uploadReq, "category_id");
		String sku = ParamUtil.getString(uploadReq, "item_sku");
		String name = ParamUtil.getString(uploadReq, "item_name");
		String description = ParamUtil.getString(uploadReq, "item_desc");
		String properties = ParamUtil.getString(uploadReq, "item_props");
		String supplierUserId = ParamUtil.getString(
			uploadReq, "item_supplier_user_id");

		int numberOfFields = ParamUtil.get(uploadReq, "n_of_fields", 1);

		List itemFields = new ArrayList();

		for (int i = 0; i < numberOfFields; i ++) {
			String fieldName = ParamUtil.getString(
				uploadReq, "item_" + i + "_field_name");
			String fieldValues = ParamUtil.getString(
				uploadReq, "item_" + i + "_field_values");
			String fieldDescription = ParamUtil.getString(
				uploadReq, "item_" + i + "_field_desc");

			ShoppingItemField itemField = new ShoppingItemField(
				null, null, fieldName, fieldValues, fieldDescription);

			itemFields.add(itemField);
		}

		String fieldsQuantities = ParamUtil.getString(
			uploadReq, "item_fields_quantities");

		int numberOfPrices = ParamUtil.get(uploadReq, "n_of_prices", 1);

		List itemPrices = new ArrayList();

		for (int i = 0; i < numberOfPrices; i ++) {
			int minQuantity = ParamUtil.get(
				uploadReq, "item_" + i + "_min_quantity", 0);
			int maxQuantity = ParamUtil.get(
				uploadReq, "item_" + i + "_max_quantity", 0);
			double price = ParamUtil.get(
				uploadReq, "item_" + i + "_price", 0.0);
			double discount = ParamUtil.get(
				uploadReq, "item_" + i + "_discount", 0.0) / 100;
			boolean taxable = ParamUtil.get(
				uploadReq, "item_" + i + "_taxable", false);
			double shipping = ParamUtil.get(
				uploadReq, "item_" + i + "_shipping", 0.0);
			boolean useShippingFormula = ParamUtil.get(
				uploadReq, "item_" + i + "_u_s_f", false);
			boolean active = ParamUtil.get(
				uploadReq, "item_" + i + "_active", false);
			int defaultPrice = ParamUtil.get(
				uploadReq, "item_default_price", 0);

			int status = ShoppingItemPrice.STATUS_ACTIVE_DEFAULT;
			if (defaultPrice != i && active) {
				status = ShoppingItemPrice.STATUS_ACTIVE;
			}
			else if (defaultPrice != i && !active) {
				status = ShoppingItemPrice.STATUS_INACTIVE;
			}

			ShoppingItemPrice itemPrice = new ShoppingItemPrice(
				null, null, minQuantity, maxQuantity, price, discount,
				taxable, shipping, useShippingFormula, status);

			itemPrices.add(itemPrice);
		}

		boolean requiresShipping = ParamUtil.get(uploadReq, "item_r_s", true);
		int stockQuantity = ParamUtil.get(uploadReq, "item_stock_quantity", 0);

		boolean featured = ParamUtil.get(uploadReq, "item_featured", true);
		Boolean sale = null;

		boolean smallImage = ParamUtil.get(
			uploadReq, "item_small_image", false);
		String smallImageURL = ParamUtil.getString(
			uploadReq, "item_small_image_url");
		File smallFile = uploadReq.getFile("item_small_i");

		boolean mediumImage = ParamUtil.get(
			uploadReq, "item_medium_image", false);
		String mediumImageURL = ParamUtil.getString(
			uploadReq, "item_medium_image_url");
		File mediumFile = uploadReq.getFile("item_medium_i");

		boolean largeImage = ParamUtil.get(
			uploadReq, "item_large_image", false);
		String largeImageURL = ParamUtil.getString(
			uploadReq, "item_large_image_url");
		File largeFile = uploadReq.getFile("item_large_i");

		if (Validator.isNull(itemId)) {

			// Add item

			ShoppingItem item = ShoppingItemServiceUtil.addItem(
				categoryId, sku, name, description, properties, supplierUserId,
				fieldsQuantities, requiresShipping, stockQuantity, featured,
				sale, smallImage, smallImageURL, smallFile, mediumImage,
				mediumImageURL, mediumFile, largeImage, largeImageURL,
				largeFile, itemFields, itemPrices);

			// Send redirect

			PortletURL portletURL = ((ActionResponseImpl)res).createRenderURL();

			portletURL.setParameter(
				"struts_action", "/shopping/view_item");
			portletURL.setParameter("item_id", item.getItemId());

			res.sendRedirect(portletURL.toString());
		}
		else {

			// Update item

			ShoppingItemServiceUtil.updateItem(
				itemId, categoryId, sku, name, description, properties,
				supplierUserId, fieldsQuantities, requiresShipping,
				stockQuantity, featured, sale, smallImage, smallImageURL,
				smallFile, mediumImage, mediumImageURL, mediumFile, largeImage,
				largeImageURL, largeFile, itemFields, itemPrices);

			// Send redirect

			res.sendRedirect(ParamUtil.getString(req, "redirect"));
		}
	}

}