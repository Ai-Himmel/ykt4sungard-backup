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
import com.liferay.util.CollectionFactory;
import com.liferay.util.StringUtil;

import java.io.BufferedReader;
import java.io.StringReader;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * <a href="YahooImporter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class YahooImporter extends Importer {

	public ABContact[] getContacts() {
		return _contacts;
	}

	public void setData(byte[] bytes) {
		BufferedReader br = null;

		try {
			br = new BufferedReader(new StringReader(new String(bytes)));

			// Get first line

			String line = br.readLine();

			// Strip leading and trailing "

			line = line.substring(1, line.length() - 1);

			// Get column definitions

			Map defs = CollectionFactory.getHashMap();

			String[] defsArray = StringUtil.split(line, "\",\"");

			for (int i = 0; i < defsArray.length; i++) {
				defs.put(defsArray[i], new Integer(i));
			}

			DateFormat df = new SimpleDateFormat("mm/dd/yyyy");

			List contacts = new ArrayList();

			while ((line = br.readLine()) != null) {

				// Strip leading and trailing "

				line = line.substring(1, line.length() - 1);

				// Get column values

				String[] values = StringUtil.split(line, "\",\"");

				// Create contact

				contacts.add(_createContact(values, defs, df));
			}

			_contacts = (ABContact[])contacts.toArray(new ABContact[0]);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			if (br != null) {
				try {
					br.close();
				}
				catch (Exception e) {
				}
			}
		}
	}

	private ABContact _createContact(String[] values, Map defs, DateFormat df) {
		ABContact c = new ABContact(null);

		c.setFirstName(getValue(values, defs, "First"));
		c.setLastName(getValue(values, defs, "Last"));
		c.setEmailAddress(getValue(values, defs, "Email"));

		c.setHomeStreet(getValue(values, defs, "Home Address"));
		c.setHomeCity(getValue(values, defs, "Home City"));
		c.setHomeState(getValue(values, defs, "Home State"));
		c.setHomeZip(getValue(values, defs, "Home ZIP"));
		c.setHomeCountry(getValue(values, defs, "Home Country"));
		c.setHomePhone(getValue(values, defs, "Home"));
		c.setHomeFax(getValue(values, defs, "Fax"));
		c.setHomeCell(getValue(values, defs, "Mobile"));

		c.setBusinessCompany(getValue(values, defs, "Company"));
		c.setBusinessStreet(getValue(values, defs, "Work Address"));
		c.setBusinessCity(getValue(values, defs, "Work City"));
		c.setBusinessState(getValue(values, defs, "Work State"));
		c.setBusinessZip(getValue(values, defs, "Work ZIP"));
		c.setBusinessCountry(getValue(values, defs, "Work Country"));
		c.setBusinessPhone(getValue(values, defs, "Work"));

		c.setBirthday(getValue(values, defs, "Birthday", df));
		c.setWebsite(getValue(values, defs, "Personal Website"));

		return c;
	}

	private ABContact[] _contacts;

}