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

package com.liferay.portlet.shopping.service.persistence;

import com.liferay.util.StringPool;
import com.liferay.util.lang.FastStringBuffer;

import java.io.Serializable;

/**
 * <a href="ShoppingOrderItemPK.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderItemPK implements Comparable, Serializable {
	public String orderId;
	public String itemId;

	public ShoppingOrderItemPK() {
	}

	public ShoppingOrderItemPK(String orderId, String itemId) {
		this.orderId = orderId;
		this.itemId = itemId;
	}

	public String getOrderId() {
		return orderId;
	}

	public void setOrderId(String orderId) {
		this.orderId = orderId;
	}

	public String getItemId() {
		return itemId;
	}

	public void setItemId(String itemId) {
		this.itemId = itemId;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingOrderItemPK pk = (ShoppingOrderItemPK)obj;
		int value = 0;
		value = orderId.compareTo(pk.orderId);

		if (value != 0) {
			return value;
		}

		value = itemId.compareTo(pk.itemId);

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingOrderItemPK pk = null;

		try {
			pk = (ShoppingOrderItemPK)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		if ((orderId.equals(pk.orderId)) && (itemId.equals(pk.itemId))) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (orderId + itemId).hashCode();
	}

	public String toString() {
		FastStringBuffer sb = new FastStringBuffer();
		sb.append(StringPool.OPEN_CURLY_BRACE);
		sb.append("orderId");
		sb.append(StringPool.EQUAL);
		sb.append(orderId);
		sb.append(StringPool.COMMA);
		sb.append(StringPool.SPACE);
		sb.append("itemId");
		sb.append(StringPool.EQUAL);
		sb.append(itemId);
		sb.append(StringPool.CLOSE_CURLY_BRACE);

		return sb.toString();
	}
}