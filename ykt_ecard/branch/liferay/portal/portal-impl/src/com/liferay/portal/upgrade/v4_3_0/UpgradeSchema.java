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

import com.liferay.portal.upgrade.SmartUpgradeSchema;

/**
 * <a href="UpgradeSchema.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpgradeSchema extends SmartUpgradeSchema {

	protected void upgradeOnce() throws Exception {
		runSQLTemplate("update-4.2.0-4.3.0.sql", false);

		for (int i = 0; i < _OLD_TABLES.length; i++) {
			try {
				runSQL("drop table " + _OLD_TABLES[i]);
			}
			catch (Exception e) {
			}
		}
	}

	private static final String[] _OLD_TABLES = new String[] {
		"ABContact", "ABContacts_ABLists", "ABList", "AdminConfig", "BJEntry",
		"BJTopic", "BJVerse", "CalTask", "ComicEntry",
		"ContactOrgDepartmentLevel", "DLFileProfile", "DLRepository",
		"MailReceipt", "NetworkAddress", "Note", "OrgDepartment", "ProjFirm",
		"ProjProject", "ProjTask", "ProjTime", "ResourceType",
		"Users_ComicEntries", "Users_ProjProjects"
	};

}