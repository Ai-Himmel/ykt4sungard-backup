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

package com.liferay.portlet.addressbook.util;

import com.liferay.portlet.addressbook.model.ABContact;

import java.io.Serializable;

import java.text.DateFormat;

import java.util.Date;
import java.util.Map;

/**
 * <a href="Importer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public abstract class Importer implements Serializable {

	public abstract ABContact[] getContacts();

	public abstract void setData(byte[] bytes);

	protected Date getValue(String[] values, Map defs, String key,
							DateFormat df) {

		Date date = null;

		Integer pos = (Integer)defs.get(key);

		try {
			date = df.parse(values[pos.intValue()]);
		}
		catch (Exception e) {
		}

		return date;
	}

	protected String getValue(String[] values, Map defs, String key) {
		String value = null;

		Integer pos = (Integer)defs.get(key);

		try {
			value = values[pos.intValue()];
		}
		catch (Exception e) {
		}

		return value;
	}

}