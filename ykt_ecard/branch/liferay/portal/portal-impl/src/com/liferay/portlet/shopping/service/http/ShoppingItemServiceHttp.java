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

package com.liferay.portlet.shopping.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.http.TunnelUtil;

import com.liferay.portlet.shopping.service.ShoppingItemServiceUtil;

/**
 * <a href="ShoppingItemServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portlet.shopping.service.ShoppingItemServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it requires an
 * additional <code>com.liferay.portal.security.auth.HttpPrincipal</code>
 * parameter.
 * </p>
 *
 * <p>
 * The benefits of using the HTTP utility is that it is fast and allows for
 * tunneling without the cost of serializing to text. The drawback is that it
 * only works with Java.
 * </p>
 *
 * <p>
 * Set the property <code>tunnel.servlet.hosts.allowed</code> in
 * portal.properties to configure security.
 * </p>
 *
 * <p>
 * The HTTP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.security.auth.HttpPrincipal
 * @see com.liferay.portlet.shopping.service.ShoppingItemServiceUtil
 * @see com.liferay.portlet.shopping.service.http.ShoppingItemServiceSoap
 *
 */
public class ShoppingItemServiceHttp {
	public static void addBookItems(HttpPrincipal httpPrincipal,
		long categoryId, java.lang.String[] isbns)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(categoryId);

			Object paramObj1 = isbns;

