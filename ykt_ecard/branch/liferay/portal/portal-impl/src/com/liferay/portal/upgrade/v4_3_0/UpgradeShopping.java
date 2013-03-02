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

package com.liferay.portal.upgrade.v4_3_0;

import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.upgrade.util.DefaultPKMapper;
import com.liferay.portal.upgrade.util.DefaultUpgradeTableImpl;
import com.liferay.portal.upgrade.util.PKUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.SwapUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;
import com.liferay.portal.upgrade.util.UpgradeTable;
import com.liferay.portal.upgrade.util.ValueMapper;
import com.liferay.portal.upgrade.v4_3_0.util.AvailableMappersUtil;
import com.liferay.portal.upgrade.v4_3_0.util.ShoppingCartItemIdUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.ShoppingCartItemIdsUpgradeColumnImpl;
import com.liferay.portal.upgrade.v4_3_0.util.ShoppingCouponLimitCategoriesUpgradeColumnImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingCartImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingCategoryImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingCouponImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemFieldImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemPriceImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingOrderImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingOrderItemImpl;

import java.sql.Types;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeShopping.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeShopping extends UpgradeProcess {

	public void upgrade() throws UpgradeException {
		_log.info("Upgrading");

		try {
			doUpgrade();
		}
		catch (Exception e) {
			throw new UpgradeException(e);
		}
	}

	protected void doUpgrade() throws Exception {

		// ShoppingCategory

		UpgradeColumn upgradeGroupIdColumn = new SwapUpgradeColumnImpl(
			"groupId", AvailableMappersUtil.getGroupIdMapper());

		UpgradeColumn upgradeUserIdColumn = new SwapUpgradeColumnImpl(
			"userId", new Integer(Types.VARCHAR),
			AvailableMappersUtil.getUserIdMapper());

		PKUpgradeColumnImpl upgradePKColumn = new PKUpgradeColumnImpl(
			"categoryId", true);

		UpgradeTable upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingCategoryImpl.TABLE_NAME, ShoppingCategoryImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeGroupIdColumn, upgradeUserIdColumn);

		upgradeTable.setCreateSQL(ShoppingCategoryImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper categoryIdMapper = new DefaultPKMapper(
			upgradePKColumn.getValueMapper());

		AvailableMappersUtil.setShoppingCategoryIdMapper(categoryIdMapper);

		UpgradeColumn upgradeParentCategoryIdColumn = new SwapUpgradeColumnImpl(
			"parentCategoryId", categoryIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingCategoryImpl.TABLE_NAME, ShoppingCategoryImpl.TABLE_COLUMNS,
			upgradeParentCategoryIdColumn);

		upgradeTable.updateTable();

		UpgradeColumn upgradeCategoryIdColumn = new SwapUpgradeColumnImpl(
			"categoryId", categoryIdMapper);

		// ShoppingItem

		upgradePKColumn = new PKUpgradeColumnImpl("itemId", true);

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingItemImpl.TABLE_NAME, ShoppingItemImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeCategoryIdColumn, upgradeUserIdColumn);

		upgradeTable.setCreateSQL(ShoppingItemImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper itemIdMapper = upgradePKColumn.getValueMapper();

		AvailableMappersUtil.setShoppingItemIdMapper(itemIdMapper);

		UpgradeColumn upgradeItemIdColumn = new SwapUpgradeColumnImpl(
			"itemId", itemIdMapper);

		// ShoppingItemField

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingItemFieldImpl.TABLE_NAME,
			ShoppingItemFieldImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("itemFieldId", false), upgradeItemIdColumn);

		upgradeTable.setCreateSQL(ShoppingItemFieldImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// ShoppingItemPrice

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingItemPriceImpl.TABLE_NAME,
			ShoppingItemPriceImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("itemPriceId", false), upgradeItemIdColumn);

		upgradeTable.setCreateSQL(ShoppingItemPriceImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// ShoppingOrder

		upgradePKColumn = new PKUpgradeColumnImpl(
			"orderId", new Integer(Types.VARCHAR), true);

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingOrderImpl.TABLE_NAME, ShoppingOrderImpl.TABLE_COLUMNS,
			upgradePKColumn, upgradeGroupIdColumn, upgradeUserIdColumn);

		upgradeTable.setCreateSQL(ShoppingOrderImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		ValueMapper orderIdMapper = upgradePKColumn.getValueMapper();

		UpgradeColumn upgradeOrderIdColumn = new SwapUpgradeColumnImpl(
			"orderId", new Integer(Types.VARCHAR), orderIdMapper);

		// ShoppingOrderItem

		UpgradeColumn upgradeCartItemIdColumn =
			new ShoppingCartItemIdUpgradeColumnImpl(itemIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingOrderItemImpl.TABLE_NAME,
			ShoppingOrderItemImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl("orderItemId", false),
			upgradeOrderIdColumn, upgradeCartItemIdColumn);

		upgradeTable.setCreateSQL(ShoppingOrderItemImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// ShoppingCart

		UpgradeColumn upgradeItemIdsColumn =
			new ShoppingCartItemIdsUpgradeColumnImpl(itemIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingCartImpl.TABLE_NAME, ShoppingCartImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl(
				"cartId", new Integer(Types.VARCHAR), false),
			upgradeGroupIdColumn, upgradeUserIdColumn, upgradeItemIdsColumn);

		upgradeTable.setCreateSQL(ShoppingCartImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();

		// ShoppingCoupon

		UpgradeColumn upgradeLimitCategoriesColumn =
			new ShoppingCouponLimitCategoriesUpgradeColumnImpl(
				categoryIdMapper);

		upgradeTable = new DefaultUpgradeTableImpl(
			ShoppingCouponImpl.TABLE_NAME, ShoppingCouponImpl.TABLE_COLUMNS,
			new PKUpgradeColumnImpl(
				"couponId", new Integer(Types.VARCHAR), false),
			upgradeGroupIdColumn, upgradeUserIdColumn,
			upgradeLimitCategoriesColumn);

		upgradeTable.setCreateSQL(ShoppingCouponImpl.TABLE_SQL_CREATE);

		upgradeTable.updateTable();
	}

	private static Log _log = LogFactory.getLog(UpgradeShopping.class);

}