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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.ListType;
import com.liferay.portal.model.Organization;
import com.liferay.portal.util.PropsUtil;

/**
 * <a href="ListTypeImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ListTypeImpl extends ListTypeModelImpl implements ListType {

	// Common

	public static final String ADDRESS = ".address";

	public static final String EMAIL_ADDRESS = ".emailAddress";

	public static final String PHONE = ".phone";

	public static final String WEBSITE = ".website";

	// Account

	public static final String ACCOUNT_ADDRESS =
		Account.class.getName() + ADDRESS;

	public static final int ACCOUNT_ADDRESS_DEFAULT =
		GetterUtil.getInteger(PropsUtil.get(PropsUtil.
			SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_ACCOUNT_ADDRESS));

	public static final String ACCOUNT_EMAIL_ADDRESS =
		Account.class.getName() + EMAIL_ADDRESS;

	public static final int ACCOUNT_EMAIL_ADDRESS_DEFAULT =
		GetterUtil.getInteger(PropsUtil.get(PropsUtil.
			SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_ACCOUNT_EMAIL_ADDRESS));

	public static final String ACCOUNT_PHONE =
		Account.class.getName() + PHONE;

	public static final String ACCOUNT_WEBSITE =
		Account.class.getName() + WEBSITE;

	// Contact

	public static final String CONTACT_ADDRESS =
		Contact.class.getName() + ADDRESS;

	public static final String CONTACT_EMAIL_ADDRESS =
		Contact.class.getName() + EMAIL_ADDRESS;

	public static final int CONTACT_EMAIL_ADDRESS_DEFAULT =
		GetterUtil.getInteger(PropsUtil.get(PropsUtil.
			SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_CONTACT_EMAIL_ADDRESS));

	public static final String CONTACT_PHONE =
		Contact.class.getName() + PHONE;

	public static final String CONTACT_PREFIX =
		Contact.class.getName() + ".prefix";

	public static final String CONTACT_SUFFIX =
		Contact.class.getName() + ".suffix";

	public static final String CONTACT_WEBSITE =
		Contact.class.getName() + WEBSITE;

	// Organization

	public static final String ORGANIZATION_ADDRESS =
		Organization.class.getName() + ADDRESS;

	public static final String ORGANIZATION_EMAIL_ADDRESS =
		Organization.class.getName() + EMAIL_ADDRESS;

	public static final String ORGANIZATION_PHONE =
		Organization.class.getName() + PHONE;

	public static final String ORGANIZATION_SERVICE =
		Organization.class.getName() + ".service";

	public static final String ORGANIZATION_STATUS =
		Organization.class.getName() + ".status";

	public static final int ORGANIZATION_STATUS_DEFAULT =
		GetterUtil.getInteger(PropsUtil.get(PropsUtil.
			SQL_DATA_COM_LIFERAY_PORTAL_MODEL_LISTTYPE_ORGANIZATION_STATUS));

	public static final String ORGANIZATION_WEBSITE =
		Organization.class.getName() + WEBSITE;

	public ListTypeImpl() {
	}

}