			if (isbns == null) {
				paramObj1 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingItemServiceUtil.class.getName(),
					"addBookItems", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem addItem(
		HttpPrincipal httpPrincipal, long categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(categoryId);

			Object paramObj1 = sku;

			if (sku == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = name;

			if (name == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = description;

			if (description == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = properties;

			if (properties == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = fieldsQuantities;

			if (fieldsQuantities == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = new BooleanWrapper(requiresShipping);

			Object paramObj7 = new IntegerWrapper(stockQuantity);

			Object paramObj8 = new BooleanWrapper(featured);

			Object paramObj9 = sale;

			if (sale == null) {
				paramObj9 = new NullWrapper("java.lang.Boolean");
			}

			Object paramObj10 = new BooleanWrapper(smallImage);

			Object paramObj11 = smallImageURL;

			if (smallImageURL == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = smallFile;

			if (smallFile == null) {
				paramObj12 = new NullWrapper("java.io.File");
			}

			Object paramObj13 = new BooleanWrapper(mediumImage);

			Object paramObj14 = mediumImageURL;

			if (mediumImageURL == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = mediumFile;

			if (mediumFile == null) {
				paramObj15 = new NullWrapper("java.io.File");
			}

			Object paramObj16 = new BooleanWrapper(largeImage);

			Object paramObj17 = largeImageURL;

			if (largeImageURL == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = largeFile;

			if (largeFile == null) {
				paramObj18 = new NullWrapper("java.io.File");
			}

			Object paramObj19 = itemFields;

			if (itemFields == null) {
				paramObj19 = new NullWrapper("java.util.List");
			}

			Object paramObj20 = itemPrices;

			if (itemPrices == null) {
				paramObj20 = new NullWrapper("java.util.List");
			}

			Object paramObj21 = new BooleanWrapper(addCommunityPermissions);

			Object paramObj22 = new BooleanWrapper(addGuestPermissions);

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingItemServiceUtil.class.getName(),
					"addItem",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingItem)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem addItem(
		HttpPrincipal httpPrincipal, long categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(categoryId);

			Object paramObj1 = sku;

			if (sku == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = name;

			if (name == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = description;

			if (description == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = properties;

			if (properties == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = fieldsQuantities;

			if (fieldsQuantities == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = new BooleanWrapper(requiresShipping);

			Object paramObj7 = new IntegerWrapper(stockQuantity);

			Object paramObj8 = new BooleanWrapper(featured);

			Object paramObj9 = sale;

			if (sale == null) {
				paramObj9 = new NullWrapper("java.lang.Boolean");
			}

			Object paramObj10 = new BooleanWrapper(smallImage);

			Object paramObj11 = smallImageURL;

			if (smallImageURL == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = smallFile;

			if (smallFile == null) {
				paramObj12 = new NullWrapper("java.io.File");
			}

			Object paramObj13 = new BooleanWrapper(mediumImage);

			Object paramObj14 = mediumImageURL;

			if (mediumImageURL == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = mediumFile;

			if (mediumFile == null) {
				paramObj15 = new NullWrapper("java.io.File");
			}

			Object paramObj16 = new BooleanWrapper(largeImage);

			Object paramObj17 = largeImageURL;

			if (largeImageURL == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = largeFile;

			if (largeFile == null) {
				paramObj18 = new NullWrapper("java.io.File");
			}

			Object paramObj19 = itemFields;

			if (itemFields == null) {
				paramObj19 = new NullWrapper("java.util.List");
			}

			Object paramObj20 = itemPrices;

			if (itemPrices == null) {
				paramObj20 = new NullWrapper("java.util.List");
			}

			Object paramObj21 = communityPermissions;

			if (communityPermissions == null) {
				paramObj21 = new NullWrapper("[Ljava.lang.String;");
			}

			Object paramObj22 = guestPermissions;

			if (guestPermissions == null) {
				paramObj22 = new NullWrapper("[Ljava.lang.String;");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingItemServiceUtil.class.getName(),
					"addItem",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingItem)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deleteItem(HttpPrincipal httpPrincipal, long itemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(itemId);

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingItemServiceUtil.class.getName(),
					"deleteItem", new Object[] { paramObj0 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItem(
		HttpPrincipal httpPrincipal, long itemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(itemId);

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingItemServiceUtil.class.getName(),
					"getItem", new Object[] { paramObj0 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingItem)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem updateItem(
		HttpPrincipal httpPrincipal, long itemId, long categoryId,
		java.lang.String sku, java.lang.String name,
		java.lang.String description, java.lang.String properties,
		java.lang.String fieldsQuantities, boolean requiresShipping,
		int stockQuantity, boolean featured, java.lang.Boolean sale,
		boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, boolean mediumImage,
		java.lang.String mediumImageURL, java.io.File mediumFile,
		boolean largeImage, java.lang.String largeImageURL,
		java.io.File largeFile, java.util.List itemFields,
		java.util.List itemPrices)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(itemId);

			Object paramObj1 = new LongWrapper(categoryId);

			Object paramObj2 = sku;

			if (sku == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = name;

			if (name == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = description;

			if (description == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = properties;

			if (properties == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = fieldsQuantities;

			if (fieldsQuantities == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = new BooleanWrapper(requiresShipping);

			Object paramObj8 = new IntegerWrapper(stockQuantity);

			Object paramObj9 = new BooleanWrapper(featured);

			Object paramObj10 = sale;

			if (sale == null) {
				paramObj10 = new NullWrapper("java.lang.Boolean");
			}

			Object paramObj11 = new BooleanWrapper(smallImage);

			Object paramObj12 = smallImageURL;

			if (smallImageURL == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = smallFile;

			if (smallFile == null) {
				paramObj13 = new NullWrapper("java.io.File");
			}

			Object paramObj14 = new BooleanWrapper(mediumImage);

			Object paramObj15 = mediumImageURL;

			if (mediumImageURL == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = mediumFile;

			if (mediumFile == null) {
				paramObj16 = new NullWrapper("java.io.File");
			}

			Object paramObj17 = new BooleanWrapper(largeImage);

			Object paramObj18 = largeImageURL;

			if (largeImageURL == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = largeFile;

			if (largeFile == null) {
				paramObj19 = new NullWrapper("java.io.File");
			}

			Object paramObj20 = itemFields;

			if (itemFields == null) {
				paramObj20 = new NullWrapper("java.util.List");
			}

			Object paramObj21 = itemPrices;

			if (itemPrices == null) {
				paramObj21 = new NullWrapper("java.util.List");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingItemServiceUtil.class.getName(),
					"updateItem",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingItem)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(ShoppingItemServiceHttp.class);
}