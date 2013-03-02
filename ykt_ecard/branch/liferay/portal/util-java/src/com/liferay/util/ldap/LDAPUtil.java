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

package com.liferay.util.ldap;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;

import javax.naming.NamingException;
import javax.naming.directory.Attribute;
import javax.naming.directory.Attributes;

/**
 * <a href="LDAPUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Toma Bedolla
 * @author Michael Young
 *
 */
public class LDAPUtil {

	public static String getAttributeValue(Attributes attrs, String id)
		throws NamingException {

		return getAttributeValue(attrs, id, StringPool.BLANK);
	}

	public static String getAttributeValue(
			Attributes attrs, String id, String defaultValue)
		throws NamingException {

		try {
			Attribute attr = attrs.get(id);

			Object obj = attr.get();

			return obj.toString();
		}
		catch (NullPointerException npe) {
			return defaultValue;
		}
	}

	public static String getFullProviderURL(String baseURL, String baseDN) {
		return baseURL + StringPool.SLASH + baseDN;
	}

	public static String[] splitFullName(String fullName) {
		String firstName = StringPool.BLANK;
		String lastName = StringPool.BLANK;
		String middleName = StringPool.BLANK;

		if (Validator.isNotNull(fullName)) {
			String[] name = StringUtil.split(fullName, " ");

			firstName = name[0];
			lastName = name[name.length - 1];
			middleName = StringPool.BLANK;

			if (name.length > 2) {
				for (int i = 1; i < name.length - 1; i++) {
					if (Validator.isNull(name[i].trim())) {
						continue;
					}

					if (i != 1) {
						middleName += " ";
					}

					middleName += name[i].trim();
				}
			}
		}
		else {
			firstName = GetterUtil.getString(firstName, lastName);
			lastName = firstName;
		}

		return new String[] {firstName, middleName, lastName};
	}

}