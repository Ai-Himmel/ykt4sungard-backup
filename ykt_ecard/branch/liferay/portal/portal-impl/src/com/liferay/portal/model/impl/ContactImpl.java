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

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Contact;

/**
 * <a href="ContactImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ContactImpl extends ContactModelImpl implements Contact {

	public static final long DEFAULT_PARENT_CONTACT_ID = 0;

	public static String getFullName(
		String firstName, String middleName, String lastName) {

		StringMaker sm = new StringMaker();

		if (Validator.isNull(middleName)) {
			sm.append(firstName);
			sm.append(StringPool.SPACE);
			sm.append(lastName);
		}
		else {
			sm.append(firstName);
			sm.append(StringPool.SPACE);
			sm.append(middleName);
			sm.append(StringPool.SPACE);
			sm.append(lastName);
		}

		return sm.toString();
	}

	public ContactImpl() {
	}

	public String getFullName() {
		return getFullName(getFirstName(), getMiddleName(), getLastName());
	}

}