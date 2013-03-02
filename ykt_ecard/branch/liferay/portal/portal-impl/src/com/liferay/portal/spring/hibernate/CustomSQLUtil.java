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

package com.liferay.portal.spring.hibernate;

import com.liferay.portal.kernel.util.OrderByComparator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CustomSQLUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Bruno Farache
 *
 */
public class CustomSQLUtil {

	public static String get(String id) {
		return _instance._portalCustomSQLUtil.get(id);
	}

	public static boolean isVendorDB2() {
		return _instance._portalCustomSQLUtil.isVendorDB2();
	}

	public static boolean isVendorInformix() {
		return _instance._portalCustomSQLUtil.isVendorInformix();
	}

	public static boolean isVendorMySQL() {
		return _instance._portalCustomSQLUtil.isVendorMySQL();
	}

	public static boolean isVendorOracle() {
		return _instance._portalCustomSQLUtil.isVendorOracle();
	}

	public static boolean isVendorSybase() {
		return _instance._portalCustomSQLUtil.isVendorSybase();
	}

	public static String[] keywords(String keywords) {
		return _instance._portalCustomSQLUtil.keywords(keywords);
	}

	public static String[] keywords(String keywords, boolean lowerCase) {
		return _instance._portalCustomSQLUtil.keywords(keywords, lowerCase);
	}

	public static String[] keywords(String[] keywordsArray) {
		return _instance._portalCustomSQLUtil.keywords(keywordsArray);
	}

	public static String[] keywords(String[] keywordsArray, boolean lowerCase) {
		return _instance._portalCustomSQLUtil.keywords(
			keywordsArray, lowerCase);
	}

	public static String replaceAndOperator(String sql, boolean andOperator) {
		return _instance._portalCustomSQLUtil.replaceAndOperator(
			sql, andOperator);
	}

	public static String replaceIsNull(String sql) {
		return _instance._portalCustomSQLUtil.replaceIsNull(sql);
	}

	public static String replaceKeywords(
		String sql, String field, String operator, boolean last,
		String[] values) {

		return _instance._portalCustomSQLUtil.replaceKeywords(
			sql, field, operator, last, values);
	}

	public static String removeOrderBy(String sql) {
		return _instance._portalCustomSQLUtil.removeOrderBy(sql);
	}

	public static String replaceOrderBy(String sql, OrderByComparator obc) {
		return _instance._portalCustomSQLUtil.replaceOrderBy(sql, obc);
	}

	private CustomSQLUtil() {
		try {
			_portalCustomSQLUtil = new PortalCustomSQLUtil();
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private static Log _log = LogFactory.getLog(CustomSQLUtil.class);

	private static CustomSQLUtil _instance = new CustomSQLUtil();

	private PortalCustomSQLUtil _portalCustomSQLUtil;

}