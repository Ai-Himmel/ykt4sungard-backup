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

package com.liferay.portal.util;

import com.liferay.portal.SystemException;
import com.liferay.portal.model.Properties;
import com.liferay.portal.service.spring.PropertiesServiceUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.ExtPropertiesLoader;
import com.liferay.util.StringUtil;

import java.util.Map;

/**
 * <a href="CompanyPropsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class CompanyPropsUtil {

	public static boolean containsKey(String companyId, String key) {
		if (get(companyId, key) != null) {
			return true;
		}
		else {
			return false;
		}
	}

	public static String get(String companyId, String key) {
		String value = null;

		try {
			java.util.Properties propsFromDatabase =
				PropertiesServiceUtil.getPortalProperties(companyId);

			value = propsFromDatabase.getProperty(key);
		}
		catch (SystemException se) {
		}

		if (value == null) {
			ExtPropertiesLoader propsFromFile = _getPropsFromFile(companyId);

			value = propsFromFile.get(key);
		}

		if (value == null) {
			value = PropsUtil.get(key);
		}

		return value;
	}

	public static String[] getArray(String companyId, String key) {
		String value = get(companyId,  key);

		if (value == null) {
			return new String[0];
		}
		else {
			return StringUtil.split(value);
		}
	}

	private static ExtPropertiesLoader _getPropsFromFile(String companyId) {
		ExtPropertiesLoader propsFromFile =
			(ExtPropertiesLoader)_propsFromFilePool.get(companyId);

		if (propsFromFile == null) {
			propsFromFile = new ExtPropertiesLoader();

			propsFromFile.init(Properties.PORTAL, companyId);

			_propsFromFilePool.put(companyId, propsFromFile);
		}

		return propsFromFile;
	}

	private static Map _propsFromFilePool = CollectionFactory.getSyncHashMap();

}